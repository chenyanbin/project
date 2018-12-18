//
//  StoryTalk.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/8/31.
//
//

#include "StoryTalk.h"
#include "../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../commonData/dictData/DictMonster/DictMonsterManager.h"
#include "../../commonData/dictData/DictNPC/DictNPCManager.h"
#include "../../common/StringUtil.h"
StoryTalk::StoryTalk()
:m_dictStory(NULL)
,leftTalkSpr(NULL)
//,rightTalkSpr(NULL)
,leftHead(NULL)
,rightHead(NULL)
,TAG_TEXT(1)
,TAG_NAME(2)
,leftHeadPath("")
,rightHeadPath("")
,callBack(NULL)
{
    
}
StoryTalk::~StoryTalk()
{
    m_dictStory = NULL;
    leftTalkSpr = NULL;
//    rightTalkSpr = NULL;
    callBack = NULL;
}
bool StoryTalk::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->isShowGrayBg = true;
        leftTalkSpr = Sprite::create(IMG_PUBLIC_STORYBG);
        leftTalkSpr->setAnchorPoint(Point::ZERO);
        this->addChild(leftTalkSpr,5);
        leftTalkSpr->setPosition(Point::ZERO);
        leftTalkSpr->setCascadeColorEnabled(true);
        leftTalkSpr->setCascadeOpacityEnabled(true);

        this->setContentSize(leftTalkSpr->getContentSize());
        bref = true;
    } while (false);
    return bref;
}
void StoryTalk::showContent(DictStory* story)
{
    this->m_dictStory = story;
      showTalkContent();
    const char* path = this->getHeadPath();
    if(story->speakerPosition == 1)
    {//左边
        if(path)
        {
            showLeftHead(path);
        }
    }
    else
    {
        if(path)
        {
            showRightHead(path);
        }
        
    }
    showTalkerName();
}
void StoryTalk::showTalkerName()
{
    
    Sprite* nameSpr = (Sprite*)leftTalkSpr->getChildByTag(TAG_NAME);
    Label* label = NULL;
    if(!nameSpr)
    {
        nameSpr = Sprite::create(IMG_PUBLIC_STORYSPEAKERNAME);
        nameSpr->setAnchorPoint(Point::ZERO);
        label = PublicShowUI::getLabel("",PublicShowUI::getColor3b(COLOR_YELLOW_WHITE),22,false,false);
        label->setPositionY(nameSpr->getContentSize().height/2);
        nameSpr->addChild(label,1,TAG_NAME);
        nameSpr->setPositionY(leftTalkSpr->getContentSize().height - nameSpr->getContentSize().height/2);
        leftTalkSpr->addChild(nameSpr,2,TAG_NAME);
    }
    else
    {
        label = (Label*)nameSpr->getChildByTag(TAG_NAME);
    }
    
    label->setString(m_dictStory->speakerName);
    label->setPositionX(nameSpr->getContentSize().width/2);
    float xx = m_dictStory->speakerPosition == 1 ? 15 : leftTalkSpr->getContentSize().width - nameSpr->getContentSize().width - 15;
    nameSpr->setPositionX(xx);
}
void StoryTalk::showTalkContent()
{

    Label* label = (Label*)leftTalkSpr->getChildByTag(TAG_TEXT);
    if(!label)
    {
        label = PublicShowUI::getLabel("",PublicShowUI::getColor3b(COLOR_YELLOW_WHITE),24,false,false);
        label->setAnchorPoint(Point::ZERO);
        label->setMaxLineWidth(leftTalkSpr->getContentSize().width * .8);
        leftTalkSpr->addChild(label,1,TAG_TEXT);
    }
    label->setString(StringUtil::replace(m_dictStory->text, "&userName&", GlobalInfo::getInstance()->gameRole->name));
    label->setPositionX((leftTalkSpr->getContentSize().width - label->getContentSize().width)/2);
    label->setPositionY(60);

}
void StoryTalk::showLeftHead(const char* path)
{
    
    float delay = .2f;
    float _scale = .8;
    if(this->rightHead)
    {
        float toScale = .6;
        ScaleTo* scale1 = ScaleTo::create(delay,-toScale,toScale);
        this->rightHead->runAction(scale1);
        rightHead->setLocalZOrder(-5);
        
    }
    if(leftHeadPath != path)
    {
        if(leftHead)
        {
            leftHead->removeFromParent();
            leftHead = NULL;
        }
    }
    if(!this->leftHead)
    {
        this->leftHead = Sprite::create(path);
        if(leftHead)
        {
            this->leftHead->setAnchorPoint(Point::ZERO);
            this->leftHead->setScale(_scale);
            this->leftHead->setPosition(0, this->getContentSize().height - 130);
            this->addChild(this->leftHead,0);
        }
        leftHeadPath = path;
    }
    else
    {
        ScaleTo* scale2 = ScaleTo::create(delay, _scale);
        this->leftHead->runAction(scale2);
    }
    if(leftHead)
    {
        leftHead->setLocalZOrder(0);
    }
  
}
void StoryTalk::showRightHead(const char* path)
{
    float delay = .2f;
    float _scale = .8;
    
    if(this->leftHead)
    {
       
        ScaleTo* scale1 = ScaleTo::create(delay, .6);
        this->leftHead->runAction(scale1);
        leftHead->setLocalZOrder(-5);
   
    }
   
    if(rightHeadPath != path)
    {
        if(this->rightHead)
        {
            this->rightHead->removeFromParent();
            this->rightHead = NULL;
        }
    }
    if(!this->rightHead)
    {
        this->rightHead = Sprite::create(path);
        if(rightHead)
        {
            this->rightHead->setAnchorPoint(Point::ZERO);
            this->rightHead->setScale(-_scale,_scale);
            this->rightHead->setPosition(this->getContentSize().width,this->getContentSize().height - 130);
            this->addChild(this->rightHead,0);
            rightHeadPath = path;
        }

    }
    else
    {
        ScaleTo* scale2 = ScaleTo::create(delay, -_scale,_scale);
        this->rightHead->runAction(scale2);
    }
    if(rightHead)
    {
        rightHead->setLocalZOrder(0);
    }
   
}
const char* StoryTalk::getHeadPath()
{
    const char* path = NULL;
    //1英雄；2怪物；3NPC
    switch (m_dictStory->speakerType) {
        case 1:
        {
            DictHero* hero = DictHeroManager::getInstance()->getData(m_dictStory->speakerId);
            path = hero ? PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH, hero->halfbodyrResource.c_str()) : NULL;
        }
        break;
        case 2:
        {
            DictMonster* monster = DictMonsterManager::getInstance()->getData(m_dictStory->speakerId);
            path = monster ? PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH, monster->halfbodyrResource.c_str()) : NULL;
        }
        break;
        case 3:
        {
            DictNPC* npc = DictNPCManager::getInstance()->getData(m_dictStory->speakerId);
            path = npc ? PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH, npc->resource.c_str()) :NULL;
        }
        break;
        default:
            break;
    }
    return path;
}
void StoryTalk::onEnter()
{
    BaseLayer::onEnter();
    this->setClickEnabled(true);
    Director::getInstance()->pause();
}
void StoryTalk::onExit()
{
    BaseLayer::onExit();
    this->setClickEnabled(false);
    Director::getInstance()->resume();
}
bool StoryTalk::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}
void StoryTalk::onTouchMoved(Touch *touch, Event *unused_event)
{
    
}
void StoryTalk::onTouchEnded(Touch *touch, Event *unused_event)
{
    if(callBack)
    {
        callBack(this);
    }
}