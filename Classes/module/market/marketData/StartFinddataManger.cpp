//
//  StartFinddataManger.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/21.
//
//

#include "StartFinddataManger.h"
StartFinddataManger* StartFinddataManger::_instance = NULL;

StartFinddataManger::StartFinddataManger()
:m_findId(0)
,m_remainingTimes(0)
,m_gold(0)
,m_jungong(0)
,m_xunfangling(0)
{

    
}
StartFinddataManger::~StartFinddataManger()
{
   
}
StartFinddataManger* StartFinddataManger::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new StartFinddataManger();
    }
    return _instance;
}
void StartFinddataManger::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}
void StartFinddataManger::setfindIdData(int findId)
{
    this->m_findId = NULL;
    m_findId = findId;
}
int StartFinddataManger::getfindIdData()
{
    return m_findId;
}
void StartFinddataManger::setRemainingTimesData(int remainingTimes)
{
    
    m_remainingTimes = remainingTimes;
}
int StartFinddataManger::getRemainingTimesData()
{
    return m_remainingTimes;
}
void StartFinddataManger::setjiasugoldData(int remainingTimes){
    
    m_gold = remainingTimes;
}
int StartFinddataManger::getjiasugoldData(){
    return m_gold;
}
void StartFinddataManger::setjungongData(int jungong)
{
    m_jungong = jungong;
}
int StartFinddataManger::getjungongData()
{
    return m_jungong;
}

void StartFinddataManger::setxunfanglingData(int xunfagnling)
{
    
    m_xunfangling = xunfagnling;
}
int StartFinddataManger::getxunfanglingData()
{
    return m_xunfangling;
}