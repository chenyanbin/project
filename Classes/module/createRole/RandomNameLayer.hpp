//
//  RandomNameLayer.hpp
//  FightPass
//
//  Created by zhangbin on 16/4/15.
//
//

#ifndef RandomNameLayer_hpp
#define RandomNameLayer_hpp

#include "../BaseLayer.h"

#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
class RandomNameLayer:public BaseLayer,EditBoxDelegate
{
public:
    RandomNameLayer();
    ~RandomNameLayer();
    virtual bool init();
    CREATE_FUNC(RandomNameLayer);
private:
    void setNameLabel();
    void setDiceBtn();
    void onDiceBtnClick(Ref* pSender);
    void setHalfBody();
    void onConfirmNameMsg(Ref* pSender);
    void setConfirmBtn();
    
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
    
    void onMsgProcess(EventCustom* message);
    
    void editBoxEditingDidBegin(EditBox* editBox);
    void editBoxEditingDidEnd(EditBox* editBox);
    void editBoxTextChanged(EditBox* editBox, const std::string& text);
    void editBoxReturn(EditBox* editBox);
private:
    int TAG_LABELBG;
    EditBox* editbox;
};


#endif /* RandomNameLayer_hpp */
