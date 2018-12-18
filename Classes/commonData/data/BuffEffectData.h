//
//  BuffData.h
//  FightPass
//
//  Created by zhangxiaobin on 15/8/7.
//
//

#ifndef __FightPass__BuffData__
#define __FightPass__BuffData__

#include "../dictData/DictBuff/DictBuffManager.h"
#include "../../module/battle/skillEffectLayer/SkillEffect.h"
class BuffEffectData:public Node
{
public:
    BuffEffectData();
    ~BuffEffectData();
    virtual bool init(int buffID);
    static BuffEffectData* create(int buffID);
    void release();
public:
    long long endTime;//结束时间
    long long startTime;//开始时间
    double damage;//效果数值
    Sprite* icon;
    virtual void onExit();
    virtual void onEnter();
private:
    void onEffectCompleted(Ref* target);
private:
    int m_buffID;
    CC_SYNTHESIZE_RETAIN(DictBuff*, _dictBuff, DictBuff);
    CC_SYNTHESIZE_RETAIN(SkillEffect*, _skillEffect, SkillEffect);
};

#endif /* defined(__FightPass__BuffData__) */
