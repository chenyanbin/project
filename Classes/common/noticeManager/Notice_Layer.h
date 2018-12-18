//
//  Notice_Layer.hpp
//  FightPass
//
//  Created by 超 顾 on 16/1/26.
//
//

#ifndef Notice_Layer_h
#define Notice_Layer_h

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../module/BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;


class NoticeData:public Ref
{
public:
    NoticeData()
    {
        DescList=new vector<string>();
    }
    ~NoticeData()
    {
        CC_SAFE_DELETE(DescList);
        DescList = NULL;
    }
    string NoticeName;//公告名字
    vector<string> *DescList;//公告描述
};
class Notice_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    Notice_Layer();
    ~Notice_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(Vector<NoticeData*> * value);
    static Notice_Layer* create(Vector<NoticeData*> * value);
    //value 0：表示登陆公告。1：表示主界面公告
    static void show(Vector<NoticeData*> * value);
    
   private:
    void createLayer();
    Node* initView();
    void initTableView();
   
    void initLayer();
    void onClick(Ref* pSender);
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view) {};
private:
    float sx;
    Node* viewNode;
    Vector<NoticeData*> *noticeList;
    int TAG_TABLEVIEW;
    int noticeMold;
};


#endif /* Notice_Layer_h */
