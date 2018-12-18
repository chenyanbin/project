//
//  FriendChatCont_Layer.hpp
//  FightPass
//
//  Created by 超 顾 on 16/1/6.
//
//

#ifndef FriendChatCont_Layer_h
#define FriendChatCont_Layer_h

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include "ChatItem.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;

#define MAXMSG   30
#define RECORDTIME 59
class FriendChatCont_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate,EditBoxDelegate,
public YVSDK::YVListern::YVFriendChatListern,
public YVSDK::YVListern::YVFriendHistoryChatListern,
public YVSDK::YVListern::YVUpdateUserInfoListern,
public YVSDK::YVListern::YVFriendChatStateListern,
public YVSDK::YVListern::YVStopRecordListern
{
public:
    FriendChatCont_Layer();
    ~FriendChatCont_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(int _YaYaId);
    static FriendChatCont_Layer* create(int _YaYaId);

private:
    void createLayer();
    void initTableView();
    
    void addEventListener();
    void removeEventListener();
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view) {};
public:
    //YYsdk部分
    void onFriendChatListern(YVSDK::YVMessagePtr) ;
    void onFriendHistoryChatListern(YVSDK::YVMessageListPtr);
    void onUpdateUserInfoListern(YVSDK::YVUInfoPtr);
    void onFriendChatStateListern(YVSDK::YVMessagePtr);
    void onStopRecordListern(YVSDK::RecordStopNotify* r);
//    void onGetCpuUserListern(YVSDK::GetCpmsgRepond);
    
    void setChatUid();
    int getHistoryIndex();
    void getBeforeMsg();
    void addContextItem(YVSDK::YVMessagePtr msg);
    ChatItem* getItemByMsg(YVSDK::YVMessagePtr msg);
    
    //语音
    void onSoundBtnClick(Node* pSender);
    void setVoiceInputModeBtn();
    void onVoiceBtnUp(Node* pSender);
    void onRelesaseOutUp(Ref* psender);
    void onVoiceBtnDown(Node* pSender);
    void onKeybordClick(Node* pSender);
    void onVoiceBtnPress(Node* pSender);
    void recordingTimeUpdate(float dt);
    void sendVoice(bool bol);
    void sendFriendVoice(YVFilePathPtr voicePath, float voiceTime);
    //文本
    void onTextSendClick(Node* pSender);
    void setInputModeBtn();

    //YYsdk部分介绍
    
    
    void editBoxEditingDidBegin(EditBox* editBox);
    void editBoxEditingDidEnd(EditBox* editBox);
    void editBoxTextChanged(EditBox* editBox, const std::string& text);
    void editBoxReturn(EditBox* editBox);
private:
    

    
private:
    uint32 m_chatWithUid;
    YVSDK::YVUInfoPtr uinfo;
    YVSDK::uint32 indexTemp;
    float m_recordingTime;
    
    std::vector<YVMessagePtr>* messageList;
//    int m_channel;
//    float m_recordingTime;
//    bool m_isSendVoice;
    Size cellSize;
private:
    int TAG_TABLEVIEW;
    int TAG_VOICEBTN;
    int TAG_INPUTEDIT;
};


#endif /* FriendChatCont_Layer_h */
