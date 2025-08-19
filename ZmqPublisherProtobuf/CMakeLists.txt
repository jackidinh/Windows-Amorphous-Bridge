cmake_minimum_required(VERSION 3.15)
project(ZMQPublisher)

set(CMAKE_C_STANDARD 99)

# Disable debug builds
set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
set(CMAKE_BUILD_TYPE Release)

# Define paths
set(VCPKG_PATH "C:/vcpkg/installed/x64-windows")

set(Protobuf_LIBRARIES "${VCPKG_PATH}/lib/libprotobuf.lib")
set(Protobuf_INCLUDE_DIRS "${VCPKG_PATH}/include")

set(ZeroMQ_LIBRARIES "${VCPKG_PATH}/lib/libzmq-mt-4_3_5.lib")
set(ZeroMQ_INCLUDE_DIRS "${VCPKG_PATH}/include")

# Only link Abseil libraries that actually exist in the lib directory
set(Abseil_LIBRARIES
    "${VCPKG_PATH}/lib/abseil_dll.lib"
    "${VCPKG_PATH}/lib/absl_flags_config.lib"
    "${VCPKG_PATH}/lib/absl_flags_parse.lib"
    "${VCPKG_PATH}/lib/absl_flags_usage.lib"
    "${VCPKG_PATH}/lib/absl_flags_program_name.lib"
    "${VCPKG_PATH}/lib/absl_log_flags.lib"
    "${VCPKG_PATH}/lib/absl_flags_internal.lib"
    "${VCPKG_PATH}/lib/absl_flags_marshalling.lib"
    "${VCPKG_PATH}/lib/absl_flags_reflection.lib"
)

set(Abseil_INCLUDE_DIRS "${VCPKG_PATH}/include")

add_executable(ZMQPublisher
    ZmqPublisher.cpp
    ../Generated/Impl/DM/Proto/ProtoGen/AreaSearchStatus.pb.cc
)

target_include_directories(ZMQPublisher PRIVATE
    ../Generated/Impl/DM/Proto/ProtoGen
    ${Protobuf_INCLUDE_DIRS}
    ${ZeroMQ_INCLUDE_DIRS}
    ${Abseil_INCLUDE_DIRS}
)

target_link_libraries(ZMQPublisher PRIVATE
    ${Protobuf_LIBRARIES}
    ${ZeroMQ_LIBRARIES}
    ${Abseil_LIBRARIES}
)

target_compile_definitions(ZMQPublisher PRIVATE ZMQ_STATIC)
