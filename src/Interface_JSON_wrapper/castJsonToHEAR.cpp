#include "Interface_JSON_wrapper/castJsonToHEAR.hpp"

namespace HEAR{

// template <> void castJsonToData<LicenseCheck_response>(json_doc& j, LicenseCheck_response& data)
// { 
//     data.isDroneExist =j["isDroneExist"].GetBool();
//     data.isDroneLicensed =j["isDroneLicensed"].GetBool();

// }


template <> void castJsonToHEAR<PID_parameters>(json_doc& j,PID_parameters& data) 
{ 
    // data.id=j["id"];
    // data.kp=j["kp"];
    // data.ki=j["ki"];
    // data.kd=j["kd"];
    // data.kdd=j["kdd"];
    // data.anti_windup=j["anti_windup"];
    // data.en_pv_derivation=j["en_pv_derivation"];
    // data.dt=j["dt"];

    data.id=j["id"].GetInt();
    data.kp=j["kp"].GetDouble();
    data.ki=j["ki"].GetDouble();
    data.kd=j["kd"].GetDouble();
    data.kdd=j["kdd"].GetDouble();
    data.anti_windup=j["anti_windup"].GetDouble();
    data.en_pv_derivation=j["en_pv_derivation"].GetInt();
    data.dt=j["dt"].GetDouble();

}
template <> void castJsonToHEAR<BoundingCtrl_parameters>(json_doc& j,BoundingCtrl_parameters& data) 
{ 
    // data.id=j["id"];
    // data.eps_1=j["eps_1"];
    // data.eps_2=j["eps_2"];
    // data.h_o1=j["h_o1"];
    // data.h_o2=j["h_o2"];
    
    data.id=j["id"].GetInt();
    data.eps_1=j["eps_1"].GetFloat();
    data.eps_2=j["eps_2"].GetFloat();
    data.h_o1=j["h_o1"].GetFloat();
    data.h_o2=j["h_o2"].GetFloat();

}

template <> void castJsonToHEAR<MRFT_parameters>(json_doc& j,MRFT_parameters& data) 
{ 
    // data.id=j["id"];
    // data.beta=j["beta"];
    // data.relay_amp=j["relay_amp"];
    // data.no_switch_delay_in_ms=j["no_switch_delay_in_ms"];
    // data.num_of_peak_conf_samples=j["num_of_peak_conf_samples"];

    data.id=j["id"].GetInt();
    data.beta=j["beta"].GetFloat();
    data.relay_amp=j["relay_amp"].GetFloat();
    data.no_switch_delay_in_ms=j["no_switch_delay_in_ms"].GetInt();
    data.num_of_peak_conf_samples=j["num_of_peak_conf_samples"].GetInt();



}

template <> void castJsonToHEAR<Trajectory_parameters>(json_doc& j,Trajectory_parameters& data) 
{ 
    // data._trajectoryType=j["_trajectoryType"];
    // data._samplingType=j["_samplingType"];
    // data._transformationType=j["_transformationType"];
    // data.scale=j["scale"].get<std::vector<float>>();
    // data.rot=j["rot"].get<std::vector<float>>();
    // data.trans=j["trans"].get<std::vector<float>>();
    // data.TotalExecutionTime=j["TotalExecutionTime"];
    // data.Velocity=j["Velocity"];
    // data.ClearQ=j["ClearQ"];



    data._trajectoryType=j["_trajectoryType"].GetInt();
    data._samplingType=j["_samplingType"].GetInt();
    data._transformationType=j["_transformationType"].GetInt();
    data.TotalExecutionTime=j["TotalExecutionTime"].GetFloat();
    data.Velocity=j["Velocity"].GetFloat();
    data.ClearQ=j["ClearQ"].GetInt();
    Value scaleArr;
    scaleArr = j["scale"].GetArray();
    Value rotArr;
    rotArr = j["rot"].GetArray();
    Value transArr;
    transArr = j["trans"].GetArray();
    loadVectorArray<float>(scaleArr, data.scale);
    loadVectorArray<float>(rotArr, data.rot);
    loadVectorArray<float>(transArr, data.trans);

}


template <> void castJsonToHEAR<float>(json_doc& j,float& data,std::string _field_name) 
{ 
    // data=j[_field_name];

    data= j[_field_name.c_str()].GetFloat();
}

template <> void castJsonToHEAR<std::vector<float>>(json_doc& j,std::vector<float>& data,std::string _field_name) 
{ 
    // data=j[_field_name].get<std::vector<float>>();

    rapidjson::Value jsonShape = j[_field_name.c_str()].GetArray();

    loadVectorArray<float>(jsonShape, data);
}

}