//
//  HomeHeroManager.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/20.
//
//

#ifndef HomeHeroManager_hpp
#define HomeHeroManager_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "../../../avatar/hero/Hero.h"

class HomeHeroManager
{
public:
    static HomeHeroManager* getInstance();
    static void destroyInstance();
    void addHero(Hero* hero);
    void clear();
public:
    void updateHeroList(float dt);
    float _mapWidth;
    float _mapHeight;
private:
    
private:
    HomeHeroManager();
    ~HomeHeroManager();
    static HomeHeroManager* _instance;
    
    __Set* _heroList;
};


#endif /* HomeHeroManager_hpp */
