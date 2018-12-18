//
//  EditTextField.h
//  Test
//
//  Created by zhangxiaobin on 14/10/31.
//
//

#ifndef __Test__EditTextField__
#define __Test__EditTextField__

#include "cocos2d.h"
USING_NS_CC;
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
class EditTextField:public Node,EditBoxDelegate
{
public:
    EditTextField();
    ~EditTextField();
    virtual bool init(const Size& size,int fontSize);
    static EditTextField* create(const Size& size,int fontSize);
    
    void setString(const std::string& text);
    void setColor(Color3B color);
    void setMaxLength(int value);
    const std::string& getText();
    
    void setDelegate(EditBoxDelegate* delegate);
public:
    //是否可以输入
    bool isEnableInput;
    
protected:
    void editBoxEditingDidBegin(EditBox* editBox);
    void editBoxEditingDidEnd(EditBox* editBox);
    void editBoxTextChanged(EditBox* editBox, const std::string& text);
    void editBoxReturn(EditBox* editBox);
    bool isTouchInside(Touch* touch);
    
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
private:
    void setEditBox();
    void setContentLabel();
    
private:
    Label* m_contentLabel;
    Color3B m_color;
    int maxLength;
    EditBoxDelegate* m_delegate;
    
    int TAG_EDITBOX;
};

#endif /* defined(__Test__EditTextField__) */
