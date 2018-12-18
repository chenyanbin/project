//
//  SelectHeadLayer.hpp
//  FightPass
//
//  Created by 超 顾 on 15/12/28.
//
//

#ifndef SelectHeadLayer_h
#define SelectHeadLayer_h

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "../../userWealth/UserEquipLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
class iconData:public Ref
{
public:
    int iconId=0;
    string resource="";
    bool isSelect=false;
    bool isHave=false;
};

class SelectHeadLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    SelectHeadLayer();
    ~SelectHeadLayer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    static SelectHeadLayer* create();
protected:
    void addEventListener();
    void removeEventListener();
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view) {};
    
private:
    void initTableView();
    void onUserClick(Node* pSender);
    
    int getIndexByIconID(int _id);
    void sortList();
    //服务器
    void setIconSelList();
    void requestListMsg();
    void requestSetIconMsg(int _id);
    void onMsgProcess(EventCustom* msg);
private:
    float sx;
    int TAG_TABLEVIEW;
    UserEquipLayer* selectIcon;
    int selectIconId;
    Vector<iconData*>* iconList;
};

#endif /* SelectHeadLayer_h */
