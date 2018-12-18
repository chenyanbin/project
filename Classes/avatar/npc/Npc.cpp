//
//  Npc.cpp
//  FightPass
//
//  Created by 超 顾 on 15/6/2.
//
//

#include "Npc.h"
#include "../../module/publicLayer/GotoModule.h"
#include "../../common/GameConfig.h"
Npc::Npc()
:_dictNpc(NULL)
{
    
}
Npc::~Npc()
{
    CC_SAFE_RELEASE_NULL(_dictNpc);
}
bool Npc::init(int npcID)
{
    bool bref = false;
    do {
        DictNPC* dictNpc = DictNPCManager::getInstance()->getData(npcID);
        this->_avatarType = AVATAR_TYPE_NPC;
        CC_BREAK_IF(!Avatar::init(dictNpc->resource.c_str()));
        this->setDictNpc(dictNpc);
        this->_avatarName = dictNpc->name;
        this->m_avatarPosY = dictNpc->resourceHighShifting;
        this->m_avatarPosX = dictNpc->resourceShifting;
         this->onEnterScene();
        this->showName();
       
        
        bref = true;
    } while (false);
    return bref;
}
Npc* Npc::create(int npcID)
{
    Npc* npc = new Npc();
    if(npc && npc->init(npcID))
    {
        npc->autorelease();
        return npc;
    }
    CC_SAFE_DELETE(npc);
    npc = NULL;
    return NULL;
}
void Npc::onActionCompleted()
{
    Avatar::onActionCompleted();
}
void Npc::onEnter()
{
    Avatar::onEnter();
    this->setTouchEnabled(true);
    m_touchCallBack = CC_CALLBACK_1(Npc::onNpcClick, this);
}
void Npc::onExit()
{
    Avatar::onExit();
    this->setTouchEnabled(false);
    m_touchCallBack = NULL;
}
void Npc::onNpcClick(Ref* pSender)
{
    GotoModule::gotoModuleByFunctionID(this->getDictNpc()->openFunction,SCENE_TAG_MAINUI);
}