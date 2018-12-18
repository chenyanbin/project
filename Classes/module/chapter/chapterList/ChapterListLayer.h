//
//  ChapterListLayer.h
//  FightPass
//
//  Created by zhangxiaobin on 15/8/7.
//
//

#ifndef __FightPass__ChapterListLayer__
#define __FightPass__ChapterListLayer__

#include "cocos2d.h"
USING_NS_CC;
#include "extensions/cocos-ext.h"
#include "../../../common/TouchSprite/Button.h"
USING_NS_CC_EXT;
class ChapterListLayer:public Layer,TableViewDataSource,TableViewDelegate
{
public:
    ChapterListLayer();
    ~ChapterListLayer();
    virtual bool init(int totalCount,ccMenuCallback callBack);
    static ChapterListLayer* create(int totalCount,ccMenuCallback callBack);
    void setSelectedByIndex(int index);
protected:
    virtual Size cellSizeForTable(TableView *table);
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view){};
    
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    Node* getNode(int idx);
private:
   
    void setDownBtn();
    void setBg();
    void setUpBtn();
    void setTableView();
    void onDownClick(Ref* pSender);
    void onUPClick(Ref* pSender);
    void onChapterClick(Ref* pSender);
    void onSelected(Ref* pSender);
private:
    ccMenuCallback m_callBack;
    int m_chapterCount;
    Size cellSize;
    Button* _itemImage;
private:
    int TAG_UPBTN;
    int TAG_DOWNBTN;
    int TAG_BG;
    int TAG_TABLEVIEW;
};

#endif /* defined(__FightPass__ChapterListLayer__) */
