//
//  ReruitTpyeMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/1/11.
//
//

#ifndef ReruitTpyeMsg_hpp
#define ReruitTpyeMsg_hpp

#include "../MessageSendI.h"
class ReruitTpyeMsg:public MessageSendI
{
public:
    ReruitTpyeMsg(int _countMode);
    ~ ReruitTpyeMsg();
    ByteStream *encodingData();
private:
    int m_countMode;//次数
};

#endif /* ReruitTpyeMsg_hpp */
