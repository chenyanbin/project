//
//  onOffButton.h
//  SuiTang
//
//  Created by 超 顾 on 15/4/16.
//
//

#ifndef __SuiTang__onOffButton__
#define __SuiTang__onOffButton__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class onOffButton: public Node
{
    public:
        static onOffButton* create(const std::string&buttonBg, const std::string&buttonOn,const std::string&buttonOff, const ccMenuCallback& callback,const std::string&buttonOnBG="");
        onOffButton();
        ~onOffButton();
        void setOnButton(bool bol);
    private:
        void onEnter();
        void onExit();
        bool isClickSprite(cocos2d::Touch* pTouch);
        void setOnBtn(const std::string&buttonOn,const std::string&buttonOnBG);
        void setOffBtn(const std::string&buttonOn);
        bool init(const std::string&buttonBg, const std::string&buttonOn,const std::string&buttonOff, const ccMenuCallback& callback,const std::string&buttonOnBG="");
        virtual bool ccTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
        virtual void ccTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
        virtual void ccTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    private:
        Sprite* btnBg;
        Sprite* btnOn;
        Sprite* btnOff;
    
        ccMenuCallback m_callBack;
        EventListenerTouchOneByOne* touchListener;
    public:
        bool btnBol;
};
#endif /* defined(__SuiTang__onOffButton__) */
