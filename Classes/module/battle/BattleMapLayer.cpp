 //
//  BattleMapLayer.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/5/24.
//
//

#include "BattleMapLayer.h"
#include "../../common/TimeUtil.h"
#include "settleLayer/BattleLose.h"
#include "settleLayer/BattleWin.h"
#include "../famousGeneral/famouseEndBattle/FamouseBattleWin.hpp"
#include "../famousGeneral/famouseEndBattle/FamouseBattleLose.hpp"
#include "../storyTalk/StoryTalkManager.h"
#include "../../common/ImagePath.h"
#include "../../commonData/enum/DictMonsterTypeEnum.h"
#include "../../commonData/enum/DictSkillCostWayEnum.h"
#include "../../commonData/dictData/DictSkillKarma/DictSkillKarmaManager.h"
#include "../../commonData/dictData/DictBattlePotion/DictBattlePotionManager.h"
#include "../../commonData/data/DictManager.h"
#include "monsterAI/MonsterAIManager.h"
#include "monsterAI/HeroAIManager.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../message/Decoding/battle/BattleEatBloodMsg.h"
#include "../../message/Decoding/battle/EnvironmentMonsterDeadMsg.h"
#include "../../net/networkDataProcessing.h"
#include "../../common/FogLayer.h"
#include "battleUI/ControlBtnPanel.h"
#include "battleUI/DoubleHitManager.h"
#include "battleUI/HeroHeadListLayer.h"
#include "battleUI/BossBloodManager.h"
//#include "battleUI/MapProgressLayer.h"
#include "enterWay/EnterWay.h"
#include "../../common/StringUtil.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "../../commonData/enum/DictStageBattleLayerTypeEnum.h"
#include "../../commonData/data/FormulaManager.h"
#include "battleUI/AngryProgressManager.h"
#include "../../commonData/enum/DictSkillTargetEnum.h"
#include "../../avatar/blockMonster/BlockMonster.h"
#include "battleUI/RebornPanel.h"
#include "../newPlayerGuide/NewPlayerGuild.h"
#include "../../commonData/enum/DictContTypeEnum.h"
#include "../../commonData/enum/DictRolePropEnum.h"
#include "../../commonData/dictData/DictResource/DictResourceManager.h"
#include "battleUI/BattleOperationLayer.hpp"
#include "battleUI/BattleCountDown.hpp"
#include "../../commonData/dictData/DictLegendBattleMonster/DictLegendBattleMonsterManager.h"
#include "../../commonData/dictData/DictSummonSkill/DictSummonSkillManager.h"
#include "../../avatar/summonedHero/SummonedHero.h"
#include "../../commonData/dictData/DictLegend/DictLegendManager.h"
#include "../battleTest/PlayerDataManager.hpp"
#include "settleLayer/ArenaBattleWin.hpp"
#include "../../commonData/enum/DictSkillTypeEnum.h"
BattleMapLayer::BattleMapLayer()
:m_mapContainer(NULL)//地图容器
,m_backGround(NULL)//背景层
,midLayer(NULL) //1层
,nearLayer(NULL)//2层
,closeLayer(NULL)//3层
,m_Hero(NULL)
,m_isbigSkilling(false)
,_monsterList(NULL)
,_heroList(NULL)
,_blockMonsterList(NULL)
,_bornMonsterList(NULL)
,_heroPropList(NULL)
,fightObjLayer(NULL)
,sceneEffecdtLayer(NULL)
,m_scaleX(0)
,m_attackClickCount(0)
,m_isInTimeing(false)
,m_stageBattleID(0)
,isArrivingEnd(false)
,_tureWaves(0)
,skillEffectLayer(NULL)
,popUpLoading(NULL)
,_mapWidth(0)
,_mapHeight(0)
,bigSkillTime(5)
,shakeAction(NULL)
,_hasNextWave(false)
,TAG_BIGSKILL_EFFECTBG(1)
,TAG_BORNEFFECT(2)
,TAG_GOEFFECT(500)
,m_totalHealth(0)
,m_curHealth(0)
,m_bloodBottle(0)
,m_totalBloodBottle(0)
,screenIsMoving(false)
,_battleReborn(NULL)
,m_nowReviceCount(0)
,_sceneEffecctList(NULL)
,_midLayerEffectList(NULL)
,m_mainHeroID(0)
,heroIsBorn(true)
,bossComeIsWarning(false)
,m_resourceTotal(0)
,m_buyBloodCount(0)
,dropCoin(0)
,m_startTime(0)
,bossBlood(0)
,m_totalBuyBloodCount(0)
,dropList(NULL)
,m_leftTime(0)
,m_victoryTime(0)
,isTimeWinMode(false)
,m_isLeft(false)
,_frameInit(1)
{
    dropList = new Vector<Node*>();
    _monsterList = new __Set();
    _heroList = new Vector<Hero*>;
    _bornMonsterList = new Vector<Avatar*>();
    _blockMonsterList = new __Set();
    _sceneEffecctList = new Vector<Armature*>();
    _midLayerEffectList = new Vector<Armature*>();
    shakeAction = Sequence::create(Shake::create(0.5f, 17.0f * GlobalInfo::getInstance()->screenScaleX),CallFunc::create(CC_CALLBACK_0(BattleMapLayer::onShakeEnd, this)),NULL);
    CC_SAFE_RETAIN(shakeAction);
}
BattleMapLayer::~BattleMapLayer()
{
    CC_SAFE_RELEASE_NULL(shakeAction);
    CC_SAFE_RELEASE_NULL(popUpLoading);
    bigSkillLayer->removeAllChildren();
    fightObjLayer->removeAllChildren();
    skillEffectLayer->removeAllChildren();
    m_mapContainer->removeAllChildren();
    
    CC_SAFE_DELETE(dropList);
    dropList = NULL;
    _sceneEffecctList->clear();
    _midLayerEffectList->clear();
    CC_SAFE_DELETE(_heroList);
    _heroList = NULL;
    _monsterList->removeAllObjects();
    CC_SAFE_DELETE(_monsterList);
    _monsterList = NULL;
    bigSkillLayer = NULL;
    fightObjLayer = NULL;
    skillEffectLayer = NULL;
    m_mapContainer = NULL;
    sceneEffecdtLayer = NULL;
   
    CC_SAFE_DELETE(_bornMonsterList);
    _bornMonsterList = NULL;
    _heroPropList = NULL;
    
    _blockMonsterList->removeAllObjects();
    CC_SAFE_DELETE(_blockMonsterList);
    _blockMonsterList = NULL;
    CC_SAFE_RELEASE_NULL(_battleReborn);
    
    CC_SAFE_DELETE(_sceneEffecctList);
    _sceneEffecctList = NULL;
    CC_SAFE_DELETE(_midLayerEffectList);
    _midLayerEffectList = NULL;
}
BattleMapLayer* BattleMapLayer::create(int battleID,Vector<DictAvatarProp*>* heroPropList)
{
    BattleMapLayer* layer = new BattleMapLayer();
    if(layer && layer->init(battleID,heroPropList))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}
bool BattleMapLayer::init(int battleID,Vector<DictAvatarProp*>* heroPropList)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        
        m_stageBattleID = battleID;
        this->isAbleGuiding = false;
        m_bloodBottle = GlobalInfo::getInstance()->bloodBottle;
        m_totalBloodBottle = m_bloodBottle;
        _heroPropList = heroPropList;
        this->m_nowReviceCount = 0;
        DictBattleReborn* data = DictBattleRebornManager::getInstance()->getData(GlobalInfo::getInstance()->vipLevel);
        this->setBattleReborn(data);
        
        DictBattlePotion* battlePotion = DictBattlePotionManager::getInstance()->getData(GlobalInfo::getInstance()->vipLevel);
        m_totalBuyBloodCount = battlePotion ? battlePotion->potionTimes : 0;
        this->m_buyBloodCount = 0;
        
        m_winSize = SDResource.size;
        m_winSize.width = m_winSize.width / GlobalInfo::getInstance()->m_mapScale ;
        this->isAnimation = false;
        m_mapContainer = Node::create();
        m_mapContainer->setAnchorPoint(Point::ZERO);
        this->addChild(m_mapContainer,0);
        setBackground();
   
        bref = true;
    } while (false);
    return bref;
}
void BattleMapLayer::setBackground()
{
  

    m_scaleX =  GlobalInfo::getInstance()->screenScaleX * GlobalInfo::getInstance()->m_mapScale ;
    string background = "";
    string resource = "";
    if(GlobalInfo::getInstance()->battleType == kBattleType_MingZhanYi)
    {
        DictStageBattle* stageBattle = DictStageBattleManager::getInstance()->getData(this->m_stageBattleID);
        _battleMode = stageBattle->LayerType == DictStageBattleLayerTypeEnumShip ? kBattleModeShip : GlobalInfo::getInstance()->battleMode;
        background = stageBattle->background;
        resource = stageBattle->mapResource;
        this->m_victoryTime = stageBattle->victoryTime;
        isTimeWinMode = this->m_victoryTime > 0;
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleTYPe_SanGuoWushuan)
    {
        DictMusouBattle* musouBattle = DictMusouBattleManager::getInstance()->getData(this->m_stageBattleID);
        _battleMode = musouBattle->LayerType == DictStageBattleLayerTypeEnumShip ? kBattleModeShip : GlobalInfo::getInstance()->battleMode;
        background = musouBattle->background;
        resource = musouBattle->mapResource;
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_MingJiangZhuan)
    {
        DictLegendBattle* legendBattle = DictLegendBattleManager::getInstance()->getData(this->m_stageBattleID);
        _battleMode = legendBattle->LayerType == DictStageBattleLayerTypeEnumShip ? kBattleModeShip : GlobalInfo::getInstance()->battleMode;
        background = legendBattle->background;
        resource = legendBattle->mapResource;
        
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_LoginBattle)
    {
        background = "cheng_far";
        resource = "NewGuide";
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_TestBattle || GlobalInfo::getInstance()->battleType == kBattleType_ArenaBattle)
    {
        background = "cheng_far";
        resource = "arena001";
    }
    
    const char* path=PublicShowUI::getResImgPath(IMG_BATTLE_MAPBG, background.c_str());
    m_backGround = Sprite::create(path);
    m_backGround->setAnchorPoint(Point::ZERO);
    float scaleY = GlobalInfo::getInstance()->getMapScaleValue();
    scaleY = scaleY == 1 ? 1 : .9 * GlobalInfo::getInstance()->screenScaleY;

    m_backGround->setScaleY(scaleY);
    
    m_mapContainer->addChild(m_backGround,0);


    path = PublicShowUI::getResImgPath(IMG_BATTLE_MIDMAP.c_str(),resource.c_str());
    midLayer = TMXTiledMap::create(path);
    midLayer->setAnchorPoint(Point::ZERO);
    midLayer->setScaleY(scaleY);
    m_mapContainer->addChild(midLayer,1);
   
 
    path = PublicShowUI::getResImgPath(IMG_BATTLE_NEARMAP.c_str(),resource.c_str());
    nearLayer = TMXTiledMap::create(path);
    nearLayer->setAnchorPoint(Point::ZERO);
   
    m_mapContainer->addChild(nearLayer,3);
    MapDataManager::getInstance()->setMapData(nearLayer);
  
    
    path = PublicShowUI::getResImgPath(IMG_BATTLE_CLOSEMAP.c_str(),resource.c_str());
    closeLayer = TMXTiledMap::create(path);
  
    m_mapContainer->addChild(closeLayer,4);
    
    MAP_TILED_WIDTH = nearLayer->getTileSize().width;
    MAP_TILED_HEIGHT = nearLayer->getTileSize().height;
    GlobalInfo::getInstance()->map_tiled_width = MAP_TILED_WIDTH;
    GlobalInfo::getInstance()->map_tiled_height = MAP_TILED_HEIGHT;
    
    bigSkillLayer = Node::create();
    bigSkillLayer->setAnchorPoint(Point::ZERO);
    nearLayer->addChild(bigSkillLayer,(int)nearLayer->getChildrenCount() + 1);
   
    sceneEffecdtLayer = Node::create();
    sceneEffecdtLayer->setAnchorPoint(Point::ZERO);
    nearLayer->addChild(sceneEffecdtLayer,(int)nearLayer->getChildrenCount() + 1);
    
    fightObjLayer = Node::create();
    fightObjLayer->setAnchorPoint(Point::ZERO);
    nearLayer->addChild(fightObjLayer,(int)nearLayer->getChildrenCount() + 1);
    
    skillEffectLayer = SkillEffectLayer::create(nearLayer, NULL);
    skillEffectLayer->setAnchorPoint(Point::ZERO);
    nearLayer->addChild(skillEffectLayer,(int)nearLayer->getChildrenCount() + 1);
    
    
   
    
    Size size = midLayer->getContentSize();
    m_mapContainer->setContentSize(size);
    m_mapContainer->setScale(m_scaleX);
    size.width *= m_scaleX;
    size.height *= m_scaleX;
    m_mapContainer->setContentSize(size);
    HeroAIManager::getInstance()->setMapLayer(nearLayer);
    HeroAIManager::getInstance()->_mapWidth = _mapWidth = nearLayer->getMapSize().width * MAP_TILED_WIDTH ;
    HeroAIManager::getInstance()->_mapHeight = _mapHeight = nearLayer->getMapSize().height * MAP_TILED_HEIGHT ;
    MonsterAIManager::getInstance()->_mapWidth = _mapWidth;
    MonsterAIManager::getInstance()->_mapHeight = _mapHeight;
    this->setContentSize(size);
    
    
}
void BattleMapLayer::setPlayerBorn()
{
    m_totalHealth = 0;
    m_curHealth = 0;
    HeroHeadListLayer::getInstance()->clear();
    _heroList->clear();
    TMXObjectGroup* group = nearLayer->getObjectGroup("hero");
   
    DictAvatarProp* heroProp = NULL;
    ValueVector vector = group->getObjects();
    Hero* hero = NULL;
    int wayNumber = 1;
    bool isMainHero = false;
    Hero* mainHero = NULL;
    for(auto object : vector)
    {
        ValueMap& dict = object.asValueMap();
        Point cp = Point(dict.at("x").asFloat(),dict.at("y").asFloat() );
//        wayNumber =  MapDataManager::getInstance()->getWayNumberByPoint(Point(int(cp.x / MAP_TILED_WIDTH),int((_mapHeight - cp.y)/MAP_TILED_HEIGHT)));
        isMainHero = false;
        if(wayNumber > _heroPropList->size())
        {
            break;
        }
        if(GlobalInfo::getInstance()->battleType == kBattleType_TestBattle || GlobalInfo::getInstance()->battleType == kBattleType_ArenaBattle)
        {
            isMainHero = wayNumber == 1;
            if(wayNumber > _heroPropList->size())
            {
                break;
            }
            heroProp = _heroPropList->at(wayNumber - 1);
        }
        else
        {
            log("wayNumbe = %d",wayNumber);
            if(wayNumber == 1)
            {
                heroProp = _heroPropList->at(1);
            }
            else if(wayNumber == 2)
            {
                heroProp = _heroPropList->at(0);
                isMainHero = true;
            }
            else if(wayNumber == 3)
            {
                heroProp = _heroPropList->at(2);
            }
        }
    
         wayNumber++;
        if(heroProp->id == 0)
        {
            continue;
        }
       
        hero = Hero::create(heroProp->dictID);
        hero->setScale(GlobalInfo::getInstance()->m_avatarScale);
        hero->m_actionFinishedCallBack = NULL;
        hero->_isMainHero = isMainHero;
        hero->isShowBlood = false;
        if(hero->_isMainHero)
        {
            mainHero = hero;
        }
        hero->_wayNumber = wayNumber;
   
        hero->setBaseAvatarProp(heroProp);
        hero->setAvatarProp(heroProp->clone());
        hero->_avatarTeam = AVATAR_TEAM_LEFT;
        hero->m_actionAttackCallBack = CC_CALLBACK_1(BattleMapLayer::onHeroSkillAttackCallBack, this);
        hero->_taskState = kTaskStateGuard;//默认为守卫状态
        hero->walkWithDirection(Point(1,0), true);
        hero->setPositionY(cp.y);
        MoveTo* moveto = MoveTo::create(1.5, cp);
        CallFuncN* callBack = CallFuncN::create(CC_CALLBACK_1(BattleMapLayer::onPlayerPosition, this));
        hero->runAction(Sequence::create(moveto,callBack, NULL));
        
//        hero->setPosition(cp.x, cp.y);
         hero->_destinatsionPostion = cp;
        
        hero->_warningRange = hero->getDictHero()->sight * GlobalInfo::getInstance()->m_avatarScale * MAP_TILED_WIDTH ;
        hero->_followMainHeroDistance = hero->_wayNumber * 4 * GlobalInfo::getInstance()->m_avatarScale * MAP_TILED_WIDTH;
        
        hero->setAnchorPoint(Point(.2,0));
        hero->_baseSpeed = hero->getDictHero()->moveSpeed * GlobalInfo::getInstance()->m_avatarScale;
        hero->_walkSpeed = hero->_baseSpeed ;
        hero->setUID(heroProp->id);
         hero->_totalHitPoints = hero->getAvatarProp()->health;
  
        _heroList->pushBack(hero);
        fightObjLayer->addChild(hero,5000 - hero->getPositionY());
        HeroHeadListLayer::getInstance()->addHero(hero);
         onAvatarPassSkill(hero);
    }

    m_starProgress = m_curHealth / m_totalHealth;

    HeroHeadListLayer::getInstance()->updateBloodbottle(m_bloodBottle);
    this->changeMainHero(mainHero);
    m_isLeft = mainHero->isLeft;
    m_Hero->walkWithDirection(Point(1,0), true);

}
void BattleMapLayer::onPlayerPosition(Ref* target)//英雄就位
{
    Hero* hero = (Hero*)target;
    hero->idle();
    if(hero->_isMainHero)
    {
        StoryTalkManager::getInstance()->onStageBattleStart(this->m_stageBattleID);
    }
    if(GlobalInfo::getInstance()->battleMode != kBattleModeHeroRun)
    {
         broadMsg(CUSTOM_SHOW_SIMPLEPAD);
        broadMsg(CUSTOM_SHOW_MAPREOURCE);
    }
   
}
void BattleMapLayer::onAvatarPassSkill(Avatar* target)
{
    target->usePassSkill();
}
Hero* BattleMapLayer::getMainHero()
{
    return m_Hero;
}
//void BattleMapLayer::onHeroDashCompleted(Hero* hero)
//{
//    ActionState state = hero->_preActionState;
//    if(state == kActionStateAttack1)
//    {
//        if(this->m_attackClickCount > 1)
//        {
//            this->attack2();
//        }
//        
//        else
//        {
//            hero->onActionCompleted();
//        }
//    }
//    else if(state == kActionStateAttack2)
//    {
//        if(this->m_attackClickCount > 2)
//        {
//            this->attack3();
//        }
//        
//        else
//        {
//            hero->onActionCompleted();
//        }
//    }
//    else if(state == kActionStateAttack3)
//    {
//        if(this->m_attackClickCount > 3)
//        {
//            this->attack4();
//        }
//        
//        else
//        {
//            hero->onActionCompleted();
//        }
//    }
//    else if(state == kActionStateAttack4)
//    {
//        if(this->m_attackClickCount > 4)
//        {
//            this->attack5();
//            m_attackClickCount = 0;
//        }
//        
//        else
//        {
//            hero->onActionCompleted();
//        }
//    }
//    else
//    {
//         hero->onActionCompleted();
//    }
//
//}
void BattleMapLayer::onHeroActionFinished(Ref* hero)
{

     if(!m_Hero)
     {
         return;
     }
    
    Hero* target = (Hero*)hero;
     NewPlayerGuild::getInstance()->onMainHeroActionEnded();
//    log("动作完成 action state==%d m_attackClickCount=%d",target->getActionState(),m_attackClickCount);
    switch (target->getActionState()) {
        case kActionStateAttack1:
            
            if(this->m_attackClickCount > 1)
            {
                this->attack2();
            }
            
            else
            {
               m_Hero->onActionCompleted();
            }
            break;
        case kActionStateAttack2:
           
            if(this->m_attackClickCount > 2)
            {
                this->attack3();
            }
            
            else
            {
                m_Hero->onActionCompleted();
            }
            break;
        case kActionStateAttack3:
           
            if(this->m_attackClickCount > 3)
            {
                this->attack4();
            }
            
            else
            {
                m_Hero->onActionCompleted();
            }
            break;
        case kActionStateAttack4:
          
            if(this->m_attackClickCount > 4)
            {
                this->attack5();
                 m_attackClickCount = 0;
            }
           
            else
            {
                m_Hero->onActionCompleted();
            }
            break;
        
        case kActionStateJump:
        case kActionStateDown:
            if(NewPlayerGuild::getInstance()->getNowData() && NewPlayerGuild::getInstance()->getNowData()->id == 4)
            {
                NewPlayerGuild::getInstance()->next();
            }
            else
            {
                m_Hero->onActionCompleted();
            }
            break;
    
        default:
            if(!m_Hero->isPauseState())
            {
                if(!NewPlayerGuild::getInstance()->isInActionTeaching())
                {
                     m_Hero->onActionCompleted();
                }
               
            }
            
            m_attackClickCount = 0;
            break;
    }
}
void BattleMapLayer::onTargetFlashMove(Avatar* target)
{
    int skillID = 0;
    Hero* hero = NULL;
    Monster* monster = NULL;
    if(target->_avatarType == AVATAR_TYPE_HERO)
    {
        hero = (Hero*)target;
    }
    else if(target->_avatarType == AVATAR_TYPE_MONSTER)
    {
         monster = (Monster*)target;
    }
    switch (target->getActionState())
    {
        case kActionStateAttack1:
            skillID = hero ? hero->getDictHero()->skill1 : monster->getDictMonster()->skill1;
            break;
        case kActionStateAttack2:
            skillID = hero ? hero->getDictHero()->skill2 : monster->getDictMonster()->skill2;
            break;
        case kActionStateAttack3:
            skillID = hero ? hero->getDictHero()->skill3 : monster->getDictMonster()->skill3;
            break;
        case kActionStateAttack4:
            skillID = hero ? hero->getDictHero()->skill4 : monster->getDictMonster()->skill4;
            break;
        case kActionStateAttack5:
           skillID = hero ? hero->getDictHero()->skill5 : monster->getDictMonster()->skill5;
            break;
        case kActionStateJumpAttact:
            skillID = hero ? hero->getDictHero()->skill6 : monster->getDictMonster()->skill6;
            break;
        case kActionStateSkill1:
            skillID = hero ? hero->getDictHero()->skill7 : monster->getDictMonster()->skill7;
            break;
        case kActionStateSkill2:
            skillID = hero ? hero->getDictHero()->skill8 : monster->getDictMonster()->skill8;
            break;
        case kActionStateSkill3:
            skillID = hero ? hero->getDictHero()->skill9 : monster->getDictMonster()->skill9;
            break;
    
            break;
            break;
        default:
            break;
    }
    if(target->getIsDashing())
    {
          skillID = target->_dashSkillID;
    }
    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(skillID);
    if(dictSkill)
    {
        dictSkill->flashMove *= GlobalInfo::getInstance()->m_avatarScale;
        target->onFlashMove(dictSkill);
    }
}
void BattleMapLayer::onFocusToEnemy(Avatar* self)
{
    pauseBattle();
    int num = abs(atoi(self->_frameParam.c_str()));
    num = self->isLeft ? num : -num;
    num *= GlobalInfo::getInstance()->m_avatarScale;
    Point cp = Point(num,0);
    MoveBy* move = MoveBy::create(.2, cp);
  
    fightObjLayer->runAction(move);

}
void BattleMapLayer::onFocusToSelf(Avatar* target)
{
    pauseBattle();
    int num = abs(atoi(target->_frameParam.c_str()));
    num *= GlobalInfo::getInstance()->m_avatarScale;
    if(target->isLeft)
    {
        num = -num;
    }
     Point cp = Point(num,0);
    MoveBy* move = MoveBy::create(.2, cp);
    
    fightObjLayer->runAction(move);
}
void BattleMapLayer::onFocusUp(Avatar* target)
{
    pauseBattle();
    int num = abs(atoi(target->_frameParam.c_str()));
    num *= GlobalInfo::getInstance()->m_avatarScale;
    Point cp = Point(0,-num);
    MoveBy* move = MoveBy::create(.2, cp);
    fightObjLayer->runAction(move);
}
void BattleMapLayer::onFocusDown(Avatar* target)
{
    pauseBattle();
    int num = abs(atoi(target->_frameParam.c_str()));
    num *= GlobalInfo::getInstance()->m_avatarScale;
    Point cp = Point(0,num);
    MoveBy* move = MoveBy::create(.2, cp);
    fightObjLayer->runAction(move);
}
void BattleMapLayer::onFocusReset(Avatar* target)
{

    Point cp = Point(0,0);
    fightObjLayer->setPosition(cp);
    
    Director::getInstance()->getScheduler()->setTimeScale(_frameInit);
}
inline void BattleMapLayer::onMonsterAttackCallBack(Ref* monster)
{
    Hero* target = (Hero*)monster;
    int skillid = 0;
    switch (target->getActionState())
    {
        case kActionStateAttack1:
            skillid = target->getAvatarProp()->type == AVATAR_TYPE_HERO ? target->getDictHero()->skill1 : ((Monster*)target)->getDictMonster()->skill1;
            
            break;
        case kActionStateAttack2:
            skillid = target->getAvatarProp()->type == AVATAR_TYPE_HERO ? target->getDictHero()->skill2 : ((Monster*)target)->getDictMonster()->skill2;
            
            break;
        case kActionStateAttack3:
            skillid = target->getAvatarProp()->type == AVATAR_TYPE_HERO ? target->getDictHero()->skill3 : ((Monster*)target)->getDictMonster()->skill3;
            break;
        case kActionStateAttack4:
            skillid = target->getAvatarProp()->type == AVATAR_TYPE_HERO ? target->getDictHero()->skill4 : ((Monster*)target)->getDictMonster()->skill4;
            
            break;
        case kActionStateAttack5:
            skillid = target->getAvatarProp()->type == AVATAR_TYPE_HERO ? target->getDictHero()->skill5 : ((Monster*)target)->getDictMonster()->skill5;
            
            break;
            
        case kActionStateJumpAttact:
            skillid = target->getAvatarProp()->type == AVATAR_TYPE_HERO ? target->getDictHero()->skill6 : ((Monster*)target)->getDictMonster()->skill6;
            
            break;
        case kActionStateSkill1:
            skillid = target->getAvatarProp()->type == AVATAR_TYPE_HERO ? target->getDictHero()->skill7 : ((Monster*)target)->getDictMonster()->skill7;
            
            break;
        case kActionStateSkill2:
            skillid = target->getAvatarProp()->type == AVATAR_TYPE_HERO ? target->getDictHero()->skill8 : ((Monster*)target)->getDictMonster()->skill8;
            break;
        case kActionStateSkill3:
            
            break;
            
            break;
        default:
            if(target->_frameParam.size())
            {
                skillid = atoi(target->_frameParam.c_str());;
            }
          
            break;
    }
    if(skillid)
    {
        onAvatarUseSkill(target,skillid,TEAM_TYPE_OTHER);
    }
   
}
void BattleMapLayer::onEatBlood()
{
    if(m_startTime <= 0)
    {//战斗没开始呢
        return;
    }
    if(this->m_bloodBottle > 0)
    {
        
        if(m_buyBloodCount < this->m_totalBuyBloodCount)
        {
            m_buyBloodCount ++;
//           扣元宝吃血瓶 去掉了
//            BattleEatBloodMsg* msg = new BattleEatBloodMsg(m_buyBloodCount);
//            NetworkDataProcessing::getInstance()->sendMessage(msg);
//            msg = NULL;
            if(m_Hero && m_Hero->getAvatarProp()->health > 0)
            {//已经死了。不能再加血了
                onHeroBloodReset();
            }
     
        }
        else
        {
            NoticeManager::getInstance()->showNotice("已达到最大补血次数，升级vip可以增加次数");
        }
   
    }
    else
    {
        NoticeManager::getInstance()->showNotice("血瓶不足，请到商城购买");
    }
  
}
void BattleMapLayer::onHeroBloodReset()
{

    this->m_bloodBottle--;
    if(m_bloodBottle <= 0)
    {
        m_bloodBottle = 0;
    }
    this->m_curHealth = m_Hero->getBaseAvatarProp()->health;
    m_Hero->getAvatarProp()->health = m_Hero->getBaseAvatarProp()->health;
    
    HeroHeadListLayer::getInstance()->updateBloodbottle(m_bloodBottle);
    HeroHeadListLayer::getInstance()->setBlood(m_curHealth, m_totalHealth);
    broadMsg(CUSTOM_HIDE_HEALTHWARNING);
    
    for(Hero* hero : * _heroList)
    {
        hero->getAvatarProp()->health = hero->getBaseAvatarProp()->health;
        hero->addEffect("xuepingren");
    }
    HeroHeadListLayer::getInstance()->resetBlood();
}
void BattleMapLayer::onHeroSkillAttackCallBack(Ref* hero)//技能攻击
{
   
    Hero* target = (Hero*)hero;
    log("%s开始了攻击＝＝%d",target->getDictHero()->name.c_str(),target->getActionState());
    switch (target->getActionState())
    {
        case kActionStateAttack1:
            onAvatarUseSkill(target,target->getDictHero()->skill1,TEAM_TYPE_SELF);
            break;
        case kActionStateAttack2:
            onAvatarUseSkill(target,target->getDictHero()->skill2,TEAM_TYPE_SELF);
            break;
        case kActionStateAttack3:
            onAvatarUseSkill(target,target->getDictHero()->skill3,TEAM_TYPE_SELF);
            break;
        case kActionStateAttack4:
            onAvatarUseSkill(target,target->getDictHero()->skill4,TEAM_TYPE_SELF);
            break;
        case kActionStateAttack5:
            onAvatarUseSkill(target,target->getDictHero()->skill5,TEAM_TYPE_SELF);
            break;
        case kActionStateJumpAttact:
        case kActionStateJump:
        case kActionStateDown:
            onAvatarUseSkill(target,target->getDictHero()->skill6,TEAM_TYPE_SELF);
            break;
        case kActionStateSkill1:
            onAvatarUseSkill(target,target->getDictHero()->skill7,TEAM_TYPE_SELF);
            break;
        case kActionStateSkill2:
            onAvatarUseSkill(target,target->getDictHero()->skill8,TEAM_TYPE_SELF);
            break;
        case kActionStateSkill3:
            onAvatarUseSkill(target,target->getDictHero()->skill9,TEAM_TYPE_SELF);
            break;
        case kActionStateSkill4:
            onAvatarUseSkill(target,target->getDictHero()->skill10,TEAM_TYPE_SELF);
            break;
        default:
            if(target->_frameParam.size())
            {
                int skillid = atoi(target->_frameParam.c_str());;
                if(skillid)
                {
                     onAvatarUseSkill(target,skillid,TEAM_TYPE_SELF);
                }
               
            }
            break;
    }
}

void BattleMapLayer::onAvatarUseSkill(Avatar* target,int skillID,int team)
{
  
    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(skillID);
    if(!dictSkill)
    {
        return;
    }
 
    skillEffectLayer->addSkillEffect(target, skillID, team);
                                       
    if(dictSkill->heroShiftForward)
    {
        target->_dashSkillID = skillID;
        target->dash(dictSkill->heroShiftForward * MAP_TILED_WIDTH * GlobalInfo::getInstance()->m_avatarScale,dictSkill->moveTime);
    }
    else if(dictSkill->heroShiftBackward)
    {
        target->_dashSkillID = skillID;
        target->dash(dictSkill->heroShiftBackward * MAP_TILED_WIDTH * GlobalInfo::getInstance()->m_avatarScale,dictSkill->moveTime);
    }
}
void BattleMapLayer::onSkillAttackCallBack(EventCustom* event)
{
   
    SkillAttackData* attackData = (SkillAttackData*)event->getUserData();
    if(attackData->m_team == TEAM_TYPE_SELF)
    {
        if(attackData->getDictSkill())
        {
            if(attackData->getDictSkill()->target == DictSkillTargetEnumEnemy)
            {
            
                 onHeroAttack(attackData);
            }
            else if(attackData->getDictSkill()->target == DictSkillTargetEnumAlly)
            {//友方
                onMonsterAttack(attackData);
            }
            else if(attackData->getDictSkill()->target == DictSkillTargetEnumParty)
            {//对友
                onMonsterAttack(attackData);
            }
            else if(attackData->getDictSkill()->target == DictSkillTargetEnumSelf)
            {//自身
                onAttackSelf(attackData);
            }
            else if(attackData->getDictSkill()->target == DictSkillTargetEnumLeastHealth)
            {//血量最少
                onHeroAttackMinBlood(attackData);
            }
            else if(attackData->getDictSkill()->target == DictSkillTargetEnumTotal)
            {//敌我所有
    
                onHeroAttack(attackData);
                onMonsterAttack(attackData);
            }
           
        }
       
    }
    else if(attackData->m_team == TEAM_TYPE_OTHER)
    {
        if(attackData->getDictSkill()->target == DictSkillTargetEnumEnemy)
        {
            onMonsterAttack(attackData);
        }
        else if(attackData->getDictSkill()->target == DictSkillTargetEnumAlly)
        {//友方
            onHeroAttack(attackData);
        }
        else if(attackData->getDictSkill()->target == DictSkillTargetEnumParty)
        {//对友
            onHeroAttack(attackData);
        }
        else if(attackData->getDictSkill()->target == DictSkillTargetEnumSelf)
        {//自身
            onAttackSelf(attackData);
        }
        else if(attackData->getDictSkill()->target == DictSkillTargetEnumLeastHealth)
        {//血量最少
            onMonsterAttackMinBlood(attackData);
        }
        else if(attackData->getDictSkill()->target == DictSkillTargetEnumTotal)
        {//敌我所有
            onHeroAttack(attackData);
            onMonsterAttack(attackData);
        }
    }
  
}
void BattleMapLayer::loadResource()
{
 
     m_loaded = 0;
    const char* path = "";
   
    //英雄资源
    for(DictAvatarProp* data : * _heroPropList)
    {
        
        DictHero* dictHero = DictHeroManager::getInstance()->getData(data->dictID);
        if(dictHero)
        {
            path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictHero->resource.c_str());
            if(!loadingList.at(path))
            {
                 m_resourceTotal += 1;
                ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(BattleMapLayer::onDataLoaded));
                loadingList.insert(path, __Bool::create(true));
                 log("loadpath===%s m_resourceTotal=%d",path,m_resourceTotal);
            }
        }
        
    }
    if(GlobalInfo::getInstance()->battleType == kBattleType_TestBattle || GlobalInfo::getInstance()->battleType == kBattleType_ArenaBattle)
    {
        Vector<DictAvatarProp*>* rightList = PlayerDataManager::getInstance()->getRightHeroList();
        for(DictAvatarProp* data : * rightList)
        {
            if(data->type == AVATAR_TYPE_HERO)
            {
                DictHero* dictHero = DictHeroManager::getInstance()->getData(data->dictID);
                if(dictHero)
                {
            
                    path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictHero->resource.c_str());
                    
                    if(!loadingList.at(path))
                    {
                        m_resourceTotal += 1;
                        ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(BattleMapLayer::onDataLoaded));
                        loadingList.insert(path, __Bool::create(true));
                          log("loadpath===%s m_resourceTotal=%d",path,m_resourceTotal);
                    }
                    
                  
                    
                }
            }
            else
            {
                DictMonster* dictMonster = DictMonsterManager::getInstance()->getData(data->dictID);
                if(dictMonster)
                {
                
                    path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictMonster->resource.c_str());
                    
                    if(!loadingList.at(path))
                    {
                        m_resourceTotal += 1;
                        ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(BattleMapLayer::onDataLoaded));
                        loadingList.insert(path, __Bool::create(true));
                          log("loadpath===%s m_resourceTotal=%d",path,m_resourceTotal);
                    }
    
                  
                    
                }
            }
            
        }
        loadSceneEffect(nearLayer);
        loadSceneEffect(closeLayer);
        loadSceneEffect(midLayer);
        
        return;
    }
    
    TMXObjectGroup* group = nearLayer->getObjectGroup("monster");
    DictStageBattleMonster* battleMonster = NULL;
    DictMusouBattleMonster* musouMonster =  NULL;
    
    ValueVector vector = group->getObjects();
   
    m_resourceTotal = vector.size();
 
    // 怪物资源
   
    DictMonster* dictMoster = NULL;
  
    int battleMonsterID = 0;
    int monsterID = 0;
    bool hasBoss = false;
    for(auto object : vector)
    {
        monsterID = 0;
        ValueMap& dict = object.asValueMap();
        battleMonsterID = dict.at("stagebattlemonster").asInt();

        if(GlobalInfo::getInstance()->battleType == kBattleTYPe_SanGuoWushuan)
        {
            musouMonster = DictMusouBattleMonsterManager::getInstance()->getData(battleMonsterID);
            monsterID = musouMonster->monsterId;
      
            if(musouMonster->type == DictMonsterTypeEnumBossMonster)
            {
                hasBoss = true;
            }
        }
        else if(GlobalInfo::getInstance()->battleType == kBattleType_MingZhanYi)
        {
            battleMonster = DictStageBattleMonsterManager::getInstance()->getData(battleMonsterID);
            monsterID = battleMonster->monsterId;

            if(battleMonster->type == DictMonsterTypeEnumBossMonster)
            {
                hasBoss = true;
            }
        }
        else if(GlobalInfo::getInstance()->battleType == kBattleType_LoginBattle)
        {
            battleMonster = DictStageBattleMonsterManager::getInstance()->getData(battleMonsterID);
            monsterID = battleMonster->monsterId;
           
            if(battleMonster->type == DictMonsterTypeEnumBossMonster)
            {
                hasBoss = true;
            }
        }
        else if(GlobalInfo::getInstance()->battleType == kBattleType_MingJiangZhuan)
        {
//            DictLegendBattleMonster* legendBattleMonster = DictLegendBattleMonsterManager::getInstance()->getData(battleMonsterID);
            monsterID = battleMonsterID;
             hasBoss = true;
          
        }
        if(monsterID)
        {
            dictMoster = DictMonsterManager::getInstance()->getData(monsterID);
            if(dictMoster)
            {
                   
                path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictMoster->resource.c_str());
                if(!loadingList.at(path))
                {
                     ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(BattleMapLayer::onDataLoaded));
                    loadingList.insert(path, __Bool::create(true));
                    log("dictMosterpath=%s m_resourceTotal=%d",path,m_resourceTotal);
                }
                else
                {
                    --m_resourceTotal;
                }

            }
            else
            {
                --m_resourceTotal;
                log("没这个怪＝＝%d",monsterID);
            }
        }
        
    }
    
    m_resourceTotal++;
    path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, MONSTER_BORN_EFFECT);
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(BattleMapLayer::onDataLoaded));
      log("IMG_SCENE_EFFECT path=%s m_resourceTotal=%d",path,m_resourceTotal);
    
    if(hasBoss)
    {
         m_resourceTotal++;
        path = PublicShowUI::getAvatarPath(IMG_PUBLIC_EFFECT, BOSS_BORN_EFFECT);
        ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(BattleMapLayer::onDataLoaded));
       log("IMG_SCENE_EFFECT path=%s m_resourceTotal=%d",path,m_resourceTotal);
        
        m_resourceTotal++;
        path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, BOSS_DEAD_EFFECT);
        ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(BattleMapLayer::onDataLoaded));
        log("IMG_SCENE_EFFECT path=%s m_resourceTotal=%d",path,m_resourceTotal);
        
        
    }
   
    loadSceneEffect(nearLayer);
    loadSceneEffect(closeLayer);
    loadSceneEffect(midLayer);
}
void BattleMapLayer::loadSceneEffect(TMXTiledMap* mapLayer)
{
    TMXObjectGroup* group = mapLayer->getObjectGroup("effect");
    if(group)
    {
        ValueVector vector = group->getObjects();
         m_resourceTotal += vector.size();
        string effectName = "";
        string path = "";
        for(auto object : vector)
        {
            ValueMap& dict = object.asValueMap();
            effectName = dict.at("name").asString();
            
            path = IMG_BATTLE_BATTLESCENE_PATH;
            path = path + "effect/" + effectName + "/" + effectName +".ExportJson";
            ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(BattleMapLayer::onDataLoaded));
            log("map effect path=%s m_resourceTotal=%d",path.c_str(),m_resourceTotal);
            
        }
    }
}
void BattleMapLayer::setMonsterBorn()//怪物出生点
{
    _blockMonsterList->removeAllObjects();
    _bornMonsterList->clear();
    _tureWaves = 1;
    float mapHeight = nearLayer->getMapSize().height * MAP_TILED_HEIGHT;
    _monsterList->removeAllObjects();
    int monsterUid  = 50;
    TMXObjectGroup* group = nearLayer->getObjectGroup("monster");
    DictStageBattleMonster* battleMonster = NULL;
    DictMusouBattleMonster* musouMonster = NULL;
    DictLegendBattleMonster* legendBattleMonster = NULL;
    DictAvatarProp* monsterProp = NULL;//DictMonsterPropManager::getInstance()->
    ValueVector vector = group->getObjects();
    Monster* monster = NULL;
    int battleMonsterID = 0;
    int monsterID = 0;
    int level = 0;
    int aiID = 0;
    DictMonster* dictMonster = NULL;

    for(auto object : vector)
    {
        aiID = 0;
        ValueMap& dict = object.asValueMap();
        battleMonsterID = dict.at("stagebattlemonster").asInt();
      
        if(GlobalInfo::getInstance()->battleType == kBattleType_MingZhanYi)
        {
            battleMonster = DictStageBattleMonsterManager::getInstance()->getData(battleMonsterID);
            if(!battleMonster)
            {
                continue;
            }
            monsterID = battleMonster->monsterId;
            level = GlobalInfo::getInstance()->stageMode == StageMode::kStageModeCommon ? battleMonster->monsterLevel : battleMonster->monsterLevelElite;
             monsterProp = DictManager::getStageBattleMonsterProp(battleMonsterID,GlobalInfo::getInstance()->stageMode == StageMode::kStageModeBest);
             monsterProp->level = level;
            aiID = battleMonster->aiID;
        }
        else if(GlobalInfo::getInstance()->battleType == kBattleTYPe_SanGuoWushuan)
        {
            musouMonster = DictMusouBattleMonsterManager::getInstance()->getData(battleMonsterID);
            monsterID = musouMonster->monsterId;
            level =   musouMonster->monsterLevel ;
             monsterProp = DictManager::getDictMonsterProp(monsterID,level);
            aiID = musouMonster->aiID;
        }
        else if(GlobalInfo::getInstance()->battleType == kBattleType_LoginBattle)
        {
            battleMonster = DictStageBattleMonsterManager::getInstance()->getData(battleMonsterID);
            if(!battleMonster)
            {
                continue;
            }
            monsterID = battleMonster->monsterId;
            level = battleMonster->monsterLevel;
            level = GlobalInfo::getInstance()->stageMode == StageMode::kStageModeCommon ? battleMonster->monsterLevel : battleMonster->monsterLevelElite;
             monsterProp = DictManager::getDictMonsterProp(monsterID,level);
        }
        else if(GlobalInfo::getInstance()->battleType == kBattleType_MingJiangZhuan)
        {
            legendBattleMonster = DictLegendBattleMonsterManager::getInstance()->getData(battleMonsterID);
            if(!legendBattleMonster)
            {
                return;
            }
            monsterID = battleMonsterID;
            level = GlobalInfo::getInstance()->famouseBossLevel;
            
             monsterProp = DictManager::getDictMonsterProp(monsterID,level);
             aiID = legendBattleMonster->aiID;
        }
        
       
        dictMonster = DictMonsterManager::getInstance()->getData(monsterID);
        if(!dictMonster)
        {
            continue;
        }
        
       
//        monsterProp->health = 999999;
        switch (dictMonster->type)
        {
            case DictMonsterTypeEnumBlockMonster:
            case DictMonsterTypeEnumStageRewardMonster:
                monster =  BlockMonster::create(battleMonster->monsterId);
                break;
            
            default:
                monster = Monster::create(monsterID);
                break;
        }
        monster->_battleMonsterID = battleMonsterID;
        monster->aiID = aiID;
        monster->_taskState = kTaskStateGuard;//默认为守卫状态
        monster->setBaseAvatarProp(monsterProp);
        monster->_avatarTeam = AVATAR_TEAM_RIGHT;
        bossBlood = GlobalInfo::getInstance()->famouseBossBlood;
        
        monsterProp->health  =   GlobalInfo::getInstance()->battleType == kBattleType_MingJiangZhuan ?  bossBlood :monsterProp->health;
        monster->_totalHitPoints = monsterProp->health;
        monster->setAvatarProp(monsterProp->clone());
        monster->m_actionAttackCallBack = CC_CALLBACK_1(BattleMapLayer::onMonsterAttackCallBack, this);
        monster->setScale(GlobalInfo::getInstance()->m_avatarScale);
        monster->setAnchorPoint(Point(.2,0));
        if(GlobalInfo::getInstance()->battleType == kBattleType_MingJiangZhuan)
        {
            monster->_baseSpeed  = legendBattleMonster->speed;
            monster->_warningRange = legendBattleMonster->sight * MAP_TILED_WIDTH;
            monster->_followMainHeroDistance = legendBattleMonster->range * MAP_TILED_WIDTH ;
            monster->_isBoss = legendBattleMonster->type == DictMonsterTypeEnumBossMonster ;
        }
        else
        {
            monster->_baseSpeed = battleMonster ? battleMonster->speed : musouMonster->speed;
            monster->_warningRange = battleMonster ? battleMonster->sight * MAP_TILED_WIDTH : musouMonster->sight * MAP_TILED_WIDTH;
            monster->_followMainHeroDistance = battleMonster ? battleMonster->range * MAP_TILED_WIDTH : musouMonster->range * MAP_TILED_WIDTH;
            monster->_isBoss = battleMonster ? battleMonster->type == DictMonsterTypeEnumBossMonster : musouMonster->type == DictMonsterTypeEnumBossMonster;
        }
        
       
        monster->_baseSpeed = monster->_baseSpeed * GlobalInfo::getInstance()->m_avatarScale;
        monster->_walkSpeed = monster->_baseSpeed;
        monster->_warningRange *= GlobalInfo::getInstance()->m_avatarScale;
        monster->_followMainHeroDistance *= GlobalInfo::getInstance()->m_avatarScale;
       
        monster->setUID(monsterUid++);

        
        Point cp = Point(dict.at("x").asFloat(),dict.at("y").asFloat());
        monster->_destinatsionPostion = cp;
        monster->setPosition(cp.x,cp.y);
        
        cp.x = int(cp.x / MAP_TILED_WIDTH);//格坐标
        cp.y = int((mapHeight - cp.y)/MAP_TILED_HEIGHT);
        
        
        if(dictMonster->type == DictMonsterTypeEnumBlockMonster)
        {
            ((BlockMonster*)monster)->_gridBlockPoint = cp;
            _blockMonsterList->addObject(monster);
        }
        
        monster->_wayNumber = MapDataManager::getInstance()->getWayNumberByPoint(cp);
        auto iter = dict.find("enterway");
        if (iter != dict.end())
        {
             monster->_enterWay = dict.at("enterway").asInt();
        }
        else
        {
            monster->_enterWay = EnterWayState::kEnterWayCommon;
        }
        
        iter = dict.find("block");
        if (iter != dict.end())
        {
            monster->_blockNum = dict.at("block").asInt();
            
        }
        else
        {
            monster->_blockNum = 1;
        }

        iter = dict.find("touch");
        if (iter != dict.end())
        {
            monster->_touch = dict.at("touch").asInt();
        }
        iter = dict.find("turn");
        if (iter != dict.end())
        {
            monster->_turnWaves = dict.at("turn").asInt();
        }
        _monsterList->addObject(monster);
        if(monster->_enterWay == EnterWayState::kEnterWayCommon && monster->_blockNum == MapDataManager::getInstance()->_nowBlockNum && monster->_turnWaves == _tureWaves)
        {
             fightObjLayer->addChild(monster,5000 - monster->getPositionY());
            _bornMonsterList->pushBack(monster);
           
        }
        
        if(monster->_isBoss)
        {
            BossBloodManager::getInstance()->updateBoss(monster);
        }
      
    }
    MapDataManager::getInstance()->_blockMonsterList = this->_blockMonsterList;
    if(this->hasDelayMonster())
    {
        this->unschedule(schedule_selector(BattleMapLayer::showDelayMonster));
        this->schedule(schedule_selector(BattleMapLayer::showDelayMonster), 1);
    }
   
}
void BattleMapLayer::setTestMonsterBorn()//测试怪出生点
{
    _blockMonsterList->removeAllObjects();
    _bornMonsterList->clear();
    _tureWaves = 1;
    
    _monsterList->removeAllObjects();
    
    TMXObjectGroup* group = nearLayer->getObjectGroup("monster");
    Vector<DictAvatarProp*>* rightList = PlayerDataManager::getInstance()->getRightHeroList();
    DictAvatarProp* heroProp = NULL;
    ValueVector vector = group->getObjects();
    Avatar* monster = NULL;
    int index = 0;
    
    
    for(auto object : vector)
    {
        ValueMap& dict = object.asValueMap();
        Point cp = Point(dict.at("x").asFloat(),dict.at("y").asFloat() );
        if(index >= rightList->size())
        {
            break;
        }
        heroProp = rightList->at(index);
        
        
        if(heroProp->id == 0)
        {
            continue;
        }
        
        monster =  heroProp->type == AVATAR_TYPE_HERO ? (Avatar*)Hero::create(heroProp->dictID) : (Avatar*)Monster::create(heroProp->dictID);
        if(!monster)
        {
            continue;
        }
        monster->isShowBlood = true;
        monster->setScale(GlobalInfo::getInstance()->m_avatarScale);
        monster->m_actionFinishedCallBack = NULL;
       
        monster->_wayNumber = index + 1;
        monster->setBaseAvatarProp(heroProp);
        monster->_avatarTeam = AVATAR_TEAM_RIGHT;
        monster->setAvatarProp(heroProp->clone());
        
        monster->m_actionAttackCallBack = CC_CALLBACK_1(BattleMapLayer::onMonsterAttackCallBack, this);
        monster->_taskState = kTaskStateGuard;//默认为守卫状态
        monster->walkWithDirection(Point(1,0), true);
        monster->setPosition(cp.x,cp.y);
        
        
        monster->_destinatsionPostion = cp;
        
        monster->_warningRange = heroProp->type == AVATAR_TYPE_HERO ? ((Hero*)monster)->getDictHero()->sight : 10;
        monster->_warningRange =  monster->_warningRange * GlobalInfo::getInstance()->m_avatarScale * MAP_TILED_WIDTH;
        
        monster->_followMainHeroDistance = 2 * GlobalInfo::getInstance()->m_avatarScale;
        
        monster->setAnchorPoint(Point(.2,0));
        monster->_baseSpeed = heroProp->type == AVATAR_TYPE_HERO ? ((Hero*)monster)->getDictHero()->moveSpeed : heroProp->walkSpeed;
        monster->_baseSpeed *= GlobalInfo::getInstance()->m_avatarScale;
        monster->_walkSpeed = monster->_baseSpeed ;
        monster->setUID(heroProp->id);
        monster->_totalHitPoints = monster->getAvatarProp()->health;
        monster->isBossShadow = true;
        _monsterList->addObject(monster);
        
        _bornMonsterList->pushBack(monster);
        fightObjLayer->addChild(monster,5000 - monster->getPositionY());
   
        
        
        index ++;
    }
    HeroAIManager::getInstance()->isAutoFight = true;
    MapDataManager::getInstance()->_blockMonsterList = this->_blockMonsterList;
}
void BattleMapLayer::onRePlay()
{
    fightObjLayer->removeAllChildren();
    _monsterList->removeAllObjects();
    _bornMonsterList->clear();
    _heroList->clear();
    HeroHeadListLayer::getInstance()->clear();
    m_Hero = NULL;
    bossComeIsWarning = false;
    onDataLoaded(1);
}
void BattleMapLayer::onDataLoaded(float percent)
{
     m_loaded ++;
    if(popUpLoading && popUpLoading->getParent())
    {
        popUpLoading->setProgressPercent(percent * 100);
       
    }
    log("percent==%f m_loaded=%d,m_resourceTotal=%d",percent,m_loaded,m_resourceTotal);
    
//    if(percent == .85)
//    {
//        log("lsdjfsl");
//    }
    if(m_loaded <  m_resourceTotal || percent < 1)
    {
        return;
    }

    MapDataManager::getInstance()->_nowBlockNum = 1;
    MapDataManager::getInstance()->setBlockLeftPos();
    Dialog::hideLoading();
    fightObjLayer->removeAllChildren();
    setPlayerBorn();
  
    onSetMonsterBorn();
}
void BattleMapLayer::onSetMonsterBorn()
{
    if(GlobalInfo::getInstance()->battleType == kBattleType_TestBattle || GlobalInfo::getInstance()->battleType == kBattleType_ArenaBattle)
    {
        _frameInit = PlayerDataManager::getInstance()->_frameRate;
        setTestMonsterBorn();
        Director::getInstance()->getScheduler()->setTimeScale(_frameInit);
    }
    else
    {
        _frameInit = 1;
        
        setMonsterBorn();
    }
    
    isMonsterInView();
    setSceneEffectBorn();
    MonsterAIManager::getInstance()->setObjectList(_bornMonsterList, _heroList);
    
    HeroAIManager::getInstance()->setMainHero(this->m_Hero);
    HeroAIManager::getInstance()->setObjectList(_bornMonsterList, _heroList);

}
void BattleMapLayer::onEnter()
{
    m_leftTime = 60 * 5;
    BaseLayer::onEnter();
    if(GlobalInfo::getInstance()->battleType == kBattleTYPe_SanGuoWushuan)
    {
        DictMusouBattle * stageBattle = DictMusouBattleManager::getInstance()->getData(m_stageBattleID);
        SoundManager::playBackgroundMusic(stageBattle->battleMusic.c_str());
        m_leftTime = stageBattle->battleTime;
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_MingZhanYi)
    {
        DictStageBattle* stageBattle = DictStageBattleManager::getInstance()->getData(m_stageBattleID);
        SoundManager::playBackgroundMusic(stageBattle->battleMusic.c_str());
        m_leftTime = stageBattle->battleTime;
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_MingJiangZhuan)
    {
        DictLegendBattle* legendBattle = DictLegendBattleManager::getInstance()->getData(m_stageBattleID);
        SoundManager::playBackgroundMusic(legendBattle->battleMusic.c_str());
        m_leftTime = GlobalInfo::getInstance()->famouseLeftSeconds;
    }
    
}
void BattleMapLayer::setSceneEffectBorn()//场景特效出生点
{
    TMXObjectGroup* group = nearLayer->getObjectGroup("effect");
    if(group)
    {
        ValueVector vector = group->getObjects();
        string effectName = "";
        string path = "";
        for(auto object : vector)
        {
            ValueMap& dict = object.asValueMap();
            effectName = dict.at("name").asString();
            
            Armature* armature = Armature::create(effectName);
            armature->setAnchorPoint(Point(.5,.5));
            armature->setScale(GlobalInfo::getInstance()->m_avatarScale);
            armature->setPosition(dict.at("x").asFloat(),dict.at("y").asFloat());
            _sceneEffecctList->pushBack(armature);
        }
    }
    
    group = closeLayer->getObjectGroup("effect");
    if(group)
    {
        ValueVector vector = group->getObjects();
        string effectName = "";
        string path = "";
        for(auto object : vector)
        {
            ValueMap& dict = object.asValueMap();
            effectName = dict.at("name").asString();
            
            Armature* armature = Armature::create(effectName);
            armature->setAnchorPoint(Point(.5,.5));
            armature->setPosition(dict.at("x").asFloat(),dict.at("y").asFloat());
            _sceneEffecctList->pushBack(armature);
        }
    }
    group = midLayer->getObjectGroup("effect");
    if(group)
    {
        ValueVector vector = group->getObjects();
        string effectName = "";
        string path = "";
        for(auto object : vector)
        {
            ValueMap& dict = object.asValueMap();
            effectName = dict.at("name").asString();
            
            Armature* armature = Armature::create(effectName);
            armature->setAnchorPoint(Point(.5,.5));
            armature->setPosition(dict.at("x").asFloat(),dict.at("y").asFloat());
            _midLayerEffectList->pushBack(armature);
        }
    }
    
   
}
void BattleMapLayer::clearResourcePerson()//清除人物资源
{
    
    fightObjLayer->removeAllChildren();
    skillEffectLayer->removeAllChildren();
    _monsterList->removeAllObjects();
     sceneEffecdtLayer->removeAllChildren();
    DictHero* dictHero = DictHeroManager::getInstance()->getData(GlobalInfo::getInstance()->gameRole->mainHeroDictID);
    string path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictHero->resource.c_str());
   
    ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);

    Monster* monster = NULL;
    for(__SetIterator it = this->_monsterList->begin(); it != _monsterList->end();   it++)
    {
        monster = (Monster*)*it;
        path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,monster->getDictMonster()->resource.c_str());
        ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
    }

    for(Hero* hero :* _heroList)
    {
        path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,hero->getDictHero()->resource.c_str());
        ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
    }
    for(Armature* armature : * _sceneEffecctList)
    {
        path = IMG_BATTLE_BATTLESCENE_PATH;
        path = path + "effect/" + armature->getName() + "/" + armature->getName() +".ExportJson";
        ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
//        log(" remove effecPath=%s",path.c_str());
    }
    for(Armature* armature : *_midLayerEffectList)
    {
        path = IMG_BATTLE_BATTLESCENE_PATH;
        path = path + "effect/" + armature->getName() + "/" + armature->getName() +".ExportJson";
        ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);

    }
  
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("");
    ArmatureDataManager::destroyInstance();
  
}
void BattleMapLayer::onExit()
{
    BaseLayer::onExit();
    
}
void BattleMapLayer::onEnterTransitionDidFinish()
{
    
    BaseLayer::onEnterTransitionDidFinish();

    this->popUpLoading = Dialog::showLoading();
    CC_SAFE_RETAIN(popUpLoading);
    
    loadResource();

 
}
void BattleMapLayer::onExitTransitionDidStart()
{

    BaseLayer::onExitTransitionDidStart();
    if(this->m_stageBattleID == GlobalInfo::getInstance()->taskInStageBattle)
    {
        GlobalInfo::getInstance()->taskInStageBattle = 0;
    }
    clearResourcePerson();
    GlobalInfo::getInstance()->isShowStoryTalk = true;
    Director::getInstance()->getActionManager()->removeAllActions();
    MonsterAIManager::destroyInstance();
    HeroAIManager::destroyInstance();
    MapDataManager::destoryInstance();
    StoryTalkManager::destoryInstance();
    
 }
void BattleMapLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
 
}
void BattleMapLayer::onMonsterAttack(SkillAttackData* attackData)//英雄攻击
{
    if(!m_Hero || this->m_isbigSkilling)
    {//大招中不被攻击
        return;
    }
    log(" onHeroAttackonHeroAttack onHeroAttackonHeroAttack");
    Avatar* target = attackData->getTarget();
    DictSkill* useSkill = attackData->getDictSkill();
   
    float damage = 0;
    float hurtCount = 0;//伤害个数
    bool isHurt = false;
    
   
    
    
    for(Hero* hero : * _heroList)
     {
         
         isHurt = avatarIsBomb(hero, attackData);
         if(isHurt)
         {
             if(hurtCount >= useSkill->damageNumber)
             {
                 break;
             }
             hurtCount ++;
             damage = FormulaManager::getHeroAttackDamage(target, hero, attackData);
             
             onHeroHurt(hero,attackData,damage);
         
         }
     }
  
//    if(m_curHealth / m_totalHealth < m_starProgress)
//    {
//        m_starProgress = m_curHealth / m_totalHealth;
//    }
//    if(m_curHealth / m_totalHealth <= .3)
//    {
//        broadMsg(CUSTOM_SHOW_HEALTHWARNING);
//    }
//    else
//    {
//        broadMsg(CUSTOM_HIDE_HEALTHWARNING);
//    }
    

    
}
inline void BattleMapLayer::onHeroHurt(Hero* hero,SkillAttackData* attackData,float damage)
{
    if(hero->getActionState() == kActionStateWin)
    {//胜利不受伤害了。
        return;
    }
    if(GlobalInfo::getInstance()->isGuiding && GlobalInfo::getInstance()->battleType == kBattleType_MingZhanYi)
    {//新手引导中。不能死，策划要求
        if(hero->getAvatarProp()->health <= damage)
        {
            damage = 0;
        }
        if(m_curHealth < 1)
        {
            m_curHealth = 1;
        }
    }
    
    DictSkill* useSkill = attackData->getDictSkill();
    
    
    if(useSkill->soundHit.size())
    {
        SoundManager::playEffectMusic(useSkill->soundHit.c_str());
    }
    
    ActionState _state = hero->getActionState();
    if(hero->hasBuffState(DictBuffTypeEnumSleep))
    {
        damage *= 2;
        hero->removeBuffByType(DictBuffTypeEnumSleep);
    }

    
    if(attackData->buffList.size() > 0)
    {
        bool isbuff = PublicShowUI::getProbability(useSkill->buffOdds);
        if(isbuff)
        {
            for(string buffID : attackData->buffList)
            {
                this->onSkillBuff(hero, attackData, damage,atoi(buffID.c_str()));
            }
            
        }
       
    }
    if(_state == kActionStateJump || _state == kActionStateDown || _state == kActionStatePrePareJumpAttack || _state == kActionStateKnockFly)
    {
        hero->knockFly(damage,attackData->_isCrit,attackData->_isBlock,attackData->_isSkillAttack);
    }
    else if(_state == kActionStateBlock)
    {
         hero->hurtWithDamage(damage,attackData->_isCrit,attackData->_isBlock,attackData->_isSkillAttack);
    }
    else if(useSkill->knockDown)
    {//击倒
        hero->knockDown(damage,attackData->_isCrit,attackData->_isBlock,attackData->_isSkillAttack);
    }
    else if(useSkill->knockFly)
    {//击飞
        
        hero->knockFly(damage,attackData->_isCrit,attackData->_isBlock,attackData->_isSkillAttack);
    }
    else if(useSkill->beatBack)
    {
        Point cp = getTargetPointByTarget(hero,useSkill->beatBack,hero->getPositionX() < attackData->getTarget()->getPositionX());
        cp = hero->getPosition() + cp;
        cp = MapDataManager::getInstance()->positionToSelfPostion(hero,cp);
        hero->knockBack(damage,cp,attackData->_isCrit,attackData->_isBlock,attackData->_isSkillAttack);
    }
    else
    {
        hero->hurtWithDamage(damage,attackData->_isCrit,attackData->_isBlock,attackData->_isSkillAttack);
    }
   
    if(damage && hero->getAvatarProp()->health > 0 && hero->_isMainHero)
    {
        if(hero->getAvatarProp()->health < damage)
        {
            m_curHealth -= hero->getAvatarProp()->health;
        }
        else
        {
            m_curHealth -= damage;
        }
       
        onHeroAddAngry(hero);
    }
//    log("%s 剩余血量==%d",hero->getDictHero()->name.c_str(), hero->getAvatarProp()->health);
     HeroHeadListLayer::getInstance()->onHeroHurt(hero->getUID(),damage);
    if(useSkill->hitResource.size())
    {
        hero->addEffect(useSkill->hitResource.c_str(),useSkill->hitHighShifting);
    }
    log("谁被打了==%s,health==%d",hero->getDictHero()->name.c_str(),hero->getAvatarProp()->health);
//    onHeroDead(hero);
 
  
}
void BattleMapLayer::onHeroDead(Hero* hero)
{
    if(hero->getAvatarProp()->health <= 0)
    {
        MapDataManager::getInstance()->_blockAvatars->erase(hero);//(hero);
    }
    if(m_curHealth <= 0 || hero->getAvatarProp()->health <= 0)
    {
        log("%s死了===",hero->getDictHero()->name.c_str());
        if(hero == m_Hero || hero->_isMainHero)
        {
            this->setNextMainHero();
        }
        
    }
}
void BattleMapLayer::showRebornDialog()//显示复活弹框
{
    if(m_nowReviceCount >= this->_battleReborn->rebornTimes)
    {
        StoryTalkManager::getInstance()->onStageBattleOver(this->m_stageBattleID,false);
        return;
    }
     m_nowReviceCount++;
    broadMsg(CUSTOM_CAMERA_RESET);
    RebornPanel::show(this->m_nowReviceCount);
   
}
void BattleMapLayer::onHeroReBorn(EventCustom* msg)
{
    Dialog::showServerLoading(3);//不让玩家做操作
    pauseBattle();
    SoundManager::playEffectMusic(EFFECT_REBORN);
    this->m_curHealth = this->m_totalHealth;
    HeroHeadListLayer::getInstance()->setBlood(m_curHealth, m_totalHealth);
    heroIsBorn = false;
    for(Hero* hero : * _heroList)
    {
        hero->getAvatarProp()->health = hero->getBaseAvatarProp()->health;
       
//        hero->_angryValue = 0; 小明说复活，怒气不清0
        if(hero->getParent())
        {
            hero->removeFromParent();
        }
      
        if(hero->getAvatarProp()->id == m_mainHeroID)
        {
            changeMainHero(hero);
        }
        hero->onBuff(15 , 0);
        fightObjLayer->addChild(hero,2);
         onAvatarPassSkill(hero);
        EnterWay::jumpIn(hero);
    }
    HeroHeadListLayer::getInstance()->onReborn();
    this->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create(CC_CALLBACK_0(BattleMapLayer::resetUesrControl, this)), NULL));

}
void BattleMapLayer::resetUesrControl()//恢复玩家操作
{
    heroIsBorn = true;
    Dialog::hideServerLoading();
    this->gotoBattle();
}
void BattleMapLayer::onHeroRebornCancel(EventCustom* msg)
{
    StoryTalkManager::getInstance()->onStageBattleOver(this->m_stageBattleID,false);
}
void BattleMapLayer::setNextMainHero()//设置下一个主将
{
     for(Hero* hero : * _heroList)
     {
        if(hero->getAvatarProp()->health > 0)
        {
            changeMainHero(hero);
            HeroHeadListLayer::getInstance()->updateMainHero(hero);
            return;
        }
     }
 
     if(m_Hero)
     {
        heroIsBorn = false;
         if(GlobalInfo::getInstance()->battleType != kBattleType_TestBattle && GlobalInfo::getInstance()->battleType != kBattleType_ArenaBattle)
         {
             showRebornDialog();
         }
         else
         {
             onBattleOver();
         }
        
        broadMsg(CUSTOM_HIDE_HEALTHWARNING);
        m_mainHeroID = m_Hero->getAvatarProp()->id;
     }
     m_Hero = NULL;
   
    
    
}
inline bool BattleMapLayer::hasBornCommonMonster()//是否有普通怪
{
    for( Avatar* monster : * _bornMonsterList)
    {
        if((strcmp(monster->class_name(), "Monster") == 0) || (strcmp(monster->class_name(), "Hero") == 0))
        {
            return true;
        }
    }
    return false;
}
inline bool BattleMapLayer::hasCommonMonster()
{
    Avatar* monster = NULL;
 
    for(__SetIterator it = this->_monsterList->begin(); it != _monsterList->end();   it++)
    {
        monster = (Avatar*)*it;
      
        if((strcmp(monster->class_name(), "Monster") == 0) || (strcmp(monster->class_name(), "Hero") == 0))
        {
            return true;
        }
    }
    return false;
}
void BattleMapLayer::onEnvironmentMonsterDead(Monster* monster)
{
    rewardMonsterPoint = monster->getPosition();
    EnvironmentMonsterDeadMsg* msg = new EnvironmentMonsterDeadMsg(monster->_battleMonsterID);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void BattleMapLayer::onMonsterDead(Avatar* target)
{
    Monster* monster = (Monster*)target;
    if(target->_avatarType == AVATAR_TYPE_MONSTER)
    {
        if(monster->_isBoss)
        {
            Director::getInstance()->getScheduler()->setTimeScale(_frameInit);
        }
        else if(monster->getDictMonster()->type == DictMonsterTypeEnumStageRewardMonster)
        {

            if(_monsterList->containsObject(monster))
            {
          
                onEnvironmentMonsterDead(monster);
            }
        }
    }
   
    _monsterList->removeObject(monster);
    if(_blockMonsterList->containsObject(monster))
    {
         this->_blockMonsterList->removeObject(monster);
    }
    MapDataManager::getInstance()->_blockAvatars->erase(monster);//(hero);
    
//   if(_bornMonsterList->size() <= 0)
//   {
//       log("_blockMonsterList 为0 ");
//   }
    bool hasCommonMonster = this->hasCommonMonster();
    if(!hasCommonMonster)
    {
        onHeroWin();//
        return;
    }
    if(hasBornCommonMonster() || !hasCommonMonster)
    {
        return;
    }
  
    _hasNextWave = false;
    int nowBlock = MapDataManager::getInstance()->_nowBlockNum;
    if(monster->getDictMonster()->type != DictMonsterTypeEnumStageRewardMonster)
    {
          _tureWaves ++;
     
    }
    this->_hasNextWave = this->hasDelayMonster();
    if(_hasNextWave)
    {
     
         this->unschedule(schedule_selector(BattleMapLayer::showDelayMonster));
        this->schedule(schedule_selector(BattleMapLayer::showDelayMonster), 1);
    }

    
    TMXObjectGroup* group = nearLayer->getObjectGroup("touch");
    if(group)
    {
        ValueVector vector = group->getObjects();
        int block = 0;
        for(auto object : vector)
        {
            ValueMap& dict = object.asValueMap();
            block = dict.at("block").asInt();
            if(block == nowBlock)
            {
          
                showNextWaveMonsters();
            }
        }
    }
    if(!_hasNextWave)
    {
    
        showNextWaveMonsters();
    }
    if(!_hasNextWave && _monsterList->count() > 0)
    {
    
        showGoEffect();
    }
}
inline bool BattleMapLayer::hasDelayMonster()//是否有延时怪
{
    Monster* monster = NULL;
    
    for(__SetIterator it = this->_monsterList->begin(); it != _monsterList->end();  it++ )
    {
        monster = (Monster*)*it;
        if(monster->_enterWay == kEnterWayDelay && monster->_turnWaves == _tureWaves)
        {
            return true;
        }
    }
    return false;
}
void BattleMapLayer::showDelayMonster(float dt)
{
    this->unschedule(schedule_selector(BattleMapLayer::showDelayMonster));
    Monster* monster = NULL;
 
    for(__SetIterator it = this->_monsterList->begin(); it != _monsterList->end();  it++ )
    {
        monster = (Monster*)*it;
        if(monster->_enterWay == kEnterWayDelay && monster->_turnWaves == _tureWaves)
        {
            showMonster(monster);
        }
    }

}
void BattleMapLayer::showMonster(Monster* monster)
{
    monster->onEnterScene();
    EnterWay::jumpIn(monster);
    _bornMonsterList->pushBack(monster);
    fightObjLayer->addChild(monster,5000 - monster->getPositionY());
    onAvatarPassSkill(monster);
    if(monster->_isBoss)
    {
        showBossComeWarning(monster);
    }

}
void BattleMapLayer::changeMainHero(Hero* hero)//更换主将
{
    if(!hero ||  m_Hero == hero)
    {
        return;
    }
    if(m_Hero)
    {
       
        if(this->getPositionZ() != 0)
        {
            this->broadMsg(CUSTOM_CAMERA_RESET);
        }
        m_Hero->_isMainHero = false;
        m_Hero->updateShadow();
        m_Hero->m_actionFinishedCallBack = NULL;
    
        CommonEffect* commonEffect = CommonEffect::create("jiaoseqiehuan",false);
        commonEffect->setAnchorPoint(Point(.5,.5));
        hero->addChild(commonEffect,0);
    }
 
    m_Hero = hero;
    m_Hero->_isMainHero = true;
    m_Hero->_isUserControl = false;
    m_Hero->_taskState = kTaskStateNone;
    m_Hero->updateShadow();
    HeroAIManager::getInstance()->setMainHero(m_Hero);
    m_Hero->m_actionFinishedCallBack = CC_CALLBACK_1(BattleMapLayer::onHeroActionFinished, this);
    onUpdateMainHero();
    this->m_curHealth = m_Hero->getAvatarProp()->health;
    this->m_totalHealth = m_Hero->getBaseAvatarProp()->health;
    HeroHeadListLayer::getInstance()->setBlood(m_curHealth, m_totalHealth);
}
inline int BattleMapLayer::getLengendHurtRate(int heroID)
{
    if(GlobalInfo::getInstance()->battleType == kBattleType_MingJiangZhuan)
    {
        DictLegend* dictLegend = DictLegendManager::getInstance()->getData(GlobalInfo::getInstance()->famousePeroid);
        if(dictLegend && dictLegend->multiItemHeroId == heroID)
        {
            return 5;
        }
        return 1;
    }
    return 1;
}
void BattleMapLayer::onHeroAttack(SkillAttackData* attackData)//英雄攻击
{
    log(" onHeroAttackonHeroAttack onHeroAttackonHeroAttack");
    Avatar* target = attackData->getTarget();
    
    DictSkill* useSkill = attackData->getDictSkill();
   
    Avatar* monster = NULL;
    Avatar* hurtMonster = NULL;
    float damage = 0;
    int hurtCount = 0;//伤害个数
    bool isHurt = false;
    ssize_t len = _bornMonsterList->size();
//    if(attackData->_backFindRange || attackData->_frontFindRange)
    {
        for(int i = 0; i < len; i++)
        {
            monster = _bornMonsterList->at(i);
            if(target != m_Hero && monster->getAvatarProp()->health <= 0)
            {
                continue;
            }
            isHurt = avatarIsHurt(monster,attackData);
            
            if(isHurt)
            {
                
                damage = FormulaManager::getHeroAttackDamage(target, monster, attackData);
                if(target->_avatarType == AVATAR_TYPE_HERO &&monster->_avatarType == AVATAR_TYPE_MONSTER)
                {
                    if(((Monster*)monster)->_isBoss)
                    {
                         damage = damage * getLengendHurtRate(((Hero*)target)->getDictHero()->id);
                    }
                   
                }
                if(monster->getAvatarProp()->health > 0)
                {
                    hurtCount ++;
                }
            
                onMonsterHurt(monster,attackData,damage);
                
                if(monster->getAvatarProp()->health <= 0)
                {
                    if(((Monster*)monster)->_isBoss && attackData->getTarget()->getActionState() != kActionStateSkill4)
                    {
                        if(Director::getInstance()->getScheduler()->getTimeScale() == _frameInit)
                        {
                             onBossDead(monster);
                        }
                    }
                }
                 hurtMonster = monster;
                break;
            }
        }
       
    }
    
    ///////
    for(int i = 0 ; i < len; i++)
     {
         monster = _bornMonsterList->at(i);
         if(monster != hurtMonster)
         {
             isHurt = avatarIsBomb(monster, attackData);
             if(isHurt)
             {
                 damage = FormulaManager::getHeroAttackDamage(target, monster, attackData);
                 if(monster->getAvatarProp()->health > 0)
                  {
                     hurtCount ++;
                  }
    
                 onMonsterHurt(monster,attackData,damage);
       
                 if(monster->getAvatarProp()->health <= 0)
                 {
                     if(((Monster*)monster)->_isBoss)
                     {
                         onBossDead(monster);
                     }
                 }
                 if(hurtCount >= useSkill->damageNumber)
                 {
                     break;
                 }

             }
         }
     }

  
}
void BattleMapLayer::onBossDead(Avatar* boss)
{
    if(Director::getInstance()->getScheduler()->getTimeScale() == _frameInit)
    {
        Director::getInstance()->getScheduler()->setTimeScale(AVATAR_SPEED_SCALE);
        

        ArmatureData *armatureData = ArmatureDataManager::getInstance()->getArmatureData(BOSS_DEAD_EFFECT);
        if(!armatureData)
        {
            return;
        }
        Armature* effect = Armature::create(BOSS_DEAD_EFFECT);
        effect->setAnchorPoint(Point(.5,0.5));
        effect->getAnimation()->playWithIndex(0,-1,0);
        effect->setPosition(screenViewCenter.x ,effect->getContentSize().height/2 - 450);
        
        nearLayer->addChild(effect,1);
        effect->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(BattleMapLayer::onEffectCompleted, this,std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

        
    }
}
inline bool BattleMapLayer::avatarIsHurt(Avatar* target,SkillAttackData* attackData)
{
    if(!target->ableHurt())
    {//无敌
        return false;
    }

  
    if(!attackData->_backFindRange && !attackData->_frontFindRange)
    {
        return avatarIsBomb(target, attackData);
    }
   
   
     ActionState _state = target->getActionState();
    DictSkill* useSkill = attackData->getDictSkill();
    if(useSkill->type == DictSkillTypeEnumPassiveSkill)
    {
        return true;
    }
    if(_state == kActionStateJump || _state == kActionStateDown || _state == kActionStatePrePareJumpAttack)
    {
        if(useSkill->hurtHigh <= 0)
        {
            return false;;//不是防空的
        }
    }
  

//    float backFindRange = MAP_TILED_WIDTH * attackData->_backFindRange;//后边查找范围
//    float frontFindRange = MAP_TILED_WIDTH * attackData->_frontFindRange;//前方查找范围
    int backFindRange =  attackData->_backFindRange * GlobalInfo::getInstance()->m_avatarScale;//后边查找范围
    int frontFindRange = attackData->_frontFindRange * GlobalInfo::getInstance()->m_avatarScale;//前方查找范围

    int findRange = fabsf((attackData->_releasePoint - target->getPosition()).getLength()) / MAP_TILED_WIDTH ;//施放点和目标的距离
    findRange *= GlobalInfo::getInstance()->m_avatarScale;
    if(attackData->_isLeft)
    {//向左施放技能
        if(frontFindRange && findRange <= frontFindRange)
        {
            attackData->_bombPoint = target->getPosition();
            return true;
        }
        if(backFindRange && findRange <= backFindRange)
        {
            attackData->_bombPoint = target->getPosition();
            return true;
        }

    }
    else if(!attackData->_isLeft)
    {
        if(frontFindRange && findRange <= frontFindRange)
        {
            attackData->_bombPoint = target->getPosition();
            return true;
        }
        if(backFindRange && findRange <= backFindRange)
        {
            attackData->_bombPoint = target->getPosition();
            return true;
        }
    }
    
    return false;
}
inline bool BattleMapLayer::avatarIsBomb(Avatar* target,SkillAttackData* attackData)//是否被爆点击中
{
    if(!target->ableHurt() || target->getAvatarProp()->health <= 0)
    {//无敌
        return false;
    }
    
    ActionState _state = target->getActionState();
    DictSkill* useSkill = attackData->getDictSkill();
    if(useSkill->type == DictSkillTypeEnumPassiveSkill)
    {
        return true;
    }
    if(_state == kActionStateJump || _state == kActionStateDown || _state == kActionStatePrePareJumpAttack)
    {
        if(useSkill->hurtHigh <= 0)
        {
            return false;;//不是防空的
        }
    }
   
//    float backHurtRange = MAP_TILED_WIDTH * attackData->_backHurtRange;//后边伤害范围
//    float frontHurtRange = MAP_TILED_WIDTH * attackData->_frontHurtRange;//前方伤害范围
    float backHurtRange =  attackData->_backHurtRange * GlobalInfo::getInstance()->m_avatarScale;//后边伤害范围
    float frontHurtRange =  attackData->_frontHurtRange * GlobalInfo::getInstance()->m_avatarScale;//前方伤害范围
//    float disX1 = fabsf(attackData->_bombPoint.x - target->getPositionX()) / MAP_TILED_WIDTH;
    int disX =  (attackData->_bombPoint - target->getPosition()).getLength() / MAP_TILED_WIDTH ;
    bool isInAttackLeft = attackData->_bombPoint.x > target->getPositionX();//是否位于攻击者左边
   
    if(attackData->_isLeft)
    {//向左施放技能
        if(isInAttackLeft)
        {
            return frontHurtRange && disX <= frontHurtRange;
        }
        else
        {
            return backHurtRange && disX <= backHurtRange;
        }
        
    }
    else
    {
        if(isInAttackLeft)
        {
            return backHurtRange && disX <= backHurtRange;
       
        }
        else
        {
            return frontHurtRange && disX <= frontHurtRange;
        }
    }
    
    return false;

}
inline void BattleMapLayer::onMonsterHurt(Avatar* monster,SkillAttackData* attackData,float damage)
{

    DictSkill* useSkill = attackData->getDictSkill();
    
    if(useSkill->soundHit.size())
    {
        SoundManager::playEffectMusic(useSkill->soundHit.c_str());
    }
    
    Avatar* target = attackData->getTarget();
    ActionState _state = monster->getActionState();
    if(monster->hasBuffState(DictBuffTypeEnumSleep))
    {
        damage *= 2;
        monster->removeBuffByType(DictBuffTypeEnumSleep);
    }
//    if(useSkill->toBuffId > 0 && monster->getDictMonster()->type != DictMonsterTypeEnumBlockMonster && monster->getDictMonster()->type != DictMonsterTypeEnumStageRewardMonster)
    if(useSkill->toBuffId  != "" )
    {
        bool isbuff = PublicShowUI::getProbability(useSkill->buffOdds);
        if(isbuff)
        {
            
            for(string buffID : attackData->buffList)
            {
                this->onSkillBuff(monster, attackData, damage,atoi(buffID.c_str()));
            }
          
        }
        
    }
    if(_state == kActionStateJump || _state == kActionStateDown || _state == kActionStatePrePareJumpAttack || _state == kActionStateKnockFly)
    {

        Point direction = Point(target->getPositionX() < monster->getPositionX() ? -1 : 1,0);
        monster->setDirection(direction);
        monster->knockFly(damage,attackData->_isCrit,attackData->_isBlock,attackData->_isSkillAttack);
    }
    else if(useSkill->knockDown && !((Monster*)monster)->_isBoss)
    {

        monster->knockDown(damage,attackData->_isCrit,attackData->_isBlock,attackData->_isSkillAttack);
    }
    else if(useSkill->knockFly && !((Monster*)monster)->_isBoss)
    {
        Point direction = Point(target->getPositionX() < monster->getPositionX() ? -1 : 1,0);
        monster->setDirection(direction);
        monster->knockFly(damage,attackData->_isCrit,attackData->_isBlock,attackData->_isSkillAttack);

        
    }
    else if(useSkill->beatBack && !((Monster*)monster)->_isBoss)
    {
        
        Point cp = getTargetPointByTarget(target,useSkill->beatBack,monster->getPositionX() < attackData->getTarget()->getPositionX());
        cp = monster->getPosition() + cp;
        
        cp = MapDataManager::getInstance()->positionToSelfPostion(monster,cp);
        monster->knockBack(damage,cp,attackData->_isCrit,attackData->_isBlock,attackData->_isSkillAttack);
    
    }
    else
    {
        monster->hurtWithDamage(damage,attackData->_isCrit,attackData->_isBlock,attackData->_isSkillAttack);
      
    }
    if(useSkill->hitResource.size())
    {
        monster->addEffect(useSkill->hitResource.c_str(),useSkill->hitHighShifting);
    }
    
    DoubleHitManager::getInstance()->onHit();
    if(((Monster*)monster)->_isBoss)
    {
        bossBlood = monster->getAvatarProp()->health;
        BossBloodManager::getInstance()->updateBlood();
    }
    if(attackData->getTarget()->_avatarType == AVATAR_TYPE_HERO && GlobalInfo::getInstance()->battleType != kBattleType_TestBattle && GlobalInfo::getInstance()->battleType == kBattleType_ArenaBattle)
    {
        onHeroAddAngry((Hero*)attackData->getTarget());
    }
}
void BattleMapLayer::onUpdateMainHero()
{
    AngryProgressManager::getInstance()->updateMainHero(m_Hero);
    int skillid = m_Hero->getDictHero()->skill10;
    if(GlobalInfo::getInstance()->battleType != kBattleType_ArenaBattle)
    {
        AngryProgressManager::getInstance()->setVisible(false);
//        AngryProgressManager::getInstance()->setVisible(true);
    }
    PublicShowUI::broadUserMsg(CUSTOM_BATTLE_CHANGE_MAINHERO, m_Hero);
    
    DictSkillKarma* dictSkillKarma = DictSkillKarmaManager::getInstance()->getData(skillid);
    if(!dictSkillKarma)
    {
        return;
    }
    int heroID = dictSkillKarma->karmaHeroId;
    
    for(Hero* hero : * _heroList)
    {
       
        if(hero->getDictHero()->id == heroID)
        {
            AngryProgressManager::getInstance()->setVisible(true);
            break;
        }
    }
    
}
void BattleMapLayer::onHeroAddAngry(Hero* hero)
{
    if(hero->getActionState() == kActionStateSkill4)
    {//大招不加怒
        return;
    }
    
    if(GlobalInfo::getInstance()->isGuiding && !AngryProgressManager::getInstance()->isGuided && GlobalInfo::getInstance()->battleType == kBattleType_MingZhanYi)
    {
        hero->_angryValue += 10;
    }
    else
    {
        hero->_angryValue++;
    }
    if(hero->_angryValue>TOTAL_ANGRY_VALUE)
    {
        hero->_angryValue = TOTAL_ANGRY_VALUE;
    }
    if(hero == m_Hero)
    {
        AngryProgressManager::getInstance()->updateAngryValue();
    }
}
void BattleMapLayer::onAttackSelf(SkillAttackData* attackData)//攻击自身
{
    double damage = FormulaManager::getHeroAttackDamage(attackData->getTarget(), attackData->getTarget(), attackData);
    if(attackData->getDictSkill()->toBuffId != "")
    {
        
        bool isbuff = PublicShowUI::getProbability(attackData->getDictSkill()->buffOdds);
        log("attackData->getDictSkill()->buffOdds==%d isbuff=%d",attackData->getDictSkill()->buffOdds,isbuff);
        if(isbuff)
        {
            for(string buffID : attackData->buffList)
            {
                attackData->getTarget()->onBuff(atoi(buffID.c_str()),abs(damage),attackData->getTarget());
                if(attackData->getTarget()->_avatarType == AVATAR_TYPE_HERO)
                {
                    HeroHeadListLayer::getInstance()->addBuff(attackData->getTarget()->getUID(), atoi(buffID.c_str()));
                }
            }
          
        }
        
    }
    else
    {
        attackData->getTarget()->showBloodPlus(abs(damage));
    }
}
void BattleMapLayer::onHeroAttackMinBlood(SkillAttackData* attackData)//攻击最小血量的怪
{
    Avatar* target = attackData->getTarget();
    
    bool isHurt = false;
 
    float damage = 0;
    Avatar* minBloodMonster = NULL;
//    for(__SetIterator it = this->_bornMonsterList->begin(); it != _bornMonsterList->end();   it++)
    for(Avatar* monster : * _bornMonsterList)
    {
        isHurt = avatarIsHurt(monster,attackData);

        if(!isHurt)
        {
            continue;
        }
        if(!minBloodMonster)
        {
            minBloodMonster = monster;
        }
        else
        {
            if(monster->getAvatarProp()->health < minBloodMonster->getAvatarProp()->health)
            {
                minBloodMonster = monster;
            }
        }
    }
    if(minBloodMonster)
    {
        damage = FormulaManager::getHeroAttackDamage(target, minBloodMonster, attackData);
        onMonsterHurt(minBloodMonster,attackData,damage);
    }
}
void BattleMapLayer::onMonsterAttackMinBlood(SkillAttackData* attackData)//攻击最小血量的英雄
{
    Avatar* target = attackData->getTarget();
//    DictSkill* useSkill = attackData->getDictSkill();
    bool isHurt = false;

    float damage = 0;
    Hero* minBloodHero = NULL;

    for(Hero* hero : * _heroList)
    {
        isHurt = avatarIsHurt(hero,attackData);;
       
        if(isHurt)
        {
            if(!minBloodHero)
            {
                minBloodHero = hero;
            }
            else
            {
                if(hero->getAvatarProp()->health < minBloodHero->getAvatarProp()->health)
                {
                    minBloodHero = hero;
                }
            }
         }
    
    }
    if(minBloodHero)
    {
        damage = FormulaManager::getHeroAttackDamage(target, minBloodHero, attackData);
        onHeroHurt(minBloodHero,attackData,damage);
    }
}
void BattleMapLayer::onSkillBuff(Avatar* hurtAvatar,SkillAttackData* attackData,float damage,int buffID)//技能buff效果
{
    DictBuff* dictBuff = DictBuffManager::getInstance()->getData(buffID);
    if(!dictBuff)
    {
        return;
    }
    switch (dictBuff->target)
    {
        case DictSkillTargetEnumEnemy://敌方
            
            hurtAvatar->onBuff(dictBuff->id, damage,attackData->getTarget());
            if(hurtAvatar->_avatarType == AVATAR_TYPE_HERO)
            {
                HeroHeadListLayer::getInstance()->addBuff(hurtAvatar->getUID(), dictBuff->id);
            }
            break;
        case DictSkillTargetEnumAlly://友方
            break;
        case DictSkillTargetEnumParty://队友
            break;
        case DictSkillTargetEnumSelf://自已
            attackData->getTarget()->onBuff(dictBuff->id, damage,attackData->getTarget());
            if(attackData->getTarget()->_avatarType == AVATAR_TYPE_HERO)
            {
                HeroHeadListLayer::getInstance()->addBuff(attackData->getTarget()->getUID(), dictBuff->id);
            }
            break;
    
        default:
            break;
    }
}
Point BattleMapLayer::getTargetPointByTarget(Avatar* target,int gridNum,bool isLeft)//得到目标格坐标
{
  
    Point postion = Point::ZERO;
    Point cp;
    if(gridNum < 0)
    {
        isLeft = !isLeft;
        gridNum = -gridNum;
    }
    for(int i =0; i< gridNum; i++)
    {
        cp = MapDataManager::getInstance()->getAvatarWalkDirection(target,isLeft);
        cp = cp * GlobalInfo::getInstance()->map_tiled_width;
        postion += cp;
    }
    
    return postion;

}
void BattleMapLayer::didChangeDirectorTo(SimplePad* simplepad,Point direction)
{
    if(!m_Hero || m_Hero->isPauseState() || !simplepad->isVisible())
    {
        return;
    }
    if(m_Hero->getActionState() == kActionStateWin || m_Hero->isPauseState())
    {
        return;
    }
    m_Hero->_isUserControl = true;
//    direction = MapDataManager::getInstance()->getAvatarWalkDirection(m_Hero, direction.x < 0);
    DictSkill* dictSkill = NULL;
    if(m_Hero->_actionState == kActionStateSkill1)
    {
        dictSkill = DictSkillManager::getInstance()->getData(m_Hero->getDictHero()->skill7);
    }
    else if(m_Hero->_actionState ==kActionStateSkill2 )
    {
         dictSkill = DictSkillManager::getInstance()->getData(m_Hero->getDictHero()->skill8);
    }
    else if(m_Hero->_actionState ==kActionStateSkill3 )
    {
        dictSkill = DictSkillManager::getInstance()->getData(m_Hero->getDictHero()->skill9);
    }
    else if(m_Hero->_actionState ==kActionStateSkill4 )
    {
        dictSkill = DictSkillManager::getInstance()->getData(m_Hero->getDictHero()->skill10);
    }
    if(dictSkill && !dictSkill->isTurn)
    {
        return;
    }
  
    this->m_Hero->walkWithDirection(direction,simplepad->isHold);
    showNextWaveMonsters();
    
}


void BattleMapLayer::isHoldingDirector(SimplePad* simplepad,Point direction)
{

    didChangeDirectorTo(simplepad,direction);
}
void BattleMapLayer::simplePadTouchEnded(SimplePad* simplepad)
{
    if(this->m_Hero)
    {
        if(m_Hero->getActionState() == kActionStateWalk)
        {
           this->m_Hero->idle();
        }
        m_Hero->_isUserControl = false;
    }
}
void BattleMapLayer::onHeroWin()
{
    pauseBattle();
    for(Hero* hero : * _heroList)
    {
        hero->win();
    }
    log(" onHeroWin onHeroWin");
//    DelayTime* delay = DelayTime::create(.5);
//    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(StoryTalkManager::onStageBattleOver, StoryTalkManager::getInstance(),m_stageBattleID,true));;
//    this->runAction(Sequence::create(delay,callBack, NULL));
    this->scheduleOnce(schedule_selector(BattleMapLayer::delayBattleWin), .5);
}
void BattleMapLayer::delayBattleWin(float dt)
{
    StoryTalkManager::getInstance()->onStageBattleOver(m_stageBattleID, true);
}
void BattleMapLayer::update(float dt)
{
    if(!m_Hero)
    {
        return;
    }
//    log("scaleTime==%f",Director::getInstance()->getScheduler()->getTimeScale());
    dt = dt >= .5 ? 0.1 : dt;

    if(!screenIsMoving)
    {
        setViewPointCenter(dt,this->m_Hero);
        
    }
    heroIsBorn = true;
    double nowTime = 0;//time(0);
    MonsterAIManager::getInstance()->updateMonster(nowTime,dt);
    HeroAIManager::getInstance()->updateHero(nowTime,dt);
  
//    float percent = this->m_Hero->getPositionX() / _mapWidth * 100;
//    MapProgressLayer::getInstance()->updateProgress(percent);
    isMonsterInView();
    if(HeroAIManager::getInstance()->isAutoFight)
    {
        if(_bornMonsterList->size() <= 0 && _monsterList->count())
        {
            showNextWaveMonsters();
        }
    }
  
}
void BattleMapLayer::showBattleWin()
{
//    玩家通关星级计算
//#令三个武将的血量相加成为总血量，该血量通用于在该场战斗中的所有武将，即要死一起死
//    1、当玩家通关一个关卡时，记录玩家在该场战斗中最低的血限的百分比（最低血量/三名武将总血量）
//    2、当血限处于【小于等于100%，大于等于55%】时，通关算三星
//    3、当血限处于【小于55%，大于等于25%】时，通关算二星
//    4、当血限处于【小于25%，大于等于0%】时，通关算一星
//PS:出现血限等于0%且通关的情况存在于当玩家死亡时使用元宝复活
//    使用战斗过程中。最小的血量值
//    int star = 0;
//    m_starProgress = m_starProgress * 100;
//    if(m_starProgress >= 55)
//    {
//        star = 3;
//    }
//    else if(m_starProgress >= 25)
//    {
//         star = 2;
//    }
//    else
//    {
//        star = 1;
//    }
    if(m_bloodBottle <= 0)
    {
        m_bloodBottle = 0;
    }
    if(m_Hero)
    {
        m_starProgress = (float)m_Hero->getAvatarProp()->health / (float)m_Hero->getBaseAvatarProp()->health;//小楠说根据当前血量来。
    }
    else
    {
        m_starProgress = 1;
    }
    
    long usetime = time(0) - m_startTime;
    Dialog::hideServerLoading();
    log("show battleWin BattleWin");
    Director::getInstance()->getScheduler()->setTimeScale(_frameInit);
    if(GlobalInfo::getInstance()->battleType == kBattleType_MingJiangZhuan)
    {
        FamouseBattleWin::show(GlobalInfo::getInstance()->famouseBossID,  GlobalInfo::getInstance()->famouseBossBlood , m_totalBloodBottle - m_bloodBottle);
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_ArenaBattle)
    {
        ArenaBattleWin::show();
    }
    else
    {
         BattleWin::show(m_stageBattleID,m_starProgress,m_totalBloodBottle - m_bloodBottle,this->dropCoin,usetime);
    }
   
}
void BattleMapLayer::showGoEffect()//显示go
{
    if(this->_monsterList->count() <= 0)
    {
        return;
    }
     Scene* scene = Director::getInstance()->getRunningScene();
    if(scene->getChildByTag(TAG_GOEFFECT))
    {
        log("showGoEffect 已经显示了。");
        return;
    }
    Sprite* goSpr = Sprite::create(IMG_BATTLE_GO);
    goSpr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(goSpr);
    goSpr->setPosition(VisibleRect::right().x - goSpr->getContentSize().width, VisibleRect::center().y - goSpr->getContentSize().height/2);
   
    scene->addChild(goSpr,100,TAG_GOEFFECT);
    Blink* blink = Blink::create(3, 3);
    RemoveSelf* remove = RemoveSelf::create();
    goSpr->runAction(Sequence::create(blink,remove, NULL));
    _tureWaves = 1;
    MapDataManager::getInstance()->_nowBlockNum += 1;
    log("MapDataManager::getInstance()->_nowBlockNum =%d",MapDataManager::getInstance()->_nowBlockNum );
    MapDataManager::getInstance()->setBlockLeftPos();
    


}
void BattleMapLayer::showNextBlockMonsters()//显示下一区域怪物
{
    if(hasBornCommonMonster())
    {
        return;
    }
    Monster* monster = NULL;
    for(__SetIterator it = this->_monsterList->begin(); it != _monsterList->end();  it++ )
    {
        monster = (Monster*)*it;
        if(monster->_blockNum == MapDataManager::getInstance()->_nowBlockNum && monster->_turnWaves == _tureWaves)
        {
         
            if(monster->_isBoss)
            {
                showBossComeWarning(monster);
            }
       
            _bornMonsterList->pushBack(monster);
            fightObjLayer->addChild(monster,2,5000 - monster->getPositionY());
          
      
        }
    }
}
inline void BattleMapLayer::showBossComeWarning(Monster* monster)//boss警告
{
//    float distance = fabsf(monster->getPositionX() - screenViewCenter.x);
    if(monster->_isBoss && !bossComeIsWarning)
    {
        
        broadMsg(CUSTOM_BATTLE_SHOW_BOSS_WARNING);
        
        bossComeIsWarning = true;
    }
}
void BattleMapLayer::showNextWaveMonsters()//显示下一波怪
{
    if(this->hasBornCommonMonster())
    {
        return;
    }
    int touch = 0;
    int turn = 0;
    int block = 0;
    int newGuideID = 0;
    float touchPosX = 0;
    int nowBlock = MapDataManager::getInstance()->_nowBlockNum;
    TMXObjectGroup* group = nearLayer->getObjectGroup("touch");
    if(group)
    {
        ValueVector vector = group->getObjects();
        for(auto object : vector)
        {
            ValueMap& dict = object.asValueMap();
             touchPosX = dict.at("x").asFloat();
         
            block = dict.at("block").asInt();
           
            if(block == nowBlock)
            {
                if(dict.find("NewGuideId") != dict.end())
                {
                    newGuideID = dict.at("NewGuideId").asInt();
                }
                
                touch = dict.at("touch").asInt();
                turn = dict.at("turn").asInt();
               
               
                if(turn == _tureWaves)
                {
                    _hasNextWave = true;
                    if(touchPosX > m_Hero->getPositionX())
                    {
                        touch = 0;
                        turn = 0;
                        newGuideID = 0;
                    }
                    break;
                }
               
            }
        }

    }
    
    bool monsterIsBorn = false;
    Monster* monster = NULL;
    for(__SetIterator it = this->_monsterList->begin(); it != _monsterList->end();  it++ )
    {
        monster = (Monster*)*it;
        if(monster->_blockNum == nowBlock)
        {
            if(monster->getParent())
            {
                continue;
            }
     
           if((monster->_turnWaves == _tureWaves && monster->_touch == touch) || (monster->_enterWay == kEnterWayCommon))
           {
               
                _bornMonsterList->pushBack(monster);
                fightObjLayer->addChild(monster,5000 - monster->getPositionY());
                _hasNextWave = true;
                monsterIsBorn = true;
              
                if(monster->_isBoss)
                {
                    showBossComeWarning(monster);
                }
           }
        }
        
      
    }
   
    if(GlobalInfo::getInstance()->isGuiding && monsterIsBorn)
    {
        if(newGuideID)
        {
            DelayTime* delay = NULL;
             CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(BattleMapLayer::delayBroadMsg, this));//
            if(NewPlayerGuild::getInstance()->getNowData() && NewPlayerGuild::getInstance()->getNowData()->bottomId == DictNewGuideEventEnumJoystick)
            {
                delay = DelayTime::create(0.01);;
                this->runAction(Sequence::create(delay,callBack, NULL));
            }
            else if(newGuideID >= 4 && newGuideID <= 8)
            {
               delay = DelayTime::create(0.03);;
                this->runAction(Sequence::create(delay,callBack, NULL));
            }
            else
            {
                 delay = DelayTime::create(0.02);;
                CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(NewPlayerGuild::showGuideByGuideId, NewPlayerGuild::getInstance(),newGuideID));//
                this->runAction(Sequence::create(delay,callBack, NULL));
             
            }
           
        }
      
    }
  
}
void BattleMapLayer::delayBroadMsg()
{
    BaseLayer::broadMsg(CUSTOM_PAUSE_AVATAR_ACTION);
     NewPlayerGuild::getInstance()->next();
}
void BattleMapLayer::onHeroArrived()
{
    m_Hero->idle();
    broadMsg(CUSTOM_SHOW_SIMPLEPAD);
}
void BattleMapLayer::onNextBlockArea(float toPosX)//进入下一区域
{
    if(screenIsMoving)
    {
        return;
    }
    float dt = .4;
    screenIsMoving = true;
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(BattleMapLayer::onNextBlockEnd, this,toPosX));
    nearLayer->runAction(MoveTo::create(dt, Point(toPosX,nearLayer->getPositionY())));

    this->midLayer->runAction(MoveTo::create(dt, Point(toPosX * MID_RATE,midLayer->getPositionY())));
    
    this->closeLayer->runAction(Sequence::create(MoveTo::create(dt, Point(toPosX * CLOSE_RATE,closeLayer->getPositionY())),callBack,NULL));
   
}
void BattleMapLayer::onNextBlockEnd(float toPosX)
{
    screenIsMoving = false;
//    showNextBlockMonsters();
}
inline void BattleMapLayer::updateShipView(float dt,Avatar* target)
{
    
    float moveSpeed = 100;
    float posX = this->midLayer->getPositionX() - moveSpeed * dt;
    if(posX < m_winSize.width - midLayer->getContentSize().width)
    {
        posX = -m_winSize.width;
    }
    this->midLayer->setPositionX(posX);
    bigSkillLayer->setPosition(m_winSize.width/2,0);
   this->closeLayer->setPositionX(posX);
}
inline void BattleMapLayer::setViewPointCenter(float dt,Avatar* target)
{
    if(!target->m_avatar)
    {
        return;
    }
    Point position = target->getPosition();
     float centerX = target->isLeft? m_winSize.width - m_winSize.width/3: m_winSize.width / 3;
    float rightPos = MapDataManager::getInstance()->getBlockRightPos();
    Point viewPoint;
    Point centerOfView = Point(centerX , m_winSize.height  /2);
    
    
    int y = MAX(position.y + (target->m_avatar->getPositionY() - target->m_avatarPosY) , m_winSize.height / 2);
    y = MIN(y, _mapHeight * GlobalInfo::getInstance()->m_mapScale  - m_winSize.height / 2);
    if(_battleMode == kBattleModeMapRun)
    {
        viewPoint = nearLayer->getPosition();
        viewPoint.x -= 100 * dt;
        float leftAdage = -(nearLayer->getContentSize().width  - m_winSize.width);
        if(viewPoint.x <= leftAdage)
        {
            viewPoint.x = leftAdage;
        }
        screenViewCenter.x = centerOfView.x + fabsf(viewPoint.x);
    }
    
    else
    {
        int x =  MAX(position.x , centerX);
        x = MIN(x, _mapWidth   - centerOfView.x);
        screenViewCenter.x = x;
        viewPoint = centerOfView - screenViewCenter;
    }
    screenViewCenter.y = y;
    position = viewPoint;

//    float leftPos = MapDataManager::getInstance()->getBlockLeftPos();

    if(position.x < m_winSize.width - nearLayer->getContentSize().width )
    {
        position.x = m_winSize.width - nearLayer->getContentSize().width ;
    }
    else if(position.x < m_winSize.width - rightPos)
    {
        position.x = m_winSize.width - rightPos;
         screenViewCenter.x = rightPos - centerX;
    }
    
//    else if(target->getPositionX() > leftPos && target->getPositionX() - leftPos < centerOfView.x )
//    {
//        if(nearLayer->getPositionX() != -leftPos )
//        {
//            float distance = abs(abs(nearLayer->getPositionX()) - leftPos);
//            if(distance > 100)
//            {
//                onNextBlockArea(-leftPos);
//                return;
//            }
//        }
//
//        position.x = -leftPos;
//        screenViewCenter.x = leftPos + m_winSize.width/2;
//       
//
//    }
    if(position.x > 0)
    {
        position.x = 0;
    }
//    nearLayer->setPositionY(position.y);
//    this->closeLayer->setPosition(position * CLOSE_RATE);
    
    if(_battleMode == kBattleModeShip)
    {
        this->updateShipView(dt, target);
        return;
    }
    position.x = nearLayer->getPositionX() + (position.x - nearLayer->getPositionX()) * .2;
    nearLayer->setPositionX(position.x);
  
    

    nearLayer-> setPositionX(position.x );
    this->closeLayer->setPositionX(position.x * CLOSE_RATE);
    if(nearLayer->getPositionX() < m_winSize.width - nearLayer->getContentSize().width)
    {
        position.x  = m_winSize.width - nearLayer->getContentSize().width ;
        nearLayer->setPositionX(position.x);
        
    }
    this->m_backGround->setPositionX(position.x * BG_RATE);
    if(m_backGround->getPositionX() < m_winSize.width - m_backGround->getContentSize().width )
    {
        m_backGround->setPositionX(m_winSize.width - m_backGround->getContentSize().width);
    }
    this->midLayer->setPositionX(position.x * MID_RATE);
    if(midLayer->getPositionX() < m_winSize.width - midLayer->getContentSize().width )
    {
        midLayer->setPositionX(m_winSize.width - midLayer->getContentSize().width );
    }
    bigSkillLayer->setPosition(screenViewCenter.x,0);

  
}
inline void BattleMapLayer::isMonsterInView()
{
 
    Point tempPoint;
    float distance = 0;
    bool isNewEnter = false;
    
//    for(__SetIterator it = this->_bornMonsterList->begin(); it != _bornMonsterList->end();  it++ )
    for(Avatar* monster : *_bornMonsterList)
    {
        if(monster->getActionState() == kActionStateDead || monster->getAvatarProp()->health <= 0)
        {
            continue;
        }
        isNewEnter = false;
        distance = fabsf(monster->getPositionX() - screenViewCenter.x);
       
       
        if(distance <= m_winSize.width)
        {
            if(!monster->m_avatar)
            {
           
                if(monster->isNewEnter && ((Monster*)monster)->_isBoss)
                {
                    this->pauseBattle();
                    StoryTalkManager::getInstance()->onMonsterStart(m_stageBattleID);
                }
                if(!isNewEnter && monster->_enterWay  != kEnterWayCommon)
                {
                    isNewEnter = monster->isNewEnter;
                 
                    if(tempPoint.y == 0)
                    {
                        tempPoint = monster->getPosition();
                    }
                    else if(monster->getPositionY()  < tempPoint.y)
                    {
                        tempPoint = monster->getPosition();
                    }
                
                }
                
                if(isNewEnter || monster->isNewEnter)
                {
                    monster->onEnterScene();
                     onAvatarPassSkill(monster);
                }
                else
                {
                    monster->onEnterScene();
                }
               
            }
            if(monster->_avatarType == AVATAR_TYPE_MONSTER)
            {
                if(((Monster*)monster)->_isBoss && !BossBloodManager::getInstance()->isVisible())
                {
                    BossBloodManager::getInstance()->setVisible(true);
                    BossBloodManager::getInstance()->updateBoss(((Monster*)monster));
                }
            }
           
        }
        
        else
        {
      
            monster->onExitScene();
            if(((Monster*)monster)->_isBoss)
            {
                BossBloodManager::getInstance()->setVisible(false);
            }
        }
    }
 
    for(Armature* armature : * _sceneEffecctList)
    {
          distance = fabsf(armature->getPositionX() - screenViewCenter.x);
        if(distance <= m_winSize.width * .5)
        {
            if(!armature->getParent())
            {
                armature->getAnimation()->playWithIndex(0);
                sceneEffecdtLayer->addChild(armature);
            }
            
        }
        else
        {
            
            if(armature->getParent())
            {
                armature->getAnimation()->stop();
                armature->removeFromParent();
            }
        }
    }
    for(Armature* armature : *_midLayerEffectList)
    {
        distance = std::abs(armature->getPositionX() - screenViewCenter.x * MID_RATE);
        if(distance <= m_winSize.width * .8)
        {
            if(!armature->getParent())
            {
                armature->getAnimation()->playWithIndex(0);
                midLayer->addChild(armature,(int)midLayer->getChildrenCount() + 1);
            }
            
        }
        else
        {
            
            if(armature->getParent())
            {
                armature->getAnimation()->stop();
                armature->removeFromParent();
            }
        }
    }
    
    if(isNewEnter)
    {
        if(skillEffectLayer->getChildByTag(TAG_BORNEFFECT))
        {
            return;
        }
        showBornEffect(tempPoint);
    }
}
void BattleMapLayer::showBornEffect(Point cp)
{
    ArmatureData *armatureData = ArmatureDataManager::getInstance()->getArmatureData(MONSTER_BORN_EFFECT);
    if(!armatureData)
    {
        const char* path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, MONSTER_BORN_EFFECT);
        ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
        ArmatureDataManager::getInstance()->addArmatureFileInfo(path);

    }
    Armature* effect = Armature::create(MONSTER_BORN_EFFECT);
    effect->setAnchorPoint(Point(.5,0));
    effect->getAnimation()->playWithIndex(0,-1,0);
    effect->setPosition(cp.x,cp.y - 50);
    skillEffectLayer->addChild(effect,1,TAG_BORNEFFECT);
    effect->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(BattleMapLayer::onEffectCompleted, this,std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

}
void BattleMapLayer::onEffectCompleted(Armature *armature, MovementEventType movementType, const std::string& movementId)
{
    if(movementType != LOOP_COMPLETE && movementType != COMPLETE)
        return;
    armature->pause();
    DelayTime* delay = DelayTime::create(.05);
    RemoveSelf* remove = RemoveSelf::create();
    armature->runAction(Sequence::create(delay,remove, NULL));
    
}

void BattleMapLayer::onAttackTimer()
{
    m_isInTimeing = false;
    this->m_attackClickCount = 1;
    startTimeing(0);
}
void BattleMapLayer::startTimeing(float dt)
{
    m_isInTimeing = true;
//    Director::getInstance()->getScheduler()->unschedule(schedule_selector(BattleMapLayer::clearAttackCount), this);
//    Director::getInstance()->getScheduler()->schedule(schedule_selector(BattleMapLayer::clearAttackCount), this,8, false);
}
void BattleMapLayer::clearAttackCount(float td)
{
  
    Director::getInstance()->getScheduler()->unschedule(schedule_selector(BattleMapLayer::clearAttackCount), this);
    m_isInTimeing = false;
}
void BattleMapLayer::onAttack()
{
    if(this->m_isbigSkilling)
    {
        return;
    }
    if(!heroIsBorn || !this->m_Hero)
    {
        return;
    }
 
    if(NewPlayerGuild::getInstance()->getNowData() && NewPlayerGuild::getInstance()->getNowData()->id == 5)
    {
        NewPlayerGuild::getInstance()->pause();
    }
    ActionState state = m_Hero->getActionState();
   
    if(state == kActionStateSkill1 || state == kActionStateSkill2 || state == kActionStateSkill3 || state == kActionStateWin)
    {
        return;
    }
    if(state == kActionStateJump )
    {
        this->onJumpAttack();
        
    }
    else if(state == kActionStateIdle || state == kActionStateWalk)
    {
        this->attack1();
    }
    else if(state == kActionStateAttack1 )
    {
        this->m_attackClickCount = 2;
    }
    else if(state == kActionStateAttack2)
    {
        this->m_attackClickCount = 3;
    }
    else if(state == kActionStateAttack3)
    {
        this->m_attackClickCount = 4;
    }
    else if(state == kActionStateAttack4)
    {
         this->m_attackClickCount = 5;
    }
    else if(state == kActionStateAttack5)
    {
        this->attack1();
    }
 
}
void BattleMapLayer::onDashClick()
{
//    ActionState state = m_Hero->_preActionState;
//    if(state == kActionStateAttack1 )
//    {
//        this->m_attackClickCount = 2;
//    }
//    else if(state == kActionStateAttack2)
//    {
//        this->m_attackClickCount = 3;
//    }
//    else if(state == kActionStateAttack3)
//    {
//        this->m_attackClickCount = 4;
//    }
//    else if(state == kActionStateAttack4)
//    {
//        this->m_attackClickCount = 5;
//    }
//    else if(state == kActionStateAttack5)
//    {
//        this->attack1();
//    }
}
void BattleMapLayer::attack1()
{
    if(this->m_isbigSkilling)
    {
        return;
    }
    if(this->m_Hero)
    {
//        onSortBornMonster();
        if(this->m_Hero->attack1())
        {
            onAttackTimer();
        }
        
    }
}

void BattleMapLayer::attack2()
{
    if(this->m_Hero)
    {
        if(this->m_isbigSkilling)
        {
            return;
        }
        onSortBornMonster();
        this->m_Hero->attack2();
        
    }
   
}

void BattleMapLayer::attack3()
{
    if(this->m_Hero)
    {
        if(this->m_isbigSkilling)
        {
            return;
        }
         onSortBornMonster();
        this->m_Hero->attack3();
      
        
    }
    
}
void BattleMapLayer::attack4()//攻击
{
    if(this->m_Hero)
    {
        if(this->m_isbigSkilling)
        {
            return;
        }
         onSortBornMonster();
        this->m_Hero->attack4();
       
    }
    
}
void BattleMapLayer::attack5()//攻击5
{
    if(this->m_Hero)
    {
        if(this->m_isbigSkilling)
        {
            return;
        }
        onSortBornMonster();
        this->m_Hero->attack5();
      
    }
  
}
void BattleMapLayer::onJumpAttack()
{
    if(this->m_isbigSkilling)
    {
        return;
    }
    if(this->m_Hero)
    {
        this->m_Hero->jumpAttact(m_Hero->m_jumpAttackTime);
    
    }

    

}
void BattleMapLayer::onJump()
{
    if(!heroIsBorn)
    {
        return;
    }
    if(this->m_isbigSkilling)
    {
        return;
    }
    if(this->m_Hero)
    {
       
        this->m_Hero->jump();
        onSortBornMonster();
    }
}
void BattleMapLayer::onSkill(int buttonType)
{
    if(this->m_isbigSkilling)
    {
        return;
    }
    if(!m_Hero || (m_Hero->isPauseState() && !GlobalInfo::getInstance()->isGuiding))
    {
        return;
    }
    if(!heroIsBorn || m_Hero->getActionState() == kActionStateWin)
    {
        return;
    }

    if(buttonType == ControlBtnPanel::BUTTON_SKILL1)
    {
    
        onSortBornMonster();
        this->m_Hero->skill1();
    }
    else if(buttonType == ControlBtnPanel::BUTTON_SKILL2)
    {
        onSortBornMonster();
        this->m_Hero->skill2();
    }
    else if(buttonType == ControlBtnPanel::BUTTON_SKILL3)
    {
        onSortBornMonster();
        this->m_Hero->skill3();
    }
    else if(buttonType == ControlBtnPanel::BUTTON_SKILL4)
    {
          this->onJump();
    }
  
}
void BattleMapLayer::onProtected()
{
    if(!this->m_Hero)
    {
        return;
    }
    if(m_Hero->getActionState() == kActionStateJump)
    {
        this->onJumpAttack();
        return;
    }
    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(m_Hero->getDictHero()->skill12);
    if(dictSkill->costWay == DictSkillCostWayEnumDodgeSkill)//闪避
    {
        m_Hero->duck();
    }
    else if(dictSkill->costWay == DictSkillCostWayEnumBlockSkill)//格档
    {
        m_Hero->block();
    }
}
void BattleMapLayer::onReleaseProtected()
{
    if(m_Hero)
    {
        m_Hero->unBlock();
    }
   
}
void BattleMapLayer::onSkill4Over()
{
    bigSkillLayer->removeAllChildren();
    
    FogLayer* layer = FogLayer::create(3,CC_CALLBACK_0(BattleMapLayer::resumeOtherAvatar, this));
    Director::getInstance()->getRunningScene()->addChild(layer);
    
    broadMsg(CUSTOM_SHOW_MAPREOURCE);
    this->closeLayer->setVisible(true);

    onFocusReset(NULL);
    HeroHeadListLayer::getInstance()->setClickEnable(true);
  
}
void BattleMapLayer::onChangeSkillBg(Avatar* target)
{
    bigSkillLayer->setPositionY(0);
    Armature* skillEffect = (Armature*)bigSkillLayer->getChildByTag(TAG_BIGSKILL_EFFECTBG);
    if(skillEffect)
    {
        skillEffect->getAnimation()->setFrameEventCallFunc(NULL);
        skillEffect->removeFromParent();
    }
    const char* path = NULL;
    if(target->_frameParam.size()>0)
    {
        path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, target->_frameParam.c_str());
       
        ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
        ArmatureDataManager::getInstance()->addArmatureFileInfo(path);
        ArmatureData *armatureData =  ArmatureDataManager::getInstance()->getArmatureData(target->_frameParam);
        if(armatureData)
        {
             skillEffect = Armature::create(target->_frameParam.c_str());
        }
        else
        {
            path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, BIGSKILL_SKILLBG_EFFECT1);
            ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
            ArmatureDataManager::getInstance()->addArmatureFileInfo(path);
            skillEffect = Armature::create(BIGSKILL_SKILLBG_EFFECT1);
        }
       
    }
    else
    {
        ArmatureData *armatureData = ArmatureDataManager::getInstance()->getArmatureData(BIGSKILL_SKILLBG_EFFECT1);
        if(!armatureData)
        {
           path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, BIGSKILL_SKILLBG_EFFECT1);
            ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
            ArmatureDataManager::getInstance()->addArmatureFileInfo(path);
        }
            
        skillEffect = Armature::create(BIGSKILL_SKILLBG_EFFECT1);
    }
     skillEffect->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(BattleMapLayer::onSkillBgFrame, this,std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
//    BATTLE_SKILLBG_MOVE
    skillEffect->getAnimation()->playWithIndex(0);
    float _scale = GlobalInfo::getInstance()->screenScaleY/ GlobalInfo::getInstance()->screenScaleX;
    if(_scale < 1)
    {
        _scale = 1;
    }
    skillEffect->setScaleY(_scale);
    skillEffect->setAnchorPoint(Point::ZERO);
    if(target->isLeft)
    {
        skillEffect->setScaleX(-1);
        skillEffect->setPosition(-skillEffect->getContentSize().width/2 + skillEffect->getContentSize().width, 0);
    }
    else
    {
        skillEffect->setScaleX(1);
        skillEffect->setPosition(-skillEffect->getContentSize().width/2, 0);
    }
    bigSkillLayer->addChild(skillEffect,0,TAG_BIGSKILL_EFFECTBG);
}
void BattleMapLayer::onSkillBgFrame(Bone *bone, const std::string& evt, int origin, int current)
{
    vector<string> params = StringUtil::split(evt, "_");
    string _frameEvent = params[0];
    string _frameParam = "";
    
    if(params.size() > 1)
    {
        _frameParam = params[1];
       
    }
    if(_frameEvent == BATTLE_SKILLBG_MOVE)
    {
        onSkillBgUpDown(atoi(_frameParam.c_str()));
    }
}
void BattleMapLayer::onSkillBgUpDown(int offY)
{
    bigSkillLayer->setPositionY(bigSkillLayer->getPositionY() + offY);
}
void BattleMapLayer::onReleaseBigSkill(Avatar* target)
{
    if(target->hasBuffState(DictBuffTypeEnumSeal))
    {//封印
        return;
    }
    if(target->getActionState() == kActionStateDead)
    {
        return;
    }
    
    if(target->getIsCDState(m_Hero->getDictHero()->skill10) || target->getActionState() == kActionStateSkill4 || m_isbigSkilling
       ||target->getActionState() == kActionStateSkill1 || target->getActionState() == kActionStateSkill2 || target->getActionState() == kActionStateSkill3)
    {
        return;
    }
    if(target->_avatarType == AVATAR_TYPE_HERO)
    {
        ((Hero*)target)->_angryValue = 0;
        AngryProgressManager::getInstance()->updateAngryValue();
    }
    HeroHeadListLayer::getInstance()->setClickEnable(false);
    broadMsg(CUSTOM_HIDE_MAPRESOURCE);
    this->closeLayer->setVisible(false);
    m_isbigSkilling = true;
    LayerColor* layer = LayerColor::create(Color4B(0,0,0,255), m_winSize.width * 2 , m_winSize.height * 2);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(-m_winSize.width/2 - 300 , 0);
    bigSkillLayer->addChild(layer,0);
    pauseOtherAvatar(target);
    flySkillName(target);
}
void BattleMapLayer::flySkillName(Avatar* target)
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* person = Sprite::create();
    person->setAnchorPoint(Point::ZERO);
    
    
    Sprite* skillBg = Sprite::create(IMG_BATTLE_BIGSKILLBG);
    skillBg->setAnchorPoint(Point(0,0));
    person->addChild(skillBg,0);
    PublicShowUI::setTargetScale(skillBg,true,true);
    
    const char* path = NULL;
   

    DictSkill* dictSkill = NULL;//
    if(target->_avatarType == AVATAR_TYPE_HERO)
    {
        Hero* hero = (Hero*)target;
        path = PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH,hero->getDictHero()->halfbodyrResource.c_str());//
        dictSkill = DictSkillManager::getInstance()->getData(hero->getDictHero()->skill10);
        
    }
    else
    {
        Monster* monster = (Monster*)target;
        path = PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH, monster->getDictMonster()->halfbodyrResource.c_str());
       dictSkill = DictSkillManager::getInstance()->getData(monster->getDictMonster()->skill10);
    }
    
    Sprite* halfbody = Sprite::create(path);
    if(!halfbody)
    {
        path = PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH,"caopi");
        halfbody =Sprite::create(path);
    }
    
  
    halfbody->setScale(1.8 * sx);
    halfbody->setPosition(halfbody->getContentSize().width * sx / 2 + 110 * sx,skillBg->getContentSize().height/2 - 100 * sx );
    person->addChild(halfbody,0);
    halfbody->runAction(MoveBy::create(10, Point(100 * sx,0)));
    if(dictSkill)
    {
        path = PublicShowUI::getResImgPath(IMG_SKILL_SKILLNAME, dictSkill->ename.c_str());
        Sprite* skillName = Sprite::create(path);
        if(skillName)
        {
            PublicShowUI::setTargetScale(skillName);
            skillName->setPosition(skillBg->getContentSize().width/2 + 110 * sx, skillBg->getContentSize().height/2);
            person->addChild(skillName,2);
        }
     
    }


    DelayTime* delay = DelayTime::create(1);
    RemoveSelf* remove = RemoveSelf::create();
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(BattleMapLayer::playBigSkill, this,target));
    person->runAction(Sequence::create(delay, remove,callBack,NULL));
    Scene* scene = Director::getInstance()->getRunningScene();
    scene->addChild(person);
    target->_frameParam = "";
    onChangeSkillBg(target);
  
}
void BattleMapLayer::playBigSkill(Avatar* target)
{
    target->skill4();
}
void BattleMapLayer::onBattleStart()
{
    m_startTime = time(0);
    dropCoin = 0;
    if(GlobalInfo::getInstance()->isShowGuide)
    {
        if(GlobalInfo::getInstance()->battleType == kBattleType_LoginBattle)
        {
            BattleOperationLayer* layer = BattleOperationLayer::create();
            layer->setAnchorPoint(Point::ZERO);
            PublicShowUI::setTargetScale(layer);
            layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2,VisibleRect::center().y - layer->getContentSize().height/2);
            Director::getInstance()->getRunningScene()->addChild(layer,SCENE_LAYER_ZORDER);
            
            return;
        }
        else if(GlobalInfo::getInstance()->battleType == kBattleType_MingZhanYi)
        {
            if(m_stageBattleID > 221003 || !GlobalInfo::getInstance()->isGuiding || GlobalInfo::getInstance()->stageMode == kStageModeBest)
            {
                broadMsg(CUSTOM_SHOW_PROTECTED_BTN);
            }
            if(NewPlayerGuild::getInstance()->getNowData() && NewPlayerGuild::getInstance()->getNowData()->bottomId == DictNewGuideEventEnumClickFightAvatar2)
            {
                NewPlayerGuild::getInstance()->showNowGuide();
            }
           
        }
        else if(GlobalInfo::getInstance()->battleType == kBattleType_MingJiangZhuan)
        {
            
        }
    }
    if(this->isTimeWinMode)
    {
        BattleCountDown::getInstance()->start(isTimeWinMode,(int)this->m_victoryTime);
    }
    else
    {
        BattleCountDown::getInstance()->start(isTimeWinMode,(int)this->m_leftTime);
    }
    
   
    gotoBattle();
}

void BattleMapLayer::pauseBattle()
{
    this->unscheduleUpdate();
    
     HeroHeadListLayer::getInstance()->setClickEnable(false);
//    log("pauseBattle pauseBattle pauseBattle 111111111");
}
void BattleMapLayer::gotoBattle(EventCustom* msg)
{
    if(StoryTalkManager::getInstance()->isTalking())
    {
        return;
    }
    this->unscheduleUpdate();
    this->scheduleUpdate();
    HeroHeadListLayer::getInstance()->setClickEnable(true);
//    log("gotoBattle gotoBattle gotoBattle 222222222");
}
void BattleMapLayer::onBattleOver()
{
    BattleCountDown::getInstance()->stop();
    DelayTime* delayPause = DelayTime::create(1);
    CallFunc* callBackPause = CallFunc::create(CC_CALLBACK_0(BattleMapLayer::pauseBattle, this));
    BattleCountDown::getInstance()->runAction(Sequence::create(delayPause,callBackPause, NULL));
    if(!this->hasCommonMonster() || GlobalInfo::getInstance()->isDebug || this->isTimeWinMode)
    {
    
        Dialog::showServerLoading(1);
        DelayTime* delay = DelayTime::create(1);
        CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(BattleMapLayer::showBattleWin, this));
        this->m_backGround->runAction(Sequence::create(delay, callBack,NULL));
  
    }
    else
    {
        
        if(GlobalInfo::getInstance()->isGuiding && GlobalInfo::getInstance()->gameRole->level <= 7)
        {
            showBattleWin();
        }
        else if(GlobalInfo::getInstance()->battleType == kBattleType_MingJiangZhuan)
        {
            FamouseBattleLose::show(this->m_leftTime <= 0, GlobalInfo::getInstance()->famouseBossID,bossBlood, m_totalBloodBottle - m_bloodBottle);
        }
        else
        {
            BattleLose::show(m_stageBattleID,m_totalBloodBottle - m_bloodBottle);
        }
        
       
    }
}
//昭唤助手
void BattleMapLayer::onSummonedHelper(EventCustom* msg)
{

    Avatar* target = (Avatar*)msg->getUserData();

    DictSummonSkill* summonSkill = DictSummonSkillManager::getInstance()->getData(target->getCurSkillID());
    if(!summonSkill)
    {
        return;
    }
//    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(summonSkill->id);
    Point cp ;
//    cp.x =  target->isLeft ? cp.x - dictSkill->hurtForward * GlobalInfo::getInstance()->m_avatarScale * MAP_TILED_WIDTH : cp.x + dictSkill->hurtForward * GlobalInfo::getInstance()->m_avatarScale * MAP_TILED_WIDTH;
     float distance = atoi(target->_frameParam.c_str());
    int grid = distance / MAP_TILED_WIDTH;
    
    cp = getTargetPointByTarget(target,grid,target->isLeft);
    cp = target->getPosition() + cp;
    cp = MapDataManager::getInstance()->positionToSelfPostion(target,cp);
 
    
//    for(int i = 0; i< 3; i++)
//    {
//        cp.y = cp.y - MAP_TILED_HEIGHT;
//        if(MapDataManager::getInstance()->getAvatarPosition(cp, 1, target->isLeft) == Point::ZERO)
//        {
//            cp.y = cp.y + MAP_TILED_HEIGHT;
//            break;
//        }
//    }
    Point startPos = cp;
   if(summonSkill->summonId1 > 0)
   {
       for(int i = 0; i < summonSkill->summonId1Number; i++)//
       {
           startPos.y = startPos.y - MAP_TILED_HEIGHT;
           if(MapDataManager::getInstance()->getAvatarPosition(cp, i + 1, target->isLeft) == Point::ZERO)
           {
               startPos.y = startPos.y + MAP_TILED_HEIGHT;
           }
           createSummonHero(target,startPos,summonSkill->summonId1,1,i + 1,summonSkill->summonId1Time);
       }
   }
    startPos = cp;
    if(summonSkill->summonId2 > 0)
    {
      
        for(int i = 0; i < summonSkill->summonId2Number; i++)
        {
            startPos.y = startPos.y - MAP_TILED_HEIGHT;
            if(MapDataManager::getInstance()->getAvatarPosition(cp, i + 1, target->isLeft) == Point::ZERO)
            {
                startPos.y = startPos.y + MAP_TILED_HEIGHT;
            }
            createSummonHero(target,startPos,summonSkill->summonId2,2,i+1,summonSkill->summonId2Time);
        }
    }
      startPos = cp;
    if(summonSkill->summonId3 > 0)
    {
        for(int i = 0; i < summonSkill->summonId3Number; i++)
        {
            startPos.y = startPos.y - MAP_TILED_HEIGHT;
            if(MapDataManager::getInstance()->getAvatarPosition(cp, i + 1, target->isLeft) == Point::ZERO)
            {
                startPos.y = startPos.y + MAP_TILED_HEIGHT;
            }
            createSummonHero(target,startPos,summonSkill->summonId3,3,i+1,summonSkill->summonId3Time);
        }
    }
    
}
void BattleMapLayer::createSummonHero(Avatar* caller,Point startPostion,int heroDictID,int row,int colum,int lifetime)
{

    SummonedHero* hero = SummonedHero::create(heroDictID,lifetime);
    if(!hero)
    {
        return;
    }
    hero->setScale(GlobalInfo::getInstance()->m_avatarScale);
    hero->m_actionFinishedCallBack = NULL;
    hero->isShowBlood = false;
    hero->_wayNumber = colum;
    int level = caller->getAvatarProp()->level > 0 ? caller->getAvatarProp()->level : 1;
    int prestige = caller->getAvatarProp()->prestige > 0 ? caller->getAvatarProp()->prestige : 1;
    DictAvatarProp* heroProp = DictManager::getDictHeroProp(heroDictID,level ,prestige);
    hero->setBaseAvatarProp(heroProp);
    hero->setAvatarProp(heroProp->clone());
     hero->_avatarTeam = caller->_avatarTeam;
    hero->m_actionAttackCallBack = CC_CALLBACK_1(BattleMapLayer::onHeroSkillAttackCallBack, this);
    hero->_taskState = kTaskStateGuard;//默认为守卫状态

    
    hero->_destinatsionPostion = startPostion;
    hero->setPosition(startPostion.x ,startPostion.y);

 
    
    hero->_warningRange = hero->getDictHero()->sight * GlobalInfo::getInstance()->m_avatarScale * MAP_TILED_WIDTH ;
    hero->_followMainHeroDistance =  hero->_wayNumber * 4 * GlobalInfo::getInstance()->m_avatarScale * MAP_TILED_WIDTH;
    
    hero->setAnchorPoint(Point(.2,0));
    hero->_baseSpeed = hero->getDictHero()->moveSpeed * GlobalInfo::getInstance()->m_avatarScale;
    hero->_walkSpeed = hero->_baseSpeed ;
    hero->setUID(heroProp->id);
    hero->_totalHitPoints = hero->getAvatarProp()->health;
    
    _heroList->pushBack(hero);
    fightObjLayer->addChild(hero,5000 - hero->getPositionY());
     onAvatarPassSkill(hero);
  
    for(int i = 0 ;i < colum ; i++)
    {
        hero->walkWithDirection(Point(1,i), true);
    }
    
}
void BattleMapLayer::onHeroRemove(Hero* hero)
{
    
    _heroList->eraseObject(hero);
    hero->win();
    DelayTime* delay = DelayTime::create(.5);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(BattleMapLayer::onHeroRemoveDelay, this,hero));
    hero->runAction(Sequence::create(delay,callBack, NULL));
}
void BattleMapLayer::onHeroRemoveDelay(Hero* hero)
{
    fightObjLayer->removeChild(hero);
}
void BattleMapLayer::onMsgProcess(EventCustom* message)
{
    Dialog::hideServerLoading();
    MessageReceive* msg = (MessageReceive*)message->getUserData();
    if(msg->messageID == SCENSE_CLIENT_BATTLE_PotionResp)
    {
        if(msg->state)
        {
            onHeroBloodReset();
        }
    }
    else if(msg->messageID == SCENSE_CLIENT_BATTLE_BattleLootResp)
    {
        if(msg->state)
        {
           
            showMonsterDrops(msg->byteStream);
        }
    }
    
}
void BattleMapLayer::showMonsterDrops(ByteStream* bytestream)
{
    int len = bytestream->get();
    const char* path = NULL;
    for(int i = 0; i < len; i++)
    {
        int itemConType = bytestream->get();
        int itemQuality = bytestream->get();
        int dictID = bytestream->getInt();
        int itemCount = bytestream->getInt();
        if(itemConType == DictContTypeEnumRoleProp)//& dictID==DictRolePropEnumCoin
        {
            DictResource* dictResource = DictResourceManager::getInstance()->getData(dictID);
            if(dictResource && dictResource->propType == DictRolePropEnumCoin)
            {
                dropCoin += itemCount;
            }
          
        }
        const char* icon = bytestream->getUTF8();
        path = PublicShowUI::getResImgPath(IMG_PUBLIC_ITEM, icon);
        Sprite* iconSpr = Sprite::create(path);
        iconSpr->setAnchorPoint(Point(.5,0));
        if(iconSpr)
        {
            sceneEffecdtLayer->addChild(iconSpr,10);
            iconSpr->setPosition(rewardMonsterPoint);
            iconSpr->setScale(.3);
             rewardMonsterPoint.x = rewardMonsterPoint.x + i * (iconSpr->getContentSize().width + 20);
            if(this->m_Hero)
            {
                rewardMonsterPoint.y = m_Hero->getPositionY() + 10;
            }
            MoveBy* moveBy = MoveBy::create(.2, Point(0,100));
            
            JumpBy* jumpby = JumpBy::create(.2, Point::ZERO, 10, 2);
        
            DelayTime* delay = DelayTime::create(1);
           
            CallFuncN* callBack = CallFuncN::create(CC_CALLBACK_1(BattleMapLayer::onDropItemCollect, this));
            iconSpr->runAction(ScaleTo::create(.1, 1));
            iconSpr->runAction(Sequence::create(moveBy,moveBy->reverse(),jumpby,delay,callBack, NULL));
            dropList->pushBack(iconSpr);
            
//            CommonEffect* commonEffect = CommonEffect::create("jinbishiqu");
//            commonEffect->setAnchorPoint(Point::ZERO);
//            commonEffect->setPosition(VisibleRect::center());
//            this->addChild(commonEffect,30);
          

        }
        
    }
}
void BattleMapLayer::onDropItemCollect(Node* target)
{

    float distance = fabsf(target->getPositionX() - screenViewCenter.x);
    if(distance > m_winSize.width)
    {
         target->removeFromParent();
    }
    else
    {
        float screenStartX = screenViewCenter.x - m_winSize.width/2;
        float screenStartY = this->_mapHeight;
        Point cp = Point(screenStartX,screenStartY);
        MoveBy* moveBy = MoveBy::create(.2, Point(0,80));
        MoveTo* moveto = MoveTo::create(.6, cp);
        RemoveSelf* hide = RemoveSelf::create();
        target->runAction(ScaleTo::create(.6, .1));

//        CommonEffect* commonEffect = CommonEffect::create("jinbishiqu");
//        target->addChild(commonEffect,30);
        target->runAction( Sequence::create(moveBy,moveto,hide,NULL));
    }
    dropList->eraseObject(target);
}
void BattleMapLayer::onAvatarPostionMove(EventCustom* message)
{
    Avatar* avatar = (Avatar*)message->getUserData();
    float num = atof(avatar->_frameParam.c_str());
    float time = 0;
    if(avatar->_avatarType == AVATAR_TYPE_HERO)
    {
        time = getHeroDashTime((Hero*)avatar);
    }
    else
    {
        time = getMonsterDashTime((Monster*)avatar);
    }
  
    avatar->dash(num,time);
}
float BattleMapLayer::getMonsterDashTime(Monster* monster)
{
    DictSkill* dictSkill = NULL;
    ActionState state = monster->getActionState();
    switch (state) {
        case kActionStateAttack1:
            dictSkill = DictSkillManager::getInstance()->getData(monster->getDictMonster()->skill1);
            break;
        case kActionStateAttack2:
             dictSkill = DictSkillManager::getInstance()->getData(monster->getDictMonster()->skill2);
            break;
        case kActionStateAttack3:
             dictSkill = DictSkillManager::getInstance()->getData(monster->getDictMonster()->skill3);
            break;
        case kActionStateAttack4:
             dictSkill = DictSkillManager::getInstance()->getData(monster->getDictMonster()->skill4);
            break;
        case kActionStateAttack5:
            dictSkill = DictSkillManager::getInstance()->getData(monster->getDictMonster()->skill5);
            break;
        case kActionStateSkill1:
            dictSkill = DictSkillManager::getInstance()->getData(monster->getDictMonster()->skill7);
            break;
        case kActionStateSkill2:
             dictSkill = DictSkillManager::getInstance()->getData(monster->getDictMonster()->skill8);
            break;
        case kActionStateSkill3:
             dictSkill = DictSkillManager::getInstance()->getData(monster->getDictMonster()->skill9);
            break;
        case kActionStateSkill4:
             dictSkill = DictSkillManager::getInstance()->getData(monster->getDictMonster()->skill10);
            break;
            
        default:
            break;
    }

    return dictSkill ? dictSkill->moveTime : 0;
}
float BattleMapLayer::getHeroDashTime(Hero* hero)
{
    DictSkill* dictSkill = NULL;
    ActionState state = hero->getActionState();
    switch (state) {
        case kActionStateAttack1:
            dictSkill = DictSkillManager::getInstance()->getData(hero->getDictHero()->skill1);
            break;
        case kActionStateAttack2:
            dictSkill = DictSkillManager::getInstance()->getData(hero->getDictHero()->skill2);
            break;
        case kActionStateAttack3:
            dictSkill = DictSkillManager::getInstance()->getData(hero->getDictHero()->skill3);
            break;
        case kActionStateAttack4:
            dictSkill = DictSkillManager::getInstance()->getData(hero->getDictHero()->skill4);
            break;
        case kActionStateAttack5:
            dictSkill = DictSkillManager::getInstance()->getData(hero->getDictHero()->skill5);
            break;
        case kActionStateSkill1:
            dictSkill = DictSkillManager::getInstance()->getData(hero->getDictHero()->skill7);
            break;
        case kActionStateSkill2:
            dictSkill = DictSkillManager::getInstance()->getData(hero->getDictHero()->skill8);
            break;
        case kActionStateSkill3:
            dictSkill = DictSkillManager::getInstance()->getData(hero->getDictHero()->skill9);
            break;
        case kActionStateSkill4:
            dictSkill = DictSkillManager::getInstance()->getData(hero->getDictHero()->skill10);
            break;
            
        default:
            break;
    }
    
    return dictSkill ? dictSkill->moveTime : 0;
}
bool sortBornMosnterRight(Avatar* a,Avatar* b)
{
    return a->getPositionX() < b->getPositionX();
}
bool sortBornMonsterLeft(Avatar* a , Avatar* b)
{
    return a->getPositionX() > b->getPositionX();
}

void BattleMapLayer::onSortBornMonster(EventCustom* msg)
{
    if(this->m_Hero->isLeft)
    {
        sort(_bornMonsterList->begin(), _bornMonsterList->end(),sortBornMonsterLeft);
    }
    else
    {
        sort(_bornMonsterList->begin(), _bornMonsterList->end(),sortBornMosnterRight);
    }
    
}
void BattleMapLayer::onCountDownOver(EventCustom* msg)//倒计时结束
{
    if(this->isTimeWinMode)
    {
        for(Hero* hero : * _heroList)
        {
            hero->win();
        }
       
    }
    onBattleOver();
    
}
void BattleMapLayer::addEventListener()
{
    _eventDispatcher->addCustomEventListener(CUSTOM_ON_SKILL_ATTACK, CC_CALLBACK_1(BattleMapLayer::onSkillAttackCallBack, this));
    addUserMsg(CUSTOM_BEFOREFIGHT_TALK_END, CC_CALLBACK_0(BattleMapLayer::onBattleStart, this));
    addUserMsg(CUSTOM_OVERFIGHT_TALK_END, CC_CALLBACK_0(BattleMapLayer::onBattleOver, this));
    addUserMsg(CUSTOM_BATTLE_COUNTDOWN_OVER, CC_CALLBACK_1(BattleMapLayer::onCountDownOver, this));
    addUserMsg(CUSTOM_BATTLE_HERO_REBORNCONFIRM, CC_CALLBACK_1(BattleMapLayer::onHeroReBorn, this));
    addUserMsg(CUSTOM_BATTLE_HERO_REBORNCANCEL, CC_CALLBACK_1(BattleMapLayer::onHeroRebornCancel, this));
    addUserMsg(CUSTOM_POSITION_MOVE,CC_CALLBACK_1(BattleMapLayer::onAvatarPostionMove, this));
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_BATTLE_PotionResp).c_str(), CC_CALLBACK_1(BattleMapLayer::onMsgProcess, this));
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_BATTLE_BattleLootResp).c_str(), CC_CALLBACK_1(BattleMapLayer::onMsgProcess, this));
    addUserMsg(CUSTOM_PLAY_SOUND,CC_CALLBACK_1(BattleMapLayer::playAvatarSound,this));
//    addUserMsg(CUSTOM_SORT_BORN_MONSTER,CC_CALLBACK_1(BattleMapLayer::onSortBornMonster,this));
    addUserMsg(CUSTOM_MONSTER_TALK_END,CC_CALLBACK_1(BattleMapLayer::gotoBattle,this));
    addUserMsg(CUSTOM_BATTLE_SUMMONED_SKILL,CC_CALLBACK_1(BattleMapLayer::onSummonedHelper,this));
}
void BattleMapLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
    _eventDispatcher->removeCustomEventListeners(CUSTOM_ON_SKILL_ATTACK);
}


void BattleMapLayer::playAvatarSound(EventCustom* message)
{
    Avatar* target = (Avatar*)message->getUserData();
    int skillID = 0;
    
    switch (target->getActionState()) {
        case kActionStateSkill1:
            skillID = target->_avatarType == AvatarType::AVATAR_TYPE_HERO ? ((Hero*)target)->getDictHero()->skill7 : ((Monster*)target)->getDictMonster()->skill7;
            break;
        case kActionStateSkill2:
            skillID = target->_avatarType == AvatarType::AVATAR_TYPE_HERO ? ((Hero*)target)->getDictHero()->skill8 : ((Monster*)target)->getDictMonster()->skill8;
            break;
        case kActionStateSkill3:
            skillID = target->_avatarType == AvatarType::AVATAR_TYPE_HERO ? ((Hero*)target)->getDictHero()->skill9 : ((Monster*)target)->getDictMonster()->skill9;
            break;
        case kActionStateSkill4:
            skillID = target->_avatarType == AvatarType::AVATAR_TYPE_HERO ? ((Hero*)target)->getDictHero()->skill10 : ((Monster*)target)->getDictMonster()->skill10;
            break;
        default:
            break;
    }
    if(skillID)
    {
        DictSkill* dictSkill = DictSkillManager::getInstance()->getData(skillID);
        if(dictSkill&& dictSkill->soundFly.size())
        {
            SoundManager::playEffectMusic(dictSkill->soundFly.c_str());
        }
    }
}
void BattleMapLayer::playShakeScreen()
{
    this->stopAction(shakeAction);
    this->runAction(shakeAction);
}
void BattleMapLayer::onShakeEnd()
{
    this->setPosition(Point::ZERO);
}
void BattleMapLayer::onShowOtherAvatar(Avatar* selfAvatar)
{
    Vector<Node*> children = fightObjLayer->getChildren();
    Avatar* avatar = NULL;
    for(Node* node : children)
    {
        avatar = (Avatar*)node;
        avatar->setVisible(true);
       
    }
}
void BattleMapLayer::onHideOtherAvatar(Avatar* selfAvatar)
{

    Vector<Node*> children = fightObjLayer->getChildren();
    Avatar* avatar = NULL;
    for(Node* node : children)
    {
        avatar = (Avatar*)node;
        if(avatar != selfAvatar)
        {
            avatar->setVisible(false);
        }
        
    }
}
void BattleMapLayer::pauseOtherAvatar(Avatar* selfAvatar)
{
    if(selfAvatar && selfAvatar->isCamreIn)
    {
   
        return;
    }
    pauseBattle();
    Vector<Node*> children = fightObjLayer->getChildren();
    Avatar* avatar = NULL;
    for(Node* node : children)
    {
        avatar = (Avatar*)node;
        if(avatar == selfAvatar)
        {
            avatar->setLocalZOrder(5000);
            continue;
        }
       
        avatar->pauseAction();
    }
    if(selfAvatar)
    {
        this->setViewPointCenter(0.01, selfAvatar);
    }
   
}
void BattleMapLayer::resumeOtherAvatar()
{
    m_isbigSkilling = false;
    this->gotoBattle();
    Vector<Node*> children = fightObjLayer->getChildren();
    Avatar* avatar = NULL;
  
    for(Node* node : children)
    {
       avatar = (Avatar*)node;
       if(avatar->_avatarType == AVATAR_TYPE_HERO || avatar->_avatarType == AVATAR_TYPE_MONSTER)
       {
          avatar->resumeAction();
        }
    }
  

}
void BattleMapLayer::goonAvatarAction()
{
 
    this->gotoBattle();
    Vector<Node*> children = fightObjLayer->getChildren();
    Avatar* avatar = NULL;
    Hero* hero = NULL;
    for(Node* node : children)
    {
        avatar = (Avatar*)node;
        if(avatar->_avatarType == AVATAR_TYPE_MONSTER)
        {
            avatar->resumeAction();
            
        }
        else if(avatar->_avatarType == AVATAR_TYPE_HERO)
        {
            hero = (Hero*)avatar;
//            if(hero->_isMainHero)
//            {
//               if(m_attackClickCount > 1)
//               {
//                    this->onHeroActionFinished(hero);
//               }
//               
//            }
//            else
//            {
                avatar->resumeAction();
//            }
        }
       
    }
}
void BattleMapLayer::onTransferPoint(Point gridPoint)
{
    Point cp = gridPoint * MAP_TILED_WIDTH;
    cp.y = _mapHeight - cp.y;
   
    for(Hero* hero : * _heroList)
    {

        cp = MapDataManager::getInstance()->positionToSelfPostion(hero,cp);
        hero->_destinatsionPostion = cp;
        hero->setPosition(cp.x,cp.y);
    }

}