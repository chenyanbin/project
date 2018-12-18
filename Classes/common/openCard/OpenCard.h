//
//  OpenCard.hpp
//  Test
//
//  Created by zhangxiaobin on 15/9/28.
//
//


#ifndef __Test__CardSprite__
#define __Test__CardSprite__

#include "cocos2d.h"
USING_NS_CC;

class OpenCard : public Node
{
public:
    OpenCard();
    ~OpenCard();
    static OpenCard* create(const char* inCardImageName, const char* outCardImageName, float duration);
    virtual bool init(const char* inCardImageName, const char* outCardImageName, float duration);
    
private:
    bool m_isOpened;
    ActionInterval* m_openAnimIn;
    ActionInterval* m_openAnimOut;
    
    
    void initData(const char* inCardImageName, const char* outCardImageName, float duration);
    
public:
    void openCard();
};

#endif /* defined(__Test__CardSprite__) */
