#ifdef VCPKG
#include "Interface_JSON_wrapper/castHEARtoJson.hpp"

namespace HEAR{

//     template <> void castHEARtoJson<std::tuple<double, double, double, double, double, double, double>>(json_doc& j,std::tuple<double, double, double, double, double, double, double>& data) 
// { 

//     j.SetObject();
//     rapidjson::Document::AllocatorType& allocator = j.GetAllocator();
//     //j.AddMember("id", data.id, allocator);
//     j.AddMember("T_1", std::get<0>(data), allocator);
//     j.AddMember("T_2", std::get<1>(data), allocator);
//     j.AddMember("tau", std::get<2>(data), allocator);
//     j.AddMember("Kp", std::get<3>(data), allocator);
//     j.AddMember("Kd", std::get<4>(data), allocator);
//     j.AddMember("Ki", std::get<5>(data), allocator);
//     j.AddMember("K_proc", std::get<6>(data), allocator);
// }
    
template <> void castHEARtoJson<PID_parameters>(json_doc& j,PID_parameters& data) 
{ 
    // std::tie(j["id"], j["kp"], j["ki"], j["kd"], j["kdd"], j["anti_windup"], j["dt"], j["en_pv_derivation"]) = 
    // std::make_tuple(data.id,data.kp,data.ki,data.kd,data.kdd,data.anti_windup,data.dt,(int)data.en_pv_derivation);


    j.SetObject();
    rapidjson::Document::AllocatorType& allocator = j.GetAllocator();
    j.AddMember("id", data.id, allocator);
    j.AddMember("kp", data.kp, allocator);
    j.AddMember("ki", data.ki, allocator);
    j.AddMember("kd", data.kd, allocator);
    j.AddMember("kdd", data.kdd, allocator);
    j.AddMember("anti_windup", data.anti_windup, allocator);
    j.AddMember("dt", data.dt, allocator);
    j.AddMember("en_pv_derivation", data.en_pv_derivation, allocator);
}
template <> void castHEARtoJson<BoundingCtrl_parameters>(json_doc& j,BoundingCtrl_parameters& data) 
{ 
    // std::tie(j["id"], j["eps_1"], j["eps_2"], j["h_o1"], j["h_o2"]) = 
    // std::make_tuple(data.id,data.eps_1,data.eps_2,data.h_o1,data.h_o2);

    j.SetObject();
    rapidjson::Document::AllocatorType& allocator = j.GetAllocator();
    j.AddMember("id", data.id, allocator);
    j.AddMember("eps_1", data.eps_1, allocator);
    j.AddMember("eps_2", data.eps_2, allocator);
    j.AddMember("h_o1", data.h_o1, allocator);
    j.AddMember("h_o2", data.h_o2, allocator);
}

template <> void castHEARtoJson<MRFT_parameters>(json_doc& j,MRFT_parameters& data) 
{
    // std::tie(j["id"], j["beta"], j["relay_amp"], j["no_switch_delay_in_ms"], j["num_of_peak_conf_samples"]) = 
    // std::make_tuple(data.id,data.beta,data.relay_amp,data.no_switch_delay_in_ms,data.num_of_peak_conf_samples);


    j.SetObject();
    rapidjson::Document::AllocatorType& allocator = j.GetAllocator();
    j.AddMember("id", data.id, allocator);
    j.AddMember("beta", data.beta, allocator);
    j.AddMember("relay_amp", data.relay_amp, allocator);
    j.AddMember("no_switch_delay_in_ms", data.no_switch_delay_in_ms, allocator);
    j.AddMember("num_of_peak_conf_samples", data.num_of_peak_conf_samples, allocator);
}

template <> void castHEARtoJson<Trajectory_parameters>(json_doc& j,Trajectory_parameters& data) 
{
    // std::tie(j["_trajectoryType"], j["_samplingType"], j["_transformationType"], j["scale"], j["rot"], j["trans"], j["TotalExecutionTime"], j["Velocity"],j["ClearQ"]) = 
    // std::make_tuple(data._trajectoryType,data._samplingType,data._transformationType,
    // data.scale,data.rot,data.trans,
    // data.TotalExecutionTime,data.Velocity,data.ClearQ);


    j.SetObject();
    rapidjson::Document::AllocatorType& allocator = j.GetAllocator();
    j.AddMember("_trajectoryType", data._trajectoryType, allocator);
    j.AddMember("TotalExecutionTime", data.TotalExecutionTime, allocator);
    j.AddMember("Velocity", data.Velocity, allocator);
    j.AddMember("_samplingType", data._samplingType, allocator);
    j.AddMember("_transformationType", data._transformationType, allocator);
    j.AddMember("ClearQ", data.ClearQ, allocator);

    rapidjson::Value scaleArray(rapidjson::kArrayType);
    rapidjson::Value rotArray(rapidjson::kArrayType);
    rapidjson::Value transArray(rapidjson::kArrayType);
    loadRapidJsonArray<float>(data.scale, allocator, scaleArray);
    loadRapidJsonArray<float>(data.rot, allocator, rotArray);
    loadRapidJsonArray<float>(data.trans, allocator, transArray);

    j.AddMember("scale", scaleArray, allocator);
    j.AddMember("rot", rotArray, allocator);
    j.AddMember("trans", transArray, allocator);
}

}
#endif