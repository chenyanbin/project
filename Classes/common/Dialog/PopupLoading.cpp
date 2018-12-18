//
//  PopupLoading.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 14-7-18.
//
//

#include "PopupLoading.h"
#include "../PublicShowUI.h"
#include "../Dialog/Dialog.h"
#include "editor-support/cocostudio/CCArmature.h"
#include "../../avatar/hero/Hero.h"
using namespace cocostudio;
PopupLoading::PopupLoading()
:pt(NULL)
,progressText(NULL)
,isAutoRemove(false)
,m_dotContainer(NULL)
,TAG_CONNECTWORD(2)
,TAG_LEFTHAND(3)
,TAG_RIGHTHAND(4)
{
    
}
PopupLoading::~PopupLoading()
{
    progressText = NULL;
    pt = NULL;
    m_dotContainer = NULL;
}
bool PopupLoading::init(float timess)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->setClickEnabled(true);
        this->isAnimation = false;
        this->isAbleGuiding = false;
        m_dotContainer = Node::create();
        m_dotContainer->setAnchorPoint(Point::ZERO);
        this->addChild(m_dotContainer,2);
        if(timess > 0)
        {
            this->runAction(Sequence::create(DelayTime::create(timess),CallFunc::create(CC_CALLBACK_0(PopupLoading::initLoading, this)), NULL));
        }
        else
        {
            initLoading();
        }
        
        bref = true;
    } while (false);
    return bref;
}
PopupLoading* PopupLoading::create(float timess)
{
    PopupLoading* layer = new PopupLoading();
    if (layer && layer->init(timess))
    {
        layer->autorelease();
        return layer;
    }
    else
    {
        delete layer;
        layer = NULL;
        return NULL;
    }
}
void PopupLoading::initLoading()
{

    this->setGrayBg();
    LayerColor* layer = (LayerColor*)this->getChildByTag(TAG_BLACKBG);
    layer->setColor(Color3B::BLACK);
    
    setProgress();
}
//void PopupLoading::setProgress()
//{
//    Sprite* circle = Sprite::create(IMG_PUBLIC_LOADING_CIRCLEBG);
//    circle->setAnchorPoint(Point::ZERO);
//    this->addChild(circle,2);
//    pt=ProgressTimer::create(Sprite::create(IMG_PUBLIC_LOADING_CIRCLEMASK));
//    //转圈的CD实现
//    
//    pt->setPosition(circle->getContentSize().width/2, circle->getContentSize().height/2);
//    pt->setType(ProgressTimer::Type::RADIAL);
//    circle->setPositionY(100 * GlobalInfo::getInstance()->screenScaleX);
//    circle->addChild(pt,2);
//    pt->setPercentage(0);
//    
//    progressText = PublicShowUI::getNumbers(100,IMG_PUBLIC_NUMBER7);//PublicShowUI::getLabelNumber("100%", Color3B::BLACK, 20, false, false);
//    circle->addChild(progressText,3);
//    progressText->setPosition((circle->getContentSize().width - progressText->getContentSize().width)/2, (circle->getContentSize().height - progressText->getContentSize().height)/2);
//    
//    PublicShowUI::setTargetScale(circle,false,false);
//    this->setContentSize(circle->getContentSize() * GlobalInfo::getInstance()->screenScaleX);
//    
//    ArmatureDataManager::getInstance()->removeArmatureFileInfo(IMG_PUBLIC_LOADING_TEXT);
//    ArmatureDataManager::getInstance()->addArmatureFileInfo(IMG_PUBLIC_LOADING_TEXT);
//    Armature* armature = Armature::create("image_public_loading_text");
//    armature->getAnimation()->playWithIndex(0);
//    armature->setAnchorPoint(Point(.5,1));
//    PublicShowUI::setTargetScale(armature,false,false);
//    armature->setPosition(this->getContentSize().width/2, 50 * GlobalInfo::getInstance()->screenScaleX);
//    this->addChild(armature,10);
//}
//void PopupLoading::setProgress()
//{
//    Sprite* conntectWord = Sprite::create(IMG_PUBLIC_CONNECTING);
//    conntectWord->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(conntectWord);
//    conntectWord->setPosition(VisibleRect::center().x - conntectWord->getContentSize().width/2, VisibleRect::center().y + 4 * GlobalInfo::getInstance()->screenScaleX);
//    this->addChild(conntectWord,1,TAG_CONNECTWORD);
//    
//    
//    Sprite* rightHand = Sprite::create(IMG_PUBLIC_LOADINGDOT);
//    rightHand->setAnchorPoint(Point(1,1));
//    m_dotContainer->addChild(rightHand,2,TAG_RIGHTHAND);
//    
//    Sprite* leftHand = Sprite::create(IMG_PUBLIC_LOADINGDOT);
//    leftHand->setAnchorPoint(Point(1,1));
//    leftHand->setFlippedX(true);
//    m_dotContainer->addChild(leftHand,1,TAG_LEFTHAND);
//    
//    leftHand->setPosition(Point::ZERO);
//    rightHand->setPosition(leftHand->getContentSize().width, 0);
//    
//    Size size = rightHand->getContentSize();
//    size.width = rightHand->getPositionX() + rightHand->getContentSize().width;
//    m_dotContainer->setContentSize(size);
//    PublicShowUI::setTargetScale(m_dotContainer);
//    m_dotContainer->setPosition(VisibleRect::center().x,conntectWord->getPositionY() + conntectWord->getContentSize().height);
//    leftHandHit();
//    
//    ArmatureDataManager::getInstance()->removeArmatureFileInfo(IMG_PUBLIC_LOADING_TEXT);
//    ArmatureDataManager::getInstance()->addArmatureFileInfo(IMG_PUBLIC_LOADING_TEXT);
//    Armature* armature = Armature::create("image_public_loading_text");
//    armature->getAnimation()->playWithIndex(0);
//    armature->setAnchorPoint(Point(.5,1));
//    PublicShowUI::setTargetScale(armature,false,false);
//    armature->setPosition(VisibleRect::center().x,conntectWord->getPositionY() - 10);
//    this->addChild(armature,10);
//}
void PopupLoading::setProgress()
{
    
    Sprite* progressBg = Sprite::create(IMG_PUBLIC_LOADING_CIRCLEBG);
    progressBg->setAnchorPoint(Point::ZERO);
    this->addChild(progressBg,2);
    progressBg->setPosition(0, 0);
    Sprite* spr = Sprite::create(IMG_PUBLIC_LOADING_CIRCLEMASK);
    spr->setAnchorPoint(Point::ZERO);
    pt=ProgressTimer::create(spr);
    pt->setAnchorPoint(Point::ZERO);
    pt->setType(ProgressTimer::Type::BAR);
    pt->setMidpoint(Point(0,1));
    pt->setBarChangeRate(Point(1,0));
    pt->setPercentage(100);
    progressBg->addChild(pt,2);
    pt->setPosition((progressBg->getContentSize().width - pt->getContentSize().width)/2, (progressBg->getContentSize().height - pt->getContentSize().height)/2);
    
    PublicShowUI::setTargetScale(progressBg,false,false);
    this->setContentSize(progressBg->getContentSize() * GlobalInfo::getInstance()->screenScaleX);
    
    const char* path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH, "Azhaoyun");
    
    ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
    // 连接该骨骼动画的资源
    ArmatureDataManager::getInstance()->addArmatureFileInfo(path);
    AnimationData* animationData = ArmatureDataManager::getInstance()->getAnimationData("Azhaoyun");
    if(animationData)
    {
        Armature* armature = Armature::create("Azhaoyun");
        armature->setAnchorPoint(Point(.5,0));
        armature->setScale(.5);
        armature->setPosition(this->getContentSize().width/2, 50 * GlobalInfo::getInstance()->screenScaleX);
        this->addChild(armature,2);
        armature->getAnimation()->play(AN_MOVE);
    }
}
void PopupLoading::leftHandHit()
{
    RotateBy* leftRotate = RotateBy::create(.08, 30);
    Node* leftHand = m_dotContainer->getChildByTag(TAG_LEFTHAND);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(PopupLoading::rightHandHit, this));
    leftHand->runAction(Sequence::create(leftRotate,leftRotate->reverse(),callBack, NULL));
    
}
void PopupLoading::rightHandHit()
{
    RotateBy* rotate = RotateBy::create(.08, 30);
    Node* leftHand = m_dotContainer->getChildByTag(TAG_RIGHTHAND);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(PopupLoading::leftHandHit, this));
    leftHand->runAction(Sequence::create(rotate,rotate->reverse(),callBack, NULL));
}
void PopupLoading::setProgressPercent(float progress)
{
  
    if(pt)
    {
        pt->setPercentage(progress);
        string str = PublicShowUI::numberToString(int(progress)) + "%";
        if(progressText)
        {
            progressText->setString(str);
           
        }
        else
        {
            Node* parent = pt->getParent();

//            progressText = PublicShowUI::getNumbers(progress,IMG_PUBLIC_NUMBER7);
            progressText = PublicShowUI::getLabel(str.c_str(),Color3B::WHITE,18,false,false);
            progressText->setAnchorPoint(Point::ZERO);
            progressText->setPosition((parent->getContentSize().width - progressText->getContentSize().width)/2, -progressText->getContentSize().height - 2);
            parent->addChild(progressText,4);
        }
      
    }
}
void PopupLoading::onEnter()
{
    BaseLayer::onEnter();
    if(isAutoRemove)
    {
        this->schedule(schedule_selector(PopupLoading::onDelay), 80);
    }
   
}
void PopupLoading::onExit()
{
    BaseLayer::onExit();
    this->unschedule(schedule_selector(PopupLoading::onDelay));
    this->setClickEnabled(false);
  
//     ArmatureDataManager::getInstance()->removeArmatureFileInfo(IMG_PUBLIC_LOADING_TEXT);
}
void PopupLoading::onDelay(float dt)
{
    this->unschedule(schedule_selector(PopupLoading::onDelay));
    if(this->getParent())
    {
        this->removeFromParent();
    }
}