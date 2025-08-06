#### <u> Instructions for Bidirectional Middleware Bridge Apps</u>

Packages needed:

- ZeroMQ

- Nanomsg Next Gen

- ProtoBuffers

- Fast DDS

Files needed:

- Custom ROS2 .msg

- Generated ROS2 .idl from .msg

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

ZmqSubscriber NNG Send (ZMQ->NNG & NNG->ZMQ bridge):

- Main Program:
  
  - Start ZMQ context
  
  - Open subscriber socket
  
  - Open NNG publisher socket
  
  - Wait for ZMQ message
  
  - Send through NNG

- Thread:
  
  - Pass ZMQ context
  
  - Open publisher socket
  
  - open NNG subscriber socket
  
  - Wait for NNG message
  
  - Send message through ZMQ

ZmqSubscriber NNG Send (ZMQ->NNG & NNG->ZMQ bridge):

- Main Program:
  
  - Start ZMQ context
  
  - Open subscriber socket
  
  - Open NNG publisher socket
  
  - Wait for ZMQ message
  
  - Send through NNG

- Thread:
  
  - Pass ZMQ context
  
  - Open publisher socket
  
  - open NNG subscriber socket
  
  - Wait for NNG message
  
  - Send message through ZMQ

testwork (NNG->DDS & DDS->NNG bridge):

- Publish Program:
  
  - In order for ROS2 to see FastDDS topic and type, must use ROS2 compatible topic name and types ie. rt/person_topic and test_msgs_pkg::msg::dds_::Person_

- Subscribe Program:
  
  - Must use different topic name so that data doesnt clash if receiving and sending at the same time.
  
  - can use threads in main ( havent implemented)

ros  (ROS2 system):

- Use topic echo for subscribing for now

- set up simple publisher in future for flow in opposite direction

---
