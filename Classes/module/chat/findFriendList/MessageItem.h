//
//  MessageItem.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/11/24.
//
//

#ifndef MessageItem_hpp
#define MessageItem_hpp
#include "cocos2d.h"
USING_NS_CC;
#include "../data/MessageData.h"
#include "../../BaseLayer.h"
class MessageItem:public BaseLayer
{
public:
    MessageItem();
    ~MessageItem();
    virtual bool init(MessageData* data);
    static MessageItem* create(MessageData* data);
protected:
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();

private:
    void setBg();
    void setContent();
    void onAddFriendClick(Ref* pSender);
    void addFriend();
    
    void onMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
private:
    MessageData* m_data;
    int TAG_BG;
  
};

#endif /* MessageItem_hpp */
