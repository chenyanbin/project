//
//  RechargeLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/10/10.
//
//

#ifndef __FightPass__RechargeLayer__
#define __FightPass__RechargeLayer__
#include "../../BaseLayer.h"
#include "../../../commonData/dictData/DictCardCost/DictCardCostManager.h"
#include "../../../commonData/dictData/DictChargeCost/DictChargeCostManager.h"
#include "extensions/cocos-ext.h"
#include "../../../common/TimeUtil.h"
#include <time.h>
#include "../../../iap/IAP/IOSiAP_Bridge.h"
USING_NS_CC_EXT;
//#include "../VipLayer.h"

class ChargeStatusData:public Ref
{
public:
    int chargetCostID;//DictChargeCost.id
    int status;//	1 第一次充 2 非第一次充值
};

class CardData:public Ref
{
public:
    enum
    {
        STATUS_UNABLE_BUY = 1,//可领取
        STATUS_ABLE_BUY = 2 ,//可以买
        STATUS_TODAY_GETTED = 3//当日已领取
    };
    CardData():cardID(0),status(0),leftDays(0),startDate(""),endDate("")
    {
        
    }
    int cardID;
    int status;//1本月已购买，不能再买
                //2本月未购买，可以买
                //3,当日已领取
    string startDate;
    string endDate;
    int leftDays;//剩余天数
    int getLeftDays()
    {
//        if(startDate.size() <= 0 || endDate.size() <= 0)
//        {
//            return 0;
//        }
//        time_t starTime = TimeUtil::strtotime(startDate.c_str());
//        time_t endTime = TimeUtil::strtotime(endDate.c_str());
//        
//        time_t leftTime = endTime - starTime;
//        int day = leftTime / (24 * 3600);
        return leftDays;
    }

};
class RechargeLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    RechargeLayer();
    ~RechargeLayer();
    virtual bool init(Vector<ChargeStatusData*> *chagerstatusdata);
    static RechargeLayer* create(Vector<ChargeStatusData*> *chagerstatusdata);
    void setYuekaCard(Vector<CardData*> *cardList);
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    virtual Size cellSizeForTable(TableView *table);
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual void tableCellHighlight(TableView* table, TableViewCell* cell);
    virtual void tableCellUnhighlight(TableView* table, TableViewCell* cell);
    virtual void tableCellWillRecycle(TableView* table, TableViewCell* cell);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view) {};
    virtual void addEventListener();
    virtual void removeEventListener();
private:

    void onyuekaClick(Ref* psender);
    void setRechargeCard();
    void onbuyBtn(Ref* psender);
    void setVipLevel();
    Node* getChargeNode(int index);
    
    void onRequestCallBack(IOSProduct* product,int code);
    
    void onPayCallBack(bool isSuc,std::string &identifier, int quantity, std::string &receipt);
    
    void requestApplePayPageMsg(int _charge_type, int _charge_id, int _card_id, int _fee, string _channel_code, string _channel_label, string _ipa_varify_str, int _is_sandbox);
    void onAppleyapMsgProcess(EventCustom* message);
    
private:
    Size cellSize;
    int TAG_CARDLIST;
    int TAG_CARDTITLE;
    Vector<DictChargeCost*>* chargeCostList;
    Vector<CardData*> * m_cardList;
    bool m_isMove;
    Vector<ChargeStatusData*>* m_chargestatusList;
    bool m_isyueka;
    int m_index;
};

#endif /* defined(__FightPass__RechargeLayer__) */
