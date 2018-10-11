//
//  MSServer.cpp
//  MSSocketLibrary
//
//  Created by Mihail Shevchuk on 24.01.18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#include "MSServer.hpp"

MSServer::MSServer(uint32_t port, uint32_t sizeBuffer):
MSSocket(MSEventType::NETWORK_SERVER, NULL, port, sizeBuffer),
mClientId(0),
mClientLen(0),
mServerId(0),
mServerLen(0),
mLaunchServerThread(0) {
}

MSServer::MSServer(pChar serverPath, uint32_t sizeBuffer):
MSSocket(MSEventType::LOCAL_SERVER, serverPath, sizeBuffer),
mClientId(0),
mClientLen(0),
mServerId(0),
mServerLen(0),
mLaunchServerThread(0) {
}

MSServer::~MSServer() {
    delete mLaunchServerThread;
}

void MSServer::ShutdownServer() {
    
}

void MSServer::LaunchServer() {
    pthread_create(&mLaunchServerThread, NULL, LaunchServerThreadBridge, (pVoid)this);
}
