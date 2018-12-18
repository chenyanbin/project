//
//  BossBloodManager.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/7/24.
//
//

#include "BossBloodManager.h"
#include "../../../common/GameConfig.h"
BossBloodManager* BossBloodManager::_instance = NULL;
BossBloodManager::BossBloodManager()
:m_boss(NULL)
,TAG_PROGRESS(1)
,TAG_HEAD(2)
,TAG_NAME(3)
{
    setBlood();
}
BossBloodManager::~BossBloodManager()
{
    m_boss = NULL;
    _instance = NULL;
}
BossBloodManager* BossBloodManager::getInstance()
{
    if(!_instance)
    {
        _instance = new BossBloodManager();
        _instance->autorelease();
    }
    return _instance;
}
void BossBloodManager::updateBoss(Monster* monster)
{
    if(m_boss != monster)
    {
        m_boss = monster;
        setHalfBody();
        setName();
    }
    
    
    updateBlood();
}
void BossBloodManager::setBlood()
{
    Sprite* bloodBg = Sprite::create(IMG_BATTLE_BOSSBLOODBG);
    bloodBg->setAnchorPoint(Point::ZERO);
    Sprite* blood = Sprite::create(IMG_BATTLE_BOSSBLOOD);
    blood->setAnchorPoint(Point::ZERO);
    ProgressTimer* pt=ProgressTimer::create(blood);
    pt->setType(ProgressTimer::Type::BAR);
    pt->setMidpoint(Point(0,1));
    pt->setBarChangeRate(Point(1,0));

    pt->setAnchorPoint(Point::ZERO);
    
    
    Sprite* bloodForm = Sprite::create(IMG_BATTLE_BOSSBLOODFORM);
    bloodForm->setAnchorPoint(Point::ZERO);
    this->addChild(bloodBg,0);
    this->addChild(pt,1,TAG_PROGRESS);
    this->addChild(bloodForm,2);
    this->setContentSize(bloodBg->getContentSize());
}
void BossBloodManager::setHalfBody()
{
//    if(this->getChildByTag(TAG_HEAD))
//    {
//        this->removeChildByTag(TAG_HEAD);
//    }
//    Node* pt = this->getChildByTag(TAG_PROGRESS);
//    const char* path = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH, this->m_boss->getDictMonster()->resource.c_str());
//    Sprite* headBody = Sprite::create(path);
//    if(headBody)
//    {
//        headBody->setAnchorPoint(Point::ZERO);
//        headBody->setPosition(pt->getContentSize().width,-headBody->getContentSize().height/2);
//        this->addChild(headBody,3,TAG_HEAD);
//    }
//    else
//    {
//        log("没有这个头像");
//    }
    
}
void BossBloodManager::setName()
{
    Node* pt = this->getChildByTag(TAG_PROGRESS);
    Label* label = (Label*)this->getChildByTag(TAG_NAME);
    string mosnterName = this->m_boss->getDictMonster()->name;
    if(label)
    {
        label->setString(mosnterName.c_str());
    }
    else
    {
        label = PublicShowUI::getLabel(mosnterName.c_str(),Color3B::WHITE,24,false,false);//COLOR_ORANGE_YELLOW
        label->setAnchorPoint(Point::ZERO);
        label->setPosition(pt->getContentSize().width - label->getContentSize().width - 50, pt->getContentSize().height - 10);
        this->addChild(label,3,TAG_NAME);
    }
}
void BossBloodManager::updateBlood()
{
    Monster* button = dynamic_cast<Monster*>(m_boss);
    if(!button)
    {
        return;
    }
    float percent = m_boss->getAvatarProp()->health / m_boss->_totalHitPoints * 100;
    ProgressTimer* pt = (ProgressTimer*)this->getChildByTag(TAG_PROGRESS);
    if(pt && (percent > 3 || percent <= 0))
    {
        pt->stopAllActions();
        ProgressFromTo* progress = ProgressFromTo::create(.2, pt->getPercentage(), percent);
        pt->runAction(progress);
    }
    if(percent <= 0)
    {
        this->setVisible(false);
    }
}