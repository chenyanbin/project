//
//  MessageManager.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/11/30.
//
//

#include "MessageManager.h"
#include "../../../common/PublicShowUI.h"
MessageManager* MessageManager::_instance = NULL;

MessageManager::MessageManager()
:dictData(NULL)
{
    dictData = new map<string,vector<YVMessagePtr>*>();
}
MessageManager::~MessageManager()
{
    dictData->clear();
    CC_SAFE_DELETE(dictData);
    dictData = NULL;
    _instance = NULL;
}
void MessageManager::destoryInstance()
{
    if(_instance)
    {
        delete _instance;
        _instance = NULL;
    }
}
MessageManager* MessageManager::getInstance()
{
    if(!_instance)
    {
        _instance = new MessageManager();
    }
    return _instance;
}
void MessageManager::addWorldMsg(YVMessagePtr msg)//世界聊天信息
{
//    YVPlatform::getSingletonPtr()->getChannalHistoryData(<#int channelKeyId#>, <#int index#>)
    
//    string key = PublicShowUI::numberToString(kChatChannel_World);
//    vector<YVMessagePtr>* list = dictData->at(key);
//    if(!list)
//    {
//        list = new vector<YVMessagePtr>();
////        dictData->insert(key, list);
//        dictData->insert(key, list);
//    }
//    list->push_back(msg);
}
Vector<YVMessagePtr>* MessageManager::getWordmsg()
{
    return NULL;
}
