//
//  ServerListLayer.h
//  FightPass
//
//  Created by zhangxiaobin on 15/7/16.
//
//

#ifndef __FightPass__ServerListLayer__
#define __FightPass__ServerListLayer__

#include "../../BaseLayer.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
#include "ServerListDataManager.h"
class ServerListLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    ServerListLayer();
    ~ServerListLayer();
    virtual bool init();
    static ServerListLayer* create();
    static void show();
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual Size cellSizeForTable(TableView *table);
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual void tableCellHighlight(TableView* table, TableViewCell* cell);
    virtual void tableCellUnhighlight(TableView* table, TableViewCell* cell);
    virtual void tableCellWillRecycle(TableView* table, TableViewCell* cell);
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view) {};
    
    void backScene();
private:
    void setServerTableView();
    void setBg();
    Node* getNode(int index);
   
    void onSelectedServer(Ref* pSender);
    void showServerList(int index);
    Node* getServerNode(ServerListData* data);
    void setLastLoginBtn();
    void onLastBtnClick(Ref* pSender);
    void setTitle();

    void setNowSelect();
    void showAllServerList(int index);
    void onAllSelectedServer(Ref* pSender);
private:
     MenuItemImage* curSelectedItem;//当前选择区
    ServerListData* m_nowSelectedData;
    Vector<ServerListData*>* serverList;
    Vector<ServerListData*>* recentList;//全部服务器（只为在最近登录中显示全部服务器单独加了一个vector）
//    Vector<ServerListData
    Size cellSize;
    int PAGENUM;
    int DISPLAY_COUNT;
    int TAG_SERVERLIST;
    int TAG_LASTLOGIN;
    int TAG_TABLEVIEW;
    int TAG_ALLLIST;
    int TAG_LABEL;
};

#endif /* defined(__FightPass__ServerListLayer__) */
