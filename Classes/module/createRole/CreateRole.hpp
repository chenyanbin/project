//
//  CreateRole.hpp
//  FightPass
//
//  Created by zhangbin on 16/4/15.
//
//

#ifndef CreateRole_hpp
#define CreateRole_hpp

#include "../BaseLayer.h"
class CreateRole:public BaseLayer
{
public:
    CreateRole();
    ~CreateRole();
    virtual bool init();
    CREATE_FUNC(CreateRole);
    static Scene* createScene(int fromeScene = SCENE_TAG_LOADING);
    static void show();
    
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();

private:
    void setRandNameLayer();
};

#endif /* CreateRole_hpp */
