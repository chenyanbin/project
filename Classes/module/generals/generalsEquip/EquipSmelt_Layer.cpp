//
//  EquipSmelt_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/9/7.
//
//

#include "EquipSmelt_Layer.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/generals/equip/EquipStrongMsg.h"
#include "../../../message/Decoding/generals/equip/EquipStartHardenMsg.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../common/commonEffect/CommonEffect.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../tdTalkData/TDTalkDataManager.hpp"
#include "../../../protocol/UserCustomEvent.h"
EquipSmelt_Layer::EquipSmelt_Layer()
:sx(1)
,_cardId(0)
,isOneKey(false)
,leftBg(NULL)
,rightBg(NULL)
,oneKeyCostCoin(0)//一键强化花费
,costCoin(0)//强化花费
,TAG_SMELT(1)
,TAG_RIGHTBG1(2)
,TAG_RIGHTBG(3)
,TAG_LEFTBG(4)
,TAG_ONEKEYCOSBTN(5)
,TAG_COSTBTN(6)
{
    equipData=new BaseEquipData();
    newEquipData=new BaseEquipData();
    equipData->autorelease();
    newEquipData->autorelease();
    CC_SAFE_RETAIN(equipData);
    CC_SAFE_RETAIN(newEquipData);
}
EquipSmelt_Layer::~EquipSmelt_Layer()
{
    CC_SAFE_RELEASE_NULL(equipData);
    CC_SAFE_RELEASE_NULL(newEquipData);
}

void EquipSmelt_Layer::onExit()
{
    BaseLayer::onExit();
}
void EquipSmelt_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void EquipSmelt_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumSoonStrengThenTheButton);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumStrengthenTheButton);
}
void EquipSmelt_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestListMsg();
}
bool EquipSmelt_Layer::init(int cardId)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        
        this->setBackground(IMG_GENERALS_SMELT_BG);
        bref = true;
    } while (false);
    return bref;
}
EquipSmelt_Layer* EquipSmelt_Layer::create(int cardId)
{
    EquipSmelt_Layer* layer = new EquipSmelt_Layer();
    if(layer && layer->init(cardId))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void EquipSmelt_Layer::leftLayer()
{
    if (leftBg) {
        return;
    }
    leftBg=(Sprite*)this->getChildByTag(TAG_BG);
    
    Sprite* smeltBgbox=Sprite::create(IMG_GENERALS_EQUIP_PROGRESSBGBOX);
    smeltBgbox->setAnchorPoint(Point::ZERO);
    smeltBgbox->setPosition(Point::ZERO);
    leftBg->addChild(smeltBgbox,1);

    const char* path =PublicShowUI::getGoods(DictItemTypeEnumItemEquip, equipData->equipDictId);
    Sprite* userOldEquip = Sprite::create(path);
    userOldEquip->setAnchorPoint(Point::ZERO);
    userOldEquip->setPosition((leftBg->getContentSize().width/sx-userOldEquip->getContentSize().width)/2-5,(leftBg->getContentSize().height/sx-userOldEquip->getContentSize().height)/2+20);
    leftBg->addChild(userOldEquip,2);
    
    string nameStr=equipData->equipName;
    Label* nameLabel=PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),17,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition((leftBg->getContentSize().width/sx-nameLabel->getContentSize().width)/2,475);
    leftBg->addChild(nameLabel,2);
    
    CommonEffect* effect = CommonEffect::create("xinqianghua",true,true);
    effect->setPosition((leftBg->getContentSize().width/sx-effect->getContentSize().width)/2+10,(leftBg->getContentSize().height/sx-effect->getContentSize().height)/2-100);
    leftBg->addChild(effect,2);
    
    
    
}
void EquipSmelt_Layer::rightLayer()
{
    BaseEquipData* data =equipData;
    
    Sprite* bgSprite=(Sprite*)this->getChildByTag(TAG_RIGHTBG1);
    if (!bgSprite) {
        bgSprite=Sprite::create(IMG_GENERALS_BG);
        bgSprite->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(bgSprite);
        bgSprite->setPosition(426*sx,0);
        bgSprite->setTag(TAG_RIGHTBG1);
        this->addChild(bgSprite);
    }
    Node* bg2=(Node*)bgSprite->getChildByTag(TAG_RIGHTBG);
    if (bg2) {
        bgSprite->removeChildByTag(TAG_RIGHTBG);
    }
    bg2=Node::create();
    bg2->setAnchorPoint(Point::ZERO);
    bg2->setContentSize(bgSprite->getContentSize()/sx);
    bgSprite->addChild(bg2,1,TAG_RIGHTBG);
    
    if(!data)
    {
        return;
    }
    Sprite* resultBg=Sprite::create(IMG_GENERALS_STRONG_RESULT);
    resultBg->setAnchorPoint(Point::ZERO);
    resultBg->setPosition(-4,bg2->getContentSize().height-resultBg->getContentSize().height-8);
    bg2->addChild(resultBg);
    
    UserEquipLayer* userHead=UserEquipLayer::create(data->resource,data->quality);
    userHead->setAnchorPoint(Point::ZERO);
    userHead->setPosition((bg2->getContentSize().width-userHead->getContentSize().width)/2,resultBg->getPositionY()-userHead->getContentSize().height-18);
    bg2->addChild(userHead,1);
    
    string nameStr=data->equipName +"    lv:"+PublicShowUI::numberToString(data->equipLevel);
    Label* nameLv = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),20,false,false);
    nameLv->setAnchorPoint(Point::ZERO);
    nameLv->setPosition((bg2->getContentSize().width-nameLv->getContentSize().width)/2,userHead->getPositionY()-nameLv->getContentSize().height-10);
    bg2->addChild(nameLv);
    
    Sprite* lineSprite=Sprite::create(IMG_GENERALS_SKILL_CONT_LINE);
    lineSprite->setAnchorPoint(Point::ZERO);
    lineSprite->setPosition(26, nameLv->getPositionY()-lineSprite->getContentSize().height-10);
    bg2->addChild(lineSprite);
    
    
    string str="当前属性";
    Label* currentLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),20,false,false);
    currentLabel->setAnchorPoint(Point::ZERO);
    currentLabel->setPosition(40,lineSprite->getPositionY()-currentLabel->getContentSize().height-10);
    bg2->addChild(currentLabel);
    
    str="提升属性";
    Label* upLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0xff8d4d),20,false,false);
    upLabel->setAnchorPoint(Point::ZERO);
    upLabel->setPosition(currentLabel->getContentSize().width+currentLabel->getPositionX()+80,currentLabel->getPositionY());
    bg2->addChild(upLabel);
    
    int size=(int)data->propertyList.size();
    for (int i=0; i<size; i++) {
        int num= data->propertyList.at(i).propertyType;
        string str=PublicShowUI::getEquipProerty(num);
        
        string proStr=PublicShowUI::numberToString(data->propertyList.at(i).propertyNum);
        Label* propertyLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),20,false,false);
        propertyLabel->setAnchorPoint(Point::ZERO);
        propertyLabel->setPosition(28,currentLabel->getPositionY()-(i+1)*(propertyLabel->getContentSize().height+15));
        bg2->addChild(propertyLabel);
        
        Label* propertyLabel2 = PublicShowUI::getLabel(proStr.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),20,false,false);
        propertyLabel2->setAnchorPoint(Point::ZERO);
        propertyLabel2->setPosition(propertyLabel->getPositionX()+propertyLabel->getContentSize().width+10 ,propertyLabel->getPositionY());
        bg2->addChild(propertyLabel2);
        
        Sprite* arrow=Sprite::create(IMG_GENERALS_EXPERIENCE_ARROW);
        arrow->setAnchorPoint(Point::ZERO);
        arrow->setPosition((bg2->getContentSize().width-arrow->getContentSize().width)/2,propertyLabel2->getPositionY()+(propertyLabel2->getContentSize().height-arrow->getContentSize().height)/2);
        bg2->addChild(arrow);
        
        //        str
        Label* upLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0xff8d4d),20,false,false);
        upLabel->setAnchorPoint(Point::ZERO);
        upLabel->setPosition(arrow->getContentSize().width+arrow->getPositionX()+10,propertyLabel->getPositionY());
        bg2->addChild(upLabel);
        
        int propertyNum=0;
        if (newEquipData->propertyList.size()!=0) {
            propertyNum=newEquipData->propertyList.at(i).propertyNum;
        }
        string proStr2="+ "+PublicShowUI::numberToString(propertyNum);
        Label* propertyLabel3 = PublicShowUI::getLabel(proStr2.c_str(),PublicShowUI::getColor3b(0xff8d4d),20,false,false);
        propertyLabel3->setAnchorPoint(Point::ZERO);
        propertyLabel3->setPosition(upLabel->getPositionX()+upLabel->getContentSize().width+5,upLabel->getPositionY());
        propertyLabel3->setTag(i);
        bg2->addChild(propertyLabel3);
    }
    
    Sprite* line2Sprite=Sprite::create(IMG_GENERALS_SKILL_CONT_LINE);
    line2Sprite->setAnchorPoint(Point::ZERO);
    line2Sprite->setPosition(26, 110);
    bg2->addChild(line2Sprite);
    
    //消耗
    string num=PublicShowUI::numberToString(costCoin);
    Sprite* cooperNode = Sprite::create(IMG_ICON_PUBLIC_COIN);
    cooperNode->setAnchorPoint(Point::ZERO);
    cooperNode->setScale(0.7, 0.7);
    cooperNode->setContentSize(cooperNode->getContentSize()*0.7);
    cooperNode->setPosition(30,20);
    bg2->addChild(cooperNode,1);
    
    Label* cooperLabel = PublicShowUI::getLabel(num.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),17,false,false);
    cooperLabel->setAnchorPoint(Point::ZERO);
    cooperLabel->setPosition(10 +cooperNode->getContentSize().width+cooperNode->getPositionX(),(cooperNode->getContentSize().height-cooperLabel->getContentSize().height)/2+cooperNode->getPositionY());
    bg2->addChild(cooperLabel);
    
    //强化
    Button* equipmentBtn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE,"", CC_CALLBACK_1(EquipSmelt_Layer::onBtnClick, this));
    equipmentBtn->setAnchorPoint(Point(.5,.5));
    equipmentBtn->setPosition(30+equipmentBtn->getContentSize().width/2 ,30+equipmentBtn->getContentSize().height);
    bg2->addChild(equipmentBtn,10,TAG_COSTBTN);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumStrengthenTheButton, equipmentBtn);
    Sprite* equipmentLabel=Sprite::create(IMG_PUBLIC_LABEL_INTENSIFY);
    equipmentBtn->addChild(equipmentLabel,2);
    
    
    
    //一键强化
    Button* equipment2Btn = Button::create(IMG_PUBLIC_BUTTON_FOUR_ORANGE,"", CC_CALLBACK_1(EquipSmelt_Layer::onBtnClick, this));
    equipment2Btn->setAnchorPoint(Point(.5,.5));
    equipment2Btn->setPosition(bg2->getContentSize().width-equipment2Btn->getContentSize().width/2-30 ,30+equipment2Btn->getContentSize().height);
    bg2->addChild(equipment2Btn,10,TAG_ONEKEYCOSBTN);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumSoonStrengThenTheButton, equipment2Btn);
    Sprite* equipment2Label=Sprite::create(IMG_PUBLIC_LABEL_ONEKEYINTENSIFY);
    if (oneKeyCostCoin<=0) {
        equipment2Btn->setEnabled(false);
    }
    equipment2Btn->addChild(equipment2Label,2);
    
    int playLv=GlobalInfo::getInstance()->gameRole->level*2;
    if (data->equipLevel>=playLv) {
        equipmentBtn->setEnabled(false);
        equipment2Btn->setEnabled(false);
        broadMsg(CUSTOM_REFRESH_DOT,__Integer::create(DictFunctionEnumEquipHarden));
    }
    
    //消耗
    num=PublicShowUI::numberToString(oneKeyCostCoin);
    Sprite* oneKeyCostNode = Sprite::create(IMG_ICON_PUBLIC_COIN);
    oneKeyCostNode->setAnchorPoint(Point::ZERO);
    oneKeyCostNode->setScale(0.7, 0.7);
    oneKeyCostNode->setContentSize(oneKeyCostNode->getContentSize()*0.7);
    oneKeyCostNode->setPosition(equipment2Btn->getPositionX()-equipment2Btn->getContentSize().width/2,20);
    bg2->addChild(oneKeyCostNode,1);
    
    Label* oneKeyCostLabel = PublicShowUI::getLabel(num.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),17,false,false);
    oneKeyCostLabel->setAnchorPoint(Point::ZERO);
    oneKeyCostLabel->setPosition(10 +oneKeyCostNode->getContentSize().width+oneKeyCostNode->getPositionX(),(oneKeyCostNode->getContentSize().height-oneKeyCostLabel->getContentSize().height)/2+oneKeyCostNode->getPositionY());
    bg2->addChild(oneKeyCostLabel);
    

}

void EquipSmelt_Layer::onBtnClick(Ref* psender)
{
    Sprite* sp=(Sprite*)psender;
    int tag=sp->getTag();
    if (tag==TAG_ONEKEYCOSBTN) {
        isOneKey=true;
    }else if (tag==TAG_COSTBTN)
    {
        isOneKey=false;
    }
    this->equipStartHardenMsg();
    DictNewGuide* newGuide = NewPlayerGuild::getInstance()->getNowData();
    if(newGuide)
    {
        if(newGuide->bottomId == DictNewGuideEventEnumStrengthenTheButton  || newGuide->bottomId == DictNewGuideEventEnumSoonStrengThenTheButton)
        {
              NewPlayerGuild::getInstance()->next();
        }
    }
  
}
void EquipSmelt_Layer::requestListMsg()
{
    if(EquipDataManager::getInstance()->getPresentData())
    {
        int _equipId=EquipDataManager::getInstance()->getPresentData()->equipId;
        EquipStrongMsg* msg = new EquipStrongMsg(_equipId);
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg = NULL;
    }
    
}
void EquipSmelt_Layer::equipStartHardenMsg()
{
    int _equipId=EquipDataManager::getInstance()->getPresentData()->equipId;
    EquipStartHardenMsg* msg = new EquipStartHardenMsg(_equipId,isOneKey);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
    
}
void EquipSmelt_Layer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
  
    if(message->messageID == SCENSE_CLIENT_EQUIP_EquipHardenPageResp)
    {
        if (message->state==false) {
            return;
        }
        equipData->propertyList.clear();
        newEquipData->propertyList.clear();
        equipData->equipId=message->byteStream->getInt();
        equipData->equipDictId=message->byteStream->getInt();
        equipData->quality=message->byteStream->getByte();
        equipData->equipLevel=message->byteStream->getInt();
        equipData->equipMaxLevel=message->byteStream->getInt();
        equipData->finalLevel=message->byteStream->getInt();
        equipData->equipName=message->byteStream->getUTF8();
        equipData->resource=message->byteStream->getUTF8();
        costCoin=message->byteStream->getInt();
        oneKeyCostCoin=message->byteStream->getInt();
        int _size=message->byteStream->getByte();
        for (int i=0; i<_size; i++) {
            struct BaseEquipProperty propertyData = {0,0};
            propertyData.propertyType=message->byteStream->getByte();
            propertyData.propertyNum=message->byteStream->getInt();
            equipData->propertyList.push_back(propertyData);
        }
        _size=message->byteStream->getByte();
        for (int i=0; i<_size; i++) {
            struct BaseEquipProperty propertyData = {0,0};
            propertyData.propertyType=message->byteStream->getByte();
            propertyData.propertyNum=message->byteStream->getInt();
            newEquipData->propertyList.push_back(propertyData);
        }
        this->leftLayer();
        this->rightLayer();
       
        EquipDataManager::getInstance()->setPresentData(equipData);
        NewPlayerGuild::getInstance()->showNowGuide();
    }else if (message->messageID ==SCENSE_CLIENT_EQUIP_EquipStartHardenResp)
    {
        
        if (message->state==false) {
            NoticeManager::getInstance()->showNotice("强化失败");
            return;
        }
        CommonEffect* effect2 = CommonEffect::create("xinqianghuabiankuang",false,true);
        effect2->setPosition((leftBg->getContentSize().width/sx-effect2->getContentSize().width)/2+5,(leftBg->getContentSize().height/sx-effect2->getContentSize().height)/2+27);
        leftBg->addChild(effect2,2);
        this->showEquipLvUpSound();
        this->requestListMsg();
//        broadMsg(CUSTOM_REFRESH_DOT,__Integer::create(DictFunctionEnumEquipHarden));
    }
}
void EquipSmelt_Layer::showEquipLvUpSound()
{
    SoundManager::playEffectMusic(EFFECT_EQUIP_UP);
}
void EquipSmelt_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_EQUIP_EquipHardenPageResp).c_str(), CC_CALLBACK_1(EquipSmelt_Layer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_EQUIP_EquipStartHardenResp).c_str(), CC_CALLBACK_1(EquipSmelt_Layer::onMsgProcess, this));
}
void EquipSmelt_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
