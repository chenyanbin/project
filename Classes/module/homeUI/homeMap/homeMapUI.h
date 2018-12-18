//
//  homeMapUI.h
//  FightPass
//
//  Created by 超 顾 on 15/6/2.
//
//

#ifndef __FightPass__homeMapUI__
#define __FightPass__homeMapUI__

#define BG_RATE 1
#define MID_RATE 1
#define NEAR_RATE 1
#define CLOSE_RATE 1

#include "../../BaseLayer.h"
#include "cocos2d.h"
#include "../../../avatar/hero/Hero.h"
#include "../../battle/simplePad/SimplePad.h"
#include "../../../avatar/npc/Npc.h"
class HomeMapUI: public BaseLayer,public SimplePadDelegate
{
public:
    HomeMapUI();
    ~HomeMapUI();
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    static HomeMapUI* create();
    
    
    virtual void didChangeDirectorTo(SimplePad* simplepad,Point direction);
    virtual void isHoldingDirector(SimplePad* simplepad,Point direction);
    virtual void simplePadTouchEnded(SimplePad* simplepad);
   
private:
    void clearResourcePerson();//清除人物资源

    void mySelfBorn();
    void setOtherUserList();
    void loadAvatarResource();
    void onOtherPersonLoaded(float percent);
    
    void loadNpcResource();
    void onNpcLoaded(float percent);
    void setBackground();
    virtual void setCloseMapZorder();
//    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    void NpcBorn();
    void update(float dt);
    void setViewPointCenter(bool isTween = true);
    void stopWalk();
    void createOtherHero(float dt);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    
   
//    npcList
private:
    Node* m_mapContainer;//地图容器
    TMXTiledMap* bg_map;//背景图
    TMXTiledMap* near_map;//
    TMXTiledMap* mid_map;//
    TMXTiledMap* close_map;//
    Hero* mySelfHero;//自己
    int m_loadedIndex;
    Vector<Npc*>* _NpcList;
    float scaleMax;
    float mapScaleX;
    Size m_winSize;
    float _mapWidth;
    float _mapHeight;
    int _maxZorder;
    int maxHeroCount;
    
public:
    static Point INITPOINT;
};

#endif /* defined(__FightPass__homeMapUI__) */