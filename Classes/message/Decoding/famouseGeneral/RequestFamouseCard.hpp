//
//  RequestFamouseCard.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/2/1.
//请求扫荡令
//

#ifndef RequestFamouseCard_hpp
#define RequestFamouseCard_hpp

#include "../MessageSendI.h"
class RequestFamouseCard:public MessageSendI
{
public:
    RequestFamouseCard();
    ~RequestFamouseCard();
    ByteStream *encodingData();
private:

    
};

#endif /* RequestFamouseCard_hpp */
