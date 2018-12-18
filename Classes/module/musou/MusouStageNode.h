//
//  MusouStageNode.h
//  FightPass
//
//  Created by zhangxiaobin on 15/10/13.
//
//

#ifndef MusouStageNode_h
#define MusouStageNode_h
#include "cocos2d.h"
USING_NS_CC;
#include "data/MusouStageData.h"
#include "../../commonData/dictData/DictMusou/DictMusouManager.h"
class MusouStageNode:public Node
{
public:
    MusouStageNode();
    ~MusouStageNode();
    virtual bool init(MusouStageData* data);
    static MusouStageNode* create(MusouStageData* data);
private:
    void setPage();
     void onClick(Node* psender);
    void onDelay(float dt);
    void onBtnClick(Ref* pSender);
    void setParticle();
    void setParticle1();
    void setInstruction(Node* parent);
    Node* getWeekStr(DictMusou* musouData);
protected:
    virtual void onEnter();
    virtual void onExit();
    
private:
    MusouStageData* m_data;
    long long m_leftTime;
private:
    int TAG_LEFTTIME;
    bool   m_isopen;
    int TAG_SPRGUAN;
    int TAG_GUAN;
    
};

#endif /* MusouStageNode_h */
