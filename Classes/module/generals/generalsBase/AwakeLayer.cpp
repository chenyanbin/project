//
//  AwakeLayer.cpp
//  FightPass
//
//  Created by zhangbin on 16/3/25.
//
//

#include "AwakeLayer.hpp"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../common/customButton/CustomButton.hpp"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../message/Decoding/generals/awake/RequestAwakePageMsg.hpp"
#include "../../../message/Decoding/generals/awake/RequestHeroAwakeMsg.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../../commonData/enum/DictFightPropEnum.h"
#include "../../tips/TipsLayer.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../common/NumberChange.h"
#include "../../../commonData/dictData/DictHeroQuality/DictHeroQualityManager.h"
#include "../../publicLayer/Getpath_Layer.h"
#include "../../../common/commonEffect/CommonEffect.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
AwakeLayer::AwakeLayer()
:m_heroDictID(0)
,m_heroID(0)
,awakeItemList(NULL)
,curQuality(1)
,coin(0)
,TAG_ATTRIB_NODE(1)
,TAG_ITEMS(2)
,TAG_COOPER(3)
,TAG_AWAKEBTN(4)
,TAG_LEFTNAME(5)
,TAG_RIGHTNAME(6)
,TAG_LEFTHERO(7)
,TAG_RIGHTHERO(8)
,isInited(false)
,isUpdateItems(false)
{
    propertyData = new CardPropertyData();
    propertyNewData = new CardPropertyData();
    awakeItemList = new Vector<AwakeItemData*>();
}
AwakeLayer::~AwakeLayer()
{
    CC_SAFE_DELETE(propertyData);
    propertyData = NULL;
    CC_SAFE_DELETE(propertyNewData);
    propertyNewData = NULL;
}
bool AwakeLayer::init(int heroId,int heroDictID)
{
    BaseLayer::init();
    this->isClickClose = true;
    this->setClickEnabled(true);
    this->m_heroDictID = heroDictID;
    this->m_heroID = heroId;
    this->setBackground(IMG_AWAKE_BG,Point::ZERO,false);
    
    return true;
}
AwakeLayer* AwakeLayer::create(int heroId,int heroDictID)
{
    AwakeLayer* layer = new AwakeLayer();
    if(layer && layer->init(heroId,heroDictID))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void AwakeLayer::show(int heroId,int heroDictID)
{
    AwakeLayer* layer = AwakeLayer::create(heroId,heroDictID);
    layer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(layer);
    Scene* scene = Director::getInstance()->getRunningScene();
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer, SCENE_LAYER_ZORDER);
}
void AwakeLayer::setAttribs()//设置属性
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
    Node* resistNode = this->getAttribNode("全抗",0 ,this->propertyNewData->attackStrengh - this->propertyData->attackStrengh);
    node->addChild(resistNode);
   
    
    Node* defenseNode = this->getAttribNode("防御", this->propertyData->defend,this->propertyNewData->defend);
    node->addChild(defenseNode);
    defenseNode->setPositionY(resistNode->getPositionY() + resistNode->getContentSize().height + offY);
    
    Node* attackNode = this->getAttribNode("攻击", this->propertyData->attack,this->propertyNewData->attack);
    node->addChild(attackNode);
    attackNode->setPositionY(defenseNode->getPositionY() + defenseNode->getContentSize().height + offY);
    
    Node* lifeNode = this->getAttribNode("生命", this->propertyData->hp,this->propertyNewData->hp);
    node->addChild(lifeNode);
    lifeNode->setPositionY(attackNode->getPositionY() + attackNode->getContentSize().height + offY);
    
   
    
    this->addChild(node,3,TAG_ATTRIB_NODE);
    
    Size size = lifeNode->getContentSize();
    size.height = lifeNode->getPositionY() + lifeNode->getContentSize().height;
    node->setContentSize(size);
    
    Node* bg = this->getChildByTag(TAG_BG);
    node->setPosition((bg->getContentSize().width - node->getContentSize().width)/2, (bg->getContentSize().height - node->getContentSize().height)/2 + 60);
    
    
}
Node* AwakeLayer::getAttribNode(const char* attribStr,int value,int newValue)
{
    Node* node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    Label* attrib = PublicShowUI::getLabel(attribStr,PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),24,false,false);
    attrib->setAnchorPoint(Point::ZERO);
    node->addChild(attrib,0);
    
    
    string str = value > 0 ? " " + PublicShowUI::numberToString(value) + "+" : " +";
  
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
void AwakeLayer::updateHeroQuanlity()
{
    
    DictHero* dictHero = DictHeroManager::getInstance()->getData(m_heroDictID);
    if(!dictHero)
    {
        return;
    }
    DictHeroQuality* heroQuality = DictHeroQualityManager::getInstance()->getData(curQuality);
    string name = heroQuality ? heroQuality->name : "";
    Label* nameLabel = (Label*)this->getChildByTag(TAG_LEFTNAME);
    Color3B color =  PublicShowUI::getNameColor(DictItemTypeEnumItemHero,curQuality);
    if(nameLabel)
    {
        
         string str = dictHero->name + "\n" + name;
        nameLabel->setString(str);
        nameLabel->setColor(color);
    }

    nameLabel = (Label*)this->getChildByTag(TAG_RIGHTNAME);
    if(nameLabel)
    {
        heroQuality = DictHeroQualityManager::getInstance()->getData(curQuality + 1);
        color =  PublicShowUI::getNameColor(DictItemTypeEnumItemHero,curQuality + 1);
        name = heroQuality ? heroQuality->name : "";
        string str = dictHero->name + "\n" + name;
      
        nameLabel->setString(str);
        nameLabel->setColor(color);
    }
}

Label* AwakeLayer::getNameLabel(string nameStr,int quality)
{
    DictHeroQuality* heroQuality = DictHeroQualityManager::getInstance()->getData(quality);
    Color3B color = PublicShowUI::getNameColor(DictItemTypeEnumItemHero,quality);
    string name = heroQuality ? heroQuality->name : "";
    string str = nameStr + "\n" + name;
    Label* nameLabel = PublicShowUI::getLabel(str.c_str(),color,30,false,false,Size::ZERO,TextHAlignment::CENTER);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setMaxLineWidth(30);
 
    return nameLabel;
}
void AwakeLayer::setLeftHero()
{
    DictHero* dictHero = DictHeroManager::getInstance()->getData(m_heroDictID);
    if(!dictHero)
    {
        return;
    }
    //q名字
  
    Label* nameLabel = (Label*)this->getChildByTag(TAG_LEFTNAME);
    if(nameLabel)
    {
        nameLabel->removeFromParent();
    }
//    float sx = this->isInited ? GlobalInfo::getInstance()->screenScaleX  : 1;
    nameLabel =getNameLabel(dictHero->name ,this->curQuality);
    nameLabel->setPosition(50, 250);
    this->addChild(nameLabel,1,TAG_LEFTNAME);
    
    if(this->getChildByTag(TAG_LEFTHERO))
    {
        this->removeChildByTag(TAG_LEFTHERO);
    }
    //半身像
    Node* node = getHeroImage(curQuality);
    node->setPosition(nameLabel->getPositionX() + nameLabel->getContentSize().width + 10,120);
    this->addChild(node,2,TAG_LEFTHERO);
}
Node* AwakeLayer::getHeroImage(int quality)
{
    int index = PublicShowUI::getColorIndexByQuality(DictItemTypeEnumItemHero,quality);
    const char* path = PublicShowUI::getResImgPath(IMG_AWAKE_CIRCLE, PublicShowUI::numberToString(index).c_str());
    Sprite* node = Sprite::create(path);
    node->setAnchorPoint(Point::ZERO);
     DictHero* dictHero = DictHeroManager::getInstance()->getData(m_heroDictID);
    path = PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH, dictHero->halfbodyrResource.c_str());
    Sprite* image = Sprite::create(path);
    if(image)
    {
        image->setAnchorPoint(Point(0.5,0));
        image->setScale(.7);
        image->setPositionX(node->getContentSize().width/2);
        image->setPositionY(-40);
        node->addChild(image);
    }
    return node;
}
void AwakeLayer::setRightHero()
{
    Node* bg = this->getChildByTag(TAG_BG);
    DictHero* dictHero = DictHeroManager::getInstance()->getData(m_heroDictID);
    if(!dictHero)
    {
        return;
    }
//    float sx = this->isInited ? GlobalInfo::getInstance()->screenScaleX  : 1;
    int quality = curQuality + 1;
    //q名字
    if(this->getChildByTag(TAG_RIGHTNAME))
    {
        this->removeChildByTag(TAG_RIGHTNAME);
    }
    Label* nameLabel =getNameLabel(dictHero->name ,quality);
    nameLabel->setPosition(bg->getContentSize().width  - 90, 250);
    this->addChild(nameLabel,5,TAG_RIGHTNAME);
    
    if(this->getChildByTag(TAG_RIGHTHERO))
    {
        this->removeChildByTag(TAG_RIGHTHERO);
    }
    //半身像
    Node* node = getHeroImage(quality);
    node->setPosition( nameLabel->getPositionX() - node->getContentSize().width - 10,120);
  
    this->addChild(node,6,TAG_RIGHTHERO);
    
    if(this->isInited)
    {
        node->setScale(5);
        ScaleTo* scaleTo = ScaleTo::create(.17, .5);
        ScaleTo* scaleTo2 = ScaleTo::create(.1, 1);
     
        node->runAction(Sequence::create(scaleTo,scaleTo2, NULL));
    }
    
  
}
void AwakeLayer::updateCooperCost()
{
    if(this->getChildByTag(TAG_COOPER))
    {
        this->removeChildByTag(TAG_COOPER);
    }
    Node* node = this->getChildByTag(TAG_AWAKEBTN);
    
    Sprite* icon = Sprite::create(IMG_ICON_PUBLIC_COIN);
    icon->setAnchorPoint(Point::ZERO);
    
    string str = PublicShowUI::numberToString(this->coin);
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
void AwakeLayer::onAwakeBtnClick(Ref* pSender)
{
    requestAwakeMsg();
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumAwakeningButton);
}
void AwakeLayer::setItems()
{
    Node* node = this->getChildByTag(TAG_ITEMS);
    Point cp;
    if(node)
    {
        cp = node->getPosition();
        node->removeFromParent();
    }
    node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    this->addChild(node,10,TAG_ITEMS);
    node->removeAllChildren();
    Node* icon = NULL;
    const char* path = NULL;
    AwakeItemData* data = NULL;
    for(int i = 0; i < awakeItemList->size() ;i++)
    {
        data = awakeItemList->at(i);
        path = PublicShowUI::getGoods(DictItemTypeEnumItem, data->itemId);// //PublicShowUI::getResImgPath(IMG_PUBLIC_ITEM,"baihutoukui");
        icon = this->getItemIcon(path, PublicShowUI::getQuality(DictItemTypeEnumItem, data->itemId),data->nowItemCount, data->itemCount);
        if(icon)
        {
            icon->setPositionX(i * (icon->getContentSize().width + 5));
            icon->setScale(.9);
            node->addChild(icon,i,data->itemId);
        }
     
    }
    if(icon)
    {
        Node* bg = this->getChildByTag(TAG_BG);
        Size size = icon->getContentSize();
        size.width = icon->getPositionX() + icon->getContentSize().width;
        node->setContentSize(size);
        if(cp.x != 0)
        {
            node->setPosition(cp);
        }
        else
        {
            node->setPosition((bg->getContentSize().width - size.width)/2, 10);
        }
        
    }

}
Node* AwakeLayer::getItemIcon(const char* path,int quality,int value,int totalValue)
{
    Node* node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    string str = PublicShowUI::numberToString(value) + "/" + PublicShowUI::numberToString(totalValue);
    Label* label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),18,false,false);
    label->setAnchorPoint(Point::ZERO);
    node->addChild(label);
    
    UserEquipLayer* equipLayer = UserEquipLayer::create(path,quality,false);
    equipLayer->setAnchorPoint(Point::ZERO);
    node->addChild(equipLayer);
    equipLayer->setPosition(0, label->getContentSize().height);
    label->setPositionX((equipLayer->getContentSize().width - label->getContentSize().width)/2);
    equipLayer->addTouchBegainCallBack(this, callfuncN_selector(AwakeLayer::onHeroHeadClick));
    Size size = equipLayer->getContentSize();
    size.height = equipLayer->getPositionY() + equipLayer->getContentSize().height;
    node->setContentSize(size);
    return node;
    
}
void AwakeLayer::onHeroHeadClick(Node* node)
{
    int tag = node->getParent()->getTag();
//    TipsLayer::show(DictItemTypeEnumItem, tag, 1);
     Getpath_Layer::show(SCENE_TAG_GENERALS_STRONG,DictItemTypeEnumItem,tag,1);
}
void AwakeLayer::requestPageMsg()
{
    Dialog::showServerLoading();
    RequestAwakePageMsg* msg = new RequestAwakePageMsg(this->m_heroID);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void AwakeLayer::requestAwakeMsg()
{
    Dialog::showServerLoading();
    RequestHeroAwakeMsg* msg = new RequestHeroAwakeMsg(this->m_heroID);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void AwakeLayer::onExit()
{
    BaseLayer::onExit();
}
void AwakeLayer::onEnter()
{
    BaseLayer::onEnter();
}
void AwakeLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    this->setClickEnabled(false);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumAwakeningButton);
}
void AwakeLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->setClickEnabled(true);
    this->isClickClose = true;
    isUpdateItems = false;
    requestPageMsg();
   
}
void AwakeLayer::onMsgProcess(EventCustom* message)
{
    MessageReceive* msg = (MessageReceive*)message->getUserData();
    if(!msg->state)
    {
        return;
    }
    if(msg->messageID == SCENSE_CLIENT_HERO_HeroWakeUpPage2Resp)
    {
        parsePageMsg(msg->byteStream);
     
        setItems();
        if(isUpdateItems)
        {
            broadMsg(CUSTOM_UPDATE_EQUIP);
            isUpdateItems = false;
            return;
        }
        setAttribs();
        setLeftHero();
       
        if(!isInited)
        {
           this->setRightHero();
            
            Node* node = this->getChildByTag(TAG_RIGHTHERO);
            if(node)
            {
                CustomButton* btn = CustomButton::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(AwakeLayer::onAwakeBtnClick, this));
                btn->addTitle(IMG_GENERALS_AWAKELABEL, IMG_GENERALS_AWAKELABEL);
                this->addChild(btn,3,TAG_AWAKEBTN);
                btn->setPosition(node->getPositionX() + node->getContentSize().width/2 , node->getPositionY() - btn->getContentSize().height);
                 GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumAwakeningButton, btn);
                updateCooperCost();
                NewPlayerGuild::getInstance()->showNowGuide();
            }

        }
        else
        {
           showIconEffect();
        }
        isInited = true;
        isUpdateItems = false;
    }
    else if(msg->messageID == SCENSE_CLIENT_HERO_HeroWakeUp2Resp)
    {
//        -1	系统异常
//        -100	此武将已达到最大品质，无法再觉醒
//        -101	道具不足
//        -102	铜钱不足
        NoticeManager::getInstance()->showNotice("觉醒成功",NoticeManager::COLOR_GREEN);
        this->requestPageMsg();
        
        broadMsg(CUSTOM_UPDATE_HEROBASEPAGEMSG,__Integer::create(DictFunctionEnumHeroQuality));
        broadMsg(CUSTOM_AWAKE_FUN);
        
    }
}
void AwakeLayer::parsePageMsg(ByteStream* byteStream)
{
    this->curQuality = byteStream->getByte();
    this->coin = byteStream->getInt();
    int len = byteStream->getByte();
    AwakeItemData* data = NULL;
    awakeItemList->clear();
    for(int i =0; i < len; i++)
    {
        data = new AwakeItemData();
        data->autorelease();
        data->itemId = byteStream->getInt();
        data->itemCount = byteStream->getShort();
        data->nowItemCount = byteStream->getShort();
        awakeItemList->pushBack(data);
    }
    len = byteStream->getByte();
    for(int i = 0; i < len; i++)
    {
        int type = byteStream->get();
        int value = byteStream->getInt();
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
            case DictFightPropEnumDamageAdd:
                propertyData->attackStrengh = value;
                break;
            default:
                break;
        }
        
    }
    len = byteStream->getByte();
    for(int i = 0; i < len; i++)
    {
        int type = byteStream->get();
        int value = byteStream->getInt();
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
            case DictFightPropEnumDamageAdd:
                propertyNewData->attackStrengh = value;
                break;
            default:
                break;
        }
        
    }

}
void AwakeLayer::onUpdateItems()
{
    isUpdateItems = true;
    this->requestPageMsg();
}
void AwakeLayer::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroWakeUpPage2Resp).c_str(), CC_CALLBACK_1(AwakeLayer::onMsgProcess, this));
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroWakeUp2Resp).c_str(), CC_CALLBACK_1(AwakeLayer::onMsgProcess, this));
    addUserMsg(CUSTOM_UPDATE_USER_ITEMS, CC_CALLBACK_0(AwakeLayer::onUpdateItems, this));
}
void AwakeLayer::removeEventListener()
{
     BaseLayer::removeEventListener();
}
void AwakeLayer::showIconEffect()
{
    Node* node = this->getChildByTag(TAG_ITEMS);
    if(!node)
    {
        return;
    }
    Node* icon = NULL;
   
    ssize_t len = awakeItemList->size();
    for(int i = 0; i < len ;i++)
    {
        icon = node->getChildByTag(awakeItemList->at(i)->itemId);
 
        MoveBy* moveBy1 = MoveBy::create(.5, Point(0,220));
        MoveTo* moveto = MoveTo::create(.5, Point(-180,icon->getPositionY() + 220));
        RemoveSelf* remove = RemoveSelf::create();
        CallFunc* callBack = i == len-1 ? CallFunc::create(CC_CALLBACK_0(AwakeLayer::showAwakeEffect, this)) : NULL;

        icon->runAction(Sequence::create(moveBy1,moveto,remove,callBack, NULL));

    }
    CustomButton* btn = (CustomButton*)this->getChildByTag(TAG_AWAKEBTN);
    btn->setEnabled(false);
}
void AwakeLayer::showAwakeEffect()
{
    Node* leftHero = this->getChildByTag(TAG_LEFTHERO);

    CommonEffect* commonEffect = CommonEffect::create("wujiangjuexingtexiao",false,true);
    commonEffect->setAnchorPoint(Point(.5,.5));
    commonEffect->setPosition(leftHero->getPositionX() + 230,leftHero->getPositionY() + 50);
    
    DelayTime* delay = DelayTime::create(.6);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(AwakeLayer::onEffectCompleted, this));
    commonEffect->runAction(Sequence::create(delay,callBack, NULL));
    this->addChild(commonEffect,12);
}
void AwakeLayer::onEffectCompleted()
{
    setRightHero();
    CustomButton* btn = (CustomButton*)this->getChildByTag(TAG_AWAKEBTN);
    btn->setEnabled(true);
    setItems();
}