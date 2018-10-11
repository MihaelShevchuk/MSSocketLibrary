//
//  MSNetServer.cpp
//  MSSocketLibrary
//
//  Created by Mihail Shevchuk on 16.01.18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#include "MSNetServer.hpp"

MSNetServer::MSNetServer(uint32_t port, uint32_t sizeBuffer): MSServer(port, sizeBuffer) {
     memset(&mServerAddress, '0', sizeof(mServerAddress));
}

void MSNetServer::CreateServer() {
    int opt = 1;
    mServerId = socket(AF_INET, SOCK_STREAM, 0);
    if (mServerId < 0) {
        GenerateEvent(NOT_SETUP);
        return;
    }
    if (int k = setsockopt(mServerId, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        GenerateEvent(NOT_SETUP);
        return;
    }
    if (int k = setsockopt(mServerId, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt))) {
        GenerateEvent(NOT_SETUP);
        return;
    }
    
    memset((pChar)&mServerAddress, 0, sizeof(mServerAddress));
    mServerAddress.sin_family = AF_INET;
    mServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    mServerAddress.sin_port = htons(mPort);
    
    if (bind(mServerId, (struct sockaddr *)&mServerAddress, sizeof(mServerAddress))) {
        GenerateEvent(NOT_SETUP);
        return;
    }
    if (listen(mServerId, 3) < 0) {
        GenerateEvent(NOT_SETUP);
        return;
    }
        printf("Ser-Cr\n");
}

bool MSNetServer::AcceptServer() {
    if ((mSocketId = accept(mServerId, (struct sockaddr *)&mServerAddress, (socklen_t *)&mServerAddress)) < 0) {
        GenerateEvent(IS_DISCONNECT);
        return false;
    } else {
        GenerateEvent(IS_CONNECT);
        CreateReadDataThread();
            printf("Ser-Cr\n");
        return true;
    }
}

void MSNetServer::ReceiveMessage(pVoid message, size_t size) {
}
