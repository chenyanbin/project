//
//  SetupLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/10/19.
//
//

#ifndef __FightPass__SetupLayer__
#define __FightPass__SetupLayer__


#include "extensions/cocos-ext.h"
#include "cocos2d.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include "../BaseLayer.h"
class SetupLayer:public BaseLayer,EditBoxDelegate
{
public:
    SetupLayer();
    ~SetupLayer();
    virtual bool init();
    static SetupLayer* create();
    static void show();
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void setUiSpr();
    void setSureBuyBtn();
    void onSureBuyClick(Ref* psender);
    void onNoticeClick(Ref* psender);
    void onchangenange(Ref* psender);
    void onclickMusic(Ref* psender);
    void onjihuomaClick(Ref* psender);
    
    void requestNameMsg(string _name);//
    void onChageNameMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    void onDialogClick(Node* psender);
    
    void onRandBtnClick(Ref* pSender);
    
protected:
    void editBoxEditingDidBegin(EditBox* editBox);
    void editBoxEditingDidEnd(EditBox* editBox);
    void editBoxTextChanged(EditBox* editBox, const std::string& text);
    void editBoxReturn(EditBox* editBox);
    void backScene();
private:
   EditBox* editbox;
    int MUSIC_TAG;//音乐开关
    int SOUND_TAG;

    
};


#endif /* defined(__FightPass__SetupLayer__) */
