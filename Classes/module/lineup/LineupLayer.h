//
//  LineupLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/6/23.
//
//

#ifndef __FightPass__LineupLayer__
#define __FightPass__LineupLayer__

#include "cocos2d.h"
#include "../BaseLayer.h"
class LineupLayer:public BaseLayer
{
public:
    LineupLayer();
    ~LineupLayer();
    virtual bool init(int nowPage,int _combatPower);
    static LineupLayer* create(int nowPage,int _combatPower);
    static void show(int fromScene,int nowPage,int _combatPower);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
private:
    void setbackGround();
    void setUserWealth();
    void setLineupChoseLayer(int nowPage);
    void setLineupCheerLayer(int nowPage);
    void setLineupHeroLayer(int nowPage);
    void setHeroBtn();//开战按钮
    void setWaitBtn();//设置等待按钮
    void onClick(Ref* psender);
    void setParticle();
    void setLineupzhenrongLayer(int nowPage);
    
    void setleadership(int _leadership);//领导力
    void combatPower(int _combatPower);//战力
    void  onlingdaoli(EventCustom* msg);
    void  onzhanli(EventCustom* msg);
    virtual void addEventListener();
    virtual void removeEventListener();
    
    void requestFightMsg(int lineupNo);//开战
    void onMsgFight(EventCustom* msg);
    void createButtonMsg(EventCustom* msg);//当前整容
    void onRoleLeaderMsg(EventCustom* msg);//返回角色领导力
    void onFightOrWiteMsg(EventCustom* msg);//开战还是待战
private:
    int TAG_USERHEAD;
    int TAG_NAMEBG;
    int m_totoalLeader;//总领导力
    int TAG_KAIZHANBTN;//开战
    int TAG_DAIMINGBTN;//待命
    int TAG_KAIZHANWORD;//开战字
    int m_nowPage;//第几张
    int m_combatPower;//增加的战力
    int TAG_COMBATSPR;//战力北京
    int TAG_COMBATNUM;//战力数值
};

#endif /* defined(__FightPass__LineupLayer__) */
