//
//  UserEquipLayer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/9/2.
//
//

#include "UserEquipLayer.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "../../common/TouchSprite/Button.h"
#include "../../commonData/enum/DictItemTypeEnum.h"
UserEquipLayer::UserEquipLayer()
:c_touchBegainTarget(NULL)
,c_touchBegainSelector(NULL)
,cardId(2)
,TAG_LVBG(3)
,TAG_PREST(4)
,TAG_HEADBOX(5)
,TAG_NUM(6)
,TAG_BLACKBG(7)
,TAG_TICK(8)
,TAG_EQUIPICON(9)
,sx(1)
,isSelect(false)
{
    
}
UserEquipLayer::~UserEquipLayer()
{
    _eventDispatcher->removeEventListenersForTarget(this);
    c_touchBegainTarget = NULL;
    c_touchBegainSelector = NULL;
}
void UserEquipLayer::onExit()
{
    Layer::onExit();
}
void UserEquipLayer::onEnter()
{
    Layer::onEnter();
}
void UserEquipLayer::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}
void UserEquipLayer::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
}
bool UserEquipLayer::init(const char* imgPath,int quality,  bool _bol,bool _bol2)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        this->createLayer(imgPath,quality,_bol,_bol2);
        bref = true;
    } while (false);
    return bref;
}
UserEquipLayer* UserEquipLayer::create(string imgPath,int quality, bool _bol,bool _bol2)
{
    const char* img=imgPath.c_str();
    UserEquipLayer* layer = new UserEquipLayer();
    if(layer && layer->init(img,quality,_bol,_bol2))
    {
        layer->autorelease();
        return layer;
    }
    else{
        delete layer;
        layer = NULL;
        return NULL;
    }
}

void UserEquipLayer::createLayer(const char* imgPath,int quality,bool _bol,bool _bol2)
{
    
    //装备
    string tempStr="no";
    if (strcmp(imgPath, tempStr.c_str())==0) {
        Button* headImg = Button::create(IMG_PUBLIC_TABLEVIEW_EQUIP,IMG_PUBLIC_TABLEVIEW_EQUIP, CC_CALLBACK_1(UserEquipLayer::onButtonClick, this));
        headImg->setPosition(Point::ZERO);
        this->addChild(headImg);
        this->setContentSize(headImg->getContentSize());
        return;
    }
    //装备背景
    char sttr[100]="";
    
    if (_bol2) {
        quality = PublicShowUI::getColorIndexByQuality(DictItemTypeEnumItem, quality);
    }
    sprintf(sttr,IMG_PUBLIC_HEROHEADFRAMEBG,quality);
    Sprite* headBg=Sprite::create(sttr);
    headBg->setPosition(0,0);
    headBg->setAnchorPoint(Point::ZERO);
    this->addChild(headBg);
    
    //装备框
    char stt[100]="";
    sprintf(stt,IMG_PUBLIC_HEADTALENTFRAME,quality);
    Sprite* headBox=Sprite::create(stt);
    headBox->setAnchorPoint(Point::ZERO);
    this->addChild(headBox,2,TAG_HEADBOX);
    
    const char* path =imgPath;
    if (_bol) {
         path = PublicShowUI::getResImgPath(IMG_PUBLIC_ITEM, imgPath);
    }
    
    Button* headImg = Button::create(path,path, CC_CALLBACK_1(UserEquipLayer::onButtonClick, this));
   
    float _scaleX = (headBg->getContentSize().width - 5) / headImg->getContentSize().height;
    headImg->setScale(_scaleX);
    headImg->setContentSize(headImg->getContentSize()*0.7);
    headImg->setPosition(headBg->getContentSize().width/2,headBg->getContentSize().height/2);
    headImg->getTouchListener()->setSwallowTouches(false);
    this->addChild(headImg,1,TAG_EQUIPICON);
    
    Sprite* headLvBg=Sprite::create(IMG_PUBLIC_HEROHEAD_LEVEL);
    headLvBg->setAnchorPoint(Point::ZERO);
    headLvBg->setPosition(headBox->getContentSize().width-headLvBg->getContentSize().width,headBox->getContentSize().height-headLvBg->getContentSize().height);
    headLvBg->setVisible(false);
    this->addChild(headLvBg,3,TAG_LVBG);
    
    Size _size=headBox->getContentSize();
    this->setContentSize(headBox->getContentSize());
}
void UserEquipLayer::onButtonClick(Ref* psender)
{
    if (this->c_touchBegainTarget and this->c_touchBegainSelector) {
        (c_touchBegainTarget->*c_touchBegainSelector)(this);
    }
}
void UserEquipLayer::setHeadInfo(int lvInt,short prestInt)
{
    Sprite* lvBg=(Sprite*)this->getChildByTag(TAG_LVBG);
    lvBg->setVisible(true);
    //等级数值
    string lvStr=PublicShowUI::numberToString(lvInt);
    
    Label* lvLabel = PublicShowUI::getLabel(lvStr.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),16,false,false);
    lvLabel->setAnchorPoint(Point::ZERO);
    lvLabel->setPosition((lvBg->getContentSize().width-lvLabel->getContentSize().width)/2,(lvBg->getContentSize().height-lvLabel->getContentSize().height)/2);
    lvBg->addChild(lvLabel);
    //声望数值
    if (prestInt==0) {
        return;
    }
    string prestStr=PublicShowUI::numberToString(prestInt);
    Sprite* prestBg=(Sprite*)this->getChildByTag(TAG_PREST);
    Label* prestLabel = PublicShowUI::getLabel(prestStr.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),16,false,false);
    prestLabel->setAnchorPoint(Point::ZERO);
    prestLabel->setPosition((prestBg->getContentSize().width-prestLabel->getContentSize().width)/2+13,-3);
    prestBg->addChild(prestLabel);
}

void UserEquipLayer::setHeadNumber(int num)
{
    Sprite* boxNumSp=(Sprite*)this->getChildByTag(TAG_NUM);
    
    if (num==0) {
        if (boxNumSp) {
            this->removeChildByTag(TAG_NUM);
        }
        return;
    }
    string str=PublicShowUI::numberToString(num);
    Sprite* numSprite=Sprite::create(IMG_GENERALS_EXPERIENCE_CARD_NUMBOX);
    numSprite->setAnchorPoint(Point::ZERO);
    numSprite->setPosition(this->getContentSize().width-numSprite->getContentSize().width+2,-10/sx);
    
    Label* numLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0x000000),20,false,false);
    numLabel->setAnchorPoint(Point(0.5,0.5));
    numLabel->setPosition(numSprite->getContentSize().width/2,numSprite->getContentSize().height/2);
    numSprite->addChild(numLabel,2);
    this->addChild(numSprite,6,TAG_NUM);
}
void UserEquipLayer::setIsSlect(bool bol)
{
    if (bol) {
        
//        Size size = this->getContentSize();
//        LayerColor* layer = LayerColor::create(Color4B(0,0,0,170), size.width+2, size.height);
//        this->addChild(layer,6,TAG_BLACKBG);
        this->setGray();
        
        Sprite* tick=Sprite::create(IMG_PUBLIC_LAYER_TICK);
        tick->setAnchorPoint(Point::ZERO);
        tick->setPosition(this->getContentSize().width-tick->getContentSize().width-5,5);
        this->addChild(tick,7,TAG_TICK);
    }else
    {
        this->removeGray();
        Sprite* boxNumSp=(Sprite*)this->getChildByTag(TAG_TICK);
        if (boxNumSp)
            this->removeChildByTag(TAG_TICK);
        
    }
}
//void UserEquipLayer::setGray()
//{
//    
//}

void UserEquipLayer::setFragment()
{
    Sprite* fragment=Sprite::create(IMG_PUBLIC_LAYER_FRAGMENT);
    fragment->setAnchorPoint(Point::ZERO);
    fragment->setPosition(-4, this->getContentSize().height-fragment->getContentSize().height-2);
    this->addChild(fragment,7);
}
void UserEquipLayer::setLetterFragment()
{
    Sprite* fragment=Sprite::create(IMG_PUBLIC_LAYER_BOOK);
    fragment->setAnchorPoint(Point::ZERO);
    fragment->setPosition(-4, this->getContentSize().height-fragment->getContentSize().height-2);
    this->addChild(fragment,7);
}
void UserEquipLayer::setGray()
{
    Size size = this->getContentSize();
    LayerColor* layer = LayerColor::create(Color4B(0,0,0,170), size.width+2, size.height);
    this->addChild(layer,6,TAG_BLACKBG);
}
void UserEquipLayer::removeGray()
{
    Sprite* blackSp=(Sprite*)this->getChildByTag(TAG_BLACKBG);
    if (blackSp)
        this->removeChildByTag(TAG_BLACKBG);
}
Rect UserEquipLayer::getRect(Node* spr)
{
    //获取精灵区域大小
    return Rect(spr->getPositionX()- spr->getContentSize().width  * spr->getAnchorPoint().x,spr->getPositionY()-spr->getContentSize().height* spr->getAnchorPoint().y,spr->getContentSize().width, spr->getContentSize().height);
}

void UserEquipLayer::addTouchBegainCallBack(Ref* target,SEL_CallFuncN selector)
{
    
    this->c_touchBegainTarget = target;
    this->c_touchBegainSelector = selector;
    
}