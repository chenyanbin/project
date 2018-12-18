//
//  ChatContent_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/11/25.
//
//

#ifndef __FightPass__ChatContent_Layer__
#define __FightPass__ChatContent_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include "ChatItem.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;

struct YaYaRespondBase;
struct FaceData
{
    int id;
    std::string tag;
    std::string tip;
    std::string file;
};

enum ChatPanelInputMode
{
    UnknowMode,
    TextInputMode,
    FaceInputMode,
    PicInputMode,
    VoiceInputMode,
};
#define MAXMSG   30
#define RECORDTIME 59
class ChatContent_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate,EditBoxDelegate,
public YVSDK::YVListern::YVStopRecordListern,
public YVSDK::YVListern::YVChannelChatListern,
public YVSDK::YVListern::YVChannelHistoryChatListern,
public YVSDK::YVListern::YVChannelChatStateListern,
public YVSDK::YVListern::YVModChannelIdListern,
public YVSDK::YVListern::YVChannalloginListern
{
public:
    ChatContent_Layer();
    ~ChatContent_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(int _channel);
    static ChatContent_Layer* create(int _channel);
public:
    void sendVoice(bool isSend);
    void sendChannalVoice(YVSDK::YVFilePathPtr voicePath, float voiceTime);
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
protected:
    void onStopRecordListern(YVSDK::RecordStopNotify*);
    void onChannelChatListern(YVSDK::YVMessagePtr);
    void onChannelHistoryChatListern(YVSDK::YVMessageListPtr);
    void onChannelChatStateListern(YVSDK::YVMessagePtr);
    void onModChannelIdListern(YVSDK::ModChannelIdRespond*);
    void onChannalloginListern(YVSDK::ChanngelLonginRespond*);
    
    
    void editBoxEditingDidBegin(EditBox* editBox);
    void editBoxEditingDidEnd(EditBox* editBox);
    void editBoxTextChanged(EditBox* editBox, const std::string& text);
    void editBoxReturn(EditBox* editBox);
private:
    void getChannalHistory(float dt);
    void getChannalHistoryD();
    
    void setVoiceInputModeBtn();
    void setInputModeBtn();
    void onKeybordClick(Node* pSender);
    void onSoundBtnClick(Node* pSender);
    void onTextSendClick(Node* pSender);
    void onVoiceBtnClick(Node* pSender);
    void onRelesaseOutUp(Ref* psender);
    void onVoiceBtnPress(Node* pSender);
    void recordingTimeUpdate(float dt);
    ChatItem* getItemByMsg(YVSDK::YVMessagePtr msg);
    void addContextItem(YVMessagePtr msg);
private:
    std::vector<YVMessagePtr>* messageList;
    int m_channel;
    float m_recordingTime;
    bool m_isSendVoice;
    Size cellSize;
private:
    int TAG_TABLEVIEW;
    int TAG_VOICEBTN;
    int TAG_INPUTEDIT;
};


#endif /* defined(__FightPass__ChatContent_Layer__) */
