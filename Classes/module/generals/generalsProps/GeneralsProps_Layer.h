//
//  GeneralsProps_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/8/20.
//
//

#ifndef __FightPass__GeneralsProps_Layer__
#define __FightPass__GeneralsProps_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include <Vector>

USING_NS_CC_EXT;
USING_NS_CC;
class PropsData:public Ref
{
public:
    int propsId;//道具ID
    string propsName;//道具名字
    int propsNumber;//道具数量
    int propsQuality;//道具品质
    string propsDesc;//道具描述
    int propsUseType;//道具使用类型
    int propsCanUse;//道具是否能使用
    string propResource;//道具素材名称
    int propsItemType;//道具类型
    int propsItemDictId;//道具原型ID
    int backPackOrder;//道具在背包位置
    int subType;//细化类型 2 为升品材料 1为消耗材料
};
class GeneralsProps_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    GeneralsProps_Layer();
    ~GeneralsProps_Layer();
    static GeneralsProps_Layer* create();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
private:
    void initTableView();
    void createLayer();
    Sprite* singleList(ssize_t idx);
    void onTopComboBoxClick(Ref* psender);
    
    void requestListMsg();
    void onMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    void sortList(string name);
    void onBtnListClick(Ref* psender);
    void runEffect();
    void effectOver();
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view) {};
    
private:
    float sx;
    int TAG_TABLEVIEW;
    int TAG_ALLPROPS;
    Vector<PropsData*> *propsList;
    Label* propsNumberLabel;
    string thisSort;
    bool isClick;
};



#endif /* defined(__FightPass__GeneralsProps_Layer__) */
