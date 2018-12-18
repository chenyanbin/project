//
//  SevendayRedPointDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 16/4/29.
//
//

#include "SevendayRedPointDataManager.hpp"
SevendayRedPointDataManager* SevendayRedPointDataManager::_instance = NULL;

SevendayRedPointDataManager::SevendayRedPointDataManager()
:m_redPoint("0000000000000000000000000000")
{
    
    
}
SevendayRedPointDataManager::~ SevendayRedPointDataManager()
{

}
SevendayRedPointDataManager* SevendayRedPointDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new SevendayRedPointDataManager();
    }
    return _instance;
}
void SevendayRedPointDataManager::addData(const char* data)
{
    m_redPoint = data;
}

void SevendayRedPointDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}


void SevendayRedPointDataManager::setDayPot(Node* target,Point point, int _day )
{
    if (target==NULL) {
        return;
    }
    int status = 0;
    
    char value = '1';
    if (_day == 1) {
        if(m_redPoint[0] == value || m_redPoint[1] == value || m_redPoint[2] == value || m_redPoint[3] == value)
        {
            status = 1;
        }
    }else if (_day == 2)
    {
        if(m_redPoint[4] == value or m_redPoint[5] == value or m_redPoint[6] == value or m_redPoint[7] == value)
        {
            status = 1;
        }
    }
    else if (_day == 3)
    {
        if(m_redPoint[8] == value || m_redPoint[9] == value || m_redPoint[10] == value || m_redPoint[11] == value)
        {
            status = 1;
        }
    }
    else if (_day == 4)
    {
        if(m_redPoint[12] == value || m_redPoint[13] == value || m_redPoint[14] == value || m_redPoint[15] == value)
        {
            status = 1;
        }
    }
    else if (_day == 5)
    {
        if(m_redPoint[16] == value || m_redPoint[17] == value || m_redPoint[18] == value || m_redPoint[19] == value)
        {
            status = 1;
        }
    }
    else if (_day == 6)
    {
        if(m_redPoint[20] == value || m_redPoint[21] == value || m_redPoint[22] == value || m_redPoint[23] == value)
        {
            status = 1;
        }
    }
    else if (_day == 7)
    {
        if(m_redPoint[24] == value || m_redPoint[25] == value || m_redPoint[26] == value || m_redPoint[27] == value)
        {
            status = 1;
        }
    }
    Sprite* dot=(Sprite*)target->getChildByTag(1024);
    if (dot) {
        target->removeChildByTag(1024);
    }
    if (status == 1) {
        Sprite* dotSprite=Sprite::create(IMG_CHAT_REDDOT);
        dotSprite->setAnchorPoint(Point::ZERO);
        dotSprite->setPosition(target->getContentSize().width-dotSprite->getContentSize().width-point.x,target->getContentSize().height-dotSprite->getContentSize().height-point.y);
        target->addChild(dotSprite,10,1024);
        
    }
}
void SevendayRedPointDataManager::setModulePot(Node* target,Point point, int _day,int num)
{
    if (target==NULL) {
        return;
    }
    int status = 0;
    char value = '1';
    int _num = (_day-1)*4 + (num - 1);
    if (m_redPoint[_num] == value) {
        status = 1;
    }
    Sprite* dot=(Sprite*)target->getChildByTag(1024);
    if (dot) {
        target->removeChildByTag(1024);
    }
    if (status == 1) {
        Sprite* dotSprite=Sprite::create(IMG_CHAT_REDDOT);
        dotSprite->setAnchorPoint(Point::ZERO);
        dotSprite->setPosition(target->getContentSize().width-dotSprite->getContentSize().width-point.x,target->getContentSize().height-dotSprite->getContentSize().height-point.y);
        target->addChild(dotSprite,10,1024);
        
    }
}