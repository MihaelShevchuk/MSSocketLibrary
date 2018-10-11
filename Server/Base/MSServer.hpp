//
//  MSServer.hpp
//  MSSocketLibrary
//
//  Created by Mihail Shevchuk on 24.01.18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#ifndef MSServer_hpp
#define MSServer_hpp

#include "MSSocket.hpp"

class MSServer: public MSSocket {
public:
    MSServer(uint32_t port, uint32_t sizeBuffer);
    MSServer(pChar serverPath, uint32_t sizeBuffer);
    virtual ~MSServer();
    
    void LaunchServer();
    void ShutdownServer();
    
    virtual void CreateServer() = 0;
    
protected:
    int mServerId;
    int mClientId;
    
    int mServerLen;
    int mClientLen;

    virtual bool AcceptServer() = 0;
    
private:
    pthread_t mLaunchServerThread;

    void CreateLaunchServerThread();
    void ReceiveMessage(pVoid message, size_t size);
    
    static pVoid LaunchServerThreadBridge(pVoid object) {
        MSServer *server = static_cast<MSServer*>(object);
        server->AcceptServer();
        return 0;
    }
};

#endif /* MSServer_hpp */
