//
//  Activity_Scene.cpp
//  FightPass
//
//  Created by 超 顾 on 15/10/28.
//
//

#include "Activity_Scene.h"
#include "../userWealth/UserWealthLayer.h"
#include "../../common/comboxBtn/ComboBoxBtn.h"
#include "../../protocol/UserCustomEvent.h"
#include "sevenActivity/SevenActivity_Layer.h"
Activity_Scene::Activity_Scene()
:sx(1)
,m_selected(NULL)
,TAG_TOP(1)
,TAG_TABLEVIEW(2)
,TAG_PERSON(3)

,TAG_SELECTED(11)//
,TAG_MODULE(12)
,TAG_MODULELABEL(13)
,TAG_COMBOBOX(100)//后面空出4个
{
    //    Vector<Button*>* btnList
    btnList=new Vector<Button*>();
}
Activity_Scene::~Activity_Scene()
{
    btnList->clear();
}
bool Activity_Scene::init(int value)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx= GlobalInfo::getInstance()->screenScaleX;
        this->createLayer();
        this->topLayer();
        this->combobox();
        this->setBackBtn(0,15*sx);
        bref = true;
    } while (false);
    return bref;
}
void Activity_Scene::onEnter()
{
    BaseLayer::onEnter();
}
void Activity_Scene::onExit()
{
    BaseLayer::onExit();
}
void Activity_Scene::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void Activity_Scene::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    
}
Activity_Scene* Activity_Scene::create(int value)
{
    Activity_Scene* layer = new Activity_Scene();
    if(layer && layer->init(value))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void Activity_Scene::show(int fromeScene,int value)
{
    Director::getInstance()->purgeCachedData();
    Activity_Scene* layer = Activity_Scene::create(value);
    layer->setFromScene(fromeScene);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    Scene* scene = Scene::create();
    scene->addChild(layer,0,SCENE_TAG_GENERALS);
    Director::getInstance()->replaceScene(scene);
}
void Activity_Scene::createLayer()
{
    
    Sprite* bg=Sprite::create(IMG_SIGNIN_BENEFIT_BG);
    PublicShowUI::setTargetScale(bg,true);
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg,0,TAG_BG);
    
    Sprite* bgSprgray = Sprite::create(IMG_PUBLIC_MODULE_MASK_BOTTOM);
    PublicShowUI::setTargetScale(bgSprgray,true);
    bgSprgray->setAnchorPoint(Point::ZERO);
    bgSprgray->setPosition(Point::ZERO);
    this->addChild(bgSprgray,0);
}
void Activity_Scene::topLayer()
{
    UserWealthLayer* layer = UserWealthLayer::create(UserWealthLayer::BELONG);
    PublicShowUI::setTargetScale(layer);
    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2, VisibleRect::top().y-layer->getContentSize().height);
    this->addChild(layer,3,TAG_TOP);
    layer->setTitle(IMG_PUBLIC_SEVENDAY);
}
void Activity_Scene::combobox()
{
    
    Sprite* spr = Sprite::create(IMG_GENERALS_SEVENACTIVITY_PERSONAE);
    spr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(spr);
    spr->setPosition(VisibleRect::center().x-spr->getContentSize().width/2-350*sx,VisibleRect::center().y-spr->getContentSize().height/2);
    this->addChild(spr,1);
    
    Sprite* sprlabel = Sprite::create(IMG_GENERALS_SEVENACTIVITY_LABEL);
    sprlabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(sprlabel);
    sprlabel->setPosition(VisibleRect::center().x-sprlabel->getContentSize().width/2-350*sx,VisibleRect::center().y-sprlabel->getContentSize().height/2-200*sx);
    this->addChild(sprlabel,2);
    
    
    SevenActivity_Layer* layer=SevenActivity_Layer::create();
//    PublicShowUI::setTargetScale(layer);
    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2+120,VisibleRect::center().y-40-layer->getContentSize().height/2);
    this->addChild(layer,3,TAG_TABLEVIEW);
    

}
void Activity_Scene::onComboBoxBtnClick(Ref* psender)
{

}
void Activity_Scene::selectLayer(int num)
{
}
void Activity_Scene::removeEventListener()
{
    BaseLayer::removeEventListener();
}