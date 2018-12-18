 //
//  HomeMenuBar.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 14/11/6.
//
//

#include "HomeMenuBar.h"
#include "../../../../common/ImagePath.h"
#include "../../../../common/PublicShowUI.h"
#include "../../../../common/GameConfig.h"
#include "../../../../commonData/data/FunctionOpenManager.h"
#include "../../../../VisibleRect.h"
#include "../../../../commonData/data/GuideButtonManager.h"
#include "../../../../common/TouchSprite/TouchSprite.h"
#include "../../../chapter/ChapterLayer.h"
#include "../../../stageLayer/StageLayer.h"
#include "../../../lineup/LineupLayer.h"
#include "../../../sweep/SweepLayer.h"
#include "../../../generals/Generals_Layer.h"
#include "../../../generals/generalsCard/GeneralsCard_Layer.h"
#include "../../../market/MarketLayer.h"
#include "../../../battle/settleLayer/BattleLose.h"
#include "../../../task/TaskLayer.h"
#include "../../../task/signin/Signin_Scene.h"
#include "../../../../common/commonEffect/CommonEffect.h"
#include "../../../mail/MailLayer.h"
#include "../.././../activity/Activity_Scene.h"
#include "../../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../../commonData/enum/DictNewGuideEventEnum.h"
#include "../../../musou/MusouLayer.h"
#include "../../../famousGeneral/GeneralScene.hpp"
#include "../../../limitCard/LimitCardLayer.h"
#include "../../../../common/StringUtil.h"
#include "../../../../commonData/enum/DictFunctionEnum.h"
#include "../../../arena/ArenaLayer.hpp"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../dot/RefreshDot.h"
#include "../../../../protocol/UserCustomEvent.h"
#include "../../../../commonData/dictData/DictFunction/DictFunctionManager.h"
HomeMenuBar::HomeMenuBar()
:MENUCOUNT(3)
,TAG_BG(1)
,TAG_MENU(2)
,TAG_OPENBTN(3)
,TAG_CLOSEBTN(4)
,TAG_SWITCH_MENU(5)
,TAG_VERTICAL_MENU(6)
,TAG_SWITCHBTN(7)
,TAG_LEFTTIME(8)
,TAG_BOOKBTN(100)
,VERTICALCOUNT(1)
,menuY(0)
,sx(0)
,bookStatus(true)
,firstBtnNum(0)//第一层按钮个数
,m_time(0)
{
    menuID[0]= MENUBAR_SUPREMACY;
    menuID[1]= MENUBAR_STAGEBATTLE;
    menuID[2]= MENUBAR_BUZHEN;
    pointList=new vector<Point>();
    btnList=new Vector<Button*>();
}
HomeMenuBar::~HomeMenuBar()
{
    this->pointList->clear();
    CC_SAFE_DELETE(pointList);
    
    btnList->clear();
    CC_SAFE_DELETE(btnList);
}
bool HomeMenuBar::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Node::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        firstBtnNum=4;
        m_time = GlobalInfo::getInstance()->luckyLeftTime*1000;
        this->setMenuList();
        this->setPrayTime();
        Sprite* bg=Sprite::create(IMG_PUBLIC_MENUBTN_WAR);
        PublicShowUI::setTargetScale(bg);
        this->setContentSize(bg->getContentSize());
        bref = true;
    } while (false);
    return bref;
}

void HomeMenuBar::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
}

void HomeMenuBar::onExitTransitionDidStart()
{
    Node::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumBattleButton);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumJuxian);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumTaskButton);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumScrollButton);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumWelfareButton);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumSanguoWarriors);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumBagButton);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumArenaButton);
//    this->removeEventListener()
}
/*****************************公共函数*****************************************/
/*
 **征战坐标在pointList数组0位置
 **任务坐标在pointList数组1位置
 **福利坐标在pointList数组2位置
 **武将坐标在pointList数组3位置
 **背包坐标在pointList数组4位置
 **阵容坐标在pointList数组5位置
 **装备坐标在pointList数组6位置
 **拍卖坐标在pointList数组7位置
 **聚贤坐标在pointList数组8位置
 */
void HomeMenuBar::setMenuList()
{
    //征战
    Button* warBtn=Button::create(IMG_PUBLIC_MENUBTN_WAR, "", CC_CALLBACK_1(HomeMenuBar::onMenuClick,this));
    warBtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(warBtn);
    this->addChild(warBtn,2,MENUBAR_STAGEBATTLE);
    Point p=warBtn->getPosition();
//    pointList->push_back(p);
//    btnList->pushBack(warBtn);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumBattleButton, warBtn);
    
    CommonEffect* warEffect = CommonEffect::create("zhengzhananniu",true,true);
//    imperEffect->setAnchorPoint(Point(0.5,0.5));
//    PublicShowUI::setTargetScale(imperEffect);
    warEffect->setPosition((warBtn->getContentSize().width/sx-warEffect->getContentSize().width)/2,(warBtn->getContentSize().height/sx-warEffect->getContentSize().height)/2);
    warBtn->addChild(warEffect,2);
    
    CommonEffect* war2Effect = CommonEffect::create("zhengzhandaojian",true,true);
//    war2Effect->setAnchorPoint(Point(0.5,0.5));
//    PublicShowUI::setTargetScale(war2Effect);
    war2Effect->setPosition((warBtn->getContentSize().width/sx-war2Effect->getContentSize().width)/2,(warBtn->getContentSize().height/sx-war2Effect->getContentSize().height)/2);
    warBtn->addChild(war2Effect,2);
    
    //书卷
    Button* bookBtn=Button::create(IMG_PUBLIC_MENUBTN_BOOK, "", CC_CALLBACK_1(HomeMenuBar::onMenuClick,this));
    bookBtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bookBtn);
    bookBtn->setPosition((warBtn->getContentSize().width-bookBtn->getContentSize().width)/2-10*sx,warBtn->getContentSize().height-20*sx);
    this->addChild(bookBtn,3,BTN_BOOK);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumScrollButton, bookBtn);
    Sprite* arrows=Sprite::create(IMG_PUBLIC_MENUBTN_UP);
    arrows->setAnchorPoint(Point::ZERO);
    arrows->setPosition(bookBtn->getContentSize().width/sx-arrows->getContentSize().width-25,22);
    bookBtn->addChild(arrows,3,12);
    PublicShowUI::setDot(arrows, Point(-20,-20), false,DictFunctionEnumHeroPrestige,DictFunctionEnumHeroQuality,DictFunctionEnumHeroStar,DictFunctionEnumEquipHarden,DictFunctionEnumHeroEquip,DictFunctionEnumEquipForge);
    
    //任务
    Button* taskBtn=Button::create(IMG_PUBLIC_MENUBTN_TASK, "", CC_CALLBACK_1(HomeMenuBar::onMenuClick,this));
    taskBtn->setAnchorPoint(Point::ZERO);
    DictFunction* datafunc = DictFunctionManager::getInstance()->getData(5);
    if (FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumTaskDaily)) {//日常任务红点在其功能开启之后显示
        PublicShowUI::setDot(taskBtn,Point(0,50),false,DictFunctionEnumTaskCommon,DictFunctionEnumTaskDaily);
    }else{
        PublicShowUI::setDot(taskBtn,Point(0,50),false,DictFunctionEnumTaskCommon);
    }
    
    PublicShowUI::setTargetScale(taskBtn);
    taskBtn->setPosition(-taskBtn->getContentSize().width,0);
    this->addChild(taskBtn,2,MENUBAR_TASK);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumTaskButton, taskBtn);
    p=taskBtn->getPosition();
    pointList->push_back(p);
    if (!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumTaskCommon))
        taskBtn->setVisible(false);
    btnList->pushBack(taskBtn);
    
    //招募
    Button* juxianBtn=Button::create(IMG_PUBLIC_MENUBTN_JUXIAN, "", CC_CALLBACK_1(HomeMenuBar::onMenuClick, this));
    juxianBtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setDot(juxianBtn,Point(0,50),false,DictFunctionEnumLead,DictFunctionEnumFind);
    PublicShowUI::setTargetScale(juxianBtn);
    juxianBtn->setPosition(taskBtn->getPositionX()-juxianBtn->getContentSize().width-10*sx,taskBtn->getPositionY());
    this->addChild(juxianBtn,2,LAYER_MARKET_JUXIAN);
    p=juxianBtn->getPosition();
    pointList->push_back(p);
    btnList->pushBack(juxianBtn);
    if (!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumLead))
        juxianBtn->setVisible(false);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumJuxian, juxianBtn);
    
//    //限时
//    Button* limitBtn=Button::create(IMG_PUBLIC_MENUBTN_LIMIT, "", CC_CALLBACK_1(HomeMenuBar::onMenuClick, this));
//    limitBtn->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(limitBtn);
//    limitBtn->setPosition(juxianBtn->getPositionX()-limitBtn->getContentSize().width-10*sx,taskBtn->getPositionY());
//    this->addChild(limitBtn,2,LAYER_LIMIT);
//    p=limitBtn->getPosition();
//    pointList->push_back(p);
//    btnList->pushBack(limitBtn);
//    if (!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumLegend))
//        limitBtn->setVisible(false);
//    
    //竞技场
    Button* fightBtn=Button::create(IMG_PUBLIC_MENUBTN_FIGHTING, "", CC_CALLBACK_1(HomeMenuBar::onMenuClick, this));
    fightBtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setDot(fightBtn, Point(0,50), false,DictFunctionEnumArena);
    PublicShowUI::setTargetScale(fightBtn);
    fightBtn->setPosition(juxianBtn->getPositionX()-fightBtn->getContentSize().width-10*sx,taskBtn->getPositionY());
    this->addChild(fightBtn,2,LAYER_FIGHT);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumArenaButton, fightBtn);
    p=fightBtn->getPosition();
    pointList->push_back(p);
    btnList->pushBack(fightBtn);
    if (!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumArena))
        fightBtn->setVisible(false);
    
    
    
    //活动
//    Button* wealBtn=Button::create(IMG_PUBLIC_MENUBTN_WEAL, "", CC_CALLBACK_1(HomeMenuBar::onMenuClick,this));
//    wealBtn->setAnchorPoint(Point::ZERO);
//    //活动红点
//    PublicShowUI::setDot(wealBtn,Point::ZERO,false,DictFunctionEnumWelfareDay,DictFunctionEnumBanquet,DictFunctionEnumSign);
//    PublicShowUI::setTargetScale(wealBtn);
//    wealBtn->setPosition(20*sx,bookBtn->getPositionY()+bookBtn->getContentSize().height-20*sx);
//    this->addChild(wealBtn,2,LAYER_WEAL);
//    p=wealBtn->getPosition();
//    pointList->push_back(p);
//    btnList->pushBack(wealBtn);
//    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumWelfareButton, wealBtn);
    
    //祈福
    Button* prayBtn=Button::create(IMG_PUBLIC_MENUBTN_PRAY, "", CC_CALLBACK_1(HomeMenuBar::onMenuClick,this));
    prayBtn->setAnchorPoint(Point::ZERO);
    //祈福红点
    PublicShowUI::setDot(prayBtn,Point(0,50),false,DictFunctionEnumLucky);
    PublicShowUI::setTargetScale(prayBtn);
    prayBtn->setPosition(20*sx,bookBtn->getPositionY()+bookBtn->getContentSize().height-20*sx);
    this->addChild(prayBtn,2,LAYER_PRAY);
    p=prayBtn->getPosition();
    pointList->push_back(p);
    btnList->pushBack(prayBtn);
    if (!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumLucky))
        prayBtn->setVisible(false);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumQifuButton, prayBtn);
    
    //武将
    Button* generalBtn=Button::create(IMG_PUBLIC_MENUBTN_GENERAL, "", CC_CALLBACK_1(HomeMenuBar::onMenuClick, this));
    generalBtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setDot(generalBtn,Point(0,50),false,DictFunctionEnumHeroPrestige,DictFunctionEnumHeroQuality,DictFunctionEnumHeroStar,DictFunctionEnumHeroEquip);
    PublicShowUI::setTargetScale(generalBtn);
    generalBtn->setPosition(-generalBtn->getContentSize().width,10*sx);
    this->addChild(generalBtn,2,LAYER_WUJIANG);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumGeneralsButton, generalBtn);
    generalBtn->setVisible(false);
    p=generalBtn->getPosition();
    pointList->push_back(p);
    btnList->pushBack(generalBtn);
    //装备
    Button* equipBtn=Button::create(IMG_PUBLIC_MENUBTN_EQUIP, "", CC_CALLBACK_1(HomeMenuBar::onMenuClick, this));
    equipBtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setDot(equipBtn,Point(0,50),false,DictFunctionEnumEquipHarden,DictFunctionEnumEquipForge,DictFunctionEnumMater);
    PublicShowUI::setTargetScale(equipBtn);
    equipBtn->setPosition(generalBtn->getPositionX()-equipBtn->getContentSize().width-10*sx,10*sx);
    
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumEquipmentButton, equipBtn);
    this->addChild(equipBtn,2,LAYER_EQUIP);
    equipBtn->setVisible(false);
    p=equipBtn->getPosition();
    pointList->push_back(p);
    btnList->pushBack(equipBtn);

    //背包
    Button* boxBtn=Button::create(IMG_PUBLIC_MENUBTN_BOX, "", CC_CALLBACK_1(HomeMenuBar::onMenuClick, this));
    boxBtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(boxBtn);
    PublicShowUI::setDot(boxBtn, Point(0,50), false,DictFunctionEnumBook,DictFunctionEnumItem);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumBagButton, boxBtn);
    boxBtn->setPosition(equipBtn->getPositionX()-boxBtn->getContentSize().width-10*sx,10*sx);
    this->addChild(boxBtn,2,MENUBAR_BAG);
    boxBtn->setVisible(false);
    p=boxBtn->getPosition();
    pointList->push_back(p);
    btnList->pushBack(boxBtn);
    //阵容
    Button* linUpBtn=Button::create(IMG_PUBLIC_MENUBTN_LINEUP, "", CC_CALLBACK_1(HomeMenuBar::onMenuClick, this));
    linUpBtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(linUpBtn);
    linUpBtn->setPosition(20*sx,bookBtn->getPositionY()+linUpBtn->getContentSize().height-20*sx);
    this->addChild(linUpBtn,2,LAYER_ZHENRONG);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumTeam, linUpBtn);
    linUpBtn->setVisible(false);
    p=linUpBtn->getPosition();
    pointList->push_back(p);
    btnList->pushBack(linUpBtn);
    
    
    //拍卖
    Button* marketBtn=Button::create(IMG_PUBLIC_MENUBTN_MARKET, "", CC_CALLBACK_1(HomeMenuBar::onMenuClick, this));
    marketBtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(marketBtn);
//    marketBtn->setPosition(20*sx,bookBtn->getPositionY()+marketBtn->getContentSize().height-20*sx);
    marketBtn->setPosition(20*sx,linUpBtn->getPositionY()+marketBtn->getContentSize().height-20*sx);
    this->addChild(marketBtn,2,LAYER_MARKET_PAIMAI);
    marketBtn->setVisible(false);
    p=marketBtn->getPosition();
    pointList->push_back(p);
    btnList->pushBack(marketBtn);
    
    //-----------------------------------------------------广告---------------------------------------------------------------------------------------//
    //三国无双
    TouchSprite* imperBtn = TouchSprite::createWithPic(IMG_PUBLIC_MENUBTN_IMPER, this, callfuncN_selector(HomeMenuBar::onBayeClick));
    imperBtn->setAnchorPoint(Point::ZERO);
     PublicShowUI::setTargetScale(imperBtn);
    imperBtn->isButtonMode = true;
    imperBtn->setPosition(-imperBtn->getContentSize().width/2 + 50 * sx,VisibleRect::top().y - 140 *  sx);
    
     GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumSanguoWarriors, imperBtn);
    
    CommonEffect* imperEffect = CommonEffect::create("uiguanggao",true,true);
    imperEffect->setAnchorPoint(Point(0.5,0.5));
    PublicShowUI::setTargetScale(imperEffect);
    imperEffect->setPosition(imperBtn->getPositionX()+imperBtn->getContentSize().width/2,imperBtn->getPositionY()+imperBtn->getContentSize().height/2);
    
    
    if (FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumMusou))
    {
        this->addChild(imperBtn,2,MENUBAR_SUPREMACY);
        this->addChild(imperEffect,2);
    }
    //名将传
    TouchSprite* activeBtn = TouchSprite::createWithPic(IMG_PUBLIC_MENUBTN_FIGHTER, this, callfuncN_selector(HomeMenuBar::onActiveClick));
    activeBtn->setAnchorPoint(Point::ZERO);
    //红点
    PublicShowUI::setDot(activeBtn,Point(0,50),false,DictFunctionEnumLegend);
    PublicShowUI::setTargetScale(activeBtn);
    activeBtn->isButtonMode = true;
    activeBtn->setPosition(imperBtn->getPositionX(),imperBtn->getPositionY() + imperBtn->getContentSize().height + 5 * sx);
   
    
    CommonEffect* activeEffect = CommonEffect::create("uiguanggao",true,true);
    activeEffect->setAnchorPoint(Point(0.5,0.5));
    PublicShowUI::setTargetScale(activeEffect);
    activeEffect->setPosition(activeBtn->getPositionX()+activeBtn->getContentSize().width/2,activeBtn->getPositionY()+activeBtn->getContentSize().height/2);
    
    if (FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumLegend))
    {
        this->addChild(activeBtn,2,MENUBAR_ACTIVE);
        this->addChild(activeEffect,2);

    }
    
}
void HomeMenuBar::setPrayTime()
{
    Button* btn = (Button*)this->getChildByTag(LAYER_PRAY);
    
    if (m_time <= 0) {
        Label* label = (Label*)btn->getChildByTag(TAG_LEFTTIME);
        if(label)
        {
            label->removeFromParent();
            RefreshDot::getInstance()->requestMsg(btn,Point(10,10),false,DictFunctionEnumLucky);
//            label->setString("祈福开始");
        }
        return;
    }
    
    string str = PublicShowUI::getTime(m_time);
    Label* label = (Label*)btn->getChildByTag(TAG_LEFTTIME);
    if(label)
    {
        label->setString(str);
    }
    else
    {
        label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),20,false,false);
        label->setAnchorPoint(Point::ZERO);
        btn->addChild(label,9,TAG_LEFTTIME);
        label->setPosition(17,7);
    }
    m_time -= 1000;
    DelayTime* delay = DelayTime::create(1);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(HomeMenuBar::setPrayTime, this));
    label->runAction(Sequence::create(delay,callBack, NULL));
    GlobalInfo::getInstance()->luckyLeftTime = m_time / 1000;
}
void HomeMenuBar::onBayeClick(Node* pSender)
{
   
    if(pSender->isVisible())
    {
        NewPlayerGuild::getInstance()->next();
        GlobalInfo::getInstance()->battleType = kBattleTYPe_SanGuoWushuan;
        MusouLayer::requestMuouList();
    }

}
void HomeMenuBar::onActiveClick(Node* pSender)
{
    if(!pSender->isVisible())
    {
        return;
    }
    GeneralScene::show(SCENE_TAG_MAINUI);
}
void HomeMenuBar::onMenuClick(Ref* pSender)
{
    Node* node = (Node*)pSender;
    if(!node->isVisible())
    {
        return;
    }
    int tag = node->getTag();
    log("click tag=%d",tag);
    Scene* scene = NULL;
    switch (tag) {
        case BTN_BOOK:
            bookStatus=!bookStatus;
            this->barAction();
            
            break;
        case MENUBAR_STAGEBATTLE:
            NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumBattleButton);
//            if(FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumMusou))
//            {
//                StageLayer::show(SCENE_TAG_MAINUI);
//            }//不走这个界面了。。可能会永远去掉
//            else
//            {
                GlobalInfo::getInstance()->battleType = kBattleType_MingZhanYi;
                GlobalInfo::getInstance()->stageMode = StageMode::kStageModeCommon;
                ChapterLayer::requestChapterByID();
                
//            }
            break;
        case LAYER_PRAY:
            NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumQifuButton);
            Signin_Scene::show(SCENE_TAG_MAINUI,Signin_Scene::TAG_MONEYDRAWING);
            break;
        case MENUBAR_TASK:
            NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumTaskButton);
            TaskLayer::show(SCENE_TAG_MAINUI,TaskLayer::TAG_PUTONG);
            break;
        case LAYER_MARKET_JUXIAN:
            NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumJuxian);
            MarketLayer::show(SCENE_TAG_MAINUI,MarketLayer::TAG_XUNFANG);
            break;
        case LAYER_MARKET_PAIMAI:
            MarketLayer::show(SCENE_TAG_MAINUI,MarketLayer::TAG_PAIMAI);
            break;
        case LAYER_WUJIANG:
            NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumGeneralsButton);
//            Generals_Layer::show(SCENE_TAG_MAINUI);
            GeneralsCard_Layer::show(SCENE_TAG_MAINUI, DictFunctionEnumEquip);
            break;
        case MENUBAR_BAG:
            NewPlayerGuild::getInstance()->next();
            Generals_Layer::show(SCENE_TAG_MAINUI,Generals_Layer::PAGE_TAG_ITEM);

            break;
        case LAYER_ZHENRONG:
        
            NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumTeam);
            LineupLayer::show(SCENE_TAG_MAINUI,1,0);
            break;
        case LAYER_EQUIP:
            NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumEquipmentButton);
            Generals_Layer::show(SCENE_TAG_MAINUI,Generals_Layer::PAGE_TAG_EQUIP);
            break;
        case LAYER_WEAL:
            NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumWelfareButton);
            Signin_Scene::show(SCENE_TAG_MAINUI,Signin_Scene::TAG_DAYBENEFIT);
            break;
        case LAYER_LIMIT:
            LimitCardLayer::show();
            break;
        case LAYER_FIGHT:
            NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumArenaButton);
            ArenaLayer::show(ArenaLayer::PAGE_ARENALIST);
            
            break;
//
        default:
            break;
    }
    if(scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
    
}
void HomeMenuBar::barAction()
{
    Button* bookBtn=(Button*)this->getChildByTag(TAG_BOOKBTN);
    if (!bookBtn) {
        return;
    }
    Sprite* arrows=(Sprite*)bookBtn->getChildByTag(12);
    
    ActionInterval* move=MoveTo::create(0.3, Point(bookBtn->getPosition()));
    ActionInterval* fade=FadeTo::create(0.3, 0);
    CallFunc* callBack = NULL;
    
  
    FiniteTimeAction * spawn = Spawn::create(move,fade,NULL);
    CallFunc* funcall2 = CallFunc::create(CC_CALLBACK_0(HomeMenuBar::barAction3, this));
    FiniteTimeAction * seq2 = Sequence::create(spawn,funcall2,callBack,NULL);
    
    if (!bookStatus) {
        for (int i=0; i<firstBtnNum; i++) {
            btnList->at(i)->setVisible(false);
        }
        bookBtn->setNormalImage(IMG_PUBLIC_MENUBTN_BOOK2);
        arrows->setTexture(IMG_PUBLIC_MENUBTN_DOWN);
        PublicShowUI::setDot(arrows, Point(-20,-20), false);
        barAction2();
    }
    else
    {
        bookBtn->setNormalImage(IMG_PUBLIC_MENUBTN_BOOK);
        PublicShowUI::setDot(arrows, Point(-20,-20), false,DictFunctionEnumHeroPrestige,DictFunctionEnumHeroQuality,DictFunctionEnumHeroStar,DictFunctionEnumEquipHarden,DictFunctionEnumHeroEquip,DictFunctionEnumEquipForge);
        arrows->setTexture(IMG_PUBLIC_MENUBTN_UP);
        for (int i=0; i<firstBtnNum; i++) {
            this->setBarVisible(btnList->at(i));
//            btnList->at(i)->setVisible(true);
        }
        btnList->at(firstBtnNum)->stopAllActions();
        btnList->at(firstBtnNum)->runAction(seq2);
        for (int i=firstBtnNum+1; i<btnList->size(); i++) {
            btnList->at(i)->stopAllActions();
            btnList->at(i)->runAction(spawn->clone());
        }
    }
}
void HomeMenuBar::barAction2()
{
    Button* bookBtn=(Button*)this->getChildByTag(TAG_BOOKBTN);
    if (!bookBtn) {
        return;
    }
    CallFunc* callBack = NULL;
    if(NewPlayerGuild::getInstance()->getNowData() && NewPlayerGuild::getInstance()->getNowData()->bottomId == DictNewGuideEventEnumScrollButton)
    {
        callBack = CallFunc::create(CC_CALLBACK_0(NewPlayerGuild::next, NewPlayerGuild::getInstance(),DictNewGuideEventEnumScrollButton));
    }
    for (int i=0; i<firstBtnNum; i++) {
        btnList->at(i)->setVisible(false);
    }
    for (int i=firstBtnNum; i<btnList->size(); i++) {
        btnList->at(i)->stopAllActions();
        btnList->at(i)->setPosition(bookBtn->getPosition());
        this->setBarVisible(btnList->at(i));
//        btnList->at(i)->setVisible(true);
        ActionInterval* move=MoveTo::create(0.3, Point(pointList->at(i)));
        ActionInterval* fade=FadeIn::create(0.3);
        FiniteTimeAction * spawn = Spawn::create(move,fade,NULL);
        btnList->at(i)->runAction(spawn);
    }
    if(callBack)
    {
        bookBtn->runAction(Sequence::create(DelayTime::create(.4),callBack, NULL));
    }
}
void HomeMenuBar::barAction3()
{
    Button* bookBtn=(Button*)this->getChildByTag(TAG_BOOKBTN);
    if (!bookBtn) {
        return;
    }
    for (int i=firstBtnNum; i<btnList->size(); i++) {
        btnList->at(i)->setVisible(false);
    }
}
void HomeMenuBar::setBarVisible(Node* node)
{
    int tag=node->getTag();
    switch (tag) {
        case LAYER_PRAY:
            if (!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumLucky))
                return;
            break;
        case MENUBAR_TASK:
            if (!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumTaskCommon))
                return;
            break;
        case LAYER_MARKET_JUXIAN:
            if (!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumLead))
                return;
            break;
        case LAYER_MARKET_PAIMAI:
            if (!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumMarket))
                return;
            
            break;
        case LAYER_LIMIT:
            if (!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumLegend))
                return;
//
            break;
//        case MENUBAR_BAG:
//            if (!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumLead))
//                return;
//          
//            break;
        case LAYER_ZHENRONG:
            if (!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumLineup))
                return;
            break;
        case LAYER_FIGHT:
            if (!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumArena))
                return;
      
//        case LAYER_EQUIP:
//            if (!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumLead))
//                return;
//            break;
//        case LAYER_WEAL:
//            if (!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumLead))
//                return;
//            break;
            //
        default:
            break;
    }
    node->setVisible(true);
}
void HomeMenuBar::onRefreshDot(EventCustom* msg)
{
//    __Integer* inter = (__Integer*)msg->getUserData();
//    int tag_index = inter->getValue();
}

void HomeMenuBar::addEventListener()
{
//    addUserMsg(CUSTOM_REFRESH_DOT, CC_CALLBACK_1(HomeMenuBar::onRefreshDot, this));
}
void HomeMenuBar::removeEventListener()
{
    BaseLayer::removeEventListener();
}