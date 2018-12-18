//
//  MusouStageNode.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/13.
//
//

#include "MusouStageNode.h"

#include "../../common/ImagePath.h"
#include "../../common/PublicShowUI.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "../musouBattle/MusouBattleLayer.h"
#include "../../common/TouchSprite/Button.h"
MusouStageNode::MusouStageNode()
:TAG_LEFTTIME(2)
,m_data(NULL)
,m_leftTime(0)
,m_isopen(false)
,TAG_SPRGUAN(101)
,TAG_GUAN(102)
{
    
}
MusouStageNode::~MusouStageNode()
{
    m_data = NULL;

}
bool MusouStageNode::init(MusouStageData* data)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Node::init());
        m_data = data;
        setPage();
        bref = true;
    } while (false);
    return bref;
}
MusouStageNode* MusouStageNode::create(MusouStageData* data)
{
    MusouStageNode* node = new MusouStageNode();
    if(node && node->init(data))
    {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return node;
    
}
void MusouStageNode::setPage()
{
    DictMusou* dictMusou = DictMusouManager::getInstance()->getData(m_data->stageID);
    const char* path = PublicShowUI::getResImgPath(IMG_MUSOU_STAGEBG, dictMusou->resource.c_str());
   
    TouchSprite*  node = NULL;

    if(m_data->status == MusouStageData::STAGE_CLOSE)
    {
        node = (TouchSprite*)GraySprite::create(path);
    }
    else
    {
        node = TouchSprite::createWithPic(path, this, callfuncN_selector(MusouStageNode::onClick));
        node->isButtonMode = true;
        node->setSwallowTouches(false);
    }
     node->setAnchorPoint(Point(0,1));
  
    
    
    Button* btn = Button::create(IMG_MUSOU_SEE, IMG_MUSOU_SEE, CC_CALLBACK_1(MusouStageNode::onBtnClick, this));
    btn->setAnchorPoint(Point::ZERO);
    btn->setPosition(node->getContentSize().width-btn->getContentSize().width-50,130);
    node->addChild(btn,2,0);
    
    string timeStr = m_data->status == MusouStageData::STAGE_OPEN ? "结束时间" : "开启时间";
    Label* timeLabel = PublicShowUI::getLabel(timeStr.c_str(),Color3B::GREEN,20,false,false);
    timeLabel->setAnchorPoint(Point::ZERO);
    timeLabel->setPosition(50,50);
    node->addChild(timeLabel,5);
    
    Label* leftLabel = PublicShowUI::getLabel("00:00:00",Color3B::RED,18,false,false);
    leftLabel->setAnchorPoint(Point::ZERO);
    leftLabel->setPosition(timeLabel->getPositionX() + timeLabel->getContentSize().width+10, timeLabel->getPositionY());
    node->addChild(leftLabel,3,TAG_LEFTTIME);
    
    path = PublicShowUI::getResImgPath(IMG_MUSOU_STAGE_ELEMENT, dictMusou->resource.c_str());
    Sprite* elementAttrib = Sprite::create(path);
    elementAttrib->setAnchorPoint(Point::ZERO);
    elementAttrib->setPosition(elementAttrib->getContentSize().width/2 + 2, node->getContentSize().height - elementAttrib->getContentSize().height - 35);
    node->addChild(elementAttrib,4);
    
    node->setPosition(Point::ZERO);
    this->addChild(node,0,m_data->stageID);
    Size size = node->getContentSize();
    this->setContentSize(size);
   
}
void MusouStageNode::onBtnClick(Ref* pSender)
{
    Node* target = (Node*)pSender;
    int tag = target->getTag();
    if (tag == 0) {
        m_isopen = true;
        
        TouchSprite* node = (TouchSprite*)this->getChildByTag(m_data->stageID);
        ScaleBy* scale = ScaleBy::create( .3,1,0.1);
        CallFunc* callback = CallFunc::create(CC_CALLBACK_0(MusouStageNode::setParticle, this));
        Sequence* seq = Sequence::create(scale,callback, NULL);
        node->runAction(seq);
        
    }else if (tag == 1)
    {
        m_isopen = false;
        TouchSprite* node = (TouchSprite*)this->getChildByTag(TAG_GUAN);
        ScaleBy* scale = ScaleBy::create( .3,1,0.1);
        CallFunc* callback = CallFunc::create(CC_CALLBACK_0(MusouStageNode::setParticle, this));
        Sequence* seq = Sequence::create(scale,callback, NULL);
        node->runAction(seq);
    }
    
}
void MusouStageNode::setParticle()
{
    if (m_isopen) {
        TouchSprite* node = (TouchSprite*)this->getChildByTag(m_data->stageID);
        node->setVisible(false);
    }
    else if (!m_isopen)
    {
        TouchSprite* node = (TouchSprite*)this->getChildByTag(TAG_GUAN);
        node->removeFromParent();
    }
 
    Sprite* spr = Sprite::create(IMG_MUSOU_GUAN);
    spr->setAnchorPoint(Point::ZERO);
    this->addChild(spr,100,TAG_SPRGUAN);
    spr->setPosition(0,-70);
    
    
    DelayTime* time = DelayTime::create(.1);
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(MusouStageNode::setParticle1, this));
    Sequence* seq =Sequence::create(time,callback, NULL);
    spr->runAction(seq);
}
void MusouStageNode::setParticle1()
{
    Sprite* spr = (Sprite*)this->getChildByTag(TAG_SPRGUAN);
    spr->removeFromParent();
    if (m_isopen) {
        TouchSprite* touchspr =TouchSprite::createWithPic(IMG_MUSOU_KAI);
        touchspr->setAnchorPoint(Point(0,1));
        setInstruction(touchspr);
        touchspr->setSwallowTouches(true);
        touchspr->cocos2d::Sprite::setScale(1, 0.1);
        this->addChild(touchspr,100,TAG_GUAN);
        touchspr->setPosition(0,0);
        Button* btn = Button::create(IMG_PUBLIC_BACKBTN, IMG_PUBLIC_BACKBTN,CC_CALLBACK_1(MusouStageNode::onBtnClick, this));
        btn->setAnchorPoint(Point::ZERO);
        btn->setPosition(115,70);
        touchspr->addChild(btn,4,1);
        
        ScaleTo* scale = ScaleTo::create(0.3, 1);
        touchspr->runAction(scale);
        
    }else if(!m_isopen)
    {
        TouchSprite* node = (TouchSprite*)this->getChildByTag(m_data->stageID);
        node->setVisible(true);
        ScaleTo* scale = ScaleTo::create( .3,1,1);
        node->runAction(scale);
    }
    
}
void MusouStageNode::setInstruction(Node* parent)
{
 
     DictMusou* dictMusou = DictMusouManager::getInstance()->getData(m_data->stageID);
    string str = "开启活动时间";
    Label* openTimeLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0xcefff6),20,false,false);
    openTimeLabel->setPosition(parent->getContentSize().width/2, parent->getContentSize().height - openTimeLabel->getContentSize().height - 50);
    parent->addChild(openTimeLabel,1);

    Node* weekLabel1 = getWeekStr(dictMusou);
    parent->addChild(weekLabel1,2);
    weekLabel1->setPosition((parent->getContentSize().width - weekLabel1->getContentSize().width)/2 - 3, openTimeLabel->getPositionY() - 65);

    str = "开放" + dictMusou->name + "副本";
    Label* openBattleLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0xf0ff00),20,false,false);
   
    parent->addChild(openBattleLabel,3);
    openBattleLabel->setPosition(parent->getContentSize().width/2, 140);
    
    
}
Node* MusouStageNode::getWeekStr(DictMusou* musouData)
{
    Color3B color = PublicShowUI::getColor3b(0xcefff6);
    int fontSize = 20;
    Node* node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    string arr[8] = {"每日","周一","周二","周三","周四","周五","周六","周日"};
    int index=  0;
    string str = "";
    string timeArr[4] = {musouData->openTime1,musouData->openTime2,musouData->openTime3,musouData->openTime4};
    string closeTimeArr[4] = {musouData->closeTime1,musouData->closeTime2,musouData->closeTime3,musouData->closeTime4};
    int weekArr[4] = {musouData->weekId1,musouData->weekId2,musouData->weekId3,musouData->weekId4};
    Label* weekLabel = NULL;
    Label* labelTime = NULL;
    for(int i = 0; i < 4 ; i++)
    {
       if(timeArr[i].size() > 0)
       {
           str = arr[weekArr[i]];
           weekLabel = PublicShowUI::getLabel(str.c_str(),color,fontSize,false,false);
           weekLabel->setAnchorPoint(Point::ZERO);
           node->addChild(weekLabel,0);
           weekLabel->setPosition(0, -index * (weekLabel->getContentSize().height  + 5));
           str = timeArr[i] + "-" + closeTimeArr[i];
           labelTime = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0xcefff6),20,false,false);
           labelTime->setAnchorPoint(Point::ZERO);
           node->addChild(labelTime,1);
           labelTime->setPosition(weekLabel->getPositionX() + weekLabel->getContentSize().width + 10, weekLabel->getPositionY());
           
           index++;
       }
    }
    Size size = labelTime->getContentSize();
    size.width = labelTime->getPositionX() + labelTime->getContentSize().width;
    size.height = abs(labelTime->getPositionY()) + labelTime->getContentSize().height;
    node->setContentSize(size);
    
    return node;
    
}
void MusouStageNode::onClick(Node* psender)
{
    TouchSprite* target = (TouchSprite*)psender;
    if(target->getIsMoveSprite())
    {
        return;
    }
    MusouBattleLayer::requestBattleList(m_data->stageID);
}
void MusouStageNode::onEnter()
{
    Node::onEnter();
    Node* node = this->getChildByTag(m_data->stageID);
    if(node)
    {
        node->setScaleY(0.01);
        ScaleTo* scale = ScaleTo::create(.3, 1);
        node->runAction(scale);
    }
    
    
    m_leftTime = m_data->getLeftTime();
    onDelay(0);
    if(m_leftTime > 0)
    {

        this->schedule(schedule_selector(MusouStageNode::onDelay), 1, m_leftTime, 0);
    }
}
void MusouStageNode::onExit()
{
    Node::onExit();
    this->unschedule(schedule_selector(MusouStageNode::onDelay));
}
void MusouStageNode::onDelay(float dt)
{
    m_leftTime --;
    if(m_leftTime < 0)
    {
        this->unschedule(schedule_selector(MusouStageNode::onDelay));
        return;
    }
//    Node* m_node = this->getChildByTag(m_data->stageID);
    Node* node = (Node*)this->getChildByTag(m_data->stageID);
    Label* leftLabel = (Label*)node->getChildByTag(TAG_LEFTTIME);
    leftLabel->setString(PublicShowUI::getTime(m_leftTime * 1000));
  
}