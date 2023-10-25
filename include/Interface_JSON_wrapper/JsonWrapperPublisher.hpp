#pragma once

#include "HEAR_core/Block.hpp"
#include "Interface_JSON_wrapper/JsonWrapperIOController.hpp"
#include "HEAR_core/HEARTypetoString.hpp"
#include <string>

namespace HEAR {
template <typename T>
class JsonWrapperPublisher : public Block {
    InputPort<T>* inp;
    std::string uri;
    JsonWrapperIOController* io_ctrl;
public:
    enum IP{INPUT};

    JsonWrapperPublisher(std::string _uri,JsonWrapperIOController* io_ctrl_para){
        io_ctrl=io_ctrl_para;
        this->updateInstanceDescription(_uri);
        uri=_uri;
        inp=createInputPort<T>(IP::INPUT, "Input");
    }
    
    void process() override {
        T data;
        inp->read(data);
        // auto data_json_payload= castHEARToJson(data);
        // std::string data_type_desc=HEARTypetoString<T>();
        // Form the message
        // auto data_json=wrapJson();
        // io_ctrl->writeJsonToIO(data_json);
    }
    void processAsync() override {

    }

    void reset() override{

    }

    std::string getTypeDescription(){
        return "JsonWrapperPublisher";
    }


};

}