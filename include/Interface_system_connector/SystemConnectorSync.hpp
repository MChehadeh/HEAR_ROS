#pragma once

#include "HEAR_core/Block.hpp"
#include <string>

namespace HEAR {
template <typename T>
class SystemConnectorSync : public Block {
    InputPort<T>* inp;
    OutputPort<T>* out;
    std::string name;
public:
    enum IP{INPUT};
    enum OP{OUTPUT};

    SystemConnectorSync(std::string _name){
        this->updateInstanceDescription(_name);
        name=_name;
        inp = createInputPort<T>(0,"Input");
        out = createOutputPort<T>(0,"Output");
    }
    
    void process() override {
        T data;
        inp->read(data);
        out->write(data);
    }
    void processAsync() override {
        
    }

    void reset() override {}

    std::string getTypeDescription(){
        return "SystemConnectorSync";
    }


};

}