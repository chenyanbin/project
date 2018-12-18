//
//  MusouBattle.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/12/10.
//
//

#include "MusouBattle.h"
#include "../../common/ImagePath.h"
#include "../../common/TouchSprite/Button.h"
#include "../tips/TipsLayer.h"
#include "../../common/Dialog/Dialog.h"
#include "../../commonData/enum/DictItemTypeEnum.h"
#include "../../message/Decoding/musou/RequestMusouFightMsg.h"
#include "../../net/NetworkDataProcessing.h"
MusouBattle::MusouBattle()
:m_battleList(NULL)
,m_curSelectedSpr(NULL)
,TAG_LEVELBTN(1)
,TAG_NAME(2)
,TAG_DROPITEMS(3)
,TAG_INSTRUCTION(4)
,TAG_BODYPOWER(5)
,TAG_FIGHT(6)
,nowData(NULL)
{
    
}
MusouBattle::~MusouBattle()
{
    m_battleList = NULL;
    CC_SAFE_RELEASE_NULL(m_curSelectedSpr);
 
}
bool MusouBattle::init(Vector<MusouBattleData*>* battleList)
{
    this->isAnimation = false;
    this->m_battleList = battleList;
    this->setBackground(IMG_MUSOUBATTLE_BG);
    m_curSelectedSpr = Sprite::create(IMG_SWEEP_BUTTOMSAODANGCHOSE);
    PublicShowUI::setTargetScale(m_curSelectedSpr,false,false);
    m_curSelectedSpr->retain();
    setLevelButton();
    setFightBtn();
    return true;
}
MusouBattle* MusouBattle::create(Vector<MusouBattleData*>* battleList)
{
    MusouBattle* battle = new MusouBattle();
    if(battle && battle->init(battleList))
    {
        battle->autorelease();
        return battle;
    }
    CC_SAFE_DELETE(battle);
    return NULL;
}
void MusouBattle::setLevelButton()
{
    Node* btnContainer = Node::create();
    btnContainer->setAnchorPoint(Point::ZERO);
    const char* path = NULL;
    Button* btn = NULL;
    MusouBattleData* data = NULL;
    DictMusouBattle* dictMusouBattle = NULL;
    float sx = GlobalInfo::getInstance()->screenScaleX;
    for(int i = 0; i < 4; i++)
    {
        data = m_battleList->at(i);
        path = PublicShowUI::getResImgPath(IMG_MUSOUBATTLE_LEVEL, PublicShowUI::numberToString(i + 1).c_str());
        btn = Button::create(path, "", CC_CALLBACK_1(MusouBattle::onButtonClick, this));
        PublicShowUI::setTargetScale(btn);

        btn->setPosition((i % 2) * (btn->getContentSize().width + 10 * sx), -(i / 2) * (btn->getContentSize().height + 20 * sx));
        btnContainer->addChild(btn, i, i);
        dictMusouBattle = DictMusouBattleManager::getInstance()->getData(data->battleId);
        if(data->status ==  MusouBattleData::STATUS_ENABLE_FIGHT && GlobalInfo::getInstance()->gameRole->level < dictMusouBattle->playerLevel)
        {
            Sprite* spr = Sprite::create(IMG_MUSOUBATTLE_UNLOCKLEVEL);
            spr->setAnchorPoint(Point::ZERO);
           
            Label* label = PublicShowUI::getLabel(PublicShowUI::numberToString(dictMusouBattle->playerLevel).c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),24,false,false);
            label->setAnchorPoint(Point::ZERO);
            label->setPosition(spr->getContentSize().width, (spr->getContentSize().height - label->getContentSize().height)/2);
            spr->addChild(label,2);
            PublicShowUI::setTargetScale(spr);
            spr->setPosition(btn->getPositionX() - spr->getContentSize().width /2, btn->getPositionY() - spr->getContentSize().height -btn->getContentSize().height/2 );
            btnContainer->addChild(spr,4);
    
        }
        btn->setEnabled(data->status == MusouBattleData::STATUS_ABLE_FIGHT);
    }
    btnContainer->setPosition(btn->getContentSize().width , this->getContentSize().height/2 + 110 * sx);
    data = m_battleList->at(4);
    this->addChild(btnContainer,1,TAG_LEVELBTN);
    path = PublicShowUI::getResImgPath(IMG_MUSOUBATTLE_LEVEL, PublicShowUI::numberToString(5).c_str());
    Button* level5Btn = Button::create(path,"",CC_CALLBACK_1(MusouBattle::onButtonClick, this));
    PublicShowUI::setTargetScale(level5Btn);
    level5Btn->setPosition(level5Btn->getContentSize().width/2, - 220 * sx);
    btnContainer->addChild(level5Btn,4,4);
    level5Btn->setEnabled(data->status == MusouBattleData::STATUS_ABLE_FIGHT);
    if(data->status ==  MusouBattleData::STATUS_ENABLE_FIGHT)
    {
        Sprite* spr = Sprite::create(IMG_MUSOUBATTLE_UNLOCKLEVEL);
        spr->setAnchorPoint(Point::ZERO);
        DictMusouBattle* dictMusouBattle = DictMusouBattleManager::getInstance()->getData(data->battleId);
        Label* label = PublicShowUI::getLabel(PublicShowUI::numberToString(dictMusouBattle->playerLevel).c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),24,false,false);
        label->setAnchorPoint(Point::ZERO);
        label->setPosition(spr->getContentSize().width, (spr->getContentSize().height - label->getContentSize().height)/2);
        spr->addChild(label,2);
        PublicShowUI::setTargetScale(spr);
        spr->setPosition(level5Btn->getPositionX() - spr->getContentSize().width /2, level5Btn->getPositionY() - spr->getContentSize().height - btn->getContentSize().height/2);
        btnContainer->addChild(spr,5);
    }
    
    
    btnContainer->addChild(m_curSelectedSpr,10);
    onButtonClick(btnContainer->getChildByTag(0));//默认选择第一个
}
void MusouBattle::onButtonClick(Ref* pSender)
{
    Button* target = (Button*)pSender;
    if(target)
    {
        m_curSelectedSpr->setPosition(target->getPositionX(),target->getPositionY());
    }
    setNowSelected(target->getTag());
}
void MusouBattle::setNowSelected(int index)
{
    nowData = m_battleList->at(index);
    DictMusouBattle* dictMusouBattle = DictMusouBattleManager::getInstance()->getData(nowData->battleId);
    setName(dictMusouBattle->name.c_str());
    setDropItems(nowData->rewardList);
    setInstruction(dictMusouBattle->desc.c_str());
    setCostPower();
    setFightBtn();
}
void MusouBattle::setName(const char* name)
{
    Label* nameLabel = (Label*)this->getChildByTag(TAG_NAME);
    if(nameLabel)
    {
        nameLabel->setString(name);
    }
    else
    {
        float sx = GlobalInfo::getInstance()->screenScaleX;
        nameLabel = PublicShowUI::getLabel(name,PublicShowUI::getColor3b(COLOR_MILK_WHITE),24,false,true);
        nameLabel->setAnchorPoint(Point::ZERO);
        this->addChild(nameLabel,4,TAG_NAME);
        nameLabel->setPosition(this->getContentSize().width/2 + 120 * sx, this->getContentSize().height - nameLabel->getContentSize().height - 115 * sx);
    }
}
void MusouBattle::setDropItems(Vector<PrizeData*>* rewardList)//设置掉落物
{
    if(this->getChildByTag(TAG_DROPITEMS))
    {
        this->removeChildByTag(TAG_DROPITEMS);
    }
    
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Node* container = Node::create();
    container->setAnchorPoint(Point::ZERO);
    const char* path = NULL;
    TouchSprite* icon = NULL;
    ssize_t len = rewardList->size();
    len = len > 2 ? 2 : len;
    PrizeData* data = NULL;
    
    for (int i =0; i < len ; i++)
    {
        data = rewardList->at(i);
        
        path = PublicShowUI::getGoods(data->itemType, data->itemDictId);
        icon = getItemIcon(path,PublicShowUI::getQuality(data->itemType, data->itemDictId));
        if(icon)
        {
            icon->addTouchBegainCallBack(this, callfuncN_selector(MusouBattle::onDropItemClick));
            icon->setAnchorPoint(Point::ZERO);
            icon->setScale(sx);
            icon->setContentSize(icon->getContentSize() * sx);
            icon->setPositionX(i * (icon->getContentSize().width * sx  + 5 * sx));
            container->addChild(icon,i,i);
           
        }
        
    }
    if(icon)
    {
        Size size = icon->getContentSize();
        size.width = icon->getPositionX() + icon->getContentSize().width ;
        container->setContentSize(size);
       
        container->setPosition(this->getContentSize().width /2 + 125 * sx, this->getContentSize().height/2 - 80 * sx);
        this->addChild(container,10,TAG_DROPITEMS);
    }
}
void MusouBattle::onDropItemClick(Node* node)
{
 
    PrizeData* prizeData = nowData->rewardList->at(node->getTag());
    TipsLayer::show(prizeData->itemType, prizeData->itemDictId, 0);
}
TouchSprite* MusouBattle::getItemIcon(const char* resource,int quality)
{
    if(strcmp(resource, "") == 0)
    {
        return NULL;
    }
    quality = PublicShowUI::getColorIndexByQuality(DictItemTypeEnumItemHero,quality);
    char sttr[100]="";
    sprintf(sttr,IMG_PUBLIC_HEROHEADFRAMEBG,quality);
    
    TouchSprite* headBg = TouchSprite::createWithPic(sttr, NULL, NULL);
    headBg->setAnchorPoint(Point::ZERO);
    
    Sprite* head = Sprite::create(resource);
    if(!head)
    {
        return NULL;
    }
    headBg->addChild(head);
    head->setPosition(headBg->getContentSize().width/2, headBg->getContentSize().height/2);
    
    
    char stt[100]="";
    sprintf(stt,IMG_PUBLIC_HEADTALENTFRAME,quality);
    
    Sprite* headForm = Sprite::create(stt);
    float sx = (headForm->getContentSize().width - 10) / head->getContentSize().width;
    head->setScale(sx);
    headBg->addChild(headForm);
    headForm->setPosition(headBg->getContentSize().width/2, headBg->getContentSize().height/2);
   
 
    return headBg;
}
void MusouBattle::setInstruction(const char* content)
{
    Node* node = this->getChildByTag(TAG_DROPITEMS);
    Label* label = (Label*)this->getChildByTag(TAG_INSTRUCTION);
    
    if(label)
    {
        label->setString(content);
    }
    else
    {
        float sx = GlobalInfo::getInstance()->screenScaleX;
        label = PublicShowUI::getLabel(content,PublicShowUI::getColor3b(COLOR_MILK_WHITE),24,false,true);
        label->setAnchorPoint(Point::ZERO);
        this->addChild(label,5,TAG_INSTRUCTION);
        label->setMaxLineWidth(300 * sx);
        label->setPosition(node->getPositionX(),node->getPositionY() - label->getContentSize().height - 25 * sx);
    }
}
void MusouBattle::setCostPower()
{
    Label* label = (Label*)this->getChildByTag(TAG_BODYPOWER);
    if(label)
    {
        label->setString(PublicShowUI::numberToString(nowData->costPower));
    }
    else
    {
        label = PublicShowUI::getLabel(PublicShowUI::numberToString(nowData->costPower).c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),24,false,true);
        label->setAnchorPoint(Point::ZERO);
        label->setPosition(this->getContentSize().width /2 + 255 * GlobalInfo::getInstance()->screenScaleX, 18 * GlobalInfo::getInstance()->screenScaleX);
        this->addChild(label,11,TAG_BODYPOWER);

    }
    if(GlobalInfo::getInstance()->bodyPower < nowData->costPower)
    {
        label->setColor(Color3B::RED);
    }
}
void MusouBattle::setFightBtn()
{
    Button* jinjiBtn = (Button*)this->getChildByTag(TAG_FIGHT);
    if(!jinjiBtn)
    {
        float sx = GlobalInfo::getInstance()->screenScaleX;
        jinjiBtn = Button::create(IMG_SWEEP_BOTTOMFIGHT, "", CC_CALLBACK_1(MusouBattle::onFightClick, this));
        PublicShowUI::setTargetScale(jinjiBtn);
       
        jinjiBtn->setAnchorPoint(Point::ZERO);
        jinjiBtn->setPosition(this->getContentSize().width - jinjiBtn->getContentSize().width - 20 * sx,5 * sx);
        this->addChild(jinjiBtn,14,TAG_FIGHT);
    }
   
    jinjiBtn->setEnabled(nowData->status == MusouBattleData::STATUS_ABLE_FIGHT);
   
    
}
void MusouBattle::onFightClick(Ref* pSender)
{
    Dialog::showServerLoading();
 
    RequestMusouFightMsg* msg = new RequestMusouFightMsg(nowData->battleId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}