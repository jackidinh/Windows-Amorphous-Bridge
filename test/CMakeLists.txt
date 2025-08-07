
cmake_minimum_required(VERSION 3.20)

project("generated_code")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find requirements
find_package(fastcdr REQUIRED)
find_package(fastdds 3 REQUIRED)


message(STATUS "Configuring Person...")
add_library(Person_lib PersonPubSubTypes.cxx)
target_link_libraries(Person_lib fastcdr fastdds)

add_executable(Person PersonApplication.cxx PersonPublisherApp.cxx PersonSubscriberApp.cxx Personmain.cxx)
target_link_libraries(Person fastcdr fastdds
        Person_lib 
        )



