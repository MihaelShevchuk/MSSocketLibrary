//
//  MSTypes.h
//  MSSocketLibrary
//
//  Created by Mihail Shevchuk on 25.01.18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#ifndef MSTypes_h
#define MSTypes_h

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <map>

const int MAX_SERVER_PATH_LEN = 30;

class MSSocket;
class MSServer;

enum MSEventType {
    LOCAL_SERVER,
    LOCAL_SOCKET,
    NETWORK_SOCKET,
    NETWORK_SERVER
};

enum MSEvent {
    ALREADY_CONNECT    = 1,
    ALREADY_DISCONNECT = 2,
    ALREADY_LAUNCH     = 3,
    ALREADY_SHUTDOWN   = 4,
    NOT_SETUP          = 6,
    NOT_READ           = 8,
    NOT_SEND           = 9,
    IS_CONNECT         = 11,
    IS_DISCONNECT      = 12
};

struct MSEventMessage {
    MSEventMessage(MSEventType sType,
                   MSEvent sEvent,
                   int sPort,
                   char* sPath) : type(sType), event(sEvent), port(sPort) {
        strcpy(serverPath, sPath);
    }
    MSEventType type;
    MSEvent event;
    int  port;
    char serverPath[MAX_SERVER_PATH_LEN];
};

typedef char* pChar;
typedef void* pVoid;

typedef void (*pFuncThrowEvent)(MSEventMessage*, pVoid);
typedef void (*pFuncCallBack)(void *message, size_t size, void *manager);

struct ServersCreateMaps {
    std::map<uint32_t, MSServer*> networkMap;
    std::map<pChar, MSServer*> localMap;
};

struct SocketsCreateMaps {
    std::map<uint32_t, MSSocket*> networMap;
    std::map<pChar, MSSocket*> localMap;
};

struct LaunchMaps {
    std::map<uint32_t, bool> networkMap;
    std::map<pChar, bool> localMap;
};

struct ServersMaps {
    ServersCreateMaps createMaps;
    LaunchMaps launchMaps;
};

struct SocketsMaps {
    SocketsCreateMaps createMaps;
    LaunchMaps launchMaps;
};

struct Maps {
    SocketsMaps socketsMaps;
    ServersMaps serversMaps;
};

#endif /* MSTypes_h */
