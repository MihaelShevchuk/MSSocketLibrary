//
//  MSLocalServer.hpp
//  MSSocketLibrary
//
//  Created by Mihail Shevchuk on 16.01.18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#ifndef MSLocalServer_hpp
#define MSLocalServer_hpp

#include "MSServer.hpp"

class MSLocalServer: public MSServer {
public:
    MSLocalServer(pChar serverPath, uint32_t sizeBuffer);
    virtual ~MSLocalServer() {};
    
    void CreateServer();
    
private:
    struct sockaddr_un mServerAddress;
    struct sockaddr_un mClientAddress;
    
    bool AcceptServer();
    void ReceiveMessage(pVoid message, size_t size);
};

#endif /* MSLocalServer_hpp */
