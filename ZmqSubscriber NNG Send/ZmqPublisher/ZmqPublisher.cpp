#include <zmq.hpp>
#include <iostream>
#include <nng.h>
#include <nng/protocol/pubsub0/pub.h>
#include <nng/protocol/pubsub0/sub.h>
#include "person.pb.h"
#include <string>
#include <thread>

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
    
    if ((rv = nng_dial(sock, "tcp://127.0.0.1:5561",NULL,0)) != 0) {
        std::cout << "Failed to connect to publisher\n";
        nng_close(sock);
        return;
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

        zmq::message_t zmq_msg(len);
        memcpy(zmq_msg.data(), data, len);

        try {
            publisher.send(zmq_msg, zmq::send_flags::none);
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

        const void* data = zmq_msg.data();
        size_t len = zmq_msg.size();

        nng_msg* nng_msg = nullptr;
        rv = nng_msg_alloc(&nng_msg, len);
        if (rv != 0) {
            std::cout << "NNG msg alloc failed." << "\n";
            continue;
        }

        memcpy(nng_msg_body(nng_msg), data, len);

        rv = nng_sendmsg(sock, nng_msg, 0);
        if (rv != 0) {
            std::cout << "NNG send failed. " << "\n";
            nng_msg_free(nng_msg); // safe to free on failure
        }
        else {
            std::cout << "Forwarded message of size " << len << "\n";
        }

        std::string serialized(static_cast<char*>(zmq_msg.data()), zmq_msg.size());
        Person received;

        if (received.ParseFromString(serialized)) {
            std::cout << "Received Person:\n";
            std::cout << "Name: " << received.name() << "\n";
            std::cout << "ID: " << received.id() << "\n";
        }
    }
    nng_close(sock);
    return 0;
}
