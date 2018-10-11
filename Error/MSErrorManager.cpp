//
//  MSErrorManager.cpp
//  MSSocket
//
//  Created by Taras on 1/16/18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#include "MSErrorManager.hpp"

MSErrorManager::MSErrorManager(uint32_t port):
mErrorMessageCallback(NULL),
mCallbackManager(NULL),
mPort(port),
mPath(NULL) {
    mMessage = new MSErrorMessage();
}

MSErrorManager::MSErrorManager(pChar path):
mErrorMessageCallback(NULL),
mCallbackManager(NULL),
mPort(0),
mPath(path) {
    mMessage = new MSErrorMessage();
}

MSErrorManager::~MSErrorManager() {
    delete mMessage;
}

void MSErrorManager::ThrowLocalEvent(MSEvent event) {
    printf("%d", (int)event);
}

void MSErrorManager::ThrowNetworkEvent(MSEvent event) {
    
}

//void MSErrorManager::ThrowError(MSEvent error) {
//    mMessage->PortFrom = mPort;
//    mMessage->ErrorNumber = (int)error;
//
//    mErrorMessageCallback(mMessage, sizeof(MSErrorMessage), mCallbackManager);
//}

