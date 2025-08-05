cmake_minimum_required(VERSION 3.20)

project("generated_code")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set protobuf paths (adjust if your vcpkg is installed elsewhere)
set(Protobuf_ROOT "C:/vcpkg/installed/x64-windows")
set(Protobuf_INCLUDE_DIR "C:/vcpkg/installed/x64-windows/include")
set(Protobuf_LIBRARIES "C:/vcpkg/installed/x64-windows/lib/libprotobuf.lib")

# Set NNG paths
set(NNG_INCLUDE_DIR "C:/nng/include")
set(NNG_LIB_DIR "C:/nng/build/Release")
set(NNG_LIB "${NNG_LIB_DIR}/nng.lib")
set(NNG_DLL "${NNG_LIB_DIR}/nng.dll")

# Find requirements
find_package(fastcdr REQUIRED)
find_package(fastdds 3 REQUIRED)
find_package(Protobuf REQUIRED)

set(PROTO_SRCS person.pb.cc)
set(PROTO_HDRS person.pb.h)

message(STATUS "Configuring Person...")

add_library(Person_lib 
    PersonPubSubTypes.cxx
    ${PROTO_SRCS}
)

target_include_directories(Person_lib PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Protobuf_INCLUDE_DIR}
    ${NNG_INCLUDE_DIR}
)

target_link_libraries(Person_lib fastcdr fastdds ${Protobuf_LIBRARIES} ${NNG_LIB})

add_executable(Person PersonApplication.cxx PersonPublisherApp.cxx PersonSubscriberApp.cxx Personmain.cxx)

target_include_directories(Person PRIVATE 
    ${Protobuf_INCLUDE_DIR}
    ${NNG_INCLUDE_DIR}
)

target_link_libraries(Person 
    fastcdr 
    fastdds 
    Person_lib 
    ${Protobuf_LIBRARIES}
    ${NNG_LIB}
)

# Copy nng.dll to executable folder after build
