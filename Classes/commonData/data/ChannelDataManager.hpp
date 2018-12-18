//
//  ChannelDataManager.hpp
//  FightPass
//
//  Created by zhangbin on 16/5/11.
//
//

#ifndef ChannelDataManager_hpp
#define ChannelDataManager_hpp

#include "../dictData/DictChannel/DictChannel.h"
#include "editor-support/spine/Json.h"
#include <network/HttpRequest.h>
#include <network/HttpResponse.h>
#include <network/HttpClient.h>
class ChannelDataManager:public Ref
{
public:
    ChannelDataManager();
    ~ChannelDataManager();
    
    void setConfigData(Json* json);
    static ChannelDataManager* getInstance();
    DictChannel* getData(int id);
    
    void loadData();
    void onDataLoaded(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);
    void onDataError();
    Vector<DictChannel*>* getDataList();
private:
    static ChannelDataManager* _instance;
    Map<string,Ref*> data_list;
    int m_loadIndex ;
};

#endif /* ChannelDataManager_hpp */
