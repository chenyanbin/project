//
//  NewPlayerGuild.h
//  SuiTang
//
//  Created by zhangxiaobin on 14-9-10.
//
//

#ifndef __SuiTang__NewPlayerGuild__
#define __SuiTang__NewPlayerGuild__

#include "GuideScene.h"
#include "GuideContent.h"
#include "../../commonData/dictData/DictFunction/DictFunctionManager.h"
#include "../../commonData/enum/DictFunctionEnum.h"
#include "../../commonData/dictData/DictStageBattle/DictStageBattleManager.h"
#define HAND_EFFECT "xinshouzhiying" //引导手指特效
#define HAND_ARROW "shubiaodonghua" //手指箭头特效
//引导数据类
class GuideData:public Ref
{
public:
    GuideData():functionID(0),step(0)
    {
    }
    ~GuideData()
    {
    }
    
    int functionID;
    int step;
};

class NewPlayerGuild
{
public:
    virtual bool init();
    void alignToSceneBottom();//底部对齐
    void alignToSceneCenter();//中心对齐
    
    void scaleToScaleY();//关卡缩放
    void scaleToscaleX();//普通缩放试
    void scaleToMax();//最大值缩放
    bool addFunction(int functionID,int _step);
    bool isNowGuideEvent(int guideEvent);
    void next(int buttonID = 0);
    void pause();
    bool isShowing();//是否显示中
public:
   
    static NewPlayerGuild* getInstance();
    static void destoryInstance();
    
    int getStageBattleIndex(int stageBattleID);//得到当前关卡战卡是该关卡的第几场
    DictNewGuide* getNowData();
    
    bool isOpened(int functionID ,int _step);
    int getOpenFuntionStep(int functionID);
    bool isInGuideList(int functionID);
    //清空以开放的功能列表
    void clearList();
    void start();
    void showGuideByGuideId(int guideID);
    void showGuideContent(int functionID,int _step);//显示当前引导内容
    void showNowGuide();
    
    bool onUserLevelUp(int level);   //玩家升级了。
    void onStageBattleOver(int stageBattleID);//玩家通过了某个关卡
    void onMainHeroActionEnded();//英雄动作完成
    bool isInActionTeaching();//是否动作教学中
    DictFunction* isInFunctionOpenList(int stageBattleID);
    
    void sendNewGuideMsg();
    void goNext();
private:
    
   
    NewPlayerGuild();
     ~NewPlayerGuild();
    inline DictNewGuide* getNextData();//得到下一步数据
    inline int getBreadkPointIndex(int functionID,int step);//得到断点后，重新登陆的起始点
public:
    
private:
    static NewPlayerGuild* _instance;
    int m_curStep;//当前步数
    int m_functionID;//当前功能编号
    GuideScene* guideScene;
    GuideContent* guideContent;
    DictNewGuide* curGuideData;
    Vector<DictNewGuide*>* guideList;
    //已经开放的功能列表
    Vector<GuideData*>* openList;
    Vector<DictStageBattle*>* stageBattleList;
  
};

#endif /* defined(__SuiTang__NewPlayerGuild__) */
