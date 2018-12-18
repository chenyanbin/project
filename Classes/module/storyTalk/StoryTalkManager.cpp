//
//  StoryTalkManager.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/8/31.
//
//

#include "StoryTalkManager.h"
#include "../../commonData/enum/DictTriggerEnum.h"
#include "../../protocol/UserCustomEvent.h"
StoryTalkManager* StoryTalkManager::_instance = NULL;
StoryTalkManager::StoryTalkManager()
:talkList(NULL)
,m_index(0)
,storyTalkLayer(NULL)

{
    talkList = new Vector<DictStory*>();
    
    taskList = new Map<int,StoryData*>();
    battleList = new Map<int,StoryData*>();
   
    initData();
}
StoryTalkManager::~StoryTalkManager()
{
    CC_SAFE_DELETE(talkList);
    talkList = NULL;
    
    CC_SAFE_DELETE(taskList);
    taskList = NULL;
    CC_SAFE_DELETE(battleList);
    battleList = NULL;
    CC_SAFE_RELEASE_NULL(storyTalkLayer);
   
}
void StoryTalkManager::destoryInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}
bool comparisonStoryTalkLess(DictStory* n1, DictStory* n2)
{
    return n1->order < n2->order;
}
StoryTalkManager* StoryTalkManager::getInstance()
{
    if(!_instance)
    {
        _instance = new StoryTalkManager();
    }
    return _instance;
}
void StoryTalkManager::initData()
{
    StoryData* storyData = NULL;
    Vector<DictStory*>* list = DictStoryManager::getInstance()->getDataList();
    for(DictStory* data : *list)
    {
        if(data->triggerType == 1)
        {
            storyData = taskList->at(data->triggerId);
            if(!storyData)
            {
                storyData = new StoryData();
                storyData->autorelease();
                taskList->insert(data->triggerId, storyData);
            }
            storyData->dataList->pushBack(data);
        }
        else if(data->triggerType == 2)
        {
            storyData = battleList->at(data->triggerId);
            if(!storyData)
            {
                storyData = new StoryData();
                storyData->autorelease();
                battleList->insert(data->triggerId, storyData);
            }
            storyData->dataList->pushBack(data);
        }
     
    }
    CC_SAFE_DELETE(list);
    list = NULL;
}
void StoryTalkManager::onMonsterStart(int battleID)//怪物说话
{

    talkList->clear();
    m_index = 0;
    StoryData* storyData = battleList->at(battleID);
    if(!storyData || storyData->dataList->size() <= 0 || !GlobalInfo::getInstance()->isShowStoryTalk)
    {
        PublicShowUI::broadUserMsg(CUSTOM_MONSTER_TALK_END, NULL);
        return;
    }
    for(DictStory* data : *storyData->dataList)
    {
        if(data->triggerNode == 3)
        {
            talkList->pushBack(data);
        }
    }
    if(talkList->size() <= 0)
    {
        PublicShowUI::broadUserMsg(CUSTOM_MONSTER_TALK_END, NULL);
        return;
    }
    sort(talkList->begin(), talkList->end(), comparisonStoryTalkLess);
    showTalk();
}
void StoryTalkManager::onNextSpeakCallBack(Ref* pSender)
{
    if(talkList->size() <= 0 || m_index >= talkList->size())
    {
        this->storyTalkLayer->removeFromParent();
        CC_SAFE_RELEASE_NULL(storyTalkLayer);
        
        if(talkList->at(0)->triggerNode == 1)
        {
            PublicShowUI::broadUserMsg(CUSTOM_BEFOREFIGHT_TALK_END,NULL);
        }
        else if(talkList->at(0)->triggerNode == 2)
        {

             PublicShowUI::broadUserMsg(CUSTOM_OVERFIGHT_TALK_END,NULL);
        }
        else if(talkList->at(0)->triggerNode == 3)
        {
   
            PublicShowUI::broadUserMsg(CUSTOM_MONSTER_TALK_END,NULL);
        }
        
        
   
    }
    else
    {
        showTalk();
    }
    
}

void StoryTalkManager::onTaskRecevice(int taskID)
{
    talkList->clear();
    m_index = 0;
    StoryData* storyData = taskList->at(taskID);
    if(!storyData)
    {
        return;
    }
    for(DictStory* data : *storyData->dataList)
    {
        if(data->triggerNode == 1)
        {
            talkList->pushBack(data);
        }

    }
    sort(talkList->begin(), talkList->end(), comparisonStoryTalkLess);
     showTalk();
}
void StoryTalkManager::onTaskFinished(int taskID)
{
    talkList->clear();
    m_index = 0;
    StoryData* storyData = taskList->at(taskID);
    if(!storyData)
    {
        return;
    }
    for(DictStory* data : *storyData->dataList)
    {
        if(data->triggerNode == 2)
        {
            talkList->pushBack(data);
        }
    }
    
    sort(talkList->begin(), talkList->end(), comparisonStoryTalkLess);
     showTalk();
}

void StoryTalkManager::onStageBattleStart(int battleID)
{
    talkList->clear();
    m_index = 0;
    StoryData* storyData = battleList->at(battleID);
    if(!storyData || storyData->dataList->size() <= 0 || !GlobalInfo::getInstance()->isShowStoryTalk)
    {
        PublicShowUI::broadUserMsg(CUSTOM_BEFOREFIGHT_TALK_END, NULL);
        return;
    }
    for(DictStory* data : *storyData->dataList)
    {
        if(data->triggerNode == 1)
        {
            talkList->pushBack(data);
        }
    }
    if(talkList->size() <= 0)
    {
        PublicShowUI::broadUserMsg(CUSTOM_BEFOREFIGHT_TALK_END, NULL);
        return;
    }
    sort(talkList->begin(), talkList->end(), comparisonStoryTalkLess);
     showTalk();
    
}
void StoryTalkManager::onStageBattleOver(int battleID,bool isWin)
{
    log("StoryTalkManager::onStageBattleOver");
    talkList->clear();
    m_index = 0;
    StoryData* storyData = battleList->at(battleID);
    if(!storyData || !GlobalInfo::getInstance()->isShowStoryTalk)
    {
        log("没有剧情对话");
        PublicShowUI::broadUserMsg(CUSTOM_OVERFIGHT_TALK_END, NULL);
        return;
    }
     log("有剧情对话");
    for(DictStory* data : *storyData->dataList)
    {
        if(data->triggerNode == 2)
        {
            talkList->pushBack(data);
        }
    }
    if(talkList->size() <= 0)
    {
        log("说话结束。战斗结束");
        PublicShowUI::broadUserMsg(CUSTOM_OVERFIGHT_TALK_END, NULL);
        return;
    }
    if(isWin)
    {
        sort(talkList->begin(), talkList->end(), comparisonStoryTalkLess);
        showTalk();
    }
    else
    {
         PublicShowUI::broadUserMsg(CUSTOM_OVERFIGHT_TALK_END, NULL);
    }
   
}
                         
void StoryTalkManager::showTalk()
{
   log("showTalk ，显示说话内容");
    Scene* scene = Director::getInstance()->getRunningScene();
    if(talkList->size() <= 0 || m_index >= talkList->size())
    {
        log("没有谈话内容");
        PublicShowUI::broadUserMsg(CUSTOM_OVERFIGHT_TALK_END, NULL);
        return;
    }
    if(!this->storyTalkLayer)
    {
        storyTalkLayer = StoryTalk::create();
        storyTalkLayer->setAnchorPoint(Point::ZERO);
        storyTalkLayer->callBack = CC_CALLBACK_1(StoryTalkManager::onNextSpeakCallBack, this);
        PublicShowUI::setTargetScale(storyTalkLayer,false,false);
        storyTalkLayer->setPositionX(VisibleRect::center().x - storyTalkLayer->getContentSize().width * GlobalInfo::getInstance()->screenScaleX/2);
        storyTalkLayer->setPositionY(VisibleRect::bottom().y + 100 * GlobalInfo::getInstance()->screenScaleY);
        scene->addChild(storyTalkLayer);
        CC_SAFE_RETAIN(storyTalkLayer);
    }
    storyTalkLayer->showContent(talkList->at(m_index));
    m_index ++;
}
bool StoryTalkManager::isTalking()
{
    return storyTalkLayer && storyTalkLayer->getParent() != NULL;
}