 


#ifndef AreaSearchStatus_GENERATED_PBTOFB_H_
#define AreaSearchStatus_GENERATED_PBTOFB_H_

#include "AreaSearchStatus_reader.h"
#include "AreaSearchStatus_builder.h"
#include "AreaSearchStatus.pb.h"

namespace AreaSearchStatus {

    inline static void CreateGeoCircleFromPB(flatcc_builder_t* _fbb, const GeoCircle& _o)
    {
        AreaSearchStatus_GeoCircle_center_add(_fbb, _o.center());
        AreaSearchStatus_GeoCircle_radius_m_add(_fbb, _o.radius_m());
    }

    inline static void CreatePBFromGeoCircle(const AreaSearchStatus_GeoCircle_table_t root, GeoCircle& o_)
    {
        o_.set_center(AreaSearchStatus_GeoCircle_center(root));
        o_.set_radius_m(AreaSearchStatus_GeoCircle_radius_m(root));
    }

    inline static void CreateGeoPointFromPB(flatcc_builder_t* _fbb, const GeoPoint& _o)
    {
        AreaSearchStatus_GeoPoint_altitude_msl_m_add(_fbb, _o.altitude_msl_m());
        AreaSearchStatus_GeoPoint_latitude_deg_add(_fbb, _o.latitude_deg());
        AreaSearchStatus_GeoPoint_longitude_deg_add(_fbb, _o.longitude_deg());
    }

    inline static void CreatePBFromGeoPoint(const AreaSearchStatus_GeoPoint_table_t root, GeoPoint& o_)
    {
        o_.set_altitude_msl_m(AreaSearchStatus_GeoPoint_altitude_msl_m(root));
        o_.set_latitude_deg(AreaSearchStatus_GeoPoint_latitude_deg(root));
        o_.set_longitude_deg(AreaSearchStatus_GeoPoint_longitude_deg(root));
    }

    inline static AreaSearchStatus_GeoRectangle_ref_t CreateGeoRectangleFromPB(flatcc_builder_t* _fbb, const GeoRectangle& _o)
    {
        // Create bottom_right_point
        AreaSearchStatus_GeoPoint_ref_t bottom_right_ref = 0;
        if (_o.has_bottom_right_point()) {
            AreaSearchStatus_GeoPoint_start(_fbb);
            CreateGeoPointFromPB(_fbb, _o.bottom_right_point());
            bottom_right_ref = AreaSearchStatus_GeoPoint_end(_fbb);
        }

        // Create upper_left_point  
        AreaSearchStatus_GeoPoint_ref_t upper_left_ref = 0;
        if (_o.has_upper_left_point()) {
            AreaSearchStatus_GeoPoint_start(_fbb);
            CreateGeoPointFromPB(_fbb, _o.upper_left_point());
            upper_left_ref = AreaSearchStatus_GeoPoint_end(_fbb);
        }

        // Create GeoRectangle
        AreaSearchStatus_GeoRectangle_start(_fbb);
        if (bottom_right_ref) {
            AreaSearchStatus_GeoRectangle_bottom_right_point_add(_fbb, bottom_right_ref);
        }
        if (upper_left_ref) {
            AreaSearchStatus_GeoRectangle_upper_left_point_add(_fbb, upper_left_ref);
        }
        return AreaSearchStatus_GeoRectangle_end(_fbb);
    }

    inline static void CreatePBFromGeoRectangle(const AreaSearchStatus_GeoRectangle_table_t root, GeoRectangle& o_)
    {
        auto bottom_right = AreaSearchStatus_GeoRectangle_bottom_right_point(root);
        if (bottom_right) {
            CreatePBFromGeoPoint(bottom_right, *o_.mutable_bottom_right_point());
        }

        auto upper_left = AreaSearchStatus_GeoRectangle_upper_left_point(root);
        if (upper_left) {
            CreatePBFromGeoPoint(upper_left, *o_.mutable_upper_left_point());
        }
    }

    inline static void CreateGeoPolygonFromPB(flatcc_builder_t* _fbb, const GeoPolygon& _o)
    {
        AreaSearchStatus_GeoPolygon_bounding_points_add(_fbb, _o.bounding_points());
    }

    inline static void CreatePBFromGeoPolygon(const AreaSearchStatus_GeoPolygon_table_t root, GeoPolygon& o_)
    {
        o_.set_bounding_points(AreaSearchStatus_GeoPolygon_bounding_points(root));
    }

    inline static void CreateAreaSearchStatusFromPB(flatcc_builder_t* _fbb, const AreaSearchStatus& _o)
    {
        // Add basic fields
        AreaSearchStatus_AreaSearchStatus_vehicle_id_add(_fbb, _o.vehicle_id());
        AreaSearchStatus_AreaSearchStatus_timestamp_epoch_usec_add(_fbb, _o.timestamp_epoch_usec());
        AreaSearchStatus_AreaSearchStatus_estimated_completion_time_epoch_usec_add(_fbb, _o.estimated_completion_time_epoch_usec());
        AreaSearchStatus_AreaSearchStatus_estimated_percent_complete_add(_fbb, _o.estimated_percent_complete());

        // Handle heatmap bounding box
        if (_o.has_heatmap_bounding_box()) {
            auto rect_ref = CreateGeoRectangleFromPB(_fbb, _o.heatmap_bounding_box());
            AreaSearchStatus_AreaSearchStatus_heatmap_bounding_box_add(_fbb, rect_ref);
        }

        // Add heatmap dimensions
        AreaSearchStatus_AreaSearchStatus_heatmap_height_add(_fbb, _o.heatmap_height());
        AreaSearchStatus_AreaSearchStatus_heatmap_width_add(_fbb, _o.heatmap_width());

        // Handle heatmap data
        if (_o.heatmap_data_size() > 0) {
            std::vector<uint8_t> heatmap_data;
            heatmap_data.reserve(_o.heatmap_data_size());
            for (int i = 0; i < _o.heatmap_data_size(); ++i) {
                heatmap_data.push_back(_o.heatmap_data(i));
            }
            flatbuffers_uint8_vec_ref_t heatmap_data_vec = flatbuffers_uint8_vec_create(_fbb, heatmap_data.data(), heatmap_data.size());
            AreaSearchStatus_AreaSearchStatus_heatmap_data_add(_fbb, heatmap_data_vec);
        }

        // Handle oneof field: geo (PB to FB)
        switch (_o.geo_case()) {
        case AreaSearchStatus::AreaSearchStatus::kCircle: {
            // Set the discriminator enum
            AreaSearchStatus_AreaSearchStatus_active_geometry_type_add(_fbb, AreaSearchStatus_GeometryKind_Enum_CIRCLE);

            // Create circle
            AreaSearchStatus_GeoCircle_start(_fbb);
            CreateGeoCircleFromPB(_fbb, _o.circle());
            auto fb_circle = AreaSearchStatus_GeoCircle_end(_fbb);

            // Create vector with single circle
            AreaSearchStatus_GeoCircle_vec_ref_t circle_vec = AreaSearchStatus_GeoCircle_vec_create(_fbb, &fb_circle, 1);
            AreaSearchStatus_AreaSearchStatus_circle_add(_fbb, circle_vec);
            break;
        }

        case AreaSearchStatus::AreaSearchStatus::kPolygon: {
            // Set the discriminator enum
            AreaSearchStatus_AreaSearchStatus_active_geometry_type_add(_fbb, AreaSearchStatus_GeometryKind_Enum_POLYGON);

            // Create polygon
            AreaSearchStatus_GeoPolygon_start(_fbb);
            CreateGeoPolygonFromPB(_fbb, _o.polygon());
            auto fb_polygon = AreaSearchStatus_GeoPolygon_end(_fbb);

            // Create vector with single polygon
            AreaSearchStatus_GeoPolygon_vec_ref_t polygon_vec = AreaSearchStatus_GeoPolygon_vec_create(_fbb, &fb_polygon, 1);
            AreaSearchStatus_AreaSearchStatus_polygon_add(_fbb, polygon_vec);
            break;
        }

        case AreaSearchStatus::AreaSearchStatus::GEO_NOT_SET:
        default:
            // oneof not set - set discriminator to unknown or don't set anything
            AreaSearchStatus_AreaSearchStatus_active_geometry_type_add(_fbb, AreaSearchStatus_GeometryKind_Enum_UNKNOWN);
            break;
        }
    }

    inline static void CreatePBFromAreaSearchStatus(const AreaSearchStatus_AreaSearchStatus_table_t root, AreaSearchStatus& o_)
    {
        o_.set_vehicle_id(AreaSearchStatus_AreaSearchStatus_vehicle_id(root));
        o_.set_timestamp_epoch_usec(AreaSearchStatus_AreaSearchStatus_timestamp_epoch_usec(root));
        o_.set_estimated_completion_time_epoch_usec(AreaSearchStatus_AreaSearchStatus_estimated_completion_time_epoch_usec(root));
        o_.set_estimated_percent_complete(AreaSearchStatus_AreaSearchStatus_estimated_percent_complete(root));

        // Handle heatmap bounding box
        auto bbox = AreaSearchStatus_AreaSearchStatus_heatmap_bounding_box(root);
        if (bbox) {
            CreatePBFromGeoRectangle(bbox, *o_.mutable_heatmap_bounding_box());
        }

        o_.set_heatmap_height(AreaSearchStatus_AreaSearchStatus_heatmap_height(root));
        o_.set_heatmap_width(AreaSearchStatus_AreaSearchStatus_heatmap_width(root));

        // Handle heatmap data
        flatbuffers_uint8_vec_t heatmap_data = AreaSearchStatus_AreaSearchStatus_heatmap_data(root);
        if (heatmap_data) {
            o_.clear_heatmap_data();
            size_t len = flatbuffers_uint8_vec_len(heatmap_data);
            for (size_t i = 0; i < len; ++i) {
                o_.add_heatmap_data(flatbuffers_uint8_vec_at(heatmap_data, i));
            }
        }
        else {
            o_.clear_heatmap_data();
        }

        // Handle oneof field: geo (FB to PB)
        AreaSearchStatus_GeometryKind_Enum_enum_t oneofType = AreaSearchStatus_AreaSearchStatus_active_geometry_type(root);
        switch (oneofType) {
        case AreaSearchStatus_GeometryKind_Enum_CIRCLE: {
            auto fb_circle_vec = AreaSearchStatus_AreaSearchStatus_circle(root);
            if (fb_circle_vec && AreaSearchStatus_GeoCircle_vec_len(fb_circle_vec) > 0) {
                auto fb_circle = AreaSearchStatus_GeoCircle_vec_at(fb_circle_vec, 0);
                CreatePBFromGeoCircle(fb_circle, *o_.mutable_circle());
            }
            break;
        }

        case AreaSearchStatus_GeometryKind_Enum_POLYGON: {
            auto fb_polygon_vec = AreaSearchStatus_AreaSearchStatus_polygon(root);
            if (fb_polygon_vec && AreaSearchStatus_GeoPolygon_vec_len(fb_polygon_vec) > 0) {
                auto fb_polygon = AreaSearchStatus_GeoPolygon_vec_at(fb_polygon_vec, 0);
                CreatePBFromGeoPolygon(fb_polygon, *o_.mutable_polygon());
            }
            break;
        }

        case AreaSearchStatus_GeometryKind_Enum_UNKNOWN:
        default:
            // oneof not set or unknown type - no action needed
            break;
        }
    }

} // namespace AreaSearchStatus

#endif  //AreaSearchStatus_GENERATED_PBTOFB_H_