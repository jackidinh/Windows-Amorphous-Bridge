
cmake_minimum_required(VERSION 3.20)

project(generated_code)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GENERATED_DIR "C:/jackiWork/Generated/Impl/DM/msg/FastDDSGen")

# Find requirements
find_package(fastcdr REQUIRED)
find_package(fastdds 3 REQUIRED)


message(STATUS "Configuring GeoPoint...")
add_library(GeoPoint_lib ${GENERATED_DIR}/GeoPointPubSubTypes.cxx)
target_link_libraries(GeoPoint_lib fastcdr fastdds)

add_executable(GeoPoint 
	${GENERATED_DIR}/GeoPointApplication.cxx 
	${GENERATED_DIR}/GeoPointPublisherApp.cxx 
	${GENERATED_DIR}/GeoPointSubscriberApp.cxx 
	${GENERATED_DIR}/GeoPointmain.cxx
)
target_link_libraries(GeoPoint fastcdr fastdds
        GeoPoint_lib 
        )



message(STATUS "Configuring GeoPolygon...")
add_library(GeoPolygon_lib ${GENERATED_DIR}/GeoPolygonPubSubTypes.cxx)
target_link_libraries(GeoPolygon_lib fastcdr fastdds)

add_executable(GeoPolygon 
	${GENERATED_DIR}/GeoPolygonApplication.cxx 
	${GENERATED_DIR}/GeoPolygonPublisherApp.cxx 
	${GENERATED_DIR}/GeoPolygonSubscriberApp.cxx 
	${GENERATED_DIR}/GeoPolygonmain.cxx
)
target_link_libraries(GeoPolygon fastcdr fastdds
        GeoPolygon_lib 
        )



message(STATUS "Configuring GeoCircle...")
add_library(GeoCircle_lib ${GENERATED_DIR}/GeoCirclePubSubTypes.cxx)
target_link_libraries(GeoCircle_lib fastcdr fastdds)

add_executable(GeoCircle 
	${GENERATED_DIR}/GeoCircleApplication.cxx 
	${GENERATED_DIR}/GeoCirclePublisherApp.cxx 
	${GENERATED_DIR}/GeoCircleSubscriberApp.cxx 
	${GENERATED_DIR}/GeoCirclemain.cxx)
target_link_libraries(GeoCircle fastcdr fastdds
        GeoCircle_lib 
        )



message(STATUS "Configuring GeoRectangle...")
add_library(GeoRectangle_lib ${GENERATED_DIR}/GeoRectanglePubSubTypes.cxx)
target_link_libraries(GeoRectangle_lib fastcdr fastdds)

add_executable(GeoRectangle 
	${GENERATED_DIR}/GeoRectangleApplication.cxx 
	${GENERATED_DIR}/GeoRectanglePublisherApp.cxx 
	${GENERATED_DIR}/GeoRectangleSubscriberApp.cxx 
	${GENERATED_DIR}/GeoRectanglemain.cxx)
target_link_libraries(GeoRectangle fastcdr fastdds
        GeoRectangle_lib GeoPoint_lib
        )



message(STATUS "Configuring AreaSearchStatus...")
add_library(AreaSearchStatus_lib ${GENERATED_DIR}/AreaSearchStatusPubSubTypes.cxx)
target_link_libraries(AreaSearchStatus_lib fastcdr fastdds)

add_executable(AreaSearchStatus 
	${GENERATED_DIR}/AreaSearchStatusApplication.cxx 
	AreaSearchStatusPublisherApp.cxx 
	AreaSearchStatusSubscriberApp.cxx 
	AreaSearchStatusmain.cxx)
target_include_directories(AreaSearchStatus PRIVATE
C:/jackiWork/Generated/Impl/DM
C:/jackiWork/Generated/Impl/DM/msg/FastDDSGen
)
target_link_libraries(AreaSearchStatus fastcdr fastdds
        AreaSearchStatus_lib GeoRectangle_lib GeoPoint_lib GeoPolygon_lib GeoCircle_lib
        )



