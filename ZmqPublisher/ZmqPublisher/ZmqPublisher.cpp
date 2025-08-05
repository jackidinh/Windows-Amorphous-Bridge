#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include "person.pb.h"
#include <string>



int main() {
    zmq::context_t context(1);
    zmq::socket_t publisher(context, zmq::socket_type::pub);

    publisher.bind("tcp://*:5555");

    Person olivia;
    olivia.set_name("Olivia");
    olivia.set_id(9);

    std::string serialized;
    olivia.SerializeToString(&serialized);

    int count = 0;
    while (true) {
        publisher.send(zmq::buffer(serialized), zmq::send_flags::none);
        std::cout << "Sent Protobuf Message: " << olivia.name()<<" with id: "<<olivia.id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}


