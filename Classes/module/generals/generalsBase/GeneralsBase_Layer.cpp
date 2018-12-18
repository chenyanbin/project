//
//  GeneralsBase_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/7/29.
//
//

#include "GeneralsBase_Layer.h"
#include "ChooseEquip_Layer.h"
#include "../Generals_Layer.h"
#include "../../../common/TouchSprite/TouchSprite.h"

#include "../../../message/Decoding/generals/base/GeneralsBaseMsg.h"
#include "../../../message/Decoding/generals/base/HeroOneKeyPutOnMsg.h"
#include "../../../message/Decoding/generals/base/HeroWakeUpMsg.h"
#include "../../../message/Decoding/generals/base/HeroOneKeyStrongMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../../commonData/enum/DictEquipPartsEnum.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../commonData/dictData/DictItemEquip/DictItemEquipManager.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../commonData/dictData/DictHeroQualityUp/DictHeroQualityUpManager.h"
#include "../../../commonData/data/FunctionOpenManager.h"
#include "AwakeLayer.hpp"
#include "UpStarLayer.hpp"
#include "../../../common/GraySprite/GraySprite.h"
#include "../../dot/RefreshDot.h"
#include "../../publicLayer/Getpath_Layer.h"
#define EQUIP_SLOT1_ITEMID 160001
#define EQUIP_SLOT2_ITEMID 160002
#define EQUIP_SLOT3_ITEMID 160003
#define EQUIP_SLOT4_ITEMID 160004
#define EQUIP_SLOT5_ITEMID 160005
#define EQUIP_SLOT6_ITEMID 160006
GeneralsBase_Layer::GeneralsBase_Layer()
:TAG_EQUIPMENT(1)
,TAG_AWAKEN(2)
,TAG_STRONG(3)
,TAG_EQUIPS(10)
,TAG_AWAKELABEL(11)
,TAG_UPSTARLABEL(12)
,TAG_PLUSBTN(13)
,awakePt(NULL)
,upStarPt(NULL)
,_cardId(1)
,heroID(0)
,heroDictId(0)
,hasBaseEquip(0)
,oneKeyHardenCost(0)
,starUpBookId(0)
,starUpBookCount(0)
,starUpBookCountOwn(0)
,wakeUpItemId(0)
,wakeUpItemCount(0)
,wakeUpItemCountOwn(0)
,starStatus(0)
,quailtyStatus(0)
,lineupStatus(0)
,upStartBtn(NULL)
,awakeBtn(NULL)
{
//    karmaList=new vector<KarmaData*>();
    equipList=new vector<BaseEquipData*>();
}
GeneralsBase_Layer::~GeneralsBase_Layer()
{
//    karmaList->clear();
//    CC_SAFE_DELETE(karmaList);
    equipList->clear();
    CC_SAFE_DELETE(equipList);
}
void GeneralsBase_Layer::onExit()
{
    BaseLayer::onExit();
}
void GeneralsBase_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void GeneralsBase_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumEquipmentGrid1);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumButtonOnABbutton);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumHeroSoonStrengThenTheButton);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumAwakeningLabel);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumStarBag);
}
void GeneralsBase_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestMsg();
}
bool GeneralsBase_Layer::init(int cardId)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->setBackground(IMG_GENERALS_BG);
        _cardId=cardId;
        this->createLayer();
        setBottomBtn();
        bref = true;
    } while (false);
    return bref;
}
GeneralsBase_Layer* GeneralsBase_Layer::create(int cardId)
{
    GeneralsBase_Layer* layer = new GeneralsBase_Layer();
    if(layer && layer->init(cardId))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void GeneralsBase_Layer::createLayer()
{
    Sprite* bgSprite=(Sprite*) this->getChildByTag(TAG_BG);
    TouchSprite* equipSprite = NULL;
    for (int i=0; i<6; i++) {
        const char* path = PublicShowUI::getResImgPath(IMG_GENERALS_BASE_EQUIP, PublicShowUI::numberToString(i + 1).c_str());
        equipSprite = TouchSprite::createWithPic(path);
        equipSprite->isButtonMode = true;
        equipSprite->setAnchorPoint(Point::ZERO);
        equipSprite->setPosition(25+100*(i%3),395-100*floor(i/3));
        equipSprite->setTag(TAG_EQUIPS+i+10);
        bgSprite->addChild(equipSprite,1);
        if(!GuideButtonManager::getInstance()->getButton(DictNewGuideEventEnumEquipmentGrid1))
        {
            GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumEquipmentGrid1, equipSprite);
        }
      
    }
    
    //一键装备
    Button* equipmentBtn = Button::create(IMG_PUBLIC_BUTTON_FOUR_ORANGE,"", CC_CALLBACK_1(GeneralsBase_Layer::onBtnClick, this));
    equipmentBtn->setPosition(equipmentBtn->getContentSize().width/2+ 30 ,equipSprite->getPositionY() - equipmentBtn->getContentSize().height + 10);
    bgSprite->addChild(equipmentBtn,2,TAG_EQUIPMENT);
     GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumButtonOnABbutton, equipmentBtn);
    Sprite* equipmentLabel=Sprite::create(IMG_PUBLIC_LABEL_EQUIP);
    equipmentBtn->addChild(equipmentLabel,2);
    
    //一键强化
    Button* strongBtn = Button::create(IMG_PUBLIC_BUTTON_FOUR_RED,"", CC_CALLBACK_1(GeneralsBase_Layer::onBtnClick, this));
    strongBtn->setPosition(bgSprite->getContentSize().width/GlobalInfo::getInstance()->screenScaleX- strongBtn->getContentSize().width/2-30,equipmentBtn->getPositionY());
    bgSprite->addChild(strongBtn,2,TAG_STRONG);
    Sprite* strongLabel=Sprite::create(IMG_PUBLIC_LABEL_ONEKEYINTENSIFY);
    strongBtn->addChild(strongLabel,2);
    if (!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumEquipHarden))
        strongBtn->setEnabled(false);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumHeroSoonStrengThenTheButton, strongBtn);
}
void GeneralsBase_Layer::setBottomBtn()
{
    Sprite* bgSprite=(Sprite*) this->getChildByTag(TAG_BG);
    Sprite* twoBg = Sprite::create(IMG_GENERALS_BASE_TWOBG);
    twoBg->setAnchorPoint(Point::ZERO);
    twoBg->setPosition((bgSprite->getContentSize().width / GlobalInfo::getInstance()->screenScaleX - twoBg->getContentSize().width)/2, 35);
    bgSprite->addChild(twoBg,3);
    
    upStartBtn = Button::create(IMG_PUBLIC_BUTTON_TWO_SMALLORED, "", CC_CALLBACK_1(GeneralsBase_Layer::onUpStarBtnClick, this));
    Sprite* title = Sprite::create(IMG_GENERALS_UpStarLabel);
    upStartBtn->addChild(title,10);
    upStartBtn->setPosition(20 + upStartBtn->getContentSize().width/2, 45);
    twoBg->addChild(upStartBtn,1);
     GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumStarBag, upStartBtn);

    awakeBtn = Button::create(IMG_PUBLIC_BUTTON_TWO_SMALLORANGE, "", CC_CALLBACK_1(GeneralsBase_Layer::onAwakeBtnClick, this));
    title = Sprite::create(IMG_GENERALS_AWAKELABEL);
    awakeBtn->addChild(title,10);
    awakeBtn->setPosition(upStartBtn->getPositionX(), upStartBtn->getPositionY() + 70);
    twoBg->addChild(awakeBtn,1);
    
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumAwakeningLabel, awakeBtn);
    
    Sprite* progressBg = Sprite::create(IMG_GENERALS_CARD_PROGRESSBG);
    progressBg->setAnchorPoint(Point::ZERO);
    Sprite* spr = Sprite::create(IMG_GENERALS_CARD_PROGRESS);
    spr->setAnchorPoint(Point::ZERO);
    awakePt = ProgressTimer::create(spr);
    awakePt->setType(ProgressTimer::Type::BAR);
    awakePt->setMidpoint(Point(0,1));
    awakePt->setBarChangeRate(Point(1,0));
    awakePt->setAnchorPoint(Point(0 ,0));
    awakePt->setPosition(0,0);
    progressBg->addChild(awakePt);
    awakePt->setPercentage(0);
    progressBg->setPosition(awakeBtn->getPositionX() + awakeBtn->getContentSize().width / 2 + 10, awakeBtn->getPositionY() - awakeBtn->getContentSize().height/2);
    twoBg->addChild(progressBg,2);
    
    progressBg = Sprite::create(IMG_GENERALS_CARD_PROGRESSBG);
    progressBg->setAnchorPoint(Point::ZERO);
    spr = Sprite::create(IMG_GENERALS_CARD_PROGRESSYELLOW);
    spr->setAnchorPoint(Point::ZERO);
    upStarPt = ProgressTimer::create(spr);
    upStarPt->setType(ProgressTimer::Type::BAR);
    upStarPt->setMidpoint(Point(0,1));
    upStarPt->setBarChangeRate(Point(1,0));
    upStarPt->setAnchorPoint(Point(0 ,0));
    upStarPt->setPosition(0,0);
    progressBg->addChild(upStarPt);
    upStarPt->setPercentage(0);
    progressBg->setPosition(upStartBtn->getPositionX() + upStartBtn->getContentSize().width / 2 + 10, upStartBtn->getPositionY() - upStartBtn->getContentSize().height/2);
    twoBg->addChild(progressBg,2);
    
    updateAwakeProgress();
    updateUpStarProgress();
}
void GeneralsBase_Layer::onAwakeBtnClick(Ref* pSender)
{

    if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumHeroQuality))
    {
        FunctionOpenManager::getInstance()->showNoOpenNotice(DictFunctionEnumHeroQuality);
        return;
    }
    AwakeLayer::show(this->heroID, this->heroDictId);
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumAwakeningLabel);
}
void GeneralsBase_Layer::onUpStarBtnClick(Ref* pSender)
{
    if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumHeroStar))
    {
        FunctionOpenManager::getInstance()->showNoOpenNotice(DictFunctionEnumHeroStar);
        return;
    }
    UpStarLayer::show(this->heroID, this->heroDictId);
}
void GeneralsBase_Layer::updateAwakeProgress()
{
    if(awakePt)
    {
        
        string itemName = "";//PublicShowUI::getName(DictItemTypeEnumItem, wakeUpItemId);
        string str = PublicShowUI::numberToString((int)wakeUpItemCountOwn) + "/" + PublicShowUI::numberToString((int)wakeUpItemCount) + itemName;// //"50/50材料";
        Label* label = (Label*)awakePt->getChildByTag(TAG_AWAKELABEL);
        if(label)
        {
            label->setString(str);
        }
        else
        {
            label = PublicShowUI::getLabel(str.c_str(),Color3B::WHITE,18,false,false);
            label->setAnchorPoint(Point::ZERO);
            
            awakePt->addChild(label,2,TAG_AWAKELABEL);
        }
        label->setPosition((awakePt->getContentSize().width - label->getContentSize().width)/2,( awakePt->getContentSize().height - label->getContentSize().height)/2);
        awakePt->stopAllActions();
        float percent = wakeUpItemCountOwn > wakeUpItemCount ? 100 : wakeUpItemCountOwn / wakeUpItemCount * 100;
        awakePt->runAction(ProgressFromTo::create(.3, awakePt->getPercentage(),percent ));
    }
    
}
void GeneralsBase_Layer::updateUpStarProgress()
{

    if(upStarPt)
    {
        
        string bookName = "";//PublicShowUI::getName(DictItemTypeEnumItemBook,this->starUpBookId);
        string str = PublicShowUI::numberToString((int)this->starUpBookCountOwn) + "/" + PublicShowUI::numberToString((int)this->starUpBookCount) + bookName;
        Label* label = (Label*)upStarPt->getChildByTag(TAG_UPSTARLABEL);
        if(label)
        {
            label->setString(str);
        }
        else
        {
            label = PublicShowUI::getLabel(str.c_str(),Color3B::WHITE,18,false,false);
            label->setAnchorPoint(Point::ZERO);
          
            upStarPt->addChild(label,2,TAG_UPSTARLABEL);
        }
        label->setPosition((upStarPt->getContentSize().width - label->getContentSize().width)/2, (upStarPt->getContentSize().height - label->getContentSize().height)/2);
        upStarPt->stopAllActions();
        float percent = starUpBookCountOwn > starUpBookCount ? 100 : starUpBookCountOwn / starUpBookCount * 100;
        upStarPt->runAction(ProgressFromTo::create(.3, upStarPt->getPercentage(), percent));
        
    }
}
void GeneralsBase_Layer::onPlusClick(Node* psender)
{
    int tag=psender->getTag();
    if (tag>19) {
        tag-=10;
    }
    int eqipID = 0;
    switch (tag) {
        case 10://武器
            eqipID=EQUIP_SLOT1_ITEMID;
            break;
        case 11://头盔
            eqipID=EQUIP_SLOT2_ITEMID;
            break;
        case 12://腰带
            eqipID=EQUIP_SLOT3_ITEMID;
            break;
        case 13://衣服
            eqipID=EQUIP_SLOT4_ITEMID;
            break;
        case 14://项链
            eqipID= EQUIP_SLOT5_ITEMID;
            break;
        case 15://玉佩
            eqipID= EQUIP_SLOT6_ITEMID;
            break;
        default:
            break;
    }
    
    Getpath_Layer::show(SCENE_TAG_GENERALS_STRONG,DictItemTypeEnumItemEquip,eqipID,1);

}
void GeneralsBase_Layer::onItemClick(Node* pSender)
{
    onPlusClick(pSender->getParent());
//    int tag=pSender->getParent()->getTag();
//    if (tag>19) {
//        tag-=10;
//    }
//    int eqipID = 0;
//    switch (tag) {
//        case 10://武器
//            eqipID=EQUIP_SLOT1_ITEMID;
//            break;
//        case 11://头盔
//            eqipID=EQUIP_SLOT2_ITEMID;
//            break;
//        case 12://腰带
//            eqipID=EQUIP_SLOT3_ITEMID;
//            break;
//        case 13://衣服
//            eqipID=EQUIP_SLOT4_ITEMID;
//            break;
//        case 14://项链
//            eqipID= EQUIP_SLOT5_ITEMID;
//            break;
//        case 15://玉佩
//            eqipID= EQUIP_SLOT6_ITEMID;
//            break;
//        default:
//            break;
//    }
//
//      Getpath_Layer::show(SCENE_TAG_GENERALS_STRONG,DictItemTypeEnumItemEquip,eqipID,1);
}
void GeneralsBase_Layer::updateEquip()
{
    Sprite* bgSprite=(Sprite*) this->getChildByTag(TAG_BG);
    if (!bgSprite) {
        return;
    }
    Button* onKeyBtn=(Button*)bgSprite->getChildByTag(TAG_EQUIPMENT);
    if (onKeyBtn and !hasBaseEquip) {
        onKeyBtn->setEnabled(false);
    }
    Button* strongBtn=(Button*)bgSprite->getChildByTag(TAG_STRONG);
    bool openBol=!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumEquipHarden);
    if (!oneKeyHardenCost and strongBtn and openBol) {
        strongBtn->setEnabled(false);
    }
    Point cp;
    Size size ;
    bool isNewEquip = false;
    for (int i=0; i<6; i++) {
        //删除已装备的
        isNewEquip  = true;
        Sprite* equipSp=(Sprite*)bgSprite->getChildByTag(TAG_EQUIPS+i);
        if (equipSp) {
          
            isNewEquip = false;
            bgSprite->removeChildByTag(TAG_EQUIPS+i);
        }
        //添加事件
        TouchSprite* equipSprite=(TouchSprite*)bgSprite->getChildByTag(TAG_EQUIPS+i+10);
        cp = equipSprite->getPosition();
        size = equipSprite->getContentSize();
        if(i >= equipList->size())
        {
            return;
        }
        BaseEquipData* equip=equipList->at(i);
        if (!equip) {
            return;
        }
        Node* plus = equipSprite->getChildByTag(TAG_PLUSBTN);
        if(plus)
        {
            plus->stopAllActions();
            plus->removeFromParent();
        }
        
        if (equip->equipId==0 )
        {
            if (equip->status==2 )
            {
                //"可装备";
                equipSprite->addTouchBegainCallBack(this, callfuncN_selector(GeneralsBase_Layer::onButtonClick));
                if (lineupStatus == 1) {
                    PublicShowUI::setDot(equipSprite, Point::ZERO, false,DictFunctionEnumHeroEquip);
                }
            }
            else if (equip->status==3 )
            {
                //"可合成";
                equipSprite->addTouchBegainCallBack(this, callfuncN_selector(GeneralsBase_Layer::onButtonMaterialClick));
            }
            else if (equip->status==4)
            {
                //"无装备";
//                int tag = equipSprite->getTag();
//                equipSprite->removeFromParent();
//                const char* path = PublicShowUI::getResImgPath(IMG_GENERALS_BASE_EQUIP, PublicShowUI::numberToString(i + 1).c_str());
//                equipSprite = (TouchSprite*)GraySprite::create(path);
//                equipSprite->setAnchorPoint(Point::ZERO);
//                equipSprite->setPosition(cp);
//                bgSprite->addChild(equipSprite,i,tag);
//                
                equipSprite->addTouchBegainCallBack(this, callfuncN_selector(GeneralsBase_Layer::onPlusClick));
                Sprite* plus = Sprite::create(IMG_GENERALS_EQUIPPLUS);
                plus->setScale(.8);
                plus->setPosition(equipSprite->getContentSize().width - 15, 15);
                equipSprite->addChild(plus,1,TAG_PLUSBTN);
                
                FadeIn* fadeIn = FadeIn::create(.5);
                FadeOut* fadeOut = FadeOut::create(.5);
                RepeatForever* action = RepeatForever::create(Sequence::create(fadeIn,fadeOut, NULL));
                plus->runAction(action);
            }

            continue;
        }
        DictItemEquip* equipData=DictItemEquipManager::getInstance()->getData(equip->equipDictId);
        if (!equip || !equipData) {
            return;
        }
        if (equipData) {
            
            if(equipSprite)
            {
                
//                equipSprite->setTouchEnabled();
            }
            string resource=equipData->resource.c_str();
            UserEquipLayer* userEquip=UserEquipLayer::create(resource,equip->quality);
            userEquip->addTouchBegainCallBack(this, callfuncN_selector(GeneralsBase_Layer::onButtonClick));
            userEquip->setAnchorPoint(Point::ZERO);
            userEquip->setScale(size.width / userEquip->getContentSize().width);
            userEquip->setPosition(cp);
            bgSprite->addChild(userEquip,1,TAG_EQUIPS+i);
            
            Sprite* rankBg=Sprite::create(IMG_GENERALS_EQUIP_RANKBG);
            rankBg->setAnchorPoint(Point::ZERO);
            rankBg->setPosition(userEquip->getContentSize().width-rankBg->getContentSize().width-2,userEquip->getContentSize().height-rankBg->getContentSize().height-3);
            userEquip->addChild(rankBg,2);
            
            string rankStr=PublicShowUI::numberToString(equip->equipLevel);
            string maxRankStr= "";// "/" + PublicShowUI::numberToString(equip->equipMaxLevel);
            Sprite* rankSprite =PublicShowUI::getAttribLabel(rankStr.c_str(), maxRankStr.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),false,14,12,false);
            
            rankSprite->setAnchorPoint(Point::ZERO);
            rankSprite->setPosition((rankBg->getContentSize().width-rankSprite->getContentSize().width)/2,(rankBg->getContentSize().height-rankSprite->getContentSize().height)/2);
            rankBg->addChild(rankSprite);
            
            if(isNewEquip)
            {
                CommonEffect* effect = CommonEffect::create("zhuangbeichuandaikuang");
                effect->setAnchorPoint(Point::ZERO);
                effect->setPosition((userEquip->getContentSize().width - effect->getContentSize().width)/2, (userEquip->getContentSize().height - effect->getContentSize().height)/2);
                userEquip->addChild(effect,10);
            }
        }
    }

}
void GeneralsBase_Layer::onBtnClick(Ref* pSender)
{
    Node* node=(Node*)pSender;
    int tag=node->getTag();
    if (tag==TAG_EQUIPMENT) {
        this->oneKeyPutOnMsg();
    }else if (tag==TAG_AWAKEN)
    {
        this->wakeUpMsg();
        
    }else if (tag==TAG_STRONG)
    {
        this->oneKeyStrongMsg();
    }
    NewPlayerGuild::getInstance()->next();
}

void GeneralsBase_Layer::onButtonClick(Node* pSender)
{
    int tag=pSender->getTag();
    if (tag>19) {
        tag-=10;
    }
    int quipSlot=0;
    switch (tag) {
        case 10://武器
            quipSlot=DictEquipPartsEnumEquipSlot1EquipID;
            break;
        case 11://头盔
            quipSlot=DictEquipPartsEnumEquipSlot2EquipID;
            break;
        case 12://腰带
            quipSlot=DictEquipPartsEnumEquipSlot3EquipID;
            break;
        case 13://衣服
            quipSlot=DictEquipPartsEnumEquipSlot4EquipID;
            break;
        case 14://项链
            quipSlot=DictEquipPartsEnumEquipSlot5EquipID;
            break;
        case 15://玉佩
            quipSlot=DictEquipPartsEnumEquipSlot6EquipID;
            break;
        default:
            break;
    }
    NewPlayerGuild::getInstance()->next();
    ChooseEquip_Layer* layer=ChooseEquip_Layer::create(_cardId, quipSlot);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
    Scene* scene=Director::getInstance()->getRunningScene();
    scene->addChild(layer);
}
void GeneralsBase_Layer::onButtonMaterialClick(Node* pSender)
{
    Generals_Layer::show(SCENE_TAG_CHOOSEEQUIP,Generals_Layer::PAGE_TAG_MATERIAL,_cardId);
    
}
//-----------------------------------------------访问服务器-------------------------------------------------------//
void GeneralsBase_Layer::requestMsg()
{
    GeneralsBaseMsg* msg = new GeneralsBaseMsg(_cardId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void GeneralsBase_Layer::oneKeyPutOnMsg()
{
    HeroOneKeyPutOnMsg* msg = new HeroOneKeyPutOnMsg(_cardId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void GeneralsBase_Layer::wakeUpMsg()
{
    HeroWakeUpMsg* msg = new HeroWakeUpMsg(_cardId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void GeneralsBase_Layer::oneKeyStrongMsg()
{
    HeroOneKeyStrongMsg* msg = new HeroOneKeyStrongMsg(_cardId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void GeneralsBase_Layer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_HERO_HeroBasePageResp)
    {
        this->heroID = message->byteStream->getInt();
        heroDictId=message->byteStream->getInt();
        hasBaseEquip=message->byteStream->getByte();
        oneKeyHardenCost=message->byteStream->getInt();
        this->lineupStatus = message->byteStream->getByte();
        this->starStatus = message->byteStream->getByte();
        this->quailtyStatus = message->byteStream->getByte();
        log("oneKeyHardenCost=========================%d",oneKeyHardenCost);
        short equipNum=message->byteStream->getShort();
        equipList->clear();
//        karmaList->clear();
        for (int i=0; i<equipNum; i++)
        {
            BaseEquipData* data=new BaseEquipData();
            data->autorelease();
            data->equipId=message->byteStream->getInt();
            data->equipDictId=message->byteStream->getInt();
            
            data->quality=message->byteStream->getByte();
            data->equipLevel=message->byteStream->getInt();
            data->equipMaxLevel=message->byteStream->getInt();
            
            data->status = message->byteStream->get();
            data->canStrengthen= data->status == 1;
            data->canPutOn = data->status == 2;
            equipList->push_back(data);
        }
        this->starUpBookId = message->byteStream->getInt();
        this->starUpBookCount = message->byteStream->getShort();
        this->starUpBookCountOwn = message->byteStream->getShort();
        this->wakeUpItemId = message->byteStream->getInt();
        this->wakeUpItemCount = message->byteStream->getShort();
        this->wakeUpItemCountOwn = message->byteStream->getShort();

        this->updateUpStarProgress();
        this->updateAwakeProgress();
        this->updateEquip();
        
        if (starStatus == 1) {
            PublicShowUI::setDot(upStartBtn, Point(10,10), false,DictFunctionEnumHeroStar);
        }
        if (quailtyStatus == 1) {
            PublicShowUI::setDot(awakeBtn, Point(10,10), false,DictFunctionEnumHeroQuality);
        }
    }
    else if (message->messageID == SCENSE_CLIENT_HERO_HeroOneKeyPutOnResp)
    {
        this->broadMsg(CUSTOM_HEROPUTONEQUIP);
    }
    else if (message->messageID == SCENSE_CLIENT_HERO_HeroOneKeyHardenResp)
    {
        showEquipLvUpSound();
        int getInt = message->byteStream->getInt();
        log("getInt=========================%d",getInt);
        this->broadMsg(CUSTOM_HEROPUTONEQUIP);
    }

}
void GeneralsBase_Layer::onUpStarSuc(EventCustom* msg)
{
    requestMsg();
    broadMsg(CUSTOM_START_FUN);
    
//    __Integer* inter = (__Integer*)msg->getUserData();
//    if (inter) {
//        int tag_index = inter->getValue();
//        if (tag_index == DictFunctionEnumHeroQuality)
//        {
//            RefreshDot::getInstance()->requestMsg(awakeBtn,Point::ZERO,false,DictFunctionEnumHeroQuality);
//        }
//        else if (tag_index == DictFunctionEnumHeroStar)
//        {
//            RefreshDot::getInstance()->requestMsg(upStartBtn,Point::ZERO,false,DictFunctionEnumHeroStar);
//        }
//    }
}
void GeneralsBase_Layer::showEquipLvUpSound()
{
    SoundManager::playEffectMusic(EFFECT_EQUIP_UP);
}
void GeneralsBase_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroBasePageResp).c_str(), CC_CALLBACK_1(GeneralsBase_Layer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroOneKeyPutOnResp).c_str(), CC_CALLBACK_1(GeneralsBase_Layer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroOneKeyHardenResp).c_str(), CC_CALLBACK_1(GeneralsBase_Layer::onMsgProcess, this));
    this->addUserMsg(CUSTOM_UPDATE_HEROBASEPAGEMSG, CC_CALLBACK_1(GeneralsBase_Layer::onUpStarSuc, this));
    this->addUserMsg(CUSTOM_UPDATE_EQUIP, CC_CALLBACK_0(GeneralsBase_Layer::requestMsg, this));
}
void GeneralsBase_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}