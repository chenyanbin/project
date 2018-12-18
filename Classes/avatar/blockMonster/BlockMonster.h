//
//  BlockMonster.h
//  FightPass
//
//  Created by zhangxiaobin on 15/9/1.
//阻挡怪，不能攻击和移动。只能被击
//

#ifndef __FightPass__BlockMonster__
#define __FightPass__BlockMonster__

#include "../monster/Monster.h"
class BlockMonster:public Monster
{
public:
    BlockMonster();
    ~BlockMonster();
    virtual bool init(int monsterID);
    static BlockMonster* create(int monsterID);
    virtual char* class_name(){return "BlockMonster";};
public:
    void updatePositon(float dt);
    virtual void hurtWithDamage(float damage,bool isCrit,bool isBlock,bool isSkillAttack);//受伤
    virtual void knockDown(float damage,bool isCrit,bool isBlock,bool isSkillAttack);//击倒
    virtual void knockFly(float damage,bool isCrit,bool isBlock,bool isSkillAttack);//击飞
    virtual void knockBack(float damage,Point targetPoint,bool isCrit,bool isBlock,bool isSkillAttack);//击退
    virtual void onBuff(int buffID,double damage);
    
    void idle();
public:
     void updateShadow();
public:
    Point _gridBlockPoint;//阻挡格子点
};

#endif /* defined(__FightPass__BlockMonster__) */
