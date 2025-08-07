#### <u> Instructions for Bidirectional Middleware Bridge Apps</u>

Packages needed:

- ZeroMQ

- Nanomsg Next Gen

- ProtoBuffers

- Fast DDS

Files needed:

- Custom ROS2 .msg

- Generated ROS2 .idl from .msg ( fastddsgen -typeros2 -no-typeobjectsupport example.idl)

- Generated fastddsgen code from ros2 .idl using -typeros2 and -no-typeobjectsupport flags

- Equivalent .proto file

- Auto generated .proto code

TODO:

- Integrate populated buffer converters

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
  
  - TODO: implement proto to flatbuffer converter
  
  - send flat buffer

- Thread:
  
  - Pass ZMQ context
  
  - Open publisher socket
  
  - open NNG subscriber socket
  
  - Wait for NNG message
  
  - TODO: implement flatbuffer to proto converter
  
  - Send message through ZMQ

- Run using sln

testwork (NNG->DDS & DDS->NNG bridge):

- Publish Program:
  
  - In order for ROS2 to see FastDDS topic and type, must use ROS2 compatible topic name and types ie. rt/person_topic and test_msgs_pkg::msg::dds_::Person_
  - TODO: implement flat buffer to dds converter

- Subscribe Program:
  
  - Must use different topic name so that data doesnt clash if receiving and sending at the same time.
  
  - TODO: implement dds to flatbuffer converter
  
  - 

- Build using cmake .. and cmake --build .  in build folder, then run executable Person.exe in Debug directory

ros  (ROS2 system):

- Use topic echo for subscribing for now

- set up simple publisher in future for flow in opposite direction

---
