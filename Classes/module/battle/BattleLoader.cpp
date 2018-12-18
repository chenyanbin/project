//
//  BattleLoader.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/6/11.
//
//

#include "BattleLoader.h"
#include "../../common/ImagePath.h"
#include "BattleScene.h"
#include "../../commonData/dictData/DictMusouBattle/DictMusouBattleManager.h"
#include "../../commonData/dictData/DictStageBattle/DictStageBattleManager.h"
#include "../../commonData/dictData/DictLegendBattle/DictLegendBattleManager.h"
#include "../../commonData/dictData/DictStageBattleMonster/DictStageBattleMonsterManager.h"
#include "../../commonData/dictData/DictMonster/DictMonsterManager.h"
#include "../../message/Decoding/stage/RequestEnterStageBattle.h"
#include "../../message/Decoding/musou/RequestMusouFightMsg.h"
#include "../../message/Decoding/famouseGeneral/FamouseFightMsg.hpp"
#include "../../net/NetworkDataProcessing.h"
#include "platform/CCSAXParser.h"
#include "tinyxml2/tinyxml2.h"
#include "../../tdTalkData/TDTalkDataManager.hpp"
BattleLoader::BattleLoader()
:totalNum(0)
,loadedNum(0)
,popUpLoading(NULL)
,m_battleID(0)
,m_fromeScene(0)
,tmxList(NULL)
,heroList(NULL)
,monsterList(NULL)
,resourcePre("")
,envirEffectList(NULL)
,_byteStream(NULL)
{
    tmxList = new vector<string>();
    heroList = new vector<string>();
    monsterList = new vector<string>();
    envirEffectList = new vector<string>();
}
BattleLoader::~BattleLoader()
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
    
    envirEffectList->clear();
    CC_SAFE_DELETE(envirEffectList);
    envirEffectList = NULL;
    CC_SAFE_DELETE(_byteStream);
    _byteStream = NULL;
}
bool BattleLoader::init(ByteStream* bytestream,int fromeScene)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Scene::init());
        if(bytestream)
        {
            int len = bytestream->length();
            uint8_t* buf = new uint8_t[len];
            memcpy(buf, bytestream->getBuf(), len);
            _byteStream = new ByteStream(buf,len,true);
            _byteStream->setPosition(bytestream->_count);
            this->m_battleID = bytestream->getInt();
        }
      
        m_fromeScene = fromeScene;
        parseBattleResource();
        addMonsterList();
        addHeroList();
        bref = true;
    } while (false);
    return bref;
}
BattleLoader* BattleLoader::create(ByteStream* bytestream,int fromeScene)
{
    BattleLoader* layer = new BattleLoader();
    if(layer && layer->init(bytestream,fromeScene))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void BattleLoader::show(ByteStream* bytestream,int fromeScene)
{

    Director::getInstance()->purgeCachedData();

    BattleLoader* loader = BattleLoader::create(bytestream,fromeScene);
    Director::getInstance()->replaceScene(loader);
}
void BattleLoader::requestStageBattle(int stageBattleID)
{
    Dialog::showServerLoading(.5);
    if(GlobalInfo::getInstance()->battleType == kBattleTYPe_SanGuoWushuan)
    {
        RequestMusouFightMsg* msg = new RequestMusouFightMsg(stageBattleID);
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg = NULL;
        
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_MingZhanYi)
    {
        RequestEnterStageBattle* msg = new RequestEnterStageBattle(stageBattleID);
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg = NULL;
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_MingJiangZhuan)
    {
        GlobalInfo::getInstance()->battleType = kBattleType_MingJiangZhuan;
        FamouseFightMsg* msg = new FamouseFightMsg(stageBattleID);
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg = NULL;
    }
    else
    {
        Dialog::hideServerLoading();
    }
    TDTalkDataManager::getInstance()->onMissionBegain(PublicShowUI::numberToString(stageBattleID).c_str());
   
}
void BattleLoader::addMonsterList()
{

}
void BattleLoader::addHeroList()
{
    
}
void BattleLoader::parseBattleResource()
{
    
    const char* path = NULL;
     string resource = "";//stageBattle->mapResource;
    string envirEffect = "";
    string skyEffect = "";
    if(GlobalInfo::getInstance()->battleType == kBattleType_MingZhanYi)
    {
        DictStageBattle* stageBattle = DictStageBattleManager::getInstance()->getData(this->m_battleID);
        if(!stageBattle)
        {
            return;
        }
        path = PublicShowUI::getResImgPath(IMG_BATTLE_MAPBG, stageBattle->background.c_str());
        resource = stageBattle->mapResource;
        envirEffect = stageBattle->envirEffect;
        skyEffect = stageBattle->skyEffect;
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleTYPe_SanGuoWushuan)
    {
        DictMusouBattle* musouBattle = DictMusouBattleManager::getInstance()->getData(this->m_battleID);
        if(!musouBattle)
        {
            return;
        }
        path = PublicShowUI::getResImgPath(IMG_BATTLE_MAPBG, musouBattle->background.c_str());
        resource = musouBattle->mapResource;
        envirEffect = musouBattle->envirEffect;
        skyEffect = musouBattle->skyEffect;
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_MingJiangZhuan)
    {
        DictLegendBattle* legendBattle = DictLegendBattleManager::getInstance()->getData(this->m_battleID);
        if(!legendBattle)
        {
            return;
        }
        path = PublicShowUI::getResImgPath(IMG_BATTLE_MAPBG, legendBattle->background.c_str());
        resource = legendBattle->mapResource;
        envirEffect = legendBattle->envirEffect;
        skyEffect = legendBattle->skyEffect;
       
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_LoginBattle)
    {
        path = PublicShowUI::getResImgPath(IMG_BATTLE_MAPBG, "cheng_far");
        resource = "NewGuide";
        envirEffect = "shuye";
        skyEffect = "sun";
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_TestBattle || GlobalInfo::getInstance()->battleType == kBattleType_ArenaBattle)
    {
        path = PublicShowUI::getResImgPath(IMG_BATTLE_MAPBG, "cheng_far");
        resource = "arena001";
        envirEffect = "shuye";
        skyEffect = "sun";
    }
    tmxList->push_back(path);
    
    resourcePre = IMG_BATTLE_BATTLESCENE_PATH;
   
    path = PublicShowUI::getResImgPath(IMG_BATTLE_NEARMAP.c_str(), resource.c_str());
    
    string pBuffer = FileUtils::getInstance()->getStringFromFile(path);
    parseXMLDoc(pBuffer.c_str());
    
    path = PublicShowUI::getResImgPath(IMG_BATTLE_CLOSEMAP.c_str(),resource.c_str());
    pBuffer = FileUtils::getInstance()->getStringFromFile(path);
    parseXMLDoc(pBuffer.c_str());
    
    path = PublicShowUI::getResImgPath(IMG_BATTLE_MIDMAP.c_str(), resource.c_str());
    pBuffer = FileUtils::getInstance()->getStringFromFile(path);
    parseXMLDoc(pBuffer.c_str());
    
    if(envirEffect.size())
    {
        path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, envirEffect.c_str());
        this->envirEffectList->push_back(path);
    }
    if(skyEffect.c_str())
    {
        path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, skyEffect.c_str());
        this->envirEffectList->push_back(path);
    }
    path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, BIGSKILL_SKILLBG_EFFECT1);
    this->envirEffectList->push_back(path);
    path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, BIGSKILL_SKILLBG_EFFECT2);
    this->envirEffectList->push_back(path);
    

    path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, AVATAR_SHADOWE_MAINHERO);
    this->envirEffectList->push_back(path);
    path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, AVATAR_SHADOWE_BOSS);
    this->envirEffectList->push_back(path);
    path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, AVATAR_DEAD_WARNING);
    this->envirEffectList->push_back(path);
    path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, AVATAR_BLOOD_EFFECT);
    this->envirEffectList->push_back(path);
    path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, AUTOFIGHT_EFFECT);
    this->envirEffectList->push_back(path);
 
}
void BattleLoader::parseXMLDoc(const char* content)
{
    tinyxml2::XMLDocument* xmlDoc = new tinyxml2::XMLDocument();
    xmlDoc->Parse(content);
    
    tinyxml2::XMLElement* rootNode = xmlDoc->RootElement();
    tinyxml2::XMLElement* node = rootNode->FirstChildElement();
   
    string source = "";
    const char* nodeName = "";
//    bool effectIsOk = false;
    for(node = rootNode->FirstChildElement(); node ; node = node->NextSiblingElement())
    {
        nodeName =node->Value();
        if(strcmp(nodeName, "tileset") != 0)
        {
            break;
        }
        if(strcmp(nodeName, "tileset") == 0)
        {
            source = node->FirstChildElement()->Attribute("source");
            if(source.size())
            {
                source = resourcePre + source;
                tmxList->push_back(source);
            }
        }
//        if(strcmp(nodeName, "objectgroup") == 0)
//        {
//            if(strcmp(node->Attribute("name"), "effect") == 0)
//            {
//                tinyxml2::XMLElement* effectNode = NULL;
//                string effectName = "";
//                 for(effectNode = node->FirstChildElement(); effectNode ; effectNode = effectNode->NextSiblingElement())
//                 {
//                     effectName = effectNode->Attribute("name");
//                     source = IMG_BATTLE_BATTLESCENE_PATH;
//                     source = source + "effect/" + effectName + "/" + effectName +".ExportJson";
////                     log("effectpaht=%s",source.c_str());
//                     this->envirEffectList->push_back(source);
//                 }
//                effectIsOk = true;
//            }

//        }
        
//        if(effectIsOk && strcmp(nodeName, "tileset") != 0)
//        {
//            break;
//        }
        
    }
    
   
}
void BattleLoader::startLoad()
{
    Director::getInstance()->purgeCachedData();
    Director::getInstance()->getTextureCache()->removeAllTextures();
    loadedNum = 0;
    ssize_t len = tmxList->size();
    totalNum = len + monsterList->size() + heroList->size() + envirEffectList->size();
    loadImage();
    
}
void BattleLoader::loadImage()
{
    string str = tmxList->at(loadedNum);
    log("load image ==%s",str.c_str());
    Director::getInstance()->getTextureCache()->addImageAsync(str,CC_CALLBACK_1(BattleLoader::imageAsyncCallback, this));
}
void BattleLoader::imageAsyncCallback(Ref* pSender)
{
    loadedNum ++;
    float percent = loadedNum / totalNum * 100;
    if(popUpLoading && popUpLoading->getParent())
    {
        popUpLoading->setProgressPercent(percent);
    }
//    log("loadNum==%d tmxList.size==%ld",loadedNum,tmxList->size());
    if(tmxList && loadedNum >= tmxList->size())
    {
        loadAvatarResource();
    }
    else
    {
        loadImage();
    }
}
void BattleLoader::loadAvatarResource()
{
    for(string resource : *heroList)
    {
       ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(resource, this, schedule_selector(BattleLoader::onAvatarLoaded));
    }
    for(string resource : *monsterList)
    {
        ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(resource, this, schedule_selector(BattleLoader::onAvatarLoaded));
    }
    for(string resource : *envirEffectList)
    {
        ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(resource, this, schedule_selector(BattleLoader::onAvatarLoaded));
        log("envireffect==%s",resource.c_str());
    }
}
void BattleLoader::onAvatarLoaded(float percent)
{
    loadedNum ++ ;
    float progress = loadedNum / totalNum;
    if(popUpLoading && popUpLoading->getParent())
    {
        popUpLoading->setProgressPercent(progress * 100);
    }

    if(percent < 1 || loadedNum < totalNum)
    {
        return;
    }
    Dialog::hideLoading();
    Scene* scene = BattleScene::createScene(_byteStream,m_fromeScene);
    Director::getInstance()->replaceScene(scene);
}
void BattleLoader::onEnter()
{
    Scene::onEnter();
    this->popUpLoading = Dialog::showLoading();
    //    this->popUpLoading->removeGrayBg();
    CC_SAFE_RETAIN(popUpLoading);

}
void BattleLoader::onEnterTransitionDidFinish()
{
    Scene::onEnterTransitionDidFinish();
    startLoad();
}
void BattleLoader::onExit()
{
    Scene::onExit();
}
void BattleLoader::onExitTransitionDidStart()
{
    Scene::onExitTransitionDidStart();
}