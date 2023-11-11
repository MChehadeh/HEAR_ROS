#pragma once
#include "natnet/DataTypes.hpp"
#include "HEAR_core/Block.hpp"
#include "Interface_motive_natnet/NatNetMotiveController.hpp"

namespace HEAR {

class NatNetMotiveController;

class NatNetMotive_Subscriber : public Block , public CallbackG<OptiTrackRigidBodyData> {
private:

NatNetMotiveController* motive_ctrl;

OutputPort<Vector3D<float>>* _output_port_position;
OutputPort<tf2::Quaternion>* _output_port_ori_quat;

public:

enum OP {OUTPUT_POS,OUTPUT_QUAT};

std::string getTypeDescription();

NatNetMotive_Subscriber(NatNetMotiveController* motive_ctrl_para,int rigid_body_id);

void callbackPerform(OptiTrackRigidBodyData rigid_body_data);

void process() override;

void processAsync() override;

void reset() override;

};

}