#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include "person.pb.h"
#include <string>

void subscriber_thread(zmq::context_t& context) {
    zmq::socket_t subscriber(context, zmq::socket_type::sub);
    subscriber.connect("tcp://localhost:5560");
    subscriber.set(zmq::sockopt::subscribe, "");

    try {
        while (true) {
            zmq::message_t msg;
            subscriber.recv(msg, zmq::recv_flags::none);
            std::string data(static_cast<char*>(msg.data()), msg.size());

            Person received_person;
            if (received_person.ParseFromString(data)) {
                std::cout << "Person Received " << received_person.name()<<"\n" << std::endl;

            }
            else {
                std::cout << "Failed to parse message\n";
            }
        }
    }
    catch (const zmq::error_t& e) {
        std::cout << "Exiting thread\n";
    }

}

int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    zmq::context_t context(1);
    zmq::socket_t publisher(context, zmq::socket_type::pub);

    publisher.bind("tcp://*:5555");

    std::thread sub_thread(subscriber_thread, std::ref(context));

    Person olivia;
    olivia.set_name("Olivia");
    olivia.set_id(9);

    std::string serialized;
    olivia.SerializeToString(&serialized);

    std::cout << "Here is the serialized data:\n";
    for (char c : serialized) {
        std::cout << std::hex << (int)(unsigned char)c << " ";
    }
    std::cout << "\n";

    std::this_thread::sleep_for(std::chrono::seconds(1));

    while (true) {
        publisher.send(zmq::buffer(serialized), zmq::send_flags::none);
        std::cout << "Sent Protobuf Message: " << olivia.name()<<" with id: "<<olivia.id() << "\n" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }
    return 0;
}


