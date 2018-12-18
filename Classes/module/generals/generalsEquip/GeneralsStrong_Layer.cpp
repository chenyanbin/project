//
//  GeneralsStrong_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/25.
//
//

#include "GeneralsStrong_Layer.h"
#include "GeneralsEquipStrong_Layer.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../message/Decoding/generals/equip/EquipForgeMsg.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../message/Decoding/generals/equip/EquipStartForgeMsg.h"
#include "../data/EquipDataManager.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../commonData/dictData/DictEquipHardenCost/DictEquipHardenCostManager.h"
#include "../../../commonData/dictData/DictEquipForge/DictEquipForgeManager.h"
#include "../../../commonData/dictData/DictEquipHardenLevel/DictEquipHardenLevelManager.h"
#include "../../../commonData/dictData/DictEquipHardenFightProp/DictEquipHardenFightPropManager.h"
#include "../../../commonData/dictData/DictEquipForgeCost/DictEquipForgeCostManager.h"
#include "../../../message/Decoding/generals/equip/EquipStartHardenMsg.h"
#include "../../../message/Decoding/generals/equip/EquipListMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../commonData/enum/DictEquipPartsEnum.h"
#include "../../../commonData/enum/DictFightPropEnum.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../commonData/dictData/DictItemQuality/DictItemQualityManager.h"
GeneralsStrong_Layer::GeneralsStrong_Layer()
:sx(1)
,TAG_LISTBG(1)
,TAG_EQUIPMENT(3)
,TAG_AUTOBTN(4)
,TAG_CARDBG(6)
,TAG_EQUIPBG(7)
,TAG_EXPERENCE(8)
,TAG_EXPLABLE(100)
,TAG_RIGHTBG(100001)
,TAG_CURRENTLABEL(100003)
,TAG_PROPERTYLABEL(100004)//保留 4位数下面从100008开始
,TAG_RIGHTBG1(100009)
,TAG_EQUIPSTRONG(100010)
,cardId(1)
,maxQuality(0)
,equipList(NULL)
{
    
    oldEquipData=new BaseEquipData();
    newEquipData=new BaseEquipData();
    oldEquipData->autorelease();
    newEquipData->autorelease();
    CC_SAFE_RETAIN(oldEquipData);
    CC_SAFE_RETAIN(newEquipData);
    
    
    
}
GeneralsStrong_Layer::~GeneralsStrong_Layer()
{
    Vector<BaseEquipData*>* chooseList =EquipDataManager::getInstance()->getDataList();
    for (BaseEquipData* data:*chooseList) {
        data->cardLocation=0;
    }
    EquipDataManager::getInstance()->clearCardList();
    CC_SAFE_DELETE(equipList);
    CC_SAFE_RELEASE_NULL(oldEquipData);
    CC_SAFE_RELEASE_NULL(newEquipData);
    
}

void GeneralsStrong_Layer::onExit()
{
    BaseLayer::onExit();
}
void GeneralsStrong_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void GeneralsStrong_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumMeltingAutomaticAdding);
}
void GeneralsStrong_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestListMsg();
}
bool sortOnStrongQualityDescend(BaseEquipData* n1, BaseEquipData* n2)//倒序(从小到大)
{
    return n1->quality < n2->quality;
}
bool GeneralsStrong_Layer::init(int cardId)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        Sprite*bg=Sprite::create(IMG_GENERALS_BG);
        PublicShowUI::setTargetScale(bg);
        this->setContentSize(bg->getContentSize());
        
        this->isAbleGuiding =true;
        bref = true;
    } while (false);
    return bref;
}
GeneralsStrong_Layer* GeneralsStrong_Layer::create(int cardId)
{
    GeneralsStrong_Layer* layer = new GeneralsStrong_Layer();
    if(layer && layer->init(cardId))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
//-------------------------------------------------------------右layer部分--------------------------------------------------------------------//
void GeneralsStrong_Layer::rightLayer()
{
    BaseEquipData* data =EquipDataManager::getInstance()->getPresentData();

    Sprite* bg2=(Sprite*)this->getChildByTag(TAG_RIGHTBG);
    if (bg2) {
        this->removeChildByTag(TAG_RIGHTBG);
    }
    bg2=Sprite::create(IMG_GENERALS_BG);
    bg2->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bg2);
    bg2->setPosition(426*sx, 0);
    bg2->setTag(TAG_RIGHTBG);
    this->addChild(bg2,2);
    
    this->setContentSize(bg2->getContentSize());
                         
    if(!data)
    {
        return;
    }
    Sprite* resultBg=Sprite::create(IMG_GENERALS_SMELT_RESULT);
    resultBg->setAnchorPoint(Point::ZERO);
    resultBg->setPosition(-4,bg2->getContentSize().height/sx-resultBg->getContentSize().height-8);
    bg2->addChild(resultBg);
    
    UserEquipLayer* userHead=UserEquipLayer::create(newEquipData->resource,newEquipData->quality);
    userHead->setAnchorPoint(Point::ZERO);
    userHead->setPosition((bg2->getContentSize().width/sx-userHead->getContentSize().width)/2,resultBg->getPositionY()-userHead->getContentSize().height-18);
    bg2->addChild(userHead,1);
    
    string nameStr=data->equipName +"    lv:"+PublicShowUI::numberToString(data->equipLevel);
    Label* nameLv = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),20,false,false);
    nameLv->setAnchorPoint(Point::ZERO);
    nameLv->setPosition((bg2->getContentSize().width/sx-nameLv->getContentSize().width)/2,userHead->getPositionY()-nameLv->getContentSize().height-10);
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
        propertyLabel2->setTag(TAG_PROPERTYLABEL+i);
        propertyLabel2->setPosition(propertyLabel->getPositionX()+propertyLabel->getContentSize().width+10 ,propertyLabel->getPositionY());
        bg2->addChild(propertyLabel2);
        
        Sprite* arrow=Sprite::create(IMG_GENERALS_EXPERIENCE_ARROW);
        arrow->setAnchorPoint(Point::ZERO);
        arrow->setPosition((bg2->getContentSize().width/sx-arrow->getContentSize().width)/2,propertyLabel2->getPositionY()+(propertyLabel2->getContentSize().height-arrow->getContentSize().height)/2);
        bg2->addChild(arrow);
        
//        str
        Label* upLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0xff8d4d),20,false,false);
        upLabel->setAnchorPoint(Point::ZERO);
        upLabel->setPosition(arrow->getContentSize().width+arrow->getPositionX()+10,propertyLabel->getPositionY());
        bg2->addChild(upLabel);
        
        int proNum=updataProperyt(data->equipDictId,data->quality,num,data->equipLevel);
        string proStr2="+ "+PublicShowUI::numberToString(proNum);
        Label* propertyLabel3 = PublicShowUI::getLabel(proStr2.c_str(),PublicShowUI::getColor3b(0xff8d4d),20,false,false);
        propertyLabel3->setAnchorPoint(Point::ZERO);
        propertyLabel3->setPosition(upLabel->getPositionX()+upLabel->getContentSize().width+5,upLabel->getPositionY());
        propertyLabel3->setTag(i);
        bg2->addChild(propertyLabel3);
    }
    Sprite* lineSprite3=Sprite::create(IMG_GENERALS_SKILL_CONT_LINE);
    lineSprite3->setAnchorPoint(Point::ZERO);
    lineSprite3->setPosition(26, 100);
    bg2->addChild(lineSprite3);
    
    //消耗
    string num="0";
    Sprite* cooperNode = Sprite::create(IMG_ICON_PUBLIC_COIN);
    cooperNode->setAnchorPoint(Point::ZERO);
    cooperNode->setScale(0.7, 0.7);
    cooperNode->setContentSize(cooperNode->getContentSize()*0.7);
    cooperNode->setPosition(40,40);
    bg2->addChild(cooperNode,1);
    
    DictEquipForgeCost* cost=DictEquipForgeCostManager::getInstance()->getData(data->quality);
    if (cost) {
        num=PublicShowUI::numberToString(cost->consumeCoin);
    }
    Label*cooperLabel = PublicShowUI::getLabel(num.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),20,false,false);
    cooperLabel->setAnchorPoint(Point::ZERO);
    cooperLabel->setPosition(cooperNode->getContentSize().width+cooperNode->getPositionX()+20,(cooperNode->getContentSize().height-cooperLabel->getContentSize().height)/2+cooperNode->getPositionY());
    bg2->addChild(cooperLabel);
    
    //熔炼
    Button* equipmentBtn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE,"", CC_CALLBACK_1(GeneralsStrong_Layer::onBtnClick, this));
    equipmentBtn->setPosition((bg2->getContentSize().width/sx-equipmentBtn->getContentSize().width/2-40) ,35+equipmentBtn->getContentSize().height/2);
    equipmentBtn->setEnabled(false);
    bg2->addChild(equipmentBtn,10,TAG_EQUIPMENT);
  
    Sprite* equipmentLabel=Sprite::create(IMG_PUBLIC_LABEL_PRACTICE);
    equipmentBtn->addChild(equipmentLabel,2);
    
}
int GeneralsStrong_Layer::updataProperyt(int equipId,int quality,int propertyType,int lv)
{
    DictEquipHardenFightProp* propData=DictEquipHardenFightPropManager::getInstance()->getData(equipId);
    DictEquipForge* forgeData=DictEquipForgeManager::getInstance()->getData(equipId);
    if (!forgeData or !propData) {
        return 0;
    }
    DictEquipHardenFightProp* propData2=DictEquipHardenFightPropManager::getInstance()->getData(forgeData->forgeEquip);
    if (!propData2) {
        return 0;
    }
    int propNum=0;
    int tempNum=0;
    if (propData) {
        switch (propertyType) {
            case DictFightPropEnumHealth:
                propNum=propData->health;
                propNum+=propData->healthLevelUp*(lv-1);
                
                tempNum=propData2->health;
                tempNum+=propData2->healthLevelUp*(lv-1);
                
                propNum=tempNum-propNum;
                break;
            case DictFightPropEnumAttack:
                propNum=propData->attack;
                propNum+=propData->attackLevelUp*(lv-1);
                
                tempNum=propData2->attack;
                tempNum+=propData2->attackLevelUp*(lv-1);
                
                propNum=tempNum-propNum;
                break;
            case DictFightPropEnumDefend:
                propNum=propData->defend;
                propNum+=propData->defendLevelUp*(lv-1);
                
                tempNum=propData2->defend;
                tempNum+=propData2->defendLevelUp*(lv-1);
                
                propNum=tempNum-propNum;
                break;
            case DictFightPropEnumCritic:
                propNum=propData->critic;
                propNum+=propData->criticLevelUp*(lv-1);
                
                tempNum=propData2->critic;
                tempNum+=propData2->criticLevelUp*(lv-1);
                
                propNum=tempNum-propNum;
                break;
            case DictFightPropEnumTenaci:
                propNum=propData->tenaci;
                propNum+=propData->tenaciLevelUp*(lv-1);
                
                tempNum=propData2->tenaci;
                tempNum+=propData2->tenaciLevelUp*(lv-1);
                
                propNum=tempNum-propNum;
                break;
            case DictFightPropEnumHit:
                propNum=propData->hit;
                propNum+=propData->hitLevelUp*(lv-1);
                
                tempNum=propData2->hit;
                tempNum+=propData2->hitLevelUp*(lv-1);
                
                propNum=tempNum-propNum;
                break;
            case DictFightPropEnumBlock:
                propNum=propData->block;
                propNum+=propData->blockLevelUp*(lv-1);
                
                tempNum=propData2->block;
                tempNum+=propData2->blockLevelUp*(lv-1);
                
                propNum=tempNum-propNum;
                break;
            default:
                break;
        }

    }
    
    return propNum;

}
void GeneralsStrong_Layer::onBtnClick(Ref* pSender)
{
    Node* node=(Node*)pSender;
    int tag=node->getTag();
    if (tag==TAG_EQUIPMENT) {//熔炼
        this->equipStartSmeltMsg();
    }else if (tag==TAG_AUTOBTN)//自动添加
    {
        this->updateEquip();
        
    }
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumMeltingAutomaticAdding);
}
//-------------------------------------------------------------左layer部分--------------------------------------------------------------------//
void GeneralsStrong_Layer::leftLayer()
{
    Vector<DictItemQuality*>* list= DictItemQualityManager::getInstance()->getDataList();
    if (list) {
        maxQuality=(int)list->size();
    }
    if (this->getChildByTag(TAG_CARDBG)) {
        this->removeChildByTag(TAG_CARDBG);
    }
    Sprite* cardBg=Sprite::create(IMG_GENERALS_CARD_BG);
    PublicShowUI::setTargetScale(cardBg);
    cardBg->setAnchorPoint(Point::ZERO);
    cardBg->setPosition(Point::ZERO);
    this->addChild(cardBg,1,TAG_CARDBG);
    
    Sprite* cardBg2=Sprite::create(IMG_GENERALS_EQUIP_BG);
    cardBg2->setAnchorPoint(Point::ZERO);
    cardBg2->setPosition(-3, 0);
    cardBg->addChild(cardBg2,2,TAG_EQUIPBG);
    
    Sprite* cardBgbox=Sprite::create(IMG_GENERALS_EQUIP_PROGRESSBGBOX);
    cardBgbox->setAnchorPoint(Point::ZERO);
    cardBgbox->setPosition(-3, 0);
    cardBg->addChild(cardBgbox,2);
    int tempX=-245;
    int tempY=-38;
    BaseEquipData* equipData = EquipDataManager::getInstance()->getPresentData();
    if(equipData)
    {
        const char* path =PublicShowUI::getGoods(DictItemTypeEnumItemEquip, equipData->equipDictId);
        Sprite* equip = Sprite::create(path);
        
        equip->setAnchorPoint(Point::ZERO);
        equip->setPosition((cardBg2->getContentSize().width-equip->getContentSize().width)/2-5, (cardBg2->getContentSize().height-equip->getContentSize().height)/2+20);
        cardBg2->addChild(equip);
    }
    
    
    int equipX=0;
    int equipY=0;
    Vector<BaseEquipData*>* chooseList= EquipDataManager::getInstance()->getDataList();
    //判断是否可以熔炼了
    int equipSize=(int)chooseList->size();
    Sprite* bg2=(Sprite*)this->getChildByTag(TAG_RIGHTBG);
    if (bg2) {
        Button* btn=(Button*)bg2->getChildByTag(TAG_EQUIPMENT);
        if (equipSize==6 and btn and maxQuality>equipData->quality) {
            btn->setEnabled(true);
        }
    }
    for (int i=0; i<6; i++) {
        if (i==0) {
            equipX=414+tempX;
            equipY=417+tempY;
        }else if (i==1)
        {
            equipX=279+tempX;
            equipY=353+tempY;
        }else if (i==2)
        {
            equipX=557+tempX;
            equipY=353+tempY;
        }else if (i==3)
        {
            equipX=279+tempX;
            equipY=210+tempY;
        }else if (i==4)
        {
            equipX=557+tempX;
            equipY=210+tempY;
        }else if (i==5)
        {
            equipX=414+tempX;
            equipY=110+tempY;
        }
        if (chooseList->size()>i) {
            equipY-=10;
            equipX-=11;
            UserEquipLayer* userHead=UserEquipLayer::create(chooseList->at(i)->resource,chooseList->at(i)->quality);
            userHead->setScale(0.75);
            userHead->setPosition(equipX,equipY);
            
            userHead->addTouchBegainCallBack(this, callfuncN_selector(GeneralsStrong_Layer::onUserClick));
            cardBg2->addChild(userHead,1);
        }
        else
        {
            Button* equip=Button::create(IMG_PUBLIC_TABLEVIEW_EQUIP2,IMG_PUBLIC_TABLEVIEW_EQUIP2, CC_CALLBACK_1(GeneralsStrong_Layer::onEquipClick, this));
            equip->setAnchorPoint(Point::ZERO);
            equip->setPosition(equipX, equipY);
            cardBg2->addChild(equip,2);
        }
    }
    //自动添加
    Button* autoBtn = Button::create(IMG_PUBLIC_BUTTON_FOUR_ORANGE,"", CC_CALLBACK_1(GeneralsStrong_Layer::onBtnClick, this));
    autoBtn->setPosition(cardBg2->getContentSize().width/2,20+autoBtn->getContentSize().height/2);
    cardBg2->addChild(autoBtn,10,TAG_AUTOBTN);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumMeltingAutomaticAdding, autoBtn);
    Sprite* autoLabel=Sprite::create(IMG_PUBLIC_LABEL_AUTOADD);
    autoBtn->addChild(autoLabel,2);
    
    CC_SAFE_DELETE(list);
    list = NULL;
}

void GeneralsStrong_Layer::onEquipClick(Ref* pSender)
{
    this->tableLayer();
}
void GeneralsStrong_Layer::onUserClick(Node* pSender)
{
    this->tableLayer();
}
//--------------------------------列表部分-------------------------------------------------------//
void GeneralsStrong_Layer::tableLayer()
{
    GeneralsEquipStrong_Layer* _layer=GeneralsEquipStrong_Layer::create(1);
    _layer->setPosition(VisibleRect::center().x -_layer->getContentSize().width/2,VisibleRect::center().y-_layer->getContentSize().height/2);
    Scene* scene = Director::getInstance()->getRunningScene();
    scene->addChild(_layer,SCENE_TWOLAYER_ZORDER,TAG_EQUIPSTRONG);
}
void GeneralsStrong_Layer::updateEquip()
{
    Vector<BaseEquipData*>* chooseList= EquipDataManager::getInstance()->getDataList();
    int len=(int)chooseList->size();
    if (chooseList and len>0) {
        for (BaseEquipData* data :*chooseList) {
            data->cardLocation=0;
            data->cardOldLocation=0;
        }
        EquipDataManager::getInstance()->clearCardList();
    }
    int equipLen=(int)equipList->size();
    for (int i=0; i<equipLen; i++) {
        int _size=(int)EquipDataManager::getInstance()->getDataList()->size();
        BaseEquipData* data=equipList->at(i);
        if (data->equipLevel<2 and _size<6) {
            EquipDataManager::getInstance()->addData(data);
            data->cardLocation=_size+1;
            data->cardOldLocation=_size+1;
        }
        
        
    }
    this->leftLayer();
    
}
void GeneralsStrong_Layer::effectOver()
{
    NoticeManager::getInstance()->showNotice("熔炼成功",NoticeManager::COLOR_GREEN);
    EquipDataManager::getInstance()->setPresentData(newEquipData);
    EquipDataManager::getInstance()->clearCardList();
    this->equipListMsg();
}
//-------------------------------------------------------熔炼-------------------------------------------------------//
void GeneralsStrong_Layer::requestListMsg()
{
    if(EquipDataManager::getInstance()->getPresentData())
    {
        int _equipId=EquipDataManager::getInstance()->getPresentData()->equipId;
        EquipForgeMsg* msg = new EquipForgeMsg(_equipId);
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg = NULL;
    }
    
}
void GeneralsStrong_Layer::equipStartSmeltMsg()
{
    int _equipId=EquipDataManager::getInstance()->getPresentData()->equipId;
    EquipStartForgeMsg* msg = new EquipStartForgeMsg(_equipId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
    
}
void GeneralsStrong_Layer::equipListMsg()
{
    EquipListMsg* msg = new EquipListMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void GeneralsStrong_Layer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_EQUIP_EquipForgePageResp)
    {
        oldEquipData->equipId=newEquipData->equipId=message->byteStream->getInt();
        oldEquipData->equipDictId=message->byteStream->getInt();
        oldEquipData->equipName=message->byteStream->getUTF8();
        oldEquipData->quality=message->byteStream->getByte();
        maxQuality=message->byteStream->getByte();
        oldEquipData->equipLevel=newEquipData->equipLevel=message->byteStream->getInt();
        oldEquipData->equipMaxLevel=message->byteStream->getInt();
        oldEquipData->resource=message->byteStream->getUTF8();
        
        newEquipData->equipDictId=message->byteStream->getInt();
        newEquipData->equipName=message->byteStream->getUTF8();
        newEquipData->quality=message->byteStream->getByte();
        newEquipData->resource=message->byteStream->getUTF8();
        
        
        int smeltRockType=message->byteStream->getInt();
        int smeltRockNum=message->byteStream->getInt();
        int smeltRockMaxNum=message->byteStream->getInt();
        int _size=message->byteStream->getByte();
        for (int i=0; i<_size; i++) {
            struct BaseEquipProperty propertyData = {0,0};
            propertyData.propertyType=message->byteStream->getByte();
            propertyData.propertyNum=message->byteStream->getInt();
            oldEquipData->propertyList.push_back(propertyData);
        }
        _size=message->byteStream->getByte();
        for (int i=0; i<_size; i++) {
            struct BaseEquipProperty propertyData = {0,0};
            propertyData.propertyType=message->byteStream->getByte();
            propertyData.propertyNum=message->byteStream->getInt();
            newEquipData->propertyList.push_back(propertyData);
        }
        this->onSort();
        this->leftLayer();
        this->rightLayer();
        NewPlayerGuild::getInstance()->showNowGuide();
        
    }else if (message->messageID ==SCENSE_CLIENT_EQUIP_EquipForgeResp)
    {
        this->showEquipForgeSound();
        Sprite* leftBg=(Sprite*)this->getChildByTag(TAG_CARDBG);
        CommonEffect* commonEffect = CommonEffect::create("ronglianqiu",false,true,CC_CALLBACK_0(GeneralsStrong_Layer::effectOver, this));
        commonEffect->setAnchorPoint(Point(0.5,0.5));
        commonEffect->setPosition((leftBg->getContentSize().width/sx)/2-12,(leftBg->getContentSize().height/sx)/2+22);
        leftBg->addChild(commonEffect,12);
        broadMsg(CUSTOM_REFRESH_DOT,__Integer::create(DictFunctionEnumEquipForge));
        
    }else if(message->messageID == SCENSE_CLIENT_EQUIP_EquipListPageResp)
    {
        CC_SAFE_DELETE(equipList);
        
        EquipDataManager::getInstance()->clearEquipList();
        int maxListSize=message->byteStream->getShort();
        int _size=message->byteStream->getShort();
        for (int i=0; i<_size; i++) {
            BaseEquipData* data=new BaseEquipData();
            data->autorelease();
            data->equipId=message->byteStream->getInt();
            data->equipDictId=message->byteStream->getInt();
            data->quality=message->byteStream->getByte();
            data->equipLevel=message->byteStream->getInt();
            data->equipMaxLevel=message->byteStream->getInt();
            data->equipName=message->byteStream->getUTF8();
            data->equipParts=message->byteStream->getByte();
            data->heroName=message->byteStream->getUTF8();
            data->equipStatus=message->byteStream->getByte();
            data->resource=message->byteStream->getUTF8();
            data->isAbleStrong = message->byteStream->get();
            int propertySize=message->byteStream->getByte();
            for (int i=0; i<propertySize; i++) {
                struct BaseEquipProperty propertyData = {0,0};
                propertyData.propertyType=message->byteStream->getByte();
                propertyData.propertyNum=message->byteStream->getInt();
                data->propertyList.push_back(propertyData);
            }
            EquipDataManager::getInstance()->addEquipData(data);
            if (data->equipId==EquipDataManager::getInstance()->getPresentData()->equipId) {
                EquipDataManager::getInstance()->setPresentData(data);
            }
        }
        this->requestListMsg();
    }
}
void GeneralsStrong_Layer::showEquipForgeSound()
{
    SoundManager::playEffectMusic(EFFECT_EQUIP_FORGE);
}
void GeneralsStrong_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_EQUIP_EquipForgePageResp).c_str(), CC_CALLBACK_1(GeneralsStrong_Layer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_EQUIP_EquipForgeResp).c_str(), CC_CALLBACK_1(GeneralsStrong_Layer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_EQUIP_EquipListPageResp).c_str(), CC_CALLBACK_1(GeneralsStrong_Layer::onMsgProcess, this));
    addUserMsg(CUSTOM_CHOOSE_CARD_OVER_FUN,CC_CALLBACK_1(GeneralsStrong_Layer::chooseCardOver, this));
}
//-------------------------------------------------------------卡牌排序部分------------------------------------------------------------//


void GeneralsStrong_Layer::onSort()
{
    equipList=new Vector<BaseEquipData*>();
    
    Vector<BaseEquipData*>* tempList=EquipDataManager::getInstance()->getEquipDataList();
    BaseEquipData* presentData=EquipDataManager::getInstance()->getPresentData();
    //排除所需装备和被穿装备和熔炼品质装备不一样的
    for (BaseEquipData* data: *tempList) {
        if (data->equipId!=presentData->equipId and data->heroName=="" and data->quality==presentData->quality) {
            equipList->pushBack(data);
        }
    }
}
//-------------------------------------------------------

void GeneralsStrong_Layer::chooseCardOver(EventCustom* msg)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    GeneralsEquipStrong_Layer* _layer=(GeneralsEquipStrong_Layer*)scene->getChildByTag(TAG_EQUIPSTRONG);
    if (_layer) {
        scene->removeChildByTag(TAG_EQUIPSTRONG);
    }
    this->leftLayer();
}
void GeneralsStrong_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
    _eventDispatcher->removeCustomEventListeners(CUSTOM_CHOOSE_CARD_OVER_FUN);
}