//
//  GeneralLayer.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/7.
//
//

#include "GeneralScene.hpp"
#include "../userWealth/UserWealthLayer.h"
#include "famouseLayer/FamouseLayer.hpp"
#include "../../message/Decoding/famouseGeneral/FamouseBaseInfoMsg.hpp"
#include "../../commonData/dictData/DictLegend/DictLegendManager.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../common/Dialog/Dialog.h"
#include "../../common/TimeUtil.h"
GeneralScene::GeneralScene()
:m_showPage(0)
,TAG_CHALEAGE_COUNT(1)
,TAG_ACTIVETIME(2)
,TAG_USERWEALTH(3)
,m_name("")
,m_activeStartTime("")
,m_activeEndTime("")
,m_nowChallengeCount(0)
,m_maxChanllengeCount(0)
{
    
}
GeneralScene::~GeneralScene()
{
    
}
bool GeneralScene::init(int showPage)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->m_showPage = showPage;
        this->isAnimation = false;
        setBg();
        this->setBackBtn(20 * GlobalInfo::getInstance()->screenScaleX,15 * GlobalInfo::getInstance()->screenScaleX,true);
        bref = true;
    } while (false);
    return bref;
}
GeneralScene* GeneralScene::create(int showPage)
{
    GeneralScene* scene = new GeneralScene();
    if(scene && scene->init(showPage))
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return NULL;
}
void GeneralScene::show(int fromeScene,int showPage)
{
    GeneralScene* layer = GeneralScene::create(showPage);
    layer->setFromScene(fromeScene);
    Scene* scene = Scene::create();
    scene->addChild(layer,0,SCENE_TAG_FAMOUSE);
    Director::getInstance()->replaceScene(scene);
}
void GeneralScene::setBg()
{
    Sprite* bg = Sprite::create(IMG_PUBLIC_MODULE_BG);
    float sx = PublicShowUI::getTagScale(bg);
    bg->setScale(sx);
    this->addChild(bg,0);
    bg->setPosition(VisibleRect::center());
}
void GeneralScene::setMoudleLayer()
{
    FamouseLayer* layer = FamouseLayer::create();
    layer->setInitPage(this->m_showPage);
    layer->setAnchorPoint(Point::ZERO);
    this->addChild(layer,1);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2 - 30 * GlobalInfo::getInstance()->screenScaleX);
}
void GeneralScene::onEnter()
{
    BaseLayer::onEnter();
}
void GeneralScene::onExit()
{
    BaseLayer::onExit();
}
void GeneralScene::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void GeneralScene::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    topLayer();
    setMoudleLayer();
    requestBaseInfo();
}
void GeneralScene::requestBaseInfo()
{
    Dialog::showServerLoading();
    FamouseBaseInfoMsg* msg  = new FamouseBaseInfoMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void GeneralScene::topLayer()
{
    UserWealthLayer* layer = (UserWealthLayer*)this->getChildByTag(TAG_USERWEALTH);
    if(!layer)
    {
        layer = UserWealthLayer::create(UserWealthLayer::FAMOUSE);
        PublicShowUI::setTargetScale(layer);
    }
  
    
    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2, VisibleRect::top().y-layer->getContentSize().height);
    this->addChild(layer,2,TAG_USERWEALTH);
    layer->setTitle(IMG_PUBLIC_MINGJIANGZHUAN);
    
}
void GeneralScene::setTitleBaseInfo()
{
    Node* layer = this->getChildByTag(TAG_USERWEALTH);
    if(this->getChildByTag(TAG_CHALEAGE_COUNT))
    {
        this->removeChildByTag(TAG_CHALEAGE_COUNT);
        this->removeChildByTag(TAG_ACTIVETIME);
    }
    
    
    Sprite* challengeCount = Sprite::create(IMG_FAMOUSE_CHALLENGECOUNT);
    challengeCount->setAnchorPoint(Point::ZERO);
    Size size = challengeCount->getContentSize();
    string str = PublicShowUI::numberToString(m_nowChallengeCount) + "/" + PublicShowUI::numberToString(m_maxChanllengeCount);
    Label* label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),22,false,false);
    label->setAnchorPoint(Point::ZERO);
    challengeCount->addChild(label,1);
    
    label->setPosition(challengeCount->getContentSize().width,(challengeCount->getContentSize().height - label->getContentSize().height)/2);
    size.width += label->getContentSize().width;
    challengeCount->setContentSize(size);
    PublicShowUI::setTargetScale(challengeCount);
    challengeCount->setPosition(290 * GlobalInfo::getInstance()->screenScaleX,layer->getPositionY() + (layer->getContentSize().height - challengeCount->getContentSize().height)/2);
    
    this->addChild(challengeCount,3,TAG_CHALEAGE_COUNT);
    
    Sprite* activeTime = Sprite::create(IMG_FAMOUSE_ACTIVETIME);
    activeTime->setAnchorPoint(Point::ZERO);
    
    str = m_activeStartTime + " / " + m_activeEndTime;
    label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),22,false,false);
    label->setAnchorPoint(Point::ZERO);
    activeTime->addChild(label,1);
    label->setPosition(activeTime->getContentSize().width,(activeTime->getContentSize().height - label->getContentSize().height)/2);
    PublicShowUI::setTargetScale(activeTime);
    activeTime->setPosition(challengeCount->getPositionX() + challengeCount->getContentSize().width + 5,challengeCount->getPositionY());
    
    this->addChild(activeTime,4,TAG_ACTIVETIME);
}
void GeneralScene::onMsgProcess(EventCustom* message)
{
    Dialog::hideServerLoading();
    MessageReceive* msg = (MessageReceive*)message->getUserData();
    if(!msg->state)
    {
        return;
    }
    if(msg->messageID == SCENSE_CLIENT_LEGEND_LegendBaseInfoResp)
    {
        m_name = msg->byteStream->getUTF8();
        long long startTime = msg->byteStream->getLong();
        m_activeStartTime = TimeUtil::timetodate(startTime / 1000);
        m_activeStartTime = m_activeStartTime.substr(0,m_activeStartTime.size() - 3);
        long long endtime = msg->byteStream->getLong();
        m_activeEndTime = TimeUtil::timetodate(endtime / 1000);
        m_activeEndTime = m_activeEndTime.substr(0,m_activeEndTime.size() - 3);
        m_nowChallengeCount = msg->byteStream->getShort();
        m_maxChanllengeCount = msg->byteStream->getShort();
        int period = msg->byteStream->getByte();
        GlobalInfo::getInstance()->famousePeroid = period;
        GlobalInfo::getInstance()->famouseChallengeCount = m_nowChallengeCount;
        DictLegend* legend = DictLegendManager::getInstance()->getData(period);
     
        GlobalInfo::getInstance()->famouseName = legend ? legend->legendName : PublicShowUI::numberToString(period);
        
        setTitleBaseInfo();
    }
}
void GeneralScene::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LEGEND_LegendBaseInfoResp).c_str(), CC_CALLBACK_1(GeneralScene::onMsgProcess, this));
}
void GeneralScene::removeEventListener()
{
    BaseLayer::removeEventListener();
}