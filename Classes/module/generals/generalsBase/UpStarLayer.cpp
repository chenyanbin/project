//
//  UpStarLayer.cpp
//  FightPass
//
//  Created by zhangbin on 16/3/26.
//
//

#include "UpStarLayer.hpp"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../common/customButton/CustomButton.hpp"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../message/Decoding/generals/heroUpStar/HeroUpStarPageMsg.hpp"
#include "../../../message/Decoding/generals/heroUpStar/HeroUpStarMsg.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../commonData/enum/DictFightPropEnum.h"
#include "../../../message/Decoding/generals/heroUpStar/HeroUpStarMsg.hpp"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../tips/TipsLayer.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../common/NumberChange.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../publicLayer/Getpath_Layer.h"
#include "../../../common/commonEffect/CommonEffect.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
UpStarLayer::UpStarLayer()
:m_heroDictID(0)
,m_heroID(0)
,TAG_STARFORM(1)
,TAG_UPSTARBTN(2)
,TAG_COOPER(3)
,TAG_PROGRESSLABEL(4)
,TAG_ATTRIB_NODE(5)
,promotePt(NULL)
,costCoin(0)
,m_nowStar(0)
,heroBookId(0)
,heroBookCount(0)
,nowHeroBookCount(0)
,propertyData(NULL)
,isInited(false)
{
    propertyData = new CardPropertyData();
    propertyNewData = new CardPropertyData();
}
UpStarLayer::~UpStarLayer()
{
    CC_SAFE_DELETE(propertyData);
    propertyData = NULL;
    CC_SAFE_DELETE(propertyNewData);
    propertyNewData = NULL;
}
bool UpStarLayer::init(int heroID,int heroDictID)
{
    BaseLayer::init();
    this->isClickClose = true;
    this->setClickEnabled(true);
    this->m_heroID = heroID;
    this->m_heroDictID = heroDictID;
    this->setBackground(IMG_UPSTAR_BG,Point::ZERO,false);
    setLeftHero();
    setRightStar();
    return true;
}
UpStarLayer* UpStarLayer::create(int heroID,int heroDictID)
{
    UpStarLayer* layer = new UpStarLayer();
    if(layer && layer->init(heroID,heroDictID))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void UpStarLayer::show(int heroID,int heroDictID)
{
    UpStarLayer* layer = UpStarLayer::create(heroID,heroDictID);
    layer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(layer);
    Scene* scene = Director::getInstance()->getRunningScene();
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer, SCENE_LAYER_ZORDER);
}
void UpStarLayer::setAttribs()//设置属性
{
    Node* node = this->getChildByTag(TAG_ATTRIB_NODE);
 
    if(!node)
    {
        node = Node::create();
        node->setAnchorPoint(Point::ZERO);
    }
    else
    {
        node->removeAllChildren();
    }
    int offY = 12;
    Node* defenseNode = this->getAttribNode("防御", propertyData->defend,propertyNewData->defend);
    node->addChild(defenseNode);
    
    Node* attackNode = this->getAttribNode("攻击", propertyData->attack,propertyNewData->attack);
    node->addChild(attackNode);
    attackNode->setPositionY(defenseNode->getPositionY() + defenseNode->getContentSize().height + offY);
    
    Node* lifeNode = this->getAttribNode("生命", propertyData->hp,propertyNewData->hp);
    node->addChild(lifeNode);
    lifeNode->setPositionY(attackNode->getPositionY() + attackNode->getContentSize().height + offY);
    
    this->addChild(node,3,TAG_ATTRIB_NODE);
    
    Size size = lifeNode->getContentSize();
    size.height = lifeNode->getPositionY() + lifeNode->getContentSize().height;
    node->setContentSize(size);
    
    Node* bg = this->getChildByTag(TAG_BG);
    node->setPosition((bg->getContentSize().width - node->getContentSize().width)/2, (bg->getContentSize().height - node->getContentSize().height)/2 + 40);

    
}
Node* UpStarLayer::getAttribNode(const char* attribStr,int value,int newValue)
{
    Node* node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    Label* attrib = PublicShowUI::getLabel(attribStr,PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),24,false,false);
    attrib->setAnchorPoint(Point::ZERO);
    node->addChild(attrib,0);
 
    string str =   " " + PublicShowUI::numberToString(value) + "+";
    Label* valueLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_ORANGE_YELLOW),24,false,false);
    valueLabel->setAnchorPoint(Point::ZERO);
    node->addChild(valueLabel,1);
    valueLabel->setPosition(attrib->getContentSize().width, attrib->getPositionY());
    
    
    str = PublicShowUI::numberToString(newValue - value);
    Label* newValueLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),24,false,false);
    newValueLabel->setAnchorPoint(Point::ZERO);
    node->addChild(newValueLabel,1);
    newValueLabel->setPosition(valueLabel->getPositionX() + valueLabel->getContentSize().width, valueLabel->getPositionY());
    
    if(isInited)
    {
        newValueLabel->runAction(NumberChange::create(.3,value,newValue));
    }
    

    
    Size size = attrib->getContentSize();
    size.width = newValueLabel->getPositionX() + newValueLabel->getContentSize().width;
    node->setContentSize(size);
   
    return node;
}
Label* UpStarLayer::getNameLabel(string nameStr,int quality)
{
    Color3B color = PublicShowUI::getNameColor(DictItemTypeEnumItemHero,quality);
    string str = nameStr + "\n" + PublicShowUI::numberToString(quality);
    Label* nameLabel = PublicShowUI::getLabel(str.c_str(),color,30,false,false,Size::ZERO,TextHAlignment::CENTER);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setMaxLineWidth(30);
    
    return nameLabel;
}
void UpStarLayer::setLeftHero()
{
    DictHero* dictHero = DictHeroManager::getInstance()->getData(m_heroDictID);
    if(!dictHero)
    {
        return;
    }
    int quality = 1;
    //q名字
    Label* nameLabel =getNameLabel(dictHero->name ,quality);
    nameLabel->setPosition(50, this->getContentSize().height - nameLabel->getContentSize().height - 80);
    this->addChild(nameLabel,2);
    
    //半身像
    Node* node = getHeroImage(quality);
    node->setScale(.62);
    node->setPosition(nameLabel->getPositionX() + nameLabel->getContentSize().width + node->getContentSize().width/2 - 120,this->getContentSize().height/2 );
    this->addChild(node,1);
}
Node* UpStarLayer::getHeroImage(int quality)
{
   
    DictHero* dictHero = DictHeroManager::getInstance()->getData(m_heroDictID);
    const char* path = PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH, dictHero->halfbodyrResource.c_str());
    Sprite* image = Sprite::create(path);

    return image;
}
void UpStarLayer::setRightStar()
{
    Node* node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    
    Sprite* starBg = Sprite::create(IMG_UPSTAR_STARLIGHTBG);
    
    Sprite* starForm = Sprite::create(IMG_UPSTAR_STARFORM);
    starForm->setAnchorPoint(Point::ZERO);
    
    starBg->setPosition(starForm->getContentSize().width / 2, starForm->getContentSize().height/2);
    node->addChild(starBg,0);
    node->addChild(starForm,2);
    node->setContentSize(starForm->getContentSize());
    node->setPosition(this->getContentSize().width - node->getContentSize().width - 30, (this->getContentSize().height - node->getContentSize().height)/2 +  40);
    this->addChild(node,2,TAG_STARFORM);
    
//    
    CustomButton* btn = CustomButton::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(UpStarLayer::onUpStarClick, this));
    btn->addTitle(IMG_GENERALS_UpStarLabel, IMG_GENERALS_UpStarLabel);
    this->addChild(btn,3,TAG_UPSTARBTN);
    btn->setPosition(node->getPositionX() + node->getContentSize().width/2 , node->getPositionY() - 10);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumStarButton, btn);
  
}
void UpStarLayer::updateStar(int starNum)
{
    Node* node = this->getChildByTag(TAG_STARFORM);
    float height = node->getContentSize().height;
    Sprite* star = NULL;
    Point pointList[5] = {{164,height - 24.5f},{296.45f,height - 109.45f},{254.45,height - 269.45f},{74,height - 265.45f},{23.5,height - 109.45f}};
    for(int i = 0; i < starNum; i++)
    {
        if(node->getChildByTag(i))
        {
            continue;
        }
        star = Sprite::create(IMG_PUBLIC_STAR);
        star->setScale(1.6);
        star->setPosition(pointList[i].x + star->getContentSize().width /2 ,pointList[i].y - star->getContentSize().height/2);
        node->addChild(star,10 + i,i);
    }
}
void UpStarLayer::updateCooperCost()
{
    if(this->getChildByTag(TAG_COOPER))
    {
        this->removeChildByTag(TAG_COOPER);
    }
    Node* node = this->getChildByTag(TAG_UPSTARBTN);
    
    Sprite* icon = Sprite::create(IMG_ICON_PUBLIC_COIN);
    icon->setAnchorPoint(Point::ZERO);
    
    string str = PublicShowUI::numberToString(costCoin);
    Label* label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),18,false,false);
    label->setAnchorPoint(Point::ZERO);
    icon->addChild(label);
    label->setPosition(icon->getContentSize().width, (icon->getContentSize().height - label->getContentSize().height)/2);
    this->addChild(icon,2,TAG_COOPER);
    Size size = icon->getContentSize();
    size.width = label->getPositionX() + label->getContentSize().width;
    icon->setContentSize(size);
    icon->setPosition(node->getPositionX() - size.width/2 - 3, node->getPositionY() - size.height - node->getContentSize().height/2);
}
void UpStarLayer::onUpStarClick(Ref* pSender)
{
    Dialog::showServerLoading();
    HeroUpStarMsg* msg = new HeroUpStarMsg(this->m_heroID);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
//    this->removeFromParent();
}
void UpStarLayer::updateCondition()
{
    float percent = heroBookCount ? nowHeroBookCount / heroBookCount : 0;
    percent *= 100;
    if(!this->promotePt)
    {
       
        Node* bg = this->getChildByTag(TAG_BG);
        Sprite* spr = Sprite::create(IMG_GENERALS_CARD_PROGRESSYELLOW);
        spr->setAnchorPoint(Point::ZERO);
       
        this->promotePt = ProgressTimer::create(spr);
        promotePt->setType(ProgressTimer::Type::BAR);
        promotePt->setMidpoint(Point(0,1));
        promotePt->setBarChangeRate(Point(1,0));
        promotePt->setAnchorPoint(Point(0 ,0));
        promotePt->setScale(1.46);
        promotePt->setContentSize(promotePt->getContentSize() * 1.46);
        this->addChild(promotePt,3);
        promotePt->setPercentage(percent);
        promotePt->setPosition((bg->getContentSize().width - promotePt->getContentSize().width)/2 - 42, 62);
        
        
        const char* path = PublicShowUI::getGoods(DictItemTypeEnumItemBook, this->heroBookId);//PublicShowUI::getResImgPath(IMG_PUBLIC_ITEM,"baihutoukui");
        UserEquipLayer* icon = UserEquipLayer::create(path, PublicShowUI::getQuality(DictItemTypeEnumItemBook, this->heroBookId),false);
        icon->setAnchorPoint(Point::ZERO);
        icon->setScale(.8);
        icon->setContentSize(icon->getContentSize() * .8);
        icon->setPosition(promotePt->getPositionX() + promotePt->getContentSize().width , promotePt->getPositionY() + (promotePt->getContentSize().height - icon->getContentSize().height)/2);
        this->addChild(icon,3);
        icon->addTouchBegainCallBack(this, callfuncN_selector(UpStarLayer::onIconClick));

    }
    else
    {
        promotePt->setPercentage(percent);
    }
    string str = PublicShowUI::numberToString(nowHeroBookCount) + "/" + PublicShowUI::numberToString(heroBookCount);
    Label* label = (Label*)this->getChildByTag(TAG_PROGRESSLABEL);
    if(label)
    {
        label->setString(str);
    }
    else
    {
        label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),24,false,false);
        label->setAnchorPoint(Point::ZERO);
        
        this->addChild(label,3,TAG_PROGRESSLABEL);
        label->setPosition(promotePt->getPositionX() + (promotePt->getContentSize().width - label->getContentSize().width)/2,promotePt->getPositionY() - label->getContentSize().height);
    }
}
void UpStarLayer::onIconClick(Node* pSender)
{
//    TipsLayer::show(DictItemTypeEnumItemBook, this->heroBookId, 1);
     Getpath_Layer::show(SCENE_TAG_GENERALS_STRONG,DictItemTypeEnumItemBook,heroBookId,1);
}
void UpStarLayer::onExit()
{
    BaseLayer::onExit();
}
void UpStarLayer::onEnter()
{
    BaseLayer::onEnter();
}
void UpStarLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
     GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumStarButton);
}
void UpStarLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestPageMsg();
  
}
void UpStarLayer::requestPageMsg()
{
    Dialog::showServerLoading();
    HeroUpStarPageMsg* msg = new HeroUpStarPageMsg(this->m_heroID);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void UpStarLayer::onMsgProcess(EventCustom* message)
{
    MessageReceive* msg = (MessageReceive*)message->getUserData();
    if(!msg->state)
    {
        return;
    }
    if(msg->messageID == SCENSE_CLIENT_HERO_HeroStarUpPageResp)
    {
        this->m_nowStar = msg->byteStream->get();
        this->costCoin = msg->byteStream->getInt();
        this->heroBookId = msg->byteStream->getInt();
        this->heroBookCount = msg->byteStream->getShort();
        this->nowHeroBookCount = msg->byteStream->getShort();
        int len = msg->byteStream->getByte();
        for(int i = 0; i < len; i++)
        {
            int type = msg->byteStream->get();
            int value = msg->byteStream->getInt();
            switch (type)
            {
                case DictFightPropEnumHealth:
                    propertyData->hp = value;
                    break;
                case DictFightPropEnumAttack:
                    propertyData->attack = value;
                    break;
                case DictFightPropEnumDefend:
                    propertyData->defend = value;
                    break;
                    
                default:
                    break;
            }
           
        }
        
        len =  msg->byteStream->getByte();
        for(int i = 0; i < len; i++)
        {
            int type = msg->byteStream->get();
            int value = msg->byteStream->getInt();
            switch (type)
            {
                case DictFightPropEnumHealth:
                    propertyNewData->hp = value;
                    break;
                case DictFightPropEnumAttack:
                    propertyNewData->attack = value;
                    break;
                case DictFightPropEnumDefend:
                    propertyNewData->defend = value;
                    break;
                    
                default:
                    break;
            }
            
        }
        updateCooperCost();
        setAttribs();
        updateCondition();
        updateStar(m_nowStar);
        this->isInited = true;
    }
    else if(msg->messageID == SCENSE_CLIENT_HERO_HeroStarUpResp)
    {//升星成功
        NoticeManager::getInstance()->showNotice("升星成功",NoticeManager::COLOR_GREEN);
        requestPageMsg();
        broadMsg(CUSTOM_UPDATE_HEROBASEPAGEMSG,__Integer::create(DictFunctionEnumHeroStar));
        
        onUpStarSuc();
        
        
    }
	

}
void UpStarLayer::onUpStarSuc()
{
     Node* bg = this->getChildByTag(TAG_BG);
    CommonEffect* commonEffec = CommonEffect::create("shengxing",false,true);
    commonEffec->setAnchorPoint(Point(.5,.5));
    bg->addChild(commonEffec,10);
    
      Node* node = this->getChildByTag(TAG_STARFORM);
    commonEffec->setPosition(node->getPositionX() + node->getContentSize().width/2,node->getPositionY() + node->getContentSize().height/2);
}
void UpStarLayer::addEventListener()
{
    this->addUserMsg( PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroStarUpPageResp).c_str(), CC_CALLBACK_1(UpStarLayer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroStarUpResp).c_str(), CC_CALLBACK_1(UpStarLayer::onMsgProcess, this));
   addUserMsg(CUSTOM_UPDATE_USER_ITEMS, CC_CALLBACK_0(UpStarLayer::requestPageMsg, this));
}
void UpStarLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}