//
//  RequestRechargePage.hpp
//  FightPass
//充值 页协议
//  Created by zhangxiaobin on 15/10/26.
//
//

#ifndef RequestRechargePage_hpp
#define RequestRechargePage_hpp

#include "../MessageSendI.h"

class RequestRechargePage:public MessageSendI
{
public:
    RequestRechargePage();
    ~RequestRechargePage();
    ByteStream *encodingData();
private:

};

#endif /* RequestRechargePage_hpp */
