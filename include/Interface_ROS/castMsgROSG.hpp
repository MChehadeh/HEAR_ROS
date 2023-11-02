#pragma once

#include "HEAR_core/DataTypes.hpp"
#include "HEAR_core/Vector3D.hpp"
#include <ros/ros.h>
#include <std_srvs/Empty.h>
#include <std_srvs/SetBool.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <geometry_msgs/QuaternionStamped.h>
#include <hear_msgs/set_bool.h>
#include <hear_msgs/set_int.h>
#include <hear_msgs/set_float.h>
#include <hear_msgs/set_point.h>
#include <hear_msgs/Update_Controller_Bounding.h>
#include <hear_msgs/Update_Controller_MRFT.h>
#include <hear_msgs/PID_param.h>
#include <hear_msgs/Update_Controller_PID.h>
#include <hear_msgs/Update_Trajectory.h>


namespace HEAR {

template <typename T,typename U> void castMsgToROS(T& data_from,U& data_to) 
{ 
    throw std::runtime_error("Invalid castMsgToROS function signature in ROSUnit_Client");
}

template <> void castMsgToROS<int,std_srvs::Empty>(int& data_from,std_srvs::Empty& data_to);

template <> void castMsgToROS<bool,hear_msgs::set_bool>(bool& data_from,hear_msgs::set_bool& data_to);

template <> void castMsgToROS<int,hear_msgs::set_int>(int& data_from,hear_msgs::set_int& data_to);

template <> void castMsgToROS<float,hear_msgs::set_float>(float& data_from,hear_msgs::set_float& data_to);

template <> void castMsgToROS<float,std_msgs::Float32>(float& data_from,std_msgs::Float32& data_to);

//TODO AA check this
template <> void castMsgToROS<Vector3D<float>,hear_msgs::set_point>(Vector3D<float>& data_from,hear_msgs::set_point& data_to);

template <> void castMsgToROS<Vector3D<float>,geometry_msgs::Point>(Vector3D<float>& data_from,geometry_msgs::Point& data_to);

template <> void castMsgToROS<std::vector<float>,std_msgs::Float32MultiArray>(std::vector<float>& data_from,std_msgs::Float32MultiArray& data_to);

template <> void castMsgToROS<BoundingCtrl_parameters,hear_msgs::Update_Controller_Bounding>(BoundingCtrl_parameters& data_from,hear_msgs::Update_Controller_Bounding& data_to);

template <> void castMsgToROS<MRFT_parameters,hear_msgs::Update_Controller_MRFT>(MRFT_parameters& data_from,hear_msgs::Update_Controller_MRFT& data_to);

template <> void castMsgToROS<PID_parameters,hear_msgs::Update_Controller_PID>(PID_parameters& data_from,hear_msgs::Update_Controller_PID& data_to) ;

template <typename T,typename U> void castMsgFromROS(T& data_from,U& data_to) 
{ 
    throw std::runtime_error("Invalid castMsgFromROS function signature in ROSUnit_Client");
}


template <> void castMsgFromROS<std_srvs::Empty::Request,int>(std_srvs::Empty::Request& data_from,int& data_to);


template <> void castMsgFromROS<hear_msgs::set_bool::Request,bool>(hear_msgs::set_bool::Request& data_from, bool& data_to);

template <> void castMsgFromROS<hear_msgs::set_int::Request,int>(hear_msgs::set_int::Request& data_from,int& data_to);

template <> void castMsgFromROS<hear_msgs::set_float::Request,float>(hear_msgs::set_float::Request& data_from,float& data_to);

template <> void castMsgFromROS<std_msgs::Float32::ConstPtr,float>(std_msgs::Float32::ConstPtr& data_from,float& data_to);

//TODO AA: revert this
template <> void castMsgFromROS<hear_msgs::set_point::Request,Vector3D<float>>(hear_msgs::set_point::Request& data_from,Vector3D<float>& data_to);

template <> void castMsgFromROS<geometry_msgs::Point::ConstPtr, Vector3D<float>>(geometry_msgs::Point::ConstPtr& data_from,Vector3D<float>& data_to);

template <> void castMsgFromROS<std_msgs::Float32MultiArray::ConstPtr,std::vector<float>>(std_msgs::Float32MultiArray::ConstPtr& data_from,std::vector<float>& data_to);

template <> void castMsgFromROS<hear_msgs::Update_Controller_Bounding::Request,BoundingCtrl_parameters>(hear_msgs::Update_Controller_Bounding::Request& data_from,BoundingCtrl_parameters& data_to);

template <> void castMsgFromROS<hear_msgs::Update_Controller_MRFT::Request,MRFT_parameters>(hear_msgs::Update_Controller_MRFT::Request& data_from,MRFT_parameters& data_to);

template <> void castMsgFromROS<hear_msgs::Update_Controller_PID::Request,PID_parameters>(hear_msgs::Update_Controller_PID::Request& data_from,PID_parameters& data_to);

template <> void castMsgFromROS<hear_msgs::Update_Trajectory::Request,Trajectory_parameters>(hear_msgs::Update_Trajectory::Request& data_from,Trajectory_parameters& data_to);

template <> void castMsgFromROS<geometry_msgs::QuaternionStamped::ConstPtr,tf2::Quaternion>(geometry_msgs::QuaternionStamped::ConstPtr& data_from,tf2::Quaternion& data_to);


}


