//
//  LineupListDataManger.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/23.
//
//

#include "LineupListDataManger.h"
LineupListDataManger* LineupListDataManger::_instance = NULL;

LineupListDataManger::LineupListDataManger()
:heroList(NULL)
{
    heroList=new Vector<LineupListData*>();
    
}
LineupListDataManger::~ LineupListDataManger()
{
    heroList->clear();
    CC_SAFE_DELETE(heroList);
    heroList = NULL;
}
LineupListDataManger* LineupListDataManger::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new LineupListDataManger();
    }
    return _instance;
}
void LineupListDataManger::addData(LineupListData* data)
{
    heroList->pushBack(data);
}

void LineupListDataManger::clearheroList()
{
    this->heroList->clear();
}
void LineupListDataManger::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}

