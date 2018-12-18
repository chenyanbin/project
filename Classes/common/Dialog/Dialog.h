//
//  Dialog.h
//  SuiTang
//
//  Created by mac on 14-6-26.
//
//

#ifndef __SuiTang__Dialog__
#define __SuiTang__Dialog__

#include "cocos2d.h"
USING_NS_CC;
#include "PopUpLayer.h"
#include "PopupLoading.h"
#include "LoadingPage.h"
class Dialog
{
public:
     static PopUpLayer* show(const char* content,const char*  title = "提示",unsigned short buttonCount = 1,Ref* target = NULL,SEL_CallFuncN callfun = NULL);
    
    static PopupLoading* showLoading(float timess = 0);
    static void hideLoading();
//    游戏屏蔽层。用于屏蔽所有操作
    static void showShieldLayer();
    
    static void showServerLoading(float times = 0.8,float isShowReLogin = true);
    static void hideServerLoading();

    static PopUpLayer* createPopLayer(const char* content,const char*  title,Ref* target = NULL,SEL_CallFuncN callfun = NULL);
    
    static LoadingPage* showLoadingPage();
    
    static void showNoPowerDialog(int fromeMoudle);
};

#endif /* defined(__SuiTang__Dialog__) */
