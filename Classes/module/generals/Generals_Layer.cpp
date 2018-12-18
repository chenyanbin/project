//
//  Generals_layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/7/27.
//
//

#include "Generals_Layer.h"
#include "../../common/comboxBtn/ComboBoxBtn.h"
#include "generalsBase/GeneralsBase_Layer.h"
#include "../userWealth/UserHeadLayer.h"
#include "../../message/Decoding/heroListMsg/heroListMsg.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../commonData/dictData/DictHero/DictHeroManager.h"
#include "generalsLetter/GeneralsLetter_Layer.h"
#include "generalsProps/GeneralsProps_Layer.h"
#include "generalsMaterial/GeneralsMaterial_Layer.h"
#include "generalsEquip/GeneralsEquip_Layer.h"
#include "generalsHeroList/GeneralsHeroList_Layer.h"
#include "../../commonData/data/FunctionOpenManager.h"
#include "generalsRiseQuality/GeneralsRiseQuality_Layer.hpp"
#include "../newPlayerGuide/NewPlayerGuild.h"
#include "../dot/RefreshDot.h"
#include "../../commonData/enum/DictFunctionEnum.h"
#include "../../protocol/UserCustomEvent.h"
Generals_Layer::Generals_Layer()
:sx(1)
,sy(1)
,TAG_LISTBG(1)
,TAG_TABLEVIEW(2)
,TAG_TOP(4)
,topsLayer(NULL)
,rightSelected(4)
,cardId(0)
{
}
Generals_Layer::~Generals_Layer()
{
    
}
bool Generals_Layer::init(int value,int _cardId)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx= GlobalInfo::getInstance()->screenScaleX;
        sy= GlobalInfo::getInstance()->screenScaleY;
        rightSelected=value;
        cardId=_cardId;
     
        this->setBackBtn(0,15*sx,true);
        this->setBackBg();
        this->setClickEnabled(false);
        this->topLayer();
        
        bref = true;
    } while (false);
    return bref;
}
void Generals_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void Generals_Layer::onExit()
{
    BaseLayer::onExit();
}
void Generals_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    
    if (cardId) {
        CardPropertyData* data=new CardPropertyData();
        data->heroId=cardId;
        CardDataManager::getInstance()->setPresentData(data);
    }

//    this->requestListMsg();
}
void Generals_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumMaterialTag);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumLetterTag);
    removeEventListener();
}
Generals_Layer* Generals_Layer::create(int value,int _cardId)
{
    Generals_Layer* layer = new Generals_Layer();
    if(layer && layer->init(value,_cardId))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void Generals_Layer::show(int fromeScene,int value,int _cardId)
{
    
    if(value == PAGE_TAG_GENERAL)
    {
        if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumHero))
        {
            return;
        }
    }
    else if(value == PAGE_TAG_LETTER)
    {
        if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumBook))
        {
            return;
        }
    }
    else if(value == PAGE_TAG_EQUIP)
    {
        if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumEquip))
        {
            return;
        }
    }
    else if(value == PAGE_TAG_MATERIAL)
    {
        if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumMater))
        {
            return;
        }
    }
    else if(value == PAGE_TAG_ITEM)
    {
        if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumItem))
        {
            return;
        }
    }
    Director::getInstance()->purgeCachedData();
    Generals_Layer* layer = Generals_Layer::create(value,_cardId);
    layer->setFromScene(fromeScene);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    Scene* scene = Scene::create();
    scene->addChild(layer,0,SCENE_TAG_GENERALS);
    Director::getInstance()->replaceScene(scene);
}
//--------------------------------背景----------------------------------------------------
void Generals_Layer::setBackBg()
{
    Sprite* bg=Sprite::create(IMG_PUBLIC_MODULE_BG2);
    bg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bg,true,true);
    this->addChild(bg,0,TAG_BG);

    Sprite* bottom=Sprite::create(IMG_PUBLIC_MODULE_MASK_BOTTOM);
    bottom->setAnchorPoint(Point::ZERO);
    bottom->setPosition(Point::ZERO);
    PublicShowUI::setTargetScale(bottom,true);
    this->addChild(bottom);
    
    
}
//--------------------------------顶层----------------------------------------------------
void Generals_Layer::topLayer()
{
    topsLayer = UserWealthLayer::create(UserWealthLayer::BELONG);
    PublicShowUI::setTargetScale(topsLayer);
    topsLayer->setPosition(VisibleRect::center().x-topsLayer->getContentSize().width/2, VisibleRect::top().y-topsLayer->getContentSize().height);
    this->addChild(topsLayer,3,TAG_TOP);
    
    this->rightListVertical();
}
//--------------------------------右列表----------------------------------------------------
void Generals_Layer::rightListVertical()
{
    float rightY= VisibleRect::right().x;
    UserWealthLayer* layer=(UserWealthLayer*)this->getChildByTag(TAG_TOP);
    ComboBoxBtn* boxBtn =NULL;
    if (rightSelected==PAGE_TAG_GENERAL )//武将 
    {
        layer->setTitle(IMG_PUBLIC_HERO);
        
        GeneralsHeroList_Layer* tempLayer=GeneralsHeroList_Layer::create();
        Sprite* top=(Sprite*)this->getChildByTag(TAG_TOP);
        tempLayer->setPosition((this->getContentSize().width-tempLayer->getContentSize().width)/2, (this->getContentSize().height-top->getContentSize().height-tempLayer->getContentSize().height)/2-10*sx);
        this->addChild(tempLayer,2,TAG_TABLEVIEW);
        
//        const char* pathList[2] = {IMG_PUBLIC_LABEL_GENERAL_VER,IMG_PUBLIC_LABEL_LETTER_VER};
//        int functionList[2]={DictFunctionEnumHero,DictFunctionEnumBook};
//        boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_VERTICAL, -28, CC_CALLBACK_1(Generals_Layer::onRightBtnClick, this));
//        for (int i = 0; i<2; i++) {
//            if(FunctionOpenManager::getInstance()->functionIsOpened(functionList[1-i]))
//            {
//                boxBtn->addBtn(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE,IMG_PUBLIC_COMBOBOX_BTNCHOSE, pathList[1-i],true,functionList[1-i]);
//            }
//        }
//        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumLetterTag, boxBtn->getButtonAt(0));
//        PublicShowUI::setTargetScale(boxBtn);
//        boxBtn->setPosition(rightY-boxBtn->getContentSize().width-10*sx,(this->getContentSize().height-boxBtn->getContentSize().height)/2);
//        if (rightSelected==PAGE_TAG_GENERAL) {
//            boxBtn->selectAtByTag(DictFunctionEnumHero);
//        }else{
//            boxBtn->selectAtByTag(DictFunctionEnumBook);
//        }
//        this->addChild(boxBtn,3);
    }else if (rightSelected==PAGE_TAG_EQUIP or rightSelected==PAGE_TAG_MATERIAL)//装备 材料
    {
        layer->setTitle(IMG_PUBLIC_EQUIP3);
        const char* pathList[2] = {IMG_PUBLIC_LABEL_EQUIP_VER,IMG_PUBLIC_LABEL_STUFF_VER};
        int functionList[2]={DictFunctionEnumEquip,DictFunctionEnumMater};
        boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_VERTICAL, -28, CC_CALLBACK_1(Generals_Layer::onRight2BtnClick, this));
        for (int i = 0; i<2; i++) {
            if(FunctionOpenManager::getInstance()->functionIsOpened(functionList[1-i]))
            {
                boxBtn->addBtn(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE,IMG_PUBLIC_COMBOBOX_BTNCHOSE, pathList[1-i],true,functionList[1-i]);
            }
        }
        PublicShowUI::setDot(boxBtn->getButtonByTag(DictFunctionEnumEquip),Point(10,10),false,DictFunctionEnumEquipHarden,DictFunctionEnumEquipForge);
        PublicShowUI::setDot(boxBtn->getButtonByTag(DictFunctionEnumMater),Point(10,10),false,DictFunctionEnumMater);
        
        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumMaterialTag, boxBtn->getButtonAt(0));
        PublicShowUI::setTargetScale(boxBtn);
        boxBtn->setPosition(rightY-boxBtn->getContentSize().width-10*sx,(this->getContentSize().height-boxBtn->getContentSize().height)/2);
        if (rightSelected==PAGE_TAG_EQUIP) {
            boxBtn->selectAtByTag(DictFunctionEnumEquip);
        }else{
            boxBtn->selectAtByTag(DictFunctionEnumMater);
        }
        this->addChild(boxBtn,3);
    }else if (rightSelected==PAGE_TAG_ITEM or rightSelected==PAGE_TAG_LETTER or rightSelected == PAGE_TAG_RISEQUALIGY)//背包 书信 升品
    {
        
        const char* pathList[3] = {IMG_PUBLIC_LABEL_ITEMDETAILS,IMG_PUBLIC_LABEL_HEROFRAMENT,IMG_PUBLIC_LABEL_CAILIAOTAG};
        int functionList[3]={DictFunctionEnumItem,DictFunctionEnumBook,DictFunctionEnumHeroQuality};
        boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_VERTICAL, -28, CC_CALLBACK_1(Generals_Layer::onRight3BtnClick, this));
        for (int i = 0; i<3; i++) {
            if(FunctionOpenManager::getInstance()->functionIsOpened(functionList[2-i]))
            {
                boxBtn->addBtn(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE,IMG_PUBLIC_COMBOBOX_BTNCHOSE, pathList[2-i],true,functionList[2-i]);
            }
        }
        PublicShowUI::setDot(boxBtn->getButtonByTag(DictFunctionEnumItem),Point(10,10),false,DictFunctionEnumItem);
        PublicShowUI::setDot(boxBtn->getButtonByTag(DictFunctionEnumBook),Point(10,10),false,DictFunctionEnumBook);

        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumLetterTag, boxBtn->getButtonAt(0));
        PublicShowUI::setTargetScale(boxBtn);
        boxBtn->setPosition(rightY-boxBtn->getContentSize().width-10*sx,(this->getContentSize().height-boxBtn->getContentSize().height)/2);
        if (rightSelected==PAGE_TAG_ITEM) {
            boxBtn->selectAtByTag(DictFunctionEnumItem);
        }else if(rightSelected==PAGE_TAG_LETTER){
            boxBtn->selectAtByTag(DictFunctionEnumBook);
        }
        else {
            boxBtn->selectAtByTag(DictFunctionEnumHeroQuality);
        }
        this->addChild(boxBtn,3);
        
        
//        layer->setTitle(IMG_PUBLIC_PROPS);
//        GeneralsProps_Layer* tempLayer=GeneralsProps_Layer::create();
//        Sprite* top=(Sprite*)this->getChildByTag(TAG_TOP);
//        tempLayer->setPosition((this->getContentSize().width-tempLayer->getContentSize().width)/2, (this->getContentSize().height-top->getContentSize().height-tempLayer->getContentSize().height)/2-10*sx);
//        this->addChild(tempLayer,2,TAG_TABLEVIEW);
//        
//        topsLayer->setTitle(IMG_PUBLIC_PROPS);
    }
    
    
    
}
//-------------------------------view结束。点击事件部分-------------------------------------------------------//
void Generals_Layer::onRightBtnClick(Ref* psender)
{
    Node* node=(Node*) psender;
    int tag=node->getTag();
    Sprite* viewLayer=(Sprite*)this->getChildByTag(TAG_TABLEVIEW);
    if (viewLayer) {
        this->removeChildByTag(TAG_TABLEVIEW);
    }
    if (tag==DictFunctionEnumHero) {
        GeneralsHeroList_Layer* tempLayer=GeneralsHeroList_Layer::create();
        Sprite* top=(Sprite*)this->getChildByTag(TAG_TOP);
        tempLayer->setPosition((this->getContentSize().width-tempLayer->getContentSize().width)/2-90*sx, (this->getContentSize().height-top->getContentSize().height-tempLayer->getContentSize().height)/2-10*sx);
        this->addChild(tempLayer,2,TAG_TABLEVIEW);
    }else
    {
        GeneralsLetter_Layer* tempLayer=GeneralsLetter_Layer::create();
        Sprite* top=(Sprite*)this->getChildByTag(TAG_TOP);
        tempLayer->setPosition((this->getContentSize().width-tempLayer->getContentSize().width)/2-90*sx, (this->getContentSize().height-top->getContentSize().height-tempLayer->getContentSize().height)/2-10*sx);
        this->addChild(tempLayer,2,TAG_TABLEVIEW);
        NewPlayerGuild::getInstance()->next();
    }
    
}

void Generals_Layer::onRight2BtnClick(Ref* psender)
{
    Node* node=(Node*) psender;
    int tag=node->getTag();
    
    Sprite* viewLayer=(Sprite*)this->getChildByTag(TAG_TABLEVIEW);
    if (viewLayer) {
        this->removeChildByTag(TAG_TABLEVIEW);
    }
    if (tag==DictFunctionEnumEquip) {
        GeneralsEquip_Layer* tempLayer=GeneralsEquip_Layer::create();
        Sprite* top=(Sprite*)this->getChildByTag(TAG_TOP);
        tempLayer->setPosition((this->getContentSize().width-tempLayer->getContentSize().width)/2-90*sx, (this->getContentSize().height-top->getContentSize().height-tempLayer->getContentSize().height)/2-10*sx);
        this->addChild(tempLayer,2,TAG_TABLEVIEW);
    }else
    {
        NewPlayerGuild::getInstance()->next();
        GeneralsMaterial_Layer* tempLayer=GeneralsMaterial_Layer::create();
        Sprite* top=(Sprite*)this->getChildByTag(TAG_TOP);
        tempLayer->setPosition((this->getContentSize().width-tempLayer->getContentSize().width)/2-90*sx, (this->getContentSize().height-top->getContentSize().height-tempLayer->getContentSize().height)/2-10*sx);
        this->addChild(tempLayer,2,TAG_TABLEVIEW);
        
    }
   
}

void Generals_Layer::onRight3BtnClick(Ref* psender)//背包 书信
{
    Node* node=(Node*) psender;
    int tag=node->getTag();
    Sprite* viewLayer=(Sprite*)this->getChildByTag(TAG_TABLEVIEW);
    if (viewLayer) {
        this->removeChildByTag(TAG_TABLEVIEW);
    }
    if (tag==DictFunctionEnumItem) {
        GeneralsProps_Layer* tempLayer=GeneralsProps_Layer::create();
        Sprite* top=(Sprite*)this->getChildByTag(TAG_TOP);
        tempLayer->setPosition((this->getContentSize().width-tempLayer->getContentSize().width)/2-90*sx, (this->getContentSize().height-top->getContentSize().height-tempLayer->getContentSize().height)/2-10*sx);
        this->addChild(tempLayer,2,TAG_TABLEVIEW);
        
        topsLayer->setTitle(IMG_PUBLIC_PROPS);
    }else if(tag == DictFunctionEnumBook)
    {
        GeneralsLetter_Layer* tempLayer=GeneralsLetter_Layer::create();
        Sprite* top=(Sprite*)this->getChildByTag(TAG_TOP);
        tempLayer->setPosition((this->getContentSize().width-tempLayer->getContentSize().width)/2-90*sx, (this->getContentSize().height-top->getContentSize().height-tempLayer->getContentSize().height)/2-10*sx);
        this->addChild(tempLayer,2,TAG_TABLEVIEW);
        NewPlayerGuild::getInstance()->next();
    }else
    {
        GeneralsRiseQuality_Layer* tempLayer=GeneralsRiseQuality_Layer::create();
        Sprite* top=(Sprite*)this->getChildByTag(TAG_TOP);
        tempLayer->setPosition((this->getContentSize().width-tempLayer->getContentSize().width)/2-90*sx, (this->getContentSize().height-top->getContentSize().height-tempLayer->getContentSize().height)/2-10*sx);
        this->addChild(tempLayer,2,TAG_TABLEVIEW);
        topsLayer->setTitle(IMG_PUBLIC_PROPS);
    }
    
}
void Generals_Layer::onRefreshDot(EventCustom* msg)
{
    __Integer* inter = (__Integer*)msg->getUserData();
    if(!inter)
    {
        return;
    }
    int tag_index = inter->getValue();
    Button* btn = NULL;
    if (tag_index == DictFunctionEnumMater) {
        btn = (Button*)this->getChildByTag(DictFunctionEnumMater);
        if (btn) {
            RefreshDot::getInstance()->requestMsg(btn,Point::ZERO,false,DictFunctionEnumMater);
        }
    }else if (tag_index == DictFunctionEnumBook){
        btn = (Button*)this->getChildByTag(DictFunctionEnumBook);
        if (btn) {
            RefreshDot::getInstance()->requestMsg(btn,Point::ZERO,false,DictFunctionEnumBook);
        }
        
    }
}

void Generals_Layer::addEventListener()
{
    addUserMsg(CUSTOM_REFRESH_DOT, CC_CALLBACK_1(Generals_Layer::onRefreshDot, this));
}
void Generals_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}