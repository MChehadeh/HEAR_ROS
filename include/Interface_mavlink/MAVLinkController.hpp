#pragma once
#include <tuple>
#include <string>

#include "Interface_core/InterfaceController.hpp"
#include "HEAR_core/CallbackG.hpp"
#include "HEAR_core/CallerKeyed.hpp"
#include "sync_io_drivers/IOWriter.hpp"

#include "mavlink.h"

namespace HEAR{
class MAVLinkController: public InterfaceController, public CallbackG<std::tuple<size_t,char*>>, public CallerKeyed<int,mavlink_message_t> {
private:
IOWriter* io_writer;
MAVLinkController() {}
public:

void Update() override {

}

void callbackPerform(const std::tuple<size_t,char*> data_received) override{

    int ret=std::get<0>(data_received);
    char* buffer=std::get<1>(data_received);
    mavlink_message_t message;
    mavlink_status_t status;
    for (int i = 0; i < ret; ++i) {
        if (mavlink_parse_char(MAVLINK_COMM_0, buffer[i], &message, &status) == 1) {
            this->callCallbackByKey(message.msgid,message);
        }
    }
}

void writeMAVLinkMsgToIO(mavlink_message_t& msg){
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    int len = mavlink_msg_to_send_buffer(buffer, &msg);
    io_writer->writeData(len,(char*)buffer);
}
/// @brief Only constructor for MAVLinkController class
/// @param io_writer_para is IOWriter pointer like 
MAVLinkController(IOWriter* io_writer_para) : io_writer(io_writer_para) {}

~MAVLinkController(){}

};
}