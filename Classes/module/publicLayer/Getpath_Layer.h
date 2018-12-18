//
//  Getpath_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/9/8.
//获取途径
//

#ifndef __FightPass__Getpath_Layer__
#define __FightPass__Getpath_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
class WayData:public Ref
{
public:
//    int wayId;//途径ID
    string wayName;//途径名字
    string wayDesc;//途径描述
    int wayCount;   //途径次数
                    //    不同way，次数有不同的定义
                    //    战役：当日可进次数, -1未开启
                    //    举贤：免费举贤次数
                    //    寻访：寻访
                    //    其他：没有
    int wayMaxCount;//途径最大次数
    int wayFunction;//功能模块
    int wayStageId;//关卡id      战役有效
    int wayBattleMode;//战役模式
                      //    战役有效
                      //    普通 1
                      //    精英 2
};

class Getpath_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    Getpath_Layer();
    ~Getpath_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(int itemType ,int itemId,int itemQuality,int fromLayer);
    static Getpath_Layer* create(int itemType ,int itemId,int itemQuality,int fromLayer);
    static void show(int fromLayer,int itemType ,int itemId,int itemQuality);
private:
    void createLayer();
    void requestListMsg();
    void initTableView();
    void updateLabel();
    void onMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    void onBtnClick(Ref* psender);
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view) {};
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    
    void closeScene();
private:
    float sx;
    int TAG_TABLEVIEW;
    
    
    int _itemType;
    int _itemId;
    int _itemQuality;
    int _fromMoudeId;
    
    Vector<WayData*> *wayList;
    string currentItemName;//
    int currentItemCount;
    string currentItemDesc;
    
    Label* nameLabel;
    Label* numLabel;
    Label* descLabel;
    
    bool isMoveing;
};

#endif /* defined(__FightPass__Getpath_Layer__) */
