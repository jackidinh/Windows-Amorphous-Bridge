#include <zmq.hpp>
#include <iostream>
#include <nng.h>
#include <nng/protocol/pubsub0/pub.h>

int main() {
    zmq::context_t context(1);
    zmq::socket_t subscriber(context, zmq::socket_type::sub);

    subscriber.connect("tcp://localhost:5555");
    subscriber.set(zmq::sockopt::subscribe, "");  // Subscribe to all messages

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

        std::string message(static_cast<char*>(zmq_msg.data()), zmq_msg.size());
        std::cout << "Received: " << message << std::endl;
    }
    return 0;
}
