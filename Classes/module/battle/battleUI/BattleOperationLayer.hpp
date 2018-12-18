//
//  BattleOperationLayer.hpp
//  FightPass
//战场操作示例层
//  Created by zhangxiaobin on 16/1/11.
//
//

#ifndef BattleOperationLayer_hpp
#define BattleOperationLayer_hpp

#include "../../BaseLayer.h"
class BattleOperationLayer:public BaseLayer
{
public:
    BattleOperationLayer();
    ~BattleOperationLayer();
    virtual bool init();
    CREATE_FUNC(BattleOperationLayer);
protected:
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
};

#endif /* BattleOperationLayer_hpp */
