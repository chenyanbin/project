//
//  BattleLoader.h
//  FightPass
//
//  Created by zhangxiaobin on 15/6/11.
//
//

#ifndef __FightPass__BattleLoader__
#define __FightPass__BattleLoader__

#include "../../common/Dialog/Dialog.h"
#include "cocos2d.h"
USING_NS_CC;
#include "editor-support/cocostudio/CCArmature.h"
using namespace cocostudio;
#include "../../net/bytestream.h"
class BattleLoader:public Scene
{
public:
    BattleLoader();
    ~BattleLoader();
    virtual bool init(ByteStream* bytestream,int fromeScene);
    static BattleLoader* create(ByteStream* bytestream,int fromeScene);
    static void show(ByteStream* bytestream,int fromeScene);
    static void requestStageBattle(int stageBattleID);
protected:
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
private:
    void addMonsterList();
    void addHeroList();
    
    void loadImage();
    void startLoad();
    void imageAsyncCallback(Ref* pSender);
    
    void loadAvatarResource();
    void onAvatarLoaded(float percent);
    
    void parseBattleResource();//解析战场资源
    void parseXMLDoc(const char* content);
    
    
private:
    vector<string>* tmxList;
    vector<string>* heroList;
    vector<string>* monsterList;
    vector<string>* envirEffectList;//环境特效列表
    string resourcePre;//路径前缀
    int m_battleID;
    int m_fromeScene;
    PopupLoading* popUpLoading;
    ByteStream* _byteStream;
    int totalNum;
    int loadedNum;
};

#endif /* defined(__FightPass__BattleLoader__) */
