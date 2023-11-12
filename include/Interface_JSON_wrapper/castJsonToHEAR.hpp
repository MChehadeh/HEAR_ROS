#ifdef VCPKG
#pragma once

#include "Json/JsonHelperFunctions.hpp"
#include "HEAR_core/DataTypes.hpp"

namespace HEAR{

template <typename T> void castJsonToHEAR(json_doc& json_data,T& data) 
{ 
    throw std::runtime_error("Invalid castJsonToHEAR function signature in LoadFromJsonG");
}

template <> void castJsonToHEAR<PID_parameters>(json_doc& j,PID_parameters& data);

template <> void castJsonToHEAR<BoundingCtrl_parameters>(json_doc& j,BoundingCtrl_parameters& data) ;

template <> void castJsonToHEAR<MRFT_parameters>(json_doc& j,MRFT_parameters& data);

template <> void castJsonToHEAR<Trajectory_parameters>(json_doc& j,Trajectory_parameters& data);


template <typename T> void castJsonToHEAR(json_doc& json_data,T& data,std::string _field_name) 
{ 
    throw std::runtime_error("Invalid castJsonToHEAR function signature in LoadFromJsonG");
}

template <> void castJsonToHEAR<float>(json_doc& j,float& data,std::string _field_name) ;

template <> void castJsonToHEAR<std::vector<float>>(json_doc& j,std::vector<float>& data,std::string _field_name) ;

}
#endif