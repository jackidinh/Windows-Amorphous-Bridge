cmake_minimum_required(VERSION 3.20)
project("AreaSearchStatusClient" CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

# ========== Protobuf ================
set(Protobuf_ROOT "C:/vcpkg/installed/x64-windows")
set(Protobuf_INCLUDE_DIR "C:/vcpkg/installed/x64-windows/include")
set(Protobuf_LIBRARIES "C:/vcpkg/installed/x64-windows/lib/libprotobuf.lib")

# ========== NNG ================
set(NNG_INCLUDE_DIR "C:/nng/include")
set(NNG_LIB_DIR "C:/nng/build/Release")
set(NNG_LIB "${NNG_LIB_DIR}/nng.lib")
set(NNG_DLL "${NNG_LIB_DIR}/nng.dll")

# ========== FastDDS & FastCDR ===========
find_package(fastcdr REQUIRED)
find_package(fastdds 3 REQUIRED)
find_package(Protobuf REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Protobuf_INCLUDE_DIR}
    ${NNG_INCLUDE_DIR}
)

# ======= GeoPoint =========
add_library(GeoPoint_lib STATIC
    GeoPointPubSubTypes.cxx
)
target_link_libraries(GeoPoint_lib fastcdr fastdds)

# ======= GeoPolygon =========
add_library(GeoPolygon_lib STATIC
    GeoPolygonPubSubTypes.cxx
)
target_link_libraries(GeoPolygon_lib fastcdr fastdds)

# ======= GeoCircle =========
add_library(GeoCircle_lib STATIC
    GeoCirclePubSubTypes.cxx
)
target_link_libraries(GeoCircle_lib fastcdr fastdds)

# ======= GeoRectangle =========
add_library(GeoRectangle_lib STATIC
    GeoRectanglePubSubTypes.cxx
)
target_link_libraries(GeoRectangle_lib GeoPoint_lib fastcdr fastdds)

# ======= AreaSearchStatus =========
add_library(AreaSearchStatus_lib STATIC
    AreaSearchStatusPubSubTypes.cxx
)
target_link_libraries(AreaSearchStatus_lib
    GeoRectangle_lib
    GeoCircle_lib
    GeoPolygon_lib
    GeoPoint_lib
    fastcdr
    fastdds
)

# ======= Executable =========
add_executable(Person
    PersonApplication.cxx
    PersonPublisherApp.cxx
    PersonSubscriberApp.cxx
    Personmain.cxx
)

target_link_libraries(Person
    AreaSearchStatus_lib
    GeoRectangle_lib
    GeoCircle_lib
    GeoPolygon_lib
    GeoPoint_lib
    fastcdr
    fastdds
    ${Protobuf_LIBRARIES}
    ${NNG_LIB}
)

# ======= Copy NNG DLL =========
add_custom_command(TARGET Person POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${NNG_DLL} $<TARGET_FILE_DIR:Person>
)

# ======= Output Directories =========
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
