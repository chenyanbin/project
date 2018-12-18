//
//  SevenDayGiftLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/11/26.
//
//

#ifndef __FightPass__SevenDayGiftLayer__
#define __FightPass__SevenDayGiftLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include "../../../common/TouchSprite/Button.h"
#include "../../data/BaseTypeData.h"
class SevenDayGiftLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
   
    SevenDayGiftLayer();
    ~ SevenDayGiftLayer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(int _day);
    static SevenDayGiftLayer* create(int _day);
private:
    void createLayer();
    void removeEventListener();
    void onComboBoxBtn2Click(Ref* psender);
    void setItembuy(int itemtype);//七日福利
    void gotoClick(Ref* pSender);//前往
    void sethalfPrive();//半价
    
    void onitemClick(Node* pSender);
    void onhalfitemClick(Node* pSender);
    void onBuyClick(Ref* pSender);
    void requestWeekRewardMsg(int _day, int _type, int _numPrice, int _numHero);
    void onWeekDayRewardMsgProcess(EventCustom* msg);
    void addEventListener();
    void onqianwang(int _type);
    void requestWeekhalfBuyMsg(int _day);
    void onWeekhalfBuyProcess(EventCustom* msg);
    
    void initTableView();
    void onCellClick(Ref* pSender);
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view) {};
    Button* singleList(ssize_t idx);
    
    void onChoseHeroProcess(EventCustom* msg);
//    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
//    virtual void onTouchMoved(Touch *touch, Event *unused_event);
//    virtual void onTouchEnded(Touch *touch, Event *unused_event);
private:
    float sx;
    int TAG_TABLEVIEW;
    int TAG_ITEMBG;
    int TAG_HALFPRIVE;
    int TAG_NODE;
    int m_day;//第几天
    int m_rewardType;
    int m_numhero;
};


#endif /* defined(__FightPass__SevenDayGiftLayer__) */
