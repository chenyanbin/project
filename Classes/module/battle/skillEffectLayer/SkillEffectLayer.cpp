//
//  SkillEffectLayer.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/6/15.
//
//

#include "SkillEffectLayer.h"
#include "../../../commonData/dictData/DictSkill/DictSkillManager.h"
#include "../../../AppMacros.h"
#include "../../../common/StringUtil.h"
#include "../../../commonData/enum/DictSkillTypeEnum.h"
SkillEffectLayer::SkillEffectLayer()
:m_callBack(NULL)
,m_objectMap(NULL)
,dataList(NULL)
,m_tiledWidth(0)
,m_tiledHeight(0)
{
    dataList = new Map<int,SkillAttackData*>();
}
SkillEffectLayer::~SkillEffectLayer()
{
    m_callBack = NULL;
    dataList->clear();
    CC_SAFE_DELETE(dataList);
    dataList = NULL;
}
bool SkillEffectLayer::init(TMXTiledMap* objectMap,ccMenuCallback skillAttackCallBack)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->m_objectMap = objectMap;
        
        m_tiledWidth = m_objectMap->getTileSize().width;
        m_tiledHeight = m_objectMap->getTileSize().height;
        this->m_callBack = skillAttackCallBack;
        bref = true;
    } while (false);
    return bref;
}
SkillEffectLayer* SkillEffectLayer::create(TMXTiledMap* objectMap,ccMenuCallback skillAttackCallBack)
{
    SkillEffectLayer* layer = new SkillEffectLayer();
    if(layer && layer->init(objectMap,skillAttackCallBack))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void SkillEffectLayer::addSkillEffect(Avatar* target,int skillID,int team)
{
    SkillAttackData* data = NULL;
    auto iter = dataList->find(skillID);
   if (iter != dataList->end())
   {
       log("正在技能效果中..");
       return;
   }
    
    data = dataList->at(skillID);

    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(skillID);
    if(!dictSkill)
    {
        return;
    }
    data = new SkillAttackData(target,team);
    data->autorelease();
    data->setDictSkill(dictSkill);
    float posX = target->getPositionX();
    data->_destinatsionPostion = target->getPosition();
    data->_bombPoint = target->getPosition();
    data->_releasePoint = data->_bombPoint;
    data->_frontHurtRange = dictSkill->hurtForward;
    data->_backHurtRange = dictSkill->hurtBackward;
    data->_frontFindRange = dictSkill->effectRangeForward;
    data->_backFindRange = dictSkill->effectRangeBackward;
    data->_isLeft = target->isLeft;
    data->_isSkillAttack = target->_actionState == kActionStateSkill1 ||  target->_actionState == kActionStateSkill2 ||  target->_actionState == kActionStateSkill3  ||  target->_actionState == kActionStateSkill4 ;
    data->buffList = StringUtil::split(dictSkill->toBuffId, ",");
    if(target->_frameEvent == SKILL_ATTACK_EVENT || dictSkill->type == DictSkillTypeEnumPassiveSkill)
    {
   
        data->onSkillAttack(1);
        return;
    }
 
    if(dictSkill->flyResource.size())
    {
        data->setReleaseEffect(SkillEffect::create(dictSkill->flyResource.c_str(),dictSkill->resourceHighShifting,dictSkill->flyRLoopMarker));
        data->getReleaseEffect()->m_actionAttackCallBack = CC_CALLBACK_0(SkillAttackData::onSkillAttack, data,2);
       
    }
    else if(dictSkill->fullScreen.size())
    {//全屏特效字段用于控制摄像机移动了。

        data->onSkillAttack(1);
        return;
    }
    else
    {
      
        data->onSkillAttack(1);
        return;
    }
    
    
    if(dictSkill->effectBlastForward)
    {
        
        data->_destinatsionPostion.x =   target->isLeft ? data->_destinatsionPostion.x - dictSkill->effectBlastForward * m_tiledWidth : data->_destinatsionPostion.x + dictSkill->effectBlastForward * m_tiledWidth;
        posX = target->getPositionX();
       data->_frontHurtRange = dictSkill->effectBlastForward;
    }
    else if(dictSkill->effectBlastBackward)
    {
        data->_destinatsionPostion.x =   target->isLeft ? data->_destinatsionPostion.x + dictSkill->effectBlastBackward * m_tiledWidth : data->_destinatsionPostion.x - dictSkill->effectBlastBackward * m_tiledWidth;
        posX = target->getPositionX();
         data->_backHurtRange = dictSkill->effectBlastBackward;
    }
    else if(dictSkill->effectRangeForward)
    {
        data->_destinatsionPostion.x =   target->isLeft ? data->_destinatsionPostion.x - dictSkill->effectRangeForward * m_tiledWidth : data->_destinatsionPostion.x + dictSkill->effectRangeForward * m_tiledWidth;
        posX = target->getPositionX();
         data->_frontFindRange = dictSkill->effectRangeForward;
    }
    else if(dictSkill->effectRangeBackward)
    {
        data->_destinatsionPostion.x =   target->isLeft ? data->_destinatsionPostion.x + dictSkill->effectRangeBackward * m_tiledWidth : data->_destinatsionPostion.x - dictSkill->effectRangeBackward * m_tiledWidth;
        posX = target->getPositionX();
        data->_backFindRange = dictSkill->effectRangeBackward;
    }

  
    if(dictSkill->effectPositionForward)
    {//地刺
         posX = target->isLeft ? target->getPositionX() - dictSkill->effectPositionForward * m_tiledWidth : target->getPositionX() + dictSkill->effectPositionForward * m_tiledWidth;
        data->_destinatsionPostion.x = posX;
        data->_bombPoint.x = posX;
        data->_bombPoint.y = data->_destinatsionPostion.y;
        data->_frontFindRange = dictSkill->hurtForward;
    }
    if(dictSkill->effectPositionBackward)
    {//地刺
        posX = target->isLeft ? target->getPositionX() + dictSkill->effectPositionBackward * m_tiledWidth : target->getPositionX() -dictSkill->effectPositionBackward * m_tiledWidth;
         data->_destinatsionPostion.x = posX;
        
        data->_bombPoint.x = posX;
        data->_bombPoint.y = data->_destinatsionPostion.y;
        data->_backFindRange = dictSkill->hurtBackward;
    }
   
    dataList->insert(skillID, data);
    data->getReleaseEffect()->setAnchorPoint(Point(0.5,0));
    data->getReleaseEffect()->setPosition(posX,data->_destinatsionPostion.y);
    data->getReleaseEffect()->setScaleX(target->isLeft ? -1 : 1);
    this->addChild(data->getReleaseEffect());
    MoveBy* moveBy = NULL;
    if(data->_frontFindRange)
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
       moveBy = MoveBy::create(dictSkill->flyResourceTime, Point(data->getReleaseEffect()->getScaleX() * data->_frontFindRange * m_tiledWidth,0));
    }
    else if(data->_backFindRange)
    {
        moveBy = MoveBy::create(dictSkill->flyResourceTime, Point(-                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       data->getReleaseEffect()->getScaleX() * m_tiledWidth,0));
    }
    else
    {
        moveBy = MoveBy::create(dictSkill->flyResourceTime, Point(0,0));
    }
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(SkillEffectLayer::onFlyEffectEnd, this,data));
    data->getReleaseEffect()->runAction(Sequence::create(moveBy,callBack, NULL));
}
void SkillEffectLayer::onFlyEffectEnd(SkillAttackData* target)
{
    if(target->getReleaseEffect()->getParent())
    {
        target->getReleaseEffect()->removeFromParent();
    }
    dataList->erase(target->getDictSkill()->id);
}
void SkillEffectLayer::update(float dt)
{
//    Vector<SkillAttackData*>* removeList = new Vector<SkillAttackData*>();
//    Point cp;
//    bool isPlayOver = false;
//    bool isArrive = false;
//    for(auto value : *dataList)
//    {
//        SkillAttackData* data  = ( SkillAttackData* )value.second;
//   
//        isPlayOver = data->getReleaseEffect()->isPlayOver();
//        cp = data->_destinatsionPostion;
//        isArrive = false;
//        if(data->getReleaseEffect()->getScaleX() == -1)
//        {
//            if(data->_frontFindRange || data->_backFindRange)
//            {
//                cp.x = data->getReleaseEffect()->getPositionX() - 800 * dt;
//                data->getReleaseEffect()->setPosition(cp);
//                isArrive = cp.x <= data->_destinatsionPostion.x;
//            }
//            else
//            {
//                isArrive = true;
//            }
//           
//        }
//        else
//        {
//            if(data->_frontFindRange || data->_backFindRange)
//            {
//                 cp.x = data->getReleaseEffect()->getPositionX() + 800 * dt;
//                 data->getReleaseEffect()->setPosition(cp);
//                isArrive = cp.x >= data->_destinatsionPostion.x;
//            }
//            else
//            {
//                isArrive = true;
//            }
//        }
//        if(isPlayOver && isArrive)
//        {
//            removeList->pushBack(data);
//        }
//    }
//    for(auto value : * removeList)
//    {
//        if(value->getReleaseEffect()->getParent())
//        {
//            value->getReleaseEffect()->removeFromParent();
//        }
//        dataList->erase(value->getDictSkill()->id);
//    }
//    removeList->clear();
//    delete removeList;
//    removeList = NULL;
}

void SkillEffectLayer::onEnter()
{
    Layer::onEnter();
//    this->scheduleUpdate();
}
void SkillEffectLayer::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
 
}
void SkillEffectLayer::onExit()
{
    Layer::onExit();
}
void SkillEffectLayer::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
//    this->unscheduleUpdate();
}