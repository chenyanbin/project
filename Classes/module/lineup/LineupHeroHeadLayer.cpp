//
//  LineupHeroHeadLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/6.
//
//

#include "LineupHeroHeadLayer.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "../userWealth/UserHeadLayer.h"
#include "../../protocol/Protocal.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../common/TouchSprite/Button.h"
#include "lineup_data/LineupPageDataManger.h"
LineupHeroHeadLayer::LineupHeroHeadLayer()
:TAG_WUJIANG(1)
,TAG_YUANFEN(2)
,isHide(true)
,m_lineupNo(1)
,m_index(0)
,TAG_NAME(10)
,TAG_LEVEL(11)
{
}
LineupHeroHeadLayer::~LineupHeroHeadLayer()
{
 
}

bool LineupHeroHeadLayer::init(int nowPage)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->isAnimation = false;
        m_lineupNo = nowPage;
        setBackGround();
        bref = true;
    } while (false);
    return bref;
}

LineupHeroHeadLayer* LineupHeroHeadLayer::create(int nowPage)
{
    LineupHeroHeadLayer* list = new LineupHeroHeadLayer();
    if(list && list->init(nowPage))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void LineupHeroHeadLayer::setBackGround()
{
    Sprite* Bg = Sprite::create(IMG_LINEUP_HEADPICBG);
    Bg->setAnchorPoint(Point::ZERO);
    addChild(Bg, 2, TAG_BG);
    Size size = Bg->getContentSize();
    Bg->setPosition(Point::ZERO);
    this->setContentSize(Bg->getContentSize());
}
void LineupHeroHeadLayer::onEnter()
{
    BaseLayer::onEnter();
}
void LineupHeroHeadLayer::onExit()
{
    BaseLayer::onExit();
}
void LineupHeroHeadLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void LineupHeroHeadLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void LineupHeroHeadLayer::setCheerHero()
{
    if (this->getChildByTag(TAG_NAME)) {
        this->removeChildByTag(TAG_NAME);
    }
    Node* footShadow = Node::create();
    footShadow->setAnchorPoint(Point::ZERO);
    //名字背景
    Sprite* nameBg = Sprite::create(IMG_LINEUP_NAMEBG);
    nameBg->setAnchorPoint(Point::ZERO);
    nameBg->setPositionY(this->getContentSize().height / GlobalInfo::getInstance()->screenScaleX+10);
    footShadow->addChild(nameBg,2);
    
    //英雄名字
    string nameStr= LineupPageDataManger::getInstance()->getpageHero()->at(m_index)->heroName;
    GlobalInfo::getInstance()->gameRole->mainHeroDictID = nameStr.size() > 0 ? LineupPageDataManger::getInstance()->getpageHero()->at(m_index)->heroDictId : GlobalInfo::getInstance()->gameRole->mainHeroDictID;
    Label* nameLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_YELLOW),20,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(10,nameBg->getContentSize().height/2-nameLabel->getContentSize().height/2);
    nameBg->addChild(nameLabel);
    //英雄等级
    int timeStr=LineupPageDataManger::getInstance()->getpageHero()->at(m_index)->level;
    string prestStr=PublicShowUI::numberToString(timeStr);
    Label* timeLabel = PublicShowUI::getLabel(prestStr.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_YELLOW),20,false,false);
    timeLabel->setAnchorPoint(Point(0.5,0));
    timeLabel->setPosition(nameBg->getContentSize().width-25,nameBg->getContentSize().height/2-timeLabel->getContentSize().height/2);
    nameBg->addChild(timeLabel);

    
    //l领导力背景
    Sprite* leaderbg = Sprite::create(IMG_PUBLIC_LAYER_LEAD);
    leaderbg->setAnchorPoint(Point::ZERO);
    leaderbg->setPositionY(this->getContentSize().height/2  / GlobalInfo::getInstance()->screenScaleX+80);
    footShadow->addChild(leaderbg,2);
    
    Sprite* starbg = Sprite::create(IMG_LINEUP_STAR);
    starbg->setAnchorPoint(Point::ZERO);
    starbg->setPosition(leaderbg->getContentSize().width/2+15,-5);
    leaderbg->addChild(starbg,2);
    
    //领导力
    int leader=LineupPageDataManger::getInstance()->getpageHero()->at(m_index)->leadership;
    string leaderStr=PublicShowUI::numberToString(leader);
    Label* leaderLabel = PublicShowUI::getLabel(leaderStr.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_YELLOW),18,false,false);
    leaderLabel->setAnchorPoint(Point(0.5,0));
    leaderLabel->setPosition(leaderbg->getContentSize().width-23,leaderbg->getContentSize().height/2-timeLabel->getContentSize().height/2);
    leaderbg->addChild(leaderLabel,3);

    
    //缘分加成
    string karmaStr="缘分加成";
    Label* karmaLabel = PublicShowUI::getLabel(karmaStr.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_PINK),20,false,false);
    karmaLabel->setAnchorPoint(Point::ZERO);
    karmaLabel->setPosition(10,this->getContentSize().height/2  / GlobalInfo::getInstance()->screenScaleX+50);
    footShadow->addChild(karmaLabel,2);
    
    //缘分一
    int own = LineupPageDataManger::getInstance()->getpageHero()->at(m_index)->own1;
    string liveStr=LineupPageDataManger::getInstance()->getpageHero()->at(m_index)->karmaDesc1;
    Label* liveLabel = NULL;
    if (own == 1)
    {
        liveLabel = PublicShowUI::getLabel(liveStr.c_str(),PublicShowUI::getColor3b(COLOR_SERVERNAME_WHITE),16,false,false);
    }else if (own == 0)
    {
        liveLabel = PublicShowUI::getLabel(liveStr.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_HESE),16,false,false);
    }
    liveLabel->setAnchorPoint(Point::ZERO);
    liveLabel->setPosition(10,this->getContentSize().height/ GlobalInfo::getInstance()->screenScaleX / 2 +10);
    liveLabel->setLineBreakWithoutSpace(true);
    liveLabel->setMaxLineWidth(190);
    footShadow->addChild(liveLabel,2);
    
    //缘分二
    own = LineupPageDataManger::getInstance()->getpageHero()->at(m_index)->own2;
    string liveStr2=LineupPageDataManger::getInstance()->getpageHero()->at(m_index)->karmaDesc2;
    Label* liveLabel2 = NULL;
    if (own == 1)
    {
        liveLabel2 = PublicShowUI::getLabel(liveStr2.c_str(),PublicShowUI::getColor3b(COLOR_SERVERNAME_WHITE),16,false,false);
    }else if (own == 0)
    {
        liveLabel2 = PublicShowUI::getLabel(liveStr2.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_HESE),16,false,false);
    }
    liveLabel2->setAnchorPoint(Point::ZERO);
    liveLabel2->setPosition(10,this->getContentSize().height/ GlobalInfo::getInstance()->screenScaleX / 2-40 );
    liveLabel2->setLineBreakWithoutSpace(true);
    liveLabel2->setMaxLineWidth(190);
    footShadow->addChild(liveLabel2,2);

    
    //技能名字
    string skillnanmeStr=LineupPageDataManger::getInstance()->getpageHero()->at(m_index)->skillName;
  
    Label* skillnanmeLabel = PublicShowUI::getLabel(skillnanmeStr.c_str(),PublicShowUI::getColor3b(COLOR_YELLOW_ORANGEYELLOW),20,false,false);
    skillnanmeLabel->setAnchorPoint(Point::ZERO);
    skillnanmeLabel->setPosition(10,this->getContentSize().height/ GlobalInfo::getInstance()->screenScaleX / 2-70 );
    skillnanmeLabel->setLineBreakWithoutSpace(true);
    skillnanmeLabel->setMaxLineWidth(190);
    footShadow->addChild(skillnanmeLabel,2);
    
    //技能描述
    own = LineupPageDataManger::getInstance()->getpageHero()->at(m_index)->skillOwn;
    string skillStr2=LineupPageDataManger::getInstance()->getpageHero()->at(m_index)->skilldesc;
    Label* skillLabel = NULL;
    if (own == 1)
    {
        skillLabel = PublicShowUI::getLabel(skillStr2.c_str(),PublicShowUI::getColor3b(COLOR_SERVERNAME_WHITE),16,false,false);
    }else if (own == 0)
    {
        skillLabel = PublicShowUI::getLabel(skillStr2.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_HESE),16,false,false);
    }
    skillLabel->setAnchorPoint(Point(0,1));
    skillLabel->setPosition(10,this->getContentSize().height/ GlobalInfo::getInstance()->screenScaleX / 2-70 );
    skillLabel->setLineBreakWithoutSpace(true);
    skillLabel->setMaxLineWidth(190);
    footShadow->addChild(skillLabel,2);
    
    //英雄大图
    DictHero* dictHero = DictHeroManager::getInstance()->getData(LineupPageDataManger::getInstance()->getpageHero()->at(m_index)->heroDictId);
    if(dictHero)
    {
        const char* path  = PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH,dictHero->halfbodyrResource.c_str());
        log("path=%s",path);
        Sprite* heroPic = Sprite::create(path);
        if(heroPic)
        {
            heroPic->setAnchorPoint(Point::ZERO);
            heroPic->setPosition(60,-290);
            MoveBy* move1 = MoveBy::create(2, Point( 0,10));
            MoveBy* move2 = MoveBy::create(2, Point(0,-10));
            Sequence* seq = Sequence::create(move1,move2, NULL);
            RepeatForever* rep = RepeatForever::create(seq);
            heroPic->runAction(rep);
            footShadow->setGlobalZOrder(1);
            footShadow->addChild(heroPic,-1);

        }
    }
    this->addChild(footShadow,10,TAG_NAME);

}
void LineupHeroHeadLayer::onChangePageCallBack(EventCustom* msg)//接受消息，更新HeroPos，接收当前页
{
    __Integer* inter = (__Integer*)msg->getUserData();
    m_index = inter->getValue();
    setCheerHero();
}
void LineupHeroHeadLayer::onlineupNo(EventCustom* msg)
{
    __Integer* inter = (__Integer*)msg->getUserData();
    m_lineupNo = inter->getValue();
}

void LineupHeroHeadLayer::addEventListener()//添加监听
{
    addUserMsg(CUSTOM_CHANGE_TEAMPAGE, CC_CALLBACK_1(LineupHeroHeadLayer::onlineupNo, this));
    addUserMsg(CUSTOM_LINEUP_SAHNGZHENWUJIANG, CC_CALLBACK_1(LineupHeroHeadLayer::onChangePageCallBack, this));
}
void LineupHeroHeadLayer::removeEventListener()//清除监听
{
    BaseLayer::removeEventListener();
}

