#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include "AreaSearchStatus.pb.h"
#include <string>

void subscriber_thread(zmq::context_t& context) {
    zmq::socket_t subscriber(context, zmq::socket_type::sub);
    subscriber.connect("tcp://localhost:5560");
    subscriber.set(zmq::sockopt::subscribe, "");
    //C:\vcpkg\installed\x64-windows\include\google\protobuf\io\coded_stream.h

    try {
        while (true) {
            zmq::message_t msg;
            subscriber.recv(msg, zmq::recv_flags::none);
            std::string data(static_cast<char*>(msg.data()), msg.size());

            //Person received_person;
            AreaSearchStatus::AreaSearchStatus statTest1;
            if (statTest1.ParseFromString(data)) {
                
                std::cout << "\n=== Received Protobuf Message ===" << std::endl;
                std::cout << "Vehicle ID: " << statTest1.vehicle_id() << std::endl;
                std::cout << "Timestamp (epoch usec): " << statTest1.timestamp_epoch_usec() << std::endl;
                std::cout << "Estimated Completion Time (epoch usec): " << statTest1.estimated_completion_time_epoch_usec() << std::endl;
                std::cout << "Estimated Percent Complete: " << statTest1.estimated_percent_complete() << "%" << std::endl;

                std::cout << "\n--- Heatmap Bounding Box ---" << std::endl;
                std::cout << "Bottom Right Point:" << std::endl;
                std::cout << "  Latitude: " << statTest1.heatmap_bounding_box().bottom_right_point().latitude_deg() << std::endl;
                std::cout << "  Longitude: " << statTest1.heatmap_bounding_box().bottom_right_point().longitude_deg() << std::endl;
                std::cout << "  Altitude MSL: " << statTest1.heatmap_bounding_box().bottom_right_point().altitude_msl_m() << "m" << std::endl;

                std::cout << "Upper Left Point:" << std::endl;
                std::cout << "  Latitude: " << statTest1.heatmap_bounding_box().upper_left_point().latitude_deg() << std::endl;
                std::cout << "  Longitude: " << statTest1.heatmap_bounding_box().upper_left_point().longitude_deg() << std::endl;
                std::cout << "  Altitude MSL: " << statTest1.heatmap_bounding_box().upper_left_point().altitude_msl_m() << "m" << std::endl;

                std::cout << "\n--- Heatmap Data ---" << std::endl;
                std::cout << "Dimensions: " << statTest1.heatmap_width() << " x " << statTest1.heatmap_height() << std::endl;
                std::cout << "Data (" << statTest1.heatmap_data_size() << " bytes): ";
                for (int i = 0; i < statTest1.heatmap_data_size(); ++i) {
                    std::cout << (int)statTest1.heatmap_data(i) << " ";
                }
                std::cout << std::endl;

                std::cout << "\n--- Geometry Information ---" << std::endl;
                if (statTest1.has_circle()) {
                    std::cout << "Circle:" << std::endl;
                    std::cout << "  Center: " << statTest1.circle().center() << std::endl;
                    std::cout << "  Radius: " << statTest1.circle().radius_m() << "m" << std::endl;
                }

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

  
    AreaSearchStatus::AreaSearchStatus statTest;
    auto* georectangle = statTest.mutable_heatmap_bounding_box();
    AreaSearchStatus::GeoCircle geocircle;
  
    statTest.set_vehicle_id(1);
    statTest.set_timestamp_epoch_usec(25);
    statTest.set_estimated_completion_time_epoch_usec(45);
    statTest.set_estimated_percent_complete(50);
    //GeoRectangle
    //1st geopoint
    georectangle->mutable_bottom_right_point()->set_altitude_msl_m(61.3);
    georectangle->mutable_bottom_right_point()->set_latitude_deg(3.14);
    georectangle->mutable_bottom_right_point()->set_longitude_deg(78.0);
    //2nd geopoint
    georectangle->mutable_upper_left_point()->set_altitude_msl_m(65.5);
    georectangle->mutable_upper_left_point()->set_latitude_deg(28.9);
    georectangle->mutable_upper_left_point()->set_longitude_deg(77.6);

    //statTest.set_allocated_heatmap_bounding_box(&georectangle);

    statTest.set_heatmap_height(3); //f
    statTest.set_heatmap_width(4); //0
    
    for (int i = 0; i < 10; ++i) {
        statTest.add_heatmap_data(i);
    }
    statTest.mutable_circle()->set_center(56.2);
    statTest.mutable_circle()->set_radius_m(45.2);


    std::string serialized;
    statTest.SerializeToString(&serialized);

    /*std::cout << "Here is the serialized data:\n";
    for (char c : serialized) {
        std::cout << std::hex << (int)(unsigned char)c << " ";
    }
    std::cout << "\n";*/

    std::this_thread::sleep_for(std::chrono::seconds(1));

    while (true) {
        publisher.send(zmq::buffer(serialized), zmq::send_flags::none);
        /*std::cout << "\n=== Sent Protobuf Message ===" << std::endl;
        std::cout << "Vehicle ID: " << statTest.vehicle_id() << std::endl;
        std::cout << "Timestamp (epoch usec): " << statTest.timestamp_epoch_usec() << std::endl;
        std::cout << "Estimated Completion Time (epoch usec): " << statTest.estimated_completion_time_epoch_usec() << std::endl;
        std::cout << "Estimated Percent Complete: " << statTest.estimated_percent_complete() << "%" << std::endl;

        std::cout << "\n--- Heatmap Bounding Box ---" << std::endl;
        std::cout << "Bottom Right Point:" << std::endl;
        std::cout << "  Latitude: " << statTest.heatmap_bounding_box().bottom_right_point().latitude_deg() << std::endl;
        std::cout << "  Longitude: " << statTest.heatmap_bounding_box().bottom_right_point().longitude_deg() << std::endl;
        std::cout << "  Altitude MSL: " << statTest.heatmap_bounding_box().bottom_right_point().altitude_msl_m() << "m" << std::endl;

        std::cout << "Upper Left Point:" << std::endl;
        std::cout << "  Latitude: " << statTest.heatmap_bounding_box().upper_left_point().latitude_deg() << std::endl;
        std::cout << "  Longitude: " << statTest.heatmap_bounding_box().upper_left_point().longitude_deg() << std::endl;
        std::cout << "  Altitude MSL: " << statTest.heatmap_bounding_box().upper_left_point().altitude_msl_m() << "m" << std::endl;

        std::cout << "\n--- Heatmap Data ---" << std::endl;
        std::cout << "Dimensions: " << statTest.heatmap_width() << " x " << statTest.heatmap_height() << std::endl;
        std::cout << "Data (" << statTest.heatmap_data_size() << " bytes): ";
        for (int i = 0; i < statTest.heatmap_data_size(); ++i) {
            std::cout << (int)statTest.heatmap_data(i) << " ";
        }
        std::cout << std::endl;

        std::cout << "\n--- Geometry Information ---" << std::endl;
        if (statTest.has_circle()) {
            std::cout << "Circle:" << std::endl;
            std::cout << "  Center: " << statTest.circle().center() << std::endl;
            std::cout << "  Radius: " << statTest.circle().radius_m() << "m" << std::endl;
        }*/


        std::this_thread::sleep_for(std::chrono::seconds(1));

    }
    return 0;
}


