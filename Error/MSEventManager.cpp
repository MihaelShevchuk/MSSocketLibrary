//
//  MSEventManager.cpp
//  MSSocketLibrary
//
//  Created by Mihail Shevchuk on 31.01.18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#include "MSEventManager.hpp"


pFuncThrowEvent MSEventManager::GetThrowForEventType() {
    auto mFunc = [](MSEventMessage* message, pVoid eventManager) {
        MSEventManager *manager = (MSEventManager *)eventManager;
        manager->ReveiveEventMessage((MSEventMessage*)message);
    };
    return mFunc;
}

void MSEventManager::ReveiveEventMessage(MSEventMessage *message) {
    switch (message->type) {
        case LOCAL_SOCKET: {                                                                                                                                                                                                                                                                                                                                                                              
            for (auto obj:mMap.socketsMaps.launchMaps.localMap) {
                if (obj.first == message->serverPath) {
                    if (message->event == NOT_SETUP || message->event == NOT_READ || message->event == NOT_SEND || message->event == IS_DISCONNECT) {
                        mMap.socketsMaps.launchMaps.localMap[obj.first] = false;
                    }
                }
            }
        } break;
        case LOCAL_SERVER: {
            for (auto obj:mMap.serversMaps.launchMaps.localMap) {
                if (obj.first == message->serverPath) {
                    if (message->event == NOT_SETUP || message->event == NOT_READ || message->event == NOT_SEND || message->event == IS_DISCONNECT) {
                        mMap.serversMaps.launchMaps.localMap[obj.first] = false;
                    } else if (message->event == IS_CONNECT) {
                        mMap.serversMaps.launchMaps.localMap[obj.first] = true;
                    }
                }
            }
        } break;
        case NETWORK_SOCKET: {
            for (auto obj:mMap.socketsMaps.launchMaps.networkMap) {
                if (obj.first == message->port) {
                    if (message->event == NOT_SETUP || message->event == NOT_READ || message->event == NOT_SEND || message->event == IS_DISCONNECT) {
                        mMap.socketsMaps.launchMaps.networkMap[obj.first] = false;
                    } else if (message->event == IS_CONNECT) {
                        mMap.socketsMaps.launchMaps.networkMap[obj.first] = true;
                    }
                }
            }
        } break;
        case NETWORK_SERVER: {
            for (auto obj:mMap.serversMaps.launchMaps.networkMap) {
                if (obj.first == message->port) {
                    if (message->event == NOT_SETUP || message->event == NOT_READ || message->event == NOT_SEND || message->event == IS_DISCONNECT) {
                        mMap.serversMaps.launchMaps.networkMap[obj.first] = false;
                    }
                }
            }
        } break;
        
        default:
            break;
    }
}
