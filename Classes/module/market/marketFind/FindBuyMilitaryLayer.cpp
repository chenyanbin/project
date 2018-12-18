//
//  FindBuyMilitaryLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/1.
//
//

#include "FindBuyMilitaryLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/market/findStartMsg/FindStartMsg.h"
#include "../../../message/Decoding/market/marketFindMsg/MarketFindPageMsg.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../marketData/marketFindDataManager.h"
#include "../../../common/Dialog/Dialog.h"
#include "../marketData/StartFinddataManger.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "FinderHeroListLayer.h"
#include "../marketData/MarketFindData.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
FindBuyMilitaryLayer::FindBuyMilitaryLayer()
:m_nowcount(0)
,TAG_COUNT(2)
,TAG_ALLCOUNT(3)
,editbox(NULL)
,slide_control(NULL)
,m_idx(0)
,m_minHonor(0)
,m_jungongCount(0)
,jungongcountlabel(NULL)
{
    
}

FindBuyMilitaryLayer::~FindBuyMilitaryLayer()
{
//    StartFinddataManger::getInstance()->destroyInstance();
}


bool FindBuyMilitaryLayer::init(int idx, int _minHonor, int _jungongCount)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        m_idx = idx;
        m_minHonor = _minHonor;
        m_jungongCount = _jungongCount;
        this->setBackground(IMG_DIALOG_BG,Point::ZERO,true);
        this->isAnimation = false;
        this->setClickEnabled(true);
        this->isClickClose = true;//点击外面自动关闭
        this->isShowGrayBg = true;
        setUIButton();
        setPrice(m_nowcount);
        setSureBuyBtn();
        bref = true;
    } while (false);
    return bref;
}

FindBuyMilitaryLayer* FindBuyMilitaryLayer::create(int idx, int _minHonor, int _jungongCount)
{
    FindBuyMilitaryLayer* list = new FindBuyMilitaryLayer();
    if(list && list->init(idx,_minHonor,_jungongCount))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void FindBuyMilitaryLayer::show(int idx, int _minHonor, int _jungongCount)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    FindBuyMilitaryLayer* layer = FindBuyMilitaryLayer::create(idx,_minHonor,_jungongCount);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}

void FindBuyMilitaryLayer::onEnter()
{
    BaseLayer::onEnter();
}
void FindBuyMilitaryLayer::onExit()
{
    BaseLayer::onExit();
}
void FindBuyMilitaryLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void FindBuyMilitaryLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumPlusButton);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumOkButton);
}

void FindBuyMilitaryLayer::setUIButton()
{

    float sx = GlobalInfo::getInstance()->screenScaleX;
    
    MarketFindData* data =  marketFindDataManager::getInstance()->findList->at(m_idx);
    DictHero* dictHero = DictHeroManager::getInstance()->getData(data->heroDictId);
    if (dictHero) {
        UserHeadLayer* userHead=UserHeadLayer::create(dictHero->resource.c_str(),data->heroQuality);
        userHead->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(userHead);
        userHead->setHeadInfo(data->heroLevel, data->heroPrestige);
        userHead->setPosition(50*sx ,this->getContentSize().height-userHead->getContentSize().height-60*sx);
        this->addChild(userHead,2);
    }else{
        TouchSprite* boxbg = TouchSprite::createWithPic(IMG_PUBLIC_HEROHEADBG, this, callfuncN_selector(FindBuyMilitaryLayer::onHeadClick));
        boxbg->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(boxbg);
        boxbg->setPosition(50*sx ,this->getContentSize().height-boxbg->getContentSize().height-60*sx);
        this->addChild(boxbg,1,1);
        Label* xunfangLabel = PublicShowUI::getLabel("选择武将",PublicShowUI::getColor3b(COLOR_GREEN_BLUE),32,false,false);
        xunfangLabel->setAnchorPoint(Point::ZERO);
        xunfangLabel->setMaxLineWidth(80);
        xunfangLabel->setPosition(25,20);
        boxbg->addChild(xunfangLabel,2);
    }
    //军工Word
    Sprite* nowHave = Sprite::create(IMG_MARKET_MARKETFIND_MILITARYWORD);
    nowHave->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(nowHave);
    nowHave->setPosition(50*sx,this->getContentSize().height-nowHave->getContentSize().height-30*sx);
//    this->addChild(nowHave,1);

    //总军工
    string renwuWord= "拥有铜钱";
    Label* renwuLabel = PublicShowUI::getLabel(renwuWord.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
    renwuLabel->setAnchorPoint(Point(Point::ZERO));
    PublicShowUI::setTargetScale(renwuLabel);
    renwuLabel->setPosition(this->getContentSize().width/2-renwuLabel->getContentSize().width/2-70*sx ,this->getContentSize().height/2+renwuLabel->getContentSize().height/2+60*sx);    
    this->addChild(renwuLabel,2);
   
    string timesStr=StringUtils::format("%d",m_jungongCount);
    Label* jungongLabel = PublicShowUI::getLabel(timesStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
    jungongLabel->setAnchorPoint(Point(Point::ZERO));
    PublicShowUI::setTargetScale(jungongLabel);
    jungongLabel->setPosition(renwuLabel->getPositionX()+renwuLabel->cocos2d::Node::getContentSize().width+20*sx,renwuLabel->getPositionY());
    this->addChild(jungongLabel,2);
    
    //消耗军工
    string renwuWord1= "花费铜钱";
    Label* renwuLabel1 = PublicShowUI::getLabel(renwuWord1.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
    renwuLabel1->setAnchorPoint(Point(Point::ZERO));
    PublicShowUI::setTargetScale(renwuLabel1);
    renwuLabel1->setPosition(this->getContentSize().width/2-renwuLabel1->getContentSize().width/2-70*sx ,this->getContentSize().height/2+renwuLabel1->getContentSize().height/2+20*sx);
    this->addChild(renwuLabel1,2);
    
    
    string jungongcount= "0";
    jungongcountlabel = PublicShowUI::getLabel(jungongcount.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
    jungongcountlabel->setAnchorPoint(Point(Point::ZERO));
    PublicShowUI::setTargetScale(jungongcountlabel);
    jungongcountlabel->setPosition(Point(renwuLabel1->getPositionX()+renwuLabel1->cocos2d::Node::getContentSize().width+20*sx,renwuLabel1->getPositionY()-4*sx));
    this->addChild(jungongcountlabel,2);
    //设置军工
//    editbox = EditBox::create(Size(91 ,29 ), Scale9Sprite::create(IMG_MARKET_MARKETSHOP_PRICEBG));
//    editbox->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(editbox);
//    editbox->setInputMode(EditBox::InputMode::NUMERIC);
//    editbox->setDelegate(this);//开启委托
//    editbox->setFontColor(Color3B::WHITE);//设置文字颜色
//    editbox->setText("0");//设置默认显示数字
//    editbox->setPosition(Point(renwuLabel1->getPositionX()+renwuLabel1->cocos2d::Node::getContentSize().width+20*sx,renwuLabel1->getPositionY()-4*sx));
//    this->addChild(editbox,1);
    
    slide_control = ControlSlider::create(IMG_MARKET_MARKETFIND_MILITARYBG,IMG_MARKET_MARKETFIND_MILITARYTIAO,IMG_MARKET_MARKETFIND_MILITARYSLIDER);
    slide_control->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(slide_control);
    slide_control->setPosition(Point(this->getContentSize().width/2-slide_control->getContentSize().width/2+50*sx,this->getContentSize().height/2-slide_control->getContentSize().height/2));
    slide_control->setMinimumValue(0.0f);//设置最小值
    int maxNum = m_jungongCount;
    if (m_jungongCount>10000) {
        maxNum = 10000;
    }
    slide_control->setMaximumValue(maxNum);//设置最大值
    slide_control->setValue(1.0f);//设置初始值
    slide_control->setTag(20);
    slide_control->addTargetWithActionForControlEvents(this,cccontrol_selector(FindBuyMilitaryLayer::slideCallback),Control::EventType::VALUE_CHANGED);//设置拖动回调
    this->addChild(slide_control,1);

    //加10
    Button * addTen = Button::create(IMG_MARKET_MARKETSHOP_ADDTEN, IMG_MARKET_MARKETSHOP_ADDTEN, CC_CALLBACK_1(FindBuyMilitaryLayer::onBuyclick, this));
    addTen->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(addTen);
    addTen->setPosition(this->getContentSize().width/2-addTen->getContentSize().width/2+170*sx,this->getContentSize().height/2-addTen->getContentSize().height/2);
    this->addChild(addTen,2,TAG_ADDTEN);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumPlusButton, addTen);
    //减10
    Button * minTen = Button::create(IMG_MARKET_MARKETSHOP_MINTEN, IMG_MARKET_MARKETSHOP_MINTEN, CC_CALLBACK_1(FindBuyMilitaryLayer::onBuyclick, this));
    minTen->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(minTen);
    minTen->setPosition(this->getContentSize().width/2-minTen->getContentSize().width/2 - 70*sx,this->getContentSize().height/2-minTen->getContentSize().height/2);
    this->addChild(minTen,2 ,TAG_MINUSTEN);
    
}

void FindBuyMilitaryLayer::onHeadClick(Node* psender)
{
    if (marketFindDataManager::getInstance()->findList->at(m_idx)->status == 1) {
        FinderHeroListLayer::show(m_idx);
        log("%d",psender->getTag());
    }
}
void FindBuyMilitaryLayer::onBuyclick(Ref* psender)
{
    Node* target = (Node*)psender;
    switch (target->getTag()) {
        case TAG_ADDTEN:
            m_nowcount += 10;
            break;
        case TAG_MINUSTEN:
            m_nowcount -= 10;
            break;
        default:
            break;
    }
    if (m_nowcount <= 0) {
        m_nowcount = 0;
    }
    setPrice(m_nowcount);
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumPlusButton);
}
void FindBuyMilitaryLayer::setPrice(int nowCount)
{
    int current_value = nowCount;//获取slide当前的值
    char buf_str[16];
    sprintf(buf_str,"%d",current_value);
//    editbox->setText(buf_str);
    slide_control->setValue((float)nowCount);//重新设置slide的值
}

void FindBuyMilitaryLayer::setSureBuyBtn()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* buyWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    buyWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(buyWord);
    buyWord->setPosition(this->getContentSize().width/2-buyWord->getContentSize().width/2+100*sx ,40*sx);
    this->addChild(buyWord,3);
    Button * surebuy = Button::create(IMG_BUTTON_CONFIRM_LABEL, IMG_BUTTON_CONFIRM_LABEL, CC_CALLBACK_1(FindBuyMilitaryLayer::onSureBuyClick, this));
    surebuy->setAnchorPoint(Point::ZERO);
    surebuy->setPosition(Point::ZERO);
    buyWord->addChild(surebuy,2);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumOkButton, surebuy);
    Sprite* cancelWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_RED);
    cancelWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(cancelWord);
    cancelWord->setPosition(this->getContentSize().width/2-cancelWord->getContentSize().width/2-100*sx ,40*sx);
    this->addChild(cancelWord,3);
    Button * cancel = Button::create(IMG_BUTTON_CANCEL_LABEL, IMG_BUTTON_CANCEL_LABEL, CC_CALLBACK_1(FindBuyMilitaryLayer::onCencelClick, this));
    cancel->setAnchorPoint(Point::ZERO);
    cancel->setPosition(Point::ZERO);
    cancelWord->addChild(cancel,2);

}
void FindBuyMilitaryLayer::onSureBuyClick(Ref* psender)
{
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumOkButton);
    log("%zd",marketFindDataManager::getInstance()->findList->size());
    if (m_nowcount<m_minHonor) {
        string numCard = StringUtils::format("军功数不可以少于%d",m_minHonor);
        NoticeManager::getInstance()->showNotice(numCard.c_str());
        return;
    }else{
        requestMilitaryMsg(marketFindDataManager::getInstance()->findList->at(m_idx)->findId,m_nowcount);
    }
}
void FindBuyMilitaryLayer::onCencelClick(Ref* psender)
{
    this->removeFromParent();
}
void FindBuyMilitaryLayer::slideCallback(Ref *sender, Control::EventType controlEvent)
{
    auto slide_control = (ControlSlider*)sender;//通过回调参数sender 获得ControlSlider
    int current_value = slide_control->getValue();//获取slide当前的值
    
    char buf_str[16];
    sprintf(buf_str,"%d",current_value);
    
    jungongcountlabel->setString(buf_str);
//    editbox->setText(buf_str);//设置editBox的值
    m_nowcount = current_value;
}

void FindBuyMilitaryLayer::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
    int num_int = std::atoi(text.c_str());//将字符串转成整型
    int maxNum = m_jungongCount;//因为controlSlider 的最大值为100，所以这里输入的值最大也不能超过100
    if (m_jungongCount>10000) {
        maxNum = 10000;
    }
    if(num_int > maxNum)
    {
        num_int = maxNum;
    }
    char buf_str[16];
    sprintf(buf_str,"%d",num_int);//将int的数值放入buf_str中
    editBox->setText(buf_str);//重新设置editBox的值
    //改变ControlSlider的值
    slide_control->setValue((float)num_int);//重新设置slide的值
    m_nowcount = num_int;
}
void FindBuyMilitaryLayer::editBoxReturn(cocos2d::extension::EditBox*){}
void FindBuyMilitaryLayer::editBoxEditingDidEnd(cocos2d::extension::EditBox*){}
void FindBuyMilitaryLayer::editBoxEditingDidBegin(cocos2d::extension::EditBox*){}

/**************--------------------------访问服务器------------------------------------*****************/
void FindBuyMilitaryLayer::requestMilitaryMsg(int findId, int honor)//开始寻访
{
    Dialog::showServerLoading(0.5);
    FindStartMsg* msg = new FindStartMsg(findId,honor);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void FindBuyMilitaryLayer::onMilitaryMsgProcess(EventCustom* msg)//接收开始寻访消息
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    Dialog::hideServerLoading();
    if(message->messageID == SCENSE_CLIENT_FIND_FindStartResp)
    {
        if(message->state)//返回成功
        {
            StartFinddataManger::getInstance()->setfindIdData(message->byteStream->getInt());
            StartFinddataManger::getInstance()->setRemainingTimesData(message->byteStream->getInt());
            StartFinddataManger::getInstance()->setjiasugoldData(message->byteStream->getInt());
            StartFinddataManger::getInstance()->setxunfanglingData(message->byteStream->getInt());
            StartFinddataManger::getInstance()->setjungongData(message->byteStream->getInt());
            this->removeFromParent();
            broadMsg(CUSTOM_MARKER_KAISHIXUNFANG);
        }
    }
}
void FindBuyMilitaryLayer::addEventListener()
{
    
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FIND_FindStartResp).c_str(), CC_CALLBACK_1(FindBuyMilitaryLayer::onMilitaryMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FIND_FindStartResp).c_str(), CC_CALLBACK_1(FindBuyMilitaryLayer::onMilitaryMsgProcess, this));
}
void FindBuyMilitaryLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}

