//
//  BaseLayer.cpp
//  TwoMahjong
//
//  Created by mac on 14-4-25.
//
//

#include "BaseLayer.h"
#include "homeUI/HomeScene.h"
#include "../common/TouchSprite/Button.h"
#include "battle/BattleLoader.h"
#include "homeUI/HomeLoader.h"
#include "stageLayer/StageLayer.h"
#include "sweep/SweepLayer.h"
#include "lineup/LineupLayer.h"
#include "market/MarketLayer.h"
#include "generals/generalsCard/GeneralsCard_Layer.h"
#include "chapter/ChapterLayer.h"
#include "musou/MusouLayer.h"
#include "generals/Generals_Layer.h"
#include "task/TaskLayer.h"
#include "login/LoginLayer.h"
#include "newPlayerGuide/NewPlayerGuild.h"
#include "famousGeneral/GeneralScene.hpp"
#include "famousGeneral/famouseBossCome/FamouseBossCome.hpp"
BaseLayer::BaseLayer()
:TAG_BG(-2)
,TAG_BLACKBG(-3)
,TAG_BACKBTN(0)
,m_fromScene(-1)
,m_eventDispatcher(NULL)
,m_touchAllDispatcher(NULL)
,keyboardListener(NULL)
,isAnimation(false)
,isClickClose(false)
,isShowGrayBg(false)
,isAbleGuiding(false)
,isTouchBegainThis(false)
,isShowOpenSound(false)
,isAutoReleasePlist(true)
,m_pvrPlistPath("")
,isHideSceneFun(false)

{
    
}
BaseLayer::~BaseLayer()
{
    userMsgList.clear();
    vector<string> msg;
    userMsgList.swap(msg);
    if(m_eventDispatcher)
    {
        CC_SAFE_RELEASE_NULL(m_eventDispatcher);
    }
    if(m_touchAllDispatcher)
    {
        CC_SAFE_RELEASE_NULL(m_touchAllDispatcher);
    }
    m_fromScene = -1;
    m_pvrPlistPath.clear();
}
bool BaseLayer::init()
{
    bool bref = false;
    do
    {
        CC_BREAK_IF(!Layer::init());
     
      
        bref = true;
    }while (false);
    return bref;
}
void  BaseLayer::addPvrPlist(const char* plistPath)//加载模块资源
{
    m_pvrPlistPath = plistPath;
    if(m_pvrPlistPath != "")
    {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(m_pvrPlistPath);
    }

}
void BaseLayer::onEnter()
{
    Layer::onEnter();
    addEventListener();

    if(isAnimation)
    {
        this->setScale(.5 );
        ActionInterval* act_fd = ScaleTo::create(0.1f, 1.2f);
        ActionInterval* act_f = ScaleTo::create(0.1f, 1.f);
        this->runAction(Sequence::create(act_fd,act_f,NULL));
    }

    if(isShowGrayBg)
    {
        this->setGrayBg();
    }
    
    if(isHideSceneFun)
    {
        this->broadMsg(CUSTOM_HIDE_SCENE_FUN);
    }
  
}
void BaseLayer::onExit()
{
    
    Layer::onExit();
    this->removeGrayBg();
   

//   log("BaseLayerBaseLayer~onExit~onExit~onExit==%d",this->getReferenceCount());
}
void BaseLayer::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
    removeEventListener();
    if(m_pvrPlistPath != "" && isAutoReleasePlist)
    {
        SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(m_pvrPlistPath);
    }
    
    if(isHideSceneFun)
    {
        this->broadMsg(CUSTOM_SHOW_SCENE_FUN);
        GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumBack);
    }
  
}
void BaseLayer::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    if(isShowOpenSound)
    {
//        SoundManager::playEffectMusic(EFFECT_UI_OPEN);
    }
    if(isAbleGuiding)
    {
        NewPlayerGuild::getInstance()->showNowGuide();
    }
}
void BaseLayer::addEventListener()
{
   
}
void BaseLayer::removeEventListener()
{
   
    _eventDispatcher->removeEventListenersForTarget(this);
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->removeEventListenersForTarget(this);
    
    ssize_t size = userMsgList.size();
    for(int i = 0; i < size; i++)
    {
        _eventDispatcher->removeCustomEventListeners(userMsgList.at(i));
    }
    this->setClickEnabled(false);
    this->setTouchAllEnabled(false);
    
}
void BaseLayer::setGrayBg()
{
    if(this->getChildByTag(TAG_BLACKBG))
    {
        return;
    }
    Size size = VisibleRect::getVisibleRect().size;
    LayerColor* layer = LayerColor::create(Color4B(0,0,0,170), size.width*3, size.height*3);
    layer->setPosition((VisibleRect::center().x-layer->getContentSize().width)/2,(VisibleRect::center().y-layer->getContentSize().height)/2);
    this->addChild(layer,-2,TAG_BLACKBG);
}
void BaseLayer::removeGrayBg()
{
    if(this->getChildByTag(TAG_BLACKBG))
    {
        this->removeChildByTag(TAG_BLACKBG);
    }
 
}
void BaseLayer::setClickEnabled(bool enabled,int proprity)
{
    if(m_eventDispatcher == NULL)
    {
        m_eventDispatcher = EventListenerTouchOneByOne::create();
        CC_SAFE_RETAIN(m_eventDispatcher);
    }
    if(enabled)
    {
       
        _eventDispatcher->removeEventListener(m_eventDispatcher);
        m_eventDispatcher->setSwallowTouches(true);
         m_eventDispatcher->onTouchBegan = CC_CALLBACK_2(BaseLayer::onTouchBegan, this);
         m_eventDispatcher->onTouchMoved = CC_CALLBACK_2(BaseLayer::onTouchMoved, this);
         m_eventDispatcher->onTouchEnded = CC_CALLBACK_2(BaseLayer::onTouchEnded, this);
         _eventDispatcher->addEventListenerWithSceneGraphPriority(m_eventDispatcher, this);
        _eventDispatcher->setPriority(m_eventDispatcher, proprity);
    }
    else
    {
        _eventDispatcher->removeEventListener(m_eventDispatcher);

    }
    
}
bool BaseLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    Rect rect = this->getBoundingBox();
    this->isTouchBegainThis = rect.containsPoint(touch->getLocation());
    log("isTouchBegainThis111111=%d",isTouchBegainThis);
    
    Rect r = PublicShowUI::getRect(this);
    isTouchBegainThis = r.containsPoint(touch->getLocation());
    log("isTouchBegainThis222222=%d",isTouchBegainThis);
    return true;
}
void BaseLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    
}
void BaseLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    if(isClickClose && !isTouchBegainThis)
    {
       
        Rect rect = PublicShowUI::getRect(this);;
        if(rect.containsPoint(touch->getLocation()) == false)
        {

            this->backScene();
            if(this->isShowOpenSound)
            {
//                SoundMa nager::playEffectMusic(EFFECT_UI_CLOSE);
            }
        }
        
    }
}
void BaseLayer::setTouchAllEnabled(bool enabled)//多点触摸
{
    if(m_touchAllDispatcher == NULL)
    {
        m_touchAllDispatcher = EventListenerTouchAllAtOnce::create();
        CC_SAFE_RETAIN(m_touchAllDispatcher);
    }
    if(enabled)
    {
        _eventDispatcher->removeEventListener(m_touchAllDispatcher);
       
        m_touchAllDispatcher->onTouchesBegan = CC_CALLBACK_2(BaseLayer::onTouchesBegan, this);
        m_touchAllDispatcher->onTouchesMoved = CC_CALLBACK_2(BaseLayer::onTouchesMoved, this);
        m_touchAllDispatcher->onTouchesEnded = CC_CALLBACK_2(BaseLayer::onTouchesEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(m_touchAllDispatcher, this);

    }
    else
    {
        _eventDispatcher->removeEventListener(m_eventDispatcher);
    }
}
void BaseLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    
}
void BaseLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    
}
void BaseLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    
}
//void BaseLayer::setKeypadEnabled(bool enabled)
//{
//    Layer::setKeyboardEnabled(enabled);
//    if(keyboardListener == NULL)
//    {
//        keyboardListener = EventListenerKeyboard::create();
//        keyboardListener->onKeyPressed = CC_CALLBACK_2(BaseLayer::onKeyPressed, this);
//        keyboardListener->onKeyReleased = CC_CALLBACK_2(BaseLayer::onKeyReleased, this);
//        
//        _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
//    }
//    else
//    {
//          _eventDispatcher->removeEventListener(keyboardListener);
//    }
//}
//
void BaseLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("22222Key with keycode %d pressed", keyCode);
}

void BaseLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("111111Key with keycode %d released backscene", keyCode);
    backScene();;
}
void BaseLayer::setBackground(const char* path,Point anchorPoint,bool isAutoScale)
{
    if(path == NULL)
    {
        path = IMG_PUBLIC_MODULE_BG;
    }
    Sprite* bg = NULL;
    if(this->m_pvrPlistPath != "")
    {
        bg = Sprite::createWithSpriteFrameName(path);
        if(!bg)
        {
            bg = Sprite::create(path);
        }
    }
    else
    {
        bg = Sprite::create(path);
        if(!bg)
        {
            bg = Sprite::createWithSpriteFrameName(path);
        }
    }
    
    if(!bg)
    {
        return;
    }
    bg->setAnchorPoint(anchorPoint);
    if(isAutoScale)
    {
         PublicShowUI::setTargetScale(bg);
    }
    this->setContentSize(bg->getContentSize());
   
    bg->setPosition(Point(0,0));

    this->addChild(bg,0,TAG_BG);
}
void BaseLayer::setFromScene(int fromScene)
{
    
    this->m_fromScene = fromScene;
}
int BaseLayer::getFromScene()
{
    return this->m_fromScene;
}
void BaseLayer::setBackBtn(float offX ,float offY,bool autoScale)
{
    Button* item = Button::create(IMG_PUBLIC_BACKBTN,"", CC_CALLBACK_1(BaseLayer::onBackClick, this));
    
    item->isShowClickSound = true;
    if(autoScale)
    {
       PublicShowUI::setTargetScale(item);
      
    }
    item->setPosition(VisibleRect::right().x - item->getContentSize().width + offX, VisibleRect::top().y - item->getContentSize().height + offY+10*GlobalInfo::getInstance()->screenScaleX);
    this->addChild(item,30,TAG_BACKBTN);
     GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumBack);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumBack, item);
   
}
void BaseLayer::onBackClick(Ref* pSender)
{
    if(this->isShowOpenSound)
    {
//        SoundManager::playEffectMusic(EFFECT_UI_CLOSE);
    }
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumBack);
    backScene();
}
void BaseLayer::backScene()
{
    Scene* scene = NULL;
    switch (this->m_fromScene) {
        case SCENE_TAG_MAINUI:

            LoginLayer::enterMainUI();
            break;
        case SCENE_TAG_GOTOBATTLE:
         
            StageLayer::show(SCENE_TAG_MAINUI);
            break;
        case SCENE_TAG_MARKET:
            MarketLayer::show(SCENE_TAG_MAINUI);
            break;
        case SCENE_TAG_CHOOSEEQUIP:
            GeneralsCard_Layer::show(SCENE_TAG_MAINUI, DictFunctionEnumEquip);
            break;
        case SCENE_TAG_CHAPTER:
            ChapterLayer::requestChapterByID();
            break;
        case SCENE_TAG_GENERALS:
            Generals_Layer::show(SCENE_TAG_MAINUI);
            break;
        case SCENE_TAG_GENERALS_LATER:
            Generals_Layer::show(SCENE_TAG_MAINUI,3);
            break;
        case SCENE_TAG_GENERALS_EQUIP:
            Generals_Layer::show(SCENE_TAG_MAINUI,2);
            break;
        case SCENE_TAG_GENERALS_MATERIAL:
            Generals_Layer::show(SCENE_TAG_MAINUI,1);
            break;
        case SCENE_TAG_GENERALS_PROPS:
            Generals_Layer::show(SCENE_TAG_MAINUI,0);
            break;
        case SCENE_TAG_MUSOU:
            MusouLayer::requestMuouList();
            break;
        case SCENE_TAG_GENERALSCARD:
            GeneralsCard_Layer::show(SCENE_TAG_MAINUI, DictFunctionEnumHeroProp);
            break;
        case SCENE_TAG_TASK:
            TaskLayer::show(SCENE_TAG_MAINUI, TaskLayer::TAG_PUTONG);
            break;
        case SCENE_TAG_DAILYTASK:
            TaskLayer::show(SCENE_TAG_MAINUI, TaskLayer::TAG_RICHANG);
            break;
        case SCENE_TAG_LINEUP:
            LineupLayer::show(SCENE_TAG_MAINUI, 1,0);
            break;
        case SCENE_TAG_LOADING:
            scene = LoginLayer::createScene();
            break;
        case SCENE_TAG_FAMOUSE:
            GeneralScene::show(SCENE_TAG_MAINUI);
            break;
        case SCENE_TAG_BOSSCOME:
            FamouseBossCome::show();
            break;
        case SCENE_TAG_GENERALS_STRONG:
            GeneralsCard_Layer::show(SCENE_TAG_MAINUI, DictFunctionEnumEquip);
            break;
        default:
            this->removeFromParent();
            break;
    }
    if(scene)
    {
        Director::getInstance()->purgeCachedData();
        Director::getInstance()->replaceScene(scene);
    }
}
void BaseLayer::addUserMsg(const char* msg,const std::function<void(EventCustom*)>& callback)
{
    EventDispatcher* dispatch = Director::getInstance()->getEventDispatcher();
    dispatch->addCustomEventListener(msg, callback);
    userMsgList.push_back(msg);
}
void BaseLayer::broadMsg(const char* msg, void* _userData)
{
    EventDispatcher* dispatch = Director::getInstance()->getEventDispatcher();
    EventCustom event(msg);
    event.setUserData(_userData);
    dispatch->dispatchEvent(&event);
}
