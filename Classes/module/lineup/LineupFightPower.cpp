//
//  LineupFightPower.cpp
//  FightPass
//
//  Created by chenyanbin on 15/6/26.
//
//

#include "LineupFightPower.h"
#include "../../common/TouchSprite/Button.h"


#include "../../protocol/UserCustomEvent.h"
#include "../../protocol/Protocal.h"
#include "../../message/Decoding/lineup/lineupCountMsg/LineupCountMsg.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../message/Decoding/lineup/LineupCreateMsg/LineupCreateMsg.h"
#include "../../message/Decoding/lineup/lineupPage/LineupPageMsg.h"
#include "CreateNewLineupLayer.h"
#include "../../common/Dialog/Dialog.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "LineupLayer.h"
LineupFightPower::LineupFightPower()
:m_nowPage(1)
,m_AllPage(3)
,TAG_PAGE(1)
,m_isLevel(false)
,m_totalPage(10)
,m_nextConsume(1)
,isRight(true)
,m_allGold(1)
{
    lineupCount = new Vector<LineupCountData*>() ;
}
LineupFightPower::~LineupFightPower()
{
    log("~StageLayer ~StageLayer");
    lineupCount->clear();
    CC_SAFE_DELETE(lineupCount);
}

bool LineupFightPower::init(int nowPage)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->isAnimation = false;
        m_nowPage = nowPage;
        requestListMsg();
        setBackGround();
        
        bref = true;
    } while (false);
    return bref;
}

LineupFightPower* LineupFightPower::create(int nowPage)
{
    LineupFightPower* layer = new LineupFightPower();
    if(layer && layer->init(nowPage))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}
void LineupFightPower::setBackGround()
{
    Sprite* laberBg = Sprite::create(IMG_LINEUP_FIGHTBG);
    laberBg->setAnchorPoint(Point::ZERO);
    laberBg->setOpacity(160);
    laberBg->setPosition(Point::ZERO);
    this->addChild(laberBg);
    
    Sprite* fightPower = Sprite::create(IMG_LINEUP_ZHENRONGWORD);
    fightPower->setAnchorPoint(Point::ZERO);
    fightPower->setPosition(60, 8);
    laberBg->addChild(fightPower,1);
    this->setContentSize(laberBg->getContentSize());    
}
void LineupFightPower::setPage()
{
    log("%d",m_nowPage);
    string numCard = StringUtils::format("%d",m_nowPage);
    Label* numLabel = PublicShowUI::getLabel(numCard.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_WHITE),30,false,false);
    numLabel->setAnchorPoint(Point::ZERO);
    numLabel->setPosition(150, 2);
    this->addChild(numLabel,3,TAG_PAGE);
    if (m_isLevel) {
        this->removeChildByTag(TAG_PAGE);
        broadMsg(CUSTOM_CHANGE_TEAMPAGE,__Integer::create(m_nowPage));//发布消息现在是第几个阵容
    }
    m_isLevel = true;
}
void LineupFightPower::setPageNum()
{
//    log("%d",m_nowPage);
//    string numCard = StringUtils::format("%d",m_nowPage);
//    Label* numLabel = PublicShowUI::getLabel(numCard.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_WHITE),30,false,false);
//    numLabel->setAnchorPoint(Point::ZERO);
//    numLabel->setPosition(150, 2);
//    this->addChild(numLabel,3,TAG_PAGE);
//    if (m_isLevel) {
//        this->removeChildByTag(TAG_PAGE);
//        broadMsg(CUSTOM_CHANGE_TEAMPAGE,__Integer::create(m_nowPage));
//    }
//    m_isLevel = true;
}

void LineupFightPower::setButton()
{
    TouchSprite* leftBtn = TouchSprite::createWithPic(IMG_STAGE_RIGHTBTN, this, callfuncN_selector(LineupFightPower::onBtnclick));
    leftBtn->setAnchorPoint(Point(0.5,0.5));
    leftBtn->setRotation(180);
    leftBtn->setPosition(-50,22);
    this->addChild(leftBtn,1,10);
    
}
void LineupFightPower::setRightBtn()
{
    if (isRight) {
        if (m_nowPage == m_AllPage) {
            setzengjiaBtn();
            return;
        }
    }
    TouchSprite* rightBtn =  TouchSprite::createWithPic(IMG_STAGE_RIGHTBTN, this, callfuncN_selector(LineupFightPower::onBtnclick));
    rightBtn->setAnchorPoint(Point::ZERO);
    rightBtn->setPosition(280,-12);
    this->addChild(rightBtn,1,11);
}
void LineupFightPower::setzengjiaBtn()
{
    TouchSprite* zengjiaBtn = TouchSprite::createWithPic(IMG_LINEUP_ZENGJIA, this,callfuncN_selector(LineupFightPower::onBtnclick));
    zengjiaBtn->setAnchorPoint(Point::ZERO);
    zengjiaBtn->setSwallowTouches(true);
    zengjiaBtn->setPosition(280,-5);
    
    this->addChild(zengjiaBtn,1,12);
}
void LineupFightPower::onBtnclick(Node* psender)
{
    int tag = psender->getTag();
    switch (tag) {
        case 10:
            if (m_nowPage ==1) {
                return;
            }
            if (m_nowPage == m_AllPage) {
                isRight = false;
                this->removeChildByTag(12);
                 setRightBtn();
            }
            m_nowPage--;
            setPage();
            break;
        case 11:
            if (m_nowPage == m_totalPage) {
                return;
            }
            if (m_nowPage == m_AllPage-1) {
                this->removeChildByTag(11);
                setzengjiaBtn();
            }
            m_nowPage++;
            setPage();
            break;
        case 12:
            if(m_nextConsume<=0)
            {
                Dialog::show("阵容不可再创建");
                return;
            }
            CreateNewLineupLayer::show(m_nextConsume,m_AllPage);//创建新阵容
            break;
        default:
            break;
    }
}
void LineupFightPower::onEnter()
{
    BaseLayer::onEnter();
}
void LineupFightPower::onExit()
{
    BaseLayer::onExit();
}
void LineupFightPower::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    
}
void LineupFightPower::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}

void LineupFightPower::onMsgupdataLineup(EventCustom* msg)//接收阵容跟新消息
{
    __Integer* inter = (__Integer*)msg->getUserData();
    m_nextConsume = inter->getValue();
    m_nowPage++;
    m_AllPage = m_AllPage+1;
    setPage();
    string linupCount = StringUtils::format("已开启阵容%d",m_nowPage);
    NoticeManager::getInstance()->showNotice(linupCount.c_str());
    
}
//-----------------------------------------------访问服务器-------------------------------------------------------//


void LineupFightPower::requestListMsg()//获取阵容数量信息
{
    LineupCountMsg* msg = new LineupCountMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void LineupFightPower::onMsgProcess(EventCustom* msg)//获取阵容数量信息返回值
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();

    if(message->messageID == SCENSE_CLIENT_LINEUP_LineupListResp)
    {
        if(message->state)//返回成功
        {
            m_totalPage = message->byteStream->getByte();//总阵容数
            m_AllPage = message->byteStream->getByte();//现在阵容数
            m_nextConsume = message->byteStream->getInt();//购买下一个阵容所需要的钱数
            if (m_AllPage >= 1) {
                requestPageMsg(m_nowPage);
                setButton();
                setRightBtn();
                setPage();
            }else{
                CreateNewLineupLayer::show(m_nextConsume,m_AllPage);
            }
        }
        else
        {
            return;
        }
        
    }
}

void LineupFightPower::requestPageMsg(int team)//获取上阵武将信息
{
    Dialog::showServerLoading(.5);
    LineupPageMsg* msg = new LineupPageMsg(team);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void LineupFightPower::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LINEUP_LineupListResp).c_str(), CC_CALLBACK_1(LineupFightPower::onMsgProcess, this));//切换阵容
    this->addUserMsg(CUSTOM_LINEUP_FIRSTCREATELINEUP, CC_CALLBACK_1(LineupFightPower::onMsgupdataLineup, this));//跟新阵容
}
void LineupFightPower::removeEventListener()
{
    BaseLayer::removeEventListener();
}


