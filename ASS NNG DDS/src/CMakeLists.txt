
cmake_minimum_required(VERSION 3.20)

project("generated_code")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find requirements
find_package(fastcdr REQUIRED)
find_package(fastdds 3 REQUIRED)


message(STATUS "Configuring GeoPoint...")
add_library(GeoPoint_lib GeoPointPubSubTypes.cxx)
target_link_libraries(GeoPoint_lib fastcdr fastdds)

add_executable(GeoPoint GeoPointApplication.cxx GeoPointPublisherApp.cxx GeoPointSubscriberApp.cxx GeoPointmain.cxx)
target_link_libraries(GeoPoint fastcdr fastdds
        GeoPoint_lib 
        )



message(STATUS "Configuring GeoPolygon...")
add_library(GeoPolygon_lib GeoPolygonPubSubTypes.cxx)
target_link_libraries(GeoPolygon_lib fastcdr fastdds)

add_executable(GeoPolygon GeoPolygonApplication.cxx GeoPolygonPublisherApp.cxx GeoPolygonSubscriberApp.cxx GeoPolygonmain.cxx)
target_link_libraries(GeoPolygon fastcdr fastdds
        GeoPolygon_lib 
        )



message(STATUS "Configuring GeoCircle...")
add_library(GeoCircle_lib GeoCirclePubSubTypes.cxx)
target_link_libraries(GeoCircle_lib fastcdr fastdds)

add_executable(GeoCircle GeoCircleApplication.cxx GeoCirclePublisherApp.cxx GeoCircleSubscriberApp.cxx GeoCirclemain.cxx)
target_link_libraries(GeoCircle fastcdr fastdds
        GeoCircle_lib 
        )



message(STATUS "Configuring GeoRectangle...")
add_library(GeoRectangle_lib GeoRectanglePubSubTypes.cxx)
target_link_libraries(GeoRectangle_lib fastcdr fastdds)

add_executable(GeoRectangle GeoRectangleApplication.cxx GeoRectanglePublisherApp.cxx GeoRectangleSubscriberApp.cxx GeoRectanglemain.cxx)
target_link_libraries(GeoRectangle fastcdr fastdds
        GeoRectangle_lib GeoPoint_lib
        )



message(STATUS "Configuring AreaSearchStatus...")
add_library(AreaSearchStatus_lib AreaSearchStatusPubSubTypes.cxx)
target_link_libraries(AreaSearchStatus_lib fastcdr fastdds)

add_executable(AreaSearchStatus AreaSearchStatusApplication.cxx AreaSearchStatusPublisherApp.cxx AreaSearchStatusSubscriberApp.cxx AreaSearchStatusmain.cxx)
target_link_libraries(AreaSearchStatus fastcdr fastdds
        AreaSearchStatus_lib GeoRectangle_lib GeoPoint_lib GeoPolygon_lib GeoCircle_lib
        )



