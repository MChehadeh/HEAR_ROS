#pragma once
#include <ros/ros.h>
#include "Interface_core/InterfaceController.hpp"
#include "Interface_ROS/ROSUnit_Client.hpp"
#include "Interface_ROS/ROSUnit_Server.hpp"
#include "Interface_ROS/ROSUnit_Subscriber.hpp"
#include "Interface_ROS/ROSUnit_Publisher.hpp"

#include "Interface_mavlink/MAVLink_Publisher.hpp"
#include "Interface_mavlink/MAVLink_Subscriber.hpp"

#include "Interface_system_connector/SysConnController.hpp"
#include "Interface_system_connector/SystemConnectorAsync.hpp"
#include "Interface_system_connector/SystemConnectorSync.hpp"

#include "Interface_motive_natnet/NatNetMotiveController.hpp"

#include "Interface_JSON_wrapper/JsonWrapperIOController.hpp"
#include "Interface_JSON_wrapper/JsonWrapperClient.hpp"
#include "Interface_JSON_wrapper/JsonWrapperPublisher.hpp"
#include "Interface_JSON_wrapper/JsonWrapperServer.hpp"
#include "Interface_JSON_wrapper/JsonWrapperSubscriber.hpp"


#include <string>

namespace HEAR{
//These are for InterfaceFactory type specialization:
class ROS{}; 
class ROS2{};
class SystemConnector{};
class JsonWrapper{};
class MAVLink{};

class InterfaceFactoryBase {
private:
InterfaceController* infc_ctrl;

public:
void setController(InterfaceController* _infc_ctrl){
    infc_ctrl=_infc_ctrl;
}
InterfaceController* getController(){
    return infc_ctrl;
}
};

template <typename T>
class InterfaceFactory : public InterfaceFactoryBase{
};
template <>
class InterfaceFactory<ROS> : public InterfaceFactoryBase{

public:
template <class U>
ROSUnit_Client<U>* createClient(std::string uri){
    return new ROSUnit_Client<U>(this->getController(),uri);
}
template <class U>
ROSUnit_Server<U>* createServer(std::string uri){
    return new ROSUnit_Server<U>(this->getController(),uri);
}
template <class U>
ROSUnit_Subscriber<U>* createSubscriber(std::string uri){
    return new ROSUnit_Subscriber<U>(this->getController(),uri);
}
template <class U>
ROSUnit_Publisher<U>* createPublisher(std::string uri){
    return new ROSUnit_Publisher<U>(this->getController(),uri);
}
};

template <>
class InterfaceFactory<SystemConnector> : public InterfaceFactoryBase{

public:
InterfaceFactory(){
    this->setController(new SysConnController());
}
template <class U>
SystemConnectorAsync<U>* createClient(std::string uri){
    return new SystemConnectorAsync<U>(uri);
}
template <class U>
SystemConnectorAsync<U>* createServer(std::string uri){
    return new SystemConnectorAsync<U>(uri);
}
template <class U>
SystemConnectorSync<U>* createSubscriber(std::string uri){
    return new SystemConnectorSync<U>(uri);
}
template <class U>
SystemConnectorSync<U>* createPublisher(std::string uri){
    return new SystemConnectorSync<U>(uri);
}
};


template <>
class InterfaceFactory<JsonWrapper> : public InterfaceFactoryBase{

public:
InterfaceFactory(){

}
template <class U>
JsonWrapperClient<U>* createClient(std::string uri){
    return new JsonWrapperClient<U>(uri,(JsonWrapperIOController*)this->getController());
}
template <class U>
JsonWrapperServer<U>* createServer(std::string uri){
    return new JsonWrapperServer<U>(uri,(JsonWrapperIOController*)this->getController());
}

template <class U>
JsonWrapperSubscriber<U>* createSubscriber(std::string uri){
    return new JsonWrapperSubscriber<U>(uri,(JsonWrapperIOController*)this->getController());
}
template <class U>
JsonWrapperPublisher<U>* createPublisher(std::string uri){
    return new JsonWrapperPublisher<U>(uri,(JsonWrapperIOController*)this->getController());
}

};

//Interface Factory for MAVLink
template <>
class InterfaceFactory<MAVLink> : public InterfaceFactoryBase{

public:
InterfaceFactory(){

}
template <class U>
MAVLink_Subscriber<U>* createSubscriber(uint8_t msg_id_para){
    return new MAVLink_Subscriber<U>((MAVLinkController*)this->getController(),msg_id_para);
}
template <class U>
MAVLink_Publisher<U>* createPublisher(std::string uri){
    return new MAVLink_Publisher<U>((MAVLinkController*)this->getController(),uri);
}

};



}