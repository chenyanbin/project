//
//  MailLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/10/20.
//
//

#ifndef __FightPass__MailLayer__
#define __FightPass__MailLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../BaseLayer.h"
#include "../../common/TouchSprite/Button.h"
USING_NS_CC_EXT;
USING_NS_CC;
class MailLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    MailLayer();
    ~ MailLayer();
    static MailLayer* create();
    static void show();
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
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view) {};
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
private:
    void createTableView();
    void setBg();
    Button* singleList(ssize_t idx);
    void requestMailListMsg();//邮件列表
    void onMsgProcess(EventCustom* msg);
    virtual void addEventListener();
    virtual void removeEventListener();
    void onallClick(Ref* psender);
    void onReiveClick(Ref* psender);
    void onClick(Ref* psender);
    
    void requestMailAllGiftListMsg();
    void onMailAllGiftMsgProcess(EventCustom* msg);
    
    void requestMailCelReceivelMsg(int mailId);//请求领取;
    void onMailCelReceivelMsgProcess(EventCustom* msg);
    
    void onlingquchenggongProgress(EventCustom* msg);
private:
    Sprite* listBg;
    int TAG_TABLEVIEW;//tableView
    TableView* _tableView;
    bool isMoveing;
    Point isDownPoint;
    int TAG_LISTBG;
    int TAG_BTNLINGQU;//一键领取
    int m_index;
};


#endif /* defined(__FightPass__MailLayer__) */
