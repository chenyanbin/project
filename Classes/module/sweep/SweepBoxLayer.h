//
//  SweepBoxLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/7/15.
//
//

#ifndef __FightPass__SweepBoxLayer__
#define __FightPass__SweepBoxLayer__

#include "../BaseLayer.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "SweepLayer.h"
class SweepBoxLayer:public BaseLayer
{
public:
    SweepBoxLayer();
    ~SweepBoxLayer();
    virtual bool init(BattleBoxData* boxData);
    static SweepBoxLayer* create(BattleBoxData* boxData);
    
    
private:
    void updateBox();
 
    void setOpenBox(Node* psender);
    void onMsgProcess(EventCustom* msg);
    void onEffectFinised(int boxID);
protected:
    virtual void addEventListener();
    virtual void removeEventListener();
    virtual void onEnter();
    virtual void onExit();
private:
    BattleBoxData* m_boxData;
    int TAG_BOX;
    int TAG_LEFTSTAR;

};
#endif /* defined(__FightPass__SweepBoxLayer__) */
