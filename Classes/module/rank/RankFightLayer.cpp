//
//  RankFightLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/1/4.
//
//

#include "RankFightLayer.h"
#include "../../common/TouchSprite/Button.h"
#include "../userWealth/UserWealthLayer.h"
#include "../../common/comboxBtn/ComboBoxBtn.h"
#include "RankPriceLayer.h"
#include "RankSynLayer.hpp"
#include "RankDayLayer.hpp"
RankFightLayer::RankFightLayer()
:sx(0)
,_tableView(NULL)
,TAG_TABLEBG(1)
,TAG_TABLEVIEW(2)
,TAG_PERDETAILBG(3)
,TAG_MULTIPLE(4)
,TAG_DAY(5)
,m_layer(6)
{
    
}
RankFightLayer::~ RankFightLayer()
{
    
}
void RankFightLayer::onExit()
{
    BaseLayer::onExit();
}
void RankFightLayer::onEnter()
{
    BaseLayer::onEnter();
}
void RankFightLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void RankFightLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
bool RankFightLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        
        this->isAnimation = false;
        this->isClickClose=true;
        this->setClickEnabled(true);
        this->isShowGrayBg = true;
        this->setBackBtn(0,15*sx);
       
        this->setBackground();
        this->createLayer();
        bref = true;
    } while (false);
    return bref;
}
RankFightLayer* RankFightLayer::create()
{
    RankFightLayer* layer = new RankFightLayer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void RankFightLayer::show(int fromScene)
{
    
    Director::getInstance()->purgeCachedData();
    Director::getInstance()->getTextureCache()->removeAllTextures();
    RankFightLayer* layer = RankFightLayer::create();
    layer->setFromScene(fromScene);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);

    Scene* scene = Scene::create();//
    scene->addChild(layer,0,SCENE_TAG_RANK);
    
    Director::getInstance()->replaceScene(scene);
}
void RankFightLayer::setBackground()
{
    Sprite* background = Sprite::create(IMG_PUBLIC_MODULE_BG2);
    PublicShowUI::setTargetScale(background,true);
    background->setAnchorPoint(Point::ZERO);
    background->setPosition(Point::ZERO);
    this->addChild(background,1);
}
void RankFightLayer::createLayer()
{

    Sprite* tablebg = Sprite::create(IMG_PUBLIC_LAYER_LISTBG);
    tablebg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(tablebg);
    tablebg->setPosition(VisibleRect::center().x-tablebg->getContentSize().width/2,VisibleRect::center().y-tablebg->getContentSize().height/2-20*sx);
    this->addChild(tablebg,1,TAG_TABLEBG);
    
    UserWealthLayer* layer = UserWealthLayer::create(UserWealthLayer::BELONG);
    PublicShowUI::setTargetScale(layer);
    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2, VisibleRect::top().y-layer->getContentSize().height);
    this->addChild(layer,2.);
    layer->setTitle(IMG_PUBLIC_MINGJIANGZHUAN);
    
    Sprite* listBg2=Sprite::create(IMG_PUBLIC_LAYER_TITLEBG);
    listBg2->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(listBg2);
    listBg2->setPosition(tablebg->getPositionX()+15*sx,tablebg->getPositionY()+450*sx);
    this->addChild(listBg2,2);
    
    ComboBoxBtn* btn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL,10, CC_CALLBACK_1(RankFightLayer::onClick, this));
    btn->addCustomBtn(IMG_PUBLIC_COMBOBOX_RANK1, IMG_PUBLIC_COMBOBOX_RANK2, IMG_RANK_ALLRANKWORD,IMG_RANK_ALLRANKWORDCHOSE);
    btn->addCustomBtn(IMG_PUBLIC_COMBOBOX_RANK1, IMG_PUBLIC_COMBOBOX_RANK2, IMG_RANK_DAYRANK, IMG_RANK_DAYRANKCHOSE);
    btn->setAnchorPoint(Point::ZERO);
    btn->setPosition(20*sx,(listBg2->getContentSize().height/sx-btn->getContentSize().height)/2+10*sx);
    listBg2->addChild(btn,10);
    btn->selectedAt(0);
    
    string decsstr = "排名将在次日更新";
    Label* decslabel = PublicShowUI::getLabel(decsstr.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),24,false,false);
    decslabel->setAnchorPoint(Point::ZERO);
    decslabel->setPosition(600*sx,(tablebg->getContentSize().height-decslabel->getContentSize().height)/2);
    this->addChild(decslabel,1);
    
}

void RankFightLayer::onClick(Ref* pSender)
{
//    return;
    Sprite* tablebg = (Sprite*)this->getChildByTag(TAG_TABLEBG);
    Node* target = (Node*)pSender;
    int tag = target->getTag();
    if (tag == 0) {
        if(m_layer == TAG_MULTIPLE ){
            return;
        }
        this->removeChildByTag(m_layer);
        RankSynLayer* layer =  RankSynLayer::create();
        if (layer) {
            layer->setAnchorPoint(Point::ZERO);
            PublicShowUI::setTargetScale(layer);
            layer->setPosition(tablebg->getPositionX() + 30*sx, tablebg->getPositionY() + 50*sx);
            this->addChild(layer,3,TAG_MULTIPLE);
            m_layer = TAG_MULTIPLE;
        }
    }else if (tag == 1)
    {
        if(m_layer == TAG_DAY ){
            return;
        }
        this->removeChildByTag(m_layer);
        RankDayLayer* daylayer =  RankDayLayer::create();
        if (daylayer) {
            daylayer->setAnchorPoint(Point::ZERO);
            PublicShowUI::setTargetScale(daylayer);
            daylayer->setPosition(tablebg->getPositionX() + 30*sx, tablebg->getPositionY() + 50*sx);
            this->addChild(daylayer,3,TAG_DAY);
            m_layer = TAG_DAY;
        }
    }
}
void RankFightLayer::onPriceClick(Ref* pSender) 
{
    RankPriceLayer::show();
}
//-----------------------------------------------------------------tableView-------------------------------------------------------------------------//
