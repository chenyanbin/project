//
//  CreateNewLineupLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/16.
//
//

#include "CreateNewLineupLayer.h"
#include "../../common/TouchSprite/Button.h"
#include "../../message/Decoding/lineup/LineupCreateMsg/LineupCreateMsg.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "LineupLayer.h"
#include "../../protocol/Protocal.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../common/Dialog/Dialog.h"
CreateNewLineupLayer::CreateNewLineupLayer()
:m_nextConsume(0)
,m_AllPage(0)
,m_allGold(100000)
{
    
}
CreateNewLineupLayer::~ CreateNewLineupLayer()
{
    log("~StageLayer ~StageLayer");
}
bool CreateNewLineupLayer::init( int coust, int AllPage)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->m_nextConsume = coust;
        this->m_AllPage = AllPage;
        this->setBackground(IMG_DIALOG_BG,Point::ZERO,true);
        this->isAnimation = false;
        this->setClickEnabled(true);
        this->isClickClose = true;//点击外面自动关闭
        this->isShowGrayBg = true;
        setButton();
        bref = true;
    } while (false);
    return bref;
}
CreateNewLineupLayer* CreateNewLineupLayer::create(int coust, int AllPage)
{
    CreateNewLineupLayer* layer= new CreateNewLineupLayer();
    if(layer && layer->init(coust ,AllPage))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}

void CreateNewLineupLayer::show(int coust, int AllPage)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    CreateNewLineupLayer* layer = CreateNewLineupLayer::create(coust,AllPage);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}
void CreateNewLineupLayer::setButton()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    
    string titleStr = "是否激活新阵容?";//
    Label* titleLabel = PublicShowUI::getLabel(titleStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),24,false,false);
    titleLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(titleLabel);
    titleLabel->setPosition(this->getContentSize().width/2-titleLabel->getContentSize().width/2,this->getContentSize().height-100*sx);
    this->addChild(titleLabel);
    
    string numCard = StringUtils::format("花费： %d",m_nextConsume);//
    Label* numLabel = PublicShowUI::getLabel(numCard.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),24,false,false);
    numLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(numLabel);
    numLabel->setPosition(this->getContentSize().width/2-numLabel->getContentSize().width/2-30*sx, 150*sx);
    this->addChild(numLabel);
    
    Sprite* gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    gold->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(gold);
    gold->setScale(0.7*sx);
    gold->setPosition(numLabel->getPositionX()+numLabel->getContentSize().width+10*sx,numLabel->getPositionY());
    this->addChild(gold,1);
    
    Sprite* buyWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    buyWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(buyWord);
    buyWord->setPosition(this->getContentSize().width/2-buyWord->getContentSize().width/2+100*sx ,50*sx);
    this->addChild(buyWord,3);
    Button * surebuy = Button::create(IMG_BUTTON_CONFIRM_LABEL, IMG_BUTTON_CONFIRM_LABEL, CC_CALLBACK_1(CreateNewLineupLayer::onSureBuyClick, this));
    surebuy->setAnchorPoint(Point::ZERO);
    surebuy->setPosition(Point::ZERO);
    buyWord->addChild(surebuy,2);
    
    Sprite* cancelWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_RED);
    cancelWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(cancelWord);
    cancelWord->setPosition(this->getContentSize().width/2-cancelWord->getContentSize().width/2-100*sx ,50*sx);
    this->addChild(cancelWord,3);
    Button * cancel = Button::create(IMG_BUTTON_CANCEL_LABEL, IMG_BUTTON_CANCEL_LABEL, CC_CALLBACK_1(CreateNewLineupLayer::onCencelClick, this));
    cancel->setAnchorPoint(Point::ZERO);
    cancel->setPosition(Point::ZERO);
    cancelWord->addChild(cancel,2);

}
void CreateNewLineupLayer::onSureBuyClick(Ref* psender)
{
    log("chongzhi");
    requestCreateMsg();


}

void CreateNewLineupLayer::onCencelClick(Ref* psender)
{
    this->removeFromParent();
}
void CreateNewLineupLayer::onEnter()
{
    BaseLayer::onEnter();
}
void CreateNewLineupLayer::onExit()
{
    BaseLayer::onExit();
}
void CreateNewLineupLayer::onEnterTransitionDidFinish()
{
    
    BaseLayer::onEnterTransitionDidFinish();
    
}
void CreateNewLineupLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void CreateNewLineupLayer::requestCreateMsg()//创建新阵容
{
    LineupCreateMsg* msg = new LineupCreateMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void CreateNewLineupLayer::onCreateNewLineup(EventCustom* msg)//创建新阵容
{
        MessageReceive* message = (MessageReceive*)msg->getUserData();
        if(message->messageID == SCENSE_CLIENT_LINEUP_LineupCreateResp)
        {
            if(message->state)//创建成功
            {
                int mextLineupCount = message->byteStream->getInt();
                if (m_AllPage < 1) {
                    NoticeManager::getInstance()->showNotice("已开启阵容1");
                    LineupLayer::show(SCENE_TAG_MAINUI,1,0);
                }else{
                    broadMsg(CUSTOM_LINEUP_FIRSTCREATELINEUP,__Integer::create(mextLineupCount));
                }
                this->removeFromParent();
            }
            else
            {
                return;
            }
        }
}
void CreateNewLineupLayer::addEventListener()
{     
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LINEUP_LineupCreateResp).c_str(), CC_CALLBACK_1(CreateNewLineupLayer::onCreateNewLineup, this));//创建新阵容
}
void CreateNewLineupLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
