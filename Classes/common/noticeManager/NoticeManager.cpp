//
//  NoticeManager.cpp
//  SuiTang
//
//  Created by mac on 14-6-4.
//
//

#include "NoticeManager.h"
#include "../PublicShowUI.h"

#include "../GameConfig.h"
#include "../Dialog/Dialog.h"
#include "../../commonData/dictData/DictTips/DictTipsManager.h"
NoticeManager* NoticeManager::_instance = NULL;
NoticeManager::NoticeManager()
:spriteList(NULL)
,isStart(false)
,m_dialogID(0)
{
//    msgList = new queue<string>();
//    colorList = new queue<Color3B>();
    spriteList = new queue<Sprite*>();
    msgList = new queue<NoticeMsg*>();
}
NoticeManager::~NoticeManager()
{
    stop();
    while (!msgList->empty())
    {
        NoticeMsg* data = msgList->front();
        delete data;
        data = NULL;
        msgList->pop();
    }
    while (spriteList->size()) {
        spriteList->pop();
    }
//    while (colorList->size()) {
//        colorList->pop();
//    }
    delete msgList;
    msgList = NULL;
    delete spriteList;
    spriteList = NULL;
//    delete colorList;
//    colorList = NULL;
//    
    
    _instance = NULL;
    
}
NoticeManager* NoticeManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new NoticeManager();
        _instance->autorelease();
        Scene* scene = Director::getInstance()->getRunningScene();
        scene->addChild(_instance,SCENE_NOTICE_ZORDER);
    }
    return _instance;
}
void NoticeManager::showConfirmDialog(const char* content,int dialogID)
{
    m_dialogID = dialogID;
    Dialog::show(content,"提示",2,this,callfuncN_selector(NoticeManager::onDialogBack));
}
void NoticeManager::onDialogBack(Node* pSender)
{
    if(this->m_dialogID > 0)
    {
        
        m_dialogID = 0;
    }
}
void NoticeManager::start()
{
    stop();
    isStart = true;
    Director::getInstance()->getScheduler()->schedule(schedule_selector(NoticeManager::update), this,0.5, false);
}
void NoticeManager::stop()
{
    isStart = false;
    Director::getInstance()->getScheduler()->unschedule(schedule_selector(NoticeManager::update), this);
}
void NoticeManager::update(float dt)
{
    if(msgList->size() <= 0)
    {
        stop();
        return;
    }
    NoticeMsg* noticeData = msgList->front();

    Sprite* labelBg = noticeData->showBg ? Sprite::create(IMG_PUBLIC_FLOATLABELBG) : Sprite::create();
    PublicShowUI::setTargetScale(labelBg,false,false);
    labelBg->setPosition(noticeData->fromCp);
    this->addChild(labelBg,1/*(int)msgList->size()*/);
    labelBg->stopAllActions();
    labelBg->setCascadeOpacityEnabled(true);
    spriteList->push(labelBg);
    
    const char* content = noticeData->content.c_str();
    Label* label = PublicShowUI::getLabel(content,noticeData->color,noticeData->fontSize,false,false);
    label->setPositionX(labelBg->getContentSize().width/2);
    label->setPositionY(labelBg->getContentSize().height/2);
    labelBg->addChild(label,1);
    
    
    
    if(noticeData->color == Color3B::GREEN)
    {
        CallFunc* callBack =  CallFunc::create(CC_CALLBACK_0(NoticeManager::onMoveEnd,this));
        MoveTo* move = MoveTo::create(0.6, noticeData->toCp);
        ActionInterval * easeSineIn = EaseSineIn::create(move);
        ScaleTo* scaleTo = ScaleTo::create(1, 0.01);
        labelBg->runAction(Sequence::create(DelayTime::create(0.3),easeSineIn, scaleTo, callBack, NULL));
    }
    else
    {
        CallFunc* callBack =  CallFunc::create(CC_CALLBACK_0(NoticeManager::onMoveEnd,this));
        MoveTo* move = MoveTo::create(1, noticeData->toCp);
        FadeOut* fadeOut = FadeOut::create(0.4);
        
        labelBg->runAction(Sequence::create(Spawn::create( move, Sequence::create(DelayTime::create(0.6),fadeOut,NULL), NULL),callBack, NULL));
    }
    msgList->pop();
    delete noticeData;
    noticeData = NULL;
}

void NoticeManager::showNoOpenFunctionNotice(int functionID)
{
//tips:通关$1的【$2】开放
//    $1---关卡名称
//    $2---关卡战斗名称
//    【汉白玉】  16:47:46
//    采用黄色tips提示
    
}
void NoticeManager::showNotice(const char* content,int colorFlag)
{
    Point fromCp = VisibleRect::center();
    fromCp.y += 50 * GlobalInfo::getInstance()->screenScaleY;
    Point toCp = fromCp;
    toCp.y = colorFlag == COLOR_GREEN ? fromCp.y +  150 * GlobalInfo::getInstance()->screenScaleY : fromCp.y + 200  * GlobalInfo::getInstance()->screenScaleY;
    showNotice(content,colorFlag,fromCp,toCp,26,true);
    
}
void NoticeManager::showNotice(const char* content,int colorFlag, Point fromCp,Point toCp,int fontSize,bool showBg)
{
    if(strcmp(content, "") == 0)
    {
        return;
    }
    Color3B color = Color3B::BLACK;
    switch (colorFlag) {
        case COLOR_WHITE:
            color = Color3B::WHITE;
            break;
        case COLOR_YELLOW:
            color = Color3B::YELLOW;
            break;
        case COLOR_GREEN:
            color = Color3B::GREEN;
            break;
        case COLOR_RED:
            color = Color3B::RED;
            break;
        default:
            break;
    }
    NoticeMsg* data = new NoticeMsg();
    data->content = content;
    data->color = color;
    data->fromCp = fromCp;
    data->toCp = toCp;
    data->showBg = showBg;
    data->fontSize = fontSize;
    msgList->push(data);
    if(this->isStart == false)
    {
        this->start();
    }
}
void NoticeManager::showNotice(Vector<BaseTypeData*> m_baseList)
{
    
    Sprite* labelBg = Sprite::create(IMG_PUBLIC_LAYER_GAIN_BG);
    PublicShowUI::setTargetScale(labelBg,false,false);
    labelBg->setPositionX(VisibleRect::center().x);
    labelBg->setPositionY(VisibleRect::center().y + labelBg->getContentSize().height/2);
    this->addChild(labelBg,1);
    labelBg->setCascadeOpacityEnabled(true);
    spriteList->push(labelBg);
}
void NoticeManager::onMoveEnd()
{
    if(spriteList && spriteList->size())
    {
        Sprite* labelBg = spriteList->front();
        if(labelBg)
        {
            if(labelBg->getReferenceCount() > 0)
            {
                try
                {
                    if(labelBg->getParent())
                    {
                        labelBg->removeFromParent();
                    }
                }
                catch(exception)
                {
                    log("exception");
                }
            }
        }
        
        spriteList->pop();
    }
}
void NoticeManager::showDictTipsMsg(int dictTipsID)
{
    DictTips* dictTips = DictTipsManager::getInstance()->getData(dictTipsID);
    if(!dictTips)
    {
        return;
    }
    this->showNotice(dictTips->desc.c_str());
}