//
//  RankAddFriendLayer.hpp
//  FightPass
//
//  Created by chenyanbin on 16/2/1.
//
//  添加好友

#ifndef RankAddFriendLayer_hpp
#define RankAddFriendLayer_hpp

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../BaseLayer.h"

USING_NS_CC_EXT;
USING_NS_CC;
class RankAddFriendLayer:public BaseLayer
{
public:
    RankAddFriendLayer();
    ~ RankAddFriendLayer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(long heriId, string heroName );
    static RankAddFriendLayer* create(long heriId, string heroName );
    static void show(long heriId, string heroName );
private:
    void createLayer();
    void onSureBuyClick(Ref* psender);
    void onCencelClick(Ref* psender);
    void onAddFriendClick(long userId);
    void onaddfriendProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    
private:
    float sx;
    long m_roleId;
    string m_heroName;
    
};


#endif /* RankAddFriendLayer_hpp */
