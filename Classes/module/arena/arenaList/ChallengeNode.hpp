//
//  ChallengeNode.hpp
//  FightPass
//
//  Created by zhangbin on 16/3/9.
//
//

#ifndef ChallengeNode_hpp
#define ChallengeNode_hpp

#include "cocos2d.h"
#include "../../BaseLayer.h"
USING_NS_CC;
class ChallengeNode:public BaseLayer
{
public:
    ChallengeNode();
    ~ChallengeNode();
    static ChallengeNode* create(ssize_t idx);
    bool init(ssize_t idx);
    
private:
    void setHead();
    void setName();
    void setBtn();
    void onBtnClick(Ref* pSender);
    void setPrizeValue();
    
protected:
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    int m_index;
};

#endif /* ChallengeNode_hpp */
