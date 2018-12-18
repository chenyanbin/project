//
//  MarketFindLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/8/3.
//
//  寻访层

#ifndef __FightPass__MarketFindLayer__
#define __FightPass__MarketFindLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "../marketData/MarketFindData.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include "../../../common/Dialog/Dialog.h"
class MarketFindLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    enum state
    {
        TAG_KAISHIXUNFANG = 1,//开始寻访
        TAG_KUAISUXUNFANG,//快速寻访
        TAG_XUNFANGWANCHENG//寻访完成     
    };

    MarketFindLayer();
    ~MarketFindLayer();
    static MarketFindLayer* create();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
private:

    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view) {};
private:
    void createTableView();
    void setBackGround();
    Sprite* singleList(ssize_t idx);
    void onkuozhanClick(Ref* psender);
    void onClick(Node* psender);//开始寻访
    void onjieguoClick(Ref* psender);//寻访结果
    void addGoodsLayer();
    void onHeroHeadClick(Node* psender);
    
    void onMsgProcess(EventCustom* msg);
    virtual void addEventListener();
    virtual void removeEventListener();
    void requestfindListMsg();//请求列表信息

    void requestDumpMsg(int findId);
    void ontDumpMsgProcess(EventCustom* msg);
    void setJungong();
    
    void loadPerson();
    void clearResourcePerson();
    void onDataLoaded(float percent);
    void onSureFindMsgProcess(EventCustom* msg);
    void ontSureSpeedMsgProcess(EventCustom* msg);//确认加速寻访
    void ontlingdikuozhanProcess(EventCustom* msg);
private:
    Sprite* listBg;
    TableView* _tableView;
    MarketFindData *data;
    PopupLoading* popUpLoading;
    int m_nextExtentGold;//开始寻访需要话费军工
    int TAG_TABLEVIEW;
    int m_idx;//查询id
    int m_mark;
    int TAG_JUNGONG;//军工tag
    int TAG_XUNFANGLING;//寻访令tag
    int m_jungongCount;//军工数量 （把所有涉及到军公的地方都改为铜钱）
    int m_xunfanglinCount;//寻访令数量
    int m_minHonor;//最少军功（改为最少铜钱）
    int TAG_JUNGONGPIC;
    int TAG_XUNFANGWORD;//
};

#endif /* defined(__FightPass__MarketFindLayer__) */
