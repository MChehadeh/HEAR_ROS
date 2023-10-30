#pragma once

#include <ros/ros.h>
#include "HEAR_core/DataTypes.hpp"
#include "HEAR_core/Port.hpp"
#include "Interface_ROS/castMsgROSG.hpp"
#include "Interface_ROS/ROSController.hpp"

namespace HEAR{

// template <typename T, typename U>
// class ROSUnit_Subscriber : public Block {
// protected:
//     int id_; 
//     ros::Subscriber sub_;
//     OutputPort<T>* _output_port;
// public:
//     enum OP {OUTPUT};

//     // OutputPort<T>* getOutputPort() { return (OutputPort<T>*)_output_port;}


//     ROSUnit_Subscriber(ros::NodeHandle& nh, const std::string& topic, int idx){
//     sub_ = nh.subscribe<U>(topic, 10, &ROSUnit_Subscriber::callback, this);
//     _output_port=this->createOutputPort<T>(OP::OUTPUT,"OUTPUT");
//     id_ = idx;
//     }

//     typedef typename U::ConstPtr Sub_para;
//     void callback(const Sub_para& msg){
//         T data;
//         Sub_para msg_c=msg; //Non-constant type to be passed to castMsgROS
//         // castMsgROS<Sub_para,T>(msg_c,data);
//         _output_port->write(data);
//     }

//     void process() override{}

//     void processAsync() override{}

//     void reset() override{}


// };

template <typename T>
class ROSUnit_Subscriber : public Block {
protected:
    ros::Subscriber sub_;
    OutputPort<T>* _output_port;
public:
    enum OP {OUTPUT};

    ROSUnit_Subscriber(ROSController* ros_ctrl, const std::string& topic){
        this->updateInstanceDescription(topic);
        using ROS_type=typename ROSTopicTypeTranslator<T>::ROSType;
        sub_ = ros_ctrl->nh.subscribe<ROS_type>(topic, 10, &ROSUnit_Subscriber::callback, this);
        _output_port=this->createOutputPort<T>(OP::OUTPUT,"OUTPUT");
        this->block_att->block_func=BlockNodeAttributes::Source;
    }

    void callback(const typename ROSTopicTypeTranslator<T>::ROSType::ConstPtr& msg){
        T data;
        using ROS_type=typename ROSTopicTypeTranslator<T>::ROSType::ConstPtr;
        ROS_type msg_c=msg; //Non-constant type to be passed to castMsgROS
        castMsgFromROS<ROS_type,T>(msg_c,data);
        _output_port->write(data);
    }

    void process() override{}

    void processAsync() override{}

    void reset() override{}

    std::string getTypeDescription(){
        return "ROSUnit_Subscriber";
    }

};

}

