//
//  OpenCard.cpp
//  Test
//
//  Created by zhangxiaobin on 15/9/28.
//
//

#include "OpenCard.h"
//
//  CardSprite.cpp
//  Cocos2dev.com
//
//  Created by LiuYanghui on 13-6-17.
//
//

#define kInAngleZ        270 //里面卡牌的起始Z轴角度
#define kInDeltaZ        90  //里面卡牌旋转的Z轴角度差

#define kOutAngleZ       0   //封面卡牌的起始Z轴角度
#define kOutDeltaZ       90  //封面卡牌旋转的Z轴角度差

enum {
    tag_inCard = 1,
    tag_outCard
};

OpenCard::OpenCard()
{
    
}

OpenCard::~OpenCard()
{
    m_openAnimIn->release();
    m_openAnimOut->release();
}

OpenCard* OpenCard::create(const char* inCardImageName, const char* outCardImageName, float duration)
{
    OpenCard *pSprite = new OpenCard();
    if (pSprite && pSprite->init(inCardImageName, outCardImageName, duration))
    {
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

bool OpenCard::init(const char* inCardImageName, const char* outCardImageName, float duration)
{
    if (!Node::init())
    {
        return false;
    }
    initData(inCardImageName, outCardImageName, duration);
    return true;
}

#pragma mark - initData
void OpenCard::initData(const char* inCardImageName, const char* outCardImageName, float duration)
{
    m_isOpened = false;
    
    Sprite* inCard = Sprite::create(inCardImageName);
    inCard->setPosition(Point::ZERO);
    inCard->setVisible(false);
    inCard->setTag(tag_inCard);
    addChild(inCard);
    
    Sprite* outCard = Sprite::create(outCardImageName);
    outCard->setPosition(Point::ZERO);
    outCard->setTag(tag_outCard);
    addChild(outCard);
    
    m_openAnimIn = (ActionInterval*)Sequence::create(DelayTime::create(duration * .5),
                                                         Show::create(),
                                                         OrbitCamera::create(duration * .5, 1, 0, kInAngleZ, kInDeltaZ, 0, 0),
                                                         NULL);
    m_openAnimIn->retain();
    
    m_openAnimOut = (ActionInterval *)Sequence::create(OrbitCamera::create(duration * .5, 1, 0, kOutAngleZ, kOutDeltaZ, 0, 0),
                                                           Hide::create(),
                                                           DelayTime::create(duration * .5),
                                                           NULL);
    m_openAnimOut->retain();
}

#pragma mark - public func
void OpenCard::openCard()
{
    Sprite* inCard = (Sprite*)getChildByTag(tag_inCard);
    Sprite* outCard = (Sprite*)getChildByTag(tag_outCard);
    inCard->runAction(m_openAnimIn);
    outCard->runAction(m_openAnimOut);
}