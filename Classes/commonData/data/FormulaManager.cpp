//
//  FormulaManager.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/8/12.
//
//

#include "FormulaManager.h"
#include "../../avatar/hero/Hero.h"
#include "../../avatar/monster/Monster.h"
#include "../dictData/DictGlobalFormula/DictGlobalFormulaManager.h"
#include "DictManager.h"
#include "../enum/DictAttackTypeEnum.h"
#include "../../common/StringUtil.h"
double FormulaManager::getHeroAttackDamage(Avatar* attacker,Avatar* defender,SkillAttackData* skillAttackData)
{
    
    

    double damageActual = 0;
    double handBlockAdjust = DictManager::getFormulaValue(BLOCKHAND_ADJUST);
    double blockAdjust = DictManager::getFormulaValue(BLOCK_ADJUST);
    double criticAdjust = DictManager::getFormulaValue(CRITIC_ADJUST);
    double hitBase = DictManager::getFormulaValue(HIT_BASE);
    double damage = getAttackerBaseDamage(attacker,defender,skillAttackData);
    //hitActual=hitBase+A.hit-B.block
    float hitActual = hitBase + attacker->getAvatarProp()->hit - defender->getAvatarProp()->block;
    int hitRand = PublicShowUI::genRandom(1, 10000);//1~10000随机值
    float hitJudge = hitActual / hitRand ;
//    hitJudge>=1,则命中成功，执行暴击结算；hitJudge<1,则被格挡，则跳过暴击结算过程
    
    skillAttackData->_isCrit  = false;
    skillAttackData->_isBlock = false;
    if(hitJudge >= 1)
    {
        double criticActual = attacker->getAvatarProp()->critic - defender->getAvatarProp()->tenaci;
        int critiRand = PublicShowUI::genRandom(1, 10000);
        double criticJudge = criticActual / critiRand;
        
        skillAttackData->_isCrit  = criticJudge >= 1; //是否暴击
        damageActual = skillAttackData->_isCrit ? damage * criticAdjust : damage;
    }
    else
    {
        damageActual = damage * blockAdjust;
        skillAttackData->_isBlock = true;
    }

    damageActual = damageActual + damageActual * (CCRANDOM_0_1() * 10 / 100);//
   if(defender->getActionState() == kActionStateBlock)
   {//格档状态
       skillAttackData->_isBlock = true;
       damageActual *= handBlockAdjust;
   }
    damageActual = ceil(damageActual);
    damageActual = damageActual < 1 ? 1 : damageActual;
        
    return (damageActual);
}
double FormulaManager::getAttackerBaseDamage(Avatar* attacker,Avatar* defender,SkillAttackData* skillAttackData)
{
    double unhurtLevelAdjust = DictManager::getFormulaValue(UNHURTLEVEL_ADJUST);
    double unhurtAdjust = DictManager::getFormulaValue(UNHURT_ADJUST);
//    if(skillAttackData->getDictSkill()->id == 146135)
//    {
//        log("111111");
//    }
  
    float skillDamagePower = 0;
    if(skillAttackData->getAttackNumber() == 1)
    {
        skillDamagePower = skillAttackData->getDictSkill()->damagePower1;
    }
    else if(skillAttackData->getAttackNumber() == 2)
    {
        skillDamagePower = skillAttackData->getDictSkill()->damagePower2;
    }

    
    //    A攻击方；B防守方,Z=skill.damagePower1/skill.damagePower2/skill.damagePower3/buff.effect/buff.hurt
    string buffIDStr = skillAttackData->getDictSkill()->toBuffId;
    int buffid = 0;
    if(buffIDStr.size() > 0)
    {
        buffid = atoi(StringUtil::split(buffIDStr, ",").at(0).c_str());
    }
    DictBuff* dictbuff = DictBuffManager::getInstance()->getData(buffid);
    double Z = 100;
    float damage = 0;
    if(dictbuff && (dictbuff->effect != 0 || dictbuff->hurt != 0))
    {
        int buffEffect = dictbuff ? dictbuff->effect : 100;
        buffEffect = buffEffect == 0 ? 100 : buffEffect;
        int buffHurt = dictbuff ? dictbuff->hurt : 100;
        buffHurt = buffHurt == 0 ? 100 : buffHurt ;
        Z = skillDamagePower /100 * buffEffect / 100 * buffHurt / 100;

        damage = (attacker->getAvatarProp()->attack - defender->getAvatarProp()->defend - unhurtAdjust - defender->getAvatarProp()->level * defender->getAvatarProp()->level * unhurtLevelAdjust) * Z;
    }
    else
    {
//        damage =  skillDamagePower * attacker->getAvatarProp()->attack * (defender->getAvatarProp()->level * unhurtLevelAdjust + unhurtAdjust) / (defender->getAvatarProp()->defend + defender->getAvatarProp()->level * unhurtLevelAdjust + unhurtAdjust) /100 ;
        damage = skillDamagePower * (attacker->getAvatarProp()->attack - defender->getAvatarProp()->defend - unhurtAdjust - defender->getAvatarProp()->level * defender->getAvatarProp()->level * unhurtLevelAdjust) / 100;
    }
  
    float resist = 0;
    switch (skillAttackData->getDictSkill()->attackType) {
        case DictAttackTypeEnumMelee://物理
            resist = 0;
            break;
        case DictAttackTypeEnumFire://火焰
            resist = defender->getAvatarProp()->fireResist;
            break;
        case DictAttackTypeEnumIce://冰霜
            resist = defender->getAvatarProp()->iceResist;
            break;
        case DictAttackTypeEnumBolt://雷电
            resist = defender->getAvatarProp()->boltResist;
            break;
        case DictAttackTypeEnumWind://飓风
            resist = defender->getAvatarProp()->windResist;
            break;
        case DictAttackTypeEnumPoison://巫毒
            resist = defender->getAvatarProp()->poisonResist;
            break;
        default:
            break;
    }

    damage = damage * (1 + attacker->getAvatarProp()->damageAdd /10000 - resist /10000);
   
    return damage;
}
 bool FormulaManager::isAbleKnockFly(int count)
{
    if(count <= 0 || count >= 3)
    {
        return true;
    }
    bool bref = false;
    int rate = 0;
    if(count == 1)
    {
        rate = DictManager::getFormulaValue("StunProtect1");
    }
    else if(count < 3)
    {
        rate = DictManager::getFormulaValue("StunProtect2");
    }
    int num = PublicShowUI::genRandom(0, rate);
    bref = rate < (10000 - num);

    return bref;
   
}