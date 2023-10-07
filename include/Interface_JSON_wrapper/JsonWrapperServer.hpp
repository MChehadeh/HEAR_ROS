#pragma once

#include "HEAR_core/Block.hpp"
#include <string>

namespace HEAR {
template <typename T>
class SystemConnectorAsync : public Block {
    AsyncInputPort<T>* inp;
    AsyncOutputPort<T>* out;
    std::string name;
public:
    enum IP{INPUT_ASYNC};
    enum OP{OUTPUT_ASYNC};

    SystemConnectorAsync(std::string _name){
        this->updateInstanceDescription(_name);
        name=_name;
        inp=createAsyncInputPort<T>(IP::INPUT_ASYNC, "Input");
        out=createAsyncOutputPort<T>(OP::OUTPUT_ASYNC,"Output");
    }
    
    void process() override {

    }
    void processAsync() override {
        if (inp->wasUpdated_AsyncIP()){
            T data;
            inp->read_AsyncIP(data);
            out->write_AsyncOP(data);
        }
    }

    std::string getTypeDescription(){
        return "SystemConnectorAsync";
    }


};

}