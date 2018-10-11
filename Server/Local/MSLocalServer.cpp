//
//  MSLocalServer.cpp
//  MSSocketLibrary
//
//  Created by Mihail Shevchuk on 16.01.18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#include "MSLocalServer.hpp"

MSLocalServer::MSLocalServer(pChar serverPath, uint32_t sizeBuffer): MSServer(serverPath, sizeBuffer) {
    memset(&mServerAddress, '0', sizeof(mServerAddress));
    memset(&mClientAddress, '0', sizeof(mClientAddress));
}

void MSLocalServer::CreateServer() {
    int opt = 1;
    mServerId = socket(AF_UNIX, SOCK_STREAM, 0);
    
    if (mServerId < 0) {
        GenerateEvent(NOT_SETUP);
        return;
    }
    if (int k = setsockopt(mServerId, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        GenerateEvent(NOT_SETUP);
        return;
    }
    
    memset((pChar)&mServerAddress, 0, sizeof(mServerAddress));
    mServerAddress.sun_family = AF_UNIX;
    strcpy(mServerAddress.sun_path, mServerPath);
    mServerLen = sizeof(mServerAddress);
    
    unlink(mServerPath);
    
    if (bind(mServerId, (struct sockaddr *)&mServerAddress, mServerLen)) {
        GenerateEvent(NOT_SETUP);
        return;
    }
    if (listen(mServerId, 5) < 0) {
        GenerateEvent(NOT_SETUP);
        return;
    }
    printf("Ser-Cr\n");
}

bool MSLocalServer::AcceptServer() {
    printf("Ser-SAC\n");
    if ((mClientId = accept(mServerId, (struct sockaddr *)&mClientAddress, (socklen_t *)&mClientLen)) < 0) {
        GenerateEvent(IS_DISCONNECT);
        return false;
    } else {
        printf("Ser-C\n");
        GenerateEvent(IS_CONNECT);
        CreateReadDataThread();
        return true;
    }
}

void MSLocalServer::ReceiveMessage(pVoid message, size_t size) {
    
}
