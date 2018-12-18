//
//  ServerAllListLayer.hpp
//  FightPass
//
//  Created by chenyanbin on 16/5/5.
//
//

#ifndef ServerAllListLayer_hpp
#define ServerAllListLayer_hpp

#include "../../BaseLayer.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
#include "ServerListDataManager.h"
class ServerAllListLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    ServerAllListLayer();
    ~ServerAllListLayer();
    virtual bool init();
    static ServerAllListLayer* create();
protected:
    virtual void onEnter();
    virtual void onExit();
   
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view) {};
private:
    void initTableView();
    Node* initView();
    Node* getServerNode(ServerListData* data);
    void onAllSelectedServer(Ref* pSender);
private:
    int TAG_TABLEVIEW;
    Node* viewNode;
    Vector<ServerListData*>* recentList;
};


#endif /* ServerAllListLayer_hpp */
