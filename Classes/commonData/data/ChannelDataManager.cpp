//
//  ChannelDataManager.cpp
//  FightPass
//
//  Created by zhangbin on 16/5/11.
//
//

#include "ChannelDataManager.hpp"
#include "../../common/PublicShowUI.h"
#include "../../common/Dialog/Dialog.h"
ChannelDataManager* ChannelDataManager::_instance = NULL;
ChannelDataManager::ChannelDataManager()
:m_loadIndex(0)
{
    
}
ChannelDataManager::~ChannelDataManager()
{
    
}

void ChannelDataManager::setConfigData(Json* json)
{
    Json* node = json->child->child;
    node = node->next;
    while (node)
    {
        if(node->type == Json_Array)
        {
            Json* item = node->child;
            DictChannel* data = new DictChannel();
            
            data->id = item->valueInt;
            item = item->next;
            data->channelID = item->valueString;
            item = item->next;
            data->channelName = item->valueString;
            item = item->next;
            data->url = item->valueString;
            data_list.insert(PublicShowUI::numberToString(data->id), data);
        }  
        node = node->next;
    }
    m_loadIndex = 0;
}
ChannelDataManager* ChannelDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new ChannelDataManager();
    }
    return _instance;
}
Vector<DictChannel*>* ChannelDataManager::getDataList()
{
    Vector<DictChannel*>* list = new Vector<DictChannel*>();
    for(auto value : data_list)
    {
        DictChannel* data  = ( DictChannel* )value.second;
        list->pushBack(data);
    }
    return list;
}
DictChannel* ChannelDataManager::getData(int id)
{
    string key = PublicShowUI::numberToString(id);
    DictChannel* data = (DictChannel*)(data_list.at(key));
    return data;
}
void ChannelDataManager::loadData()
{
    Dialog::showServerLoading();
    string resoucePreURL = GlobalInfo::getInstance()->resourceDomainList[m_loadIndex] + "/";
    string channelUrl = Configuration::getInstance()->getValue("channelDataURL").asString();
    std::string url =  resoucePreURL  + channelUrl;
    log("ChannelDataManager url===%s",url.c_str());
    network::HttpRequest* request = new network::HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(network::HttpRequest::Type::GET);
    request->setResponseCallback(this, httpresponse_selector(ChannelDataManager::onDataLoaded));
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
 
}
void ChannelDataManager::onDataLoaded(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response)
{
  
    if (!response)
    {
        onDataError();
      
        return;
    }
    
    if (!response->isSucceed())
    {
         onDataError();
        return;
    }
     Dialog::hideServerLoading();
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    std::string rest(buffer->begin(),buffer->end());
    log("Rest=====\n%s",rest.c_str());
    Json* root = Json_create(rest.c_str());
    log("root.name==%s string==%s",root->name,root->valueString);
    setConfigData(root);

}
void ChannelDataManager::onDataError()
{
    m_loadIndex ++;
    if(m_loadIndex >= GlobalInfo::getInstance()->resourceDomainList.size())
    {
         Dialog::hideServerLoading();
        MessageBox("渠道数据加载失败，请检查您的网络！", "提示");
        return;
    }
    this->loadData();
}