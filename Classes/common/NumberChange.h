//
//  NumberChange.h
//  FightPass
//
//  Created by 超 顾 on 15/10/15.
//
//

#ifndef __FightPass__NumberChange__
#define __FightPass__NumberChange__

#ifndef __MISC_NODE_CCNUMBER_CHANGE_H__
#define __MISC_NODE_CCNUMBER_CHANGE_H__

#include <vector>

#include "2d/CCAction.h"
#include "2d/CCAnimation.h"
#include "2d/CCActionInterval.h"
#include "CCProtocols.h"
#include "CCVector.h"

//NS_CC_BEGIN
#include "cocos2d.h"
USING_NS_CC;



class NumberChange : public ActionInterval
{
public:
    
    static NumberChange* create(float duration, int fromNum, int toNum);
    
    virtual NumberChange* clone() const override;
    virtual NumberChange* reverse(void) const  override;
    virtual void startWithTarget(cocos2d::Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    NumberChange();
    virtual ~NumberChange();
    
    /** initializes the action */
    bool initWithDuration(float duration, int fromNum, int toNum);
    
protected:
    int _fromNum;
    int _toNum;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(NumberChange);
};

//NS_CC_END

#endif //__MISC_NODE_CCNUMBER_CHANGE_H__

#endif /* defined(__FightPass__NumberChange__) */
