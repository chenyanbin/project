//
//  CameraIn.h
//  FightPass
//
//  Created by zhangxiaobin on 15/7/14.
//
//

#ifndef __FightPass__CameraIn__
#define __FightPass__CameraIn__

#include "cocos2d.h"
USING_NS_CC;
class CameraIn:public ActionInterval
{
public:
    CameraIn();
    ~CameraIn();
    
    static CameraIn* create(float duration, float endZ);
    //
    // Overrides
    //
   	virtual CameraIn* reverse() const override {return NULL;};
    virtual CameraIn* clone() const override {return NULL;};
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

protected:
    bool initWithDuration(float duration, float endZ);
    float _initPositionZ;
    float _endPositionZ;
    float _deletaZ;
 
};

#endif /* defined(__FightPass__CameraIn__) */
