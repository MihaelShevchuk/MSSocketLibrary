//
//  MSSocket.cpp
//  MSSocketLibrary
//
//  Created by Mihail Shevchuk on 15.01.18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#include "MSSocket.hpp"

MSSocket::MSSocket(MSEventType type, pChar ip, uint32_t port, uint32_t sizeBuffer):
mType(type),
mSizeForRead(sizeBuffer),
mSocketId(0),
mPort(port),
mIp(ip),
mServerPath(NULL),
mReceiveMessageManager(NULL),
mReceiveMessageCallback(NULL),
mEventManager(NULL),
mGenerateEventCallback(NULL),
mReadDataThread(0){
    mReadDataBuffer = new char[mSizeForRead]();
}

MSSocket::MSSocket(MSEventType type, pChar serverPath, uint32_t sizeBuffer):
mType(type),
mSizeForRead(sizeBuffer),
mSocketId(0),
mServerPath(serverPath),
mPort(0),
mIp(NULL),
mReceiveMessageManager(NULL),
mReceiveMessageCallback(NULL),
mEventManager(NULL),
mGenerateEventCallback(NULL),
mReadDataThread(0){
    mReadDataBuffer = new char[mSizeForRead]();
}

MSSocket::~MSSocket() {
    mServerPath = NULL;
    mReceiveMessageManager = NULL;
    mReceiveMessageCallback = NULL;
    mEventManager = NULL;
    mGenerateEventCallback = NULL;
    delete mReadDataThread;
    delete [] mReadDataBuffer;
}

bool MSSocket::Disconnect() {
    close(mSocketId);
    mSocketId = 0;
    pthread_join(mReadDataThread, NULL);
    return false;
}

void MSSocket::CreateReadDataThread() {
    pthread_create(&mReadDataThread, NULL, ThreadBridge, (pVoid)this);
}

bool MSSocket::SendMessage(pVoid message, size_t size) {
    size_t sendSize = send(mSocketId, message, size, 0);
    if (sendSize == 0) {
        GenerateEvent(NOT_SEND);
        return false;
    }
    return true;
}

void MSSocket::ReadData() {
    while (mSocketId > 0) {
        size_t valread = read(mSocketId, mReadDataBuffer, mSizeForRead);
        if (valread == 0) {
            GenerateEvent(IS_DISCONNECT);
        } else {
            mReceiveMessageCallback(mReadDataBuffer, valread, mReceiveMessageManager);
        }
    }
}

void MSSocket::GenerateEvent(MSEvent event) {
    MSEventMessage *message = new MSEventMessage(mType, event, mPort, mServerPath);
    mGenerateEventCallback(message, mEventManager);
}

bool MSSocket::Connect() {
    return false;
}

void MSSocket::CreateSocket() {
}

