#pragma once
#include "Interface_core/InterfaceController.hpp"
#include "natnet/natnet_optitrack.hpp"
#include "natnet/DataTypes.hpp"
#include "HEAR_core/SharedMemory.hpp"
#include "HEAR_core/Threaded.hpp"
#include "HEAR_core/CallbackG.hpp"
#include "HEAR_core/CallerKeyed.hpp"
#include "Interface_motive_natnet/NatNetMotive_Subscriber.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

namespace HEAR{

class NatNetMotiveController: public InterfaceController , public CallbackG<std::tuple<size_t, char *>>, public CallerKeyed<int,OptiTrackRigidBodyData> {
private:
// SharedMemory<std::vector<OptiTrackRigidBodyData>> rigid_bodies_shmem;
SharedMemory<OptiTrackRigidBodyData> rigid_bodies_shmem;

public:

NatNetMotiveController();
void HandShakeMotive(unsigned char* multicastAddr,unsigned char* ownAddr,unsigned char* serverAddr);
void Update() override; //Process the data received from the callback and give it to corresponding subscriber

void callbackPerform(std::tuple<size_t, char *> data) override;

~NatNetMotiveController();
    
};
}