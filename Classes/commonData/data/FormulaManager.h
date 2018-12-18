//
//  FormulaManager.h
//  FightPass
//
//  Created by zhangxiaobin on 15/8/12.
//公式管理
//

#ifndef __FightPass__FormulaManager__
#define __FightPass__FormulaManager__

#define BLOCK_ADJUST        "blockAdjust" //格档调整值
#define CRITIC_ADJUST       "criticAdjust"//暴击伤害调整值
#define UNHURTLEVEL_ADJUST  "unhurtLevelAdjust"//免伤等级调整值
#define UNHURT_ADJUST       "unhurtAdjust"//免伤调整值
#define HIT_BASE            "hitBase"//默认命中率
#define BLOCKHAND_ADJUST     "blockHandAdjust"//主动格挡调整值


#include "cocos2d.h"
USING_NS_CC;
#include "../../avatar/Avatar.h"
#include "../../module/battle/skillEffectLayer/SkillEffectLayer.h"
class FormulaManager
{
public:
    //得到攻击伤害值
    static double getHeroAttackDamage(Avatar* attacker,Avatar* defender,SkillAttackData* skillAttackData);
    //基础伤害值
    static double getAttackerBaseDamage(Avatar* attacker,Avatar* defender,SkillAttackData* skillAttackData);
    //根据击飞次数判断本次是否可被击飞
    static bool isAbleKnockFly(int count);
};

#endif /* defined(__FightPass__FormulaManager__) */
