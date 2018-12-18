//
//  FindExtendLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/1.
//
//

#include "FindExtendLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/market/findExtendMsg/MarketFindExtendMsg.h"
#include "../../../message/Decoding/market/marketFindMsg/MarketFindPageMsg.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../common/noticeManager/NoticeManager.h"
FindExtendLayer::FindExtendLayer()
:m_nextExtentGold(0)
{
    
}

FindExtendLayer::~FindExtendLayer()
{
}


bool FindExtendLayer::init(int nextExtentGold)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        m_nextExtentGold= nextExtentGold;
        this->setBackground(IMG_DIALOG_BG,Point::ZERO,true);
        this->isAnimation = false;
        this->setClickEnabled(true);
        this->isClickClose = true;//点击外面自动关闭
        this->isShowGrayBg = true;
        setUiSpr();
        setSureBuyBtn();
        bref = true;
    } while (false);
    return bref;
}

FindExtendLayer* FindExtendLayer::create(int nextExtentGold)
{
    FindExtendLayer* list = new FindExtendLayer();
    if(list && list->init(nextExtentGold))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void FindExtendLayer::show(int nextExtentGold)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    FindExtendLayer* layer = FindExtendLayer::create(nextExtentGold);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}

void FindExtendLayer::onEnter()
{
    BaseLayer::onEnter();
}
void FindExtendLayer::onExit()
{
    BaseLayer::onExit();
}
void FindExtendLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    
}
void FindExtendLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumOkButton);
}

void FindExtendLayer::setUiSpr()
{

    float sx = GlobalInfo::getInstance()->screenScaleX;
    if (m_nextExtentGold<=0) {
        string xiaohaoStr = "确认扩展 ？";
        Label* leadLabel = PublicShowUI::getLabel(xiaohaoStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT),24,false,false);
        leadLabel->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(leadLabel);
        leadLabel->setPosition(this->getContentSize().width/2-leadLabel->getContentSize().width/2,this->getContentSize().height/2+leadLabel->getContentSize().height/2+6*sx);
        this->addChild(leadLabel,1);
        requestExtendMsg();
        return;
    }
    
    
    string xiaohaoStr = "消耗：";
    Label* leadLabel = PublicShowUI::getLabel(xiaohaoStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),24,false,false);
    leadLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(leadLabel);
    leadLabel->setPosition(this->getContentSize().width/2-leadLabel->getContentSize().width/2-50 *sx ,this->getContentSize().height/2+leadLabel->getContentSize().height/2-6*sx);
    this->addChild(leadLabel,1);

    string costGoldStr = StringUtils::format("%d",m_nextExtentGold);
    Label* costGoldLabel = PublicShowUI::getLabel(costGoldStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),24,false,false);
    costGoldLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(costGoldLabel);
    costGoldLabel->setPosition(this->getContentSize().width/2-costGoldLabel->getContentSize().width/2,this->getContentSize().height/2+costGoldLabel->getContentSize().height/2-6*sx);
    this->addChild(costGoldLabel,1);
    
    Sprite* gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    gold->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(gold);
    gold->setScale(0.7*sx);
    gold->setPosition(costGoldLabel->getPositionX()+costGoldLabel->getContentSize().width+5*sx,costGoldLabel->getPositionY()-4*sx);
    this->addChild(gold,1);
}


void FindExtendLayer::setSureBuyBtn()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    
    Sprite* buyWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    buyWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(buyWord);
    buyWord->setPosition(this->getContentSize().width/2-buyWord->getContentSize().width/2+100*sx ,50*sx);
    this->addChild(buyWord,3);
    
    Button * surebuy = Button::create(IMG_BUTTON_CONFIRM_LABEL, IMG_BUTTON_CONFIRM_LABEL, CC_CALLBACK_1(FindExtendLayer::onSureBuyClick, this));
    surebuy->setAnchorPoint(Point::ZERO);
    surebuy->setPosition(Point::ZERO);
    buyWord->addChild(surebuy,2);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumOkButton, surebuy);
    
    Sprite* cancelWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_RED);
    cancelWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(cancelWord);
    cancelWord->setPosition(this->getContentSize().width/2-cancelWord->getContentSize().width/2-100*sx ,50*sx);
    this->addChild(cancelWord,3);
    Button * cancel = Button::create(IMG_BUTTON_CANCEL_LABEL, IMG_BUTTON_CANCEL_LABEL, CC_CALLBACK_1(FindExtendLayer::onCencelClick, this));
    cancel->setAnchorPoint(Point::ZERO);
    cancel->setPosition(Point::ZERO);
    cancelWord->addChild(cancel,2);
}
void FindExtendLayer::onSureBuyClick(Ref* psender)
{
    if (m_nextExtentGold <GlobalInfo::getInstance()->userGold) {
        requestExtendMsg();
        NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumOkButton);
    }
    else
    {
        NoticeManager::getInstance()->showNotice("元宝不足，扩展失败!");
        this->removeFromParent();
    }
   
}
void FindExtendLayer::onCencelClick(Ref* psender)
{
    this->removeFromParent();
}

void FindExtendLayer::requestExtendMsg()//请求创建新领地
{
    MarketFindExtendMsg* msg = new MarketFindExtendMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void FindExtendLayer::onExtendMsgProcess(EventCustom* msg)//获取扩展领地成功返回值
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    
    if(message->messageID == SCENSE_CLIENT_FIND_FindExtendResp)
    {
        if(message->state)//返回成功
        {
            log("kuozhanchenggong");
            this->removeFromParent();
            int nextgold = message->byteStream->getInt();
            broadMsg(CUSTOM_MARKER_LINGDIKUOZHAN,__Integer::create(nextgold));
        }
    }
}
void FindExtendLayer::removeRequestfindlistMsg()//重新发送寻访消息
{
    MarketFindPageMsg* msg = new MarketFindPageMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void FindExtendLayer::addEventListener()
{

    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FIND_FindExtendResp).c_str(), CC_CALLBACK_1(FindExtendLayer::onExtendMsgProcess, this));
}
void FindExtendLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
