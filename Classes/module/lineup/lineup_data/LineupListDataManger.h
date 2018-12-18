//
//  LineupListDataManger.h
//  FightPass
//
//  Created by chenyanbin on 15/9/23.
//
//

#ifndef __FightPass__LineupListDataManger__
#define __FightPass__LineupListDataManger__

#include "cocos2d.h"
USING_NS_CC;
#include "LineupListData.h"
class LineupListDataManger
{
public:
    LineupListDataManger();
    ~ LineupListDataManger();
    static void destroyInstance();
    static LineupListDataManger* getInstance();
    void addData(LineupListData* data);
    void removeData(int _heroId);
    
    int getIndexByCardID(int _heroId);
    Vector<LineupListData*>* heroList;
    
    void clearheroList();
    
private:
    
    static LineupListDataManger* _instance;
};


#endif /* defined(__FightPass__LineupListDataManger__) */
