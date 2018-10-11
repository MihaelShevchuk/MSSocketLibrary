//
//  MSNetSocket.cpp
//  MSSocket
//
//  Created by Mihail Shevchuk on 15.01.18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#include "MSNetSocket.hpp"

MSNetSocket::MSNetSocket(pChar ip, uint32_t port, uint32_t sizeBuffer):
MSSocket(MSEventType::NETWORK_SOCKET, ip, port, sizeBuffer) {
    memset(&mServerAdress, '0', sizeof(mServerAdress));
}

void MSNetSocket::CreateSocket() {
    if ((mSocketId = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        GenerateEvent(NOT_SETUP);
    } else {
        mServerAdress.sin_family = AF_INET;
        mServerAdress.sin_port = htons(mPort);
        
        if(inet_pton(AF_INET, mIp, &mServerAdress.sin_addr) <= 0) {
            GenerateEvent(NOT_SETUP);
        }
    }
}

bool MSNetSocket::Connect() {
    CreateSocket();
    if ((connect(mSocketId, (struct sockaddr *)&mServerAdress, sizeof(mServerAdress))) < 0) {
        GenerateEvent(IS_DISCONNECT);
        return false;
    } else {
        CreateReadDataThread();
            printf("Sok-C\n");
        return true;
    }
}
