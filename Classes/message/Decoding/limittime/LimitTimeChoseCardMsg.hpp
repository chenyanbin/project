//
//  LimitTimeChoseCardMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/1/19.
//
//

#ifndef LimitTimeChoseCardMsg_hpp
#define LimitTimeChoseCardMsg_hpp

#include "../MessageSendI.h"
class LimitTimeChoseCardMsg:public MessageSendI
{
public:
    LimitTimeChoseCardMsg(int _cardType);
    ~ LimitTimeChoseCardMsg();
    ByteStream *encodingData();
private:
    int m_cardType;//次数
};


#endif /* LimitTimeChoseCardMsg_hpp */
