//
//  MailPageLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/10/21.
//
//

#ifndef __FightPass__MailPageLayer__
#define __FightPass__MailPageLayer__

#include "cocos2d.h"
#include "../BaseLayer.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;

#include "../userWealth/UserEquipLayer.h"
#include "../data/BaseTypeData.h"
class MailPageLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    
    MailPageLayer();
    ~ MailPageLayer();
    virtual bool init(int _index);
    static MailPageLayer* create(int _index);
    static void show(int  _level);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
private:
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view) {};
    
    void createTableView();
    Sprite* singleList(ssize_t idx);
    
    void setbg();
    void onclick(Ref* psender);
  
    void requestMailCellMsg(int mailId);
    void onMailCellMsgProcess(EventCustom* msg);
    
    void requestMailCelReceivelMsg(int mailId);
    void onMailCelReceivelMsgProcess(EventCustom* msg);
    
    void addEventListener();
    void removeEventListener();
    void onHeroHeadClick(Node* pSender);
    void setgiftItem(int _tpye, string _content,string _sender, string _title);
private:
    Sprite* listBg;
    int m_mailId;
    int TAG_BUTTON;
    TableView* _tableView;
    int TAG_TABLEVIEW;//tableView
    float sx;
    
    Vector<BaseTypeData*>* m_baseList;

};

#endif /* defined(__FightPass__MailPageLayer__) */
