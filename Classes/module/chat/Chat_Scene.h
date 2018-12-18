//
//  Chat_Scene.h
//  FightPass
//
//  Created by 超 顾 on 15/11/20.
//
//

#ifndef __FightPass__Chat_Scene__
#define __FightPass__Chat_Scene__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../BaseLayer.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../common/comboxBtn/ComboBoxBtn.h"
//#include "../../common/TouchSprite/Button.h"
#include <Vector>
#include "../../YVSDK/YVPlatform.h"
using namespace YVSDK;

USING_NS_CC_EXT;
USING_NS_CC;
class Chat_Scene:public BaseLayer,public cocos2d::extension::EditBoxDelegate
{
public:
    
    Chat_Scene();
    ~Chat_Scene();
    static Chat_Scene* create();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
private:
    void createLayer();
    void hideOtherLayer(int tag);
    void onUserClick(Node* pSender);
    void onSocialBtnClick(Ref* psender=NULL);
    void onFriendBtnClick(Ref* psender);
    void onSearchBtnClick(Ref* psender);
    void onComboBoxBtnClick(Ref* psender);
    void callbackC();
    void FriendcallbackC();
    void WorldCallBackC();
    void SetChatLayer(int isSelect);
    void createList();
    
    void editBoxEditingDidBegin(EditBox* editBox);
    void editBoxEditingDidEnd(EditBox* editBox){};
    void editBoxTextChanged(EditBox* editBox, const std::string& text){};
    void editBoxReturn(EditBox* editBox){};
    
    void onSelectMessageCallBack(EventCustom* msg);
    void onSelectFriendMessageCallBack(EventCustom* msg);
    
    void onAlterHeadCallBack(EventCustom* msg);
    
    void requestMyInfoMsg();
    void updateYaYaIdMsg(int yayaId);
    void onMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
protected:

private:
    float sx;
    Sprite* listBg;
    ComboBoxBtn* boxBtn;
    
    Vector<TouchSprite*>* btnList;
    int selectBtn;
    int TAG_COMBOBOXBTN;
    int TAG_TRAN;
    int TAG_SEARCH;
    int TAG_LAYER;
    int TAG_CHATCONTENT;//世界聊天框
    int TAG_FRIENDCHAT;//好友聊天框
    int TAG_SHEJIAOBTN;
    int TAG_SEARCHLAYER;//查询页面
    int TAG_MESSAGELAYER;//消息列表页面
    int TAG_FRIENDLAYER;//好友列表页面
    int TAG_APPLYLAYER;//好友申请页面
    EditBox* editbox;
    Sprite* headImg;
    int myHeadId;
    int chatFriendId;
};

#endif /* defined(__FightPass__Chat_Scene__) */
