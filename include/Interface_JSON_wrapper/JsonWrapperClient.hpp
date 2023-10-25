#pragma once

#include "HEAR_core/Block.hpp"
#include "Interface_JSON_wrapper/JsonWrapperIOController.hpp"
#include "HEAR_core/HEARTypetoString.hpp"
#include <string>

namespace HEAR {
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
    
    void process() override {

    }
    void processAsync() override {
        if (inp->wasUpdated_AsyncIP()){
            T data;
            inp->read_AsyncIP(data);
            auto data_json_payload= castHEARToJson(data);
            std::string data_type_desc=HEARTypetoString<T>();
            // Form the message
            // auto data_json=wrapJson();
            // io_ctrl->writeJsonToIO(data_json);
        }
    }
    void reset() override{
        
    }
    std::string getTypeDescription(){
        return "JsonWrapperClient";
    }


};

}