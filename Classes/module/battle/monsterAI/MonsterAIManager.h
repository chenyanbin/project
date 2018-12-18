//
//  MonsterAIManager.h
//  FightPass
//
//  Created by zhangxiaobin on 15/6/24.
//
//

#ifndef __FightPass__MonsterAIManager__
#define __FightPass__MonsterAIManager__

#include "cocos2d.h"
USING_NS_CC;
#include "../../../avatar/monster/Monster.h"
#include "../../../avatar/hero/Hero.h"

class MonsterAIManager
{
public:
    static MonsterAIManager* getInstance();
    static void destroyInstance();
    void setObjectList(Vector<Avatar*>* monsterList,Vector<Hero*>* heroList);
    void setMainHero(Hero* hero);
    inline Hero* getEnemy(Avatar* monster);
     Hero* getNearyEnemy(Avatar* monster);//得到最近的一个怪
public:
    void updateMonster(double nowtime,float dt);
public:

    float _mapWidth;
    float _mapHeight;
private:
    inline void onMonsterGuard(Avatar* moster,int friendNum,float distance);
    inline void onMonsterEscape(Avatar* moster,int friendNum,float distance,Hero* ememy);
    inline void onMonsterAttack(Avatar* monster,int friendNum,float distance,Hero* ememy);
    inline int getFriendNum(Avatar* monster);
    
    inline bool monsterIsCloseIn(Avatar* monster);//是否被包围 前后方都有英雄
    inline bool frontIsHasEnemy(Avatar* monster);//前方1格内是否有怪
    inline void monsterRun(Avatar* monster,bool isLeft);
    inline int getMonsterSkill(Avatar* monster);
    inline int getAttackDelayTime(Avatar* target);//得到等待时间
    inline void delayToSkill(const std::function<void()>& func,Avatar* Avatar);
 
    inline void onDelayState(Avatar* monster,Avatar* ememy);//等待状态
    inline AttackDelayState getDelayStateFlag(Avatar* mosnter);//随机怪物等待状态标志

private:
    MonsterAIManager();
    ~MonsterAIManager();
    static MonsterAIManager* _instance;
    double m_nowTime;
    float m_attackRange;//攻击范围
    Vector<Avatar*>* _monsterList;//怪物列表
    Vector<Hero*>* _heroList;
    Hero* m_hero;
    Vector<Avatar*>* removeList;
    
};

#endif /* defined(__FightPass__MonsterAIManager__) */
