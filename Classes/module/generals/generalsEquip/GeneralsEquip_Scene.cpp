//
//  GeneralsEquip_Scene.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/25.
//
//

#include "GeneralsEquip_Scene.h"
#include "../../userWealth/UserWealthLayer.h"
#include "../../../common/TouchSprite/Button.h"

#include "../Generals_Layer.h"
#include "GeneralsStrong_Layer.h"
#include "EquipSmelt_Layer.h"
#include "../data/EquipDataManager.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../commonData/data/FunctionOpenManager.h"
#include "../../dot/RefreshDot.h"
GeneralsEquip_Scene::GeneralsEquip_Scene()
:sx(1)
,TAG_TOP(1)
,chooseId(-1)
,TAG_STRONGLAYER(2)
,TAG_SMELTLAYER(3)
,TAG_BOBOXCOM(4)
,userlayerHeight(0)
,boxBtn(NULL)
{
    
}
GeneralsEquip_Scene::~GeneralsEquip_Scene()
{
    EquipDataManager::getInstance()->clearEquipList();
    EquipDataManager::getInstance()->clearCardList();
}
GeneralsEquip_Scene* GeneralsEquip_Scene::create(int valueId)
{
    GeneralsEquip_Scene* layer = new GeneralsEquip_Scene();
    if(layer && layer->init(valueId))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
bool GeneralsEquip_Scene::init(int valueId)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        chooseId=valueId;
        sx=GlobalInfo::getInstance()->screenScaleX;
        this->createLayer();
        this->setBackBtn(0,15*sx);
        this->addRightList();
        this->isAbleGuiding = true;
        bref = true;
    } while (false);
    return bref;
}
void GeneralsEquip_Scene::onEnter()
{
    BaseLayer::onEnter();
}
void GeneralsEquip_Scene::onExit()
{
    BaseLayer::onExit();
}
void GeneralsEquip_Scene::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void GeneralsEquip_Scene::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}

void GeneralsEquip_Scene::show(int fromeScene,int valueId)
{
    Director::getInstance()->purgeCachedData();
    GeneralsEquip_Scene* layer=GeneralsEquip_Scene::create(valueId);
    layer->setFromScene(fromeScene);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    Scene* scene = Scene::create();
    scene->addChild(layer,0,SCENE_TAG_GENERALSCARD);
    Director::getInstance()->replaceScene(scene);
}

void GeneralsEquip_Scene::createLayer()
{
    Sprite* bg=Sprite::create(IMG_PUBLIC_EQUIP_BG);
    PublicShowUI::setTargetScale(bg,true);
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg,0,TAG_BG);
    this->setContentSize(bg->getContentSize());
    

    UserWealthLayer* userlayer = UserWealthLayer::create(UserWealthLayer::BELONG);
    PublicShowUI::setTargetScale(userlayer);
    userlayer->setPosition(VisibleRect::center().x-userlayer->getContentSize().width/2, VisibleRect::top().y-userlayer->getContentSize().height);
    this->addChild(userlayer,3,TAG_TOP);
    userlayer->setTitle(IMG_PUBLIC_EQUIP3);
    userlayerHeight=userlayer->getContentSize().height;
}
void GeneralsEquip_Scene::smeltLayer()
{
    GeneralsStrong_Layer* layer=(GeneralsStrong_Layer*)this->getChildByTag(TAG_STRONGLAYER);
    if (layer) {
        this->removeChildByTag(TAG_STRONGLAYER);
    }
    
}

//------------------------------------------------------右列表------------------------------------------------------------//
void GeneralsEquip_Scene::addRightList()
{
    const char* pathList[2] = {IMG_PUBLIC_LABEL_PRACTICE_VER,IMG_PUBLIC_LABEL_INTENSIFY_VER};
    int functionList[2]={DictFunctionEnumEquipForge,DictFunctionEnumEquipHarden};
    boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_VERTICAL, 0, CC_CALLBACK_1(GeneralsEquip_Scene::onComboBoxBtnClick, this));
    for (int i = 0; i<2; i++) {
        boxBtn->addBtn(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE, IMG_PUBLIC_COMBOBOX_BTNCHOSE, pathList[i],true,functionList[i]);
    }
    PublicShowUI::setTargetScale(boxBtn);
    PublicShowUI::setDot(boxBtn->getButtonByTag(DictFunctionEnumEquipForge),Point(10,10),false,DictFunctionEnumEquipForge);
    PublicShowUI::setDot(boxBtn->getButtonByTag(DictFunctionEnumEquipHarden),Point(10,10),false,DictFunctionEnumEquipHarden);
    boxBtn->setPosition(this->getContentSize().width-boxBtn->getContentSize().width-15*sx,(this->getContentSize().height-boxBtn->getContentSize().height)/2-40*sx);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumMeltingTag, boxBtn->getButtonAt(0));
    
    if (chooseId==LAYER_EQUIP_STRONG) {
//        boxBtn->selectedAt(1);
        boxBtn->selectAtByTag(DictFunctionEnumEquipHarden);
    }else
    {
//        boxBtn->selectedAt(0);
         boxBtn->selectAtByTag(DictFunctionEnumEquipForge);
    }
    
    this->addChild(boxBtn,3,TAG_BOBOXCOM);
}

void GeneralsEquip_Scene::onComboBoxBtnClick(Ref* psender)
{
    Node* sp=(Node*)psender;
    int tag=sp->getTag();
    if (tag==DictFunctionEnumEquipHarden) {
        GeneralsStrong_Layer*strongLayer=(GeneralsStrong_Layer*)this->getChildByTag(TAG_STRONGLAYER);
        if (strongLayer) {
            this->removeChildByTag(TAG_STRONGLAYER);
        }
        EquipSmelt_Layer*smeltLayer=(EquipSmelt_Layer*)this->getChildByTag(TAG_SMELTLAYER);
        if (smeltLayer) {
            this->removeChildByTag(TAG_SMELTLAYER);
        }
        
        EquipSmelt_Layer* layer=EquipSmelt_Layer::create(chooseId);
        layer->setPosition(150*sx,(this->getContentSize().height-userlayerHeight-layer->getContentSize().height)/2);
        this->addChild(layer,31,TAG_SMELTLAYER);


    }else if (tag==DictFunctionEnumEquipForge)
    {
        EquipSmelt_Layer*smeltLayer=(EquipSmelt_Layer*)this->getChildByTag(TAG_SMELTLAYER);
        if (smeltLayer) {
            this->removeChildByTag(TAG_SMELTLAYER);
        }
        GeneralsStrong_Layer*strongLayer=(GeneralsStrong_Layer*)this->getChildByTag(TAG_STRONGLAYER);
        if (strongLayer) {
            this->removeChildByTag(TAG_STRONGLAYER);
        }
        NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumMeltingTag);
        GeneralsStrong_Layer* layer=GeneralsStrong_Layer::create(chooseId);
        layer->setPosition(150*sx,(this->getContentSize().height-userlayerHeight-layer->getContentSize().height)/2);
        this->addChild(layer,31,TAG_STRONGLAYER);

        
    }
    
}
//-------------------------------------------------------
void GeneralsEquip_Scene::onRefreshDot(EventCustom* msg)
{
    __Integer* inter = (__Integer*)msg->getUserData();
    if(!inter)
    {
        return;
    }
    int tag_index = inter->getValue();
    if (tag_index == DictFunctionEnumEquipHarden) {
        RefreshDot::getInstance()->requestMsg(boxBtn->getButtonByTag(DictFunctionEnumEquipHarden),Point(10,10),false);
    }else if (DictFunctionEnumEquipForge)
    {
        RefreshDot::getInstance()->requestMsg(boxBtn->getButtonByTag(DictFunctionEnumEquipForge),Point(10,10),false);
    }
}
void GeneralsEquip_Scene::addEventListener()//添加监听
{
    addUserMsg(CUSTOM_REFRESH_DOT, CC_CALLBACK_1(GeneralsEquip_Scene::onRefreshDot, this));
}
void GeneralsEquip_Scene::removeEventListener()
{
    BaseLayer::removeEventListener();
}