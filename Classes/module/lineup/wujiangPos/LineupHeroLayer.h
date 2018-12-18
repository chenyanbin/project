//
//  LineupHeroLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/6/24.
//
//

#ifndef __FightPass__LineupHeroLayer__
#define __FightPass__LineupHeroLayer__

#include "../../BaseLayer.h"
#include "editor-support/cocostudio/CCArmature.h"
#include "RotateMenu.h"
#include <Vector>
#include "../lineup_data/LineupPageData.h"
#include "../../../common/Dialog/Dialog.h"
using namespace cocostudio;
class LineupHeroLayer:public BaseLayer
{
public:
    LineupHeroLayer();
    ~LineupHeroLayer();
    virtual bool init(int nowPage);
    static LineupHeroLayer* create(int nowPage);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
private:
    void setHeroPos();
    void loadPerson();
    void onDataLoaded(float percent);
    void clearResourcePerson();
    void setBackGround();
    void zhujiangPOs();//设置空白位置（获得英雄所在位置）
    void onPosClick(Node* psender);
    void onChangePageCallBack(EventCustom* msg);
    void requestPageMsg(int team);
    void  onMsgProcess(EventCustom* msg);
    virtual void addEventListener();
    virtual void removeEventListener();
    void changeLinguoHero(EventCustom* msg);//接受武将位置改变的消息
    void onChangeHeroPos();//收到武将位置改变的消息
    void requestLocationMsg(int lineupNo, int heroId1, int heroId2,int heroId3);
    
    Node* getItem(LineupPageData* data);
    void ontouchchangeProcess(EventCustom* msg);
private:
    bool m_isPos;
   
    PopupLoading* popUpLoading;
    Vector<LineupPageData*> *lineipPageList;
    Vector<LineupPageData*> *lineupCheerList;
    int m_location;//点击的位置
    int m_heroType;//英雄类型（战斗/助威）
    int m_tag_heroPos;//旋转获得武将位置的英雄ID
    int m_turn;//武将位置顺序
    int m_nowPage;//当前阵容页
    int m_leadership;//总领导力
    int TAG_MENU;
    int TAG_SHADOWE;
    int m_index;//切换角标
};

#endif /* defined(__FightPass__LineupHeroLayer__) */
