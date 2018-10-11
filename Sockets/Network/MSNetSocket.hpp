//
//  MSNetSocket.hpp
//  MSSocket
//
//  Created by Mihail Shevchuk on 15.01.18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#ifndef MSNetSocket_hpp
#define MSNetSocket_hpp

#include "MSSocket.hpp"

class MSNetSocket: public MSSocket {
public:
    MSNetSocket(pChar ip, uint32_t port, uint32_t sizeBuffer);
    virtual ~MSNetSocket() {};
    
    bool Connect();
    
    inline void GenerateEvent(MSEvent event) {
//        mErrorManager->ThrowNetworkEvent(event);
    }
    
private:
    struct sockaddr_in mServerAdress;
    
    void CreateSocket();
    void ReceiveMessage(pVoid message, size_t size);
};

#endif /* MSNetSocket_hpp */
