//
//  MSSocketInterface.hpp
//  MSSocket
//
//  Created by Mihail Shevchuk on 15.01.18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#ifndef MSSocketInterface_hpp
#define MSSocketInterface_hpp

#include "MSTypes.h"

class MSSocketInterface {
public:
    MSSocketInterface() {};
    ~MSSocketInterface() {};
    
//--------------------------------- SOCKETS ------------------------------------
    void CreateNetworkSocket(pChar ip, uint32_t port, uint32_t sizeBuffer, pFuncCallBack callback, pVoid manager);
    void CreateLocalSocket(pChar serverPath, uint32_t sizeBuffer, pFuncCallBack callback, pVoid manager);
    
    void ConnectAllSockets();
    void ConnectAllNetworkSockets();
    void ConnectAllLocalSockets();
    void ConnectSocket(uint32_t port);
    void ConnectSocket(pChar serverPath);
    
    void DisconnectAllSockets();
    void DisconnectAllNetworkSocekts();
    void DisconnectAllLocalSockets();
    void DisconnectSocket(uint32_t port);
    void DisconnectSocket(pChar serverPath);
    
//--------------------------------- SERVERS ------------------------------------
    void CreateNetworkServer(uint32_t port, uint32_t sizeBuffer, pFuncCallBack callback, pVoid manager);
    void CreateLocalServer(pChar serverPath, uint32_t sizeBuffer, pFuncCallBack callback, pVoid manager);
    
    void LaunchAllServers();
    void LaunchAllNetworkServers();
    void LaunchAllLocalServers();
    void LaunchServer(uint32_t port);
    void LaunchServer(pChar serverPath);

    void ShutdownAllServers();
    void ShutdownAllNetworkServers();
    void ShutdownAllLocalServers();
    void ShutdownServer(pChar serverPath);
    void ShutdownServer(uint32_t port);

//------------------------------------------------------------------------------
    void SendMessage(uint32_t port, pVoid message, size_t size);
    void SendMessage(pChar serverPath, pVoid message, size_t size);
    
//private:
    Maps mUseMaps;
};

#endif /* MSSocketInterface_hpp */
