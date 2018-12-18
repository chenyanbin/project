//
//  TaskData.h
//  FightPass
//
//  Created by zhangxiaobin on 15/9/28.
//
//

#ifndef TaskData_h
#define TaskData_h
#include "../../../commonData/data/ItemData.h"
class TaskData:public Ref
{
public:
    TaskData():taskID(0),prizeList(NULL),name(""),desc(""),status(0),headItemType(0)
    ,headItemId(0),headItemQuality(0),levelCanSubmit(0),function(0),funtionType(0),exp(0),coin(0),progress(0),finishValue(0),targetValue(0)
    {
        prizeList = new Vector<ItemData*>();
    }
    ~TaskData()
    {
        prizeList->clear();
        CC_SAFE_DELETE(prizeList);
        prizeList = NULL;
    }
    enum
    {
        TASK_STATE_NOFINISH = 1,//未完成
        TASK_STATE_FINISHED = 2,//可领取
        TAG_STATE_RECEIVE = 3//已完成
    };
    enum
    {
        TASK_STATE_NOABLE_SUBMIT = 0,//不可提交
        TASK_STATE_ABLE_SUBMIT = 1//可提交
    };
    enum
    {
        TASK_BUTTON_TYPE_GO = 1,//前往
        TASK_BUTTON_TYPE_BUY = 2//购买
    };
public:
    int taskID;
    string name;
    string desc;
    int status;//任务状态 1，未完成。2已完成
    int finishValue;//任务已完成目标值
    int targetValue;//任务完成目标
    int headItemType;//首选奖励图标类型 DictItemTypeEnum表里
    int headItemId;//首选奖励道具ID
    int headItemQuality;//首选奖励品质
    int levelCanSubmit;//能否提交0
    int function;//前往功能模块
    int funtionType;//前往功能类型 1前往/2购买
    int exp;//经验奖励
    int coin;//铜币奖励
    int progress;
    Vector<ItemData*>* prizeList;
    
    
};

#endif /* TaskData_h */
