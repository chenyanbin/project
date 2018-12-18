//
//  ChapterLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/7/29.
//
//

#include "ChapterLayer.h"
#include "../userWealth/UserWealthLayer.h"
#include "chapterList/ChapterListLayer.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../message/Decoding/stage/RequestChapterMsg.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../common/Dialog/Dialog.h"
#include "chapterType/ChapterType.h"
#include "../sweep/SweepLayer.h"
#include "../battle/BattleLoader.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "../../message/Decoding/stage/RequestStageMsg.h"
#include "../newPlayerGuide/NewPlayerGuild.h"
#include "../../commonData/data/FunctionOpenManager.h"
#include "../../common/CustomMsgProcesser.h"
#include "../../common/StringUtil.h"
#include "../../commonData/dictData/DictTips/DictTipsManager.h"
ChapterLayer::ChapterLayer()
:chapterList(NULL)
,m_chapter(NULL)
,TAG_CHAPTERLIST(1)
,TAG_USERWEALTH(2)
,m_nowIndex(0)
,isLastPage(false)
,_cloundArmature(NULL)
{
    
}
ChapterLayer::~ChapterLayer()
{
    this->setClickEnabled(false);
    CC_SAFE_DELETE(chapterList);
    chapterList = NULL;
    m_chapter = NULL;
    _cloundArmature = NULL;
}
inline bool sortChapterList(const DictChapter* pair1, const DictChapter* pair2)
{
    return pair1->indexOrder < pair2->indexOrder;
}

bool ChapterLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->isAnimation = false;
        setMask();
        chapterList =DictChapterManager::getInstance()->getDataList();
        std::sort(chapterList->begin(), chapterList->end(), sortChapterList);
        float sx = GlobalInfo::getInstance()->screenScaleX;
        this->setBackBtn(0,15*sx,true);
        setChapterList();
        this->setClickEnabled(false);
        bref = true;
    } while (false);
    return bref;
}
ChapterLayer* ChapterLayer::create()
{
    ChapterLayer* layer= new ChapterLayer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}
void ChapterLayer::setMask()
{
    Sprite* layer = Sprite::create(IMG_PUBLIC_MASK);
    layer->setAnchorPoint(Point::ZERO);
    layer->setOpacity(100);
    PublicShowUI::setTargetScale(layer,true);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2,VisibleRect::center().y - layer->getContentSize().height/2);
    this->addChild(layer,1);
}
ChapterLayer* ChapterLayer::show()
{
    Director::getInstance()->purgeCachedData();
    ChapterLayer* layer = ChapterLayer::create();
//    if(FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumMusou))
//    {
//        layer->setFromScene(SCENE_TAG_GOTOBATTLE);
//    }
//    else
//    {
       layer->setFromScene(SCENE_TAG_MAINUI);
//    }
   
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    
    Scene* scene = Scene::create();
    scene->addChild(layer,0,SCENE_TAG_CHAPTER);
    
    Director::getInstance()->replaceScene(scene);
    return layer;
    
}
void ChapterLayer::requestStageBattle(int stageID,StageMode stageMode)
{
    Dialog::showServerLoading(.5);
    GlobalInfo::getInstance()->stageMode = stageMode;
    RequestStageMsg* msg = new RequestStageMsg(stageID);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
//chapterid=0表示 请求当前进行到的章节进度
void ChapterLayer::requestChapterByID(int chapterID)
{
    if(GlobalInfo::getInstance()->stageMode == StageMode::kStageModeBest)
    {
        if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumCampaignElite))
        {
            FunctionOpenManager::getInstance()->showNoOpenNotice(DictFunctionEnumCampaignElite);
            return;
        }
    }
     if(GlobalInfo::getInstance()->stageMode == StageMode::kStageModeCommon)
     {
         DictChapter* dictChapter = DictChapterManager::getInstance()->getData(chapterID);
         
         if(dictChapter && GlobalInfo::getInstance()->gameRole->level < dictChapter->levelOpen)
         {
             DictTips* dictTips = DictTipsManager::getInstance()->getData(6001014);
             string str = StringUtil::replace(dictTips->desc, "#1#",PublicShowUI::numberToString(dictChapter->levelOpen));
             NoticeManager::getInstance()->showNotice(str.c_str());
             return;
         }
     }
    
    
    Dialog::showServerLoading(1);
    RequestChapterMsg* msg  = new RequestChapterMsg(chapterID);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
   
}
void ChapterLayer::onMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_BATTLE_ChapterOpenBoxResp)
    {
        if(message->state)
        {
//            NoticeManager::getInstance()->showNotice("开启宝箱成功",NoticeManager::COLOR_GREEN);
            m_chapter->updateChapterStar(message->byteStream);
        }
       
    }
}
void ChapterLayer::setSelectedChapter(ByteStream* byteStream)
{
    int chapterID = byteStream->getInt();
//    if(m_chapter && chapterID == this->m_chapter->getChapter()->id)
//    {
//        return;
//    }
    ssize_t len = chapterList->size();
    DictChapter* data = NULL;
    int index = 0;
    for( index = 0; index < len; index++)
    {
        data = chapterList->at(index);
        if(data->id == chapterID)
        {
            break;
        }
    }
    
    ChapterListLayer* layer = (ChapterListLayer*)this->getChildByTag(TAG_CHAPTERLIST);
    layer->setSelectedByIndex(index);
    Point cp = Point::ZERO;
    if(m_chapter)
    {
        cp.x = m_chapter->getContentSize().width;
        cp.x = index > m_nowIndex ? cp.x : -cp.x;
    }
    Chapter* chapter = Chapter::create(chapterList->at(index)->id,byteStream);
    chapter->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(chapter,false);
    chapter->setPosition(cp);
    
    if(m_chapter)
    {
        m_chapter->clear();
        cp = m_chapter->getPosition();
        cp.x = index > m_nowIndex ? -m_chapter->getContentSize().width : m_chapter->getContentSize().width;
        MoveTo* move = MoveTo::create(.1, cp);
        EaseSineIn* easeIn = EaseSineIn::create(move);
        RemoveSelf* remove = RemoveSelf::create();
        m_chapter->runAction(Sequence::create(easeIn, remove,NULL));
        
        MoveTo* move1 = MoveTo::create(.1, Point::ZERO);
        EaseSineIn* easeIn1 = EaseSineIn::create(move1);
        chapter->runAction(easeIn1);
    }
    m_chapter = chapter;
    m_nowIndex = index;

    this->addChild(m_chapter,0);
  

}
void ChapterLayer::showChapterType()
{
    ChapterType* layer = ChapterType::create();
    layer->setAnchorPoint(Point::ZERO);

    layer->setPosition(VisibleRect::right().x - layer->getContentSize().width/2 - 50 * GlobalInfo::getInstance()->screenScaleX ,VisibleRect::center().y  - 5 * GlobalInfo::getInstance()->screenScaleY);
    this->addChild(layer,101);

}
void ChapterLayer::setChapterList()
{
    ChapterListLayer* listLayer = ChapterListLayer::create(chapterList->size(), CC_CALLBACK_1(ChapterLayer::onChapterClick, this));
    listLayer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(listLayer);
    listLayer->setPosition(VisibleRect::left().x + 30 * GlobalInfo::getInstance()->screenScaleX, VisibleRect::center().y - listLayer->getContentSize().height/2 );
    this->addChild(listLayer,100,TAG_CHAPTERLIST);
}
void ChapterLayer::onChapterClick(Ref* pSender)
{
    
    __Integer* inter = (__Integer*)pSender;
    int index = inter->getValue();
  
    enterChapter(index);
   
 }
void ChapterLayer::enterChapter(int index)
{
     DictChapter* chapter = chapterList->at(index);
    
     ChapterListLayer* layer = (ChapterListLayer*)this->getChildByTag(TAG_CHAPTERLIST);

    if(chapter->levelOpen > GlobalInfo::getInstance()->gameRole->level)
    {
        //        NoticeManager::getInstance()->showNotice("您还未占领下一章哦！亲！！");
        DictTips* dictTips = DictTipsManager::getInstance()->getData(6001014);
        string str = StringUtil::replace(dictTips->desc, "#1#",PublicShowUI::numberToString(chapter->levelOpen));
        NoticeManager::getInstance()->showNotice(str.c_str());
        
        layer->setSelectedByIndex(m_nowIndex);
        return;
    }
    
    if(index > m_nowIndex && isLastPage)
    {
        NoticeManager::getInstance()->showNotice("您还未占领下一章哦！亲！！");
        layer->setSelectedByIndex(m_nowIndex);
        return;
    }
    layer->setSelectedByIndex(index);
   

    
    
    this->setClickEnabled(false);
    
    if(this->_cloundArmature)
    {
        _cloundArmature->setVisible(true);
        this->_cloundArmature->getAnimation()->playWithIndex(0);
    }
    requestChapterByID(chapter->id);
    
}
void ChapterLayer::onNextChapter(int chapterID)
{
    requestChapterByID(chapterID);
}
//--------------------------------顶层----------------------------------------------------
void ChapterLayer::topLayer()
{
    
    UserWealthLayer* layer = UserWealthLayer::create(UserWealthLayer::STAGE);
    PublicShowUI::setTargetScale(layer);
   
    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2, VisibleRect::top().y-layer->getContentSize().height);
    this->addChild(layer,10,TAG_USERWEALTH);
    switch (GlobalInfo::getInstance()->battleType)
    {
        case kBattleType_MingZhanYi:
            layer->setTitle(IMG_PUBLIC_MINGZHANYI);
            break;
        case kBattleType_MingJiangZhuan:
            layer->setTitle(IMG_PUBLIC_MINGJIANGZHUAN);
            break;
        case kBattleTYPe_SanGuoWushuan:
            layer->setTitle(IMG_PUBLIC_SANGUOWUSHUANG);
            break;
        default:
            layer->setTitle(IMG_PUBLIC_CAMPAIGN);
            break;
    }

    
}
void ChapterLayer::onLastStage(int chapterID)
{
    if(chapterID == this->m_chapter->getChapter()->id)
    {
          this->isLastPage = true;
    }
  
}
void ChapterLayer::noLastStage()
{
    this->isLastPage = false;
}
void ChapterLayer::onEnter()
{
    BaseLayer::onEnter();
   

    showChapterType();
  
}
void ChapterLayer::onExit()
{
    BaseLayer::onExit();
    
}
void ChapterLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    if(_cloundArmature)
    {
        _cloundArmature->pause();
    }
    string path = PublicShowUI::getAvatarPath(IMG_PUBLIC_EFFECT,CLOUND_EFFECT);
    ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
    if(m_chapter)
    {
        m_chapter->clear();
    }
}
void ChapterLayer::onEnterTransitionDidFinish()
{
    SoundManager::playBackgroundMusic(MUSIC_STAGE);
   
    
    BaseLayer::onEnterTransitionDidFinish();
   
    _cloundArmature = NULL;
    
    DelayTime* delay = DelayTime::create(.1);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(ChapterLayer::loadClundEffect, this));
    this->runAction(Sequence::create(delay,callBack, NULL));
   
   
}
void ChapterLayer::showStageBattle()
{
    requestStageBattle(GlobalInfo::getInstance()->chapterOpenStage, GlobalInfo::getInstance()->stageMode);
    GlobalInfo::getInstance()->chapterOpenStage = 0;
}
void ChapterLayer::loadClundEffect()
{
    Dialog::showServerLoading(2);
    string path = PublicShowUI::getAvatarPath(IMG_PUBLIC_EFFECT,CLOUND_EFFECT);
    ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(ChapterLayer::onCloundInit));
    
//    ArmatureDataManager::getInstance()->addArmatureFileInfo(path);
//    onCloundInit(1);
}
void ChapterLayer::onCloundInit(float percent)
{
    if(percent < 1)
    {
        return;
    }
    Dialog::hideServerLoading();
    
    if(GlobalInfo::getInstance()->chapterOpenStage)
    {
        DelayTime* delay = DelayTime::create(.1);
        CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(ChapterLayer::showStageBattle, this));
        this->runAction(Sequence::create(delay,callBack, NULL));
    }
    else
    {
        topLayer();
        CustomMsgProcesser::getInstance()->nextMsgListData();
    }
    
    if(!ArmatureDataManager::getInstance()->getAnimationData(CLOUND_EFFECT))
    {
        return;
    }
  
    this->setClickEnabled(true);
    if(!ArmatureDataManager::getInstance()->getAnimationData(CLOUND_EFFECT))
    {
        return;
    }
    if(!ArmatureDataManager::getInstance()->getArmatureData(CLOUND_EFFECT))
    {
        return;
    }
    this->_cloundArmature = Armature::create(CLOUND_EFFECT);
    PublicShowUI::setTargetScale(this->_cloundArmature,true,false);
    _cloundArmature->setPosition(VisibleRect::center().x,VisibleRect::center().y);
    this->addChild(this->_cloundArmature,6);
     _cloundArmature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(ChapterLayer::onCloundPlayEnded));
    _cloundArmature->setVisible(false);
}

void ChapterLayer::onCloundPlayEnded(Armature *armature, MovementEventType type, const std::string& name)
{
    if(type != MovementEventType::COMPLETE && type != MovementEventType::LOOP_COMPLETE)
    {
        return;
    }
    this->setClickEnabled(true);
    _cloundArmature->setVisible(false);

}
void ChapterLayer::onShowFun(EventCustom* msg)
{
    topLayer();
    
    Node* node = this->getChildByTag(TAG_BACKBTN);
    node->setVisible(true);
    
    node = this->getChildByTag(TAG_CHAPTERLIST);
    node->setVisible(true);
}
void ChapterLayer::onHideFun(EventCustom* msg)
{
    Node* node = this->getChildByTag(TAG_USERWEALTH);
    if(node)
    {
        node->removeFromParent();
    }
    
    node = this->getChildByTag(TAG_BACKBTN);
    if(node)
    {
       node->setVisible(false);
    }
    
    node = this->getChildByTag(TAG_CHAPTERLIST);
    if(node)
    {
       node->setVisible(false);
    }
    
}
void ChapterLayer::addEventListener()
{
    addUserMsg(CUSTOM_SHOW_SCENE_FUN, CC_CALLBACK_1(ChapterLayer::onShowFun, this));
    addUserMsg(CUSTOM_HIDE_SCENE_FUN, CC_CALLBACK_1(ChapterLayer::onHideFun, this));
    
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_BATTLE_ChapterOpenBoxResp).c_str(), CC_CALLBACK_1(ChapterLayer::onMsgProcess, this));

}
void ChapterLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
  
}
bool ChapterLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    clickPoint = touch->getLocation();
    return true;
}
void ChapterLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    
}
void ChapterLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    long index = m_nowIndex;
    int deltaX = touch->getLocation().x - clickPoint.x;
    if(deltaX < -50 * GlobalInfo::getInstance()->screenScaleX)
    {
  
        index++;
        if(index >= chapterList->size())
        {
            index = chapterList->size() - 1;
            return;
        }
        
    }
    else if(deltaX > 50 * GlobalInfo::getInstance()->screenScaleX)
    {
        index--;
        if(index < 0)
        {
            index = 0;
            return;
        }
        
    }
    if(index == m_nowIndex)
    {
        return;
    }
  
    enterChapter(index);

   
}