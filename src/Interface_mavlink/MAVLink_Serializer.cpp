#include "Interface_mavlink/MAVLink_Serializer.hpp"

namespace HEAR {
    
    //TODO AA: remove component and system id
    template <> void serializeMessage<mavlink_hil_sensor_t>(mavlink_hil_sensor_t* data, mavlink_message_t &msg_data){
        uint8_t id = 0; // Set the value of the id parameter here
        uint8_t system_id = 1;
        uint8_t component_id = 0x33;
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
        data->fields_updated,
        id);
    }

    //TODO AA: add serializers for other messages
    template <> void serializeMessage(mavlink_vision_position_estimate_t* data, mavlink_message_t &msg_data){
        uint8_t id = 0; // Set the value of the id parameter here
        uint8_t system_id = 1;
        uint8_t component_id = 0x33;
        mavlink_msg_vision_position_estimate_pack(system_id,
        component_id,
        &msg_data,
        data->usec,
        data->x,
        data->y,
        data->z,
        data->roll,
        data->pitch,
        data->yaw,
        data->covariance,
        data->reset_counter);
    }

    //TODO AA: Do we need to create custom data types, or can we directly use the defined structs
    template <> void serializeMessage(mavlink_hil_state_quaternion_t* data, mavlink_message_t &msg_data){
        uint8_t id = 0; // Set the value of the id parameter here
        uint8_t system_id = 1;
        uint8_t component_id = 0x33;
        mavlink_msg_hil_state_quaternion_pack(system_id,
        component_id,
        &msg_data,
        data->time_usec,
        data->attitude_quaternion,
        data->rollspeed,
        data->pitchspeed,
        data->yawspeed,
        data->lat,
        data->lon,
        data->alt,
        data->vx,
        data->vy,
        data->vz,
        data->ind_airspeed,
        data->true_airspeed,
        data->xacc,
        data->yacc,
        data->zacc);
    }

    template <> void serializeMessage(mavlink_system_time_t* data, mavlink_message_t &msg_data){
        uint8_t id = 0; // Set the value of the id parameter here
        uint8_t system_id = 1;
        uint8_t component_id = 0x33;
        mavlink_msg_system_time_pack(system_id,
        component_id,
        &msg_data,
        data->time_unix_usec,
        data->time_boot_ms);
    }

    template <> void serializeMessage(mavlink_heartbeat_t* data, mavlink_message_t &msg_data){
        uint8_t id = 0; // Set the value of the id parameter here
        uint8_t system_id = 1;
        uint8_t component_id = 0x33;        
        mavlink_msg_heartbeat_pack(system_id,
        component_id,
        &msg_data,
        data->type,
        data->autopilot,
        data->base_mode,
        data->custom_mode,
        data->system_status);
    }
}
