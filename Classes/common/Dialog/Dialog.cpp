//
//  Dialog.cpp
//  SuiTang
//
//  Created by mac on 14-6-26.
//
//

#include "Dialog.h"
#include "ServerLoadingLayer.h"
#include "../../module/publicLayer/BodyPowerPanel.hpp"
#include "../../module/buyPower/BuyPowerLayer.hpp"
PopUpLayer* Dialog::show(const char* content,const char*  title,unsigned short buttonCount,Ref* target,SEL_CallFuncN callfun)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    PopUpLayer* pl = (PopUpLayer*)scene->getChildByTag(LAYER_DIALOG);
    if(pl)
    {
        pl->close();
    }
    
    pl = createPopLayer(content,title,target,callfun);
    if(buttonCount == 1)
    {
         pl->addButton(IMG_BUTTON_CONFIRM_LABEL, 1,IMG_PUBLIC_BUTTON_TWO_ORANGE);
    }
    else if(buttonCount == 2)
    {
        pl->addButton(IMG_BUTTON_CANCEL_LABEL, 2,IMG_PUBLIC_BUTTON_TWO_RED);
        pl->addButton(IMG_BUTTON_CONFIRM_LABEL, 1,IMG_PUBLIC_BUTTON_TWO_ORANGE);
    }
   
    pl->setPositionX(VisibleRect::center().x - pl->getContentSize().width/2);
    pl->setPositionY(VisibleRect::center().y - pl->getContentSize().height/2);
    scene->addChild(pl,SCENE_POPLAYER_ZORDER + 100,LAYER_DIALOG);

    if(strcmp(title, "提示") == 0 && strcmp(title,"") == 0)
    {
//         SoundManager::playEffectMusic(EFFECT_HINTSOUND);
    }
    return pl;

}

PopUpLayer* Dialog::createPopLayer(const char* content,const char*  title,Ref* target,SEL_CallFuncN callfun)
{
    PopUpLayer* pl =PopUpLayer::create();
    
    pl->setCallBack(target, callfun);
    
    pl->setContent(content);
    pl->setTitle(title);

    return pl;
}
PopupLoading* Dialog::showLoading(float timess)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    PopupLoading* pl = (PopupLoading*)scene->getChildByTag(LAYER_LOADING);
    if(pl)
    {
        return pl;
    }
    pl =PopupLoading::create(timess);
    pl->setPosition(VisibleRect::center().x - pl->getContentSize().width/2, VisibleRect::center().y - pl->getContentSize().height/2);
    scene->addChild(pl,SCENE_LAYERLOADING_ZORDER,LAYER_LOADING);
    return pl;
}
void Dialog::hideLoading()
{
    Scene* scene = Director::getInstance()->getRunningScene();
    
    Node* node = scene->getChildByTag(LAYER_LOADING);
    if(node)
    {
        scene->removeChildByTag(LAYER_LOADING);
    }
}
LoadingPage* Dialog::showLoadingPage()
{
    Scene* scene = Director::getInstance()->getRunningScene();
    LoadingPage* pl = (LoadingPage*)scene->getChildByTag(LAYER_LOADING);
    if(pl)
    {
        return pl;
    }
    pl =LoadingPage::create();
    pl->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(pl);
    pl->setPosition(VisibleRect::center().x - pl->getContentSize().width/2, VisibleRect::center().y - pl->getContentSize().height/2);
    scene->addChild(pl,SCENE_LAYERLOADING_ZORDER,LAYER_LOADING);
    return pl;

}
void Dialog::showShieldLayer()
{
//    Scene* scene = Director::getInstance()->getRunningScene();
//    if(scene->getChildByTag(LAYER_SHIELD))
//    {
//        return;
//    }
//    ShieldLayer* layer = ShieldLayer::create();
//    scene->addChild(layer, SCENE_LAYERLOADING_ZORDER, LAYER_SHIELD);
}
void Dialog::showServerLoading(float times,float isShowReLogin)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    if(scene->getChildByTag(LAYER_SERVER_LOADING))
    {
        return;
    }
    if(scene->getChildByTag(LAYER_LOADING))
    {
        return;
    }
    ServerLoadingLayer* layer = ServerLoadingLayer::create(times);
    layer->isShowReLogin = isShowReLogin;
    scene->addChild(layer, SCENE_LAYERLOADING_ZORDER, LAYER_SERVER_LOADING);
}
void Dialog::hideServerLoading()
{
    Scene* scene = Director::getInstance()->getRunningScene();
    
    Node* node = scene->getChildByTag(LAYER_SERVER_LOADING);
    if(node)
    {
        scene->removeChildByTag(LAYER_SERVER_LOADING);
    }
}
void Dialog::showNoPowerDialog(int fromeMoudle)
{
    BodyPowerPanel::show(fromeMoudle);
}