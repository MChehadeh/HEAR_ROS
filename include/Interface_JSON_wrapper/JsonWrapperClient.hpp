#pragma once

#include "HEAR_core/Block.hpp"
#include "Interface_JSON_wrapper/JsonWrapperIOController.hpp"
//#include "HEAR_core/HEARTypetoString.hpp"
#include <string>
#include "http/HTTPRequest.hpp"
#include "onnx/onnx.hpp"
namespace HEAR {
    inline void castHEARtoJson(json& j,std::tuple<double, double, double, double, double, double, double>& data) 
{ 

    j.SetObject();
    rapidjson::Document::AllocatorType& allocator = j.GetAllocator();
    //j.AddMember("id", data.id, allocator);
    j.AddMember("T_1", std::get<0>(data), allocator);
    j.AddMember("T_2", std::get<1>(data), allocator);
    j.AddMember("tau", std::get<2>(data), allocator);
    j.AddMember("Kp", std::get<3>(data), allocator);
    j.AddMember("Kd", std::get<4>(data), allocator);
    j.AddMember("Ki", std::get<5>(data), allocator);
    j.AddMember("K_proc", std::get<6>(data), allocator);
}




template <typename T>
class JsonWrapperClient : public Block {
    AsyncInputPort<T>* inp;
    std::string uri;
    JsonWrapperIOController* io_ctrl;
public:
    enum IP{INPUT_ASYNC};

    JsonWrapperClient(std::string _uri,JsonWrapperIOController* io_ctrl_para){
        io_ctrl=io_ctrl_para;
        this->updateInstanceDescription(_uri);
        uri=_uri;
        inp=createAsyncInputPort<T>(IP::INPUT_ASYNC, "Input");
    }
    
    void process()  {


    }
    void processAsync()
    {

        if (inp->wasUpdated_AsyncIP())
        {
            T data;
            inp->read_AsyncIP(data);

            json j;
            // onnx msg to json
            castHEARtoJson(j, data);
            // generate result json message
            std::string uri = "/UAV/onnx";
            std::string msg_type = "onnx";
            Json_Wrapper jw;
            json msg = jw.wrap_msg(j, uri, msg_type);

            // send reuslts to drone
            std::string json_payload = jw.dump(msg);
            string postUrl = "https://api.droneleaf.io/drone/sendResults";
            string token = "kglh3iQF2EZ35i1S2FtUta9qFNRXYAG/96kmkGGhwTs=";
            std::string dd = PostRequest(postUrl, json_payload, token);
            std::cout << dd << std::endl;

            std::cout << "processAsync JsonWrapperClient>> " << jw.dump(msg) << std::endl;

            // auto data_json_payload= castHEARToJson(data);
            // std::string data_type_desc=HEARTypetoString<T>();
            //  Form the message
            //  auto data_json=wrapJson();
            //  io_ctrl->writeJsonToIO(data_json);
        }
    }
    void reset() override{
        
    }
    std::string getTypeDescription(){
        return "JsonWrapperClient";
    }


};

}