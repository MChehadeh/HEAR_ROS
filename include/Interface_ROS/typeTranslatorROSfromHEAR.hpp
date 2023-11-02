#pragma once

#include <ros/ros.h>
#include <std_srvs/Empty.h>
#include <std_srvs/SetBool.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>
#include <geometry_msgs/Point.h>
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
#include "tf2/LinearMath/Quaternion.h"

#include "HEAR_core/DataTypes.hpp"
#include "HEAR_core/Vector3D.hpp"

#include <stdexcept>

#ifdef PX4
    #include <mavros_msgs/VehicleAttitude.h>
    #include <mavros_msgs/VehicleAngularVelocity.h>
#endif

namespace HEAR {


template <typename T>
struct ROSServiceTypeTranslator {
    // throw std::runtime_error("Invalid ROSServiceTypeTranslator function signature"); TODO: find a way to throw an error (possible constexpr)
    using ROSType = T;
};

template <>
struct ROSServiceTypeTranslator<void> {
    using ROSType = std_srvs::Empty;
};

template <>
struct ROSServiceTypeTranslator<int> {
    using ROSType = hear_msgs::set_int;
};

template <>
struct ROSServiceTypeTranslator<float> {
    using ROSType = hear_msgs::set_float;
};

template <>
struct ROSServiceTypeTranslator<bool> {
    using ROSType = hear_msgs::set_bool;
};

template <>
struct ROSServiceTypeTranslator<Vector3D<float>> {
    using ROSType = geometry_msgs::Point;
};

template <>
struct ROSServiceTypeTranslator<std::vector<float>> {
    using ROSType = std_msgs::Float32MultiArray;
};

template <>
struct ROSServiceTypeTranslator<BoundingCtrl_parameters> {
    using ROSType = hear_msgs::Update_Controller_Bounding;
};

template <>
struct ROSServiceTypeTranslator<MRFT_parameters> {
    using ROSType = hear_msgs::Update_Controller_MRFT;
};

template <>
struct ROSServiceTypeTranslator<PID_parameters> {
    using ROSType = hear_msgs::Update_Controller_PID;
};

template <>
struct ROSServiceTypeTranslator<Trajectory_parameters> {
    using ROSType = hear_msgs::Update_Trajectory;
};

template <typename T>
struct ROSTopicTypeTranslator {
    using ROSType = T;
};

template <>
struct ROSTopicTypeTranslator<int> {
    using ROSType = std_msgs::Int32;
};

template <>
struct ROSTopicTypeTranslator<float> {
    using ROSType = std_msgs::Float32;
};

template <>
struct ROSTopicTypeTranslator<Vector3D<float>> {
    using ROSType = geometry_msgs::Point;
};

template <>
struct ROSTopicTypeTranslator<tf2::Quaternion> {
    using ROSType = geometry_msgs::QuaternionStamped;
};

template <>
struct ROSTopicTypeTranslator<std::vector<float>> {
    using ROSType = std_msgs::Float32MultiArray;
};

//TODO AA remove below
#ifdef PX4
template <>
struct ROSTopicTypeTranslator<PX4_MAVROS_Vehicle_Att_data> {
    using ROSType = mavros_msgs::VehicleAttitude;
};

template <>
struct ROSTopicTypeTranslator<PX4_MAVROS_Vehicle_Ang_Vel_data> {
    using ROSType = mavros_msgs::VehicleAngularVelocity;
};
#endif
}

// int main() {
//     using OriginalType = int;
//     using Translator = TypeTranslator<OriginalType>;

//     // Accessing the member type TranslatedType
//     using TranslatedType = Translator::TranslatedType;

//     return 0;
// }