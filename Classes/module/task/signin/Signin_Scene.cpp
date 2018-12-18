//
//  Signin_Scene.cpp
//  FightPass
//
//  Created by 超 顾 on 15/10/9.
//
//

#include "Signin_Scene.h"
#include "../../userWealth/UserWealthLayer.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "everydaySignin/EverydaySignin_Layer.h"
#include "luxurySignin/LuxurySignin_Layer.h"
#include "../../../protocol/UserCustomEvent.h"
#include "moneyDrawing/MoneyDrawing.h"
#include "benefit/DayBenefit_Layer.h"
#include "benefit/WeekBenefit_Layer.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../commonData/data/FunctionOpenManager.h"
#include "power/PowerLayer.hpp"
#include "../../dot/RefreshDot.h"
Signin_Scene::Signin_Scene()
:sx(1)
,m_selected(NULL)
,TAG_TOP(1)
,TAG_TABLEVIEW(2)
,TAG_PERSON(3)
,TAG_NODEBTN(4)
,TAG_SELECTED(5)//
,TAG_MODULE(6)
,TAG_MODULELABEL(7)
,TAG_COMBOBOX(100)//后面空出4个
{
//    Vector<Button*>* btnList
    btnList=new Vector<Button*>();
}
Signin_Scene::~Signin_Scene()
{
    btnList->clear();
}
bool Signin_Scene::init(int value)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());        
        sx= GlobalInfo::getInstance()->screenScaleX;
        select_id=value;
       
        this->createLayer();
        this->topLayer();
        this->combobox();
        this->setBackBtn(0,15*sx);
        bref = true;
    } while (false);
    return bref;
}
void Signin_Scene::onEnter()
{
    BaseLayer::onEnter();
}
void Signin_Scene::onExit()
{
    BaseLayer::onExit();
}
void Signin_Scene::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void Signin_Scene::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumPrayerTag);
    
}
Signin_Scene* Signin_Scene::create(int value)
{
    Signin_Scene* layer = new Signin_Scene();
    if(layer && layer->init(value))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void Signin_Scene::show(int fromeScene,int value)
{
    Director::getInstance()->purgeCachedData();
    Signin_Scene* layer = Signin_Scene::create(value);
    layer->setFromScene(fromeScene);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    Scene* scene = Scene::create();
    scene->addChild(layer,0,SCENE_TAG_GENERALS);
    Director::getInstance()->replaceScene(scene);
}
void Signin_Scene::createLayer()
{
    
    Sprite* bg=Sprite::create(IMG_SIGNIN_BG);
    PublicShowUI::setTargetScale(bg,true);
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg,0,TAG_BG);
    
//    Sprite* bgSprgray = Sprite::create(IMG_PUBLIC_MODULE_MASK_BOTTOM);
//    PublicShowUI::setTargetScale(bgSprgray,true);
//    bgSprgray->setAnchorPoint(Point::ZERO);
//    bgSprgray->setPosition(Point::ZERO);
//    this->addChild(bgSprgray,1);
}
void Signin_Scene::topLayer()
{
    UserWealthLayer* layer = UserWealthLayer::create(UserWealthLayer::BELONG);
    PublicShowUI::setTargetScale(layer);
    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2, VisibleRect::top().y-layer->getContentSize().height);
    this->addChild(layer,3,TAG_TOP);
    layer->setTitle(IMG_PUBLIC_SIGNIN);
}
void Signin_Scene::combobox()
{
    Node* node=Node::create();
    int functionList[4] = {DictFunctionEnumWelfareDay,DictFunctionEnumLucky,DictFunctionEnumSign,DictFunctionEnumBanquet};
    int index = 0;
    for (int i=0; i<4; i++) {
        if (!FunctionOpenManager::getInstance()->functionIsOpened(functionList[i]))
        {
            continue;
        }
        Button* cell=Button::create(IMG_SIGNIN_COMBOBOX_BG,IMG_SIGNIN_COMBOBOX_BG,CC_CALLBACK_1(Signin_Scene::onComboBoxBtnClick, this));
        cell->setAnchorPoint(Point::ZERO);
        PublicShowUI::setDot(cell,Point::ZERO,false,functionList[i]);
        PublicShowUI::setTargetScale(cell);
        cell->setScale(0.8*sx);
        cell->setCascadeOpacityEnabled(false);
        cell->setOpacity(100);
        this->setCascadeColorEnabled(false);
        cell->setPosition(0,index*(cell->getContentSize().height-15*sx));
        node->addChild(cell,1,TAG_COMBOBOX+i);
        
        Sprite* touchBg=Sprite::create(IMG_SIGNIN_COMBOBOX_SELECTED);
        touchBg->setAnchorPoint(Point::ZERO);
        touchBg->setPosition((cell->getContentSize().width/sx-touchBg->getContentSize().width)/2,(cell->getContentSize().height/sx-touchBg->getContentSize().height)/2);
        touchBg->setVisible(false);
        cell->addChild(touchBg,3,TAG_SELECTED);
        
        string resource=PublicShowUI::numberToString(i+1);
        const char* path = PublicShowUI::getResImgPath(IMG_SIGNIN_COMBOBOX_MODULE,resource.c_str());
        Sprite* module=Sprite::create(path);
        module->setAnchorPoint(Point::ZERO);
        module->setOpacity(255);
        cell->addChild(module,2);
        module->setPosition(Point::ZERO);

        btnList->pushBack(cell);
        index++;
    }
    if(FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumLucky))
    {
         GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumPrayerTag, node->getChildByTag(TAG_COMBOBOX + 1));
    }
   
    Button* btn=(Button*)btnList->at(0);
    Size cellSize=btn->getContentSize();
    cellSize.height=(cellSize.height+5)*btnList->size();
    node->setContentSize(cellSize);
    node->setPosition(VisibleRect::right().x-node->getContentSize().width-18*sx,VisibleRect::center().y-node->getContentSize().height/2+60*sx);
    this->addChild(node,3,TAG_NODEBTN);
    if (select_id==TAG_DAYBENEFIT) {
       
        onComboBoxBtnClick(node->getChildByTag(TAG_COMBOBOX+0));
    }else if (select_id==TAG_MONEYDRAWING)
    {
        onComboBoxBtnClick(node->getChildByTag(TAG_COMBOBOX+1));
    }else if (select_id==TAG_EVERYDAY)
    {
        onComboBoxBtnClick(node->getChildByTag(TAG_COMBOBOX+2));
    }
    
}
void Signin_Scene::onComboBoxBtnClick(Ref* psender)
{
    if (m_selected) {
        m_selected->setOpacity(100);
        m_selected->setCascadeColorEnabled(false);
        m_selected->setCascadeOpacityEnabled(false);
        
        Sprite* selected=(Sprite*)m_selected->getChildByTag(TAG_SELECTED);
        if (selected) {
            selected->setVisible(false);
        }
    }
    m_selected=NULL;
    m_selected=(Sprite*)psender;
    if (m_selected) {
        m_selected->setOpacity(255);
        Sprite* selected=(Sprite*)m_selected->getChildByTag(TAG_SELECTED);
        if (selected) {
            selected->setVisible(true);
        }
        selectLayer(m_selected->getTag());
    }
    
}
void Signin_Scene::selectLayer(int num)
{
    Sprite* layer=(Sprite*)this->getChildByTag(TAG_TABLEVIEW);
    if (layer) {
        this->removeChildByTag(TAG_TABLEVIEW);
    }
    Sprite* person=(Sprite*)this->getChildByTag(TAG_PERSON);
    if (person) {
        this->removeChildByTag(TAG_PERSON);
    }
    UserWealthLayer* top_layer=(UserWealthLayer*)this->getChildByTag(TAG_TOP);
    Sprite* bg=(Sprite*)this->getChildByTag(TAG_BG);
//    num=100;
    if (num==TAG_LAYER::TAG_EVERYDAY) {
        top_layer->setTitle(IMG_PUBLIC_SIGNIN);
        EverydaySignin_Layer* layer=EverydaySignin_Layer::create();
        layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-40*sx-layer->getContentSize().height/2);
        this->addChild(layer,1,TAG_TABLEVIEW);
    }else if (num==TAG_LAYER::TAG_LUXURY)
    {
        top_layer->setTitle(IMG_PUBLIC_SIGNIN);
        LuxurySignin_Layer* layer=LuxurySignin_Layer::create();
        layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2-80*sx,VisibleRect::center().y-21*sx-layer->getContentSize().height/2);
        this->addChild(layer,1,TAG_TABLEVIEW);
    }else if (num==TAG_LAYER::TAG_MONEYDRAWING)
    {
        top_layer->setTitle(IMG_PUBLIC_LUCKY);
        NewPlayerGuild::getInstance()->next();
        MoneyDrawing* layer=MoneyDrawing::create();
        this->addChild(layer,0,TAG_TABLEVIEW);
        
    }else if (num==TAG_LAYER::TAG_DAYBENEFIT)
    {
        bg->setTexture(IMG_SEVEENDAY_BG);
        top_layer->setTitle(IMG_PUBLIC_BENEFIT);
        DayBenefit_Layer* layer= DayBenefit_Layer::create();
        layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2+20*sx,VisibleRect::center().y-31*sx-layer->getContentSize().height/2+50);
        this->addChild(layer,1,TAG_TABLEVIEW);
        
        Sprite* person=Sprite::create(IMG_SIGNIN_BENEFIT_PERSON);
        person->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(person);
        person->setPosition(-230*sx,VisibleRect::center().y-person->getContentSize().height/2);
        this->addChild(person,2,TAG_PERSON);
        
    }else if (num==TAG_LAYER::TAG_WEEKBENEFIT)
    {
        
        bg->setTexture(IMG_SEVEENDAY_BG);
        top_layer->setTitle(IMG_PUBLIC_BENEFIT);
        WeekBenefit_Layer* layer= WeekBenefit_Layer::create();
        layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2+20*sx,VisibleRect::center().y-31*sx-layer->getContentSize().height/2+50*sx);
        this->addChild(layer,1,TAG_TABLEVIEW);
        
//        bg->setTexture(IMG_SIGNIN_BENEFIT_BG);
        Sprite* person=Sprite::create(IMG_SIGNIN_BENEFIT_PERSON);
        person->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(person);
        person->setPosition(-230*sx,VisibleRect::center().y-person->getContentSize().height/2);
        this->addChild(person,2,TAG_PERSON);
    }else if(num==TAG_LAYER::TAG_POWER)
    {
        top_layer->setTitle(IMG_PUBLIC_YANXI);
        PowerLayer* layer=PowerLayer::create();
        this->addChild(layer,0,TAG_TABLEVIEW);
//        bg->setTexture(IMG_SIGNIN_POWERBG);
    }
}

//豪华签到和每日签到
void Signin_Scene::onMsgProcess(EventCustom* msg)
{
    __Integer* inter = (__Integer*)msg->getUserData();
    int _num = inter->getValue();
    selectLayer(_num);
}
void Signin_Scene::onRefreshDot(EventCustom* msg)
{
    __Integer* inter = (__Integer*)msg->getUserData();
    if(!inter)
    {
        return;
    }
    int tag_index = inter->getValue();
    Node* node = (Node*)this->getChildByTag(TAG_NODEBTN);
    if (tag_index == DictFunctionEnumWelfareDay) {
        RefreshDot::getInstance()->requestMsg(node->getChildByTag(TAG_COMBOBOX),Point::ZERO,true,DictFunctionEnumWelfareDay);
    }else if(tag_index == DictFunctionEnumLucky)
    {
        RefreshDot::getInstance()->requestMsg(node->getChildByTag(TAG_COMBOBOX+1),Point::ZERO,true,DictFunctionEnumLucky);
    }else if(tag_index == DictFunctionEnumSign)
    {
        RefreshDot::getInstance()->requestMsg(node->getChildByTag(TAG_COMBOBOX+2),Point::ZERO,true,DictFunctionEnumSign);
    }else if(tag_index == DictFunctionEnumBanquet)
    {
        RefreshDot::getInstance()->requestMsg(node->getChildByTag(TAG_COMBOBOX+3),Point::ZERO,true,DictFunctionEnumBanquet);
    }
}

void Signin_Scene::addEventListener()
{
    this->addUserMsg(CUSTOM_SIGNIN_SENDMESSAGE_EVENT, CC_CALLBACK_1(Signin_Scene::onMsgProcess, this));
    addUserMsg(CUSTOM_REFRESH_DOT, CC_CALLBACK_1(Signin_Scene::onRefreshDot, this));
}
void Signin_Scene::removeEventListener()
{
    BaseLayer::removeEventListener();
}
