#include "Interface_ROS/castMsgROSG.hpp"

namespace HEAR {

template <> void castMsgToROS<int,std_srvs::Empty>(int& data_from,std_srvs::Empty& data_to) 
{ 

}

template <> void castMsgToROS<bool,hear_msgs::set_bool>(bool& data_from,hear_msgs::set_bool& data_to) 
{ 
    data_to.request.data=data_from; 
}

template <> void castMsgToROS<int,hear_msgs::set_int>(int& data_from,hear_msgs::set_int& data_to) 
{ 
    data_to.request.data=data_from; 
}

template <> void castMsgToROS<float,hear_msgs::set_float>(float& data_from,hear_msgs::set_float& data_to) 
{ 
    data_to.request.data=data_from; 
}

template <> void castMsgToROS<float,std_msgs::Float32>(float& data_from,std_msgs::Float32& data_to) 
{ 
    data_to.data=data_from; 
}

template <> void castMsgToROS<Vector3D<float>,hear_msgs::set_point>(Vector3D<float>& data_from,hear_msgs::set_point& data_to) 
{ 
    data_to.request.x=data_from.x;
    data_to.request.y=data_from.y;
    data_to.request.z=data_from.z;
}

template <> void castMsgToROS<Vector3D<float>,geometry_msgs::Point>(Vector3D<float>& data_from,geometry_msgs::Point& data_to) 
{ 
    data_to.x= data_from.x;
    data_to.y= data_from.y;
    data_to.z= data_from.z;
}

template <> void castMsgToROS<std::vector<float>,std_msgs::Float32MultiArray>(std::vector<float>& data_from,std_msgs::Float32MultiArray& data_to) 
{ 
    // throw std::logic_error("Function not yet implemented");
    //data_to.request.data=data_from;

    data_to.data.clear();
    
    for (const auto& value : data_from)
    {
        data_to.data.push_back(value);
    }
}

template <> void castMsgToROS<BoundingCtrl_parameters,hear_msgs::Update_Controller_Bounding>(BoundingCtrl_parameters& data_from,hear_msgs::Update_Controller_Bounding& data_to) 
{ 
    data_to.request.controller_parameters.id = (int)data_from.id;
    data_to.request.controller_parameters.bounding_eps_1 = data_from.eps_1;
    data_to.request.controller_parameters.bounding_eps_2 = data_from.eps_2;
    data_to.request.controller_parameters.bounding_h_o1 = data_from.h_o1;
    data_to.request.controller_parameters.bounding_h_o2 = data_from.h_o2;
}

template <> void castMsgToROS<MRFT_parameters,hear_msgs::Update_Controller_MRFT>(MRFT_parameters& data_from,hear_msgs::Update_Controller_MRFT& data_to) 
{ 
    data_to.request.controller_parameters.id = (int)data_from.id;
    data_to.request.controller_parameters.mrft_beta = data_from.beta;
    data_to.request.controller_parameters.mrft_relay_amp = data_from.relay_amp;
    data_to.request.controller_parameters.mrft_no_switch_delay = data_from.no_switch_delay_in_ms;
    data_to.request.controller_parameters.mrft_conf_samples = data_from.num_of_peak_conf_samples;
}

template <> void castMsgToROS<PID_parameters,hear_msgs::Update_Controller_PID>(PID_parameters& data_from,hear_msgs::Update_Controller_PID& data_to) 
{ 
    data_to.request.controller_parameters.id = (int)data_from.id;
    data_to.request.controller_parameters.pid_kp = data_from.kp;
    data_to.request.controller_parameters.pid_ki = data_from.ki;
    data_to.request.controller_parameters.pid_kd = data_from.kd;
    data_to.request.controller_parameters.pid_kdd = data_from.kdd;
    data_to.request.controller_parameters.pid_anti_windup = data_from.anti_windup;
    data_to.request.controller_parameters.pid_en_pv_derivation = data_from.en_pv_derivation;
    data_to.request.controller_parameters.pid_dt = data_from.dt;
}

template <> void castMsgToROS<Trajectory_parameters,hear_msgs::Update_Trajectory>(Trajectory_parameters& data_from,hear_msgs::Update_Trajectory& data_to) 
{ 
    data_to.request.trajectory_parameters.trajectoryType = (int)data_from._trajectoryType;
    data_to.request.trajectory_parameters.samplingType = (int)data_from._samplingType;
    data_to.request.trajectory_parameters.transformationType = (int)data_from._transformationType;
    data_to.request.trajectory_parameters.scale = data_from.scale;
    data_to.request.trajectory_parameters.rot = data_from.rot;
    data_to.request.trajectory_parameters.trans = data_from.trans;
    data_to.request.trajectory_parameters.TotalExecutionTime = data_from.TotalExecutionTime;
    data_to.request.trajectory_parameters.Velocity = data_from.Velocity;
    data_to.request.trajectory_parameters.ClearQ = data_from.ClearQ;
}

template <> void castMsgToROS<PX4_MAVROS_Vehicle_Att_data,mavros_msgs::VehicleAttitude>(PX4_MAVROS_Vehicle_Att_data& data_from,mavros_msgs::VehicleAttitude& data_to){
    // data_from.att_quat=tf2::Quaternion(data_to->q_x, data_to->q_y, data_to->q_z, data_to->q_w );
}

template <> void castMsgToROS<PX4_MAVROS_Vehicle_Ang_Vel_data,mavros_msgs::VehicleAngularVelocity>(PX4_MAVROS_Vehicle_Ang_Vel_data& data_from,mavros_msgs::VehicleAngularVelocity& data_to){

}




template <> void castMsgFromROS<std_srvs::Empty::Request,int>(std_srvs::Empty::Request& data_from,int& data_to) 
{ 

}


template <> void castMsgFromROS<hear_msgs::set_bool::Request,bool>(hear_msgs::set_bool::Request& data_from, bool& data_to) 
{ 
    data_to=data_from.data; 
}

template <> void castMsgFromROS<hear_msgs::set_int::Request,int>(hear_msgs::set_int::Request& data_from,int& data_to) 
{ 
    data_to=data_from.data; 
}

template <> void castMsgFromROS<hear_msgs::set_float::Request,float>(hear_msgs::set_float::Request& data_from,float& data_to) 
{ 
    data_to=data_from.data; 
}

template <> void castMsgFromROS<std_msgs::Float32,float>(std_msgs::Float32& data_from,float& data_to) 
{ 
    data_to=data_from.data; 
}

template <> void castMsgFromROS<hear_msgs::set_point,Vector3D<float>>(hear_msgs::set_point& data_from,Vector3D<float>& data_to) 
{ 
    data_to.x= data_from.request.x;
    data_to.y= data_from.request.y;
    data_to.z= data_from.request.z;
}

template <> void castMsgFromROS<Vector3D<float>,geometry_msgs::Point>(Vector3D<float>& data_from,geometry_msgs::Point& data_to) 
{ 
    data_to.x= data_from.x;
    data_to.y= data_from.y;
    data_to.z= data_from.z;
}

template <> void castMsgFromROS<std_msgs::Float32MultiArray,std::vector<float>>(std_msgs::Float32MultiArray& data_from,std::vector<float>& data_to) 
{ 
    throw std::logic_error("Function not yet implemented");
    //data_to=data_from.request.data;
}

template <> void castMsgFromROS<hear_msgs::Update_Controller_Bounding,BoundingCtrl_parameters>(hear_msgs::Update_Controller_Bounding& data_from,BoundingCtrl_parameters& data_to) 
{ 
    data_to.id =data_from.request.controller_parameters.id;
    data_to.eps_1 = data_from.request.controller_parameters.bounding_eps_1;
    data_to.eps_2 = data_from.request.controller_parameters.bounding_eps_2;
    data_to.h_o1 = data_from.request.controller_parameters.bounding_h_o1;
    data_to.h_o2 = data_from.request.controller_parameters.bounding_h_o2;
}

template <> void castMsgFromROS<hear_msgs::Update_Controller_MRFT,MRFT_parameters>(hear_msgs::Update_Controller_MRFT& data_from,MRFT_parameters& data_to) 
{ 
     data_to.id = data_from.request.controller_parameters.id;
     data_to.beta = data_from.request.controller_parameters.mrft_beta;
     data_to.relay_amp = data_from.request.controller_parameters.mrft_relay_amp;
     data_to.no_switch_delay_in_ms = data_from.request.controller_parameters.mrft_no_switch_delay;
     data_to.num_of_peak_conf_samples = data_from.request.controller_parameters.mrft_conf_samples;
}

template <> void castMsgFromROS<hear_msgs::Update_Controller_PID,PID_parameters>(hear_msgs::Update_Controller_PID& data_from,PID_parameters& data_to) 
{ 
     data_to.id = data_from.request.controller_parameters.id;
     data_to.kp = data_from.request.controller_parameters.pid_kp;
     data_to.ki = data_from.request.controller_parameters.pid_ki;
     data_to.kd = data_from.request.controller_parameters.pid_kd;
     data_to.kdd= data_from.request.controller_parameters.pid_kdd;
     data_to.anti_windup= data_from.request.controller_parameters.pid_anti_windup;
     data_to.en_pv_derivation=data_from.request.controller_parameters.pid_en_pv_derivation;
     data_to.dt=data_from.request.controller_parameters.pid_dt;
}

template <> void castMsgFromROS<hear_msgs::Update_Trajectory,Trajectory_parameters>(hear_msgs::Update_Trajectory& data_from,Trajectory_parameters& data_to) 
{ 
     data_to._trajectoryType = data_from.request.trajectory_parameters.trajectoryType;
     data_to._samplingType = data_from.request.trajectory_parameters.samplingType;
     data_to._transformationType = data_from.request.trajectory_parameters.transformationType;
     data_to.scale = data_from.request.trajectory_parameters.scale;
     data_to.rot = data_from.request.trajectory_parameters.rot;
     data_to.trans = data_from.request.trajectory_parameters.trans;
     data_to.TotalExecutionTime = data_from.request.trajectory_parameters.TotalExecutionTime;
     data_to.Velocity = data_from.request.trajectory_parameters.Velocity;
     data_to.ClearQ =data_from.request.trajectory_parameters.ClearQ;
}

template <> void castMsgFromROS<geometry_msgs::Vector3Stamped,Vector3D<float>>(geometry_msgs::Vector3Stamped& data_from,Vector3D<float>& data_to){
    data_to.x = data_from.vector.x;
    data_to.y = data_from.vector.y;
    data_to.z = data_from.vector.z;
}

template <> void castMsgFromROS<geometry_msgs::QuaternionStamped,tf2::Quaternion>(geometry_msgs::QuaternionStamped& data_from,tf2::Quaternion& data_to){
    data_to = tf2::Quaternion(data_from.quaternion.x, data_from.quaternion.y, data_from.quaternion.z, data_from.quaternion.w);
}

//TODO AA: remove below and mavros dependancy
template <> void castMsgFromROS<mavros_msgs::VehicleAttitude,PX4_MAVROS_Vehicle_Att_data>(mavros_msgs::VehicleAttitude& data_from,PX4_MAVROS_Vehicle_Att_data& data_to){
    // data_to.att_quat=tf2::Quaternion(data_from->q_x, data_from->q_y, data_from->q_z, data_from->q_w );
}

template <> void castMsgFromROS<mavros_msgs::VehicleAngularVelocity,PX4_MAVROS_Vehicle_Ang_Vel_data>(mavros_msgs::VehicleAngularVelocity& data_from,PX4_MAVROS_Vehicle_Ang_Vel_data& data_to){
    
}
    
}

// template <typename T> 
// void castMsgToROS(T& data_from) 
// { 
//     throw std::runtime_error("Invalid castMsgToROS function signature in ROSUnit_Client");
//     }
// template <> std_srvs::Empty castMsgToROS<void>(void& data_from) 
// { 
//     std_srvs::Empty msg;
//     return msg;
// }

// template <> hear_msgs::set_bool castMsgToROS<bool>(bool& data_from) 
// { 
//     hear_msgs::set_bool msg;
//     msg.request.data = data_from; 
//     return msg;
// }
