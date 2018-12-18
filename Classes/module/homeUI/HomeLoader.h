//
//  HomeLoader.h
//  FightPass
//
//  Created by 超 顾 on 15/7/9.
//
//

#ifndef __FightPass__HomeLoader__
#define __FightPass__HomeLoader__
#include "cocos2d.h"
#include "../../common/Dialog/Dialog.h"
USING_NS_CC;

class HomeLoader: public Scene
{
public:
    HomeLoader();
    ~HomeLoader();
    virtual bool init(int fromeScene);
    static HomeLoader* create(int fromeScene);
    static void show(int fromeScene);
protected:
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
private:
    void addMonsterList();
    void addHeroList();    
    void startLoad();
    void imageAsyncCallback(Ref* pSender);
    
    void loadAvatarResource();
    void onAvatarLoaded(float percent);
    
    void parseBattleResource();//解析战场资源
    void loadTmxImage();
    void parseXMLDoc(const char* content);
private:
    vector<string>* tmxList;
    vector<string>* heroList;
    vector<string>* monsterList;
    string resourcePre;//路径前缀
    int m_battleID;
    int m_fromeScene;
    PopupLoading* popUpLoading;
    
    float totalNum;
    float loadedNum;
    static bool IS_IN_HOMELOADER;
};

#endif /* defined(__FightPass__HomeLoader__) */
