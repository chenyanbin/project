//
//  Monster.h
//  FightPass
//
//  Created by zhangxiaobin on 15/5/24.
//
//

#ifndef __FightPass__Monster__
#define __FightPass__Monster__

#include "../Avatar.h"
#include "../../commonData/dictData/DictMonster/DictMonsterManager.h"
#include "../../commonData/dictData/DictSkill/DictSkillManager.h"
class Monster:public Avatar
{
public:
    Monster();
    ~Monster();
    virtual bool init(int monsterID);
    static Monster* create(int monsterID);
public:
    void updateShadow();

    bool attack1();
    bool attack2();
    bool attack3();
    bool attack4();
    bool attack5();
    
    bool skill1();
    bool skill2();
    bool skill3();
    bool skill4();
    bool usePassSkill();//使用被动技能
    void hurtWithDamage(float damage,bool isCrit,bool isBlock,bool isSkillAttack);
    void dash(float distance,float time);//冲撞的距离
    virtual void idle();
    void knockFly(float damage,bool isCrit,bool isBlock,bool isSkillAttack);
    void dead();
    virtual void updatePositon(float dt);
    
    void addBornEffect(const char* effectName);//添加出生特效
    virtual void onEnterScene();//进入视野
    virtual void onExitScene();//退出视野
    void showAttackRange(int frontRange,int backRange);
    void hideAttackRange();
    void showLeftAttackRange(int frontRange,int backRange);
    void showRightAttackRange(int frontRange,int backRange);
    virtual int getCurSkillID();
    virtual char* class_name(){return "Monster";};
private:
    void onBossBorn();

public:
//    string m_resource;

    bool isReadyAttack;//是否准备攻击

    bool _isBoss;//是否 boss
   
    int _blockNum;//所在区域
    int _touch;//触发点
    int _turnWaves;//第几波的怪
    int _battleMonsterID;//战斗中的怪物ID，如果是关卡战斗，则是stageBattleMonsterID,如果是三国无双，则是musouBattleMonsterID......
private:
     CC_SYNTHESIZE_RETAIN(DictMonster*, _dictMonster, DictMonster);
    
    DrawNode* m_attackNode;//攻击范围
};

#endif /* defined(__FightPass__Monster__) */
