
#ifndef AreaSearchStatus_GENERATED_FastDDSTOFB_H_
#define AreaSearchStatus_GENERATED_FastDDSTOFB_H_

#include "AreaSearchStatus_reader.h"
#include "AreaSearchStatus_builder.h"
#include "C:\jackiWork\ASS NNG DDS\src\AreaSearchStatus.hpp"

#ifndef AreaSearchStatus_FastDDS_TYPES_DEFINED
//Leaving out for now
//#include "AreaSearchStatusTypeSupport.hh"
#endif
//Leaving out for now
//#include "FACEBridgeClasses.h"


  
namespace test_msgs_pkg {
namespace msg {
 


inline static void CreateGeoCircleFromFastDDS(flatcc_builder_t* _fbb, GeoCircle _o)
{
	AreaSearchStatus_GeoCircle_center_add(_fbb, _o.center());
	AreaSearchStatus_GeoCircle_radius_m_add(_fbb, _o.radius_m());

} 

inline static void CreateFastDDSFromGeoCircle(const AreaSearchStatus_GeoCircle_table_t root, GeoCircle& o_)
{
    size_t len = 0;
	size_t slen = len;
	len = slen;

    //o_.clear();

	o_.center(AreaSearchStatus_GeoCircle_center(root));
	o_.radius_m(AreaSearchStatus_GeoCircle_radius_m(root));
}

} // msg
}//test_msgs_pkg
namespace test_msgs_pkg {
namespace msg {
 


inline static void CreateGeoPointFromFastDDS(flatcc_builder_t* _fbb, GeoPoint _o)
{
	AreaSearchStatus_GeoPoint_altitude_msl_m_add(_fbb, _o.altitude_msl_m());
	AreaSearchStatus_GeoPoint_latitude_deg_add(_fbb, _o.latitude_deg());
	AreaSearchStatus_GeoPoint_longitude_deg_add(_fbb, _o.longitude_deg());

} 

inline static void CreateFastDDSFromGeoPoint(const AreaSearchStatus_GeoPoint_table_t root, GeoPoint& o_)
{
    size_t len = 0;
	size_t slen = len;
	len = slen;

    //o_.clear();

	o_.altitude_msl_m(AreaSearchStatus_GeoPoint_altitude_msl_m(root));
	o_.latitude_deg(AreaSearchStatus_GeoPoint_latitude_deg(root));
	o_.longitude_deg(AreaSearchStatus_GeoPoint_longitude_deg(root));
}

} // msg
}//test_msgs_pkg
namespace test_msgs_pkg {
namespace msg {
 


inline static void CreateGeoRectangleFromFastDDS(flatcc_builder_t* _fbb, GeoRectangle _o)
{
	AreaSearchStatus_GeoRectangle_bottom_right_point_start(_fbb);
	test_msgs_pkg::msg::CreateGeoPointFromFastDDS(_fbb, _o.bottom_right_point());
	AreaSearchStatus_GeoRectangle_bottom_right_point_end(_fbb);
	AreaSearchStatus_GeoRectangle_upper_left_point_start(_fbb);
	test_msgs_pkg::msg::CreateGeoPointFromFastDDS(_fbb, _o.upper_left_point());
	AreaSearchStatus_GeoRectangle_upper_left_point_end(_fbb);

} 

inline static void CreateFastDDSFromGeoRectangle(const AreaSearchStatus_GeoRectangle_table_t root, GeoRectangle& o_)
{
    size_t len = 0;
	size_t slen = len;
	len = slen;

    //o_.clear();

    test_msgs_pkg::msg::CreateFastDDSFromGeoPoint(AreaSearchStatus_GeoRectangle_bottom_right_point(root), o_.bottom_right_point());
    test_msgs_pkg::msg::CreateFastDDSFromGeoPoint(AreaSearchStatus_GeoRectangle_upper_left_point(root), o_.upper_left_point());
}

} // msg
}//test_msgs_pkg
namespace test_msgs_pkg {
namespace msg {
 


inline static void CreateGeoPolygonFromFastDDS(flatcc_builder_t* _fbb, GeoPolygon _o)
{
	AreaSearchStatus_GeoPolygon_bounding_points_add(_fbb, _o.bounding_points());

} 

inline static void CreateFastDDSFromGeoPolygon(const AreaSearchStatus_GeoPolygon_table_t root, GeoPolygon& o_)
{
    size_t len = 0;
	size_t slen = len;
	len = slen;

    //o_.clear();

	o_.bounding_points(AreaSearchStatus_GeoPolygon_bounding_points(root));
}

} // msg
}//test_msgs_pkg
namespace test_msgs_pkg {
namespace msg {
 


inline static void CreateAreaSearchStatusFromFastDDS(flatcc_builder_t* _fbb, AreaSearchStatus _o)
{
	AreaSearchStatus_AreaSearchStatus_active_geometry_type_add(_fbb, (AreaSearchStatus_GeometryKind_Enum_enum_t)_o.active_geometry_type()); // Enum 
	if (!_o.circle().empty())
	{
		AreaSearchStatus_AreaSearchStatus_circle_start(_fbb);

		for (unsigned int _i = 0; _i < _o.circle().size(); _i++)
		{
			AreaSearchStatus_AreaSearchStatus_circle_push_start(_fbb);
			test_msgs_pkg::msg::CreateGeoCircleFromFastDDS(_fbb, _o.circle()[_i]);
			AreaSearchStatus_AreaSearchStatus_circle_push_end(_fbb);
		}
		AreaSearchStatus_AreaSearchStatus_circle_end(_fbb);
	}
	AreaSearchStatus_AreaSearchStatus_estimated_completion_time_epoch_usec_add(_fbb, _o.estimated_completion_time_epoch_usec());
	AreaSearchStatus_AreaSearchStatus_estimated_percent_complete_add(_fbb, _o.estimated_percent_complete());
	AreaSearchStatus_AreaSearchStatus_heatmap_bounding_box_start(_fbb);
	test_msgs_pkg::msg::CreateGeoRectangleFromFastDDS(_fbb, _o.heatmap_bounding_box());
	AreaSearchStatus_AreaSearchStatus_heatmap_bounding_box_end(_fbb);
	if (!_o.heatmap_data().empty())
	{
		AreaSearchStatus_AreaSearchStatus_heatmap_data_start(_fbb);

		for (unsigned int _i = 0; _i < _o.heatmap_data().size(); _i++)
		{
			AreaSearchStatus_AreaSearchStatus_heatmap_data_push_create(_fbb, _o.heatmap_data()[_i]);
		}
		AreaSearchStatus_AreaSearchStatus_heatmap_data_end(_fbb);
	}
	AreaSearchStatus_AreaSearchStatus_heatmap_height_add(_fbb, _o.heatmap_height());
	AreaSearchStatus_AreaSearchStatus_heatmap_width_add(_fbb, _o.heatmap_width());
	if (!_o.polygon().empty())
	{
		AreaSearchStatus_AreaSearchStatus_polygon_start(_fbb);

		for (unsigned int _i = 0; _i < _o.polygon().size(); _i++)
		{
			AreaSearchStatus_AreaSearchStatus_polygon_push_start(_fbb);
			test_msgs_pkg::msg::CreateGeoPolygonFromFastDDS(_fbb, _o.polygon()[_i]);
			AreaSearchStatus_AreaSearchStatus_polygon_push_end(_fbb);
		}
		AreaSearchStatus_AreaSearchStatus_polygon_end(_fbb);
	}
	AreaSearchStatus_AreaSearchStatus_timestamp_epoch_usec_add(_fbb, _o.timestamp_epoch_usec());
	AreaSearchStatus_AreaSearchStatus_vehicle_id_add(_fbb, _o.vehicle_id());

} 

inline static void CreateFastDDSFromAreaSearchStatus(const AreaSearchStatus_AreaSearchStatus_table_t root, AreaSearchStatus& o_)
{
    size_t len = 0;
	size_t slen = len;
	len = slen;

    //o_.clear();

	o_.active_geometry_type(AreaSearchStatus_AreaSearchStatus_active_geometry_type(root)); //don't cast ??
	if (AreaSearchStatus_AreaSearchStatus_circle_is_present(root))
	{

	    AreaSearchStatus_GeoCircle_vec_t _circle = AreaSearchStatus_AreaSearchStatus_circle_get(root);
		len = (unsigned int)AreaSearchStatus_GeoCircle_vec_len(_circle);
		o_.circle().resize((uint32_t)len);
		for (unsigned int _i = 0; _i < len; _i++)
		{
			CreateFastDDSFromGeoCircle(AreaSearchStatus_GeoCircle_vec_at(_circle, _i), o_.circle()[_i]);
		}
	}
	o_.estimated_completion_time_epoch_usec(AreaSearchStatus_AreaSearchStatus_estimated_completion_time_epoch_usec(root));
	o_.estimated_percent_complete(AreaSearchStatus_AreaSearchStatus_estimated_percent_complete(root));
    test_msgs_pkg::msg::CreateFastDDSFromGeoRectangle(AreaSearchStatus_AreaSearchStatus_heatmap_bounding_box(root), o_.heatmap_bounding_box());
	if (AreaSearchStatus_AreaSearchStatus_heatmap_data_is_present(root))
	{

	    flatbuffers_uint8_vec_t _heatmap_data = AreaSearchStatus_AreaSearchStatus_heatmap_data_get(root);
		len = (unsigned int)flatbuffers_uint8_vec_len(_heatmap_data);
		o_.heatmap_data().resize((uint32_t)len);
		for (unsigned int _i = 0; _i < len; _i++)
		{
				o_.heatmap_data()[_i] = flatbuffers_uint8_vec_at(_heatmap_data, _i);
		}
	}
	o_.heatmap_height(AreaSearchStatus_AreaSearchStatus_heatmap_height(root));
	o_.heatmap_width(AreaSearchStatus_AreaSearchStatus_heatmap_width(root));
	if (AreaSearchStatus_AreaSearchStatus_polygon_is_present(root))
	{

	    AreaSearchStatus_GeoPolygon_vec_t _polygon = AreaSearchStatus_AreaSearchStatus_polygon_get(root);
		len = (unsigned int)AreaSearchStatus_GeoPolygon_vec_len(_polygon);
		o_.polygon().resize((uint32_t)len);
		for (unsigned int _i = 0; _i < len; _i++)
		{
			CreateFastDDSFromGeoPolygon(AreaSearchStatus_GeoPolygon_vec_at(_polygon, _i), o_.polygon()[_i]);
		}
	}
	o_.timestamp_epoch_usec(AreaSearchStatus_AreaSearchStatus_timestamp_epoch_usec(root));
	o_.vehicle_id(AreaSearchStatus_AreaSearchStatus_vehicle_id(root));
}

} // msg
}//test_msgs_pkg


#endif  //FLATBUFFERS_GENERATED_AreaSearchStatus_FastDDSTOFB_H_