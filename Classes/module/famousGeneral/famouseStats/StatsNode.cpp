//
//  StatsNode.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/8.
//
//

#include "StatsNode.hpp"
#include "../../../common/ImagePath.h"
#include "../../../common/PublicShowUI.h"
#include "../../../commonData/dictData/DictMonster/DictMonsterManager.h"
#include "../../../common/customButton/CustomButton.hpp"
#include "../../../common/GameConfig.h"
#include "../../../common/TimeUtil.h"
StatsNode::StatsNode()
:m_data(NULL)
{
    
}
StatsNode::~StatsNode()
{
    m_data = NULL;
}
StatsNode* StatsNode::create(FamouseStatsData* data)
{
    StatsNode* node = new StatsNode();
    if(node && node->init(data))
    {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    node = NULL;
    return NULL;
}
bool StatsNode::init(FamouseStatsData* data)
{
    this->m_data = data;
    Sprite* bg = Sprite::create(IMG_FAMOUSE_HEROITEMBG);
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg,0);
    this->setContentSize(bg->getContentSize());
    
    setHead();
    setName();

    setActiveTime();
    return true;
}
void StatsNode::setHead()
{
    DictMonster* dictMonster = DictMonsterManager::getInstance()->getData(m_data->bossDictId);
    const char* path = dictMonster ? dictMonster->resource.c_str() : "zhaoyun";
    path = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH,path);
    Sprite* head = Sprite::create(path);
    head->setAnchorPoint(Point::ZERO);
    this->addChild(head,1);
    head->setPosition(37,(this->getContentSize().height - head->getContentSize().height)/2);
}
void StatsNode::setName()
{
    int fontSize = 22;
    string str =  m_data->activityName;
    Label* nameLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),fontSize,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(198,this->getContentSize().height - nameLabel->getContentSize().height - 14);
    this->addChild(nameLabel,1);
    //击败人数
    Sprite* attackLose = Sprite::create(IMG_FAMOUSE_ATTACKLOSE);
    attackLose->setAnchorPoint(Point::ZERO);
    str =  PublicShowUI::numberToString(m_data->killBossCount);
    Label* label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),fontSize,false,false);
    label->setAnchorPoint(Point::ZERO);
    attackLose->addChild(label);
    label->setPosition(attackLose->getContentSize().width, (attackLose->getContentSize().height - label->getContentSize().height)/2);
    Sprite* weiSpr = Sprite::create(IMG_FAMOUSE_WEI);
    weiSpr->setAnchorPoint(Point::ZERO);
    attackLose->addChild(weiSpr,3);
    weiSpr->setPosition(label->getPositionX() + label->getContentSize().width, 0);
    
    this->addChild(attackLose,1);
    Size size = attackLose->getContentSize();
    size.width =weiSpr->getPositionX() + weiSpr->getContentSize().width;
    attackLose->setContentSize(size);
    attackLose->setPosition(nameLabel->getPositionX() - 20,nameLabel->getPositionY() - 45);
    
    //boss等级
    Sprite* bossLevel = Sprite::create(IMG_FAMOUSE_BOSSLEVEL);
    str = PublicShowUI::numberToString(m_data->maxBossLevel);
    bossLevel->setAnchorPoint(Point::ZERO);
    label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),fontSize,false,false);
    label->setAnchorPoint(Point::ZERO);
    bossLevel->addChild(label);
    label->setPosition(bossLevel->getContentSize().width, (bossLevel->getContentSize().height - label->getContentSize().height)/2);
    this->addChild(bossLevel,1);
    size = bossLevel->getContentSize();
    size.width += label->getContentSize().width;
    bossLevel->setContentSize(size);
    bossLevel->setPosition(this->getContentSize().width/2 + 20, attackLose->getPositionY());

}

void StatsNode::setActiveTime()
{
    
    string m_activeStartTime = TimeUtil::timetodate(m_data->activityStartTimes / 1000);
    m_activeStartTime = m_activeStartTime.substr(0,m_activeStartTime.size() - 3);
   
    string m_activeEndTime = TimeUtil::timetodate(m_data->activityEndTimes / 1000);
    m_activeEndTime = m_activeEndTime.substr(0,m_activeEndTime.size() - 3);
    
    string str = "活动时间：" + m_activeStartTime + " / " + m_activeEndTime;
    
    Label* label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_BLUE_FLOUR),18,false,false);
    label->setAnchorPoint(Point::ZERO);
    label->setPosition(190, 12);
    this->addChild(label,3);
}
