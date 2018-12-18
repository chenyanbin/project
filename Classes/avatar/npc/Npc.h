//
//  Npc.h
//  FightPass
//
//  Created by 超 顾 on 15/6/2.
//
//

#ifndef __FightPass__Npc__
#define __FightPass__Npc__
#include "../../commonData/dictData/DictNPC/DictNPCManager.h"
#include "../Avatar.h"
class Npc:public Avatar
{
public:
    Npc();
    ~Npc();
    bool init(int npcID);
    static Npc* create(int npcID);
    virtual char* class_name(){return "Npc";};
protected:
    virtual void onEnter();
    virtual void onExit();
public:
    CC_SYNTHESIZE_RETAIN(DictNPC*, _dictNpc, DictNpc);
    void onActionCompleted();
private:
    void onNpcClick(Ref* pSender);
};
#endif /* defined(__FightPass__Npc__) */
