//
//  MarketJuxianLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/8/4.
//
//

#ifndef __FightPass__MarketJuxianLayer__
#define __FightPass__MarketJuxianLayer__

#include "../../BaseLayer.h"
#include "MarketGoodsLayer.h"
#include "MarketRotateLayer.h"
#include "../marketData/JuxianListData.h"
#include "editor-support/cocostudio/CCArmature.h"
#include "../../../common/TouchSprite/TouchSprite.h"

using namespace cocostudio;


class MarketJuxianLayer:public BaseLayer,public RotateDeleate
{
public:
    enum TAG_TIME
    {
        TAG_TIME1 = 100,
        TAG_TIME2,
        TAG_TIME3
    };

    MarketJuxianLayer();
    ~MarketJuxianLayer();
    virtual bool init();
    static MarketJuxianLayer* create();
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    virtual void tableCellTouched(Ref*) ;
    virtual void scrollViewDidScroll(Ref*);
private:
    void setBackground();
    void onsetClick(Ref* psender);
    void setFreeTimes();
    void setparticle();
    void onMsgProcess(EventCustom* msg);
    virtual void addEventListener();
    virtual void removeEventListener();
    void requestListMsg();//请求列表信息
    
    void requesttimesMsg(int leadId, int countMode);
    void onTimeMsgProcess(EventCustom* msg);
    
    void settimesUpdata(int tag);
    void update(float delta);
    void update2(float delta);
    void update3(float delta);
    
    void setOrderCard(Node* parent,JuxianListData* data);
    
    void setCardPos();
    void changeCardPosProcess(EventCustom* msg);
    void setlastTime(int nextSelected);
    void clearResourcePerson();
    void settokencount();
    void changParticle();
    void setGoldCount();
private:
    int TAG_TIMELABEL;
    int TAG_LASTTIME;//剩余时间
    int TAG_LABELWORD;//免费字
    int TAG_ICON;//消耗方式
    int TAG_TOKEN;//举贤令
    int m_tag_time;
    Label* label;
    long  pTime;
    Label* label2;
    long  pTime2;
    Label* label3;
    long  pTime3;
    int m_nextSelected;//卡牌位置小标
    bool isfirst = true;
    int TAG_PARTICLE;
    int TAG_PARTICLE2;
    int TAG_MENU;
    int TAG_TIMEOUT;//免费次数用尽
    int TAG_DEXNODE;
};

#endif /* defined(__FightPass__MarketJuxianLayer__) */
