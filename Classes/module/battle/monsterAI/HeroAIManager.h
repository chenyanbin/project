//
//  HeroAIManager.h
//  FightPass
//
//  Created by zhangxiaobin on 15/6/26.
//
//

#ifndef __FightPass__HeroAIManager__
#define __FightPass__HeroAIManager__
#include "cocos2d.h"
USING_NS_CC;
#include "../../../avatar/monster/Monster.h"
#include "../../../avatar/hero/Hero.h"
#include "../..//../VisibleRect.h"
class HeroAIManager
{
public:
    static HeroAIManager* getInstance();
    static void destroyInstance();
    void setObjectList(Vector<Avatar*>* monsterList,Vector<Hero*>* heroList);
    void setMainHero(Hero* hero);
    void setMapLayer(TMXTiledMap* map);
    inline Avatar* getEnemy(Hero* hero);
    Avatar* getNearyEnemy(Avatar* hero);//得到最近的一个怪
public:
    void updateHero(double nowtime,float dt);
private:
    
    inline void followeMainHero(Hero* hero,float distance);//跟随主将
    inline void onHeroAttack(Hero* hero,Avatar* target);//英雄攻击
    inline int heroIsCloseIn(Hero* hero);//是否被包围
    inline bool frontIsHasEnemy(Avatar* monster);//前方1格内是否有怪
    inline void updateMainHero(float dt,Avatar* monster);
    inline void heroRun(Hero* hero,bool isLeft);
    inline int getSkillID(Hero* hero);
    inline int getAttackDelayTime(Hero* target);//得到等待时间
   
    inline void onSummonHeroGuard(Hero* hero,float distance);

    inline void onDelayState(Hero* monster,Avatar* ememy);//等待状态
    inline AttackDelayState getDelayStateFlag(Hero* mosnter);//随机怪物等待状态标志
public:
    float _mapWidth;
    float _mapHeight;
    bool m_heroIsWalkEnd;//是否到头了
    float m_attackRange;//攻击范围
    bool isAutoFight;//是否自动战斗
    
private:
    HeroAIManager();
    ~HeroAIManager();
    static HeroAIManager* _instance;
    TMXTiledMap* m_map;
    Hero* _mainHero;//主将
    Vector<Avatar*>* _monsterList;//怪物列表
    Vector<Hero*>* _heroList;
    double m_nowTime;
};

#endif /* defined(__FightPass__HeroAIManager__) */
