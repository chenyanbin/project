//
//  UserWealthLayer.h
//  SuiTang
//
//  Created by mac on 14-6-27.
//
//

#ifndef __SuiTang__UserWealthLayer__
#define __SuiTang__UserWealthLayer__

#include "cocos2d.h"
USING_NS_CC;
class UserWealthLayer:public Node
{
public:
    enum ModeId
    {
        GENERAL = 1,//同用
        MATRIX,
        STAGE,//关卡界面
        BELONG,//所属
        MARKET,//集市
        FAMOUSE,//名将传
    
    };
    UserWealthLayer();
    ~UserWealthLayer();
    virtual bool init(ModeId mode);
    static UserWealthLayer* create(ModeId mode);
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    void setTitle(const char* path);
private:
    Sprite* getNode(const char* iconPath,const char* labelStr,bool isHaveBtn);
    Sprite* getNode2(const char* iconPath,const char* labelStr,bool isHaveBtn,bool isPower);
    Sprite* bodyNode(const char* iconPath,const char* labelStr,const char* labelStr2,bool isHaveBtn);
    void setWealth();
    void setHomeWealth();
    void onCommonEffect(float percent );
    
    void addUserEventListener();
    void removeUserEventListener();
    void setBelongWealth();
    void onClick(Node* sper);
    void setMarketFind();
    void setFamouseTitle();
    void onUpdateAttrib(EventCustom* msg);
    void onBodyClick(Node* pSender);
private:
    int TAG_BODY_STRENGTH;//体力
    int TAG_COIN;//铜币
    int TAG_GOLD;//元宝
    int TAG_POWER;//战力
    int TAG_MEDAL;//军工
    int TAG_TITLE_BG;
    int TAG_TITLE;
    int TAG_BG;
    int TAG_PLUS;
    int TAG_VALUELABEL;
    ModeId nowMode;
};

#endif /* defined(__SuiTang__UserWealthLayer__) */
