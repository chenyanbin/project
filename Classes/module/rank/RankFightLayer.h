//
//  RankFightLayer.h
//  FightPass
//
//  Created by chenyanbin on 16/1/4.
//
//

#ifndef __FightPass__RankFightLayer__
#define __FightPass__RankFightLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../BaseLayer.h"

USING_NS_CC_EXT;
USING_NS_CC;
class RankFightLayer:public BaseLayer
{
public:
    
    RankFightLayer();
    ~ RankFightLayer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    static RankFightLayer* create();
    static void show(int fromScene);
private:
    
    void setBackground();
    void createLayer();
    void onClick(Ref* pSender);
    void onPriceClick(Ref* pSender);//奖励详情查看

private:
    float sx;
    float TAG_TABLEBG;
    int TAG_TABLEVIEW;
    TableView* _tableView;
    int TAG_PERDETAILBG;
    int TAG_MULTIPLE;//综合排名
    int TAG_DAY;//每日排名
    int m_layer;//层
};
#endif /* defined(__FightPass__RankFightLayer__) */

