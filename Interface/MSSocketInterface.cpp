//
//  MSSocketInterface.cpp
//  MSSocket
//
//  Created by Mihail Shevchuk on 15.01.18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#include "MSSocketInterface.hpp"
#include <MSNetSocket.hpp>
#include <MSLocalSocket.hpp>
#include <MSNetServer.hpp>
#include <MSLocalServer.hpp>

//--------------------------------- SOCKETS ------------------------------------

void MSSocketInterface::CreateLocalSocket(pChar serverPath, uint32_t sizeBuffer, pFuncCallBack callback, pVoid manager) {
    MSSocket *socket = new MSLocalSocket(serverPath, sizeBuffer);
    socket->SetReceiveMessageCallback(callback, manager);
    mUseMaps.socketsMaps.createMaps.localMap[serverPath] = socket;
}

void MSSocketInterface::CreateNetworkSocket(pChar ip, uint32_t port, uint32_t sizeBuffer, pFuncCallBack callback, pVoid manager) {
    MSSocket *socket = new MSNetSocket(ip, port, sizeBuffer);
    socket->SetReceiveMessageCallback(callback, manager);
    mUseMaps.socketsMaps.createMaps.networMap[port] = socket;
}

void MSSocketInterface::ConnectAllSockets() {
    ConnectAllLocalSockets();
    ConnectAllNetworkSockets();
}

void MSSocketInterface::ConnectAllNetworkSockets() {
    for (auto obj:mUseMaps.socketsMaps.createMaps.networMap) {
        if (mUseMaps.socketsMaps.launchMaps.networkMap.find(obj.first)->second == false) {
            mUseMaps.socketsMaps.launchMaps.networkMap[obj.first] = obj.second->Connect();
        }
    }
}

void MSSocketInterface::ConnectAllLocalSockets() {
    for (auto obj:mUseMaps.socketsMaps.createMaps.localMap) {
        if (mUseMaps.socketsMaps.launchMaps.localMap.find(obj.first)->second == false) {
            mUseMaps.socketsMaps.launchMaps.localMap[obj.first] = obj.second->Connect();
        }
    }
}

void MSSocketInterface::ConnectSocket(uint32_t port) {
    for (auto obj:mUseMaps.socketsMaps.createMaps.networMap) {
        if (obj.first == port) {
            if (mUseMaps.socketsMaps.launchMaps.networkMap.find(obj.first)->second == false) {
                mUseMaps.socketsMaps.launchMaps.networkMap[obj.first] = obj.second->Connect();
            } else {
//                obj.second->GenerateEvent(ALREADY_CONNECT);
            }
        }
    }
}

void MSSocketInterface::ConnectSocket(pChar serverPath) {
    for (auto obj:mUseMaps.socketsMaps.createMaps.localMap) {
        if (obj.first == serverPath) {
            if (mUseMaps.socketsMaps.launchMaps.localMap.find(obj.first)->second == false) {
                mUseMaps.socketsMaps.launchMaps.localMap[obj.first] = obj.second->Connect();
            } else {
//                obj.second->GenerateEvent(ALREADY_CONNECT);
            }
        }
    }
}

void MSSocketInterface::DisconnectAllSockets() {
    DisconnectAllLocalSockets();
    DisconnectAllNetworkSocekts();
}   

void MSSocketInterface::DisconnectAllNetworkSocekts() {
    for (auto obj:mUseMaps.socketsMaps.createMaps.networMap) {
        if (mUseMaps.socketsMaps.launchMaps.networkMap.find(obj.first)->second == true) {
            mUseMaps.socketsMaps.launchMaps.networkMap[obj.first] = obj.second->Disconnect();
        }
    }
}

void MSSocketInterface::DisconnectAllLocalSockets() {
    for (auto obj:mUseMaps.socketsMaps.createMaps.localMap) {
        if (mUseMaps.socketsMaps.launchMaps.localMap.find(obj.first)->second == true) {
            mUseMaps.socketsMaps.launchMaps.localMap[obj.first] = obj.second->Disconnect();
        }
    }
}

void MSSocketInterface::DisconnectSocket(uint32_t port) {
    for (auto obj:mUseMaps.socketsMaps.createMaps.networMap) {
        if (mUseMaps.socketsMaps.launchMaps.networkMap.find(obj.first)->second == true) {
            mUseMaps.socketsMaps.launchMaps.networkMap[obj.first] = obj.second->Disconnect();
        } else {
//             obj.second->GenerateEvent(ALREADY_DISCONNECT);
        }
    }
}

void MSSocketInterface::DisconnectSocket(pChar serverPath) {
    for (auto obj:mUseMaps.socketsMaps.createMaps.localMap) {
        if (mUseMaps.socketsMaps.launchMaps.localMap.find(obj.first)->second == true) {
            mUseMaps.socketsMaps.launchMaps.localMap[obj.first] = obj.second->Disconnect();
        } else {
//             obj.second->GenerateEvent(ALREADY_DISCONNECT);
        }
    }
}

//--------------------------------- SERVERS ------------------------------------
void MSSocketInterface::CreateNetworkServer(uint32_t port, uint32_t sizeBuffer, pFuncCallBack callback, pVoid manager) {
    MSServer *server = new MSNetServer(port, sizeBuffer);
    server->SetReceiveMessageCallback(callback, manager);
     server->CreateServer();
    mUseMaps.serversMaps.createMaps.networkMap[port] = server;
}

void MSSocketInterface::CreateLocalServer(pChar serverPath, uint32_t sizeBuffer, pFuncCallBack callback, pVoid manager) {
    MSServer *server = new MSLocalServer(serverPath, sizeBuffer);
    server->SetReceiveMessageCallback(callback, manager);
    server->CreateServer();
    mUseMaps.serversMaps.createMaps.localMap[serverPath] = server;
}

void MSSocketInterface::LaunchAllServers() {
    LaunchAllLocalServers();
    LaunchAllNetworkServers();
}

void MSSocketInterface::LaunchAllNetworkServers() {
    for (auto obj:mUseMaps.serversMaps.createMaps.networkMap) {
        if (mUseMaps.serversMaps.launchMaps.networkMap.find(obj.first)->second == false) {
            // TODO: status
            obj.second->LaunchServer();
        }
    }
}

void MSSocketInterface::LaunchAllLocalServers() {
    for (auto obj:mUseMaps.serversMaps.createMaps.localMap) {
        if (mUseMaps.serversMaps.launchMaps.localMap.find(obj.first)->second == false) {
            // TODO: status
            obj.second->LaunchServer();
        }
    }
}

void MSSocketInterface::LaunchServer(uint32_t port) {
    for (auto obj:mUseMaps.serversMaps.createMaps.networkMap) {
        if (obj.first == port) {
            // TODO: status
            obj.second->LaunchServer();
        } 
    }
}

void MSSocketInterface::LaunchServer(pChar serverPath) {
    for (auto obj:mUseMaps.serversMaps.createMaps.localMap) {
        if (obj.first == serverPath) {
            // TODO: status
            obj.second->LaunchServer();
        }
    }
}

void MSSocketInterface::ShutdownAllServers() {
    ShutdownAllLocalServers();
    ShutdownAllNetworkServers();
}

void MSSocketInterface::ShutdownAllNetworkServers() {
    for (auto obj:mUseMaps.serversMaps.createMaps.networkMap) {
        if (mUseMaps.serversMaps.launchMaps.networkMap.find(obj.first)->second == true) {
            mUseMaps.serversMaps.launchMaps.networkMap[obj.first] = obj.second->Disconnect();
        }
    }
}

void MSSocketInterface::ShutdownAllLocalServers() {
    for (auto obj:mUseMaps.serversMaps.createMaps.localMap) {
        if (mUseMaps.serversMaps.launchMaps.localMap.find(obj.first)->second == true) {
            mUseMaps.serversMaps.launchMaps.localMap[obj.first] = obj.second->Disconnect();
        }
    }
}

void MSSocketInterface::ShutdownServer(pChar serverPath) {
    for (auto obj:mUseMaps.serversMaps.createMaps.localMap) {
        if (obj.first == serverPath) {
           mUseMaps.serversMaps.launchMaps.localMap[obj.first] = obj.second->Disconnect();
        }
    }
}

void MSSocketInterface::ShutdownServer(uint32_t port) {
    for (auto obj:mUseMaps.serversMaps.createMaps.networkMap) {
        if (obj.first == port) {
            mUseMaps.serversMaps.launchMaps.networkMap[obj.first] = obj.second->Disconnect();
        }
    }
}
//------------------------------------------------------------------------------

void MSSocketInterface::SendMessage(uint32_t port, pVoid message, size_t size) {
    for (auto obj:mUseMaps.socketsMaps.createMaps.networMap) {
        if (obj.first == port) {
            if (mUseMaps.socketsMaps.launchMaps.networkMap.find(obj.first)->second == true) {
                obj.second->SendMessage(message, size);
            } else {
//                obj.second->GenerateEvent(NOT_CONNECT);
            }
        }
    }
}

void MSSocketInterface::SendMessage(pChar serverPath, pVoid message, size_t size) {
    for (auto obj:mUseMaps.socketsMaps.createMaps.localMap) {
        if (obj.first == serverPath) {
            if (mUseMaps.socketsMaps.launchMaps.localMap.find(obj.first)->second == true) {
                obj.second->SendMessage(message, size);
            } else {
//                obj.second->GenerateEvent(NOT_CONNECT);
            }
        }
    }
}


