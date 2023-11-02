#ifdef VCPKG
#pragma once

#include "HEAR_core/Block.hpp"
#include <string>
#include "Interface_JSON_wrapper/JsonWrapperIOController.hpp"

namespace HEAR {
template <typename T>
class JsonWrapperSubscriber : public Block {
    OutputPort<T>* out;
    std::string name;
    JsonWrapperIOController* io_ctrl;

public:
    enum OP{OUTPUT};

    JsonWrapperSubscriber(std::string _name,JsonWrapperIOController* io_ctrl_para){
        io_ctrl=io_ctrl_para;
        this->updateInstanceDescription(_name);
        name=_name;
        out=createOutputPort<T>(OP::OUTPUT,"Output");
    }
    
    void process() override {
        T data;
        out->write(data);
    }
    void processAsync() override {

    }
    void reset() override{
        
    }
    std::string getTypeDescription(){
        return "JsonWrapperSubscriber";
    }


};

}
#endif