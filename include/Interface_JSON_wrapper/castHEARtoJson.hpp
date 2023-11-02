#ifdef VCPKG
#pragma once

#include <string>
#include "Json/JsonHelperFunctions.hpp"
#include "HEAR_core/DataTypes.hpp"

namespace HEAR{

template <typename T> void castHEARtoJson(json& json_data,T& data) 
{ 
    throw std::runtime_error("Invalid castHEARtoJson function signature in SaveToJson");
    }
template <> void castHEARtoJson<PID_parameters>(json& j,PID_parameters& data);

template <> void castHEARtoJson<BoundingCtrl_parameters>(json& j,BoundingCtrl_parameters& data);

template <> void castHEARtoJson<MRFT_parameters>(json& j,MRFT_parameters& data);

template <> void castHEARtoJson<Trajectory_parameters>(json& j,Trajectory_parameters& data);

}
#endif