//
//  ChatItem.h
//  FightPass
//
//  Created by 超 顾 on 15/11/25.
//
//

#ifndef __FightPass__ChatItem__
#define __FightPass__ChatItem__
#include "cocos2d.h"

#include "ui/UIRichText.h"
#include "../../../YVSDK/YVPlatform.h"
#include "../../BaseLayer.h"

#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
using namespace YVSDK;
using namespace cocos2d::ui;
class ChatItem:public BaseLayer,
public YVSDK::YVListern::YVDownLoadFileListern,
public YVSDK::YVListern::YVUpdateUserInfoListern,
public YVSDK::YVListern::YVFinishPlayListern
{
public:
    ChatItem();
    ~ChatItem();
    virtual bool init(YVMessagePtr data);
    static ChatItem* create(YVMessagePtr data);
public:
    bool isSendMessage(YVMessagePtr base);
    YVMessagePtr getChatMessage();
    void setChatMsg(YVMessagePtr data);
protected:
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    void onDownLoadFileListern(YVSDK::YVFilePathPtr);
    void onUpdateUserInfoListern(YVSDK::YVUInfoPtr);
    void onFinishPlayListern(YVSDK::StartPlayVoiceRespond*);
private:
    void setContent();
    void initMessageContent(YVSDK::YVMessagePtr, bool flag);
    void initTextMessage(std::string&);
    void initVoiceMessage(YVSDK::YVVoiceMessagePtr,bool flag);
    void initPicMessage(YVSDK::YVImageMessagePtr);
    void downLoadVoiceFile();
    void playSound(Node* pSender);
    void setSending();
    void playVoice();
private:
    Sprite* redDot;
    Sprite* sendingSpr;
private:
    YVMessagePtr m_data;
    YVVoiceMessagePtr m_Message;
    bool m_isVoiceMssage;
    YVUInfoPtr userinfo;
    RichText* m_richText;
    std::string m_voiceText;
    YVSDK::YVFilePathPtr m_voicePath;
    bool isSound;
    int TAG_BG;
    int TAG_HEAD;
    int TAG_VOICEBTN;
    int TAG_TEXT;
    int TAG_SENDING;
    float sx;
};

#endif /* defined(__FightPass__ChatItem__) */
