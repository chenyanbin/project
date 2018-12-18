//
//  ServerLoadingLayer.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 15/1/14.
//
//
#include "Dialog.h"
#include "ServerLoadingLayer.h"
#include "../../net/NetworkDataProcessing.h"
#include "editor-support/cocostudio/CCArmature.h"
#include "../../avatar/hero/Hero.h"
using namespace cocostudio;
ServerLoadingLayer::ServerLoadingLayer()
:TAG_CONNECTWORD(1)
,m_dotContainer(NULL)
,delayTimes(0)
,isShowReLogin(true)
,TAG_LEFTHAND(2)
,TAG_RIGHTHAND(3)
{
    
}
ServerLoadingLayer::~ServerLoadingLayer()
{
    m_dotContainer = NULL;
}
bool ServerLoadingLayer::init(float timess)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        
        
        m_dotContainer = Node::create();
        m_dotContainer->setAnchorPoint(Point::ZERO);
        this->addChild(m_dotContainer,2);

        this->setClickEnabled(true);
        this->isAnimation = false;
        this->isShowGrayBg = false;
        this->isAbleGuiding = false;
        delayTimes = timess;
        if(delayTimes > 0)
        {
            m_dotContainer->runAction(Sequence::create(DelayTime::create(timess),CallFunc::create(CC_CALLBACK_0(ServerLoadingLayer::initLoading, this)), NULL));
        }
        else
        {
            initLoading();
        }
        
        bref = true;
    } while (false);
    return bref;

}
ServerLoadingLayer* ServerLoadingLayer::create(float timess)
{
    ServerLoadingLayer* layer = new ServerLoadingLayer();
    if (layer && layer->init(timess))
    {
        layer->autorelease();
        return layer;
    }
  
    delete layer;
    layer = NULL;
    return NULL;
    
}
void ServerLoadingLayer::onEnter()
{
    BaseLayer::onEnter();

    
}
void ServerLoadingLayer::onExit()
{
    this->unschedule(schedule_selector(ServerLoadingLayer::onDelay));
    BaseLayer::onExit();
    this->stopAllActions();;
    this->setClickEnabled(false);
}
void ServerLoadingLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    this->unschedule(schedule_selector(ServerLoadingLayer::onDelay));
}
void ServerLoadingLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onExitTransitionDidStart();
     this->unschedule(schedule_selector(ServerLoadingLayer::onDelay));
  
    
    if(GlobalInfo::getInstance()->addressIP.size() <= 0 || GlobalInfo::getInstance()->port <= 0)
    {
        this->schedule(schedule_selector(ServerLoadingLayer::onDelay), 50);
    }
    else
    {
        if(!NetworkDataProcessing::getInstance()->socketIsOk && GlobalInfo::getInstance()->gameRole->roleID != 0)
        {
            onDelay(0);
        }
        else
        {
            this->schedule(schedule_selector(ServerLoadingLayer::onDelay), 15);
        }
    }
    
    this->setClickEnabled(true);
}
void ServerLoadingLayer::onDelay(float dt)
{
    this->unschedule(schedule_selector(ServerLoadingLayer::onDelay));
   
    if(isShowReLogin)
    {
        
        if(NetworkDataProcessing::getInstance()->socketIsOk)
        {
            Dialog::show("网络信号不佳或连接已经断开，是否重新登陆游戏?","",2,this,callfuncN_selector(ServerLoadingLayer::onDialogEvent));
        }
        else
        {
            NetworkDataProcessing::sharedNet()->reConnectNet();
        }
    }
    else
    {
        NetworkDataProcessing::sharedNet()->reConnectNet();
    }
    if(this->getParent())
    {
        this->removeFromParent();
    }
    
}
void ServerLoadingLayer::onDialogEvent(Node* pSender)
{
   
    if(pSender && pSender->getTag() == 1)
    {
        if(NetworkDataProcessing::getInstance()->socketIsOk)
        {
            NetworkDataProcessing::getInstance()->reLogin();
        }
        else
        {
            NetworkDataProcessing::sharedNet()->reConnectNet();
        }
    }
}
void ServerLoadingLayer::initLoading()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    float _scale = .5 * GlobalInfo::getInstance()->screenScaleX;
    
    Sprite* conntectWord = Sprite::create(IMG_PUBLIC_CONNECTING);
    if(!conntectWord)
    {
        return;
    }
    conntectWord->setAnchorPoint(Point::ZERO);
    conntectWord->setScale(_scale);
    conntectWord->setContentSize(conntectWord->getContentSize() * _scale);
    conntectWord->setPosition(VisibleRect::center().x - conntectWord->getContentSize().width/2, VisibleRect::center().y + 4 * sx);
    this->addChild(conntectWord,1,TAG_CONNECTWORD);


    Sprite* rightHand = Sprite::create(IMG_PUBLIC_LOADINGDOT);
    rightHand->setAnchorPoint(Point(1,1));
    m_dotContainer->addChild(rightHand,2,TAG_RIGHTHAND);

    Sprite* leftHand = Sprite::create(IMG_PUBLIC_LOADINGDOT);
    leftHand->setAnchorPoint(Point(1,1));
    leftHand->setFlippedX(true);
    m_dotContainer->addChild(leftHand,1,TAG_LEFTHAND);

    leftHand->setPosition(Point::ZERO);
    rightHand->setPosition(leftHand->getContentSize().width, 0);

    Size size = rightHand->getContentSize();
    size.width = rightHand->getPositionX() + rightHand->getContentSize().width;
    m_dotContainer->setContentSize(size * _scale);
    m_dotContainer->setScale(_scale);
    m_dotContainer->setPosition(VisibleRect::center().x,conntectWord->getPositionY() + conntectWord->getContentSize().height + 12 * sx);
    leftHandHit();
    
    
//    const char* path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH, "Azhaoyun");
//    
//    ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
//    // 连接该骨骼动画的资源
//    ArmatureDataManager::getInstance()->addArmatureFileInfo(path);
//    AnimationData* animationData = ArmatureDataManager::getInstance()->getAnimationData("Azhaoyun");
//    if(animationData)
//    {
//        Armature* armature = Armature::create("Azhaoyun");
//        armature->setAnchorPoint(Point(.5,0));
//        armature->setScale(.5 * GlobalInfo::getInstance()->screenScaleX);
//        armature->setPosition(VisibleRect::center().x,VisibleRect::center().y + 10 * GlobalInfo::getInstance()->screenScaleX);
//        this->addChild(armature,2);
//        armature->getAnimation()->play(AN_MOVE);
//    }
    

    setGrayBg();
}
void ServerLoadingLayer::leftHandHit()
{
    RotateBy* leftRotate = RotateBy::create(.08, 30);
    Node* leftHand = m_dotContainer->getChildByTag(TAG_LEFTHAND);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(ServerLoadingLayer::rightHandHit, this));
    leftHand->runAction(Sequence::create(leftRotate,leftRotate->reverse(),callBack, NULL));

}
void ServerLoadingLayer::rightHandHit()
{
    RotateBy* rotate = RotateBy::create(.08, 30);
    Node* leftHand = m_dotContainer->getChildByTag(TAG_RIGHTHAND);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(ServerLoadingLayer::leftHandHit, this));
    leftHand->runAction(Sequence::create(rotate,rotate->reverse(),callBack, NULL));
}
void ServerLoadingLayer::setLoadingDot()
{
    ssize_t num = m_dotContainer->getChildrenCount();
    if(num >= 6)
    {
        m_dotContainer->removeAllChildren();
        num = 0;
    }
    Sprite* dot = Sprite::create(IMG_PUBLIC_LOADINGDOT);
    dot->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(dot);
    dot->setPosition(num * dot->getContentSize().width,0);// num *  -2 * GlobalInfo::getInstance()->screenScaleX
    m_dotContainer->addChild(dot);
}