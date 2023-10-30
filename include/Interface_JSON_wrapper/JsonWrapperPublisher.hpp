#ifndef JsonWrapperPublisher_HPP
#define JsonWrapperPublisher_HPP

#include "HEAR_core/Block.hpp"
#include "Interface_JSON_wrapper/JsonWrapperIOController.hpp"
//#include "HEAR_core/HEARTypetoString.hpp"
#include <string>
#include "Json/JsonHelperFunctions.hpp"
#include "Json/Json_Wrapper.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include "http/HTTPRequest.hpp"
#include "onnx/onnx.hpp"
namespace HEAR {

    
     
template <class T>
class JsonWrapperPublisher : public Block {
    
    std::string uri;
    JsonWrapperIOController* io_ctrl;
public:
    OutputPort<T>* _out;
    InputPort<T>* inp;
    enum IP{INPUT};
    enum OP{OUTPUT};
    JsonWrapperPublisher(std::string _uri,JsonWrapperIOController* io_ctrl_para){
        io_ctrl=io_ctrl_para;
        this->updateInstanceDescription(_uri);
        uri=_uri;
        inp=createInputPort<T>(IP::INPUT, "Input");
        _out = createOutputPort<T>(JsonWrapperPublisher<T>::OP::OUTPUT, "OUTPUT");

        std::cout << "start  JsonWrapperPublisher " << std::endl;
    }
    
    void process();
    void processAsync()  {
    //std::cout << "processAsync >>> " << std::endl;


    }

    void reset() ;

    std::string getTypeDescription(){
        return "JsonWrapperPublisher";
    }
    ~JsonWrapperPublisher(){

    }


};
template <class T>
void JsonWrapperPublisher<T>::process(){
    T data;
    inp->read(data);
    

}

template <class T>
void JsonWrapperPublisher<T>::reset(){
    std::cout << "reset >>> " << std::endl;

}



// template <typename T>
// void JsonWrapperPublisher::process()
// {
//     T data;
//     inp->read(data);

//     std::cout << "process >>> " << std::endl;
//     // std::cout << "process >>> " << std::get<0>(data)<< std::endl;

//     // auto data_json_payload= castHEARToJson(data);
//     // std::string data_type_desc=HEARTypetoString<T>();
//     // Form the message
//     // auto data_json=wrapJson();
//     // io_ctrl->writeJsonToIO(data_json);
// }
}

#endif