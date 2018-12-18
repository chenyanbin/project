//
//  LineupLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/6/23.
//
//

#include "LineupLayer.h"
#include "../userWealth/UserWealthLayer.h"
#include "../homeUI/homeMainUI/userHead/UserHead.h"
#include "LineupChoseLayer.h"
#include "LineupCheerLayer.h"
#include "wujiangPos/LineupHeroLayer.h"
#include "LineupFightPower.h"
#include "LineupHeroHeadLayer.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "../../message/Decoding/lineup/lineupFightMsg/LineupFightMsg.h"
#include "../../net/NetworkDataProcessing.h"
#include "../stageLayer/StageLayer.h"
#include "../chapter/ChapterLayer.h"
#include "../newPlayerGuide/NewPlayerGuild.h"
#include "../../commonData/data/FunctionOpenManager.h"
#include "lineup_data/LineupPageDataManger.h"
#include "../../common/NumberChange.h"
LineupLayer::LineupLayer()
:TAG_USERHEAD(1)
,TAG_NAMEBG(2)
,m_totoalLeader(100)
,TAG_KAIZHANBTN(30)
,TAG_DAIMINGBTN(40)
,TAG_KAIZHANWORD(50)
,m_nowPage(1)
,m_combatPower(0)
,TAG_COMBATSPR(51)
,TAG_COMBATNUM(52)
{
    
}
LineupLayer::~LineupLayer()
{

}
bool LineupLayer::init(int nowPage,int _combatPower)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->isAnimation = false;
        
        float sx = GlobalInfo::getInstance()->screenScaleX;
        this->setBackBtn(0,15*sx,true);
        m_nowPage = nowPage;
        m_combatPower = _combatPower;
        setbackGround();
        setUserWealth();
//        setHeroBtn();
        setParticle();
        bref = true;
    } while (false);
    return bref;
}
LineupLayer* LineupLayer::create(int nowPage,int _combatPower)
{
    LineupLayer* layer= new LineupLayer();
    if(layer && layer->init( nowPage,_combatPower))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}

void LineupLayer::show(int fromScene,int nowPage,int _combatPower)
{
   
    if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumLineup))
    {
        FunctionOpenManager::getInstance()->showNoOpenNotice();
        return;
    }
  
    Director::getInstance()->purgeCachedData();
    LineupLayer* layer = LineupLayer::create(nowPage,_combatPower);
    layer->setFromScene(fromScene);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    
    Scene* scene = Scene::create();
    scene->addChild(layer,0,SCENE_TAG_LINEUP);
    
    Director::getInstance()->replaceScene(scene);
    
}
void LineupLayer::setbackGround()
{
    Sprite* bgSpr = Sprite::create(IMG_LINEUP_BG);
    PublicShowUI::setTargetScale(bgSpr,true);
    bgSpr->setAnchorPoint(Point::ZERO);
    bgSpr->setPosition(Point::ZERO);
    this->addChild(bgSpr,-4);
}

void LineupLayer::setUserWealth()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* titlebg = Sprite::create(IMG_PUBLIC_TITLE_BG);
    titlebg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(titlebg);
    titlebg->setPosition(VisibleRect::leftTop().x,VisibleRect::leftTop().y-titlebg->getContentSize().height);
    this->addChild(titlebg,10);
    
    Sprite* littlebg = Sprite::create(IMG_PUBLIC_MODULE_MASK_TOP);
    littlebg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(littlebg);
    littlebg->setPosition(VisibleRect::leftTop().x,VisibleRect::leftTop().y-littlebg->getContentSize().height);
    this->addChild(littlebg,0);
    
    Sprite* title = Sprite::create(IMG_PUBLIC_LINEUP);
    title->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(title);
    title->setPosition(VisibleRect::leftTop().x,VisibleRect::leftTop().y-title->getContentSize().height);
    this->addChild(title,11);
    
}
void LineupLayer::setLineupChoseLayer(int nowPage)//上阵武将层
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    LineupHeroHeadLayer* choseLayer = LineupHeroHeadLayer::create(nowPage);
    choseLayer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(choseLayer);
    choseLayer->setPositionX(VisibleRect::left().x);
    choseLayer->setPositionY(VisibleRect::top().y - choseLayer->getContentSize().height - 120*sx);
    this->addChild(choseLayer, 2);
}
void LineupLayer::setLineupCheerLayer(int nowPage)//助威武将层
{
    LineupCheerLayer* cheerLayer = LineupCheerLayer::create(nowPage);
    cheerLayer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(cheerLayer);
    cheerLayer->setPosition(Point::ZERO);
    this->addChild(cheerLayer, 5);
}
void LineupLayer::setLineupHeroLayer(int nowPage)//阵容层
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    LineupHeroLayer* heroLayer = LineupHeroLayer::create(nowPage);
    heroLayer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(heroLayer,false,false);
    heroLayer->setPositionX( 400 * sx);
    heroLayer->setPositionY(VisibleRect::bottom().y + 120 * GlobalInfo::getInstance()->screenScaleY );
    this->addChild(heroLayer, 0);
}
void LineupLayer::setParticle()//火苗特效
{
    ParticleBatchNode *particlebatch;
    ParticleSystemQuad* particleSystem = ParticleSystemQuad::create(IMG_LINEUP_PARTICLE);
    particlebatch = ParticleBatchNode::createWithTexture(particleSystem->getTexture());
    particlebatch->addChild(particleSystem);
//    this->addChild(particlebatch);
}
void LineupLayer::setLineupzhenrongLayer(int nowPage)//选择阵容层
{
    LineupFightPower* layer = LineupFightPower::create(nowPage);
    layer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(layer);
    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2+100*GlobalInfo::getInstance()->screenScaleX,VisibleRect::center().y+270*GlobalInfo::getInstance()->screenScaleY);
    this->addChild(layer,5);
}
void LineupLayer::onEnter()
{
    BaseLayer::onEnter();
    setLineupzhenrongLayer(m_nowPage);
    setLineupChoseLayer(m_nowPage);
    setLineupCheerLayer(m_nowPage);
}
void LineupLayer::onExit()
{
    BaseLayer::onExit();
}
void LineupLayer::onEnterTransitionDidFinish()
{
    
    BaseLayer::onEnterTransitionDidFinish();
    setLineupHeroLayer(m_nowPage);
}
void LineupLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumPlayButton);
}
//领导力
void LineupLayer::setleadership(int _leadership)
{
    this->removeChildByTag(12);
    this->removeChildByTag(13);
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* leader = Sprite::create(IMG_LINEUP_LINGDAOLIBG);
    leader->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(leader);
    leader->setPosition(270*sx,VisibleRect::rightTop().y-45*sx);
    this->addChild(leader,2,12);
    //总领导力数值
    string lingdaoStr = StringUtils::format("%d/%d",_leadership,m_totoalLeader);
    Label* lingdaoLabel = PublicShowUI::getLabel(lingdaoStr.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),20,false,false);
    lingdaoLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(lingdaoLabel);
    lingdaoLabel->setPosition(367*sx, VisibleRect::rightTop().y-42*sx);
    this->addChild(lingdaoLabel,3,13);
}
//战力
void LineupLayer::combatPower(int _comtabPower)
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    
    
    if (!this->getChildByTag(TAG_COMBATSPR)) {
        Sprite* combat = Sprite::create(IMG_PUBLIC_MILITARY);
        combat->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(combat);
        combat->setPosition(700*sx, VisibleRect::rightTop().y-110*sx);
        this->addChild(combat,2,TAG_COMBATSPR);

    }
        //总战力数值
    this->removeChildByTag(TAG_COMBATNUM);
    string combatStr=PublicShowUI::numberToString(_comtabPower-m_combatPower);
    Label* combatLabel = PublicShowUI::getLabel(combatStr.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),20,false,false);
    combatLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(combatLabel);
    combatLabel->setPosition(775*sx,  VisibleRect::rightTop().y-108*sx);
    this->addChild(combatLabel,3,TAG_COMBATNUM);
    
    //字符跳动特效
    if(m_combatPower <= 0)
    {
        return;
    }
    string addStr = StringUtils::format("战力增加%d",m_combatPower);
    NoticeManager::getInstance()->showNotice(addStr.c_str());
    
//    this->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create(CC_CALLBACK_0(LineupLayer::changParticle, this)), NULL));
    
    DelayTime* _delaytime = DelayTime::create(0.5);
    NumberChange *pChange = NumberChange::create(1, _comtabPower-m_combatPower, _comtabPower);
    Sequence* seq = Sequence::create(_delaytime,pChange, NULL);
    combatLabel->runAction(seq);
}

void LineupLayer::setHeroBtn()//开战
{
    this->removeChildByTag(TAG_DAIMINGBTN);
    if (this->getChildByTag(TAG_KAIZHANBTN)) {
        return;
    }
    Button* heroBtn = Button::create(IMG_LINEUP_HEROBTN, "", CC_CALLBACK_1(LineupLayer::onClick, this));
    heroBtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(heroBtn);
    heroBtn->setPositionX(VisibleRect::center().x+VisibleRect::center().x*3/4-120*GlobalInfo::getInstance()->screenScaleX);
    heroBtn->setPositionY(50*GlobalInfo::getInstance()->screenScaleY);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumPlayButton, heroBtn);
    this->addChild(heroBtn,5,TAG_KAIZHANBTN);
    
    Sprite* btnword = Sprite::create(IMG_LINEUP_HEROBTNWORD);
    btnword->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(btnword);
    btnword->setPosition(VisibleRect::center().x+VisibleRect::center().x*3/4-120*GlobalInfo::getInstance()->screenScaleX,50*GlobalInfo::getInstance()->screenScaleY);
    this->addChild(btnword,6,TAG_KAIZHANWORD);
}
void LineupLayer::setWaitBtn()//待命
{
    this->removeChildByTag(TAG_KAIZHANBTN);
    this->removeChildByTag(TAG_KAIZHANWORD);
    if (this->getChildByTag(TAG_DAIMINGBTN)) {
        return;
    }
    Button* waitBtn = Button::create(IMG_LINEUP_HEROWAIT, IMG_LINEUP_HEROWAIT, CC_CALLBACK_1(LineupLayer::onClick, this));
    waitBtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(waitBtn);
    waitBtn->setPositionX(VisibleRect::center().x+VisibleRect::center().x*3/4-120*GlobalInfo::getInstance()->screenScaleX);
    waitBtn->setPositionY(50*GlobalInfo::getInstance()->screenScaleY);
    this->addChild(waitBtn,5,TAG_DAIMINGBTN);
    
    Sprite* btnword = Sprite::create(IMG_LINEUP_HEROWAITWORD);
    btnword->setAnchorPoint(Point::ZERO);
    btnword->setPosition(Point::ZERO);
    waitBtn->addChild(btnword,6);

}
void LineupLayer::onClick(Ref* psender)
{
    Node* target = (Node*)psender;
    int tag_btn = target->getTag();
    if (tag_btn == TAG_KAIZHANBTN)
    {
        Dialog::hideServerLoading();
        ChapterLayer::requestChapterByID();
    }
    else if (tag_btn == TAG_DAIMINGBTN)
    {
        bool ishavehero = false;
        for (int i = 0; i<LineupPageDataManger::getInstance()->getpageHero()->size(); i++) {
            if(LineupPageDataManger::getInstance()->getpageHero()->at(i)->heroDictId != 0){
                ishavehero = true;
            }
        }
        if(ishavehero)
        {
            requestFightMsg(m_nowPage);
        }else{
           NoticeManager::getInstance()->showNotice("请先上阵武将");
        }
    }
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumPlayButton);
    log("clilk");
}

void  LineupLayer::onlingdaoli(EventCustom* msg)//接收领导力
{
    __Integer* inter = (__Integer*)msg->getUserData();
    int lendership = inter->getValue();
    setleadership(lendership);
}
void  LineupLayer::onzhanli(EventCustom* msg)//接收战力
{
    __Integer* inter = (__Integer*)msg->getUserData();
    int combat = inter->getValue();
    combatPower(combat);
}
void LineupLayer::onRoleLeaderMsg(EventCustom* msg)//接收角色领导力
{
    __Integer* inter = (__Integer*)msg->getUserData();
    m_totoalLeader = inter->getValue();
}
void  LineupLayer::createButtonMsg(EventCustom* msg)//接收当前阵容页
{
    __Integer* inter = (__Integer*)msg->getUserData();
    m_nowPage = inter->getValue();
    m_combatPower = 0;
}
void LineupLayer::onFightOrWiteMsg(EventCustom* msg)//开战还是待战
{
    __Integer* inter = (__Integer*)msg->getUserData();
     int isDefault = inter->getValue();
    if (isDefault == 1) {
        setHeroBtn();
    }else if (isDefault == 0){
        setWaitBtn();
    }
}

//-----------------------------------------------访问服务器-------------------------------------------------------//

void LineupLayer::requestFightMsg(int lineupNo)//开战
{
    LineupFightMsg* msg = new LineupFightMsg(lineupNo);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void LineupLayer::onMsgFight(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_LINEUP_LineupSetDefaultResp)
    {
        if(message->state)//创建成功
        {
//            this->removeChildByTag(TAG_DAIMINGBTN);
            setHeroBtn();
            string numCard = StringUtils::format("已将阵容%d设为出战阵容",m_nowPage);
            NoticeManager::getInstance()->showNotice(numCard.c_str());
        }
        else
        {
            return;
        }
    }
}





void LineupLayer::addEventListener()//添加监听
{
    addUserMsg(CUSTOM_LINEUP_LEADERSHIP, CC_CALLBACK_1(LineupLayer::onlingdaoli, this));//领导力
    addUserMsg(CUSTOM_LINEUP_ZHANLI, CC_CALLBACK_1(LineupLayer::onzhanli, this));//战力
    addUserMsg(CUSTOM_LINEUP_ROLELEADERSHIP, CC_CALLBACK_1(LineupLayer::onRoleLeaderMsg, this));//角色领导力
    addUserMsg(CUSTOM_CHANGE_TEAMPAGE, CC_CALLBACK_1(LineupLayer::createButtonMsg, this));//判断当前阵容页
    addUserMsg(CUSTOM_LINEUP_FIGHTORWITE, CC_CALLBACK_1(LineupLayer::onFightOrWiteMsg, this));//开战/待战
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LINEUP_LineupSetDefaultResp).c_str(), CC_CALLBACK_1(LineupLayer::onMsgFight, this));
}
void LineupLayer::removeEventListener()//清除监听
{
    BaseLayer::removeEventListener();
}
