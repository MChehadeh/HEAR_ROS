#include "Interface_motive_natnet/NatNetMotive_Subscriber.hpp"

namespace HEAR {

std::string NatNetMotive_Subscriber::getTypeDescription(){
    return "NatNetMotiveSubscriber";
}
NatNetMotive_Subscriber::NatNetMotive_Subscriber(NatNetMotiveController* motive_ctrl_para, int rigid_body_id){
    motive_ctrl=motive_ctrl_para;
    motive_ctrl_para->registerKeyedCallback(rigid_body_id,this);
    _output_port_position=this->createOutputPort<Vector3D<float>>(OP::OUTPUT_POS,"OUTPUT_POS");
    _output_port_ori_quat=this->createOutputPort<tf2::Quaternion>(OP::OUTPUT_QUAT,"OUTPUT_QUAT");
    this->block_att->block_func=BlockNodeAttributes::Source;
}
void NatNetMotive_Subscriber::callbackPerform(OptiTrackRigidBodyData rigid_body_data){
    _output_port_position->write(rigid_body_data.pos);
    _output_port_ori_quat->write(rigid_body_data.quat);
    // std::cout << "Rigid Body received, id:" << rigid_body_data.id << ", pos: " <<rigid_body_data.pos.x << ","<<
    // rigid_body_data.pos.y << ","<< rigid_body_data.pos.z << ", quat: " << rigid_body_data.quat.getW() << ","<< 
    // rigid_body_data.quat.getX() << ","<< rigid_body_data.quat.getY() << ","<< rigid_body_data.quat.getZ() <<std::endl;
}

void NatNetMotive_Subscriber::process() {
    // OptiTrackRigidBodyData rigid_body_data;
    // rigid_body_data.pos.x=1.0;
    // _output_port_position->write(rigid_body_data.pos);
    // _output_port_ori_quat->write(rigid_body_data.quat);
    // std::cout << "Rigid Body received, id:" << rigid_body_data.id << ", pos: " <<rigid_body_data.pos.x << ","<<
    // rigid_body_data.pos.y << ","<< rigid_body_data.pos.z << ", quat: " << rigid_body_data.quat.getW() << ","<< 
    // rigid_body_data.quat.getX() << ","<< rigid_body_data.quat.getY() << ","<< rigid_body_data.quat.getZ() <<std::endl;
}

void NatNetMotive_Subscriber::processAsync() {}

void NatNetMotive_Subscriber::reset() {}



}