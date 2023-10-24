#pragma once

#include "HEAR_core/Block.hpp"
#include <string>

namespace HEAR {
template <typename T>
class JsonWrapperSubscriber : public Block {
    OutputPort<T>* out;
    std::string name;
public:
    enum OP{OUTPUT};

    JsonWrapperSubscriber(std::string _name){
        this->updateInstanceDescription(_name);
        name=_name;
        out=createAsyncOutputPort<T>(OP::OUTPUT,"Output");
    }
    
    void process() override {
        T data;
        inp->read_AsyncIP(data);
        out->write_AsyncOP(data);
    }
    void processAsync() override {

    }

    std::string getTypeDescription(){
        return "JsonWrapperSubscriber";
    }


};

}