#include "Interface_mavlink/castMAVLinkToHEAR.hpp"

namespace HEAR {
    //TODO AA: Check how is hte message type enforced?
    template <> void castMAVLinkToHEAR(mavlink_message_t* data, std::vector<float>* decoded_data){
        mavlink_hil_actuator_controls_t hil_actuator_controls;
        decoded_data->reserve(16);
        mavlink_msg_hil_actuator_controls_decode(data, &hil_actuator_controls);
        for (int i = 0; i < 16; i++) {      // Note: this writes all motors including non-valid ones
            decoded_data->push_back(hil_actuator_controls.controls[i]);
        }
    }

    template <> void castMAVLinkToHEAR(mavlink_message_t* data, mavlink_heartbeat_t* heartbeat_data){
        mavlink_msg_heartbeat_decode(data, heartbeat_data);
    }

    // template <> void castMAVLinkToHEAR(mavlink_message_t* data, mavlink_vehicle_local_position_t* position_data){
    //     mavlink_msg_vehicle_local_position_decode(data, position_data);
    // }

    // template <> void castMAVLinkToHEAR(mavlink_message_t* data, mavlink_vehicle_angular_velocity_t* angular_velocity_data){
    //     mavlink_msg_vehicle_angular_velocity_decode(data, angular_velocity_data);
    // }
    
    // template <> void castMAVLinkToHEAR(mavlink_message_t* data, mavlink_vehicle_attitude_t* attitude_data){
    //     mavlink_msg_vehicle_attitude_decode(data, attitude_data);
    // }


}
