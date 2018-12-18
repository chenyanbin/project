//
//  HomeLoader.cpp
//  FightPass
//
//  Created by 超 顾 on 15/7/9.
//
//

#include "HomeLoader.h"
#include "../../common/ImagePath.h"
#include "../../commonData/dictData/DictStageBattle/DictStageBattleManager.h"
#include "../../commonData/dictData/DictStageBattleMonster/DictStageBattleMonsterManager.h"
#include "../../commonData/dictData/DictNPC/DictNPCManager.h"
#include "../../commonData/dictData/DictMonster/DictMonsterManager.h"
#include "../../common/StringUtil.h"
#include "homeScene.h"
#include "platform/CCSAXParser.h"
#include "tinyxml2/tinyxml2.h"
bool HomeLoader::IS_IN_HOMELOADER = false;
HomeLoader::HomeLoader()
:totalNum(0)
,loadedNum(0)
,popUpLoading(NULL)
,m_fromeScene(0)
,tmxList(NULL)
,heroList(NULL)
,monsterList(NULL)
,resourcePre("")
{
    tmxList = new vector<string>();
    heroList = new vector<string>();
    monsterList = new vector<string>();
}
HomeLoader::~HomeLoader()
{
    CC_SAFE_RELEASE_NULL(popUpLoading);
    tmxList->clear();
    CC_SAFE_DELETE(tmxList);
    tmxList = NULL;
    
    heroList->clear();
    monsterList->clear();
    CC_SAFE_DELETE(heroList);
    CC_SAFE_DELETE(monsterList);
    heroList = NULL;
    monsterList = NULL;
    log("~HomeLoader~HomeLoader~HomeLoader");
}
bool HomeLoader::init(int fromeScene)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Scene::init());
        m_fromeScene = fromeScene;
        parseBattleResource();
        addMonsterList();
        addHeroList();
        bref = true;
    } while (false);
    IS_IN_HOMELOADER = bref;
    return bref;
}
HomeLoader* HomeLoader::create(int fromeScene)
{
    HomeLoader* layer = new HomeLoader();
    if(layer && layer->init(fromeScene))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void HomeLoader::show(int fromeScene)
{
    if(IS_IN_HOMELOADER)
    {
        return;
    }
    Director::getInstance()->purgeCachedData();
    HomeLoader* loader = HomeLoader::create(fromeScene);
    Director::getInstance()->replaceScene(loader);
}
void HomeLoader::addMonsterList()
{
    
}
void HomeLoader::addHeroList()
{
    DictHero* dictHero = DictHeroManager::getInstance()->getData(GlobalInfo::getInstance()->gameRole->mainHeroDictID);
    if(dictHero)
    {
        string path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictHero->resource.c_str());
        heroList->push_back(path);
    }
}
void HomeLoader::parseBattleResource()
{
    string bgPath = "";
    string closePath = "";
    string nearPath = "";
    string midPath = "";
    if(GlobalInfo::getInstance()->isInNewVillage)
    {
        bgPath = IMG_HOMEUI_MAIN001BG;
        closePath = IMG_HOMEUI_001CLOSE;
        nearPath = IMG_HOMEUI_001NEAR;
        midPath = IMG_HOMEUI_001MID;
    }
    else
    {
//        bgPath = IMG_HOMEUI_MAIN002BG;
//        closePath = IMG_HOMEUI_002CLOSE;
//        nearPath = IMG_HOMEUI_002NEAR;
//        midPath = IMG_HOMEUI_002MID;
        bgPath = IMG_HOMEUI_MAIN001BG;
        closePath = IMG_HOMEUI_001CLOSE;
        nearPath = IMG_HOMEUI_001NEAR;
        midPath = IMG_HOMEUI_001MID;
    }
    resourcePre = string(IMG_BATTLE_BATTLESCENE_PATH) ;
//    tmxList->push_back(bgPath);
    string pBuffer = FileUtils::getInstance()->getStringFromFile(bgPath);
    parseXMLDoc(pBuffer.c_str());
    
    pBuffer = FileUtils::getInstance()->getStringFromFile(closePath);
    parseXMLDoc(pBuffer.c_str());
    
    pBuffer = FileUtils::getInstance()->getStringFromFile(nearPath);
    parseXMLDoc(pBuffer.c_str());
    
    pBuffer = FileUtils::getInstance()->getStringFromFile(midPath);
    parseXMLDoc(pBuffer.c_str());
}
void HomeLoader::parseXMLDoc(const char* content)
{
    tinyxml2::XMLDocument* xmlDoc = new tinyxml2::XMLDocument();
    xmlDoc->Parse(content);
    
    tinyxml2::XMLElement* rootNode = xmlDoc->RootElement();
    tinyxml2::XMLElement* node = rootNode->FirstChildElement();
    
    string source = "";
   

    const char* nodeName = NULL;
    for(node = rootNode->FirstChildElement(); node ; node = node->NextSiblingElement())
    {
        nodeName = node->Value();
        if(strcmp(nodeName, "tileset") != 0)
        {
            break;
        }
       if(strcmp(nodeName, "tileset") == 0)
       {
          source = node->FirstChildElement()->Attribute("source");
          if(source.size())
          {
              source = IMG_BATTLE_BATTLESCENE_PATH + source;
              tmxList->push_back(source);
          }
       }
        
//        if(strcmp(nodeName, "objectgroup") == 0)
//        {
//            DictNPC* dictNpc = NULL;
//            tinyxml2::XMLElement* effectNode = NULL;
//            int npcID = 0;
//            string path = "";
//             for(effectNode = node->FirstChildElement(); effectNode ; effectNode = effectNode->NextSiblingElement())
//             {
//                 if(strcmp(effectNode->Attribute("name"), "npc") == 0)
//                 {
//                     npcID = atoi(effectNode->FirstChildElement()->FirstChildElement()->Attribute("value"));
//                     dictNpc = DictNPCManager::getInstance()->getData(npcID);
//                     path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictNpc->resource.c_str());
//                     monsterList->push_back(path);
//                 }
//             }
//           
//        }
    }
    
    
}
void HomeLoader::startLoad()
{
    Director::getInstance()->purgeCachedData();
    Director::getInstance()->getTextureCache()->removeAllTextures();
    loadedNum = 0;
    ssize_t len = tmxList->size();
    totalNum = len + monsterList->size() + heroList->size();
    if(len)
    {
//        for(int i = 0; i < len; i++)
//        {
//            log("tmxList->at(i)==%s",tmxList->at(i).c_str());
//            Director::getInstance()->getTextureCache()->addImageAsync(tmxList->at(i),CC_CALLBACK_1(HomeLoader::imageAsyncCallback, this));
//        }
        loadTmxImage();
    }
    else
    {
        loadAvatarResource();
    }
    
}
void HomeLoader::loadTmxImage()
{
    const char* path = tmxList->at(loadedNum).c_str();
    log("tmxList->path==%s",path);
    Director::getInstance()->getTextureCache()->addImageAsync(path,CC_CALLBACK_1(HomeLoader::imageAsyncCallback, this));
}
void HomeLoader::imageAsyncCallback(Ref* pSender)
{
    if(this->getReferenceCount() <= 0)
    {
        return;
    }
    
    loadedNum ++;
//     log("loadedNum==%f ,tmxList->size()=%ld",loadedNum,tmxList->size());
    float percent = loadedNum / totalNum * 100;
    if(popUpLoading && popUpLoading->getParent())
    {
        popUpLoading->setProgressPercent(percent );
    }
    if(tmxList)
    {
        if(loadedNum >= tmxList->size())
        {
            loadAvatarResource();
        }
        else
        {
            loadTmxImage();
        }
    }
    else
    {
        loadAvatarResource();
    }
}
void HomeLoader::loadAvatarResource()
{
    
    for(string resource : *heroList)
    {
        ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(resource, this, schedule_selector(HomeLoader::onAvatarLoaded));
    }
    
    
    for(string resource : *monsterList)
    {
        ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(resource, this, schedule_selector(HomeLoader::onAvatarLoaded));
    }
    
    if(heroList->size() == 0 && monsterList->size() == 0)
    {
        onAvatarLoaded(1);
    }
    
}
void HomeLoader::onAvatarLoaded(float percent)
{
    loadedNum ++ ;

    if(popUpLoading && popUpLoading->getParent())
    {
        popUpLoading->setProgressPercent(percent * 100);
    }
    if(percent < 1 || loadedNum < totalNum)
    {
        return;
    }
    Dialog::hideLoading();
    Scene* scene= HomeScene::showScene(SCENE_TAG_MAINUI);
    if(scene)
    {
        log("HomeLoader::onAvatarLoaded enter MainUI");
        Director::getInstance()->replaceScene(scene);
    }
}
void HomeLoader::onEnter()
{
    Scene::onEnter();
  

}
void HomeLoader::onEnterTransitionDidFinish()
{
    Scene::onEnterTransitionDidFinish();
    this->popUpLoading = Dialog::showLoading();
    CC_SAFE_RETAIN(popUpLoading);
    startLoad();
}
void HomeLoader::onExit()
{
    Scene::onExit();
}
void HomeLoader::onExitTransitionDidStart()
{
    Scene::onExitTransitionDidStart();
    IS_IN_HOMELOADER = false;
}
