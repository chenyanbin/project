//
//  FunctionOpenPopUp.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/9.
//
//

#ifndef FunctionOpenPopUp_hpp
#define FunctionOpenPopUp_hpp

#include "../UserPopUp.hpp"
class FunctionOpenPopUp:public UserPopUp
{
public:
    FunctionOpenPopUp();
    ~FunctionOpenPopUp();
    virtual bool init(int functionID);
    static FunctionOpenPopUp* create(int functionID);
protected:
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void setIcon();
    void onDataLoaded(float percent);
    void onIconEffectLoaded(float percent);
    void loadIconEffect();
private:
    int m_functionID;
    string effectName;
    string functionEffectName;
};

#endif /* FunctionOpenPopUp_hpp */
