//
//  MonsterAIManager.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/6/24.
//
//
#include "../BattleMapLayer.h"
#include "MonsterAIManager.h"
#include "../data/MapDataManager.h"
#include "../../../commonData/dictData/DictSkill/DictSkillManager.h"
#include "../../../common/TimeUtil.h"
#include "../../../commonData/enum/DictMonsterTypeEnum.h"
#include "../../../commonData/enum/DictSkillCostWayEnum.h"
#include "../../../commonData/dictData/DictAiSkillCast/DictAiSkillCastManager.h"
#include "../../../commonData/dictData/DictAiWaitTime/DictAiWaitTimeManager.h"
#include "../../../commonData/dictData/DictAiWaitPerformance/DictAiWaitPerformanceManager.h"
#include "HeroAIManager.h"
MonsterAIManager* MonsterAIManager::_instance = NULL;

MonsterAIManager::MonsterAIManager()
:_monsterList(NULL)
,_heroList(NULL)
,m_hero(NULL)
,_mapWidth(0)
,_mapHeight(0)
,removeList(NULL)
,m_nowTime(0)
,m_attackRange(0)
{
    removeList = new Vector<Avatar*>();
    
}
MonsterAIManager::~MonsterAIManager()
{
    _monsterList = NULL;
    _heroList = NULL;
    m_hero = NULL;
    removeList->clear();
    delete removeList;
    removeList = NULL;
}
MonsterAIManager* MonsterAIManager::getInstance()
{
    if(!_instance)
    {
        _instance = new MonsterAIManager();
    }
    return _instance;
}
void MonsterAIManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}

void MonsterAIManager::setObjectList(Vector<Avatar*>* monsterList,Vector<Hero*>* heroList)
{
    this->_heroList = heroList;
    this->_monsterList = monsterList;
    
}
void MonsterAIManager::setMainHero(Hero* hero)
{
    this->m_hero = hero;
}
void MonsterAIManager::updateMonster(double nowtime,float dt)
{


    Hero* hero = NULL;
    float distance = 0;
    m_nowTime = nowtime;
    for(Avatar* monster : *_monsterList)
    {
      
        if(!monster->getParent())
        {
            removeList->pushBack(monster);
        }
        if(monster->isPauseState() || monster->hasBuffState(DictBuffTypeEnumFrozen) || monster->getAvatarProp()->health <= 0)
        {
            continue;
        }
        monster->setLocalZOrder(5000 - monster->getPositionY());
        
        if(monster->hasBuffState(DictBuffTypeEnumBlock) && this->frontIsHasEnemy(monster))
        {
            continue;
        }
        
        monster->updatePositon(dt);

   
        
        float posX = MIN(_mapWidth - monster->_centerToSide,MAX(monster->_centerToSide,monster->_destinatsionPostion.x));
        monster->setPositionX(posX);
        if(monster->hasBuffState(DictBuffTypeEnumShield))
        {
            continue;
        }
        int friendNum = 5;//getFriendNum(monster); 没有逃跑逻辑了
        
        if(monster->trunter && monster->trunter->getAvatarProp()->health > 0)
        {
            hero = (Hero*)monster->trunter;
            monster->_taskState = kTaskStateAttack;
        }
        else
        {
            hero = HeroAIManager::getInstance()->isAutoFight ? this->getNearyEnemy(monster) : this->getEnemy(monster);
        }
//        if(monster->getDictMonster()->type == DictMonsterTypeEnumBlockMonster || monster->getDictMonster()->type == DictMonsterTypeEnumStageRewardMonster)
        if(strcmp(monster->class_name(), "Monster") != 0 && strcmp(monster->class_name(), "Hero") != 0)
        {
            continue;
        }
        if(hero)
        {
//            distance = fabsf(hero->getPositionX()- monster->getPositionX());
            distance = fabsf(hero->getPosition().getDistance(monster->getPosition()));
            if(monster->_taskState == kTaskStateGuard)
            {
                monster->idle();
                onMonsterGuard(monster,friendNum,distance);
            }
            else if(monster->_taskState == kTaskStateEscape)
            {
                onMonsterEscape(monster,friendNum,distance,hero);
            }
            else if(monster->_taskState == kTaskStateAttack)
            {
                
                onMonsterAttack(monster,friendNum,distance,hero);
            }
            else
            {
                monster->idle();
                monster->_taskState = kTaskStateGuard;
            }
        }
        else
        {
            monster->idle();
            monster->_taskState = kTaskStateGuard;
        }
    }
    for (auto monster : *removeList)
    {
        if(_monsterList->contains(monster))
        {
            _monsterList->eraseObject(monster);
            PublicShowUI::broadUserMsg(CUSTOM_BATTLE_MONSTER_DEAD, monster);
        }
    }
    removeList->clear();
}

inline void MonsterAIManager::onMonsterGuard(Avatar* monster,int friendNum,float distance)
{
    if(distance <= monster->_warningRange)
    {
        if(this->_monsterList->size() <= 10)
        {
            monster->_taskState = kTaskStateAttack;
        }
        else
        {
            monster->_taskState = friendNum < 0 ? kTaskStateEscape : kTaskStateAttack ;
        }
       
    }
    else
    {
        monster->idle();
    }
}
inline void MonsterAIManager::onMonsterEscape(Avatar* monster,int friendNum,float distance,Hero* ememy)
{
    if(friendNum <= 2 &&  distance <= monster->_warningRange)
    {
         monsterRun(monster,ememy->getPositionX() > monster->getPositionX());
    }
    else if(friendNum > 2)
    {
        monster->idle();
        monster->_taskState = kTaskStateAttack;
    }
}
inline int MonsterAIManager::getMonsterSkill(Avatar* monster)
{
    string className = monster->class_name();
    int skillid = 0;
    DictAiSkillCast* skillCast = NULL;
    vector<int> skillList;
    vector<int> rateList;
    vector<int> rangeList;
    int aiID = 0;
    if(className == "Hero")
    {
        Hero* hero = (Hero*)monster;
        aiID = hero->aiID ? hero->aiID : hero->getDictHero()->aiId;
        skillCast = DictAiSkillCastManager::getInstance()->getData(aiID);
      
        if(!skillCast)
        {
            return skillid = hero->getDictHero()->skill1;;
        }
    
        if(!hero->getIsCDState(hero->getDictHero()->skill1) && hero->getDictHero()->skill1)
        {
            rateList.push_back(skillCast->s1Rate);
            skillList.push_back(hero->getDictHero()->skill1);
            rangeList.push_back(skillCast->s1Range);
        }
        if(!hero->getIsCDState(hero->getDictHero()->skill6) && hero->getDictHero()->skill6)
        {
            rateList.push_back(skillCast->s6Rate);
            skillList.push_back(hero->getDictHero()->skill6);
            rangeList.push_back(skillCast->s6Range);
        }
        
        
        if(!hero->getIsCDState(hero->getDictHero()->skill7) && hero->getDictHero()->skill7  && hero->getAvatarProp()->quality >= SKILL1_OPEN_QUALITY)
        {
            rateList.push_back(skillCast->s7Rate);
            skillList.push_back(hero->getDictHero()->skill7);
            rangeList.push_back(skillCast->s7Range);
        }
        if(!hero->getIsCDState(hero->getDictHero()->skill8) && hero->getDictHero()->skill8  && hero->getAvatarProp()->quality >= SKILL2_OPEN_QUALITY)
        {
            rateList.push_back(skillCast->s8Rate);
            skillList.push_back(hero->getDictHero()->skill8);
            rangeList.push_back(skillCast->s8Range);
        }
        if(!hero->getIsCDState(hero->getDictHero()->skill9) && hero->getDictHero()->skill9  && hero->getAvatarProp()->quality >= SKILL3_OPEN_QUALITY)
        {
            rateList.push_back(skillCast->s9Rate);
            skillList.push_back(hero->getDictHero()->skill9);
             rangeList.push_back(skillCast->s9Range);
        }
        if(!hero->getIsCDState(hero->getDictHero()->skill10) && hero->getDictHero()->skill10)
        {
            rateList.push_back(skillCast->s10Rate);
            skillList.push_back(hero->getDictHero()->skill10);
             rangeList.push_back(skillCast->s10Range);
        }
        if(!hero->getIsCDState(hero->getDictHero()->skill11) && hero->getDictHero()->skill11)
        {
            rateList.push_back(skillCast->s11Rate);
            skillList.push_back(hero->getDictHero()->skill11);
            rangeList.push_back(skillCast->s11Range);
        }
   
    }
    else if(className == "Monster")
    {
        Monster* target = (Monster*)monster;
        
        aiID = target->aiID ? target->aiID : target->getDictMonster()->aiId;
        skillCast = DictAiSkillCastManager::getInstance()->getData(aiID);//7002001
        if(!skillCast)
        {
            return target->getDictMonster()->skill1;;
        }
        if(!monster->getIsCDState(target->getDictMonster()->skill1) && target->getDictMonster()->skill1)
        {
            rateList.push_back(skillCast->s1Rate);
            skillList.push_back(target->getDictMonster()->skill1);
            rangeList.push_back(skillCast->s1Range);
        }
        if(!monster->getIsCDState(target->getDictMonster()->skill6) && target->getDictMonster()->skill6)
        {
            rateList.push_back(skillCast->s6Rate);
            skillList.push_back(target->getDictMonster()->skill6);
            rangeList.push_back(skillCast->s6Range);
        }
        if(!monster->getIsCDState(target->getDictMonster()->skill7) && target->getDictMonster()->skill7)
        {
            rateList.push_back(skillCast->s7Rate);
            skillList.push_back(target->getDictMonster()->skill7);
            rangeList.push_back(skillCast->s7Range);
        }
        if(!monster->getIsCDState(target->getDictMonster()->skill8) && target->getDictMonster()->skill8)
        {
            rateList.push_back(skillCast->s8Rate);
            skillList.push_back(target->getDictMonster()->skill8);
            rangeList.push_back(skillCast->s8Range);
        }
        if(!monster->getIsCDState(target->getDictMonster()->skill9) && target->getDictMonster()->skill9)
        {
            rateList.push_back(skillCast->s9Rate);
            skillList.push_back(target->getDictMonster()->skill9);
            rangeList.push_back(skillCast->s9Range);
        }
        if(!monster->getIsCDState(target->getDictMonster()->skill10) && target->getDictMonster()->skill10)
        {
            rateList.push_back(skillCast->s10Rate);
            skillList.push_back(target->getDictMonster()->skill10);
             rangeList.push_back(skillCast->s10Range);
        }
     
    }
    else
    {
         Monster* monster = (Monster*)monster;
         skillid = monster->getDictMonster()->skill1;
        return skillid;
    }
   

    int totalNum = 0;
    ssize_t len = rateList.size();
    for(int i = 0; i < len; i++)
    {
        totalNum += rateList[i];
    }
    int random = PublicShowUI::genRandom(0, totalNum);
    totalNum = 0;
    
    for(int i = 0; i < len; i++)
    {
        totalNum += rateList[i];
        if(random <= totalNum)
        {
            skillid = skillList[i];
            m_attackRange = rangeList[i];
            break;
        }
    }
    return skillid;
}
inline int MonsterAIManager::getAttackDelayTime(Avatar* target)//得到等待时间
{
    
    int aiID = 0;
    string className = target->class_name();
    if(className == "Hero")
    {
        Hero* hero = (Hero*)target;
        aiID = hero->aiID ? hero->aiID : hero->getDictHero()->aiId;
    }
    else
    {
        Monster* monster = (Monster*)target;
        aiID = monster->aiID ? monster->aiID : monster->getDictMonster()->aiId;
    }

    
    int wtime = 0;
    DictAiSkillCast* skillCast = DictAiSkillCastManager::getInstance()->getData(aiID);
    if(!skillCast)
    {
        return wtime;
    }
    DictAiWaitTime* waitTime = DictAiWaitTimeManager::getInstance()->getData(skillCast->waitTimeId);
  
    int timeRateList[5] = {waitTime->wtRate1,waitTime->wtRate2,waitTime->wtRate3,waitTime->wtRate4,waitTime->wtRate5};
    int timeList[5] = {waitTime->waitTime1,waitTime->waitTime2,waitTime->waitTime3,waitTime->waitTime4,waitTime->waitTime5};
    int totalNum = 0;
    int len = 5;
    for(int i = 0; i < len; i++)
    {
        totalNum += timeRateList[i];
    }
    int random = PublicShowUI::genRandom(0, totalNum);
    totalNum = 0;
    for(int i = 0; i < len; i++)
    {
        totalNum += timeRateList[i];
        if(random <= totalNum)
        {
            wtime = timeList[i];
            break;
        }
    }
    return wtime;
}
inline void MonsterAIManager::onMonsterAttack(Avatar* monster,int friendNum,float distance,Hero* enemy)
{
    
    if(monster->getActionState() != kActionStateWalk && monster->getActionState() != kActionStateIdle)
    {
        return;
    }
    int skillid = getMonsterSkill(monster);

    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(skillid);
    if(!dictSkill)
    {
        return;
    }
    m_nowTime = time(0);
    if(distance > m_attackRange * GlobalInfo::getInstance()->m_avatarScale * GlobalInfo::getInstance()->map_tiled_width)
    {
     
        if(m_nowTime < monster->_nextDecisionTime )
        {
            if(monster->_delayState == kdelayStateWalkBack )
            {
                monster->idle();
                return;
            }
            else if(monster->_delayState == kdelayStateSlowAway)
            {
                return;
            }
        }
        if(monster->isLeft && enemy->getPositionX() >= monster->getPositionX())
        {
            Point direction;
            direction.x = 1;
            monster->setDirection(direction);
        }
        else if(!monster->isLeft && enemy->getPositionX() < monster->getPositionX())
        {
            Point direction;
            direction.x =  -1;
            monster->setDirection(direction);
        }
        monsterRun(monster,enemy->getPositionX() < monster->getPositionX());
    }
    else
    {
        
       
     
        if(m_nowTime < monster->_nextDecisionTime )
        {
            onDelayState(monster,enemy);
            return;
        }
        monster->_delayState = kdelayStateNone;
        monster->_nextDecisionTime = m_nowTime + (double)getAttackDelayTime(monster) / 1000.0f;//表里写的是毫秒
        Point direction;
        string className = monster->class_name();
        direction.x = enemy->getPositionX() < monster->getPositionX() ? -1 : 1;
        monster->setDirection(direction);
        if(className == "Hero")
        {
            Hero* hero = (Hero*)monster;
            if(skillid == hero->getDictHero()->skill1)
            {
                monster->attack1();
            }
            else if(skillid == hero->getDictHero()->skill6)
            {
                hero->prepareJumpAttack(.2);
            }
            else if(skillid == hero->getDictHero()->skill7)
            {
                 monster->skill1();
            }
            else if(skillid == hero->getDictHero()->skill8)
            {
                monster->skill2();
            }
            else if(skillid == hero->getDictHero()->skill9)
            {
                monster->skill3();
            }
            else if(skillid == hero->getDictHero()->skill10)
            {
                PublicShowUI::broadUserMsg(CUSTOM_BATTLE_RELEASEBIGSKILL, monster);
            }
            else if(skillid == hero->getDictHero()->skill11)
            {
                 hero->prepareJumpAttack(.2);
            }
            
            else
            {
                 monster->attack1();
            }
          
        }
        else
        {
            Monster* target = (Monster*)monster;

            if(skillid == target->getDictMonster()->skill1)
            {
                monster->attack1();
            }
            else if(skillid == target->getDictMonster()->skill6)
            {
                target->prepareJumpAttack(target->getDictMonster()->skillJumpTime);
            }
            else if(skillid == target->getDictMonster()->skill7)
            {
                if(dictSkill->costWay == DictSkillCostWayEnumCoolDownSkill && target->_isBoss)
                {
                    target->showAttackRange(dictSkill->hurtForward, dictSkill->hurtBackward);
                    delayToSkill(CC_CALLBACK_0(Monster::skill1, ((Monster*)monster)),monster);
                }
                else
                {
                    ((Monster*)monster)->hideAttackRange();
                    monster->skill1();
                }
            }
            else if(skillid == target->getDictMonster()->skill8)
            {
                if(dictSkill->costWay == DictSkillCostWayEnumCoolDownSkill && target->_isBoss)
                {
                    target->showAttackRange(dictSkill->hurtForward, dictSkill->hurtBackward);
                    delayToSkill(CC_CALLBACK_0(Monster::skill2, ((Monster*)monster)),((Monster*)monster));
                }
                else
                {
                    ((Monster*)monster)->hideAttackRange();
                    monster->skill2();
                }
            }
            else if(skillid == target->getDictMonster()->skill9)
            {
                if(dictSkill->costWay == DictSkillCostWayEnumCoolDownSkill && target->_isBoss)
                {
                    target->showAttackRange(dictSkill->hurtForward, dictSkill->hurtBackward);
                    delayToSkill(CC_CALLBACK_0(Monster::skill3, ((Monster*)monster)),((Monster*)monster));
                }
                else
                {
                    ((Monster*)monster)->hideAttackRange();
                    monster->skill3();
                }
            }
            else if(skillid == target->getDictMonster()->skill10)
            {
               PublicShowUI::broadUserMsg(CUSTOM_BATTLE_RELEASEBIGSKILL, monster);
            }
            else
            {
                monster->attack1();
            }
      
        }
        
    }
   
}
inline void MonsterAIManager::onDelayState(Avatar* monster,Avatar* ememy)//等待状态
{

    float _titleWidth = GlobalInfo::getInstance()->map_tiled_width * 3;
    AttackDelayState flag = monster->_delayState == kdelayStateNone ?  getDelayStateFlag(monster) : monster->_delayState;
    if(flag == kdelayStateWalkOn)
    {//wonder(0)//反复走
        monster->_walkSpeed =  monster->_baseSpeed;
        monsterRun(monster,monster->isLeft);
    }
    else if(flag == kdelayStateIdle)
    {//原地站立
        monster->_walkSpeed =  monster->_baseSpeed;
        monster->idle();
    }
    else if(flag == kdelayStateWalkBack)
    {//尝试绕后
        monster->_walkSpeed =  monster->_baseSpeed;
        
        if(monster->_delayState != kdelayStateWalkBack)
        {
      
             monsterRun(monster,!ememy->isLeft);
        }
        else
        {
            if(ememy->isLeft && monster->getPositionX() - ememy->getPositionX() > _titleWidth)
            {
                monster->idle();
            }
            else if(!ememy->isLeft && monster->getPositionX() - ememy->getPositionX() < -_titleWidth)
            {
                monster->idle();
            }
            else
            {
                 monsterRun(monster,monster->isLeft);
            }
        }
    }
 
    else if(flag == kdelayStateSlowAway)
    {//慢速远离
        monster->_walkSpeed =  monster->_baseSpeed / 2;
        bool isLeft = monster->isLeft;
        if(monster->_delayState != kdelayStateSlowAway )
        {
            isLeft = ememy->getPositionX() < monster->getPositionX() ;
            Point direction;
            direction.x = isLeft ? -1 : 1;
            monster->setDirection(direction);
        }
        monster->_delayState = flag;
        monsterRun(monster,!isLeft);
    }
    monster->_delayState = flag;
}
inline AttackDelayState MonsterAIManager::getDelayStateFlag(Avatar* target)
{
    int aiID = 0;
    string className = target->class_name();
    if(className == "Hero")
    {
        Hero* hero = (Hero*)target;
        aiID = hero->aiID ? hero->aiID : hero->getDictHero()->aiId;
    }
    else
    {
        Monster* monster = (Monster*)target;
        aiID = monster->aiID ? monster->aiID : monster->getDictMonster()->aiId;
    }
    
    
    AttackDelayState indexFlag = kdelayStateWalkOn;
    DictAiSkillCast* skillCast = DictAiSkillCastManager::getInstance()->getData(aiID);
    if(!skillCast)
    {
        return indexFlag;
    }
    DictAiWaitPerformance* waitPerformance = DictAiWaitPerformanceManager::getInstance()->getData(skillCast->WaitPerformance);
    int rateList[4] = {waitPerformance->wonder,waitPerformance->flank,waitPerformance->standBy,waitPerformance->standBack};
    AttackDelayState stateList[4] = {kdelayStateWalkOn,kdelayStateWalkBack,kdelayStateIdle,kdelayStateSlowAway};
    int totalNum = 0;
    int len = 4;
    for(int i = 0; i < len; i++)
    {
        totalNum += rateList[i];
    }
    int random = PublicShowUI::genRandom(0, totalNum);
    totalNum = 0;
    for(int i = 0; i < len; i++)
    {
        totalNum += rateList[i];
        if(random <= totalNum)
        {
            indexFlag = stateList[i];
            break;
        }
    }
    return indexFlag;
}
inline void MonsterAIManager::delayToSkill(const std::function<void()>& func,Avatar* monster)
{
    if(monster->getActionState() != kActionStateIdle && monster->getActionState() != kActionStateWalk)
    {
        return;
    }
    CallFunc* callBack = CallFunc::create(func);
   if(((Monster*)monster)->_isBoss)
   {
       DelayTime* delay = DelayTime::create(1.5);
       CallFunc* callBack1 = CallFunc::create(CC_CALLBACK_0(Monster::hideAttackRange, (Monster*)monster));
       
       monster->runAction(Sequence::create(delay, callBack1, callBack,NULL));
   }
    else
    {
        monster->runAction(Sequence::create(callBack,NULL));
    }
    
}
inline Hero* MonsterAIManager::getEnemy(Avatar* monster)
{
    Hero* hero = NULL;
    float distance =0;
    int len = (int)_heroList->size();
    for(int i = len-1; i >= 0; i--)
    {
        hero = _heroList->at(i);
        if(hero->getActionState() == kActionStateDead)
        {
            continue;
        }
        
        distance = fabsf(hero->getPositionX() - monster->getPositionX());
        if(distance <= monster->_warningRange)
        {
            return hero;
        }
        
    }
    return NULL;
}
Hero* MonsterAIManager::getNearyEnemy(Avatar* monster)//得到最近的一个怪
{
    Avatar* nearyAvatar = NULL;
    Avatar* tempMonster = NULL;
    float distance =0;
    int len = (int)_heroList->size();
    for(int i = 0; i < len; i++)
    {
        tempMonster = _heroList->at(i);
        if(tempMonster->getAvatarProp()->health <= 0)
        {
            continue;
        }
        
        distance = fabsf(tempMonster->getPositionX() - monster->getPositionX());
        if(distance <= 1136)
        {
            if(!nearyAvatar)
            {
                nearyAvatar = tempMonster;
            }
            else
            {
                if(distance < fabsf(monster->getPositionX() - nearyAvatar->getPositionX()))
                {
                    nearyAvatar = tempMonster;
                }
            }
        }
        
    }
    
    return (Hero*)nearyAvatar;
}
inline int MonsterAIManager::getFriendNum(Avatar* monster)
{
    int num = 0;
    Avatar* tempMonster = NULL;
    float distance =0;
    ssize_t len = _monsterList->size();
    for(int i = 0; i < len; i++ )
    {
        tempMonster = _monsterList->at(i);
        if(tempMonster->getActionState() == kActionStateDead || tempMonster == monster)
        {
            continue;
        }
      
        distance = fabsf(tempMonster->getPositionX() - monster->getPositionX());
        if(distance <= monster->_warningRange)
        {
            num ++;
        }
        
    }
    return num;
}
inline bool MonsterAIManager::monsterIsCloseIn(Avatar* monster)
{
    Hero* hero = NULL;
    float distance =0;
    bool isInLeft = false;
    bool isInRight = false;
    ssize_t len = _heroList->size();
    for(int i = 0; i < len ; i++)
    {
        hero = _heroList->at(i);
        distance = hero->getPositionX() - monster->getPositionX();
        if(isInLeft && isInRight)
        {
            return true;
        }
        if(abs(distance) < monster->_warningRange)
        {
            if(!isInRight && distance >= 0)
            {
                isInRight = true;
            }
            else if(!isInLeft && distance < 0)
            {
                isInLeft = true;
            }
        }
       
    }
    return false;
}
inline bool MonsterAIManager::frontIsHasEnemy(Avatar* monster)//前方1格内是否有怪
{
    Avatar* hero = NULL;
    ssize_t len = _heroList->size();
    
    float distance =0;
    BuffEffectData* buffEffect = monster->getBuffEffectData(DictBuffTypeEnumBlock);
    if(!buffEffect)
    {
        return false;
    }
    float effectRange  = buffEffect->getDictBuff()->effect;
    
    for(int i = 0; i < len ; i++)
    {
        hero = _heroList->at(i);
     
        distance = hero->getPosition().getDistance(monster->getPosition());
        if(monster->isLeft && distance >= -effectRange && distance < 0)
        {
            return true;
        }
        else if(!monster->isLeft && distance <= effectRange && distance > 0)
        {
            return true;
        }
    
    }
    return false;
}

inline void MonsterAIManager::monsterRun(Avatar* monster,bool isLeft)
{
    if(GlobalInfo::getInstance()->battleType == kBattleType_LoginBattle || strcmp(monster->class_name(), "BlockMonster") == 0)
    {
        return;
    }

    Point direction = MapDataManager::getInstance()->getAvatarWalkDirection(monster, isLeft);
    if(direction != Point::ZERO)
    {
        monster->walkWithDirection(direction, true);
    }
    else
    {
        monster->idle();
        monster->_velocity = Point::ZERO;
    }

}