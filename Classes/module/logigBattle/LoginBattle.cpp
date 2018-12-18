//
//  LoginBattle.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/11/9.
//
//

#include "LoginBattle.h"
#include "platform/CCSAXParser.h"
#include "tinyxml2/tinyxml2.h"
#include "../battle/BattleLoader.h"
#include "../../commonData/GlobalInfo.h"
LoginBattle::LoginBattle()
:_byteStream(NULL)
{
    
}
LoginBattle::~LoginBattle()
{
    CC_SAFE_DELETE(_byteStream);
    _byteStream = NULL;
}
bool LoginBattle::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Scene::init());
        parseConfigXML();
        bref = true;
    } while (false);
    return bref;
}
void LoginBattle::parseConfigXML()
{
    string path = "configs/teachFight.xml";
    string pBuffer = "";
//    ssize_t bufferSize = 0;
    pBuffer = FileUtils::getInstance()->getStringFromFile(path);//(path, "r", &bufferSize);
        
    parse(pBuffer.c_str());
//    delete [] pBuffer;
//    pBuffer = NULL;

}
void LoginBattle::parse(const char* content)
{
    tinyxml2::XMLDocument* xmlDoc = new tinyxml2::XMLDocument();
    xmlDoc->Parse(content);
    
    tinyxml2::XMLElement* rootNode = xmlDoc->RootElement();
    tinyxml2::XMLElement* node = rootNode->FirstChildElement();

    
    GlobalInfo::getInstance()->battleType = kBattleType_LoginBattle;
    _byteStream = new ByteStream(2048);
    _byteStream->putInt(221000);//battleid
    _byteStream->putInt(0);//血瓶数量
    _byteStream->put(2);//上阵人数

    for(node = node->FirstChildElement(); node ; node = node->NextSiblingElement())
    {
        string id = node->Attribute("ID");
        string dictID = node->Attribute("dictID");
        string quality = node->Attribute("quality");
        string level = node->Attribute("level");
        string prestige = node->Attribute("prestige");
        string health = node->Attribute("health");
        string attack = node->Attribute("attack");
   
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
        
        _byteStream->putInt(atoi(id.c_str()));
        _byteStream->putInt(atoi(dictID.c_str()));
        _byteStream->put(atoi(quality.c_str()));
        _byteStream->putInt(atoi(level.c_str()));
        _byteStream->putInt(atoi(prestige.c_str()));
        _byteStream->putInt(atoi(health.c_str()));
        _byteStream->putInt(atoi(attack.c_str()));
        _byteStream->putInt(atoi(defend.c_str()));
        _byteStream->putInt(atoi(critic.c_str()));
        _byteStream->putInt(atoi(tenaci.c_str()));
        _byteStream->putInt(atoi(hit.c_str()));
        _byteStream->putInt(atoi(block.c_str()));
        _byteStream->putInt(atoi(damageAdd.c_str()));
        _byteStream->putInt(atoi(fireResist.c_str()));
        _byteStream->putInt(atoi(iceResist.c_str()));
        _byteStream->putInt(atoi(boltResist.c_str()));
        _byteStream->putInt(atoi(windResist.c_str()));
        _byteStream->putInt(atoi(poisonResist.c_str()));
        
        
   
    }
}
void LoginBattle::onEnter()
{
    Scene::onEnter();
    _byteStream->setPosition(0);
    BattleLoader::show(_byteStream,SCENE_TAG_LOADING);
}
void LoginBattle::onExit()
{
    Scene::onExit();
    
}