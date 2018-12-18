//
//  PlayerDataManager.cpp
//  BattleDemo
//
//  Created by zhangbin on 16/3/4.
//
//

#include "PlayerDataManager.hpp"
#include "tinyxml2/tinyxml2.h"
using namespace std;
#include "../battle/BattleLoader.h"
#include "../../avatar/Avatar.h"
PlayerDataManager* PlayerDataManager::_instance = NULL;
PlayerDataManager::PlayerDataManager()
:_frameRate(1)
,_targetRoleID(0)
{
    leftHeroList = new Vector<DictAvatarProp*>();
    rightHeroList = new Vector<DictAvatarProp*>();
}
PlayerDataManager::~PlayerDataManager()
{
    CC_SAFE_DELETE(leftHeroList);
    CC_SAFE_DELETE(rightHeroList);
    leftHeroList = NULL;
    rightHeroList = NULL;
    _instance = NULL;
}
void PlayerDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}
void PlayerDataManager::initData()
{
    leftHeroList->clear();
    rightHeroList->clear();
    Dialog::showServerLoading();
    std::string url = "http://36.110.17.45:7998/download/battleTest.xml?";
  
    network::HttpRequest* request = new network::HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(network::HttpRequest::Type::GET);
    request->setResponseCallback(this, httpresponse_selector(PlayerDataManager::onDataLoaded));
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
}
void PlayerDataManager::onDataLoaded(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response)
{
    Dialog::hideServerLoading();
    string errorURL = "http获取地址返回参数错误，请重新登陆 errorid=";
    if (!response)
    {
        return;
    }
    
    if (!response->isSucceed())
    {
        return;
    }
    
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    std::string rest(buffer->begin(),buffer->end());
    parse(rest.c_str());
    
}
void PlayerDataManager::parse(const char* content)
{
    tinyxml2::XMLDocument* xmlDoc = new tinyxml2::XMLDocument();
    xmlDoc->Parse(content);
    
    tinyxml2::XMLElement* rootNode = xmlDoc->RootElement();
    tinyxml2::XMLElement* node = NULL;

    // find the node
    tinyxml2::XMLElement* curNode = rootNode->FirstChildElement();

    string nodeName = "";
    while (nullptr != curNode)
    {
        nodeName = curNode->Value();
        node =curNode->FirstChildElement();
        if(nodeName == "leftPlayer" || nodeName == "rightPlayer")
        {
            
            for(; node ; node = node->NextSiblingElement())
            {
                
                string id = node->Attribute("ID");
                string type = node->Attribute("type");
                string dictID = node->Attribute("dictID");
                string quality = node->Attribute("quality");
                string health = node->Attribute("health");
                string attack = node->Attribute("attack");
                string level = node->Attribute("Level");
                string defend= node->Attribute("defend");
                string critic = node->Attribute("critic");
                string tenaci = node->Attribute("tenaci");
                string hit = node->Attribute("hit");
                string block = node->Attribute("block");
                string damageAdd = node->Attribute("damageAdd");
                string fireResist = node->Attribute("fireResist");
                string iceResist = node->Attribute("iceResist");
                string boltResist = node->Attribute("boltResist");
                string windResist = node->Attribute("windResist");
                string poisonResist = node->Attribute("poisonResist");
                DictAvatarProp* prop = new DictAvatarProp();
                prop->autorelease();
                prop->id = atoi(id.c_str());
                prop->type = atoi(type.c_str());
                prop->dictID = atoi(dictID.c_str());
                prop->quality = atoi(quality.c_str());
                prop->health = atoi(health.c_str());
                prop->attack = atoi(attack.c_str());
                prop->defend = atoi(defend.c_str());
                prop->critic = atoi(critic.c_str());
                prop->tenaci =atoi(tenaci.c_str());
                prop->hit = atoi(hit.c_str());
                prop->block =atoi(block.c_str());
                prop->damageAdd =atoi(damageAdd.c_str());
                prop->fireResist = atoi(fireResist.c_str());
                prop->iceResist = atoi(iceResist.c_str());
                prop->boltResist = atoi(boltResist.c_str());
                prop->windResist = atoi(windResist.c_str());
                prop->poisonResist = atoi(poisonResist.c_str());
                
                if(nodeName == "leftPlayer")
                {
                    leftHeroList->pushBack(prop);
                }
                else
                {
                    rightHeroList->pushBack(prop);
                }
            }
        }
        else if(nodeName == "frame")
        {
         
            string rate = curNode->Attribute("rate");
            this->_frameRate = atof(rate.c_str());
        }
        curNode = curNode->NextSiblingElement();
    }


    GlobalInfo::getInstance()->battleType = kBattleType_TestBattle;
    BattleLoader::show(NULL,SCENE_TAG_LOADING);
    
    
}
void PlayerDataManager::parseMsg(ByteStream* byteStream)
{
    if(leftHeroList)
    {
        leftHeroList->clear();
        rightHeroList->clear();
    }

    
    int len = byteStream->get();
    DictAvatarProp* prop = NULL;
    for(int i = 0; i <len; i++)
    {
        prop = new DictAvatarProp();
        prop->autorelease();
        
        prop->id = byteStream->getInt();
        if( prop->id == 0)
        {
            continue;
        }
        prop->type = AVATAR_TYPE_HERO;
        prop->dictID = byteStream->getInt();
        prop->quality = byteStream->getByte();
        prop->level = byteStream->getInt();
        prop->prestige = byteStream->getInt();
        prop->health = byteStream->getInt();
        prop->attack = byteStream->getInt();
        prop->defend = byteStream->getInt();
        prop->critic = byteStream->getInt();
        prop->tenaci = byteStream->getInt();
        prop->hit = byteStream->getInt();
        prop->block = byteStream->getInt();
        prop->damageAdd = byteStream->getInt();////攻击强度就是伤害加成率
        prop->fireResist = byteStream->getInt();
        prop->iceResist = byteStream->getInt();
        prop->boltResist = byteStream->getInt();
        prop->windResist = byteStream->getInt();
        prop->poisonResist = byteStream->getInt();

        leftHeroList->pushBack(prop);

    }
    len = byteStream->get();
    for(int i = 0; i <len; i++)
    {
        prop = new DictAvatarProp();
        prop->autorelease();
        
        prop->id = byteStream->getInt();
        if( prop->id == 0)
        {
            prop->id = i + 1;
        }
        prop->type = AVATAR_TYPE_HERO;
        prop->dictID = byteStream->getInt();
        prop->quality = byteStream->getByte();
        prop->level = byteStream->getInt();
        prop->prestige = byteStream->getInt();
        prop->health = byteStream->getInt();
        prop->attack = byteStream->getInt();
        prop->defend = byteStream->getInt();
        prop->critic = byteStream->getInt();
        prop->tenaci = byteStream->getInt();
        prop->hit = byteStream->getInt();
        prop->block = byteStream->getInt();
        prop->damageAdd = byteStream->getInt();////攻击强度就是伤害加成率
        prop->fireResist = byteStream->getInt();
        prop->iceResist = byteStream->getInt();
        prop->boltResist = byteStream->getInt();
        prop->windResist = byteStream->getInt();
        prop->poisonResist = byteStream->getInt();
        
        rightHeroList->pushBack(prop);
        
    }
    GlobalInfo::getInstance()->battleType = kBattleType_ArenaBattle;
    BattleLoader::show(NULL,SCENE_TAG_LOADING);
}
Vector<DictAvatarProp*>* PlayerDataManager::getLeftHeroList()
{
    return this->leftHeroList;
}
Vector<DictAvatarProp*>* PlayerDataManager::getRightHeroList()
{
    return this->rightHeroList;
}
PlayerDataManager* PlayerDataManager::getInstance()
{
    if(!_instance)
    {
        _instance = new PlayerDataManager();
    }
    return _instance;
}