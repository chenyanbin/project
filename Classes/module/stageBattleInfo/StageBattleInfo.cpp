//
//  StageBattleInfo.cpp
//  FightPass
//
//  Created by zhangbin on 16/3/22.
//
//

#include "StageBattleInfo.hpp"
#include "../userWealth/UserWealthLayer.h"
#include "BattleInfo.hpp"
#include "StageBattleBox.hpp"
StageBattleInfo::StageBattleInfo()
:m_stageID(0)
,boxData(NULL)
,stageBattleList(NULL)
,TAG_INFOLAYER(1)
{
    stageBattleList = new Vector<BattleData*>();
}
StageBattleInfo::~StageBattleInfo()
{
    CC_SAFE_DELETE(boxData);
    boxData = NULL;
    CC_SAFE_DELETE(stageBattleList);
    stageBattleList = NULL;
}
bool StageBattleInfo::init(ByteStream* byteStream)
{
    this->setContentSize(VisibleRect::getVisibleRect().size);
    setUserWealth();
    float sx = GlobalInfo::getInstance()->screenScaleX;
    this->setBackBtn(0,15*sx,true);
    parseByteStream(byteStream);
    setInfoLayer();
    setBoxLayer();
    this->isShowGrayBg = true;
    return true;
}
StageBattleInfo* StageBattleInfo::create(ByteStream* byteStream)
{
    StageBattleInfo* layer = new StageBattleInfo();
    if(layer && layer->init(byteStream))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void StageBattleInfo::show(ByteStream* byteStream)
{
    StageBattleInfo* layer = StageBattleInfo::create(byteStream);

    layer->isHideSceneFun = true;
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    Scene* scene = Director::getInstance()->getRunningScene();
    scene->addChild(layer,SCENE_MODULAR_TAG,SCENE_TAG_SWEEP);

}
void StageBattleInfo::setBoxLayer()
{
    Node* infoLayer = this->getChildByTag(TAG_INFOLAYER);
    
    StageBattleBox* layer = StageBattleBox::create(this->boxData);
    layer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(layer);
    layer->setPosition(infoLayer->getPositionX() + infoLayer->getContentSize().width ,infoLayer->getPositionY() + infoLayer->getContentSize().height - layer->getContentSize().height);
    this->addChild(layer,5);
}
void StageBattleInfo::setUserWealth()
{
    
    UserWealthLayer* layer = UserWealthLayer::create(UserWealthLayer::STAGE);
    PublicShowUI::setTargetScale(layer);
    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2, VisibleRect::top().y-layer->getContentSize().height);
    this->addChild(layer,3);
    
    layer->setTitle(IMG_PUBLIC_CAMPAIGN);
    
}
void StageBattleInfo::setGrayBg()
{
    if(this->getChildByTag(TAG_BLACKBG))
    {
        return;
    }
    Size size = VisibleRect::getVisibleRect().size;
    LayerColor* layer = LayerColor::create(Color4B(0,0,0,210), size.width*3, size.height*3);
    layer->setPositionX(-this->getPositionX() - size.width/2);
    layer->setPositionY(-this->getPositionY() - size.height/2);
    this->addChild(layer,-2,TAG_BLACKBG);

}
void StageBattleInfo::setInfoLayer()
{
    BattleInfo* layer = BattleInfo::create(this->m_stageID, this->stageBattleList);
    layer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(layer);
    layer->setPosition(VisibleRect::center().x -layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2-40*GlobalInfo::getInstance()->screenScaleX);
    this->addChild(layer,1,TAG_INFOLAYER);
}
void StageBattleInfo::parseByteStream(ByteStream* byteStream)
{
    
    boxData = new BattleBox();
    m_stageID = byteStream->getInt();
    boxData->canOpenCount = byteStream->get();
    boxData->canOpenBoxId = byteStream->getInt();
    boxData->starCountMax = byteStream->get();
    boxData->curStarCount = byteStream->get();
    boxData->raidsCardCount = byteStream->getShort();//扫荡令个数
    GlobalInfo::getInstance()->raidsCard =  boxData->raidsCardCount;
    BattleData* battleData = NULL;
    int len = byteStream->get();
    for(int i =0 ;i <len; i++)
    {
        battleData = new BattleData();
        battleData->autorelease();
        battleData->battleId = byteStream->getInt();
        battleData->starCount = byteStream->get();
        battleData->usableCount = byteStream->get();
        battleData->state = byteStream->get();
        stageBattleList->pushBack(battleData);
    }
}
void StageBattleInfo::onEnter()
{
    BaseLayer::onEnter();
}
void StageBattleInfo::onExit()
{
    BaseLayer::onExit();
}
void StageBattleInfo::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void StageBattleInfo::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void StageBattleInfo::addEventListener()
{
    
}
void StageBattleInfo::removeEventListener()
{
    BaseLayer::removeEventListener();
}
