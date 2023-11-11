#include "Interface_motive_natnet/NatNetMotiveController.hpp"

namespace HEAR{


NatNetMotiveController::NatNetMotiveController(){

}


void NatNetMotiveController::HandShakeMotive(unsigned char* multicastAddr,unsigned char* ownAddr,unsigned char* serverAddr){
        //OptiTrack NatNet
    int optval = OPTVAL_REQUEST_SIZE;
    int optval_size = 4;

    sParsedArgs parsedArgs;
    parsedArgs.useMulticast=true;
    unsigned char multiCastAddress[4];
    for (int i=0;i<4;i++){
        multiCastAddress[i]=multicastAddr[i];
    }
    parsedArgs.multiCastAddress.s_addr=htonl(charArrayToUint32(multiCastAddress));
    unsigned char myAddress[4];
    for (int i=0;i<4;i++){
        myAddress[i]=ownAddr[i];
    }
    parsedArgs.myAddress.s_addr=htonl(charArrayToUint32(myAddress));

    gUseMulticast=parsedArgs.useMulticast;

    // create "Command" socket
    int commandPort = 0;
    gCommandSocket = CreateCommandSocket(myAddress,commandPort, optval, gUseMulticast);
    if(gCommandSocket == -1)
    {
        // error
        // printf("[PacketClient Main] gCommandSocket create failure (error: %s)\n", GetWSAErrorString(WSAGetLastError()).c_str());
        printf("[PacketClient Main] gCommandSocket create failure\n");
        // WSACleanup();
        close(gCommandSocket);
        return;
    }
    printf("[PacketClient Main] gCommandSocket started\n");



    // create the gDataSocket
    int dataPort = 0;
    gDataSocket = CreateDataSocket(myAddress,dataPort, optval,
        parsedArgs.useMulticast, multiCastAddress, PORT_DATA);
    if (gDataSocket == -1)
    {
        //printf("[PacketClient Main] gDataSocket create failure (error: %s)\n", GetWSAErrorString(WSAGetLastError()).c_str());
        printf("[PacketClient Main] gDataSocket create failure\n");
        close(gDataSocket);
        //WSACleanup();
        return;				  
    }
    printf("[PacketClient Main] gDataSocket started\n");

// startup our "Command Listener" thread
    // std::thread cmdProcessor(CommandListenThread);
    //commandListenThreadHandle = CreateThread(&commandListenSecurityAttribs, 0, CommandListenThread, NULL, 0, &commandListenThreadID);
    // printf("[PacketClient Main] CommandListenThread started\n");
    
    // startup our "Data Listener" thread
    //std::thread dataProcessor(DataListenThread);
    //dataListenThread_Handle = CreateThread( &dataListenThreadSecurityAttribs, 0, DataListenThread, NULL, 0, &dataListenThread_ID);
    //printf("[PacketClient Main] DataListenThread started\n");

    // server address for commands
    memset(&gHostAddr, 0, sizeof(gHostAddr));
    gHostAddr.sin_family = AF_INET;        
    gHostAddr.sin_port = htons(PORT_COMMAND);
    unsigned char serverAddress[4];
    for (int i=0;i<4;i++){
        serverAddress[i]=serverAddr[i];
    }
    gHostAddr.sin_addr.s_addr = htonl(charArrayToUint32(serverAddress));

    // send initial connect request
    sPacket* PacketOut = new sPacket();
    sSender sender;
    sConnectionOptions connectOptions;
    PacketOut->iMessage = NAT_CONNECT;
    PacketOut->nDataBytes = sizeof(sSender) + sizeof(connectOptions) + 4;
    memset(&sender, 0, sizeof(sender));
    memcpy(&PacketOut->Data, &sender, (int)sizeof(sSender));

    // [optional] Custom connection options
    /*
    connectOptions.subscribedDataOnly = true;
    connectOptions.BitstreamVersion[0] = 2;
    connectOptions.BitstreamVersion[1] = 2;
    connectOptions.BitstreamVersion[2] = 0;
    connectOptions.BitstreamVersion[3] = 0;
    */
    memcpy(&PacketOut->Data.cData[(int)sizeof(sSender)], &connectOptions, sizeof(connectOptions));

    int nTries = 3;
    int iRet = -1;
    while (nTries--)
    {
        iRet = sendto(gCommandSocket, (char *)PacketOut, 4 + PacketOut->nDataBytes, 0, (sockaddr *)&gHostAddr, sizeof(gHostAddr));
        if(iRet <0)
            break;
    }
    if (iRet <0)
    {
        printf("[PacketClient Main] gCommandSocket sendto error \n");
        return;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    PacketOut->iMessage = NAT_REQUEST_MODELDEF;
    PacketOut->nDataBytes = 0;
    nTries = 3;
    iRet = -1;
    while (nTries--)
    {
        iRet = sendto(gCommandSocket, (char *)PacketOut, 4 + PacketOut->nDataBytes, 0, (sockaddr *)&gHostAddr, sizeof(gHostAddr));
        if(iRet >= 0)
            break;
    }
    printf("Command: NAT_REQUEST_MODELDEF returned value: %d%s\n", iRet, (iRet==-1)?" SOCKET_ERROR":"");


    SetNatNetVersion(4,0);

    // char szCommand[512];
    // sprintf(szCommand, "TimelinePlay");
    // int returnCode = SendCommand(szCommand);
    // printf("Command: %s -  returnCode: %d\n", szCommand, returnCode);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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