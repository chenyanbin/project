//
//  NewPlayerGuild.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 14-9-10.
//
//

#include "NewPlayerGuild.h"
#include "../../common/GameConfig.h"
#include "../../commonData/dictData/DictStage/DictStageManager.h"
#include "../../message/Decoding/newGuide/SendNewGuideMsg.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../commonData/data/FunctionOpenManager.h"
#include "../battle/battleUI/AngryProgressManager.h"
NewPlayerGuild* NewPlayerGuild::_instance = NULL;

NewPlayerGuild::NewPlayerGuild()
:m_curStep(0)
,m_functionID(0)
,guideScene(NULL)
,guideContent(NULL)
,guideList(NULL)
,curGuideData(NULL)
,openList(NULL)
,stageBattleList(NULL)

{
    
    init();
}
NewPlayerGuild::~NewPlayerGuild()
{
    if(guideList)
    {
        CC_SAFE_DELETE(guideList);
        guideList = NULL;
        curGuideData = NULL;
    }
    CC_SAFE_RELEASE_NULL(guideScene);
    CC_SAFE_RELEASE_NULL(guideContent);
    CC_SAFE_DELETE(stageBattleList);
    stageBattleList = NULL;
    openList->clear();
    openList = NULL;
}
bool sortGuildList(DictNewGuide* a,DictNewGuide* b)
{
    return a->id < b->id;
}
bool sortStageBattle(DictStageBattle* a,DictStageBattle* b)
{
    return a->id < b->id;
}
bool NewPlayerGuild::init()
{
   
    stageBattleList = DictStageBattleManager::getInstance()->getDataList();
    sort(stageBattleList->begin(), stageBattleList->end(), sortStageBattle);
    
    guideList = DictNewGuideManager::getInstance()->getDataList();
    sort(guideList->begin(), guideList->end(), sortGuildList);
    if(guideScene == NULL)
    {
        guideScene = GuideScene::create();
        guideScene->setAnchorPoint(Point::ZERO);
        this->scaleToscaleX();
        CC_SAFE_RETAIN(guideScene);

    }
    if(guideContent == NULL)
    {
        guideContent = GuideContent::create();
        guideContent->setAnchorPoint(Point::ZERO);
  
        CC_SAFE_RETAIN(guideContent);
        guideContent->setPosition(VisibleRect::leftBottom());
    }
    
    openList = new Vector<GuideData*>();
    return true;
}
void NewPlayerGuild::start()
{
    if(GlobalInfo::getInstance()->isShowGuide == false)
    {
        return;
    }
    this->curGuideData = guideList->at(0);
    this->m_functionID = curGuideData->function;
    this->m_curStep = 1;
    GlobalInfo::getInstance()->isGuiding = true;
    showGuideContent(this->m_functionID ,this->m_curStep );
}
bool NewPlayerGuild::isNowGuideEvent(int guideEvent)
{
    bool bref= false;
    if(GlobalInfo::getInstance()->isGuiding && curGuideData)
    {
        if(curGuideData->newGuideEvent == guideEvent
           || curGuideData->newGuideEvent == 0)
        {
            bref = true;
        }
    }
    else
    {
        bref = true;
    }
    return bref;
}
bool comparisFunctionOpen(DictFunction* a,DictFunction* b)
{
    return a->id < b->id;
}
bool NewPlayerGuild::onUserLevelUp(int level)   //玩家升级了。
{

    if(GlobalInfo::getInstance()->isShowGuide == false)
    {
        return false;
    }

    Vector<DictFunction*>* list = DictFunctionManager::getInstance()->getDataList();
    sort(list->begin(), list->end(), comparisFunctionOpen);
    DictFunction* tempData = NULL;
    ssize_t len = list->size();
    for(int i = 0; i <len; i++)
    {
        tempData = list->at(i);
  
        if(tempData->roleLevel == level)
        {
            if(tempData->id == this->m_functionID && this->m_curStep > 1)
            {
                log("等经已经引导了。。。");
                break;;
            }
            if(!this->isInGuideList(tempData->id))
            {
                continue;
            }
            int openStep = this->getOpenFuntionStep(tempData->id);
            
            if(openStep > 0)
            {
                if(GlobalInfo::getInstance()->isFirstEnterMainScene)
                {
                    int index = getBreadkPointIndex(tempData->id,openStep);
                    if(index)
                    {
                         NewPlayerGuild::getInstance()->showGuideContent(tempData->id,index);
                    }
                   
                }
                else
                {
                    NewPlayerGuild::getInstance()->showGuideContent(tempData->id, 1);
                }
            }
            
            else
            {
                if(!GlobalInfo::getInstance()->isGuiding)
                {
                    
                    if(GlobalInfo::getInstance()->isFirstEnterMainScene)
                    {
                        int index = getBreadkPointIndex(tempData->id,openStep == 0? 1 : openStep);
                        NewPlayerGuild::getInstance()->showGuideContent(tempData->id,index);
                    }
                    else
                    {
                        if(this->addFunction(this->m_functionID, this->m_curStep))
                        {
                            sendNewGuideMsg();
                        }
                        NewPlayerGuild::getInstance()->showGuideContent(tempData->id, 1);
                    }
                    
                    return true;
                }
                else
                {
                    return true;
                    log("正在别的引导中。。。:");
                }
                
            }

            break;
        }
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return false;
}
int NewPlayerGuild::getStageBattleIndex(int stageBattleID)
{
    DictStageBattle* stageBattle = DictStageBattleManager::getInstance()->getData(stageBattleID);
    int stageID = stageBattle->inStageId;
    ssize_t len = stageBattleList->size();
    int index = 0;
    for(int i = 0; i < len; i++)
    {
        stageBattle = stageBattleList->at(i);
        if(stageBattle->inStageId == stageID)
        {
            index ++;
            if(stageBattle->id == stageBattleID)
            {
                return index;
            }
        }
    }
    return -1;
}
void NewPlayerGuild::onStageBattleOver(int stageBattleID)//玩家通过了某个关卡
{
    log("通过关过id===%d",stageBattleID);
    if(GlobalInfo::getInstance()->isShowGuide == false)
    {
        return;
    }
//    int index = getStageBattleIndex(stageBattleID);
//    if(index != 3)
//    {
//        log("不是最后一个关卡");
//        return;
//    }
//
    DictFunction* tempData = isInFunctionOpenList(stageBattleID);
    if(tempData)
    {
        FunctionOpenManager::getInstance()->setFunctionStatus(tempData->id, FunctionOpenData::STATUS_OPEN);//防止服务器未开启 ，所以客户端强制开启了。
        GlobalInfo::getInstance()->isGuiding = true;
        if(tempData->id == this->m_functionID && this->m_curStep > 1)
        {
            next();
        }
        else
        {
            NewPlayerGuild::getInstance()->showGuideContent(tempData->id, 1);
        }
    }
    else
    {
      
        next();
        log("此关卡没有开启新功能");
    }
}
DictFunction* NewPlayerGuild::isInFunctionOpenList(int stageBattleID)//是否在功能开放列表里
{
  
    Vector<DictFunction*>* tempList = new Vector<DictFunction*>();
    Vector<DictFunction*>* list = DictFunctionManager::getInstance()->getDataList();
    DictFunction* tempData = NULL;
    for(DictFunction* data : *list)
    {
        if(data->battleId == stageBattleID)
        {
            tempList->pushBack(data);
        }
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    
    for(DictNewGuide* newguide : * guideList)
    {
        for(DictFunction* data : *tempList)
        {
            if(data->id == newguide->function && !isOpened(newguide->function, 1))//
            {
                tempData = data;
                break;
            }
        }
        
    }
    
    return tempData;
}
void NewPlayerGuild::pause()
{
    if(this->guideScene && this->guideScene->getParent())
    {
        this->guideScene->removeFromParent();
    }
    if(guideContent && guideContent->getParent())
    {
        guideContent->removeFromParent();
    }
   
    PublicShowUI::broadUserMsg(CUSTOM_RESET_AVATAR_ACTION, NULL);
  
    
}
bool NewPlayerGuild::isInActionTeaching()//是否动作教学中
{
    if(!GlobalInfo::getInstance()->isGuiding || !GlobalInfo::getInstance()->isShowGuide)
    {
        return false;
    }
//    if(this->curGuideData && this->curGuideData->id == 3)
//    {
//        return true;
//    }
    return false;
}
void NewPlayerGuild::onMainHeroActionEnded()
{
    
    if(this->isInActionTeaching())
    {
        PublicShowUI::broadUserMsg(CUSTOM_PAUSE_AVATAR_ACTION, NULL);
    }
}
void NewPlayerGuild::sendNewGuideMsg()
{
    SendNewGuideMsg* msg = new SendNewGuideMsg(this->m_functionID,this->m_curStep);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void NewPlayerGuild::showGuideByGuideId(int guideID)
{
    DictNewGuide* newguide = DictNewGuideManager::getInstance()->getData(guideID);
    if(newguide)
    {
        curGuideData = NULL;
        this->showGuideContent(newguide->function, newguide->orderIndex);
    }
}
void NewPlayerGuild::showGuideContent(int functionID,int _step)//显示当前引导内容
{
    log("functionID==%d,_stope=%d",functionID,_step);
    int oldFunctionID = this->m_functionID;
    int oldStep = this->m_curStep;
    
    if(!this->isOpened(oldFunctionID, oldStep) && curGuideData && curGuideData->isToSever)//
    {//就将这个功能的引导设置为完成状态
        
        if(this->addFunction(m_functionID, m_curStep))
        {
             sendNewGuideMsg();
        }
       
    }
    
    this->m_functionID = functionID;
    this->m_curStep = _step;
    if(curGuideData && curGuideData->isPause)
    {
        m_functionID = oldFunctionID;
        m_curStep = oldStep;
        pause();
        this->curGuideData = NULL;
        return;
    }
    
    DictNewGuide* data =  getNextData();
    if(!data)
    {
        m_functionID = oldFunctionID;
        m_curStep = oldStep;
        pause();
        GlobalInfo::getInstance()->isGuiding = false;
        if(!this->isOpened(m_functionID, m_curStep) && curGuideData && curGuideData->isToSever)
        {//将这个功能的引导设置为完成状态
            if(this->addFunction(curGuideData->function, m_curStep))
            {
                sendNewGuideMsg();
            }
        }
        return;
        
    }
    if(curGuideData && curGuideData->function != data->function)
    {
        if(this->addFunction(curGuideData->function, m_curStep))
        {
            sendNewGuideMsg();
        }
        
    }

    curGuideData = data;
    if(curGuideData->bottomId == DictNewGuideEventEnumAngerTube || curGuideData->bottomId == DictNewGuideEventEnumAngerSkill)
    {
        if(!AngryProgressManager::getInstance()->isVisible())
        {
            NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumAngerSkill);
            NewPlayerGuild::getInstance()->pause();
            return;
        }
    }
    
    
    m_functionID = curGuideData->function;
    m_curStep = curGuideData->orderIndex;
    Scene* scene =  Director::getInstance()->getRunningScene();

    guideContent->setVisible(data->resource);
    guideContent->updateGuideData(data);
    guideScene->updateGuideData(data);

    
    if(guideContent->getParent() == NULL)
    {
//        guideContent->showGuider();
        scene->addChild(guideContent , SCENE_POPLAYER_ZORDER - 1);
    }
    if(this->guideScene->getParent() == NULL)
    {
        scene->addChild(guideScene, SCENE_POPLAYER_ZORDER);
    }
    GlobalInfo::getInstance()->isGuiding = true;
    
    if(curGuideData->bottomId == DictNewGuideEventEnumSkillAttack1)
    {
        PublicShowUI::broadUserMsg(CUSTOM_SHOW_SKILL1_BTN, NULL);
    }
    else if(curGuideData->bottomId == DictNewGuideEventEnumSkillAttack2)
    {
         PublicShowUI::broadUserMsg(CUSTOM_SHOW_SKILL2_BTN, NULL);
    }
    else if(curGuideData->bottomId == DictNewGuideEventEnumSkillAttack3)
    {
        PublicShowUI::broadUserMsg(CUSTOM_SHOW_SKILL3_BTN, NULL);
    }
    else if(curGuideData->bottomId == DictNewGuideEventEnumDodgeParryButton)
    {
        PublicShowUI::broadUserMsg(CUSTOM_SHOW_PROTECTED_BTN, NULL);
        PublicShowUI::broadUserMsg(CUSTOM_PAUSE_AVATAR_ACTION, NULL);
    }

}
bool NewPlayerGuild::addFunction(int functionID,int _step)
{
    if(this->isOpened(functionID, _step))
    {
        log("已经开启过了111111");
        return false;
    }
    GuideData* data = new GuideData();
    data->autorelease();
    data->functionID = functionID;
    data->step = _step;
   
    this->openList->pushBack(data);
    return true;
}
//清空以开放的功能列表
void NewPlayerGuild::clearList()
{
    this->openList->clear();
}
void NewPlayerGuild::scaleToMax()//最大值缩放
{
    if(this->guideScene)
    {
        float max = MAX(GlobalInfo::getInstance()->screenScaleX, GlobalInfo::getInstance()->screenScaleY);
        this->guideScene->setScale(max);
    }
}
void NewPlayerGuild::scaleToScaleY()//关卡缩放
{
    if(guideScene)
    {
       
        guideScene->setScale(GlobalInfo::getInstance()->screenScaleX,GlobalInfo::getInstance()->screenScaleY);
    }
}
void NewPlayerGuild::scaleToscaleX()//普通缩放试
{
    if(guideScene)
    {
        guideScene->setScale(GlobalInfo::getInstance()->screenScaleX);
    }
}
void NewPlayerGuild::alignToSceneBottom()//底部对齐
{
    if(guideScene)
    {
        guideScene->setPosition(VisibleRect::leftBottom());
    }
}
void NewPlayerGuild::alignToSceneCenter()//中心对齐
{
    if(guideScene )
    {

        guideScene->setPositionX(VisibleRect::center().x - guideScene->getContentSize().width * GlobalInfo::getInstance()->screenScaleX/2);
        guideScene->setPositionY(VisibleRect::center().y - guideScene->getContentSize().height * GlobalInfo::getInstance()->screenScaleX/2);
    }

}

NewPlayerGuild* NewPlayerGuild::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new NewPlayerGuild();
    }
    return _instance;
}
void NewPlayerGuild::destoryInstance()
{
    if(_instance)
    {
        delete _instance;
        _instance = NULL;
    }
}

bool NewPlayerGuild::isOpened(int functionID ,int _step)
{
    int openStep = this->getOpenFuntionStep(functionID);
    if(_step <= openStep)
    {
        return true;
    }
    return false;

}
int NewPlayerGuild::getOpenFuntionStep(int functionID)
{
    ssize_t len = this->openList->size();
    GuideData* data = NULL;
    for(int i = 0;i <len; i++)
    {
        data = openList->at(i);
        if(data->functionID == functionID)
        {
            return data->step;
        }
    }
    
    return 0;
}
bool NewPlayerGuild::isInGuideList(int functionID)
{
    for(DictNewGuide* data : *guideList)
    {
        if(data->function == functionID)//
        {
            return true;
        }
    }
    return false;
}
void NewPlayerGuild::showNowGuide()
{
    if(m_functionID == 0 && m_curStep == 0)
    {
        return;
    }
    if(GlobalInfo::getInstance()->isGuiding ==false)
    {
        return;
    }
    curGuideData = NULL;
    showGuideContent(this->m_functionID, this->m_curStep);
}
void NewPlayerGuild::next(int buttonID)
{
    
    if(isShowing())
    {
        guideScene->hideArrow();
    }
    if(GlobalInfo::getInstance()->isShowGuide == false)
    {
        return;
    }
    if(GlobalInfo::getInstance()->isGuiding)
    {
        if((this->getNowData() && this->getNowData()->bottomId == buttonID) || buttonID == 0)
        {
 
            goNext();

        }
    }
    
}
bool NewPlayerGuild::isShowing()
{
    return this->guideScene && guideScene->getParent();
}
inline void NewPlayerGuild::goNext()
{

     showGuideContent(this->m_functionID, this->m_curStep + 1);
}
DictNewGuide* NewPlayerGuild::getNowData()
{
    return this->curGuideData;
}
inline int NewPlayerGuild::getBreadkPointIndex(int functionID,int step)
{
    for(DictNewGuide* data : *guideList)
    {
        if(data->function == functionID)//
        {
           if(data->breakpoint && data->orderIndex >= step)
           {
               return data->orderIndex;
           }
        }
    }
    return 0;
}
inline DictNewGuide* NewPlayerGuild::getNextData()
{
    for(DictNewGuide* data : *guideList)
    {
        if(data->function == this->m_functionID && data->orderIndex == m_curStep)//
        {
          
            return data;
        }
    }
    return NULL;
}