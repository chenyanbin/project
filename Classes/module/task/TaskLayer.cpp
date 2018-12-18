//
//  TaskLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/17.
//
//

#include "TaskLayer.h"
#include "../userWealth/UserWealthLayer.h"

#include "putong/TaskPutongLayer.h"
#include "richang/TaskRichangLayer.h"
#include "../newPlayerGuide/NewPlayerGuild.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "../../commonData/data/FunctionOpenManager.h"
#include "../../common/Dialog/Dialog.h"
#include "../dot/RefreshDot.h"
#include "../../protocol/UserCustomEvent.h"
TaskLayer::TaskLayer()
:m_tagLayer(0)
,TAG_NAMEBG(2)
,TAG_RIGHTBTN(3)
{
    
}
TaskLayer::~TaskLayer()
{
//    log("~taaskLayer");
}

bool TaskLayer::init(int openLayer)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        m_tagLayer = openLayer;
        float sx = GlobalInfo::getInstance()->screenScaleX;
        this->setBackBtn(0,15*sx,true);
        setbackGround();
        setUserWealth();
        setRightBtn();
        this->isAbleGuiding = false;
        bref = true;
    } while (false);
    return bref;
    
}
TaskLayer* TaskLayer::create(int openLayer)
{
    TaskLayer* layer = new TaskLayer();
    if(layer && layer->init(openLayer))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void TaskLayer::show(int fromScene,int openLayer)
{
    if(openLayer == TAG_PUTONG)
    {
         if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumTaskCommon))
         {
             FunctionOpenManager::getInstance()->showNoOpenNotice();
             return;
         }
    }
    else if(openLayer == TAG_RICHANG)
    {
        if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumTaskDaily))
        {
            FunctionOpenManager::getInstance()->showNoOpenNotice();
            return;
        }
    }
    else if(openLayer == TAG_XUANSHANG)
    {
        if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumTaskWanted))
        {
            FunctionOpenManager::getInstance()->showNoOpenNotice();
            return;
        }
    }
   
    Director::getInstance()->purgeCachedData();
    TaskLayer* layer = TaskLayer::create(openLayer);
    layer->setFromScene(fromScene);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    
    Scene* scene = Scene::create();
    scene->addChild(layer,0,SCENE_TAG_TASK);
    
    Director::getInstance()->replaceScene(scene);
}
void TaskLayer::onEnter()
{
    BaseLayer::onEnter();
}

void TaskLayer::onExit()
{
    BaseLayer::onExit();
}
void TaskLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    ComboBoxBtn* btn = (ComboBoxBtn*)this->getChildByTag(TAG_RIGHTBTN);
    btn->resetAllBtn();
   
    switch(this->m_tagLayer)
    {
        case TAG_PUTONG:
            if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumTaskCommon))
            {
                FunctionOpenManager::getInstance()->showNoOpenNotice();
                return;
            }
            btn->getButtonByTag(DictFunctionEnumTaskCommon)->selected();
            addPutongLayer();
            break;
        case TAG_RICHANG:
            if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumTaskDaily))
            {
                FunctionOpenManager::getInstance()->showNoOpenNotice();
                return;
            }
             btn->getButtonByTag(DictFunctionEnumTaskDaily)->selected();
            addRichangLayer();
            break;
        case TAG_XUANSHANG:
            if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumTaskWanted))
            {
                FunctionOpenManager::getInstance()->showNoOpenNotice();
                return;
            }
             btn->getButtonByTag(DictFunctionEnumTaskWanted)->selected();
            break;
    }
}
void TaskLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumDailyTasksTab);
    Director::getInstance()->purgeCachedData();
    Director::getInstance()->getTextureCache()->removeAllTextures();
}
void TaskLayer::setbackGround()
{
    Sprite* bgSpr = Sprite::create(IMG_PUBLIC_MODULE_BG);
    PublicShowUI::setTargetScale(bgSpr,true);
    bgSpr->setAnchorPoint(Point::ZERO);
    bgSpr->setPosition(Point::ZERO);
    this->addChild(bgSpr,-2);
    
    Sprite* bgSprgray = Sprite::create(IMG_PUBLIC_MODULE_MASK_BOTTOM);
    PublicShowUI::setTargetScale(bgSprgray,true);
    bgSprgray->setAnchorPoint(Point::ZERO);
    bgSprgray->setPosition(Point::ZERO);
    this->addChild(bgSprgray,-1);
}
void TaskLayer::setUserWealth()
{
    UserWealthLayer* layer = UserWealthLayer::create(UserWealthLayer::BELONG);
    PublicShowUI::setTargetScale(layer);
    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2, VisibleRect::top().y-layer->getContentSize().height);
    this->addChild(layer,3,TAG_NAMEBG);
  }
void TaskLayer::setRightBtn()
{

    const char* path = NULL;

    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_VERTICAL, -20, CC_CALLBACK_1(TaskLayer::onRightBtnClick, this));
    int functionList[3] = {DictFunctionEnumTaskWanted,DictFunctionEnumTaskDaily,DictFunctionEnumTaskCommon};
 
    for (int i = 0; i < 3; i++)
    {
        path = PublicShowUI::getResImgPath(IMG_TASK_RIGHTBTN, PublicShowUI::numberToString(i + 1).c_str());
        if(FunctionOpenManager::getInstance()->functionIsOpened(functionList[i]))
        {
            if (functionList[i] == DictFunctionEnumTaskWanted) {
                continue;
            }
           boxBtn->addBtn(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE, IMG_PUBLIC_COMBOBOX_BTNCHOSE, path,true,functionList[i]);
//            boxBtn->getButtonByTag(functionList[i])->setVisible(false);
        }
  
    }
//    boxBtn-> getButtonByTag(DictFunctionEnumTaskWanted)->setVisible(false);//悬赏任务不开启呢
    PublicShowUI::setTargetScale(boxBtn);
    PublicShowUI::setDot(boxBtn->getButtonByTag(DictFunctionEnumTaskWanted),Point::ZERO,false,DictFunctionEnumTaskWanted);
    PublicShowUI::setDot(boxBtn->getButtonByTag(DictFunctionEnumTaskDaily),Point::ZERO,false,DictFunctionEnumTaskDaily);
    PublicShowUI::setDot(boxBtn->getButtonByTag(DictFunctionEnumTaskCommon),Point::ZERO,false,DictFunctionEnumTaskCommon);

    boxBtn->setPosition(VisibleRect::right().x - boxBtn->getContentSize().width,VisibleRect::center().y-boxBtn->getContentSize().height/2);
    this->addChild(boxBtn,3,TAG_RIGHTBTN);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumDailyTasksTab, boxBtn->getButtonByTag(DictFunctionEnumTaskDaily));
}
void TaskLayer::onRightBtnClick(Ref* psender)
{
    Node* target = (Node*)psender;
    int tag = target->getTag();
    switch (tag) {
        case DictFunctionEnumTaskWanted:
            if (m_tagLayer != TAG_XUANSHANG) {
//                this->removeChildByTag(m_tagLayer);
                addXuansahngLayer();
            }
            break;
        case DictFunctionEnumTaskDaily:
            if (m_tagLayer != TAG_RICHANG) {
                this->removeChildByTag(m_tagLayer);
                addRichangLayer();
                NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumDailyTasksTab);
            }
            break;
        case DictFunctionEnumTaskCommon:
            if (m_tagLayer != TAG_PUTONG) {
                this->removeChildByTag(m_tagLayer);
                addPutongLayer();
            }
            break;
        default:
            break;
    }

}
void TaskLayer::addPutongLayer()
{
  
    if(this->getChildByTag(TAG_PUTONG))
    {
        return;
    }
    Dialog::showServerLoading(1);
    m_tagLayer = TAG_PUTONG;
    float sx = GlobalInfo::getInstance()->screenScaleX;
    TaskPutongLayer* choseLayer = TaskPutongLayer::create();
    choseLayer->setAnchorPoint(Point::ZERO);
    choseLayer->setPositionX(VisibleRect::center().x-choseLayer->getContentSize().width/2 - 40 * sx);
    choseLayer->setPositionY(VisibleRect::center().y - choseLayer->getContentSize().height/2 -30*sx );
    this->addChild(choseLayer, 2,TAG_PUTONG);

    UserWealthLayer* topBg=(UserWealthLayer*)this->getChildByTag(TAG_NAMEBG);
    topBg->setTitle(IMG_PUBLIC_RENWU);

    log("putong");
}
void TaskLayer::addRichangLayer()
{
    if(this->getChildByTag(TAG_RICHANG))
    {
        return;
    }
     Dialog::showServerLoading(1);
    m_tagLayer = TAG_RICHANG;
    float sx = GlobalInfo::getInstance()->screenScaleX;
    TaskRichangLayer* choseLayer = TaskRichangLayer::create();
    choseLayer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(choseLayer);
    choseLayer->setPositionX(VisibleRect::center().x-choseLayer->getContentSize().width/2 - 40 * sx);
    choseLayer->setPositionY(VisibleRect::center().y - choseLayer->getContentSize().height/2 -30*sx );
    this->addChild(choseLayer, 2,TAG_RICHANG);
    
    UserWealthLayer* topBg=(UserWealthLayer*)this->getChildByTag(TAG_NAMEBG);
    topBg->setTitle(IMG_PUBLIC_RENWU);

    log("richang");

    
}
void TaskLayer::addXuansahngLayer()
{
    if(this->getChildByTag(TAG_XUANSHANG))
    {
        return;
    }
    NoticeManager::getInstance()->showNotice("精彩竞请期待！");
   
    return;
    m_tagLayer = TAG_XUANSHANG;
    log("xuanshang");
   
}
void TaskLayer::onRefreshDot(EventCustom* msg)
{
    ComboBoxBtn* boxBtn = (ComboBoxBtn*)this->getChildByTag(TAG_RIGHTBTN);
    __Integer* inter = (__Integer*)msg->getUserData();
    if(!inter)
    {
        return;
    }
    int tag_index = inter->getValue();
    if (tag_index == DictFunctionEnumTaskCommon) {
        RefreshDot::getInstance()->requestMsg(boxBtn->getButtonByTag(DictFunctionEnumTaskCommon),Point(10,10),false,DictFunctionEnumTaskCommon);
    }else if (DictFunctionEnumTaskDaily)
    {
        RefreshDot::getInstance()->requestMsg(boxBtn->getButtonByTag(DictFunctionEnumTaskDaily),Point(10,10),false,DictFunctionEnumTaskDaily);
    }
}
void TaskLayer::addEventListener()//添加监听
{
    addUserMsg(CUSTOM_REFRESH_DOT, CC_CALLBACK_1(TaskLayer::onRefreshDot, this));
}
void TaskLayer::removeEventListener()//清除监听
{
    BaseLayer::removeEventListener();
}
