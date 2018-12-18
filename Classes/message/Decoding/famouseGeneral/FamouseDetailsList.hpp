//
//  FamouseDetailsList.hpp
//  FightPass
//名将传详情列表主页
//  Created by zhangxiaobin on 16/1/25.
//
//

#ifndef FamouseDetailsList_hpp
#define FamouseDetailsList_hpp

#include "../MessageSendI.h"
class FamouseDetailsList:public MessageSendI
{
public:
    FamouseDetailsList();
    ~FamouseDetailsList();
    ByteStream *encodingData();
};

#endif /* FamouseDetailsList_hpp */
