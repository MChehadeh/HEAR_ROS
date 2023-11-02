#pragma once
#include <tuple>
#include <string>

#include "Interface_core/InterfaceController.hpp"
#include "HEAR_core/CallbackG.hpp"
#include "HEAR_core/CallerKeyed.hpp"
#include "sync_io_drivers/IOWriter.hpp"
#include "Json/Json_Wrapper.hpp"

// using namespace std;
namespace HEAR{
class JsonWrapperIOController: public InterfaceController, public CallbackG<std::tuple<size_t,char*>>, public CallerKeyed<std::string,std::string> {
private:
IOWriter* io_writer;
JsonWrapperIOController() {}
public:

void Update() override {
    //std::cout << "Update >>> " << std::endl;
    //ros::spinOnce();


}

void callbackPerform(const std::tuple<size_t,char*> data_received) override{
    //cout << "Data Received from callbackPerform is : " << std::get<1>(data_received) << endl;

    Json_Wrapper JW;
    std::string msg = std::get<1>(data_received);
    const auto [uri, msg_type, strigified_Paylaod] = JW.deWrap_msg(msg);
    std::string str_paload = strigified_Paylaod;
    std::cout << "str_paload from callbackPerform is : " << str_paload << std::endl;

    //json jsonData = JW.parse(str_paload);
    //string par = JW.dump(jsonData);
    //this->callCallbackByKey(uri,str_paload);
    //Implement
    // auto json_data=convertToJson(std::get<0>(data_received),std::get<1>(data_received)); // json_data -> uri,data_type,payload


    this->callCallbackByKey(uri, str_paload);
    
}

void writeJsonToIO(std::string json_payload){
    io_writer->writeData(json_payload.size(),json_payload.c_str());
}

JsonWrapperIOController(IOWriter* io_writer_para) : io_writer(io_writer_para) {}

~JsonWrapperIOController(){}

};
}