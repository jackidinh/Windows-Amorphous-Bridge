#include <zmq.hpp>
#include <iostream>
#include <nng.h>
#include <nng/protocol/pubsub0/pub.h>
#include <nng/protocol/pubsub0/sub.h>
#include "AreaSearchStatus.pb.h"

#include <string>
#include <thread>
#include <flatbuffers/flatbuffers.h>
//#include "person_generated.h"
#include "AreaSearchStatus_Generated_PBtoFB.h"


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
        AreaSearchStatus_AreaSearchStatus_table_t x = AreaSearchStatus_AreaSearchStatus_as_root(data);
        //example::Person converted_pb_person;
        AreaSearchStatus::AreaSearchStatus convertedPbPerson;
        //example::CreatePBFromPerson(x, converted_pb_person);
        AreaSearchStatus::CreatePBFromAreaSearchStatus(x, convertedPbPerson);
        std::string converted_pb_serialized;
        if (!convertedPbPerson.SerializeToString(&converted_pb_serialized)) {
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
        //example::Person received;
        AreaSearchStatus::AreaSearchStatus received;

        if (received.ParseFromString(serialized)) {
            std::cout << "Received Person:\n";
            //std::cout << "Name: " << received.name() << "\n";
            std::cout << "ID: " << received.vehicle_id() << "\n";
            std::cout << "Bottom right Point " << received.heatmap_bounding_box().bottom_right_point().altitude_msl_m() << "\n";
        }
        //temporary hard coded conversion, include converter here

        flatcc_builder_t builder2, * B2;
        flatcc_builder_init(&builder2);
        B2 = &builder2;
        AreaSearchStatus_AreaSearchStatus_start_as_root(B2);
        AreaSearchStatus::CreateAreaSearchStatusFromPB(B2, received);
        AreaSearchStatus_AreaSearchStatus_end_as_root(B2);
       
        size_t sizee;
        void* converted_fb_buf = flatcc_builder_finalize_aligned_buffer(B2, &sizee);

        if (converted_fb_buf) {
            AreaSearchStatus_AreaSearchStatus_table_t root = AreaSearchStatus_AreaSearchStatus_as_root(converted_fb_buf);

            std::cout << "\n=== Converted FlatBuffer Message ===" << std::endl;
            std::cout << "Buffer Size: " << sizee << " bytes" << std::endl;
            std::cout << "Vehicle ID: " << AreaSearchStatus_AreaSearchStatus_vehicle_id(root) << std::endl;
            std::cout << "Timestamp (epoch usec): " << AreaSearchStatus_AreaSearchStatus_timestamp_epoch_usec(root) << std::endl;
            std::cout << "Estimated Completion Time (epoch usec): " << AreaSearchStatus_AreaSearchStatus_estimated_completion_time_epoch_usec(root) << std::endl;
            std::cout << "Estimated Percent Complete: " << AreaSearchStatus_AreaSearchStatus_estimated_percent_complete(root) << "%" << std::endl;

            // Heatmap bounding box
            auto bbox = AreaSearchStatus_AreaSearchStatus_heatmap_bounding_box(root);
            if (bbox) {
                std::cout << "\n--- Heatmap Bounding Box ---" << std::endl;

                auto bottom_right = AreaSearchStatus_GeoRectangle_bottom_right_point(bbox);
                if (bottom_right) {
                    std::cout << "Bottom Right Point:" << std::endl;
                    std::cout << "  Latitude: " << AreaSearchStatus_GeoPoint_latitude_deg(bottom_right) << std::endl;
                    std::cout << "  Longitude: " << AreaSearchStatus_GeoPoint_longitude_deg(bottom_right) << std::endl;
                    std::cout << "  Altitude MSL: " << AreaSearchStatus_GeoPoint_altitude_msl_m(bottom_right) << "m" << std::endl;
                }

                auto upper_left = AreaSearchStatus_GeoRectangle_upper_left_point(bbox);
                if (upper_left) {
                    std::cout << "Upper Left Point:" << std::endl;
                    std::cout << "  Latitude: " << AreaSearchStatus_GeoPoint_latitude_deg(upper_left) << std::endl;
                    std::cout << "  Longitude: " << AreaSearchStatus_GeoPoint_longitude_deg(upper_left) << std::endl;
                    std::cout << "  Altitude MSL: " << AreaSearchStatus_GeoPoint_altitude_msl_m(upper_left) << "m" << std::endl;
                }
            }
            else {
                std::cout << "\n--- Heatmap Bounding Box ---" << std::endl;
                std::cout << "No bounding box data" << std::endl;
            }

            // Heatmap data
            std::cout << "\n--- Heatmap Data ---" << std::endl;
            std::cout << "Dimensions: " << AreaSearchStatus_AreaSearchStatus_heatmap_width(root)
                << " x " << AreaSearchStatus_AreaSearchStatus_heatmap_height(root) << std::endl;

            flatbuffers_uint8_vec_t heatmap_data = AreaSearchStatus_AreaSearchStatus_heatmap_data(root);
            if (heatmap_data) {
                size_t data_len = flatbuffers_uint8_vec_len(heatmap_data);
                std::cout << "Data (" << data_len << " bytes): ";
                for (size_t i = 0; i < data_len; ++i) {
                    std::cout << (int)flatbuffers_uint8_vec_at(heatmap_data, i) << " ";
                }
                std::cout << std::endl;
            }
            else {
                std::cout << "No heatmap data" << std::endl;
            }

            // Geometry information
            std::cout << "\n--- Geometry Information ---" << std::endl;
            AreaSearchStatus_GeometryKind_Enum_enum_t geom_type = AreaSearchStatus_AreaSearchStatus_active_geometry_type(root);

            switch (geom_type) {
            case AreaSearchStatus_GeometryKind_Enum_CIRCLE: {
                std::cout << "Active Geometry: CIRCLE" << std::endl;
                auto circles_vec = AreaSearchStatus_AreaSearchStatus_circle(root);
                if (circles_vec && AreaSearchStatus_GeoCircle_vec_len(circles_vec) > 0) {
                    auto circle = AreaSearchStatus_GeoCircle_vec_at(circles_vec, 0);
                    std::cout << "Circle:" << std::endl;
                    std::cout << "  Center: " << AreaSearchStatus_GeoCircle_center(circle) << std::endl;
                    std::cout << "  Radius: " << AreaSearchStatus_GeoCircle_radius_m(circle) << "m" << std::endl;
                }
                else {
                    std::cout << "Circle data not found" << std::endl;
                }
                break;
            }
            case AreaSearchStatus_GeometryKind_Enum_POLYGON: {
                std::cout << "Active Geometry: POLYGON" << std::endl;
                auto polygons_vec = AreaSearchStatus_AreaSearchStatus_polygon(root);
                if (polygons_vec && AreaSearchStatus_GeoPolygon_vec_len(polygons_vec) > 0) {
                    auto polygon = AreaSearchStatus_GeoPolygon_vec_at(polygons_vec, 0);
                    std::cout << "Polygon:" << std::endl;
                    std::cout << "  Bounding Points: " << AreaSearchStatus_GeoPolygon_bounding_points(polygon) << std::endl;
                }
                else {
                    std::cout << "Polygon data not found" << std::endl;
                }
                break;
            }
            case AreaSearchStatus_GeometryKind_Enum_UNKNOWN:
                std::cout << "Active Geometry: UNKNOWN" << std::endl;
                break;
            default:
                std::cout << "Active Geometry: INVALID (" << (int)geom_type << ")" << std::endl;
                break;
            }

            // Clean up
            //flatcc_builder_aligned_free(converted_fb_buf);
        }
        else {
            std::cerr << "Failed to create FlatBuffer from Protocol Buffer" << std::endl;
        }

        flatcc_builder_clear(&builder2);

        //AreaSearchStatus_AreaSearchStatus_table_t root = AreaSearchStatus_AreaSearchStatus_as_root(converted_fb_buf);

       // auto status = AreaSearchStatus_AreaSearchStatus_heatmap_bounding_box(root);
        //auto next = AreaSearchStatus_GeoRectangle_bottom_right_point(status);
        //auto finall = AreaSearchStatus_GeoPoint_altitude_msl_m(next);
       // std::cout << "ahhhhhh " << finall << "\n";

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
