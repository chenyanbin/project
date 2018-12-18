//
//  SkillEffectLayer.h
//  FightPass
//
//  Created by zhangxiaobin on 15/6/15.
//
//

#ifndef __FightPass__SkillEffectLayer__
#define __FightPass__SkillEffectLayer__

#include "cocos2d.h"
USING_NS_CC;
#include "../../../avatar/Avatar.h"
#include "SkillEffect.h"
#include "../../../commonData/dictData/DictSkill/DictSkillManager.h"
#include "../../../protocol/UserCustomEvent.h"
class SkillAttackData:public Ref
{
public:
    SkillAttackData(Avatar* target,int team)
    :_target(NULL),m_team(team)
    ,_releaseEffect(NULL),_dictSkill(NULL)
    ,m_attackCount(0),_frontHurtRange(0),_backHurtRange(0),_isCrit(false),_frontFindRange(0),_backFindRange(0)
    ,_isLeft(false),_isBlock(false),_isSkillAttack(false)
    {
       
        this->setTarget(target);
    }
   
    ~SkillAttackData()
    {
        
        CC_SAFE_RELEASE_NULL(_target);
        CC_SAFE_RELEASE_NULL(_releaseEffect);
        CC_SAFE_RELEASE_NULL(_dictSkill);
    }

    void onSkillAttack(int count)
    {
        this->m_attackCount = count;
        if(_target)
        {
            if(m_attackCount == 2)
            {//飞行特效爆点在特效位置
                _bombPoint = _releaseEffect->getPosition();
            }
//            if(_target->_avatarType == AVATAR_TYPE_HERO)
//            {
//                log("broad CUSTOM_ON_SKILL_ATTACK CUSTOM_ON_SKILL_ATTACK CUSTOM_ON_SKILL_ATTACK");
//                log("");
//            }
            PublicShowUI::broadUserMsg(CUSTOM_ON_SKILL_ATTACK, this);
        }
    
    }
    int getAttackNumber()
    {
        return m_attackCount;
    };
 public:
    CC_SYNTHESIZE_RETAIN(Avatar*, _target, Target);
    CC_SYNTHESIZE_RETAIN(SkillEffect*,_releaseEffect,ReleaseEffect);
    CC_SYNTHESIZE_RETAIN(DictSkill*,_dictSkill,DictSkill);
    int m_team;
    
    Point _destinatsionPostion;//目标位置
    Point _releasePoint;//施法点。
    Point _bombPoint;//炸点
    int _frontHurtRange;//前面伤害范围
    int _backHurtRange;//后面伤害范围
    
    int _frontFindRange;//前面查找范围
    int _backFindRange;//后面查找范围
    bool _isLeft;//是否向左边施放
    bool _isCrit;//是否暴击
    bool _isBlock;//是否格档
    bool _isSkillAttack;//是否是技能攻击
    vector<string> buffList;
private:
    int m_attackCount;//攻击次数

};
class SkillEffectLayer:public Layer
{
public:
    SkillEffectLayer();
    ~SkillEffectLayer();
    bool init(TMXTiledMap* objectMap,ccMenuCallback skillAttackCallBack);
    static SkillEffectLayer* create(TMXTiledMap* objectMap,ccMenuCallback skillAttackCallBack);
    
    void addSkillEffect(Avatar* target,int skillID,int team);
    
protected:
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    
    virtual void update(float dt);
private:
    void onFlyEffectEnd(SkillAttackData* target);
private:
    
    TMXTiledMap* m_objectMap;
    ccMenuCallback m_callBack;
    int m_tiledWidth;
    int m_tiledHeight;
    
    Map<int,SkillAttackData*>* dataList;
};

#endif /* defined(__FightPass__SkillEffectLayer__) */
