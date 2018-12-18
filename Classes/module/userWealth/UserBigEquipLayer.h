//
//  UserBigEquipLayer.h
//  FightPass
//
//  Created by 超 顾 on 15/10/27.
//
//

#ifndef __FightPass__UserBigEquipLayer__
#define __FightPass__UserBigEquipLayer__

#include "../BaseLayer.h"
#include "../generals/generalsMaterial/GeneralsMaterial_Layer.h"
class UserBigEquipLayer:public BaseLayer
{
public:
    UserBigEquipLayer();
    ~UserBigEquipLayer();
    virtual bool init(MaterData* _data);
    static UserBigEquipLayer* create(MaterData* _data);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
protected:
    virtual void backScene();
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
private:
//    void setBackground();
    void setCardItem();
    void onClick(Ref* psender);
private:
    MaterData* materData;
};

#endif /* defined(__FightPass__UserBigEquipLayer__) */
