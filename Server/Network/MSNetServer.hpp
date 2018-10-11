//
//  MSNetServer.hpp
//  MSSocketLibrary
//
//  Created by Mihail Shevchuk on 16.01.18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#ifndef MSNetServer_hpp
#define MSNetServer_hpp

#include "MSServer.hpp"

class MSNetServer: public MSServer{
public:
    MSNetServer(uint32_t port, uint32_t sizeBuffer);
    virtual ~MSNetServer() {};

    void CreateServer();
    
private:
    struct sockaddr_in mServerAddress;
    
    bool AcceptServer();
    void ReceiveMessage(pVoid message, size_t size);
};

#endif /* MSNetServer_hpp */
