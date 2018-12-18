//
//  BodyPowerPanel.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/12/29.
//
//

#ifndef BodyPowerPanel_hpp
#define BodyPowerPanel_hpp

#include "../BaseLayer.h"
class BodyPowerPanel:public BaseLayer
{
public:
    BodyPowerPanel();
    ~BodyPowerPanel();
    virtual bool init();
    CREATE_FUNC(BodyPowerPanel);
    static void show(int fromeMoudle);
    void initFromeMoudle(int fromeMoudle);
protected:
    virtual void onEnter();
    virtual void onExit();
private:
    void gotoMall(Node* pSender);
    int m_fromeMoudle;
    int TAG_PANEL;
};

#endif /* BodyPowerPanel_hpp */
