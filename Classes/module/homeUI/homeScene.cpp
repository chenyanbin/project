//  
//  homeScene.cpp
//  FightPass
//
//  Created by 超 顾 on 15/6/2.
//
//

#include "HomeScene.h"
#include "homeMainUI/mainUI/MainUI.h"
#include "../newPlayerGuide/NewPlayerGuild.h"
#include "../../commonData/enum/DictFunctionEnum.h"
#include "../chat/Chat_Scene.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../common/Dialog/Dialog.h"
#include "../../module/marquee/MarqueeManager.h"
HomeScene::HomeScene()
{
    
}
HomeScene::~HomeScene()
{
    if(m_simplePad)
    {
        m_simplePad = NULL;
    }
    CC_SAFE_RELEASE_NULL(homeBgMap);
}
bool HomeScene::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->isAnimation = false;
        this->setClickEnabled(true);
        this->isAbleGuiding = false;

        bref = true;
    } while (false);
    return bref;
}
Scene* HomeScene::showScene(int fromeScene)
{
    Scene* scene = Scene::create();
    HomeScene* layer = HomeScene::create();
    if(layer)
    {
        layer->setAnchorPoint(Point::ZERO);
        layer->setFromScene(fromeScene);
        scene->addChild(layer, 0, SCENE_TAG_MAINUI);
    }
    return scene;
}
void HomeScene::onEnter()
{
    BaseLayer::onEnter();
    addHomeMap();
    addSimplePad();
    this->addChat();

}
void HomeScene::onExit()
{
    BaseLayer::onExit();
    
}
void HomeScene::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void HomeScene::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    Dialog::showServerLoading(3);
    if(GlobalInfo::getInstance()->isFirstEnterMainScene)
    {
        MarqueeManager::getInstance()->requestMarqueeMsg();
    }
    
}
//-----------地图背景
void HomeScene::addHomeMap()
{
    homeBgMap = HomeMapUI::create();
    CC_SAFE_RETAIN(homeBgMap);
    this->addChild(homeBgMap,1);
    homeBgMap->setAnchorPoint(Point::ZERO);
    homeBgMap->setPositionX(VisibleRect::left().x);
    homeBgMap->setPositionY(VisibleRect::bottom().y);
    this->setContentSize(homeBgMap->getContentSize());
}
//-------------控制杆
void HomeScene::addSimplePad()
{

    m_simplePad = SimplePad::create(IMG_BATTLE_CONTROLBAR,100);
    m_simplePad->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(m_simplePad);
    m_simplePad->setDelegate(this->homeBgMap);
    
    m_simplePad->setPosition(150* GlobalInfo::getInstance()->screenScaleX,150* GlobalInfo::getInstance()->screenScaleX);
    this->addChild(m_simplePad, 2);

}
//--------------------人物信息
void HomeScene::addMainUI()
{
    MainUI::show(this, 2);
}

void HomeScene::addChat()
{
//    return;//先关掉了
    if (GlobalInfo::getInstance()->chatChannelIsOk) {
        onYaYaChanelLoginCallBack(NULL);
    }else
    {
        addUserMsg(CUSTOM_YAYA_CHANNELLOGIN_SUC,CC_CALLBACK_1(HomeScene::onYaYaChanelLoginCallBack, this));
    }
}
void HomeScene::onYaYaChanelLoginCallBack(EventCustom* msg)
{
    Chat_Scene* chat=Chat_Scene::create();
    chat->setPosition(0,VisibleRect::center().y-chat->getContentSize().height/2);
    this->addChild(chat,4);
}
//-----------------------------屏幕点击

////屏幕点击
//bool HomeScene::onTouchBegan(Touch *touch, Event *unused_event)
//{
//    Point mouseDownPoint= touch->getLocation();
//    m_simplePad->setPosition(mouseDownPoint);
//    return true;
//}
//void HomeScene::onTouchMoved(Touch *touch, Event *unused_event)
//{
//    
//}
//void HomeScene::onTouchEnded(Touch *touch, Event *unused_event)
//{
//    m_simplePad->setPosition(150* GlobalInfo::getInstance()->screenScaleX,150* GlobalInfo::getInstance()->screenScaleX);
//}
