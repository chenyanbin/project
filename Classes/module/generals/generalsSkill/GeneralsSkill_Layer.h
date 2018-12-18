//
//  GeneralsBase_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/7/29.
//
//

#ifndef __FightPass__GeneralsSkill_Layer__
#define __FightPass__GeneralsSkill_Layer__
#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../data/CardPropertyData.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
class GeneralsSkill_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    GeneralsSkill_Layer();
    ~GeneralsSkill_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    CREATE_FUNC(GeneralsSkill_Layer);
private:
//    void createLayer();
    void initTableView();
    void requestListMsg();
    void onMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    Node* initView();
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view) {};
private:
    int titleCount;
    float sx;
    int TAG_LISTBG;
    int TAG_TABLEVIEW;
    int cardId;
    Node* viewNode;
    CardPropertyData* cardData;
};
#endif /* defined(__GeneralsSkill_Layer__) */
