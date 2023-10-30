#pragma once

#include "HEAR_core/Block.hpp"
#include "Interface_JSON_wrapper/JsonWrapperIOController.hpp"
//#include "HEAR_core/HEARTypetoString.hpp"
#include <string>
#include "http/HTTPRequest.hpp"
#include "onnx/onnx.hpp"
namespace HEAR {
    inline void castHEARtoJson(json& j,std::vector<float>& data) 
{ 

    j.SetObject();
    rapidjson::Document::AllocatorType& allocator = j.GetAllocator();
    //j.AddMember("id", data.id, allocator);
    j.AddMember("T_1", data[0], allocator);
    j.AddMember("T_2", data[1], allocator);
    j.AddMember("tau", data[2], allocator);
    j.AddMember("Kp", data[3], allocator);
    j.AddMember("Kd", data[4], allocator);
    j.AddMember("Ki", data[5], allocator);
    j.AddMember("K_proc", data[6], allocator);
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
            //std::string uri = uri;
            std::string msg_type = "onnx";
            Json_Wrapper jw;
            json msg = jw.wrap_msg(j, uri, msg_type);

            // send reuslts to drone
            std::string json_payload = jw.dump(msg);
            io_ctrl->writeJsonToIO(json_payload);

            

            //std::cout << "processAsync JsonWrapperClient>> " << jw.dump(msg) << std::endl;

        }
    }
    void reset() override{
        
    }
    std::string getTypeDescription(){
        return "JsonWrapperClient";
    }


};

}