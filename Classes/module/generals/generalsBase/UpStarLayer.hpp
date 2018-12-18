//
//  UpStarLayer.hpp
//  FightPass
//
//  Created by zhangbin on 16/3/26.
//
//

#ifndef UpStarLayer_hpp
#define UpStarLayer_hpp

#include "../../BaseLayer.h"
#include "../data/CardPropertyData.h"
class UpStarLayer:public BaseLayer
{
public:
    UpStarLayer();
    ~UpStarLayer();
    virtual bool init(int heroID,int heroDictID);
    static UpStarLayer* create(int heroID,int heroDictID);
    static void show(int heroID,int heroDictID);
private:
    void setLeftHero();
    void setRightStar();
    Label* getNameLabel(string nameStr,int quality);
    Node* getHeroImage(int quality);
    
    void onUpStarClick(Ref* pSender);
   
    void updateStar(int starNum);
    void updateCooperCost();
    void updateCondition();
    void setAttribs();//设置属性
    Node* getAttribNode(const char* attribStr,int value,int newValue);
    void requestPageMsg();
    void onIconClick(Node* pSender);
    void onUpStarSuc();
protected:
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
    void onMsgProcess(EventCustom* message);
private:
    int m_heroID;
    int m_heroDictID;
    int m_nowStar;
    int costCoin;
    int heroBookId;
    int heroBookCount;
    int nowHeroBookCount;
    bool isInited;
    ProgressTimer* promotePt;
    CardPropertyData* propertyData;
    CardPropertyData* propertyNewData;
    int TAG_STARFORM;
    int TAG_UPSTARBTN;
    int TAG_COOPER;
    int TAG_PROGRESSLABEL;
    int TAG_ATTRIB_NODE;
    
    
};

#endif /* UpStarLayer_hpp */
