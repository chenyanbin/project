//
//  MessageNotifyNode.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/11/30.
//消息列表结点
//

#ifndef MessageNotifyNode_hpp
#define MessageNotifyNode_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "../../../YVSDK/YVPlatform.h"
using namespace YVSDK;
class MessageNotifyNode:public Node
{
public:
    MessageNotifyNode();
   ~MessageNotifyNode();
    virtual bool init(YVMessagePtr data,ccMenuCallback callBack);
    static MessageNotifyNode* create(YVMessagePtr,ccMenuCallback callBack);
protected:
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
private:
    void setBg();
    void setContent();
    void setMsgContent();
    void setTime();
    void onItemClick(Node* item);
private:
   YVMessagePtr m_data;
    YVUInfoPtr userinfo;
     ccMenuCallback m_callBack;
    int TAG_BG;
    int TAG_NICKNAME;
};

#endif /* MessageNotifyNode_hpp */
