//
//  PlayerDataManager.hpp
//  BattleDemo
//
//  Created by zhangbin on 16/3/4.
//
//

#ifndef PlayerDataManager_hpp
#define PlayerDataManager_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "../../commonData/data/DictAvatarProp.h"
#include <network/HttpRequest.h>
#include <network/HttpResponse.h>
#include <network/HttpClient.h>
#include "../../net/bytestream.h"
class PlayerDataManager:public Ref
{
public:
    PlayerDataManager();
    ~PlayerDataManager();
    void initData();
    static PlayerDataManager* getInstance();
    static void destroyInstance();
    
    void parseMsg(ByteStream* byteStream);
public:
    Vector<DictAvatarProp*>* getLeftHeroList();
    Vector<DictAvatarProp*>* getRightHeroList();
    float _frameRate;
    long _targetRoleID;
private:
    void parse(const char* content);
    void onDataLoaded(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);
private:
    static PlayerDataManager* _instance;
    
    Vector<DictAvatarProp*>* leftHeroList;
    Vector<DictAvatarProp*>* rightHeroList;
};

#endif /* PlayerDataManager_hpp */
