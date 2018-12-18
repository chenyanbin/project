//
//  BossNode.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/7.
//
//

#include "BossNode.hpp"
#include "../../../common/ImagePath.h"
#include "../../../common/PublicShowUI.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/customButton/CustomButton.hpp"
#include "../../../commonData/dictData/DictMonster/DictMonsterManager.h"
#include "../../../message/Decoding/famouseGeneral/FamouseFightMsg.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/Dialog/Dialog.h"
#include "../famouseBossCome/FamouseReset.hpp"
BossNode::BossNode()
:m_data(NULL)
,TAG_DELAYTIME(2)
{
    
}
BossNode::~BossNode()
{
    m_data = NULL;
}
BossNode* BossNode::create(FamouseBossData* data)
{
    BossNode* node = new BossNode();
    if(node && node->init(data))
    {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    node = NULL;
    return NULL;
}
bool BossNode::init(FamouseBossData* data)
{
    this->m_data = data;
    Sprite* bg = Sprite::create(IMG_FAMOUSE_HEROITEMBG);
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg,0);
    this->setContentSize(bg->getContentSize());
    setHead();
    setName();
    setDelayTime();
    setBloodPercent();
    setButton();
    return true;
}
void BossNode::setHead()
{
    DictMonster* dictMonster = DictMonsterManager::getInstance()->getData(m_data->bossDictId);
    const char* path = dictMonster ? dictMonster->resource.c_str() : "zhaoyun";
    path = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH,path);
    Sprite* head = Sprite::create(path);
    if(head)
    {
        head->setAnchorPoint(Point::ZERO);
        this->addChild(head,1);
        head->setPosition(37,(this->getContentSize().height - head->getContentSize().height)/2);
    }
   
}
void BossNode::setName()
{
    int fontSize = 22;
    string str = m_data->bossName == "" ? "     " : m_data->bossName;
    Label* nameLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),fontSize,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(190,this->getContentSize().height - nameLabel->getContentSize().height - 14);
    this->addChild(nameLabel,1);
    
    str = "LV " + PublicShowUI::numberToString(m_data->bossLevel);
    Label* levelLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),fontSize,false,false);
    levelLabel->setAnchorPoint(Point::ZERO);
    levelLabel->setPosition(nameLabel->getPositionX() + nameLabel->getContentSize().width + 5, nameLabel->getPositionY());
    this->addChild(levelLabel,1);
    
    //发现者
    Sprite* discoverMan = Sprite::create(IMG_FAMOUSE_DISCOVERMAN);
    discoverMan->setAnchorPoint(Point::ZERO);
    discoverMan->setPosition((this->getContentSize().width - levelLabel->getContentSize().width)/2 + 100, levelLabel->getPositionY());
    this->addChild(discoverMan,1);
    
    str = m_data->bossFinderName;
    Label* discoverLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),fontSize,false,false);
    discoverLabel->setAnchorPoint(Point::ZERO);
    discoverLabel->setPosition(discoverMan->getContentSize().width, 0);
    discoverMan->addChild(discoverLabel,1);
}
void BossNode::setDelayTime()
{
    
    int fontSize = 18;
    Sprite* delayTime = Sprite::create(IMG_FAMOUSE_DELAYTIME);
    delayTime->setAnchorPoint(Point::ZERO);
    Size size = delayTime->getContentSize();
    string str = PublicShowUI::getTime(m_data->bossRemainSeconds * 1000);
    Label*  label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),fontSize,false,false);
    label->setAnchorPoint(Point::ZERO);
    delayTime->addChild(label,1,TAG_DELAYTIME);
    label->setPosition(delayTime->getContentSize().width + 5,(delayTime->getContentSize().height - label->getContentSize().height)/2);
    this->addChild(delayTime,1,TAG_DELAYTIME);
    size.width += label->getContentSize().width;
    delayTime->setContentSize(size);
    delayTime->setPosition(190, (this->getContentSize().height - delayTime->getContentSize().height)/2);
    
    //支援人数
    Sprite* supportSpr = Sprite::create(IMG_FAMOUSE_SUPPORTMAN);
    supportSpr->setAnchorPoint(Point::ZERO);
    str = PublicShowUI::numberToString(m_data->attackRoleCount);
    label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),fontSize,false,false);
    label->setAnchorPoint(Point::ZERO);
    supportSpr->addChild(label);
    label->setPosition(supportSpr->getContentSize().width, (supportSpr->getContentSize().height - label->getContentSize().height)/2);
    this->addChild(supportSpr,1);
    size = supportSpr->getContentSize();
    size.width += label->getContentSize().width;
    supportSpr->setContentSize(size);
    supportSpr->setPosition(delayTime->getPositionX() + delayTime->getContentSize().width + 10, delayTime->getPositionY());
    
    //造成伤害
    str = PublicShowUI::numberToString(m_data->hurt);
    Sprite* damageSpr = Sprite::create(IMG_FAMOUSE_HURTCOUNT);
    damageSpr->setAnchorPoint(Point::ZERO);
    label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),fontSize,false,false);
    label->setAnchorPoint(Point::ZERO);
    damageSpr->addChild(label);
    label->setPosition(damageSpr->getContentSize().width, (damageSpr->getContentSize().height - label->getContentSize().height)/2);
    this->addChild(damageSpr,1);
    size = damageSpr->getContentSize();
    size.width += label->getContentSize().width;
    damageSpr->setContentSize(size);
    damageSpr->setPosition(supportSpr->getPositionX() + supportSpr->getContentSize().width + 10, supportSpr->getPositionY());
    
}
void BossNode::setBloodPercent()
{
    float percent = m_data->hp / m_data->hpMax * 100;
    const char* bloodPath = "";
    if(percent > 50)
    {
        bloodPath = IMG_FAMOUSE_BLOODGREENPRO;
    }
    else if(percent > 20)
    {
        bloodPath = IMG_FAMOUSE_BLOODYELLOWPRO;
    }
    else
    {
        bloodPath = IMG_FAMOUSE_BLOODGREENPRO;
    }
    Sprite* blood = Sprite::create(bloodPath);
    blood->setAnchorPoint(Point::ZERO);
    ProgressTimer* pt=ProgressTimer::create(blood);
    pt->setType(ProgressTimer::Type::BAR);
    pt->setMidpoint(Point(0,1));
    pt->setBarChangeRate(Point(1,0));
    pt->setAnchorPoint(Point::ZERO);
    
    pt->setPercentage(percent);
    
    pt->setPosition(182, 12);
    this->addChild(pt);
    
    string str = PublicShowUI::numberToString((int)m_data->hp) + "/" + PublicShowUI::numberToString((int)m_data->hpMax);
    Label* bloodLabel =  PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),18,false,false);
    this->addChild(bloodLabel,9);
    bloodLabel->setPosition(pt->getPositionX() +  pt->getContentSize().width/2,pt->getPositionY() + pt->getContentSize().height/2);
}
void BossNode::onDelay()
{
    Node* node = this->getChildByTag(TAG_DELAYTIME);
    if(!node)
    {
        return;
    }
    long nowTime = time(0);
    if(m_data->endTime < nowTime)
    {
        return;
    }
    Label* label = (Label*)node->getChildByTag(TAG_DELAYTIME);
    long leftTime = m_data->endTime - nowTime;
    string str = PublicShowUI::getTime(leftTime * 1000);
    label->setString(str.c_str());
    
    DelayTime* delay = DelayTime::create(1);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(BossNode::onDelay, this));
    this->runAction(Sequence::create(delay,callBack, NULL));
    
}
void BossNode::onEnter()
{
    Node::onEnter();
    onDelay();
}
void BossNode::onExit()
{
    Node::onExit();
}
void BossNode::setButton()
{
    CustomButton* btn = CustomButton::create(IMG_PUBLIC_BUTTON_TWO_RED, "", CC_CALLBACK_1(BossNode::onBtnClick, this));
    btn->setAnchorPoint(Point(.5,.5));
    btn->addTitle(IMG_PUBLIC_LABEL_FIGHT, IMG_PUBLIC_LABEL_FIGHT);
    btn->setPosition(this->getContentSize().width - btn->getContentSize().width/2 - 22 , 10 + btn->getContentSize().height/2);
    this->addChild(btn,2);
}
void BossNode::onBtnClick(Ref* pSender)
{
 
    if(GlobalInfo::getInstance()->famouseChallengeCount <= 0)
    {
        FamouseReset::show(GlobalInfo::getInstance()->famouseChallengeCount);
        return;
    }
    
    
    
    GlobalInfo::getInstance()->battleType = kBattleType_MingJiangZhuan;
    GlobalInfo::getInstance()->famouseBossBlood = m_data->hp;
    GlobalInfo::getInstance()->famouseBossLevel = m_data->bossLevel;
    GlobalInfo::getInstance()->famouseBossID = m_data->bossId;
    GlobalInfo::getInstance()->famouseLeftSeconds = m_data->endTime - time(0);
    Dialog::showServerLoading(1);
    FamouseFightMsg* msg = new FamouseFightMsg(m_data->bossId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
    
}