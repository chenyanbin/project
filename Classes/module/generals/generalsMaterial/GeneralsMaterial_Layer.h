//
//  GeneralsMaterial_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/8/20.
//
//

#ifndef __FightPass__GeneralsMaterial_Layer__
#define __FightPass__GeneralsMaterial_Layer__


#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include <Vector>

USING_NS_CC_EXT;
USING_NS_CC;

class MaterData
{
public:
    int materId;//材料ID
    string materName;//技能名字
    int materNumber;//材料数量
    int materQuality;//材料品质
    int materNeedCount;//合成需要数量
};

class GeneralsMaterial_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    GeneralsMaterial_Layer();
    ~GeneralsMaterial_Layer();
    static GeneralsMaterial_Layer* create();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
private:
    void initTableView();
    void createLayer();
    Sprite* singleList(ssize_t idx);
    
    void requestListMsg();
    void requestComposeMsg(int _materId);
    void onMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    void sortList(string name);
    void onBtnListClick(Ref* psender);
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view) {};
    
private:
    float sx;
    int TAG_TABLEVIEW;
    int TAG_COMPOUND;//合成
    int TAG_GOTOGAIN;//去获取
    int TAG_ALLMATERIAL;
    Label* materialNumberLabel;
    string onSortStr;
    MaterData* selectData;
    vector<MaterData*> *materList;

};



#endif /* defined(__FightPass__GeneralsMaterial_Layer__) */
