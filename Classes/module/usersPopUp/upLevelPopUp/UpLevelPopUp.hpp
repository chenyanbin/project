//
//  UpLevelPopUp.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/9.
//
//

#ifndef UpLevelPopUp_hpp
#define UpLevelPopUp_hpp

#include "../UserPopUp.hpp"
class UpLevelPopUp:public UserPopUp
{
public:
    UpLevelPopUp();
    ~UpLevelPopUp();
    virtual bool init(int newLevel);
    static UpLevelPopUp* create(int newLevel);
 
protected:
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void onDataLoaded(float percent);
    void setItems();
    void setTitle();
    Node* getItemNode(const char* title,int preValue,int nowValue);
    Node* getFunctionOpenNode(int functionId);
private:
    string effectName;
    int m_level;
};

#endif /* UpLevelPopUp_hpp */
