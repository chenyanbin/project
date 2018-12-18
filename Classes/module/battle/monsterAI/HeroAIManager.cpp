//
//  HeroAIManager.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/6/26.
//
//
#include "../BattleMapLayer.h"
#include "HeroAIManager.h"
#include "../data/MapDataManager.h"
#include "../../../common/TimeUtil.h"
#include "../../../commonData/dictData/DictAiSkillCast/DictAiSkillCastManager.h"
#include "../../../commonData/dictData/DictAiWaitTime/DictAiWaitTimeManager.h"
#include "MonsterAIManager.h"
#include "../../../AppMacros.h"
#include "../../../avatar/summonedHero/SummonedHero.h"
#include "../../../commonData/dictData/DictAiWaitPerformance/DictAiWaitPerformanceManager.h"
HeroAIManager* HeroAIManager::_instance = NULL;
HeroAIManager::HeroAIManager()
:_monsterList(NULL)
,_heroList(NULL)
,_mainHero(NULL)
,_mapWidth(0)
,_mapHeight(0)
,m_map(NULL)
,m_heroIsWalkEnd(false)
,m_attackRange(0)
,isAutoFight(false)
,m_nowTime(0)
{
    
}
HeroAIManager::~HeroAIManager()
{
    _monsterList = NULL;
    _heroList = NULL;
    _mainHero = NULL;
    
}

void HeroAIManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}
HeroAIManager* HeroAIManager::getInstance()
{
    if(!_instance)
    {
        _instance = new HeroAIManager();
    }
    return _instance;
}
void HeroAIManager::setObjectList(Vector<Avatar*>* monsterList,Vector<Hero*>* heroList)
{
    _monsterList = monsterList;
    _heroList = heroList;
}
void HeroAIManager::setMainHero(Hero* hero)
{
    this->_mainHero = hero;
}
void HeroAIManager::setMapLayer(TMXTiledMap* map)
{
    this->m_map = map;
}
void HeroAIManager::updateHero(double nowtime,float dt)
{
    m_nowTime = nowtime;
    if(!_mainHero || _mainHero->isPauseState())
    {
        return;
    }
   
    bool isTransfer = false;//是否是传送点
    Point cp = {_mainHero->getPositionX() / GlobalInfo::getInstance()->map_tiled_width,_mainHero->getPositionY() / GlobalInfo::getInstance()->map_tiled_height};
    cp = MapDataManager::getInstance()->isTransferPoint(cp);
    if(cp != Point::ZERO)
    {
        cp = cp * GlobalInfo::getInstance()->map_tiled_width;
        cp.y = _mapHeight - cp.y - GlobalInfo::getInstance()->map_tiled_height / 2;
        _mainHero->_destinatsionPostion = cp;
        _mainHero->setPosition(cp.x, cp.y);
        isTransfer = true;
    }
    
    
    ActionState state = kActionStateNone;
   
    float distsance = 0;
    Avatar* monster = NULL;
    
    
    float posX = 0;
    for(Hero* hero : * _heroList)
    {
        
        state = hero->getActionState();
        if(hero->isPauseState() ||  hero->getAvatarProp()->health <= 0)
        {
            continue;
        }
        if(hero->hasBuffState(DictBuffTypeEnumBlock) && this->frontIsHasEnemy(hero))
        {
            continue;
        }
        
        
        hero->updatePositon(dt);
        posX = MIN(_mapWidth - hero->_centerToSide,MAX(hero->_centerToSide,hero->_destinatsionPostion.x));
        hero->setPositionX(posX);
        hero->setLocalZOrder(5000 - hero->getPositionY());
        if(isTransfer && hero != _mainHero)
        {
            cp = MapDataManager::getInstance()->positionToSelfPostion(hero, _mainHero->getPosition());
            hero->_destinatsionPostion = cp;
            hero->setPosition(cp.x, cp.y);
            continue;
        }
        if(hero->hasBuffState(DictBuffTypeEnumShield))
        {
            continue;
        }
        if(hero->trunter && hero->trunter->getAvatarProp()->health > 0)
        {
            monster = hero->trunter;
        }
        else
        {
             monster = isAutoFight ? getNearyEnemy(hero) : getEnemy(hero);
        }
       
        
        if(hero == _mainHero)
        {
            updateMainHero(dt,monster);
        }
        else if(monster)
        {
            hero->_taskState = kTaskStateAttack;
            onHeroAttack(hero, monster);
        }
        else
        {
            distsance = abs(hero->getPositionX() - _mainHero->getPositionX());
            hero->_taskState = kTaskStateFollowMainHero;
            followeMainHero(hero, distsance);
        }
    }
}

inline int HeroAIManager::getAttackDelayTime(Hero* hero)//得到等待时间
{
    
    int aiID = hero->getDictHero()->aiId;

    
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
inline void HeroAIManager::onSummonHeroGuard(Hero* hero,float distance)
{
    
    Point direction;
    if(distance > 0 && distance > hero->_followMainHeroDistance )
    {
        if(distance > hero->_followMainHeroDistance + GlobalInfo::getInstance()->map_tiled_width * GlobalInfo::getInstance()->m_avatarScale)
        {
            direction.x =  -1;
            
        }
        else
        {
            direction.x = 0;
        }
        
    }
    else if(distance > 0 && distance < hero->_followMainHeroDistance)
    {
        if(distance < hero->_followMainHeroDistance - GlobalInfo::getInstance()->map_tiled_width * GlobalInfo::getInstance()->m_avatarScale )
        {
            direction.x = 1;
        }
        else
        {
            direction.x = 0;
        }
    }
    else if(distance < 0 && _mainHero->isLeft)
    {
        if(distance < -hero->_followMainHeroDistance - GlobalInfo::getInstance()->map_tiled_width)
        {
            direction.x = 1;
        }
        else
        {
            direction.x = 0;
        }
    }
    else if(distance < 0 && !_mainHero->isLeft)
    {
        direction.x = 1;
    }
    else if(distance == 0)
    {
        direction.x = _mainHero->isLeft ? -1 : 1;
    }
    
    hero->setDirection(direction);
    
    
    if(direction != Point::ZERO)
    {
        direction = MapDataManager::getInstance()->getAvatarWalkDirection(hero, hero->isLeft);
        hero->walkWithDirection(direction, true);
    }
    else
    {
        hero->idle();
        hero->_taskState = kTaskStateGuard;
    }
}
inline void HeroAIManager::updateMainHero(float dt,Avatar* monster)
{
    if(isAutoFight && !_mainHero->_isUserControl )
    {
        if(monster)
        {
            _mainHero->_taskState = kTaskStateAttack;
            onHeroAttack(_mainHero,monster);
        }
        else if(_monsterList->size())
        {
            monster = _monsterList->at(0);
            if(monster && monster->getAvatarProp()->health > 0)
            {
                _mainHero->_taskState = kTaskStateAttack;
                onHeroAttack(_mainHero,monster);
            }
        }
        else
        {
            _mainHero->_taskState = kTaskStateGuard;
            heroRun(_mainHero, false);
        }
        
    }
    
}
inline void HeroAIManager::onHeroAttack(Hero* hero,Avatar* target)
{

    if(hero->getActionState() != kActionStateWalk && hero->getActionState() != kActionStateIdle)
    {
        return;
    }
    int skillid = getSkillID(hero);;
  
    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(skillid);
    if(!dictSkill)
    {
        return;
    }
    //    int distance =  (attackData->_bombPoint - target->getPosition()).getLength() / MAP_TILED_WIDTH ;
    int distance = (hero->getPosition() - target->getPosition()).getLength() / GlobalInfo::getInstance()->map_tiled_width;
    float frontHurtRange = frontHurtRange = this->m_attackRange * GlobalInfo::getInstance()->m_avatarScale;//前方伤害范围;
    
    m_nowTime = time(0);
    if(distance >frontHurtRange)
    {
        
        if(m_nowTime < hero->_nextDecisionTime )
        {
            if(hero->_delayState == kdelayStateWalkBack )
            {
                hero->idle();
                return;
            }
            else if(hero->_delayState == kdelayStateSlowAway)
            {
                return;
            }
        }
        else if(hero->_actionState == kActionStateIdle|| hero->_actionState == kActionStateWalk)
        {
            if(hero->_taskState == kTaskStateFollowMainHero)
            {
                return;
            }
            if(hero->isLeft && target->getPositionX() >= target->getPositionX())
            {
                Point direction;
                direction.x = 1;
                hero->setDirection(direction);
            }
            else if(!hero->isLeft && target->getPositionX() < target->getPositionX())
            {
                Point direction;
                direction.x =  -1;
                hero->setDirection(direction);
            }
            
            heroRun(hero,target->getPositionX() < hero->getPositionX());
        }
        return;
    }
    else
    {
  
        if(m_nowTime < hero->_nextDecisionTime )
        {
        
            onDelayState(hero,target);
   
            return;
        }
        hero->_delayState = kdelayStateNone;
        hero->_nextDecisionTime = m_nowTime + (double)getAttackDelayTime(hero) / 1000.0;//表里写的是毫秒
        Point direction;

        direction.x = target->getPositionX() < hero->getPositionX() ? -1 : 1;
        hero->setDirection(direction);

        if(skillid == hero->getDictHero()->skill1)
        {
           
            hero->attack1();
        }
        else if(skillid == hero->getDictHero()->skill6)
        {
       
            hero->prepareJumpAttack(.2);
        }
        else if(skillid == hero->getDictHero()->skill7)
        {
         
            hero->skill1();
        }
        else if(skillid == hero->getDictHero()->skill8)
        {
        
            hero->skill2();
        }
        else if(skillid == hero->getDictHero()->skill9)
        {
       
            hero->skill3();
        }
        else if(skillid == hero->getDictHero()->skill10)
        {
            PublicShowUI::broadUserMsg(CUSTOM_BATTLE_RELEASEBIGSKILL, hero);
        }
        else if(skillid == hero->getDictHero()->skill11)
        {
            hero->prepareJumpAttack(.2);
        }
        else
        {
           
            hero->attack1();
        }
        
    }
    
}
inline int HeroAIManager::getSkillID(Hero* hero)
{
   
    DictAiSkillCast* skillCast = DictAiSkillCastManager::getInstance()->getData(hero->getDictHero()->aiId);
    
    if(!skillCast)
    {
        return hero->getDictHero()->skill1;;
    }
    int skillid = 0;
    vector<int> rateList;
    vector<int> skillList;
    vector<int> rangeList;
   
    
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
    if(!hero->getIsCDState(hero->getDictHero()->skill10) && hero->getDictHero()->skill10 )
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
            this->m_attackRange = rangeList[i];
            break;
        }
    }
    return skillid;
}
inline void HeroAIManager::onDelayState(Hero* hero,Avatar* ememy)//等待状态
{
    float _titleWidth = GlobalInfo::getInstance()->map_tiled_width * 3;
    AttackDelayState flag = hero->_delayState == kdelayStateNone ?  getDelayStateFlag(hero) : hero->_delayState;
    if(flag == kdelayStateWalkOn)
    {//wonder(0)//反复走
        hero->_walkSpeed =  hero->_baseSpeed;
        heroRun(hero,hero->isLeft);
    }
    else if(flag == kdelayStateIdle)
    {//原地站立
        hero->_walkSpeed =  hero->_baseSpeed;
        hero->idle();
    }
    else if(flag == kdelayStateWalkBack)
    {//尝试绕后
        hero->_walkSpeed =  hero->_baseSpeed;
        
        if(hero->_delayState != kdelayStateWalkBack)
        {
            heroRun(hero,!ememy->isLeft);
        }
        else
        {
            if(ememy->isLeft && hero->getPositionX() - ememy->getPositionX() > _titleWidth)
            {
                hero->idle();
            }
            else if(!ememy->isLeft && hero->getPositionX() - ememy->getPositionX() < -_titleWidth)
            {
                hero->idle();
            }
            else
            {
                heroRun(hero,hero->isLeft);
            }
        }
    }
    
    else if(flag == kdelayStateSlowAway)
    {//慢速远离
        hero->_walkSpeed =  hero->_baseSpeed / 2;
        bool isLeft = hero->isLeft;
        if(hero->_delayState != kdelayStateSlowAway )
        {
            isLeft = ememy->getPositionX() < hero->getPositionX() ;
            Point direction;
            direction.x = isLeft ? -1 : 1;
            hero->setDirection(direction);
        }
        hero->_delayState = flag;
        heroRun(hero,!isLeft);
    }
    hero->_delayState = flag;
    
}
inline AttackDelayState HeroAIManager::getDelayStateFlag(Hero* target)
{
    int aiID = 0;
    string className = target->class_name();
    if(className == "Hero" || className == "SummonedHero")
    {
        Hero* hero = (Hero*)target;
        aiID = hero->getDictHero()->aiId;
    }
    else
    {
        Monster* monster = (Monster*)target;
        aiID = monster->getDictMonster()->aiId;
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

inline void HeroAIManager::followeMainHero(Hero* hero,float gridDistance)//跟随主将
{
    
    if(hero->_isMainHero)
    {
        return;
    }
    
    if(gridDistance > hero->_followMainHeroDistance)
    {
        if(hero->_taskState != kTaskStateFollowMainHero)
        {
            hero->_taskState = kTaskStateFollowMainHero;
        }
        heroRun(hero,_mainHero->getPositionX() <  hero->getPositionX());
    }
    else
    {
        //        log("没怪了，休息＝＝%s",hero->getDictHero()->name.c_str());
        hero->_taskState = kTaskStateGuard;
        hero->idle();
        
    }
    
}
inline void HeroAIManager::heroRun(Hero* hero,bool isLeft)
{
    Point direction = MapDataManager::getInstance()->getAvatarWalkDirection(hero, isLeft);
    if(direction == Point::ZERO)
    {
        hero->idle();
        hero->_velocity = Point::ZERO;
    }
    else
    {
        if(hero->getActionState() != kActionStateWalk && hero->getActionState() != kActionStateIdle )
        {
            hero->idle();
        }
        hero->walkWithDirection(direction,false);
    }
}
inline Avatar* HeroAIManager::getEnemy(Hero* hero)
{
    Avatar* tempMonster = NULL;
    float distance =0;
    ssize_t len = _monsterList->size();
    for(int i = 0; i < len; i++)
    {
        tempMonster = _monsterList->at(i);
        if(tempMonster->getAvatarProp()->health <= 0)
        {
            continue;
        }
        
        distance = fabsf(tempMonster->getPositionX() - hero->getPositionX());
        if(distance <= hero->_warningRange)
        {
            return tempMonster;
        }
        
    }
    return NULL;
}
Avatar* HeroAIManager::getNearyEnemy(Avatar* hero)//得到最近的一个怪、
{
    Avatar* nearyMonster = NULL;
    Avatar* tempMonster = NULL;
    float distance =0;
    ssize_t len = _monsterList->size();
    for(int i = 0; i < len; i++)
    {
        tempMonster = _monsterList->at(i);
        if(tempMonster->getAvatarProp()->health <= 0)
        {
            continue;
        }
        
        distance = fabsf(tempMonster->getPositionX() - hero->getPositionX());
        if(distance <= 1136)
        {
            if(!nearyMonster)
            {
                nearyMonster = tempMonster;
            }
            else
            {
                if(distance < fabsf(hero->getPositionX() - nearyMonster->getPositionX()))
                {
                    nearyMonster = tempMonster;
                }
            }
        }
        
    }
    //    if(nearyMonster == NULL)
    //    {
    //        log("lsdfjlj==%f",distance);
    //    }
    return nearyMonster;
}
inline int HeroAIManager::heroIsCloseIn(Hero* hero)
{
    Avatar* monster = NULL;
    float distance =0;
    bool isInLeft = false;
    bool isInRight = false;
    ssize_t len = _monsterList->size();
    for(int i = 0; i < len; i++)
    {
        monster = _monsterList->at(i);
        distance = monster->getPositionX() - hero->getPositionX();
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
inline bool HeroAIManager::frontIsHasEnemy(Avatar* hero)//前方1格内是否有怪
{
    Avatar* monster = NULL;
    float distance =0;
     BuffEffectData* buffEffect = hero->getBuffEffectData(DictBuffTypeEnumBlock);
    if(!buffEffect)
    {
        return false;
    }
    float effectRange  = buffEffect->getDictBuff()->effect ;
   
   
    ssize_t len = _monsterList->size();
    for(int i = 0; i < len ; i++)
    {
        monster = _monsterList->at(i);
        distance = monster->getPosition().getDistance(hero->getPosition());
        if(hero->isLeft && distance >= -effectRange && distance < 0)
        {
            return true;
        }
        else if(!hero->isLeft && distance <= effectRange&& distance > 0)
        {
            return true;
        }
        
    }
    return false;
}
