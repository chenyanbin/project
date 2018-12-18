//
//  HomeHeroManager.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/20.
//
//

#include "HomeHeroManager.h"
#include "../../../module/battle/data/MapDataManager.h"
HomeHeroManager* HomeHeroManager::_instance = NULL;
HomeHeroManager::HomeHeroManager()
:_heroList(NULL)
,_mapWidth(0)
,_mapHeight(0)
{
    _heroList = new __Set();
}
HomeHeroManager::~HomeHeroManager()
{
    CC_SAFE_DELETE(_heroList);
    _heroList = NULL;
}
void HomeHeroManager::clear()
{
    _heroList->removeAllObjects();
}
HomeHeroManager* HomeHeroManager::getInstance()
{
    if(!_instance)
    {
        _instance = new HomeHeroManager();
    }
    return _instance;
}
void HomeHeroManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}
void HomeHeroManager::addHero(Hero* hero)
{
   
    _heroList->addObject(hero);
    
}

void HomeHeroManager::updateHeroList(float dt)
{
    int rand = 0;
    Point direction;
    long long nowTime = TimeUtil::getNativeTime();
    for(__SetIterator it = this->_heroList->begin(); it != _heroList->end();  it++ )
    {
        Hero* hero = (Hero*)*it;
        hero->updatePositon(dt);
        
        float posX = MIN(_mapWidth - hero->_centerToSide,MAX(hero->_centerToSide,hero->_destinatsionPostion.x));
        float posY = MIN(_mapHeight - hero->_centerToBottom,MAX(hero->_centerToBottom,hero->_destinatsionPostion.y));
        hero->setPosition(posX,posY);
        hero->setZOrder(10000 - posY);
        
        if(nowTime < hero->_nextDecisionTime )
        {
//            if(hero->getActionState() == kActionStateWalk)
//            {
//                direction = MapDataManager::getInstance()->getAvatarWalkDirection(hero, hero->isLeft);
//                if(direction != Point::ZERO)
//                {
//                    hero->walkWithDirection(direction, true);
//                }
//            }
            continue;
        }
        rand = PublicShowUI::genRandom(0, 5);
        if(rand == 0)
        {
            direction = Point(0,1);
        }
        else if(rand == 1)
        {
            direction = Point(1,0);
        }
        else if(rand == 2)
        {
            direction = Point(0,1);
        }
        else if(rand == 3)
        {
            direction = Point(0,-1);
        }
        else if(rand == 4)
        {
            direction = Point(-1,0);
        }
        else
        {
            direction.x = 0;
            direction.y = 0;
        }
        if(direction != Point::ZERO)
        {
            hero->walkWithDirection(direction, true);
        }
        else
        {
            hero->idle();
            hero->_velocity = Point::ZERO;
        }
        hero->_nextDecisionTime =   nowTime + PublicShowUI::genRandom(100, 3000);
    }

}