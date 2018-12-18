//
//  LineupPageDataManger.h
//  FightPass
//
//  Created by chenyanbin on 15/9/29.
//
//

#ifndef __FightPass__LineupPageDataManger__
#define __FightPass__LineupPageDataManger__

#include "cocos2d.h"
USING_NS_CC;
#include "LineupPageData.h"
class LineupPageDataManger
{
public:
    LineupPageDataManger();
    ~ LineupPageDataManger();
    static void destroyInstance();
    static LineupPageDataManger* getInstance();
    
    void addData(LineupPageData* data);
    Vector<LineupPageData*>* getpageHero();
    LineupPageData* getCardDataByIndex(int index);
    void clearPagelist();
    
    void addKarmaData(LineupPageData* data);
    Vector<LineupPageData*>* getKarmaData();
    LineupPageData* getKarmaDataByIndex(int index);
    void clearKarmaData();
    
private:
    Vector<LineupPageData*>* pageHero;//英雄属性
    
    Vector<LineupPageData*>* karmaList;//缘分
    static LineupPageDataManger* _instance;
};


#endif /* defined(__FightPass__LineupPageDataManger__) */
