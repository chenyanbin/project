//
//  EnterWay.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/7/27.
//
//

#include "EnterWay.h"
void EnterWay::jumpIn(Avatar* avatar)//跳入
{
    if(!avatar->m_avatar)
    {
        avatar->onExitScene();
    }
    avatar->onEnterScene();
    avatar->idle();
    Point cp = avatar->getPosition();
    if( avatar->m_avatar)
    {
        avatar->m_avatar->setPositionY(avatar->m_avatarPosY);
        avatar->setPositionY(800);
    }
    MoveTo* moveto = MoveTo::create(.2, cp);
    CallFunc* callBack = NULL;//CallFunc::create(CC_CALLBACK_0(Avatar::idle, avatar));
    avatar->runAction(Sequence::create(moveto,callBack,NULL));
    
}
