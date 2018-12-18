//
//  DoubleHitManager.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/7/9.
//
//

#include "DoubleHitManager.h"
#include "../../../common/PublicShowUI.h"
#include "../../../common/ImagePath.h"
DoubleHitManager* DoubleHitManager::_instance = NULL;
DoubleHitManager::DoubleHitManager()
:m_count(0)
,m_delayTime(2)
,TAG_COUNT(1)
,countList(NULL)
,bg(NULL)
{
    countList = new queue<int>();
    bg = Sprite::create(IMG_BATTLE_DOUBLEHIT);
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg, 0);
    this->setContentSize(bg->getContentSize());
    onClearCount();
}
DoubleHitManager::~DoubleHitManager()
{
    while (countList->size()) {
        countList->pop();
    }
    CC_SAFE_DELETE(countList);
    countList = NULL;
    _instance = NULL;
}

DoubleHitManager* DoubleHitManager::getInstance()
{
    if(!_instance)
    {
        _instance = new DoubleHitManager();
        _instance->autorelease();
    }
    return _instance;
}
void DoubleHitManager::onHit()
{
    int m = ++m_count;
   
    if(m >=2)
    {
        bg->setVisible(true);
        countList->push(m);
//        if(this->getChildByTag(TAG_COUNT) == NULL)
//        {
//            addCount();
//        }
        addCount();
    }
  
    this->stopAllActions();
    DelayTime* delay = DelayTime::create(m_delayTime);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(DoubleHitManager::onClearCount, this));
    this->runAction(Sequence::create(delay,callBack, NULL));
}
void DoubleHitManager::onClearCount()
{
    m_count = 0;
    bg->setVisible(false);
}
void DoubleHitManager::addCount()
{
    if(countList->size() <= 0)
    {
        return;
    }
    if(this->getChildByTag(TAG_COUNT))
    {
        this->removeChildByTag(TAG_COUNT);
    }
    int count = countList->front();
    countList->pop();
    Sprite* node = Sprite::create();
    Node* num = PublicShowUI::getNumbers(count,IMG_PUBLIC_NUMBER1);
  
    node->addChild(num);
    num->setPosition(-num->getContentSize().width/2,num->getContentSize().height/2);
    node->setCascadeOpacityEnabled(true);
    node->setContentSize(num->getContentSize());
    node->setScale(.3);
    ScaleTo* scaleto = ScaleTo::create(.05, 1.5);
    ScaleTo* scalleBack = ScaleTo::create(.05,1);
    DelayTime* delay = DelayTime::create(.3);
    RemoveSelf* remove = RemoveSelf::create();
    CallFunc* callFun = NULL;//CallFunc::create(CC_CALLBACK_0(DoubleHitManager::addCount, this));
    node->runAction(Sequence::create(scaleto,scalleBack,delay,remove,callFun, NULL));
    this->addChild(node,2,TAG_COUNT);
}