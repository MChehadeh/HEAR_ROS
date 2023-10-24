#pragma once
#include "mavlink.h"
#include <stdexcept>
namespace HEAR {
    template <typename T> void serializeMessage(T* data, uint8_t system_id, uint8_t component_id, mavlink_message_t &msg_data){
        throw std::runtime_error("Invalid serializeMessage function signature in MAVLink_Publisher");
    }
    template<> void serializeMessage(mavlink_hil_sensor_t* data, uint8_t system_id, uint8_t component_id, mavlink_message_t &msg_data){
        uint8_t id = 0; // Set the value of the id parameter here
        mavlink_msg_hil_sensor_pack(system_id,
        component_id,
        &msg_data,
        data->time_usec,
        data->xacc,
        data->yacc,
        data->zacc,
        data->xgyro,
        data->ygyro,
        data->zgyro,
        data->xmag,
        data->ymag,
        data->zmag,
        data->abs_pressure,
        data->diff_pressure,
        data->pressure_alt,
        data->temperature,
        data->fields_updated);
    }
    //TODO AA: add serializers for other messages
}
