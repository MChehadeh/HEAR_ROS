#pragma once

#include <sstream>
#include "HEAR_core/DataTypes.hpp"
#include "HEAR_core/Port.hpp"

#include "Interface_mavlink/MAVLinkController.hpp"
#include "Interface_mavlink/MAVLink_Serializer.hpp"

namespace HEAR{

template <typename T>
class MAVLink_Publisher : public Block {
private:
    MAVLinkController* if_ctrl;
protected:
    InputPort<T>* _input_port;

public:
    enum IP {INPUT};
    MAVLink_Publisher(MAVLinkController* if_ctrl_para,std::string uri) {
        if_ctrl=if_ctrl_para;
        this->updateInstanceDescription(uri);
        _input_port=this->createInputPort<T>(IP::INPUT,"INPUT");
        this->block_att->block_func=BlockNodeAttributes::Sink;
    }
    void process() override{
        mavlink_message_t msg;
        T buff;
        ((InputPort<T>*)_input_port)->read(buff);
        serializeMessage(&buff, msg);
        if_ctrl->writeMAVLinkMsgToIO(msg);
    }

    void processAsync() override{}

    void reset() override{}

    std::string getTypeDescription(){
        return "MAVLink_Publisher";
    }


};

}