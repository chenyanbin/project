//
//  TaskPutongLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/8/17.
//
//

#ifndef __FightPass__TaskPutongLayer__
#define __FightPass__TaskPutongLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "../../../net/bytestream.h"
#include "../data/TaskData.h"
#include "../../data/BaseTypeData.h"
USING_NS_CC_EXT;
USING_NS_CC;

class TaskPutongLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    enum state
    {
        TAG_QIANWANGBTN = 1,//前往
        TAG_GOUMAIBTN,//购买
        TAG_LINGJIANGBTN//领奖
    };
    TaskPutongLayer();
    ~TaskPutongLayer();
    static TaskPutongLayer* create();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
    
    static void onGoFunctionByTaskData(TaskData* taskData);
protected:
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view) {};
    virtual void addEventListener();
    virtual void removeEventListener();
private:
    void createTableView();
    void setBackGround();
    Sprite* singleList(ssize_t idx);
    void onqianwangClick(Ref* psender);//前往
    void onGoumaiClick(Ref* psender);//购买
    void onlingjiangClick(Ref* psender);//领奖
    void onHeadClick(Node* pSender);
    void onHeadClick2(Node* pSender);
    
    void requestTaskList();
    void submitTask(int taskID);
    void onMsgProcess(EventCustom* msg);
    void parseTaskList(ByteStream* byteStream);
    void parseTaskPrize(ByteStream* byteStream);
private:
    Sprite* listBg;
    TableView* _tableView;
    Vector<TaskData*>* taskList;
    Size cellSize;
    int m_submitTaskID;
    int expAdd;
    int coinAdd;


};
#endif /* defined(__FightPass__TaskPutongLayer__) */
