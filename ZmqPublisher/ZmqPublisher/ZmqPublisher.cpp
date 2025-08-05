#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    zmq::context_t context(1);
    zmq::socket_t publisher(context, zmq::socket_type::pub);

    publisher.bind("tcp://*:5555");

    int count = 0;
    while (true) {
        std::string message = "Hello ZeroMQ " + std::to_string(count++);
        zmq::message_t zmq_msg(message.c_str(), message.size());
        publisher.send(zmq_msg, zmq::send_flags::none);
        std::cout << "Sent: " << message << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}


