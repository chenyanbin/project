//
//  CdkeyActivity.hpp
//  FightPass
//
//  Created by 超 顾 on 15/12/19.
//
//

#ifndef CdkeyActivity_h
#define CdkeyActivity_h

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include "../../BaseLayer.h"
#include "../../data/BaseTypeData.h"
class CdkeyActivity:public BaseLayer,EditBoxDelegate
{
public:
    CdkeyActivity();
    ~CdkeyActivity();
    virtual bool init();
    static CdkeyActivity* create();
    static void show();
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void createLayer();
    void onBtnClick(Ref* pSender);
    
    void requestMsg(string str);
    void onChageNameMsgProcess(EventCustom* msg);
    
    void addEventListener();
    void removeEventListener();
protected:
    void editBoxEditingDidBegin(EditBox* editBox);
    void editBoxEditingDidEnd(EditBox* editBox);
    void editBoxTextChanged(EditBox* editBox, const std::string& text);
    void editBoxReturn(EditBox* editBox);
private:
    EditBox* editbox;
    float sx;
};

#endif /* CdkeyActivity_hpp */
