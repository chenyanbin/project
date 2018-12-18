//
//  GeneralLayer.hpp
//  FightPass
//名将传
//  Created by zhangxiaobin on 16/1/7.
//
//

#ifndef GeneralLayer_hpp
#define GeneralLayer_hpp

#include "../BaseLayer.h"
class GeneralScene:public BaseLayer
{
public:
    enum
    {
        PAGE_ACTIVE = 0,//活动
        PAGE_FIGHTGO = 1,//奇袭
        PAGE_DETAILS = 2,//详情
        PAGE_STATS = 3  //统计
        
    };
    GeneralScene();
    ~GeneralScene();
    bool init(int showPage);

    static GeneralScene* create(int showPage);
    static void show(int fromeScene,int showPage = 0);
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
    void onMsgProcess(EventCustom* message);
private:
    void setBg();
    void topLayer();
    void setMoudleLayer();
    void setTitleBaseInfo();
    void requestBaseInfo();
private:
     int m_showPage;
    string m_name;   //名将传名字
    string m_activeStartTime;//活动开启时间
    string m_activeEndTime;//活动结束时间
    int m_nowChallengeCount;//剩余挑战次数
    int m_maxChanllengeCount;//最大挑战次数
    
private:
    int TAG_USERWEALTH;
    int TAG_CHALEAGE_COUNT;
    int TAG_ACTIVETIME;
   
};

#endif /* GeneralLayer_hpp */
