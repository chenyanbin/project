//
//  UserLoginLayer.h
//  SuiTang
//
//  Created by zhangxiaobin on 15/1/13.
//
//

#ifndef __SuiTang__UserLoginLayer__
#define __SuiTang__UserLoginLayer__
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
#include "../../BaseLayer.h"
class UserLoginLayer:public BaseLayer,EditBoxDelegate
{
public:
    UserLoginLayer();
    ~UserLoginLayer();
    virtual bool init();
    CREATE_FUNC(UserLoginLayer);
    static void show();
private:
    void setLoginBtn();
    void setUserNameInput();
    void onLoginClick(Ref* pSender);
    void onTouristClick(Ref* pSender);
protected:
    void editBoxEditingDidBegin(EditBox* editBox);
    void editBoxEditingDidEnd(EditBox* editBox);
    void editBoxTextChanged(EditBox* editBox, const std::string& text);
    void editBoxReturn(EditBox* editBox);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    string m_uid;
};

#endif /* defined(__SuiTang__UserLoginLayer__) */
