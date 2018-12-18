//
//  CameraIn.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/7/14.
//
//

#include "CameraIn.h"
CameraIn::CameraIn()
:_initPositionZ(0)
,_endPositionZ(0)
,_deletaZ(0)
{
    
}
CameraIn::~CameraIn()
{
    
}
CameraIn* CameraIn::create(float duration, float endZ)
{
    CameraIn* camraIn = new CameraIn();
    if(camraIn && camraIn->initWithDuration(duration, endZ))
    {
        camraIn->autorelease();
        return camraIn;
    }
    CC_SAFE_DELETE(camraIn);
    camraIn = NULL;
    return NULL;
}
bool CameraIn::initWithDuration(float duration, float endZ)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!ActionInterval::initWithDuration(duration));
        this->_endPositionZ = endZ;
        bref = true;
    } while (false);
    return bref;
}
void CameraIn::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    _initPositionZ = target->getPositionZ();
    _deletaZ = _endPositionZ - _initPositionZ;
}
void CameraIn::update(float t)
{
    if(!_target)
    {
        return;
    }
    _target->setPositionZ(_initPositionZ + _deletaZ * t);

}