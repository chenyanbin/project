//
//  TaskPutongLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/17.
//
//

#include "TaskPutongLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../protocol/Protocal.h"
#include "../../../message/Decoding/task/RequestTaskList.h"
#include "../../../message/Decoding/task/RequestSubmitTask.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../publicLayer/GotoModule.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../../commonData/enum/DictFightPropEnum.h"
#include "../../../commonData/enum/DictFunctionEnum.h"
#include "../../../commonData/dictData/DictItemHero/DictItemHeroManager.h"
#include "../../../commonData/dictData/DictStage/DictStageManager.h"
#include "../../../commonData/dictData/DictStageBattle/DictStageBattleManager.h"
#include "../../../commonData/dictData/DictTaskCommon/DictTaskCommonManager.h"
#include "../../awardBox/AwardBox_Layer.h"
#include "../../userWealth/UserEquipLayer.h"
#include "..//../../commonData/dictData/DictTaskCommonType/DictTaskCommonTypeManager.h"
#include "../../storyTalk/StoryTalkManager.h"
#include "../../../tdTalkData/TDTalkDataManager.hpp"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../../tips/TipsLayer.h"
TaskPutongLayer::TaskPutongLayer()
:listBg(NULL)
,_tableView(NULL)
,taskList(NULL)
,expAdd(0)
,coinAdd(0)
,m_submitTaskID(0)
{
    taskList = new Vector<TaskData*>();
  
}

TaskPutongLayer::~TaskPutongLayer()
{
    CC_SAFE_DELETE(taskList);
    taskList = NULL;
 
}

bool TaskPutongLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        
        this->isAnimation = false;
        setBackGround();
       
        bref = true;
    } while (false);
    return bref;
}

TaskPutongLayer* TaskPutongLayer::create()
{
    TaskPutongLayer* list = new TaskPutongLayer();
    if(list && list->init())
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void TaskPutongLayer::onEnter()
{
    BaseLayer::onEnter();
}
void TaskPutongLayer::onExit()
{
    BaseLayer::onExit();
}
void TaskPutongLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestTaskList();
}
void TaskPutongLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumTaskReceiveButton);
}

void TaskPutongLayer::setBackGround()
{
    listBg=Sprite::create(IMG_PUBLIC_LAYER_LISTBG);
    PublicShowUI::setTargetScale(listBg);
    listBg->setAnchorPoint(Point::ZERO);
    listBg->setPosition(Point::ZERO);
    this->addChild(listBg,1);
    this->setContentSize(listBg->getContentSize());
        
}
void TaskPutongLayer::createTableView()
{
    if(_tableView)
    {
        _tableView->reloadData();
        return;
    }
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*3 + 5;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(35,60);
    listBg->addChild(_tableView,2);
    
    Sprite* shade=Sprite::create(IMG_PUBLIC_TABLE_VIEW_SHADE);
    shade->setAnchorPoint(Point::ZERO);
    
    shade->setPosition(6,40);
    listBg->addChild(shade,3);
    NewPlayerGuild::getInstance()->showNowGuide();
}
Sprite* TaskPutongLayer::singleList(ssize_t idx)
{
    TaskData* taskData = taskList->at(idx);
    Sprite*layerBg = Sprite::create(IMG_TASK_ITEMBG);
    layerBg->setAnchorPoint(Point::ZERO);
    

    Sprite*titlebg = Sprite::create(IMG_PUBLIC_LAYER__CELLTITLEBG);
    titlebg->setAnchorPoint(Point::ZERO);
    titlebg->setPosition(177,layerBg->getContentSize().height - titlebg->getContentSize().height-10);
    layerBg->addChild(titlebg);
    
    //头像
  
    DictTaskCommon* task = DictTaskCommonManager::getInstance()->getData(taskData->taskID);
    Node* head = PublicShowUI::getIconByTypeID(taskData->headItemType, taskData->headItemId, taskData->headItemQuality);
    head->setAnchorPoint(Point::ZERO);
    head->setPosition(33,10);
    layerBg->addChild(head,1);
    
    //任务奖励
    Sprite*tpriceword = Sprite::create(IMG_TASK_TASTPRICE);
    tpriceword->setAnchorPoint(Point::ZERO);
    tpriceword->setPosition(177,20);
    layerBg->addChild(tpriceword,5);
    
    //名字

    Label* nameLabel = PublicShowUI::getLabel(taskData->name.c_str(),PublicShowUI::getColor3b(COLOR_BLUE_FLOUR),22,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(head->getPositionX() + head->getContentSize().width + 35,layerBg->getContentSize().height/2+25);
    layerBg->addChild(nameLabel,2);
    //内容
    Label* nameLabel1 = PublicShowUI::getLabel(taskData->desc.c_str(),PublicShowUI::getColor3b(COLOR_YELLOW_FLOUR),16,false,false);
    nameLabel1->setAnchorPoint(Point::ZERO);
    nameLabel1->setPosition(nameLabel->getPositionX() + nameLabel->getContentSize().width + 25,layerBg->getContentSize().height/2+25);
    layerBg->addChild(nameLabel1,2);
    string str = "";
    if(task)
    {
        str = "提交等级:" + PublicShowUI::numberToString(task->level);
        Label* submitLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_NORMAL_YELLOW),16,false,false);
        submitLabel->setAnchorPoint(Point::ZERO);
        submitLabel->setPosition(nameLabel1->getPositionX() + nameLabel1->getContentSize().width + 5,nameLabel1->getPositionY());
        layerBg->addChild(submitLabel,2);
    }
   
    //奖品
    ssize_t len = taskData->prizeList->size();
    ItemData* itemData = NULL;
    UserEquipLayer* equipLayer = NULL;
    float _scale = .8;
    for (int i =0 ; i< len; i++)
    {
        itemData = taskData->prizeList->at(i);
        
        str = PublicShowUI::getGoods(itemData->itemType, itemData->itemId);
        if(str == "")
        {
            continue;
        }
        equipLayer = UserEquipLayer::create(str,itemData->itemQuality,false);
        equipLayer->setAnchorPoint(Point::ZERO);
        if (i == 0) {
            equipLayer->addTouchBegainCallBack(this, callfuncN_selector(TaskPutongLayer::onHeadClick));
        }else if (i == 1)
        {
            equipLayer->addTouchBegainCallBack(this, callfuncN_selector(TaskPutongLayer::onHeadClick2));
        }
        if(itemData->itemType == DictItemTypeEnumItemMater)
        {
            equipLayer->setFragment();
        }
        else if(itemData->itemType == DictItemTypeEnumItemBook)
        {
            equipLayer->setLetterFragment();
        }
        _scale = 70 / equipLayer->getContentSize().width;
        equipLayer->setScale(_scale);
        equipLayer->setPosition(i*(equipLayer->getContentSize().width * _scale +50)+250, 5);
        layerBg->addChild(equipLayer,5,idx);
        string numCard = StringUtils::format("x%d",itemData->itemCount);
        Label* numLabel = PublicShowUI::getLabel(numCard.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18 / _scale,false,false);
        numLabel->setAnchorPoint(Point::ZERO);
        numLabel->setPosition(equipLayer->getContentSize().width+5,0);
        equipLayer->addChild(numLabel,10);
        
        
    }
//    str = "EXP" ;
//    Label* expLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),22,false,false);
//    expLabel->setAnchorPoint(Point::ZERO);
//    layerBg->addChild(expLabel);
//    Size size = expLabel->getContentSize();
//    size.width = expLabel->getPositionX() + expLabel->getContentSize().width;
//    expLabel->setContentSize(size);
//    if(equipLayer)
//    {
//        expLabel->setPosition(equipLayer->getPositionX() + equipLayer->getContentSize().width , nameLabel1->getPositionY() - expLabel->getContentSize().height - 60 );
//    }
//    else
//    {
//        expLabel->setPosition(250,nameLabel1->getPositionY() - expLabel->getContentSize().height - 60);
//    }
//    
//    str = " X" + PublicShowUI::numberToString(taskData->exp);
//    Label* expcount = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
//    expcount->setAnchorPoint(Point::ZERO);
//    expcount->setPosition(expLabel->getPositionX()+expLabel->getContentSize().width,expLabel->getPositionY());
//    layerBg->addChild(expcount);
//
//    
//    Sprite* iconSpr = Sprite::create(IMG_ICON_PUBLIC_COIN);
//    iconSpr->setAnchorPoint(Point::ZERO);
//    iconSpr->setScale(.75);
//    layerBg->addChild(iconSpr);
//    iconSpr->setPosition(expcount->getPositionX()+expcount->getContentSize().width+10 , expcount->getPositionY() - 5 );
////
//    str = " X" + PublicShowUI::numberToString(taskData->coin);
//    Label* coinLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
//    coinLabel->setAnchorPoint(Point::ZERO);
//    layerBg->addChild(coinLabel,2);
//    coinLabel->setPosition(iconSpr->getPositionX() + iconSpr->getContentSize().width-20, expLabel->getPositionY());
    

    
    
    
    if (taskData->levelCanSubmit == TaskData::TASK_STATE_NOABLE_SUBMIT)//不可提交
    {
        Button* qianwangBtn = Button::create(IMG_PUBLIC_BUTTON_GOTO, "", CC_CALLBACK_1(TaskPutongLayer::onqianwangClick, this));
        qianwangBtn->setAnchorPoint(Point::ZERO);
        qianwangBtn->setPosition(layerBg->getContentSize().width-qianwangBtn->getContentSize().width-20,layerBg->getContentSize().height/2-qianwangBtn->getContentSize().height/2-5);
        layerBg->addChild(qianwangBtn,1,idx);
        if(!GuideButtonManager::getInstance()->getButton(DictNewGuideEventEnumTaskGoButton) || idx == 0)
        {
              GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumTaskGoButton);
             GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumTaskGoButton, qianwangBtn);
        }

    }
    else if (taskData->levelCanSubmit == TaskData::TASK_STATE_ABLE_SUBMIT)//可提交
    {
        Button* goumaiBtn = Button::create(IMG_PUBLIC_BUTTON_GETPRIZE, "", CC_CALLBACK_1(TaskPutongLayer::onlingjiangClick, this));
        goumaiBtn->setAnchorPoint(Point::ZERO);
        goumaiBtn->setPosition(layerBg->getContentSize().width-goumaiBtn->getContentSize().width-20,layerBg->getContentSize().height/2-goumaiBtn->getContentSize().height/2-5);
        layerBg->addChild(goumaiBtn,1,idx);
        if(idx == 0)
        {
            GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumTaskReceiveButton);
            GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumTaskReceiveButton, goumaiBtn);

        }
        if(idx >= 0)
        {//可提交的都在最上面。所以不会有前往按钮
             GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumTaskGoButton);
        }
       
    }
    return layerBg;
}
void TaskPutongLayer::onHeadClick(Node* pSender)
{
    
    ItemData* itemData = taskList->at(pSender->getTag())->prizeList->at(0);
    TipsLayer::show(itemData->itemType,itemData->itemId, itemData->itemCount);
}
void TaskPutongLayer::onHeadClick2(Node* pSender)
{
    ItemData* itemData = taskList->at(pSender->getTag())->prizeList->at(1);
    TipsLayer::show(itemData->itemType,itemData->itemId, itemData->itemCount);
}
//前往
void TaskPutongLayer::onqianwangClick(Ref* psender)
{
    log("qianwang ");
    Node* target = (Node*)psender;
    log("%d",target->getTag());
    TaskData* taskData = taskList->at(target->getTag());
     NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumTaskGoButton);
    onGoFunctionByTaskData(taskData);
   
}
void TaskPutongLayer::onGoFunctionByTaskData(TaskData* taskData)
{
    DictTaskCommon* task = DictTaskCommonManager::getInstance()->getData(taskData->taskID);
    if(task->taskType == 30 || task->taskType == 31)
    {
        int stageBattleID = atoi(task->finishCon1.c_str());
        GotoModule::param1 = __Integer::create(stageBattleID);
        GlobalInfo::getInstance()->stageMode = StageMode::kStageModeCommon;
        
        DictStageBattle* stageBattle = DictStageBattleManager::getInstance()->getData(stageBattleID);
        if(stageBattle)
        {
            GlobalInfo::getInstance()->taskInStageBattle = stageBattle->inStageId;
        }
    }
    else if(task->taskType == 32 || task->taskType == 33)
    {
        int value = atoi(task->finishCon2.c_str());
       if(task->taskType == 32)
       {
            GlobalInfo::getInstance()->taskInStageBattle = value;
       }
        GotoModule::param1 = __Integer::create(value);
    }
    if(taskData->function == DictFunctionEnumCampaignElite)
    {
      
        GlobalInfo::getInstance()->stageMode = StageMode::kStageModeBest;
    }
    
    
 
    GotoModule::gotoModuleByFunctionID(taskData->function, SCENE_TAG_TASK);
}
//购买
void TaskPutongLayer::onGoumaiClick(Ref* psender)
{
}
//领奖
void TaskPutongLayer::onlingjiangClick(Ref* psender)
{
    log("lingjiang");
    Node* target = (Node*)psender;
    log("%d",target->getTag());
    TaskData* taskData = taskList->at(target->getTag());
    submitTask(taskData->taskID);
  
}


TableViewCell* TaskPutongLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Sprite* list=singleList(idx);
    list->setAnchorPoint(Point::ZERO);
    cell->addChild(list);
    cell->setContentSize(list->getContentSize());
    cell->setTag(idx);
    
    return cell;
}

//列表大小
Size TaskPutongLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    if(cellSize.height == 0)
    {
         Sprite* temp = Sprite::create(IMG_TASK_ITEMBG);
        cellSize = temp->getContentSize();
        cellSize.height += 10;
    }

    return cellSize;
}
//获取view的长度
ssize_t TaskPutongLayer::numberOfCellsInTableView(TableView *table)
{
    return taskList->size();
}
//点击cell事件
void TaskPutongLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    log("%d",cell->getTag());
}
void TaskPutongLayer::requestTaskList()
{
    Dialog::showServerLoading(1);
    RequestTaskList* msg = new RequestTaskList();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
    

}
void TaskPutongLayer::submitTask(int taskID)
{
    Dialog::showServerLoading(.5);
    m_submitTaskID = taskID;
    RequestSubmitTask* msg = new RequestSubmitTask(taskID);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void TaskPutongLayer::onMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(!message->state)
    {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_TASK_TaskCommonPageResp)
    {
        parseTaskList(message->byteStream);
        if(m_submitTaskID)
        {
             NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumTaskReceiveButton);
        }
        
         m_submitTaskID = 0;
    }
    else if(message->messageID == SCENSE_CLIENT_TASK_TaskCommonRewardResp)
    {
        parseTaskPrize(message->byteStream);
        if(m_submitTaskID)
        {
            TDTalkDataManager::getInstance()->onMissionCompleted(PublicShowUI::numberToString(m_submitTaskID).c_str());
            StoryTalkManager::getInstance()->onTaskFinished(m_submitTaskID);
        }
        requestTaskList();
    }
    
}
void TaskPutongLayer::parseTaskList(ByteStream* byteStream)
{
    int len = byteStream->get();
    taskList->clear();
    TaskData* taskData = NULL;
    for(int i =0; i < len; i++)
    {
        taskData = new TaskData();
        taskData->autorelease();
        taskData->taskID = byteStream->getInt();
        taskData->name = byteStream->getUTF8();
        taskData->desc = byteStream->getUTF8();
        taskData->status = byteStream->get();
        taskData->headItemType = byteStream->get();
        taskData->headItemId = byteStream->getInt();
        taskData->headItemQuality = byteStream->get();
        taskData->headItemQuality = taskData->headItemQuality == 0 ? 1 : taskData->headItemQuality ;
        taskData->levelCanSubmit = byteStream->get();
        taskData->function = byteStream->get();
     
        taskData->funtionType = byteStream->get();
        taskData->exp = byteStream->getInt();
        taskData->coin = byteStream->getInt();
        int rewardCount = byteStream->get();
        for(int j = 0; j < rewardCount; j++)
        {
            ItemData* itemData = new ItemData();
            itemData->autorelease();
            itemData->itemType = byteStream->get();
            itemData->itemId = byteStream->getInt();
            itemData->itemCount = byteStream->getInt();
            itemData->itemQuality = byteStream->get();
            itemData->itemQuality = itemData->itemQuality == 0 ? 1 : itemData->itemQuality;
            taskData->prizeList->pushBack(itemData);
        }
         TDTalkDataManager::getInstance()->onMissionBegain(PublicShowUI::numberToString(taskData->taskID).c_str());
        taskList->pushBack(taskData);
    }
    createTableView();
}
void TaskPutongLayer::parseTaskPrize(ByteStream* byteStream)
{
    this->expAdd = byteStream->getInt();
    this->coinAdd = byteStream->getInt();
    TDTalkDataManager::getInstance()->onReward(coinAdd, "普通任务铜币奖励");
    int oldLevel = byteStream->getInt();
    int newLevel = byteStream->getInt();
    CommonMsgProcesser::onUserLevelUp(newLevel, oldLevel);
    int len = byteStream->get();
    BaseTypeData* itemData = NULL;
    Vector<BaseTypeData*>* itemPrizeList = new Vector<BaseTypeData*>();
    for(int i = 0; i < len; i++)
    {
        itemData = new BaseTypeData();
        itemData->autorelease();
        
        itemData->dataType = byteStream->get();
        itemData->dataId = byteStream->getInt();;
        itemData->dataCount = byteStream->getInt();
        itemData->dataQuality = byteStream->get();
        itemData->dataQuality = itemData->dataQuality == 0 ? 1 : itemData->dataQuality;
        itemData->dataName = PublicShowUI::getName(itemData->dataType, itemData->dataId );
        itemPrizeList->pushBack(itemData);
    }
    
    if(itemPrizeList->size())
    {
        AwardBox_Layer* layer=AwardBox_Layer::create(itemPrizeList);
        layer->setAnchorPoint(Point::ZERO);
        layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
        Scene* scene=Director::getInstance()->getRunningScene();
        scene->addChild(layer,SCENE_POPLAYER_ZORDER);
        broadMsg(CUSTOM_REFRESH_DOT,__Integer::create(DictFunctionEnumTaskCommon));
    }
    else
    {
        CC_SAFE_DELETE(itemPrizeList);
        itemPrizeList = NULL;
    }
    
  
}
void TaskPutongLayer::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_TASK_TaskCommonPageResp).c_str(), CC_CALLBACK_1(TaskPutongLayer::onMsgProcess, this));
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_TASK_TaskCommonRewardResp).c_str(), CC_CALLBACK_1(TaskPutongLayer::onMsgProcess, this));
}
void TaskPutongLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}