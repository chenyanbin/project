//
//  SetupLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/19.
//
//

#include "SetupLayer.h"
#include "../userWealth/UserHeadLayer.h"
#include "../../common/TouchSprite/Button.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "../../common/TouchSprite/onOffButton.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../sdk/SdkManager.h"
#include "../newPlayerGuide/NewPlayerGuild.h"
#include "../../common/Dialog/Dialog.h"
#include "../../protocol/Protocal.h"
#include "../../YVSDK/YVPlatform.h"
using namespace YVSDK;
#include "../../net/NetworkDataProcessing.h"
#include "../../message/Decoding/setup/RequestSetupMsg.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "../../common/StringUtil.h"
#include "../login/LoginLayer.h"
#include "../../message/Decoding/setup/RequestRandName.hpp"
#include "../../commonData/dictData/DictRoleLevel/DictRoleLevelManager.h"
#include "../../commonData/RoleData.h"
#include "../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../activity/cdkeyActivity/CdkeyActivity.h"
#include "../userWealth/UserHeadLayer.h"
SetupLayer::SetupLayer()
:editbox(NULL)
,MUSIC_TAG(10)
,SOUND_TAG(11)
{
    
}

SetupLayer::~SetupLayer()
{

}


bool SetupLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->setBackground(IMG_MARKET_MARKETJUXIAN_JUXIANBG,Point::ZERO,true);//  IMG_MARKET_MARKETJUXIAN_JUXIANBG
        this->isAnimation = false;
        
        
        this->isShowGrayBg = true;
        this->isAbleGuiding = false;
        setUiSpr();
        
        setSureBuyBtn();
        
        bref = true;
    } while (false);
    return bref;
}

SetupLayer* SetupLayer::create()
{
    SetupLayer* list = new SetupLayer();
    if(list && list->init())
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void SetupLayer::show()
{
    Scene* scene = Director::getInstance()->getRunningScene();
    SetupLayer* layer = SetupLayer::create();
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,SCENE_LAYER_ZORDER);
}

void SetupLayer::onEnter()
{
    BaseLayer::onEnter();
    this->setClickEnabled(true);
}
void SetupLayer::onExit()
{
    BaseLayer::onExit();
    this->setClickEnabled(false);
}
void SetupLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->isClickClose = true;//点击外面自动关闭
    if(GlobalInfo::getInstance()->gameRole->name == "")
    {
        onRandBtnClick(NULL);
    }
}
void SetupLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumNickNameInputBox) ;
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumReplaceTheNicknameButton);
}

void SetupLayer::setUiSpr()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    
    
    //设置字
    Sprite* setupword = Sprite::create(IMG_SETUP_SETUPWORD);
    setupword->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(setupword);
    setupword->setPosition(270*sx,this->getContentSize().height-setupword->getContentSize().height-5*sx);
    this->addChild(setupword,1);

    //头像
    DictHero* dictHero =  DictHeroManager::getInstance()->getData(GlobalInfo::getInstance()->gameRole->mainHeroDictID);
    if (dictHero) {
        const char* imgPath = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH, dictHero->headResource.c_str());
//        Sprite* heroHead = Sprite::create(imgPath);

        UserHeadLayer* heroHead = UserHeadLayer::create(imgPath,GlobalInfo::getInstance()->gameRole->quality,false);
        heroHead->setAnchorPoint(Point::ZERO);
        heroHead->setHeadInfo(GlobalInfo::getInstance()->gameRole->level, 0);
        PublicShowUI::setTargetScale(heroHead);
        heroHead->setPosition(40*sx,this->getContentSize().height/2-heroHead->getContentSize().height/2+80*sx);
        this->addChild(heroHead,1);
    }
    

    //输入框
    string moneyStr = GlobalInfo::getInstance()->gameRole->name;
    editbox = EditBox::create(Size(185 * sx,44 * sx), Scale9Sprite::create(IMG_SETUP_NANEBG));
    editbox->setAnchorPoint(Point::ZERO);
    editbox->setMaxLength(18);
    editbox->setFontSize(16);
    editbox->setText(moneyStr.c_str());
    editbox->setDelegate(this);
    editbox->setInputMode(EditBox::InputMode::ANY);
    editbox->setPosition(Point((this->getContentSize().width-editbox->getContentSize().width)/2-10*sx,this->getContentSize().height-editbox->getContentSize().height-50*sx));
    this->addChild(editbox,1);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumNickNameInputBox, editbox);
    //更改名字按钮
    Sprite* namebtn = Sprite::create(IMG_BUTTON_BYTTON_NANEBTN);
    namebtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(namebtn);
    namebtn->setPosition(editbox->getPositionX()+editbox->getContentSize().width-20*sx,editbox->getPositionY()-12*sx);
    this->addChild(namebtn,2);
    
    Button * surebuy = Button::create(IMG_BUTTON_BYTTON_NANEBTNWORD, IMG_BUTTON_BYTTON_NANEBTNWORD, CC_CALLBACK_1(SetupLayer::onchangenange, this));
    surebuy->setAnchorPoint(Point::ZERO);
    surebuy->getTouchListener()->setSwallowTouches(true);
    surebuy->setPosition(Point::ZERO);
    namebtn->addChild(surebuy,2);
  
     GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumReplaceTheNicknameButton, surebuy);
    
    
    
    //账号Id 经验条
    Sprite* zword = Sprite::create(IMG_SETUP_PROCESSGROMWORD);
    zword->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(zword);
    zword->setPosition(200*sx,  this->getContentSize().height/2-zword->getContentSize().height/2+50*sx);
    this->addChild(zword,1);
    
    //1 经验条
    DictRoleLevel* roleLevel = DictRoleLevelManager::getInstance()->getData(GlobalInfo::getInstance()->gameRole->level);
    float percent = GlobalInfo::getInstance()->gameRole->experience / roleLevel->needExp * 100;
    
    Sprite* downProSpr = Sprite::create(IMG_SETUP_PROCESSGROMBG);
    downProSpr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(downProSpr);
    downProSpr->setPosition(265*sx,240*sx);
    this->addChild(downProSpr,3);
    
    Sprite* progress = Sprite::create(IMG_SETUP_PROCESSGROM);
    progress->setAnchorPoint(Point::ZERO);
    ProgressTimer* progressTimer = ProgressTimer::create(progress);
    progressTimer->setType(ProgressTimer::Type::BAR);
    progressTimer->setMidpoint(Point(0,1));
    progressTimer->setBarChangeRate(Point(1,0));
    progressTimer->setAnchorPoint(Point::ZERO);
    progressTimer->setPosition(Point::ZERO);
    progressTimer->setPercentage(percent);
    downProSpr->addChild(progressTimer);
    
    string process = StringUtils::format("%d/%d",(int)GlobalInfo::getInstance()->gameRole->experience,roleLevel->needExp);
    Label* processLabel = PublicShowUI::getLabel(process.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_WHITE),16,false,false);
    processLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(processLabel);
    processLabel->setPosition(downProSpr->getPositionX()+downProSpr->getContentSize().width,  downProSpr->getPositionY()-3*sx);
    this->addChild(processLabel,1);
    
    
    //账号Id
    string user_id = GlobalInfo::getInstance()->gameID;
    Label* useridLabel = PublicShowUI::getLabel(user_id.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_WHITE),20,false,false);
    useridLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(useridLabel);
    useridLabel->setPosition(zword->getPositionX()+zword->getContentSize().width+5,  200*sx);
    this->addChild(useridLabel,1);
    
    
    //音乐
    Sprite* music = Sprite::create(IMG_SETUP_MUSIC);
    music->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(music);
    music->setPosition(300*sx,  this->getContentSize().height/2-music->getContentSize().height/2-15*sx);
    this->addChild(music,1);
    onOffButton* musicBtn = onOffButton::create(IMG_SETUP_SWITCHBG, IMG_SETUP_SMUSICNTNBG,IMG_SETUP_SWITCHBTN, CC_CALLBACK_1(SetupLayer::onclickMusic, this),IMG_SETUP_SWITCHBTN);
    musicBtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(musicBtn);
    musicBtn->setPosition(music->getPositionX()+music->getContentSize().width,music->getPositionY());
    musicBtn->setTag(MUSIC_TAG);
    musicBtn->setOnButton(GlobalInfo::getInstance()->getIsPlayBackMusic());
    this->addChild(musicBtn);
    
    //音效
    Sprite* yinxiao = Sprite::create(IMG_SETUP_YINXIAO);
    yinxiao->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(yinxiao);
    yinxiao->setPosition(300*sx,this->getContentSize().height/2-yinxiao->getContentSize().height/2-70*sx);
    this->addChild(yinxiao,1);
    onOffButton* soundBtn = onOffButton::create(IMG_SETUP_SWITCHBG, IMG_SETUP_SMUSICNTNBG,IMG_SETUP_SWITCHBTN, CC_CALLBACK_1(SetupLayer::onclickMusic, this),IMG_SETUP_SWITCHBTN);
    soundBtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(soundBtn);
    soundBtn->setPosition(yinxiao->getPositionX()+yinxiao->getContentSize().width,yinxiao->getPositionY());
    soundBtn->setTag(SOUND_TAG);
    soundBtn->setOnButton(GlobalInfo::getInstance()->getIsPlayBackMusic());
    this->addChild(soundBtn);
    
   
}
void SetupLayer::onRandBtnClick(Ref* pSender)
{
    Dialog::showServerLoading(1);
    int sex = PublicShowUI::genRandom(1, 2);
    RequestRandName* msg = new RequestRandName(sex);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
//控制音乐音效
void SetupLayer::onclickMusic(Ref* psender)
{
    Node* temp = (Node*)psender;
    int tag = temp->getTag();
    SoundManager::playEffectMusic(EFFECT_CLICK);
    if(tag == MUSIC_TAG)//音乐开关
    {
        onOffButton* temp2=(onOffButton*)psender;
        GlobalInfo::getInstance()->setIsPlayBackMusic(temp2->btnBol);
        
        if (temp2->btnBol) {
            log("打开背景音乐");
            SoundManager::resumeBackgroundMusic();
            
        }
        else
        {
            log("关闭背景音乐");
            SoundManager::pauseBackgroundMusic();
        }
        
    }else if (tag==SOUND_TAG)//音效开关
    {
        onOffButton* temp2=(onOffButton*)psender;
        GlobalInfo::getInstance()->setIsPlayEffectMusic(temp2->btnBol);
        if (temp2->btnBol) {
            log("打开音效");
            SoundManager::playEffectMusic(EFFECT_CLICK);
        }
        else
        {
            log("关闭音效");
            SoundManager::stopEffectMusic();
        }
    }
}


//修改名字
void SetupLayer::onchangenange(Ref* psender)
{

    log("genhuannicheng");
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumReplaceTheNicknameButton);
    string name =  editbox->getText();
    int len  = StringUtil::str_utf8_len(name.c_str());
    log("%d",len);
    if(len>6)
    {
        NoticeManager::getInstance()->showNotice("名字最多为6个字符");
        return;
    }
    if(name == GlobalInfo::getInstance()->gameRole->name)
    {
        NoticeManager::getInstance()->showNotice("修改昵称成功",NoticeManager::COLOR_GREEN);
        return;
    }
    log("%s",name.c_str());
    requestNameMsg(name);
 
    
 
}
void SetupLayer::setSureBuyBtn()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    //退出游戏
    Sprite* buyWord = Sprite::create(IMG_BUTTON_BYTTON_TUICHUBTN);
    buyWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(buyWord);
    buyWord->setPosition(this->getContentSize().width/2-buyWord->getContentSize().width/2 ,20*sx);
    this->addChild(buyWord,3);
    Button * surebuy = Button::create(IMG_BUTTON_BYTTON_TUICHUBTNWORD, IMG_BUTTON_BYTTON_TUICHUBTNWORD, CC_CALLBACK_1(SetupLayer::onSureBuyClick, this));
    surebuy->setAnchorPoint(Point::ZERO);
    surebuy->setPosition(Point::ZERO);
    buyWord->addChild(surebuy,2);
    
    //系统公告
    Sprite* cancelWord = Sprite::create(IMG_BUTTON_BYTTON_NANEBTN);
    cancelWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(cancelWord);
    cancelWord->setPosition(50*sx ,75*sx);
    this->addChild(cancelWord,3);
    Button * cancel = Button::create(IMG_BUTTON_BYTTON_XITONGGAOGAOWORD, IMG_BUTTON_BYTTON_XITONGGAOGAOWORD, CC_CALLBACK_1(SetupLayer::onNoticeClick, this));
    cancel->setAnchorPoint(Point::ZERO);
    cancel->setPosition(Point::ZERO);
    cancelWord->addChild(cancel,2);
    
    //激活码
    Sprite* jihuoWord = Sprite::create(IMG_BUTTON_BYTTON_NANEBTN);
    jihuoWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(jihuoWord);
    jihuoWord->setPosition(50*sx ,cancelWord->getPositionY()+cancelWord->getContentSize().height-10*sx);
    this->addChild(jihuoWord,3);
    Button * jihuo = Button::create(IMG_SETUP_ACATIVETIONCODE, IMG_SETUP_ACATIVETIONCODE, CC_CALLBACK_1(SetupLayer::onjihuomaClick, this));
    jihuo->setAnchorPoint(Point::ZERO);
    jihuo->setPosition(Point::ZERO);
    jihuoWord->addChild(jihuo,2);
    
}
void SetupLayer::onSureBuyClick(Ref* psender)
{
    SdkManager::getInstance()->startExit();
}
void SetupLayer::onDialogClick(Node* psender)
{
    if(psender->getTag() == 1)
    {
        SdkManager::getInstance()->startExit();
    }
}
//系统公告
void SetupLayer::onNoticeClick(Ref* psender)
{

}
//激活码
void SetupLayer::onjihuomaClick(Ref* psender)
{
            CdkeyActivity* layer=CdkeyActivity::create();
            layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
            Scene* scene=Director::getInstance()->getRunningScene();
            scene->addChild(layer,SCENE_LAYER_ZORDER);
}
/************************************************服务器***************************************************/
void SetupLayer::requestNameMsg(string _name)// 请求更改名字
{
    Dialog::showServerLoading(.5);
    RequestSetupMsg* msg = new RequestSetupMsg(_name);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void SetupLayer::onChageNameMsgProcess(EventCustom* msg)//获取成功返回值
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_ACCOUNT_SetRolenameResp)
    {
        if(message->state)//返回成功
        {
            GlobalInfo::getInstance()->gameRole->name = editbox->getText();
            broadMsg(CUSTOM_UPDATE_NICK_NAME);
            NoticeManager::getInstance()->showNotice("修改昵称成功",NoticeManager::COLOR_GREEN);
            YVSDK::YVPlatform::getSingletonPtr()->cpLogout();
            YVSDK::YVPlatform::getSingletonPtr()->cpLogin(PublicShowUI::numberToString(GlobalInfo::getInstance()->gameRole->roleID), GlobalInfo::getInstance()->gameRole->name);
            
            
            LoginLayer::enterMainUI();
            
            
        }
    }
    else if(message->messageID == SCENSE_CLIENT_ACCOUNT_RandomRoleNameResp)
    {
        if(message->state)
        {
            string initName = message->byteStream->getUTF8();
            initName = initName != "" ? initName : "金永哲";
            GlobalInfo::getInstance()->gameRole->name = initName;
            editbox->setText(initName.c_str());
            broadMsg(CUSTOM_UPDATE_NICK_NAME);
            requestNameMsg(initName);
        }
    }
}
void SetupLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ACCOUNT_SetRolenameResp).c_str(), CC_CALLBACK_1(SetupLayer::onChageNameMsgProcess, this));
     this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ACCOUNT_RandomRoleNameResp).c_str(), CC_CALLBACK_1(SetupLayer::onChageNameMsgProcess, this));
}
void SetupLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}

void SetupLayer::editBoxEditingDidBegin(EditBox* editBox)
{
    
}
void SetupLayer::editBoxEditingDidEnd(EditBox* editBox)
{
    log("editBoxEditingDidEnd");
}
void SetupLayer::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
 
}
void SetupLayer::editBoxReturn(EditBox* editBox)
{
    log("editBoxReturn");
    NewPlayerGuild::getInstance()->next();
}
void SetupLayer::backScene()
{
//    DictNewGuide* data = NewPlayerGuild::getInstance()->getNowData();
//    if(data)
//    {
//        if(data->bottomId == DictNewGuideEventEnumNickNameInputBox || data->bottomId == DictNewGuideEventEnumReplaceTheNicknameButton )
//        return;
//    }
    BaseLayer::backScene();
}