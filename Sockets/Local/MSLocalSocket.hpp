//
//  MSLocalSocket.hpp
//  MSSocket
//
//  Created by Mihail Shevchuk on 15.01.18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#ifndef MSLocalSocket_hpp
#define MSLocalSocket_hpp

#include "MSSocket.hpp"

class MSLocalSocket: public MSSocket {
public:
    MSLocalSocket(pChar serverPath, uint32_t sizeBuffer);
    virtual ~MSLocalSocket() {};
    
    bool Connect();
    
    inline void GenerateEvent(MSEvent event) {
//        mErrorManager->ThrowLocalEvent(event);
    }

private:
    sockaddr_un mServerAdress;

    void CreateSocket();
    void ReceiveMessage(pVoid message, size_t size);
};

#endif /* MSLocalSocket_hpp */
