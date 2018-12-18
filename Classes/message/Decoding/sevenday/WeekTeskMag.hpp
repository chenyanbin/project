//
//  WeekTeskMag.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/15.
//
//

#ifndef WeekTeskMag_hpp
#define WeekTeskMag_hpp

#include "../MessageSendI.h"
class WeekTeskMag:public MessageSendI
{
public:
    WeekTeskMag(int day,int teskTag);
    ~ WeekTeskMag();
    ByteStream *encodingData();
private:
    int m_day;
    int m_teskTag;
    
};
#endif /* WeekTeskMag_hpp */
