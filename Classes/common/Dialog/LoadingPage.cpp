//
//  LoadingPage.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/12/2.
//
//

#include "LoadingPage.h"
#include "editor-support/cocostudio/CCArmature.h"
using namespace cocostudio;
LoadingPage::LoadingPage()
:pt(NULL)
,progressText(NULL)
,drumSpr(NULL)
,TAG_CONNECTWORD(1)
,TAG_LEFTHAND(2)
,TAG_RIGHTHAND(3)
,loadingText(NULL)
,m_textIndex(0)
{
    
}
LoadingPage::~LoadingPage()
{
    pt = NULL;
}
bool LoadingPage::init()
{

    ArmatureDataManager::getInstance()->removeArmatureFileInfo(IMG_PUBLIC_LOADING_EFFECT);
    // 连接该骨骼动画的资源
    ArmatureDataManager::getInstance()->addArmatureFileInfo(IMG_PUBLIC_LOADING_EFFECT);
    
    Armature* armature = Armature::create("loading");
    armature->setAnchorPoint(Point::ZERO);
    this->addChild(armature,0,TAG_BG);
    this->setContentSize(armature->getContentSize());
    this->setClickEnabled(true);
    setProgressCircle();

    return true;
}
LoadingPage* LoadingPage::create()
{
    LoadingPage* page = new LoadingPage();
    if(page && page->init())
    {
        page->autorelease();
        return page;
    }
    return NULL;
}
void LoadingPage::setProgressCircle()
{

    Sprite* progressBg = Sprite::create(IMG_PUBLIC_LOADING_CIRCLEBG);
    progressBg->setAnchorPoint(Point::ZERO);
    Armature* armature = (Armature*)this->getChildByTag(TAG_BG);
    this->addChild(progressBg,2);
    progressBg->setPosition((armature->getPositionX() + armature->getContentSize().width - progressBg->getContentSize().width)/2 , 150);
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


   
}
void LoadingPage::setDrum()
{
//    Armature* armature = (Armature*)this->getChildByTag(TAG_BG);
//    drumSpr = Node::create();
//    drumSpr->setAnchorPoint(Point::ZERO);
//    this->addChild(drumSpr,3);
//    Sprite* conntectWord = Sprite::create(IMG_PUBLIC_CONNECTING);
//    conntectWord->setAnchorPoint(Point::ZERO);
//
//    this->addChild(conntectWord,1,TAG_CONNECTWORD);
//    conntectWord->setPosition(armature->getPositionX() + armature->getContentSize().width/2 + 45 ,armature->getPositionY() + armature->getContentSize().height - conntectWord->getContentSize().height - 100 );
//    
//    Sprite* rightHand = Sprite::create(IMG_PUBLIC_LOADINGDOT);
//    rightHand->setAnchorPoint(Point(1,1));
//    drumSpr->addChild(rightHand,2,TAG_RIGHTHAND);
//    
//    Sprite* leftHand = Sprite::create(IMG_PUBLIC_LOADINGDOT);
//    leftHand->setAnchorPoint(Point(1,1));
//    leftHand->setFlippedX(true);
//    drumSpr->addChild(leftHand,1,TAG_LEFTHAND);
//    
//    leftHand->setPosition(Point::ZERO);
//    rightHand->setPosition(leftHand->getContentSize().width, 0);
//    
//    Size size = rightHand->getContentSize();
//    size.width = rightHand->getPositionX() + rightHand->getContentSize().width;
//    drumSpr->setContentSize(size);
//    drumSpr->setPosition(conntectWord->getPositionX() + conntectWord->getContentSize().width/2,conntectWord->getPositionY() + conntectWord->getContentSize().height);
//    leftHandHit();
}
void LoadingPage::leftHandHit()
{
    RotateBy* leftRotate = RotateBy::create(.08, 30);
    Node* leftHand = drumSpr->getChildByTag(TAG_LEFTHAND);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(LoadingPage::rightHandHit, this));
    leftHand->runAction(Sequence::create(leftRotate,leftRotate->reverse(),callBack, NULL));
}
void LoadingPage::rightHandHit()
{
    RotateBy* rotate = RotateBy::create(.08, 30);
    Node* leftHand = drumSpr->getChildByTag(TAG_RIGHTHAND);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(LoadingPage::leftHandHit, this));
    leftHand->runAction(Sequence::create(rotate,rotate->reverse(),callBack, NULL));
}
void LoadingPage::onEnter()
{
    BaseLayer::onEnter();
}
void LoadingPage::onExit()
{
    BaseLayer::onExit();
    ArmatureDataManager::getInstance()->removeArmatureFileInfo(IMG_PUBLIC_LOADING_EFFECT);
}
void LoadingPage::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
   
}
void LoadingPage::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    Armature* armature = (Armature*)this->getChildByTag(TAG_BG);
    armature->getAnimation()->playWithIndex(0);
    m_textIndex = 1;
    setBlackBg();
    setLoadingText();
    DelayTime* delay = DelayTime::create(3);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(LoadingPage::setLoadingText, this));
    RepeatForever* repeat = RepeatForever::create(Sequence::create(delay,callBack, NULL));
    this->runAction(repeat);
}
void LoadingPage::setLoadingText()
{
    if(loadingText && loadingText->getParent())
    {
        loadingText->removeFromParent();
    }
    if(m_textIndex > 49)
    {
        m_textIndex = 1;
    }
    string str = PublicShowUI::numberToString(m_textIndex);
    if(str.size() == 1)
    {
       str = "00" + str;
    }
    else if(str.size() == 2)
    {
        str = "0" + str;
    }
    str  = PublicShowUI::getResImgPath(IMG_PUBLIC_LOADING_TEXT, str.c_str());
    loadingText = Sprite::create(str.c_str());
    
    if(pt)
    {
    
        Node* parent = pt->getParent();

        loadingText->setPosition((parent->getContentSize().width)/2,  - loadingText->getContentSize().height - 25);
        parent->addChild(loadingText,6);
     
        
    }
    m_textIndex++;
    
    
   
}
void LoadingPage::setBlackBg()
{
    Size size = VisibleRect::getVisibleRect().size * 3;
    LayerColor* layer = LayerColor::create(Color4B(0,0,0,255), size.width, size.height);
    layer->setAnchorPoint(Point::ZERO);
    this->setContentSize(layer->getContentSize());
    this->addChild(layer,-2,TAG_BLACKBG);

}

void LoadingPage::setProgressPercent(float progress)
{
    if(pt)
    {
        pt->setPercentage(progress);
        
        Node* parent = pt->getParent();
        string str = "军师莫急，俺在玩命中 " + PublicShowUI::numberToString((int)progress) + "%";
        if(progressText)
        {
          
            progressText->setString(str);
        }
        else
        {
            progressText = PublicShowUI::getLabel(str.c_str(),Color3B::WHITE,18,false,false);
            progressText->setPosition((parent->getContentSize().width)/2, -progressText->getContentSize().height/2 - 2);
            parent->addChild(progressText,7);

        }
        
    }
}