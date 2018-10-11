//
//  MSSocket.hpp
//  MSSocketLibrary
//
//  Created by Mihail Shevchuk on 15.01.18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#ifndef MSSocket_hpp
#define MSSocket_hpp

#include "MSErrorManager.hpp"

class MSSocket {
public:
    MSSocket(MSEventType type, pChar ip, uint32_t port, uint32_t sizeBuffer);
    MSSocket(MSEventType type, pChar serverPath, uint32_t sizeBuffer);
    virtual ~MSSocket();

    void SetReceiveMessageCallback(pFuncCallBack callback, pVoid manager) {
        mReceiveMessageCallback = callback;
        mReceiveMessageManager = manager;
    }
    
    void SetGenerateEventCallback(pFuncThrowEvent callback, pVoid manager) {
        mGenerateEventCallback = callback;
        mEventManager = manager;
    }
    
    virtual bool Connect();
    bool Disconnect();
    bool SendMessage(pVoid message, size_t size);
    
protected:
    pVoid mReceiveMessageManager;
    pVoid mEventManager;
    pFuncCallBack mReceiveMessageCallback;
    pFuncThrowEvent mGenerateEventCallback;

    pChar mIp;
    pChar mServerPath;
    uint32_t mPort;
    MSEventType mType;
    
    int mSocketId;
    void CreateReadDataThread();
    void GenerateEvent(MSEvent event);
    virtual void CreateSocket();

private:
    uint32_t mSizeForRead;
    pthread_t mReadDataThread;
    pChar mReadDataBuffer;
    
    void ReadData();
    static void *ThreadBridge(pVoid object) {
        MSSocket *socket =  static_cast<MSSocket*>(object);
        socket->ReadData();
        return 0;
    }
};

#endif /* MSSocket_hpp */
