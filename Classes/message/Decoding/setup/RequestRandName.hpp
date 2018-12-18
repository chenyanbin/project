//
//  RequestRandName.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/9.
//
//

#ifndef RequestRandName_hpp
#define RequestRandName_hpp

#include "../MessageSendI.h"
class RequestRandName:public MessageSendI
{
public:
    RequestRandName(int sex);
    ~RequestRandName();
    ByteStream *encodingData();
private:
    int m_sex;//名字哦
};

#endif /* RequestRandName_hpp */
