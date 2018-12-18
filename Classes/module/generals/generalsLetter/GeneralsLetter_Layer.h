//
//  GeneralsLetter_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/8/19.
//
//

#ifndef __FightPass__GeneralsLetter_Layer__
#define __FightPass__GeneralsLetter_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "../data/LetterDataManager.h"
#include <Vector>

USING_NS_CC_EXT;
USING_NS_CC;
class GeneralsLetter_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    enum
    {
        BUTTON_LETTER= 1,//送信
        BUTTON_GIFTS = 2,//送礼
        BUTTON_NOTGIFTS=3,//送礼次数最大了
        BUTTON_GAIN = 4,//获得
        BUTTON_DEYAMA = 5//出山
    };
    GeneralsLetter_Layer();
    ~GeneralsLetter_Layer();
    static GeneralsLetter_Layer* create();
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
    void onUpdata();
//    void sortList(string name);
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
    int TAG_LATTERNUM;
    int TAG_ALLLETTER;
    Vector<LetterData*>* letterList;
    int giftCount;//今日送礼次数
    int giftCountMax;//最大送礼次
    Label* equipNumLabel;
    Label* todayNumLabel;
    bool isSort;
};

#endif /* defined(__FightPass__GeneralsLetter_Layer__) */
