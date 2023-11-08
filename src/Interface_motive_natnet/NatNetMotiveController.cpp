#include "Interface_motive_natnet/NatNetMotiveController.hpp"

namespace HEAR{


NatNetMotiveController::NatNetMotiveController(){
    
}


void NatNetMotiveController::Update() { //Process the data received from the callback and give it to corresponding subscriber
    // for (auto it : *rigid_bodies_shmem.getSharedData()){
    //     this->callCallbackByKey(it.id,it);
    // }
    auto rgbdy = *rigid_bodies_shmem.getSharedData();
    this->callCallbackByKey(rgbdy.id,rgbdy);

}

void NatNetMotiveController::callbackPerform(std::tuple<size_t, char *> data){
    std::vector<OptiTrackRigidBodyData> rigid_bodies;
    Unpack((char*)std::get<1>(data),rigid_bodies);
    if (rigid_bodies.size()>0){
        rigid_bodies_shmem.writeSharedData(rigid_bodies[0]);
    }
    // for (auto rgbdy : rigid_bodies){
    //     std::cout << "Rigid Body received, id:" << rgbdy.id << ", pos: " <<rgbdy.pos.x << ","<<
    // rgbdy.pos.y << ","<< rgbdy.pos.z << ", quat: " << rgbdy.quat.getW() << ","<< 
    // rgbdy.quat.getX() << ","<< rgbdy.quat.getY() << ","<< rgbdy.quat.getZ() <<std::endl;
    // }
    
}

NatNetMotiveController::~NatNetMotiveController(){
}
    

}