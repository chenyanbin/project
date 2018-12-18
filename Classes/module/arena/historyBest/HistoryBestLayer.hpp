//
//  HistoryBestLayer.hpp
//  FightPass
//
//  Created by zhangbin on 16/4/5.
//历史最高界面
//

#ifndef HistoryBestLayer_hpp
#define HistoryBestLayer_hpp

#include "../../BaseLayer.h"

class HistoryBestLayer:public BaseLayer
{
public:
    HistoryBestLayer();
    ~HistoryBestLayer();
    virtual bool init(int nowOrder,int historyOrder,int goldPrize);
    static HistoryBestLayer* create(int nowOrder,int historyOrder,int goldPrize);
private:
    void onConfirmClick(Ref* pSender);
    void setContent();

    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
    
    void onMsgProcess(EventCustom* message);
private:
    int m_nowOrder;
    int m_historyOrder;
    int m_goldPrize;
    int m_changeValue;
    
    int TAG_CONTENT;
};


#endif /* HistoryBestLayer_hpp */
