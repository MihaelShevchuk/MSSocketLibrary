//
//  MSEventManager.hpp
//  MSSocketLibrary
//
//  Created by Mihail Shevchuk on 31.01.18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#ifndef MSEventManager_hpp
#define MSEventManager_hpp

#include "MSTypes.h"

class MSEventManager {
public:
    static MSEventManager& Instance() {
        static MSEventManager manager;
        return manager;
    }
    
    void SetMaps(Maps& map) {
        mMap = map;
    }
    
    pFuncThrowEvent GetThrowForEventType();

private:
    MSEventManager() {}
    ~MSEventManager() {}
    
    MSEventManager(MSEventManager const&) = delete;
    MSEventManager& operator= (MSEventManager const&) = delete;
    
    void ReveiveEventMessage(MSEventMessage *message);
    
    Maps mMap;
};

#endif /* MSEventManager_hpp */
