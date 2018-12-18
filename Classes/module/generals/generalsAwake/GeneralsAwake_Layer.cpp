//
//  GeneralsAwake_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/2.
//
//

#include "GeneralsAwake_Layer.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/generals/awake/HeroAwakeMsg.h"
#include "../data/CardDataManager.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../message/Decoding/generals/awake/HeroAwakeUpMsg.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../common/commonEffect/CommonEffect.h"
#include "../../../commonData/dictData/DictItem/DictItemManager.h"
GeneralsAwake_Layer::GeneralsAwake_Layer()
:sx(1)
,TAG_AWAKEN(1)
,TAG_NODEBG(2)
,m_awakeData(NULL)
{
    m_awakeData=new AwakeData();
}
GeneralsAwake_Layer::~GeneralsAwake_Layer()
{
    CC_SAFE_RELEASE_NULL(m_awakeData);
}
void GeneralsAwake_Layer::onExit()
{
    BaseLayer::onExit();
}
void GeneralsAwake_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void GeneralsAwake_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void GeneralsAwake_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestListMsg();
}
bool GeneralsAwake_Layer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        this->setBackground(IMG_GENERALS_BG);
//                this->createLayer();
        bref = true;
    } while (false);
    return bref;
}
void GeneralsAwake_Layer::createLayer()
{
    Sprite* bgSprite=(Sprite*)this->getChildByTag(TAG_BG);
    Node* bgNode=(Node*)bgSprite->getChildByTag(TAG_NODEBG);
    if (bgNode) {
        bgSprite->removeChildByTag(TAG_NODEBG);
    }
    bgNode=Node::create();
    bgNode->setAnchorPoint(Point::ZERO);
    bgNode->setContentSize(bgSprite->getContentSize()/sx);
    bgSprite->addChild(bgNode,1,TAG_NODEBG);
    CardPropertyData* data = CardDataManager::getInstance()->getPresentData();
    if (!data) {
        return;
    }
    //
    
    
    int tempNum=data->heroDictId;
    DictHero* dictHero = DictHeroManager::getInstance()->getData(tempNum);
    if (!dictHero) {
        return;
    }
    //
    Sprite* bg=Sprite::create(IMG_GENERALS_AWAKE_BG);
    bg->setAnchorPoint(Point::ZERO);
    bg->setPosition(0,bgNode->getContentSize().height-bg->getContentSize().height-20);
    bgNode->addChild(bg);
    
    const char* imgPath = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH, dictHero->headResource.c_str());
    UserEquipLayer* userHead=UserEquipLayer::create(imgPath,data->quality,false);
    userHead->setAnchorPoint(Point::ZERO);
    userHead->setPosition(36,364);
    bgNode->addChild(userHead,1);
    
    string str=data->heroName;
    Label*userHeadLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),18,false,false);
    userHeadLabel->setAnchorPoint(Point::ZERO);
    userHeadLabel->setPosition(205,435);
    bgNode->addChild(userHeadLabel);
    
    str="LV"+PublicShowUI::numberToString(data->level);
    Label*userLvLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0x28dc41),18,false,false);
    userLvLabel->setAnchorPoint(Point::ZERO);
    userLvLabel->setPosition(160,412);
    bgNode->addChild(userLvLabel);
    //分割线
    Sprite* lineSprite3=Sprite::create(IMG_GENERALS_SKILL_CONT_LINE);
    lineSprite3->setAnchorPoint(Point::ZERO);
    lineSprite3->setPosition((bgNode->getContentSize().width-lineSprite3->getContentSize().width)/2, bg->getPositionY()-lineSprite3->getContentSize().height-10);
    bgNode->addChild(lineSprite3);
    
    
    
    if (data->quality>=8 or m_awakeData->canWakeUp==0) {
        Sprite* maxSp=Sprite::create(IMG_PUBLIC_LABEL_MAXQUALITY);
        maxSp->setAnchorPoint(Point::ZERO);
        maxSp->setPosition((bgNode->getContentSize().width-maxSp->getContentSize().width)/2,20);
        bgNode->addChild(maxSp);
    }else
    {
        UserEquipLayer* userHead2=UserEquipLayer::create(imgPath,data->quality+1,false);
        userHead2->setAnchorPoint(Point::ZERO);
        userHead2->setPosition(36,102);
        bgNode->addChild(userHead2,1);
        
        string str=data->heroName;
        Label*userHead2Label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),18,false,false);
        userHead2Label->setAnchorPoint(Point::ZERO);
        userHead2Label->setPosition(205,170);
        bgNode->addChild(userHead2Label);
        
        str="LV"+PublicShowUI::numberToString(data->level);
        Label*userLv2Label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0x28dc41),18,false,false);
        userLv2Label->setAnchorPoint(Point::ZERO);
        userLv2Label->setPosition(160,150);
        bgNode->addChild(userLv2Label);
        
        const char* path=PublicShowUI::getGoods(DictItemTypeEnumItem, m_awakeData->needStoneId);
        Sprite* stone=Sprite::create(path);
        stone->setAnchorPoint(Point::ZERO);
        stone->setPosition(150,246);
        stone->setScale(0.6);
        stone->setContentSize(stone->getContentSize()*0.6);
        bgNode->addChild(stone);
        
        DictItem* itemData=DictItemManager::getInstance()->getData(m_awakeData->needStoneId);
        if (itemData) {
            char stt[100]="";
            sprintf(stt,IMG_PUBLIC_HEADTALENTFRAME,itemData->quality);
            Sprite* stoneBox=Sprite::create(stt);
            stoneBox->setAnchorPoint(Point::ZERO);
            float scalex=(stone->getContentSize().width+4)/stoneBox->getContentSize().width;
            float scaleY=(stone->getContentSize().height+4)/stoneBox->getContentSize().height;
            stoneBox->setScale(scalex, scaleY);
            stoneBox->setPosition(149,245);
            bgNode->addChild(stoneBox,2);
        }
        
        
        
        str=m_awakeData->needStoneName+"  "+PublicShowUI::numberToString(m_awakeData->ownStoneCount)+"/"+PublicShowUI::numberToString(m_awakeData->needStoneCount);
        Label*stoneNameLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),18,false,false);
        stoneNameLabel->setAnchorPoint(Point::ZERO);
        stoneNameLabel->setPosition(104,329);
        bgNode->addChild(stoneNameLabel);
        
        //消耗
        string num=PublicShowUI::numberToString(m_awakeData->needCoin);
        Sprite* cooperNode = Sprite::create(IMG_ICON_PUBLIC_COIN);
        cooperNode->setAnchorPoint(Point::ZERO);
        cooperNode->setScale(0.7, 0.7);
        cooperNode->setContentSize(cooperNode->getContentSize()*0.7);
        cooperNode->setPosition(30,30);
        bgNode->addChild(cooperNode,1);
        
        Label* cooperLabel = PublicShowUI::getLabel(num.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),17,false,false);
        cooperLabel->setAnchorPoint(Point::ZERO);
        cooperLabel->setPosition(10 +cooperNode->getContentSize().width+cooperNode->getPositionX(),(cooperNode->getContentSize().height-cooperLabel->getContentSize().height)/2+cooperNode->getPositionY());
        bgNode->addChild(cooperLabel);
        
        Button* awakenBtn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE,IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(GeneralsAwake_Layer::onBtnClick, this));
        awakenBtn->setPosition(bgNode->getContentSize().width-awakenBtn->getContentSize().width/2-30 ,24+awakenBtn->getContentSize().height/2);
        bgNode->addChild(awakenBtn,2,TAG_AWAKEN);
        
        Sprite* awakenLabel=Sprite::create(IMG_PUBLIC_LABEL_AWAKEN);
        awakenBtn->addChild(awakenLabel,2);
    }
    

}
void GeneralsAwake_Layer::onBtnClick(Ref* pSender)
{
    this->requestUpMsg();
}
//-----------------------------------------------访问服务器-------------------------------------------------------//
void GeneralsAwake_Layer::requestUpMsg()
{
    
    HeroAwakeUpMsg* msg = new HeroAwakeUpMsg(CardDataManager::getInstance()->getPresentData()->heroId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void GeneralsAwake_Layer::requestListMsg()
{
    HeroAwakeMsg* msg = new HeroAwakeMsg(CardDataManager::getInstance()->getPresentData()->heroId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void GeneralsAwake_Layer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_HERO_HeroWakeUpPageResp)
    {
        m_awakeData->canWakeUp=message->byteStream->getByte();
        m_awakeData->needStoneId=message->byteStream->getInt();
        m_awakeData->needStoneName=message->byteStream->getUTF8();
        m_awakeData->needStoneQuality=message->byteStream->getByte();
        m_awakeData->needStoneCount=message->byteStream->getByte();
        m_awakeData->ownStoneCount=message->byteStream->getInt();
        m_awakeData->needCoin=message->byteStream->getInt();
        this->createLayer();
    }else if (message->messageID ==SCENSE_CLIENT_HERO_HeroWakeUpResp)
    {
        this->broadMsg(CUSTOM_AWAKE_FUN);
    }
    
}
void GeneralsAwake_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroWakeUpPageResp).c_str(), CC_CALLBACK_1(GeneralsAwake_Layer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroWakeUpResp).c_str(), CC_CALLBACK_1(GeneralsAwake_Layer::onMsgProcess, this));
}
void GeneralsAwake_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}