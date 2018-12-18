//
//  ChooseCard_layer.h
//  FightPass
//
//  Created by 超 顾 on 15/8/13.
//
//

#ifndef __FightPass__ChooseCard_layer__
#define __FightPass__ChooseCard_layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../data/CardPropertyData.h"
#include "../data/CardDataManager.h"
#include "../../BaseLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../commonData/dictData/DictHeroPrestigeUpCost/DictHeroPrestigeUpCostManager.h"
USING_NS_CC_EXT;
USING_NS_CC;
class ChooseCard_layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    ChooseCard_layer();
    ~ChooseCard_layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(int cardId);
    static ChooseCard_layer* create(int cardId);
private:
    void createLayer();
    void initTableView();
    void onUserClick(Node* pSender);
    void updataData();
    void onNext(Node* pSender);
    
    int setCardInfoData(string valueStr , int value);
    void addEventListener();
    void removeEventListener();
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view) {};
    
    //服务器
    void requestListMsg();
    void onMsgProcess(EventCustom* msg);
    void onStartExperience(Ref* psender);
    void effectOver();
    
    void sortList(string name);
    
private:
    float sx;
    int TAG_LISTBG;
    int TAG_TABLEVIEW;
    int TAG_EXPERIENCELABEL;//当前获得经验
    int TAG_EXPUPDATALABEL;//升级所需经验
    int TAG_CURRENTLV;//当前等级
    int TAG_UPLEVEL;//升级后等级
    
    int TAG_ADDPRESTIGE;//加声望
    int TAG_CONSUME;//花费
    
    int cardId;
    Vector<CardPropertyData*> *chooseCardList;
    int cardExperience;//
    int cardLeve;//当前卡牌等级；
    int getExperience;//当前获得经验；
    int upgradeExperience;//升级所需经验；
//    Vector<CardPropertyData*>* upCostList;
    CardPropertyData* upHeroData;
    UserHeadLayer* selectCard;
    string thisSort;
    bool isMoveing;
};


#endif /* defined(__FightPass__ChooseCard_layer__) */
