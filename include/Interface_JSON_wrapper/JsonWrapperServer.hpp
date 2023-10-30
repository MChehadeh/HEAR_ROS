#pragma once

#include "HEAR_core/Block.hpp"
#include <string>
#include "Interface_JSON_wrapper/JsonWrapperIOController.hpp"

namespace HEAR {
template <typename T>
class JsonWrapperServer : public Block,public CallbackG<std::string> {
    AsyncOutputPort<T>* out;
    std::string name;
    JsonWrapperIOController* io_ctrl;

public:
    enum OP{OUTPUT_ASYNC};

    JsonWrapperServer(std::string _name,JsonWrapperIOController* io_ctrl_para){
        io_ctrl=io_ctrl_para;
        io_ctrl_para->registerKeyedCallback(_name,this);

        this->updateInstanceDescription(_name);
        name=_name;
        out=createAsyncOutputPort<T>(OP::OUTPUT_ASYNC,"Output");
    }
    void callbackPerform(T ipc_msg)
    {
        std::cout << "from JsonWrapperServer callbackPerform ...." << ipc_msg<< std::endl;
        out->write_AsyncOP(ipc_msg);

    }

    void process() override {

    }
    void processAsync() override {
        //T data;
        //out->write_AsyncOP(data);
    }
    void reset() override{
        
    }
    std::string getTypeDescription(){
        return "JsonWrapperServer";
    }


};

}