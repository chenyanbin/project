//
//  TaskRichangLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/17.
//
//

#include "TaskRichangLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../message/Decoding/task/RequestDailyTaskList.h"
#include "../../../message/Decoding/task/RequestSubmitDailyTask.h"
#include "../../../message/Decoding/task/RequestProgressPrize.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../commonData/dictData/DictTaskDay/DictTaskDayManager.h"
#include "../../../commonData/dictData/DictStageBattle/DictStageBattleManager.h"
#include "../../publicLayer/GotoModule.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../commonData/enum/DictRolePropEnum.h"
#include "../../../commonData/enum/DictFunctionEnum.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../data/BaseTypeData.h"
#include "../../awardBox/AwardBox_Layer.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../tips/TipsLayer.h"
#include "../../../tdTalkData/TDTalkDataManager.hpp"
TaskRichangLayer::TaskRichangLayer()
:listBg(NULL)
,_tableView(NULL)
,taskList(NULL)
,expAdd(0)
,coinAdd(0)
,progressList(NULL)
,m_progress(0)
,progressTimer(NULL)
,TAG_PROGRESS(1)
,TAG_NOWJIFEN(2)
{
    taskList = new Vector<TaskData*>();
   
    progressList = new Vector<ProgressPrize*>();
}

TaskRichangLayer::~TaskRichangLayer()
{
    CC_SAFE_DELETE(taskList);
    taskList = NULL;
 
    CC_SAFE_DELETE(progressList);
    progressList = NULL;
    progressTimer = NULL;
}

bool TaskRichangLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        
        this->isAnimation = false;
        setBackGround();

        Sprite* lineSpr = Sprite::create(IMG_TASK_RICAHNG_LINE);
        lineSpr->setAnchorPoint(Point::ZERO);
        lineSpr->setPosition(30,50);
        this->addChild(lineSpr,1);
        bref = true;
    } while (false);
    return bref;
}

TaskRichangLayer* TaskRichangLayer::create()
{
    TaskRichangLayer* list = new TaskRichangLayer();
    if(list && list->init())
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void TaskRichangLayer::onEnter()
{
    BaseLayer::onEnter();
}
void TaskRichangLayer::onExit()
{
    BaseLayer::onExit();
}
void TaskRichangLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestTaskList();
}
void TaskRichangLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void TaskRichangLayer::requestTaskList()
{
    Dialog::showServerLoading(.5);
    RequestDailyTaskList* msg = new RequestDailyTaskList();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void TaskRichangLayer::submitTask(int taskID)
{
    Dialog::showServerLoading(.5);
    RequestSubmitDailyTask* msg = new RequestSubmitDailyTask(taskID);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void TaskRichangLayer::setBackGround()
{
    listBg=Sprite::create(IMG_PUBLIC_LAYER_LISTBG);
    listBg->setAnchorPoint(Point::ZERO);
    listBg->setPosition(Point::ZERO);
    this->addChild(listBg,1);
    this->setContentSize(listBg->getContentSize());
    this->setSwallowsTouches(true);
}
void TaskRichangLayer::setProgress()
{

    Node* progressSpr = this->getChildByTag(TAG_PROGRESS);
    if(progressSpr)
    {
        progressSpr->removeAllChildren();
    }
    else
    {
        progressSpr = Node::create();
        progressSpr->setAnchorPoint(Point::ZERO);
        progressSpr->setPosition(163, 75);
        this->addChild(progressSpr,9,TAG_PROGRESS);
    }
    
    int len = progressList->size();
    ProgressPrize* prize = NULL;
    float percentList[4] = {20,45,75,100};
    for (int i = 0; i < 4 ; i ++)
    {
        if(i < len)
        {
             prize = progressList->at(i);
        }
       
        Sprite* jifenBg = Sprite::create(IMG_TASK_RICAHNG_JIFENBG);
        jifenBg->setAnchorPoint(Point::ZERO);
        float xx = 654 * (percentList[i] / 100) - jifenBg->getContentSize().width/2;
        
        jifenBg->setPositionX(xx);
//        jifenBg->setPosition(i * (jifenBg->getContentSize().width+120),0);
        progressSpr->addChild(jifenBg,2,i);
        int progress = prize ? prize->progress : (i +1) * 20;
        string numCard = StringUtils::format("%d",progress);
        Label* numLabel = PublicShowUI::getLabel(numCard.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),13,false,false);
        numLabel->setAnchorPoint(Point(0.5,0));
        numLabel->setPosition(jifenBg->getContentSize().width/2,17);
        jifenBg->addChild(numLabel,2);
        
        const char* path = (prize && prize->status == 2) ? IMG_PUBLIC_BOXOPEN : IMG_PUBLIC_BOXCLOSE;
        Button* box = Button::create(path, "", CC_CALLBACK_1(TaskRichangLayer::sethuise, this));
        box->setAnchorPoint(Point(.5,0));
        box->setScale(0.3);
        box->setPosition(jifenBg->getContentSize().width /2 + 4, jifenBg->getContentSize().height - 15);
        jifenBg->addChild(box,5 + i,i);
        if(prize && prize->status == 3)
        {
            PublicShowUI::setTargetSwing(box);
        }
        else if(prize && prize->status == 2)
        {
            box->setEnabled(false);
        }
    }
     string numCard = StringUtils::format("%d",this->m_progress);
    Sprite* jifenSpr = (Sprite*)this->getChildByTag(TAG_NOWJIFEN);
    Label* numLabel = NULL;
    if(jifenSpr)
    {
        numLabel = (Label*)jifenSpr->getChildByTag(TAG_NOWJIFEN);
        numLabel->setString(numCard);
    }
    else
    {
        Sprite* jifenSpr = Sprite::create(IMG_TASK_RICAHNG_JIFEN);
        jifenSpr->setAnchorPoint(Point::ZERO);
        jifenSpr->setPosition(50,67);
        this->addChild(jifenSpr,1,TAG_NOWJIFEN);
       
        numLabel = PublicShowUI::getLabel(numCard.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
        numLabel->setAnchorPoint(Point(0.5,0));
        numLabel->setPosition(jifenSpr->getContentSize().width/2,52);
        jifenSpr->addChild(numLabel,2,TAG_NOWJIFEN);
    }
    
    
    if(this->progressTimer)
    {
        progressTimer->stopAllActions();
        progressTimer->runAction(ProgressFromTo::create(.4, progressTimer->getPercentage(), m_progress));
        return;
    }
    /////////////
    
 

    Sprite* downProSpr = Sprite::create(IMG_TASK_RICAHNG_DOWNPROGRESS);
    downProSpr->setAnchorPoint(Point::ZERO);
    downProSpr->setPosition(163,65);
    this->addChild(downProSpr,2);
    
    
    Sprite* progress = Sprite::create(IMG_TASK_RICAHNG_UPPROGRESS);
    progress->setAnchorPoint(Point::ZERO);
    this->progressTimer = ProgressTimer::create(progress);
    progressTimer->setType(ProgressTimer::Type::BAR);
    progressTimer->setMidpoint(Point(0,1));
    progressTimer->setBarChangeRate(Point(1,0));
    progressTimer->setAnchorPoint(Point::ZERO);
    progressTimer->setPosition(0,(downProSpr->getContentSize().height - progressTimer->getContentSize().height)/2);
    progressTimer->setPercentage(this->m_progress);
    downProSpr->addChild(progressTimer);
   
}
void TaskRichangLayer::sethuise(Ref* psender)
{
    
    Button* target = (Button*)psender;
    int index = target->getTag();
    if(index >= progressList->size())
    {
        NoticeManager::getInstance()->showNotice("您的完成度还不够哦。");
        return;
    }
    ProgressPrize* prize = progressList->at(index);
    if(prize->status == 2)
    {
        NoticeManager::getInstance()->showNotice("已经开启此宝箱。");
        return;
    }
    if(prize->status == 3)
    {
        RequestProgressPrize* msg = new RequestProgressPrize(prize->progressId);
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg= NULL;
        
        target->setNormalImage(IMG_PUBLIC_BOXOPEN);
        target->setEnabled(false);
        target->setAnchorPoint(Point(.5,0));
//        target->setScale(0.3);
    }
    else
    {
        NoticeManager::getInstance()->showNotice("不能领取该宝箱");
    }
  
    PublicShowUI::stopTargetSwing(target);
 
}
void TaskRichangLayer::createTableView()
{
    if(_tableView)
    {
        _tableView->reloadData();
        return;
    }
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*2 + 55;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(35,170);
    listBg->addChild(_tableView,2);
    
    Sprite* shade=Sprite::create(IMG_PUBLIC_TABLE_VIEW_SHADE);
    shade->setAnchorPoint(Point::ZERO);
    shade->setPosition(6,40);
    listBg->addChild(shade,3);
}
Sprite* TaskRichangLayer::singleList(ssize_t idx)
{
    TaskData* taskData = taskList->at(idx);
    Sprite*layerBg = Sprite::create(IMG_TASK_ITEMBG);
    layerBg->setAnchorPoint(Point::ZERO);
    
    Sprite*titlebg = Sprite::create(IMG_PUBLIC_LAYER__CELLTITLEBG);
    titlebg->setAnchorPoint(Point::ZERO);
    titlebg->setPosition(177,layerBg->getContentSize().height - titlebg->getContentSize().height-10);
    layerBg->addChild(titlebg);
    
    //任务奖励
    Sprite*tpriceword = Sprite::create(IMG_TASK_TASTPRICE);
    tpriceword->setAnchorPoint(Point::ZERO);
    tpriceword->setPosition(177,20);
    layerBg->addChild(tpriceword,5);
    
    //头像
    Node* head = PublicShowUI::getIconByTypeID(taskData->headItemType, taskData->headItemId, taskData->headItemQuality);
    if(head)
    {
        head->setAnchorPoint(Point::ZERO);
        head->setPosition(33,10);
        layerBg->addChild(head,1);
    }
    
    
    DictTaskDay* task = DictTaskDayManager::getInstance()->getData(taskData->taskID);
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
    
    string str = StringUtils::format("任务完成进度%d/%d",taskData->finishValue,taskData->targetValue);
//    string str = "提交等级:" + PublicShowUI::numberToString(task->level);
    Label* submitLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_NORMAL_YELLOW),16,false,false);
    submitLabel->setAnchorPoint(Point::ZERO);
    submitLabel->setPosition(nameLabel1->getPositionX() + nameLabel1->getContentSize().width + 5,nameLabel1->getPositionY());
    layerBg->addChild(submitLabel,2);

    UserEquipLayer* equipLayer = NULL;
    ssize_t len = taskData->prizeList->size();
    ItemData* itemData = NULL;
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
            equipLayer->addTouchBegainCallBack(this, callfuncN_selector(TaskRichangLayer::onHeadClick));
        }else if (i == 1)
        {
            equipLayer->addTouchBegainCallBack(this, callfuncN_selector(TaskRichangLayer::onHeadClick2));
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
        layerBg->addChild(equipLayer,10,idx);
        string numCard = StringUtils::format("x%d",itemData->itemCount);
        Label* numLabel = PublicShowUI::getLabel(numCard.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18 / _scale,false,false);
        numLabel->setAnchorPoint(Point::ZERO);
        numLabel->setPosition(equipLayer->getContentSize().width+5,0);
        equipLayer->addChild(numLabel,10);
        
    }
    str = "积分X" + PublicShowUI::numberToString(taskData->progress);

    Label* coinLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18 ,false,false);
    coinLabel->setAnchorPoint(Point::ZERO);

    layerBg->addChild(coinLabel);
    if(equipLayer)
    {
        coinLabel->setPosition(equipLayer->getPositionX() + equipLayer->getContentSize().width + 20, equipLayer->getPositionY());
    }
    else
    {
        coinLabel->setPosition(250,5);
    }

    if (taskData->status == TaskData::TASK_STATE_NOFINISH)//不可提交
    {
        Button* qianwangBtn = Button::create(IMG_PUBLIC_BUTTON_GOTO, "", CC_CALLBACK_1(TaskRichangLayer::onqianwangClick, this));
        qianwangBtn->setAnchorPoint(Point::ZERO);
        qianwangBtn->setPosition(layerBg->getContentSize().width-qianwangBtn->getContentSize().width-40,layerBg->getContentSize().height/2-qianwangBtn->getContentSize().height/2-20);
        layerBg->addChild(qianwangBtn,1,idx);
    }
    else if (taskData->status == TaskData::TASK_STATE_FINISHED)//可提交
    {
        Button* goumaiBtn = Button::create(IMG_PUBLIC_BUTTON_GETPRIZE, "", CC_CALLBACK_1(TaskRichangLayer::onlingjiangClick, this));
        goumaiBtn->setAnchorPoint(Point::ZERO);
        goumaiBtn->setPosition(layerBg->getContentSize().width-goumaiBtn->getContentSize().width-40,layerBg->getContentSize().height/2-goumaiBtn->getContentSize().height/2-20);
        layerBg->addChild(goumaiBtn,1,idx);
        
    }
    else if (taskData->status == TaskData::TAG_STATE_RECEIVE)//已完成
    {
        Sprite* succeed = Sprite::create(IMG_PUBLIC_LABEL_BASE_SUCCEED);
        succeed->setAnchorPoint(Point::ZERO);
        succeed->setPosition(layerBg->getContentSize().width-succeed->getContentSize().width-20,layerBg->getContentSize().height/2-succeed->getContentSize().height/2);
        layerBg->addChild(succeed,1,idx);
        log("lsdfjlsf");
    }
    return layerBg;
}
void TaskRichangLayer::onHeadClick(Node* pSender)
{
    
    ItemData* itemData = taskList->at(pSender->getTag())->prizeList->at(0);
    TipsLayer::show(itemData->itemType,itemData->itemId, itemData->itemCount);
}
void TaskRichangLayer::onHeadClick2(Node* pSender)
{
    ItemData* itemData = taskList->at(pSender->getTag())->prizeList->at(1);
    TipsLayer::show(itemData->itemType,itemData->itemId, itemData->itemCount);
}

//前往
void TaskRichangLayer::onqianwangClick(Ref* psender)
{
    
    
    
    Node* target = (Node*)psender;
    log("%d",target->getTag());
    TaskData* taskData = taskList->at(target->getTag());
    
    DictTaskDay* task = DictTaskDayManager::getInstance()->getData(taskData->taskID);
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

    GotoModule::gotoModuleByFunctionID(taskData->function, SCENE_TAG_DAILYTASK);
}

//购买
void TaskRichangLayer::onGoumaiClick(Ref* psender)
{

}
//领奖
void TaskRichangLayer::onlingjiangClick(Ref* psender)
{
    log("lingjiang");
    Node* target = (Node*)psender;
    log("%d",target->getTag());
    TaskData* taskData = taskList->at(target->getTag());
    submitTask(taskData->taskID);
}


TableViewCell* TaskRichangLayer::tableCellAtIndex(TableView *table, ssize_t idx)
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
Size TaskRichangLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_TASK_ITEMBG);
    cellSize.height = temp->getContentSize().height+10;
    cellSize.width = temp->getContentSize().width ;
    return cellSize;
}
//获取view的长度
ssize_t TaskRichangLayer::numberOfCellsInTableView(TableView *table)
{
    return taskList->size();
}
//点击cell事件
void TaskRichangLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    log("%d",cell->getTag());
}

void TaskRichangLayer::onMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(!message->state)
    {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_TASK_TaskDayPageResp)
    {
        parseTaskList(message->byteStream);
        setProgress();
    }
    else if (message->messageID == SCENSE_CLIENT_TASK_TaskDayRewardResp)
    {
        parseTaskPrize(message->byteStream);
        requestTaskList();
    }
    else if(message->messageID == SCENSE_CLIENT_TASK_TaskDayProgressRewardResp)
    {
//        conId	奖励类型	byte DictRolePropEnum
//        conVal	奖励值	int
        int conID = message->byteStream->getByte();
        int conVal = message->byteStream->getInt();
//        DictRolePropEnumExp=1,//经验
//        DictRolePropEnumGold=2,//元宝
//        DictRolePropEnumCoin=3,//铜钱
//        DictRolePropEnumPower=4,//体力
//        DictRolePropEnumGlory=5,//荣誉
//        DictRolePropEnumHonor=6,//军功
//        DictRolePropEnumMoneyTreeTimes=7,//每日祈福次数
//        DictRolePropEnumPowerBuyTimes=8,//体力丹购买次数
//        DictRolePropEnumBookGiftTimes=9,//武将送礼次数
//        DictRolePropEnumSweepCommand=10,//扫荡令
//        DictRolePropEnumFindCommand=11,//寻访令
//        DictRolePropEnumRecruitCommand1=12,//求贤若渴令
//        DictRolePropEnumRecruitCommand2=13,//礼贤下士令
//        DictRolePropEnumRecruitCommand3=14,//唯才是举令
//        DictRolePropEnumHeroBelongUpPlus=15,//武将携带上限扩容
//        DictRolePropEnumEquipBelongUpPlus=16//装备携带上限扩容
        onGetProgressPrize(conID,conVal);
        
    }
}
void TaskRichangLayer::onGetProgressPrize(int conID,int propValue)
{
    std::string str = "获得了";
    switch(conID)
    {
        case DictRolePropEnumExp:
            GlobalInfo::getInstance()->gameRole->experience += propValue;
            str += "经验";
            break;
        case DictRolePropEnumGold:
            str += "元宝";
            GlobalInfo::getInstance()->userGold += propValue;
             TDTalkDataManager::getInstance()->onReward(propValue, "日常任务宝箱元宝奖励");
            break;
        case DictRolePropEnumCoin:
            str += "铜币";
            GlobalInfo::getInstance()->userCopper += propValue;
            TDTalkDataManager::getInstance()->onReward(propValue, "日常任务宝箱铜币奖励");
            break;
        case DictRolePropEnumPower:
            str += "体力";
            GlobalInfo::getInstance()->bodyPower += propValue;
            break;
        case DictRolePropEnumGlory://荣誉
            str += "荣誉";
            GlobalInfo::getInstance()->gameRole->glory += propValue;
            break;
        case DictRolePropEnumHonor://军功
            str += "军功";
            GlobalInfo::getInstance()->gameRole->expLoit += propValue;
            break;
            default:
            break;
    }
    if(propValue > 0)
    {
        str += PublicShowUI::numberToString(propValue);
        NoticeManager::getInstance()->showNotice(str.c_str(),NoticeManager::COLOR_GREEN);
        broadMsg(CUSTOM_UPDATE_USERPROP_VALUE);
    }
   broadMsg(CUSTOM_REFRESH_DOT,__Integer::create(DictFunctionEnumTaskDaily));

}
void TaskRichangLayer::parseTaskList(ByteStream* byteStream)
{
   m_progress = byteStream->getInt();
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
        taskData->finishValue = byteStream->getInt();
        taskData->targetValue = byteStream->getInt();
        taskData->headItemType = byteStream->get();
        taskData->headItemId = byteStream->getInt();
        taskData->headItemQuality = byteStream->get();
        taskData->function = byteStream->get();
        taskData->funtionType = byteStream->get();
        taskData->exp = byteStream->getInt();
        taskData->coin = byteStream->getInt();
        taskData->progress = byteStream->get();
        int rewardCount = byteStream->get();
        for(int j = 0; j < rewardCount; j++)
        {
            ItemData* itemData = new ItemData();
            itemData->autorelease();
            itemData->itemType = byteStream->get();
            itemData->itemId = byteStream->getInt();
            itemData->itemCount = byteStream->getInt();
            itemData->itemQuality = byteStream->get();
            taskData->prizeList->pushBack(itemData);
        }
        
        taskList->pushBack(taskData);
    }
    progressList->clear();
 
    len = byteStream->getByte();
    ProgressPrize* progressPrize = NULL;
    for(int i = 0; i < len; i++)
    {
        progressPrize = new ProgressPrize();
        progressPrize->autorelease();
        progressPrize->progressId = byteStream->getInt();
        progressPrize->progress = byteStream->getInt();
        progressPrize->status = byteStream->getByte();
        progressList->pushBack(progressPrize);
    }
  
    createTableView();
}
void TaskRichangLayer::parseTaskPrize(ByteStream* byteStream)
{
    this->expAdd = byteStream->getInt();
    this->coinAdd = byteStream->getInt();
    
    int oldLevel = byteStream->getInt();
    int newLevel = byteStream->getInt();
    CommonMsgProcesser::onUserLevelUp(newLevel, oldLevel);
    int len = byteStream->get();
    BaseTypeData* itemData = NULL;
    Vector<BaseTypeData*>* itemPrizeList = new Vector<BaseTypeData*>();
    progressList->clear();
    for(int i = 0; i < len; i++)
    {
        itemData = new BaseTypeData();
        itemData->autorelease();

        
        itemData->dataType = byteStream->get();
        itemData->dataId = byteStream->getInt();;
        itemData->dataCount = byteStream->getInt();
        itemData->dataQuality = byteStream->get();
        itemData->dataName = PublicShowUI::getName(itemData->dataType, itemData->dataId );

        
        itemPrizeList->pushBack(itemData);
    }
    
    len = byteStream->get();
    ProgressPrize* progressPrize = NULL;
    for(int i = 0; i < len; i++)
    {
        progressPrize = new ProgressPrize();
        progressPrize->autorelease();
        progressPrize->progressId = byteStream->getInt();
        progressPrize->progress = byteStream->getInt();
        progressPrize->status = byteStream->getByte();
        progressList->pushBack(progressPrize);
    }
    setProgress();
    if(itemPrizeList->size())
    {
        AwardBox_Layer* layer=AwardBox_Layer::create(itemPrizeList);
        layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
        Scene* scene=Director::getInstance()->getRunningScene();
        scene->addChild(layer);
        
    }
    else
    {
        CC_SAFE_DELETE(itemPrizeList);
        itemPrizeList = NULL;
    }
    broadMsg(CUSTOM_REFRESH_DOT,__Integer::create(DictFunctionEnumTaskDaily));
}
void TaskRichangLayer::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_TASK_TaskDayPageResp).c_str(), CC_CALLBACK_1(TaskRichangLayer::onMsgProcess, this));
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_TASK_TaskDayRewardResp).c_str(), CC_CALLBACK_1(TaskRichangLayer::onMsgProcess, this));
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_TASK_TaskDayProgressRewardResp).c_str(), CC_CALLBACK_1(TaskRichangLayer::onMsgProcess, this));
}
void TaskRichangLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
 
}