//
//  FindBuyMilitaryLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/9/1.
//
//  点击开始寻访弹出层

#ifndef __FightPass__FindBuyMilitaryLayer__
#define __FightPass__FindBuyMilitaryLayer__


#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
#include "../../BaseLayer.h"
class FindBuyMilitaryLayer:public BaseLayer ,public cocos2d::extension::EditBoxDelegate

{
public:
    enum TAG_BTN
    {
        TAG_ADDTEN = 10,
        TAG_MINUSTEN
    };
    FindBuyMilitaryLayer();
    ~FindBuyMilitaryLayer();
    virtual bool init(int idx, int _minHonor, int _jungongCount);
    static FindBuyMilitaryLayer* create(int idx, int _minHonor, int _jungongCount);
    static void show(int idx,int _minHonor, int _jungongCount);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void setUIButton();
    void setPrice(int nowCount);
    void onBuyclick(Ref* psender);
    void setSureBuyBtn();
    void onSureBuyClick(Ref* psender);
    void onCencelClick(Ref* psender);
    
    //输入伪托
    void editBoxEditingDidBegin(EditBox* editBox);
    void editBoxEditingDidEnd(EditBox* editBox);
    void editBoxTextChanged(EditBox* editBox, const std::string& text);
    void editBoxReturn(EditBox* editBox);
    //滑杆回调
    void slideCallback(cocos2d::Ref* sender, Control::EventType controlEvent);
    
    void requestMilitaryMsg(int findId, int honor);//请求开始寻访
    void onMilitaryMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    void onHeadClick(Node* psender);
private:
    int m_nowcount;
    int TAG_COUNT;
    int TAG_ALLCOUNT;
    EditBox* editbox;
    ControlSlider* slide_control;
    int m_idx;
    int m_minHonor;//寻访最少军功
    int m_jungongCount;//军工数量
    Label* jungongcountlabel;

};


#endif /* defined(__FightPass__FindBuyMilitaryLayer__) */
