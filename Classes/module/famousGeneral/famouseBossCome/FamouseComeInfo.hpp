//
//  FamouseComeInfo.hpp
//  FightPass
//名将来袭信息层
//  Created by zhangxiaobin on 16/1/25.
//
//

#ifndef FamouseComeInfo_hpp
#define FamouseComeInfo_hpp

#include "../../BaseLayer.h"
class FamouseComeInfo:public BaseLayer
{
public:
    FamouseComeInfo();
    ~FamouseComeInfo();
    virtual bool init();
    CREATE_FUNC(FamouseComeInfo);
private:
    void onMsgProcess(EventCustom* message);
    void setButton();
    void onDelayBtnClick(Ref* pSender);
    void onFightBtnClick(Ref* pSender);
    void setBloodPercent();
    void setTitle();
    void updateProgress();
    void setInfo();
    void onDelay();
    void onResetClick(Ref* pSender);
    void onConfirmCallBack(Node* pSender);
    void requestInfoMsg();
    void updateAttackCount();//更新挑战次数
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
private:
    int bossDictId;//	boss原型id	int	Y	DictLegendBattleMonster.id
    float bossCurHp;//boss当前血量
    float bossHpMax;//	boss最大血量	int	Y
    string legendName;//	名将传名称	string	Y
    int bossLevel;
    int attackCount;//	可用挑战次数	short	Y
    int attackCountMax;//	最大挑战次数	short	Y
    long long activityStartTimes;//	活动开始时间	long	Y	单位：毫秒
    long long activityEndTimes;//	活动结束时间			单位：毫秒
    int bossRemainSeconds;//	倒计时	int	Y	单位：秒此时间过后，boss会逃跑
private:
    ProgressTimer* bloodPt;
    Label* delayLabel;
    int TAG_PROGRESS;
    int TAG_ATTACKCOUNT;
};

#endif /* FamouseComeInfo_hpp */
