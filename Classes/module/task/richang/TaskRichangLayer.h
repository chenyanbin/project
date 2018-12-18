//
//  TaskRichangLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/8/17.
//
//

#ifndef __FightPass__TaskRichangLayer__
#define __FightPass__TaskRichangLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include "../../../net/bytestream.h"
#include "../data/TaskData.h"
class ProgressPrize;
class TaskRichangLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    enum state
    {
        TAG_QIANWANGBTN = 1,//前往
        TAG_GOUMAIBTN,//购买
        TAG_LINGJIANGBTN//领奖
    };
    
    TaskRichangLayer();
    ~TaskRichangLayer();
    static TaskRichangLayer* create();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
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
    void setProgress();//设置进度条
    void sethuise(Ref* psender);
    void requestTaskList();
    void submitTask(int taskID);
    void onMsgProcess(EventCustom* msg);
    void parseTaskList(ByteStream* byteStream);
    void parseTaskPrize(ByteStream* byteStream);
    void onGetProgressPrize(int conID,int conVal);
    void onHeadClick(Node* pSender);
    void onHeadClick2(Node* pSender);
private:
    Sprite* listBg;
    TableView* _tableView;
  
    int m_progress;//完成进度
    int expAdd;
    int coinAdd;
    Vector<TaskData*>* taskList;
   
    Vector<ProgressPrize*>* progressList;
    ProgressTimer* progressTimer;
private:
    int TAG_PROGRESS;
    int TAG_NOWJIFEN;
};
//进度奖励数据
class ProgressPrize:public Ref
{
public:
    ProgressPrize():progressId(0),progress(0),status(0)
    {
        
    }
    ~ProgressPrize()
    {
        
    }
public:
    int progressId;//进度奖励id
    int progress;//当前进度 100% = 100
    int status;//Y	1未领取 2已领取    3可领取
  
};
#endif /* defined(__FightPass__TaskRichangLayer__) */
