#pragma once

#include "mavlink.h"
#include <stdexcept>
#include <vector>

namespace HEAR {
    template <typename T> void castMAVLinkToHEAR(mavlink_message_t* data,T* decoded_data,uint8_t msg_id){// msg_id will be used to resolve conflicts of two messages having the same resultant data-type
        throw std::runtime_error("Invalid serializeMessage function signature in MAVLink_Publisher");
    }
    
    //TODO AA: Check how is hte message type enforced?
    template <> void castMAVLinkToHEAR(mavlink_message_t* data,std::vector<float>* decoded_data,uint8_t msg_id){
        mavlink_hil_actuator_controls_t hil_actuator_controls;
        mavlink_msg_hil_actuator_controls_decode(data, &hil_actuator_controls);
        for (int i = 0; i < 16; i++) { // Note: this writes all motors including non-valid ones
            decoded_data->push_back(hil_actuator_controls.controls[i]);
        }
    }

    template <> void castMAVLinkToHEAR(mavlink_message_t* data,mavlink_heartbeat_t* heartbeat_data,uint8_t msg_id){
        mavlink_msg_heartbeat_decode(data, heartbeat_data);
    }
}