//
//  StageBattleBox.hpp
//  FightPass
//
//  Created by zhangbin on 16/3/23.
//
//

#ifndef StageBattleBox_hpp
#define StageBattleBox_hpp

#include "../BaseLayer.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "StageBattleInfo.hpp"
class StageBattleBox:public BaseLayer
{
public:
    StageBattleBox();
    ~StageBattleBox();
    virtual bool init(BattleBox* boxData);
    static StageBattleBox* create(BattleBox* boxData);
    
    
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
    BattleBox* m_boxData;
    int TAG_BOX;
    int TAG_LEFTSTAR;
    
};

#endif /* StageBattleBox_hpp */
