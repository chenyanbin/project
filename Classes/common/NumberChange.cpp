//
//  NumberChange.cpp
//  FightPass
//
//  Created by 超 顾 on 15/10/15.
//
//

#include "2d/CCActionInterval.h"

#include <stdarg.h>

#include "2d/CCSprite.h"
#include "2d/CCNode.h"
#include "2d/CCSpriteFrame.h"
#include "2d/CCActionInstant.h"
#include "CCDirector.h"
#include "CCEventCustom.h"
#include "CCEventDispatcher.h"
#include "CCStdC.h"
#include "deprecated/CCString.h"
#include "NumberChange.h"

USING_NS_CC;
//NS_CC_BEGIN
NumberChange::NumberChange(){
}

NumberChange::~NumberChange(){
}

NumberChange* NumberChange::create(float duration, int fromNum, int toNum)
{
    NumberChange *ret = new (std::nothrow) NumberChange();
    ret->initWithDuration(duration, fromNum, toNum);
    ret->autorelease();
    
    return ret;
}


bool NumberChange::initWithDuration(float duration, int fromNum, int toNum)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _fromNum = fromNum;
        _toNum = toNum;
        return true;
    }
    
    return false;
}

NumberChange* NumberChange::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) NumberChange();
    a->initWithDuration(_duration, _fromNum, _toNum);
    a->autorelease();
    return a;
}

void NumberChange::startWithTarget(cocos2d::Node *target)
{
    ActionInterval::startWithTarget(target);
    LabelProtocol *pLabel = dynamic_cast<LabelProtocol*>(target);
    if (pLabel)
    {
        std::string numStr = cocos2d::StringUtils::format("%i", _fromNum);
        pLabel->setString(numStr.c_str());
    }
}

NumberChange* NumberChange::reverse() const
{
    return NumberChange::create(_duration, _toNum, _fromNum);
}


void NumberChange::update(float t)
{
    LabelProtocol *pLabel = dynamic_cast<LabelProtocol*>(_target);
    if (pLabel)
    {
        int tempNum = (_toNum - _fromNum) * t;
        int num = _fromNum + tempNum;
        std::string numStr = cocos2d::StringUtils::format("%i", num);
        pLabel->setString(numStr.c_str());
    }
}

//NS_CC_END