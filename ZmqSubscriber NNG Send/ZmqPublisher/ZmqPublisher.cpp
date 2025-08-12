#include <zmq.hpp>
#include <iostream>
#include <nng.h>
#include <nng/protocol/pubsub0/pub.h>
#include <nng/protocol/pubsub0/sub.h>
#include "person.pb.h"
#include <string>
#include <thread>
#include <flatbuffers/flatbuffers.h>
//#include "person_generated.h"
#include "example_Generated_PBtoFB.h"


void publisher_thread(zmq::context_t& context) {
    zmq::socket_t publisher(context, zmq::socket_type::pub);
    publisher.bind("tcp://*:5560");


    nng_socket sock;
    int rv;

    if ((rv = nng_sub0_open(&sock)) != 0) {
        std::cout << "Failed to open sub socket\n";
        return;
    }

    if ((rv = nng_setopt(sock, NNG_OPT_SUB_SUBSCRIBE, "", 0)) != 0) {
        std::cout << "Failed to set subscriber option\n";
        nng_close(sock);
        return;
    }
    
    while ((rv = nng_dial(sock, "tcp://127.0.0.1:5561", NULL, 0)) != 0) {
        std::cout << "Failed to connect to publisher, retrying...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }


    std::cout << "Connected to publisher. Waiting for messages...\n";

    while (true) {
        nng_msg* msg = nullptr;

        rv = nng_recvmsg(sock, &msg, 0);
        if (rv != 0) {
            std::cout << "NNG receive failed.\n";
            continue;
        }
        std::cout << "RECEIVED from NNG inside of thread!\n";
        size_t len = nng_msg_len(msg);
        void* data = nng_msg_body(msg);

        //convert data to proto
        example_Person_table_t x = example_Person_as_root(data);
        example::Person converted_pb_person;
        example::CreatePBFromPerson(x, converted_pb_person);
        std::string converted_pb_serialized;
        if (!converted_pb_person.SerializeToString(&converted_pb_serialized)) {
            return;
        }


        try {
            publisher.send(zmq::buffer(converted_pb_serialized), zmq::send_flags::none);
            std::cout << "Sent through ZMQ inside of thread!\n";
        }
        catch (const zmq::error_t& e) {
            std::cout << "ZMQ send error\n";
        }
        nng_msg_free(msg);
    }
    nng_close(sock);



}

int main() {
    zmq::context_t context(1);
    zmq::socket_t subscriber(context, zmq::socket_type::sub);

    subscriber.connect("tcp://localhost:5555");
    subscriber.set(zmq::sockopt::subscribe, "");  // Subscribe to all messages

    std::thread pub_thread(publisher_thread, std::ref(context));

    nng_socket sock;
    int rv;
    if ((rv = nng_pub0_open(&sock)) != 0) {
        std::cout << "Failed to open pub socket\n";
        return 1;
    }

    if ((rv = nng_listen(sock, "tcp://0.0.0.0:5554", NULL, 0)) != 0) {
        std::cout << "Failed to listen.\n";
        nng_close(sock);
        return 1;
    }
    std::cout << "Publisher listening on tcp://0.0.0.0:5554\n";

    std::cout << "Bridging ZMQ->NNG (ZMQ sub to NNG pub) running...\n";

    
    while (true) {
        zmq::message_t zmq_msg;
        subscriber.recv(zmq_msg, zmq::recv_flags::none);


        std::string serialized(static_cast<char*>(zmq_msg.data()), zmq_msg.size());
        example::Person received;

        if (received.ParseFromString(serialized)) {
            std::cout << "Received Person:\n";
            std::cout << "Name: " << received.name() << "\n";
            std::cout << "ID: " << received.id() << "\n";
        }
        //temporary hard coded conversion, include converter here

        flatcc_builder_t builder2, * B2;
        flatcc_builder_init(&builder2);
        B2 = &builder2;
        example_Person_start_as_root(B2);
        example::CreatePersonFromPB(B2, received);
        example_Person_end_as_root(B2);
        size_t sizee;
        void* converted_fb_buf = flatcc_builder_finalize_aligned_buffer(B2, &sizee);
        flatcc_builder_clear(&builder2);


        nng_msg* nng_msg = nullptr;
        rv = nng_msg_alloc(&nng_msg, sizee);
        if (rv != 0) {
            std::cout << "NNG msg alloc failed." << "\n";
            continue;
        }

        memcpy(nng_msg_body(nng_msg), converted_fb_buf, sizee);

        rv = nng_sendmsg(sock, nng_msg, 0);
        if (rv != 0) {
            std::cout << "NNG send failed. " << "\n";
            nng_msg_free(nng_msg); // safe to free on failure
        }
        else {
            std::cout << "Forwarded message of size " << sizee << "\n";
        }


    }
    nng_close(sock);
    return 0;
}
