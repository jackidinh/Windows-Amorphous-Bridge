#### <u> Instructions for Bidirectional Middleware Bridge Apps</u>

Packages needed:

- ZeroMQ
  
  - Option 1: Installed using vcpkg
  
  - Option 2: Clone from https://github.com/zeromq/libzmq and build

- Nanomsg Next Gen
  
  - Option 1: Install using vcpkg
  
  - Option 2: Clone from [GitHub - nanomsg/nng at stable](https://github.com/nanomsg/nng/tree/stable) and build

- ProtoBuffers(protoc and protoc-c)
  
  - Option 1: Install both using vcpkg
  
  - Option 2: https://github.com/protocolbuffers/protobuf/releases Install .zip from release 29.5 for protoc, look here for protobuf-c https://github.com/protobuf-c/protobuf-c

- Fast DDS
  
  - Option 1: Install using vcpkg
  
  - Option 2: Install fastdds installer https://www.eprosima.com/product-download

Files needed:

- Custom ROS2 .msg

- Generated ROS2 .idl from .msg ( fastddsgen -typeros2 -no-typeobjectsupport example.idl)

- Generated fastddsgen code from ros2 .idl using -typeros2 and -no-typeobjectsupport flags

- Equivalent .proto file

- Auto generated .proto code

---

ZmqPublisher (proto system):

- Main Program:
  
  - Start ZMQ context
  
  - Open publisher socket
  
  - Serialize proto buffer 
  
  - Send serialized buffer through ZMQ to next app

- Thread:
  
  - Pass in main context (1 per program)
  
  - Open subscriber socket
  
  - Receive proto buffer through thread from previous app

- Run using sln

ZmqSubscriber NNG Send (ZMQ->NNG & NNG->ZMQ bridge):

- Main Program:
  
  - Start ZMQ context
  
  - Open subscriber socket
  
  - Open NNG publisher socket
  
  - Wait for ZMQ message
  
  - Use generated template code to convert protobuf to flatbuffer
  
  - send flat buffer through nng publisher

- Thread:
  
  - Pass ZMQ context
  
  - Open publisher socket
  
  - open NNG subscriber socket
  
  - Wait for NNG message
  
  - Use generated template code to convert flatbuffer to protobuf
  
  - Send message through ZMQ

- Run using sln

testwork (NNG->DDS & DDS->NNG bridge):

- Publish Program:
  
  - In order for ROS2 to see FastDDS topic and type, must use ROS2 compatible topic name and types ie. rt/person_topic and test_msgs_pkg::msg::dds_::Person_

- Subscribe Program:
  
  - Must use different topic name so that data doesnt clash if receiving and sending at the same time.

- Build using cmake .. and cmake --build .  in build folder, then open sln file to add additional includes and directories and run.

ros  (ROS2 system):

- Use topic echo for subscribing for now

- set up simple publisher in future for flow in opposite direction

---

Compiler Auto Gen Instructions (After Getting Schemas)

- Use equivalent .proto to run through Protoc-c

- Use equivalent .fbs to run through flatcc

- Use equivalent .idl from ROS2 and run through fastddsgen -typeros2 -no-typeobjectsupport

```flowchart
st=>operation: App 1: Proto System

app1=>operation: App 2: ZMQ to NNG Bridge
app2=>operation: App 3: NNG to FastDDS Bridge
app3=>operation: App 4: ROS2 System

st->app1
app1->app2
app2->app3





```



NNG to FastDDS vs project include directives(for sln file after building):

Some of these are automatically included from cmakelists file already, some need to be added since they were not put into the cmakelists file.


Include directories:

- C:\jackiWork\ZmqSubscriber NNG Send\ZmqPublisher\flatcc\flatcc\include

- C:\jackiWork\testwork\src

- C:\vcpkg\installed\x64-windows\include

- C:\nng\include

Linker General Libaries:

- C:\jackiWork\ZmqSubscriber NNG Send\ZmqPublisher\flatcc\flatcc\lib\Release

Linker input libraries:
C:\Program Files\eProsima\fastdds 3.2.2\lib\x64Win64VS2019\libfastcdrd-2.3.lib
C:\Program Files\eProsima\fastdds 3.2.2\lib\x64Win64VS2019\libfastddsd-3.2.lib
Debug\Person_lib.lib
C:\vcpkg\installed\x64-windows\lib\libprotobuf.lib
C:\nng\build\Release\nng.lib
C:\Program Files\eProsima\fastdds 3.2.2\lib\x64Win64VS2019\foonathan_memory-0.7.3-dbg.lib
C:\Program Files\OpenSSL-Win64\lib\VC\x64\MDd\libssl_static.lib
C:\Program Files\OpenSSL-Win64\lib\VC\x64\MDd\libcrypto_static.lib
ws2_32.lib
crypt32.lib
iphlpapi.lib
Shlwapi.lib
kernel32.lib
user32.lib
gdi32.lib
winspool.lib
shell32.lib
ole32.lib
oleaut32.lib
uuid.lib
comdlg32.lib
advapi32.lib
flatcc.lib
