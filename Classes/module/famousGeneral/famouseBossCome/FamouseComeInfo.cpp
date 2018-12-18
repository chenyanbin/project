//
//  FamouseComeInfo.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/25.
//
//

#include "FamouseComeInfo.hpp"
#include "../../../protocol/Protocal.h"
#include "../../../message/Decoding/famouseGeneral/FamouseComeMsg.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/customButton/CustomButton.hpp"
#include "../../../message/Decoding/famouseGeneral/FamouseFightMsg.hpp"
#include "../../../common/Dialog/Dialog.h"
#include "../../../common/TimeUtil.h"
#include "FamouseReset.hpp"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../commonData/dictData/DictMonster/DictMonsterManager.h"
FamouseComeInfo::FamouseComeInfo()
:bloodPt(NULL)
,TAG_PROGRESS(1)
,TAG_ATTACKCOUNT(2)
,delayLabel(NULL)
,bossDictId(0)//	boss原型id	int	Y	DictLegendBattleMonster.id
,bossCurHp(0)//boss当前血量
,bossHpMax(0)//	boss最大血量	int	Y
,legendName("金永哲")//	名将传名称	string	Y
,attackCount(0)//	可用挑战次数	short	Y
,attackCountMax(0)//	最大挑战次数	short	Y
,activityStartTimes(0)//	活动开始时间	long	Y	单位：毫秒
,activityEndTimes(0)//	活动结束时间			单位：毫秒
,bossRemainSeconds(0)//	倒计时	int	Y	单位：秒此时间过后，boss会逃跑
,bossLevel(0)
{
    
}
FamouseComeInfo::~FamouseComeInfo()
{
    bloodPt = NULL;
    delayLabel = NULL;
}
bool FamouseComeInfo::init()
{

    setButton();
    Sprite* bg = Sprite::create(IMG_FAMOUSE_INFOBG);
    bg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bg);
    bg->setPosition(0, 70 * GlobalInfo::getInstance()->screenScaleX);
    this->addChild(bg,1,TAG_BG);
    Size size = bg->getContentSize();
    size.height = bg->getPositionY() + bg->getContentSize().height;
    this->setContentSize(size);
    setBloodPercent();
    setTitle();
  
    return true;
}
void FamouseComeInfo::setButton()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    CustomButton* delayBtn = CustomButton::create(IMG_PUBLIC_BUTTON_TWO_RED, "", CC_CALLBACK_1(FamouseComeInfo::onDelayBtnClick, this));
    delayBtn->setAnchorPoint(Point(.5,.5));
    
    delayBtn->addTitle(IMG_PUBLIC_LABEL_DELAYTITLE, IMG_PUBLIC_LABEL_DELAYTITLE);
    
    PublicShowUI::setTargetScale(delayBtn);
    delayBtn->setPosition(delayBtn->getContentSize().width/2, delayBtn->getContentSize().height/2);
    
    CustomButton* fightBtn = CustomButton::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(FamouseComeInfo::onFightBtnClick, this));
    fightBtn->setAnchorPoint(Point(.5,.5));
    fightBtn->addTitle(IMG_PUBLIC_LABEL_FIGHT, IMG_PUBLIC_LABEL_FIGHT);
    PublicShowUI::setTargetScale(fightBtn);
    fightBtn->setPosition(delayBtn->getPositionX() + delayBtn->getContentSize().width + 50 * sx, delayBtn->getPositionY());
    this->addChild(delayBtn,0);
    this->addChild(fightBtn,1);
}
void FamouseComeInfo::onDelayBtnClick(Ref* pSender)
{
    Node* parent = this->getParent();
    parent->removeFromParent();
}
void FamouseComeInfo::onFightBtnClick(Ref* pSender)
{
    Dialog::showServerLoading();
    GlobalInfo::getInstance()->battleType = kBattleType_MingJiangZhuan;
    FamouseFightMsg* msg = new FamouseFightMsg(GlobalInfo::getInstance()->famouseBossID);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
   
}
void FamouseComeInfo::setBloodPercent()
{
    Sprite* bloodBg = Sprite::create(IMG_FAMOUSE_COME_BLOODBG);
    bloodBg->setAnchorPoint(Point::ZERO);
   
    Sprite* blood = Sprite::create(IMG_FAMOUSE_COME_BLOOD);
    blood->setAnchorPoint(Point::ZERO);
    bloodPt = ProgressTimer::create(blood);
    bloodPt->setAnchorPoint(Point::ZERO);
    bloodPt->setType(ProgressTimer::Type::BAR);
    bloodPt->setMidpoint(Point(0,1));
    bloodPt->setBarChangeRate(Point(1,0));
    bloodPt->setPercentage(0);
    bloodPt->setPosition((bloodBg->getContentSize().width - bloodPt->getContentSize().width)/2,0);
    
    bloodBg->addChild(bloodPt,1);
    
    PublicShowUI::setTargetScale(bloodBg);
    this->addChild(bloodBg,3,TAG_PROGRESS);
    bloodBg->setPosition(2 * GlobalInfo::getInstance()->screenScaleX, this->getContentSize().height - bloodBg->getContentSize().height - 2 * GlobalInfo::getInstance()->screenScaleX);
}
void FamouseComeInfo::setTitle()
{
    Node* blood = this->getChildByTag(TAG_PROGRESS);
    
    Sprite* title = Sprite::create(IMG_FAMOUSE_COME_TITLE);
    title->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(title);
    title->setPosition(30 * GlobalInfo::getInstance()->screenScaleX, blood->getPositionY() + blood->getContentSize().height + 10 * GlobalInfo::getInstance()->screenScaleX);
//    this->addChild(title,5);
    
    Size size = this->getContentSize();
    size.height = title->getPositionY() + title->getContentSize().height;
    this->setContentSize(size);
}
void FamouseComeInfo::onEnter()
{
    BaseLayer::onEnter();
    this->setClickEnabled(true);
}
void FamouseComeInfo::onExit()
{
    BaseLayer::onExit();
}
void FamouseComeInfo::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    this->setClickEnabled(false);
}
void FamouseComeInfo::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    
    requestInfoMsg();
}
void FamouseComeInfo::requestInfoMsg()
{
    Dialog::showServerLoading();
    FamouseComeMsg* msg = new FamouseComeMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void FamouseComeInfo::onMsgProcess(EventCustom* message)
{
    Dialog::hideServerLoading();
    MessageReceive* msg = (MessageReceive*)message->getUserData();
    if(!msg->state)
    {
        return;
    }
    if(msg->messageID == SCENSE_CLIENT_LEGEND_LegendBattlePageResp)
    {
        this->bossDictId = msg->byteStream->getInt();
     
        this->legendName = msg->byteStream->getUTF8();//	名将传名称	string	Y
        GlobalInfo::getInstance()->famouseName = legendName;
        this->bossLevel = msg->byteStream->getShort();
        this->attackCount = msg->byteStream->getShort();//	可用挑战次数	short	Y
        this->attackCountMax = msg->byteStream->getShort();//	最大挑战次数	short	Y
        this->activityStartTimes = msg->byteStream->getLong();//	活动开始时间	long	Y	单位：毫秒
        this->activityEndTimes = msg->byteStream->getLong();//	活动结束时间			单位：毫秒
        this->bossRemainSeconds	= msg->byteStream->getInt();// 倒计时	int	Y	单位：秒//        此时间过后，boss会逃跑
        this->bossCurHp = msg->byteStream->getInt();
        this->bossHpMax	= msg->byteStream->getInt();
        GlobalInfo::getInstance()->famouseBossBlood = this->bossCurHp;
        this->updateProgress();
        setInfo();
        updateAttackCount();
    }
    else if (msg->messageID == SCENSE_CLIENT_ITEM_ItemUseResp)
    {
        requestInfoMsg();
    }
}
void FamouseComeInfo::onDelay()
{
//    bossRemainSecondsdelayLabel
    string  str = PublicShowUI::getTime(bossRemainSeconds * 1000);
    delayLabel->setString(str);
    bossRemainSeconds --;
    GlobalInfo::getInstance()->famouseLeftSeconds = bossRemainSeconds;
    if(bossRemainSeconds < 0)
    {
        GlobalInfo::getInstance()->famouseLeftSeconds = 0;
        return;
    }
    DelayTime* delay = DelayTime::create(1);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(FamouseComeInfo::onDelay, this));
    this->runAction(Sequence::create(delay,callBack, NULL));
}
void FamouseComeInfo::setInfo()
{
    if(delayLabel)
    {
        return;
    }
    float disY = 50;
    int fontSize = 20;
    Node* node = this->getChildByTag(TAG_BG);
    //逃亡剩余时间
    Sprite* leftTime = Sprite::create(IMG_FAMOUSE_EASECAPE_TIME);
    leftTime->setAnchorPoint(Point::ZERO);
    
    if(!delayLabel)
    {
        delayLabel = PublicShowUI::getLabel("00:00:00",PublicShowUI::getColor3b(COLOR_PINK),fontSize,false,false);
        delayLabel->setAnchorPoint(Point::ZERO);
        leftTime->addChild(delayLabel,1);
        delayLabel->setPosition(150,0);
        leftTime->setPosition(4,12);
        node->addChild(leftTime);
        onDelay();
    }
    
    //活动时间
    Sprite* activeTime = Sprite::create(IMG_FAMOUSE_ACTIVETIME);
    activeTime->setAnchorPoint(Point::ZERO);
    string m_activeStartTime = TimeUtil::timetodate(activityStartTimes / 1000);
    m_activeStartTime = m_activeStartTime.substr(0,m_activeStartTime.size() - 3);
    
    string m_activeEndTime = TimeUtil::timetodate(activityEndTimes / 1000);
    m_activeEndTime = m_activeEndTime.substr(0,m_activeEndTime.size() - 3);
    
    string str = m_activeStartTime + "\n" + m_activeEndTime;
    Label* timeLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),fontSize,false,false);
    timeLabel->setAnchorPoint(Point::ZERO);
    activeTime->addChild(timeLabel);
    timeLabel->setPosition(activeTime->getContentSize().width,-20);
    node->addChild(activeTime);
    activeTime->setPosition(leftTime->getPositionX(),leftTime->getPositionY() + disY + 30);
    
    //挑战次数
  
    Sprite* challegeSpr = Sprite::create(IMG_FAMOUSE_CHALLENGECOUNT);
    challegeSpr->setAnchorPoint(Point::ZERO);
 
    str = PublicShowUI::numberToString(attackCount) + " / " + PublicShowUI::numberToString(attackCountMax);
    Label* countLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),fontSize,false,false);
    countLabel->setAnchorPoint(Point::ZERO);
    challegeSpr->addChild(countLabel,3,TAG_ATTACKCOUNT);
    countLabel->setPosition(challegeSpr->getContentSize().width,0);
    node->addChild(challegeSpr,3,TAG_ATTACKCOUNT);
    challegeSpr->setPosition(activeTime->getPositionX(),activeTime->getPositionY() + disY);
    
    //重置按钮
    CustomButton* resetBtn = CustomButton::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(FamouseComeInfo::onResetClick, this));
    resetBtn->setPosition(challegeSpr->getPositionX() + challegeSpr->getContentSize().width + countLabel->getContentSize().width + resetBtn->getContentSize().width / 2 + 15, challegeSpr->getPositionY() + resetBtn->getContentSize().height/2 - 2);
    resetBtn->addTitle(IMG_PUBLIC_LABEL_RESET, IMG_PUBLIC_LABEL_RESET);
    node->addChild(resetBtn);
    //名将传名字
//    str = this->legendName;
    DictMonster* dictMonster = DictMonsterManager::getInstance()->getData(this->bossDictId);
    str = dictMonster ? dictMonster->name : this->legendName ;
    str +=  "  LV" + PublicShowUI::numberToString(bossLevel);
    Label* nameLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),fontSize + 2,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    node->addChild(nameLabel);
    nameLabel->setPosition(challegeSpr->getPositionX(),challegeSpr->getPositionY() + disY);
    
}
void FamouseComeInfo::updateAttackCount()//更新挑战次数
{
    string str = PublicShowUI::numberToString(attackCount) + " / " + PublicShowUI::numberToString(attackCountMax);
     Node* node = this->getChildByTag(TAG_BG);
    Sprite* challegeSpr = (Sprite*)node->getChildByTag(TAG_ATTACKCOUNT);
    if(challegeSpr)
    {
        Label* label = (Label*)challegeSpr->getChildByTag(TAG_ATTACKCOUNT);
        label->setString(str);
    }
}
void FamouseComeInfo::onResetClick(Ref* pSender)
{
     FamouseReset::show(attackCount);
//    if(this->attackCount >= this->attackCountMax)
//    {
//        NoticeManager::getInstance()->showNotice("您的名将传次数已满，无需恢复",NoticeManager::COLOR_GREEN);
//    }
//    else
//    {
//            FamouseReset::show(attackCount);
//    }

//    Dialog::show("消耗10元宝，重置扫荡次数","",2,this,callfuncN_selector(FamouseComeInfo::onConfirmCallBack));
}
void FamouseComeInfo::onConfirmCallBack(Node* pSender)
{
    int tag = pSender->getTag();
    log("tag=%d",tag);
    if(pSender->getTag() == 1)
    {
        
    }
}
void FamouseComeInfo::updateProgress()
{
    float percent = (this->bossCurHp / this->bossHpMax) * 100;
    this->bloodPt->stopAllActions();
    ProgressFromTo* action = ProgressFromTo::create(.5,bloodPt->getPercentage(),percent);
    bloodPt->runAction(action);
    string str = PublicShowUI::numberToString(int(bossCurHp)) + "/" + PublicShowUI::numberToString(int(bossHpMax));
    Label* label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),20,false,false);
 
    label->setPosition(bloodPt->getContentSize().width / 2, bloodPt->getContentSize().height/2);
    bloodPt->getParent()->addChild(label,4);
}
void FamouseComeInfo::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LEGEND_LegendBattlePageResp).c_str() , CC_CALLBACK_1(FamouseComeInfo::onMsgProcess, this));
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ITEM_ItemUseResp).c_str() , CC_CALLBACK_1(FamouseComeInfo::onMsgProcess, this));
}
void FamouseComeInfo::removeEventListener()
{
    BaseLayer::removeEventListener();
}