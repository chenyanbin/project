//
//  SupportNode.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/9.
//
//

#include "SupportNode.hpp"
#include "../../../../common/ImagePath.h"
#include "../../../../common/PublicShowUI.h"
#include "../../../../common/customButton/CustomButton.hpp"
#include "../../../../common/GameConfig.h"
#include "../../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../userWealth/UserHeadLayer.h"
SupportNode::SupportNode()
:m_data(NULL)
{
    
}
SupportNode::~SupportNode()
{
    
}
SupportNode* SupportNode::create(DetailsData* data)
{
    SupportNode* node = new SupportNode();
    if(node && node->init(data))
    {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    node = NULL;
    return NULL;
}
bool SupportNode::init(DetailsData* data)
{
    this->m_data = data;
    Sprite* bg = Sprite::create(IMG_FAMOUSE_DETAILS_ITEMBG);
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg,0);
    this->setContentSize(bg->getContentSize());
    
    setHead();
    setName();
    setItems();
    return true;
}
void SupportNode::setHead()
{
    DictHero* dictHero = DictHeroManager::getInstance()->getData(m_data->iconHeroDictId);
    const char* path = dictHero ? dictHero->resource.c_str() : "caopi";
    UserHeadLayer* head = UserHeadLayer::create(path,5,true);
    head->setHeadInfo(m_data->roleLevel,m_data->prestige);
    head->setAnchorPoint(Point::ZERO);
    head->setScale(.9);
    this->addChild(head,1);
    head->setPosition(30,16);
}
void SupportNode::setName()
{
    //发现者
    string str = m_data->isFinder ? IMG_FAMOUSE_DISCOVERMAN : IMG_FAMOUSE_SUPPORT;
    Sprite* discoverMan = Sprite::create(str.c_str());
    discoverMan->setAnchorPoint(Point::ZERO);
    discoverMan->setPosition(20,this->getContentSize().height - discoverMan->getContentSize().height - 14);
    this->addChild(discoverMan,1);
    str = m_data->roleName;
    Label* label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_YELLOW_WHITE),20,false,false);
    label->setAnchorPoint(Point::ZERO);
    label->setPosition(discoverMan->getContentSize().width, 0);
    discoverMan->addChild(label,1);
    Size size = discoverMan->getContentSize();
    size.width = label->getPositionX() + label->getContentSize().width;
    discoverMan->setContentSize(size);
    
    
    Sprite* challengeCount = Sprite::create(IMG_FAMOUSE_CHALLENGECOUNT);
    challengeCount->setAnchorPoint(Point::ZERO);
    str = PublicShowUI::numberToString(m_data->attackCount);
    label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),22,false,false);
    label->setAnchorPoint(Point::ZERO);
    label->setPosition(challengeCount->getContentSize().width, 0);
    challengeCount->addChild(label,1);
    size = challengeCount->getContentSize();
    size.width = label->getPositionX() + label->getContentSize().width;
    challengeCount->setContentSize(size);
    this->addChild(challengeCount,2);
    challengeCount->setPosition(discoverMan->getPositionX() + discoverMan->getContentSize().width + 80, discoverMan->getPositionY() - 2);
    
    //伤害
    Sprite* hurtCountSpr = Sprite::create(IMG_FAMOUSE_HURTCOUNT);
    hurtCountSpr->setAnchorPoint(Point::ZERO);
    str = PublicShowUI::numberToString(m_data->hurt);
    label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),22,false,false);
    label->setAnchorPoint(Point::ZERO);
    hurtCountSpr->addChild(label);
    label->setPosition(hurtCountSpr->getContentSize().width, 0);
    this->addChild(hurtCountSpr,2);
    hurtCountSpr->setPosition(135, this->getContentSize().height/2);
    
    if(m_data->isTop)
    {
        Sprite* topSpr = Sprite::create(IMG_FAMOUSE_DETAILS_TOP);
        topSpr->setAnchorPoint(Point::ZERO);
        topSpr->setPosition(this->getContentSize().width - topSpr->getContentSize().width - 10, hurtCountSpr->getPositionY());
        this->addChild(topSpr,4);
    }
}
void SupportNode::setItems()
{
    ssize_t len = m_data->itemList->size();
    Node* icon = NULL;
    DetailsItemData* itemData = NULL;
    float _width = 70;
    for(int i = 0; i < len; i++)
    {
        itemData = m_data->itemList->at(i);
        icon = PublicShowUI::getIconByTypeID(itemData->itemType, itemData->itemId, itemData->quality);
        icon->setAnchorPoint(Point::ZERO);
        icon->setPosition(135+ i * _width, 15);
        icon->setScale(.6);
        this->addChild(icon,6);
    }
}
