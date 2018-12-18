//
//  ServerListDataManager.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/7/20.
//
//
#include "../../../common/Dialog/Dialog.h"
#include "ServerListDataManager.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
ServerListDataManager* ServerListDataManager::_instance = NULL;
ServerListDataManager::ServerListDataManager()
:serverList(NULL)
,recentList(NULL)
,_nowServerData(NULL)
{
    serverList = new Vector<ServerListData*>();
    recentList = new Vector<ServerListData*>();
}
ServerListDataManager::~ServerListDataManager()
{
    _nowServerData = NULL;
    serverList->clear();
    CC_SAFE_DELETE(serverList);
    
    recentList->clear();
    CC_SAFE_DELETE(recentList);
    
    
    serverList = NULL;
    recentList = NULL;
    _instance = NULL;
    
    
}
ServerListDataManager* ServerListDataManager::getInstance()
{
    if(!_instance)
    {
        _instance = new ServerListDataManager();
    }
    return _instance;
}
void ServerListDataManager::destoryInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;

}

void ServerListDataManager::parseServerList(const char* content)
{
    
    _nowServerData = NULL;
    this->serverList->clear();
    this->recentList->clear();
    rapidjson::Document _doc;
    _doc.Parse<0>(content);
    if (_doc.HasParseError())
    {
        Dialog::show("登陆json格式错误");
        return;
    }
    int retCode = _doc["ret_code"].GetInt();
    if(retCode != 0)
    {
        Dialog::show(_doc["debug_msg"].GetString());
        return;
    }
    const rapidjson::Value& serverListValue = _doc["serverList"];
    if(!serverListValue.IsArray())
    {
        return;
    }
    
    int count = serverListValue.Size();
    for (unsigned int i=0;i<count;i++)
    {
        const rapidjson::Value &userValue=serverListValue[i];
        if (userValue.IsObject())
        {
            ServerListData *data = new ServerListData();
            data->autorelease();
            data->id = userValue["server_id"].GetString();
            data->serverName = userValue["name"].GetString();
            data->IP = userValue["ip"].GetString();
            data->port = userValue["port"].GetInt();
            data->state = userValue["status"].GetInt();
            data->visible = userValue["visible"].GetInt();
            data->canEnter = userValue["canEnter"].GetInt();
            data->nameColor = userValue["nameColor"].GetUint64();
            this->serverList->pushBack(data);
   
      
        }
        
    }
    
    const rapidjson::Value& recentListValue = _doc["recentList"];
    count = recentListValue.Size();
    for (unsigned int i=0;i<count;i++)
    {
        const rapidjson::Value &userValue=recentListValue[i];
        if (userValue.IsObject())
        {
            ServerListData *data = new ServerListData();
            data->autorelease();
            data->id = userValue["server_id"].GetString();
            data->serverName = userValue["name"].GetString();
            data->IP = userValue["ip"].GetString();
            data->port = userValue["port"].GetInt();
            data->state = userValue["status"].GetInt();
            data->visible = userValue["visible"].GetInt();
            data->canEnter = userValue["canEnter"].GetInt();
            data->nameColor = userValue["nameColor"].GetUint64();
            this->recentList->pushBack(data);
            
        }
        
    }
    if(recentList->size())
    {
         _nowServerData = recentList->at(0);
    }
    else if(serverList->size())
    {
        _nowServerData = serverList->at(0);
    }

    
}

Vector<ServerListData*>* ServerListDataManager::getServerList()
{
   return this->serverList;
}
Vector<ServerListData*>* ServerListDataManager::getRecentList()
{
    return this->recentList;
}