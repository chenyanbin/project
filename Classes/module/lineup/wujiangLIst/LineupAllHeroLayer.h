//
//  LineupAllHeroLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/8/8.
//
//

#ifndef __FightPass__LineupAllHeroLayer__
#define __FightPass__LineupAllHeroLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include <Vector>
#include "../lineup_data/LineupListData.h"
class LineupAllHeroLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    LineupAllHeroLayer();
    ~LineupAllHeroLayer();
    static LineupAllHeroLayer* create(int _lineupId, int _fromHeroType, int _fromLocation, int leader);
    static void show(int _lineupId, int _fromHeroType, int _fromLocation, int leader);
    virtual bool init( int _lineupId,int _fromHeroType,int _fromLocation, int leader);
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
    virtual void scrollViewDidZoom(ScrollView* view){} ;
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
private:
    void createTableView();
    void setallBackGround();
    Sprite* singleList(ssize_t idx);
    void sortList(string name);//排序
    void onTopComboBoxClick(Ref* psender);//英雄排序
    void onshangzhenClick(Node* psender);//上阵
    void onzuiyizhenClick(Node* psender);//最已阵
    void onxiazhenClick(Node* psender);//下阵
    
    
    virtual void addEventListener();
    virtual void removeEventListener();
    void requestListMsg(int _lineupId,int _fromHeroType,int _fromLocation);//武将列表
    void onMsgProcess(EventCustom* msg);//接收武将列表信息
    void requestLineupDownMsg(int lineupNo,int heroId);//发送下阵阵容
    void onDownLineupMsgProcess(EventCustom* msg);//接收下阵消息
    void requestLineupSetMsg(int lineupNo,int heroType, int location, int heroId);//发送上阵阵容
    void onUpLineupMsgProcess(EventCustom* msg);//接收上阵信息
    
    void onUserClick(Node* pSender);
    
private:
    Sprite* listBg;
    int TAG_TABLEVIEW;//tableView
    TableView* _tableView;
   
    Vector<LineupListData*> *heroList;
    int m_lineupNo;//阵容编号
    int m_fromHeroType;//武将类型
    int m_fromLocation;//位置
    int m_heroid;//英雄ID。下阵用
    int m_leader;//英雄总领导力
    int m_combatpower;//上阵英雄战力
    
    bool isMoveing;
    Point isDownPoint;
    int m_oldCombatPower;
    
};


#endif /* defined(__FightPass__LineupAllHeroLayer__) */
