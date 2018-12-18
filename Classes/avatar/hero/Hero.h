//
//  Hero.h
//  FightPass
//
//  Created by zhangxiaobin on 15/5/24.
//
//

#ifndef __FightPass__Hero__
#define __FightPass__Hero__

#include "../Avatar.h"
#include "../../commonData/dictData/DictHero/DictHeroManager.h"

class Hero:public Avatar
{
public:
    Hero();
    ~Hero();
    bool init(int heroID);
    static Hero* create(int heroID);
    virtual char* class_name(){return "Hero";};
public:
    void updateShadow();
    void idle();
    void dash(float distance,float time = -1);//冲撞的距离
    void walkWithDirection(Point direction,bool isHold);
    void knockFly(float damage,bool isCrit,bool isBlock,bool isSkillAttack);//击飞
    void knockDown(float damage,bool isCrit,bool isBlock,bool isSkillAttack);//击倒
    void knockBack(float damage,Point targetPoint,bool isCrit,bool isBlock,bool isSkillAttack);
    void hurtWithDamage(float damage,bool isCrit,bool isBlock,bool isSkillAttack);
    bool skill1();
    bool skill2();
    bool skill3();
    bool skill4();
    bool attack1();
    bool attack2();
    bool attack3();
    bool attack4();
    bool attack5();
    bool usePassSkill();//使用被动技能
    void updatePositon(float dt);
    void setActionState(ActionState state);
    void prepareJumpAttack(float delayTime);
    void jumpAttact(float dt);
    void jump();//跳
    bool block();//格档
    bool duck();//闪避
    void dead();//死亡
    virtual void onActionCompleted();
    long getLeftCdTime(int skillID);//得到剩余CD时间
    virtual int getCurSkillID();
public:
    virtual void onAddBloodBuff(int buffType); //持续回血
    virtual void onHurtBloodBuff(int buffType);//持续伤害
protected:
    void onUseSkill(DictSkill* dictSkill);
public:
   
    CC_SYNTHESIZE_RETAIN(DictHero*, _dictHero, DictHero);
    bool _isUserControl;//是否玩家在控制中。
    bool _isMainHero;
   
    
    float _angryValue;//怒气值
};

#endif /* defined(__FightPass__Hero__) */
