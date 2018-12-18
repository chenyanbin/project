//
//  LineupPageDataManger.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/29.
//
//

#include "LineupPageDataManger.h"
LineupPageDataManger* LineupPageDataManger::_instance = NULL;

LineupPageDataManger::LineupPageDataManger()
:pageHero(NULL)
,karmaList(NULL)
{
    pageHero = new Vector<LineupPageData*>();
    karmaList = new Vector<LineupPageData*>();
    
}
LineupPageDataManger::~ LineupPageDataManger()
{
    pageHero->clear();
    CC_SAFE_DELETE(pageHero);
    pageHero = NULL;
    
    karmaList->clear();
    CC_SAFE_DELETE(karmaList);
    karmaList = NULL;
}
LineupPageDataManger* LineupPageDataManger::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new LineupPageDataManger();
    }
    return _instance;
}
void LineupPageDataManger::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}
void LineupPageDataManger::addData(LineupPageData* data)
{
    pageHero->pushBack(data);
}
Vector<LineupPageData*>* LineupPageDataManger::getpageHero()
{
    return this->pageHero;
}
LineupPageData* LineupPageDataManger::getCardDataByIndex(int index)
{
    if(index < 0 || index >= this->pageHero->size())
    {
        return NULL;
    }
    return this->pageHero->at(index);
}
void LineupPageDataManger::clearPagelist()
{
    this->pageHero->clear();
}


void LineupPageDataManger::addKarmaData(LineupPageData* data)
{
    karmaList->pushBack(data);
}
Vector<LineupPageData*>* LineupPageDataManger::getKarmaData()
{
    return this->karmaList;
}
LineupPageData* LineupPageDataManger::getKarmaDataByIndex(int index)
{
    if(index < 0 || index >= this->karmaList->size())
    {
        return NULL;
    }
    return this->karmaList->at(index);
}
void LineupPageDataManger::clearKarmaData()
{
    this->karmaList->clear();

}