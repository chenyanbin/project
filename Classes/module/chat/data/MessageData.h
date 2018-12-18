//
//  MessageData.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/11/24.
//
//

#ifndef MessageData_hpp
#define MessageData_hpp
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

enum ChatChannel
{
    kChatChannel_World = 0,//世界聊天
    kChatChannel_Private = 1,//私聊
};

typedef enum _messageType
{
    kMessageItemType_NULL = 0,
    kMessageItemType_Friend = 1,//好友
    kMessageItemType_Message,//消息列表结点
    kMessageItemType_FreindApply,//好友申请
    kMessageItemType_Search//查找类型
}MessageType;

class MessageData:public Ref
{
public:
    MessageData():nickName(""),userid(""),roleId(0),level(0),combat(0),content(""),header(""),online(0),type(kMessageItemType_NULL)
    ,isSound(false)
    {
        
    }
    ~MessageData()
    {
        
    }
public:
    std::string nickName;//名字
    string userid;//
    long roleId;//ID
    int level;//等级
    int combat;//战斗力
    int headId;//头像的武将ID
    int status;
    string content;
    string header;
    int online;
    bool isSound;//是否是语音
    int yayaId;//云娃id
    
    MessageType type;
};

#endif /* MessageData_hpp */
