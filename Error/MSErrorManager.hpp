//
//  MSErrorManager.hpp
//  MSSocket
//
//  Created by Taras on 1/16/18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#ifndef MSErrorManager_hpp
#define MSErrorManager_hpp

#include "MSTypes.h"

struct MSErrorMessage {
    uint32_t PortFrom;
    int ErrorNumber;
};



class MSErrorManager {
public:
    MSErrorManager(uint32_t port);
    MSErrorManager(pChar path);
    
    ~MSErrorManager();

    void SetCallback(pFuncCallBack callback, pVoid manager) {
        mCallbackManager = manager;
        mErrorMessageCallback = callback;
    }
    
    void ThrowLocalEvent(MSEvent event);
    void ThrowNetworkEvent(MSEvent event);
    
private:
    pChar mPath;
    uint32_t mPort;
    
    pFuncCallBack mErrorMessageCallback;
    pVoid mCallbackManager;
    
    MSErrorMessage *mMessage;
};
#endif /* ErrorManager_hpp */

