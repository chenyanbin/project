//
//  StoryTalkManager.h
//  FightPass
//
//  Created by zhangxiaobin on 15/8/31.
//
//

#ifndef __FightPass__StoryTalkManager__
#define __FightPass__StoryTalkManager__
#include "StoryTalk.h"
#include "cocos2d.h"
USING_NS_CC;
class StoryData:public Ref
{
public:
    StoryData():_id(0),dataList(NULL)
    {
        dataList = new Vector<DictStory*>();
    }
    ~StoryData()
    {
        CC_SAFE_DELETE(dataList);
        dataList = NULL;
    }
    int _id;
    Vector<DictStory*>* dataList;
};
class StoryTalkManager
{
public:
    StoryTalkManager();
    ~StoryTalkManager();
    static void destoryInstance();
    static StoryTalkManager* getInstance();
    void onTaskRecevice(int taskID);
    void onTaskFinished(int taskID);
    
    void onStageBattleStart(int battleID);
    void onStageBattleOver(int battleID,bool isWin);
    
    void onMonsterStart(int battleID);//怪物说话
    bool isTalking();//是否说话中。
private:
    void initData();
    void showTalk();
    void onNextSpeakCallBack(Ref* pSender);
private:
    static StoryTalkManager* _instance;
    
    Map<int, StoryData*>* taskList;//任务列表
    Map<int,StoryData*>* battleList;//战斗列表
  
    Vector<DictStory*>* talkList;
private:
    int m_index;
    StoryTalk* storyTalkLayer;
};

#endif /* defined(__FightPass__StoryTalkManager__) */
