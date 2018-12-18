//
//  HeroListBar_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/8/18.
//
//

#ifndef __FightPass__HeroListBar_Layer__
#define __FightPass__HeroListBar_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../BaseLayer.h"
#include "data/CardPropertyData.h"
#include <Vector>

USING_NS_CC_EXT;
USING_NS_CC;
class HeroListBar_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    HeroListBar_Layer();
    ~HeroListBar_Layer();
    static HeroListBar_Layer* create(int _id=-1,string sortMode="level");
    virtual bool init(int _id,string sortMode);
    virtual void onEnter();
    virtual void onExit();
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
    void setLocation();
    void setUpdata();
private:
    void initTableView();
    void setDirectBtn();
    void onUserClick(int idx);
    void requestListMsg();
    void onMsgProcess(EventCustom* msg);
    void sortList(string name);
    void addEventListener();
    void removeEventListener();
    void onMoreBtnClick(Ref* pSender);
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view) {};
private:
    Vector<CardPropertyData*> *heroList;
    int TAG_TABLEVIEW;
    int heroId;
    int touchIdx;
    float sx;
    string m_sortMode;
};

#endif /* defined(__FightPass__HeroListBar_Layer__) */
