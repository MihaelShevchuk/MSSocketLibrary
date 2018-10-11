//
//  MSLocalSocket.cpp
//  MSSocket
//
//  Created by Mihail Shevchuk on 15.01.18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#include "MSLocalSocket.hpp"

MSLocalSocket::MSLocalSocket(pChar serverPath, uint32_t sizeBuffer):
MSSocket(MSEventType::LOCAL_SOCKET, serverPath, sizeBuffer) {
    memset(&mServerAdress, '0', sizeof(mServerAdress));
}

void MSLocalSocket::CreateSocket() {
    if ((mSocketId = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        GenerateEvent(NOT_SETUP);
        printf("%s, %d\n", "Soc", mSocketId);
    } else {
        mServerAdress.sun_family = AF_UNIX;
        strcpy(mServerAdress.sun_path, mServerPath);
        printf("%s, %s\n", "Soc", mServerPath);
    }
}

bool MSLocalSocket::Connect() {
    CreateSocket();
    if ((connect(mSocketId, (sockaddr*)&mServerAdress, sizeof(mServerAdress))) < 0) {
        GenerateEvent(IS_DISCONNECT);
        return false;
    } else {
        printf("Soc-C");
        CreateReadDataThread();
        return true;
    }
}
