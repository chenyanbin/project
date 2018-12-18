//
//  MessageManager.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/11/30.
//
//

#ifndef MessageManager_hpp
#define MessageManager_hpp

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "../../../YVSDK/YVPlatform.h"
using namespace YVSDK;
#include "MessageData.h"
class MessageManager
{
public:
    static MessageManager* getInstance();
    static void destoryInstance();
    void addWorldMsg(YVMessagePtr msg);//世界聊天信息
    Vector<YVMessagePtr>* getWordmsg();
private:
    
    MessageManager();
    ~MessageManager();
private:
    
    map<string,vector<YVMessagePtr>*>* dictData;
    static MessageManager* _instance;
};

#endif /* MessageManager_hpp */
