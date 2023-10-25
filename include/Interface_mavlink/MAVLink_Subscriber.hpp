#pragma once

#include "HEAR_core/DataTypes.hpp"
#include "HEAR_core/Port.hpp"
#include "HEAR_core/CallbackG.hpp"

#include "Interface_mavlink/MAVLinkController.hpp"

#include <sstream>

namespace HEAR{

template <typename T>
class MAVLink_Subscriber : public Block, CallbackG<mavlink_message_t> {
protected:
    MAVLinkController* if_ctrl;
    OutputPort<T>* _output_port;
    uint8_t msg_id;
    T data;
public:
    enum OP {OUTPUT};

    MAVLink_Subscriber(MAVLinkController* if_ctrl_para,uint8_t msg_id_para ){
        if_ctrl=if_ctrl_para;
        std::stringstream ss;
        ss << "MAVLink_Subscriber for Msg ID: "<<msg_id_para;
        this->updateInstanceDescription(ss.str());
        msg_id=msg_id_para;
        if_ctrl->registerKeyedCallback(msg_id_para,this);
        _output_port=this->createOutputPort<T>(OP::OUTPUT,"OUTPUT");
        this->block_att->block_func=BlockNodeAttributes::Source;
    }

    void callbackPerform(mavlink_message_t msg){
        castMAVLinkToHEAR(&msg,&data);
    }

    void process() override{
        _output_port->write(data);
    }

    void processAsync() override{}

    void reset() override{}

    std::string getTypeDescription(){
        return "MAVLink_Subscriber";
    }

};

}

