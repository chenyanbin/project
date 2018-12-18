//
//  UserHeadLayer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/7/31.
//
//

#include "UserHeadLayer.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "../../common/TouchSprite/Button.h"
#include "../../commonData/enum/DictItemTypeEnum.h"
UserHeadLayer::UserHeadLayer()
:c_touchBegainTarget(NULL)
,c_touchBegainSelector(NULL)
,cardId(2)
,m_isHeroHead(false)
,TAG_LVBG(3)
,TAG_PREST(4)
,TAG_HEADBOX(5)
,TAG_TICK(6)
,TAG_HEAD(7)
,TAG_BLACKBG(8)
{
    
}
UserHeadLayer::~UserHeadLayer()
{
    _eventDispatcher->removeEventListenersForTarget(this);
    c_touchBegainTarget = NULL;
    c_touchBegainSelector = NULL;
}
void UserHeadLayer::onExit()
{
    Layer::onExit();
}
void UserHeadLayer::onEnter()
{
    Layer::onEnter();
}
void UserHeadLayer::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}
void UserHeadLayer::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
}
bool UserHeadLayer::init(const char* imgPath,int quality,bool isHeroHead)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        m_isHeroHead = isHeroHead;
        char stt[100]="";
        sprintf(stt,IMG_PUBLIC_HEADTALENTFRAME,1);
        Sprite* bgSprite=Sprite::create(stt);
        this->setContentSize(bgSprite->getContentSize());
        this->createLayer(imgPath,quality);
        bref = true;
    } while (false);
    return bref;
}

UserHeadLayer* UserHeadLayer::create(string imgPath,int quality,bool isHeroHead)
{
    const char* img=imgPath.c_str();
    UserHeadLayer* layer = new UserHeadLayer();
    if(layer && layer->init(img,quality,isHeroHead))
    {
        layer->autorelease();
        return layer;
    }
    else{
        CC_SAFE_DELETE(layer);
        layer = NULL;
        return NULL;
    }
}

void UserHeadLayer::createLayer(const char* imgPath,int quality)
{
    //头像
    string tempStr="no";
    if (strcmp(imgPath, tempStr.c_str())==0) {
        Button* headImg = Button::create(IMG_PUBLIC_TABLEVIEW_HERO,IMG_PUBLIC_TABLEVIEW_HERO, CC_CALLBACK_1(UserHeadLayer::onButtonClick, this));
        headImg->setPosition(Point::ZERO);
        this->addChild(headImg);
        return;
    }
    if(m_isHeroHead)
    {
        imgPath = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH, imgPath);
    }

    Button* headImg = Button::create(imgPath,imgPath, CC_CALLBACK_1(UserHeadLayer::onButtonClick, this));
    headImg->setAnchorPoint(Point::ZERO);
    headImg->getTouchListener()->setSwallowTouches(false);
    this->addChild(headImg,1,TAG_HEAD);
    
    //头像背景
    char sttr[100]="";
    quality = PublicShowUI::getColorIndexByQuality(DictItemTypeEnumItemHero,quality);
    sprintf(sttr,IMG_PUBLIC_HEROHEADFRAMEBG,quality);
    Sprite* headBg=Sprite::create(sttr);
    headBg->setPosition(-4,-4);
    headBg->setAnchorPoint(Point::ZERO);
    this->addChild(headBg);
    
    //头像框
    char stt[100]="";
    sprintf(stt,IMG_PUBLIC_HEADTALENTFRAME,quality);
    Sprite* headBox=Sprite::create(stt);
    headBox->setAnchorPoint(Point::ZERO);
    headBox->setPosition(-4.5,-4.5);
    this->addChild(headBox,1,TAG_HEADBOX);
    
    //星星背景
    Sprite* starbg=Sprite::create(IMG_PUBLIC_HEAD_STARBG);
    if(starbg)
    {
        starbg->setAnchorPoint(Point::ZERO);
        starbg->setPosition(0,0);
        this->addChild(starbg,1);
    }
    //头像声望 现在叫星级了
    Node* starNode = Node::create();
    starNode->setAnchorPoint(Point::ZERO);
    this->addChild(starNode,5,TAG_PREST);
    starNode->setCascadeOpacityEnabled(true);
    starNode->setPositionY(-5);
    //头像等级背景
    Sprite* headRankBg=Sprite::create(IMG_PUBLIC_HEROHEAD_LEVEL);
    headRankBg->setAnchorPoint(Point::ZERO);
    headRankBg->setPosition(headBox->getContentSize().width-headRankBg->getContentSize().width-5,headBox->getContentSize().height-headRankBg->getContentSize().height-5);
    headRankBg->setCascadeOpacityEnabled(true);
    this->addChild(headRankBg,1,TAG_LVBG);
}
void UserHeadLayer::onButtonClick(Ref* psender)
{
    if (this->c_touchBegainTarget and this->c_touchBegainSelector) {
        (c_touchBegainTarget->*c_touchBegainSelector)(this);
    }
    
}
void UserHeadLayer::disableTouchEvent()
{
    Button* headImg=(Button*)this->getChildByTag(TAG_HEAD);
    headImg->disableTouchEvent();
    
}
void UserHeadLayer::setHeadInfo(int lvInt,short prestInt)
{
    Sprite* lvBg=(Sprite*)this->getChildByTag(TAG_LVBG);
    if (lvBg) {
        //等级数值
        lvBg->setCascadeOpacityEnabled(true);
        string lvStr=PublicShowUI::numberToString(lvInt);
        
        Label* lvLabel = PublicShowUI::getLabel(lvStr.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),16,false,false);
        lvLabel->setAnchorPoint(Point::ZERO);
        lvLabel->setPosition((lvBg->getContentSize().width-lvLabel->getContentSize().width)/2,(lvBg->getContentSize().height-lvLabel->getContentSize().height)/2);
        lvBg->addChild(lvLabel);
    }
   
    //声望数值
//    string prestStr=PublicShowUI::numberToString(prestInt);
    Sprite* prestBg=(Sprite*)this->getChildByTag(TAG_PREST);
    if (prestBg) {
//        Label* prestLabel = PublicShowUI::getLabel(prestStr.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),16,false,false);
//        prestLabel->setAnchorPoint(Point::ZERO);
//        prestLabel->setPosition((prestBg->getContentSize().width-prestLabel->getContentSize().width)/2+13,0);
//        prestBg->addChild(prestLabel);
        prestBg->removeAllChildren();
        Sprite* star = NULL;
        for(int i = 0; i < prestInt; i++)
        {
            star = Sprite::create(IMG_PUBLIC_STAR);
            star->setAnchorPoint(Point::ZERO);
            star->setScale(.5);
            star->setContentSize(star->getContentSize() * .5);
            prestBg->addChild(star,i,i);
            star->setPositionX(i * (star->getContentSize().width - 6));
        }
        if(star)
        {
            Size size = star->getContentSize();
            size.width = star->getPositionX() + size.width;
            Node* node = this->getChildByTag(TAG_HEADBOX);
            prestBg->setPositionX((node->getContentSize().width - size.width)/2 - 5);
        }
    }
}
void UserHeadLayer::hideHeadInfo()
{
     Sprite* prestBg=(Sprite*)this->getChildByTag(TAG_PREST);
    if(prestBg)
    {
        prestBg->setVisible(false);
    }
    Sprite* lvBg=(Sprite*)this->getChildByTag(TAG_LVBG);
    if(lvBg)
    {
        lvBg->setVisible(false);
    }
}
void UserHeadLayer::setHeadNumber(bool bol)
{
    if (bol) {
        
        Size size = this->getContentSize();
        LayerColor* layer = LayerColor::create(Color4B(0,0,0,170), size.width+2, size.height);
        layer->setPositionX(-4.5);
        layer->setPositionY(-4.5);
        this->addChild(layer,6,TAG_BLACKBG);
        
        Sprite* tick=Sprite::create(IMG_PUBLIC_LAYER_TICK);
        tick->setAnchorPoint(Point::ZERO);
        tick->setPosition(this->getContentSize().width-tick->getContentSize().width-5,5);
        this->addChild(tick,6,TAG_TICK);
    }else
    {
        Sprite* boxNumSp=(Sprite*)this->getChildByTag(TAG_TICK);
        
        if (boxNumSp) {
            this->removeChildByTag(TAG_TICK);
            this->removeChildByTag(TAG_BLACKBG);
        }
    }
}
void UserHeadLayer::setFragment()
{//碎片
    Sprite* fragment=Sprite::create(IMG_PUBLIC_LAYER_FRAGMENT);
    fragment->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(fragment);
    fragment->setPosition(-5, this->getContentSize().height-fragment->getContentSize().height-3);
    this->addChild(fragment,7);
    
    hideHeadInfo();
}
void UserHeadLayer::setRemoveOther()
{
    Sprite* lvBg=(Sprite*)this->getChildByTag(TAG_LVBG);
    if (lvBg) {
        this->removeChildByTag(TAG_LVBG);
    }
    Sprite* prestBg=(Sprite*)this->getChildByTag(TAG_PREST);
    if (prestBg) {
        this->removeChildByTag(TAG_PREST);
    }
}
Rect UserHeadLayer::getRect(Node* spr)
{
    //获取精灵区域大小
    return Rect(spr->getPositionX()- spr->getContentSize().width  * spr->getAnchorPoint().x,spr->getPositionY()-spr->getContentSize().height* spr->getAnchorPoint().y,spr->getContentSize().width, spr->getContentSize().height);
}

void UserHeadLayer::addTouchBegainCallBack(Ref* target,SEL_CallFuncN selector)
{
    this->c_touchBegainTarget = target;
    this->c_touchBegainSelector = selector;
    
}

