//
//  StoryTalk.h
//  FightPass
//
//  Created by zhangxiaobin on 15/8/31.
//
//

#ifndef __FightPass__StoryTalk__
#define __FightPass__StoryTalk__

#include "../BaseLayer.h"
#include "../../commonData/dictData/DictStory/DictStoryManager.h"
class StoryTalk:public BaseLayer
{
public:
    StoryTalk();
    ~StoryTalk();
    virtual bool init();
    CREATE_FUNC(StoryTalk);
public:
    void showContent(DictStory* story);
    const char* getHeadPath();
    void showLeftHead(const char* path);
    void showRightHead(const char* path);
    void showTalkContent();
    void showTalkerName();
protected:
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
public:
    ccMenuCallback callBack;
private:
    DictStory* m_dictStory;
    Sprite* leftTalkSpr;
//    Sprite* rightTalkSpr;
    string leftHeadPath;
    string rightHeadPath;
    Sprite* leftHead;//左边人物
    Sprite* rightHead;//右边人物

private:
    int TAG_TEXT;
    int TAG_NAME;
};

#endif /* defined(__FightPass__StoryTalk__) */
