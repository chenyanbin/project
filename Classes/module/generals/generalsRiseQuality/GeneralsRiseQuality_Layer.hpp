//
//  GeneralsRiseQuality_Layer.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/11.
//
// 升品材料

#ifndef GeneralsRiseQuality_Layer_hpp
#define GeneralsRiseQuality_Layer_hpp
#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include <Vector>
#include "../generalsProps/GeneralsProps_Layer.h"
USING_NS_CC_EXT;
USING_NS_CC;

class GeneralsRiseQuality_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    GeneralsRiseQuality_Layer();
    ~ GeneralsRiseQuality_Layer();
    static GeneralsRiseQuality_Layer* create();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
private:
    void initTableView();
    Sprite* singleList(ssize_t idx);
   
    void requestListMsg();
    void onMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    
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
    bool isClick;
};


#endif /* GeneralsRiseQuality_Layer_hpp */
