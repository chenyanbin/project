//
//  homeMapUI.cpp
//  FightPass
//
//  Created by 超 顾 on 15/6/2.
//
//


#include "HomeMapUI.h"
#include "../homeMainUI/mainUI/MainUI.h"
#include "../../../common/TimeUtil.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../module/battle/data/MapDataManager.h"
#include "HomeHeroManager.h"
Point HomeMapUI::INITPOINT = Point::ZERO;
HomeMapUI::HomeMapUI()
:bg_map(NULL)
,mySelfHero(NULL)
,mid_map(NULL)
,near_map(NULL)
,close_map(NULL)
,_NpcList(NULL)
,scaleMax(0)
,m_mapContainer(NULL)
,_mapWidth(0)
,_mapHeight(0)
,_maxZorder(10000)
,m_loadedIndex(0)
,maxHeroCount(0)
,mapScaleX(0)
{
    _NpcList = new Vector<Npc*>();
}

HomeMapUI::~HomeMapUI()
{
    CC_SAFE_RELEASE_NULL(mySelfHero);
    _NpcList->clear();
    CC_SAFE_DELETE(_NpcList);
    _NpcList = NULL;
    mid_map = NULL;
    near_map = NULL;
    close_map = NULL;
    bg_map = NULL;
}

void HomeMapUI::onEnter()
{
    BaseLayer::onEnter();
}
void HomeMapUI::onExit()
{
    BaseLayer::onExit();
}

void HomeMapUI::onEnterTransitionDidFinish()
{
     BaseLayer::onEnterTransitionDidFinish();
    mySelfBorn();
    setViewPointCenter(false);
    this->setTouchAllEnabled(true);
    
   
    
    loadAvatarResource();
   
}
void HomeMapUI::loadAvatarResource()
{
    m_loadedIndex = 0;
    Vector<RoleData*>* list = GlobalInfo::getInstance()->mainSceneHeroList;
    ssize_t len = list->size();
    DictHero* dictHero = NULL;
    const char* path = NULL;
    maxHeroCount = len;
    int failedCount = 0;
    for(int i = 0; i < len; i++)//第一的位置为自己的位置
    {
        dictHero = DictHeroManager::getInstance()->getData(list->at(i)->mainHeroDictID);
        if(!dictHero)
        {
            maxHeroCount = i;
            break;
        }
        
        path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictHero->resourceRun.c_str());
        if(path)
        {
            ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(HomeMapUI::onOtherPersonLoaded));
        }
        else
        {
            failedCount ++;
        }
        
    }
    if(maxHeroCount == 0)
    {
        onOtherPersonLoaded(1);
    }
}
void HomeMapUI::onOtherPersonLoaded(float percent)
{
     m_loadedIndex ++;
    log("percent==%f m_loadedIndex=%d total ==%d",percent,m_loadedIndex,maxHeroCount);

    if(percent < 1 || m_loadedIndex < maxHeroCount)
    {
        return;
    }
   this->runAction(Sequence::create(DelayTime::create(.5),CallFunc::create(CC_CALLBACK_0(HomeMapUI::setOtherUserList, this)), NULL));
    
    this->scheduleUpdate();
    loadNpcResource();
    
}
void HomeMapUI::loadNpcResource()
{
    TMXObjectGroup* group = near_map->getObjectGroup("NPC");
    auto& objs = group->getObjects();
    DictNPC* dictNPC = NULL;
    int npcID = 0;
    const char* path = NULL;
    for (auto& obj : objs)
    {
        ValueMap& object = obj.asValueMap();
        
        npcID = object.at("npcID").asInt();
        dictNPC = DictNPCManager::getInstance()->getData(npcID);
        if(dictNPC)
        {
            path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictNPC->resource.c_str());
            ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(HomeMapUI::onNpcLoaded));
        }
      
    }

}
void HomeMapUI::onNpcLoaded(float percent)
{
    log("onNpcLoaded==%f",percent);
    if(percent < 1)
    {
        return;
    }
    NpcBorn();
    
    MainUI::show(this->getParent(),2);
}
void HomeMapUI::setOtherUserList()
{
    m_loadedIndex = 0;
    
    HomeHeroManager::getInstance()->clear();
    this->schedule(schedule_selector(HomeMapUI::createOtherHero), 2, GlobalInfo::getInstance()->mainSceneHeroList->size(), 0);

}
void HomeMapUI::createOtherHero(float dt)
{
     Vector<RoleData*>* list = GlobalInfo::getInstance()->mainSceneHeroList;////第1的位置为自己的位置
    if(m_loadedIndex >= list->size())
    {
        this->unschedule(schedule_selector(HomeMapUI::createOtherHero));
        
        return;
    }
    TMXObjectGroup* group = near_map->getObjectGroup("hero");
   
    RoleData* data = list->at(m_loadedIndex);
    ValueMap object = group->getObject(PublicShowUI::numberToString(m_loadedIndex + 2));
    if(object.size())
    {
        float xx = object.at("x").asFloat();
        float yy = object.at("y").asFloat();
        Hero* hero= Hero::create(data->mainHeroDictID);
        if(hero)
        {
            hero->setScale(GlobalInfo::getInstance()->m_avatarScale);
            hero->setUID(data->roleID);
            hero->setAnchorPoint(Point::ZERO);
            hero->_walkSpeed = hero->getDictHero()->moveSpeed * GlobalInfo::getInstance()->m_avatarScale;
            hero->_wayNumber = 1;
          
            near_map->addChild(hero,10,data->roleID);
            hero->_destinatsionPostion = (Point(xx,yy));
            hero->setPosition(xx,yy);
            HomeHeroManager::getInstance()->addHero(hero);
        }
    }
    m_loadedIndex++;

}
void HomeMapUI::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    
    this->setTouchAllEnabled(false);
    this->unscheduleUpdate();
    clearResourcePerson();
    m_mapContainer->removeAllChildren();
    HomeHeroManager::destroyInstance();
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("");
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    
    ArmatureDataManager::destroyInstance();
}

bool HomeMapUI::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->isAnimation=false;
        mapScaleX = GlobalInfo::getInstance()->m_mapScale;
        
        scaleMax = GlobalInfo::getInstance()->screenScaleX * mapScaleX;
        m_mapContainer = Node::create();
        this->addChild(m_mapContainer,0);
        m_winSize = SDResource.size;
        m_winSize.width = m_winSize.width / mapScaleX;
        setBackground();
        setCloseMapZorder();
        bref = true;
    } while (false);
    return  bref;
}
HomeMapUI* HomeMapUI::create()
{
    HomeMapUI* layer = new HomeMapUI();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}
void HomeMapUI::setBackground()
{
    string bgPath = "";
    string closePath = "";
    string nearPath = "";
    string midPath = "";
  
    if(GlobalInfo::getInstance()->isInNewVillage)
    {
        bgPath = IMG_HOMEUI_MAIN001BG;
        nearPath = IMG_HOMEUI_001NEAR;
        midPath = IMG_HOMEUI_001MID;
   
    }
    else
    {

        bgPath = IMG_HOMEUI_MAIN001BG;
        nearPath = IMG_HOMEUI_001NEAR;
        midPath = IMG_HOMEUI_001MID;
     
    }

    bg_map= TMXTiledMap::create(bgPath);
    bg_map->setAnchorPoint(Point::ZERO);
    bg_map->setPosition(Point::ZERO);
 
    float scaleY = GlobalInfo::getInstance()->getMapScaleValue();
    scaleY = scaleY == 1 ? 1 : .9 * GlobalInfo::getInstance()->screenScaleY;
    
    bg_map->setScaleY(scaleY);
    
    
    m_mapContainer->addChild(bg_map,0);
    if(midPath.size())
    {
        mid_map = TMXTiledMap::create(midPath);
        mid_map->setAnchorPoint(Point::ZERO);
//        mid_map->setScaleY(scaleY);
        mid_map->setPosition(Point::ZERO);
        m_mapContainer->addChild(mid_map,1);
    }
    
    
   near_map=TMXTiledMap::create(nearPath);
   near_map->setAnchorPoint(Point::ZERO);

   near_map->setPosition(Point::ZERO);
   m_mapContainer->addChild(near_map,2);
   if(closePath.size())
   {
       close_map=TMXTiledMap::create(closePath);
       close_map->setAnchorPoint(Point::ZERO);
   
       close_map->setPosition(Point::ZERO);
       m_mapContainer->addChild(close_map,3);
   }
   
   
    MapDataManager::getInstance()->setMapData(near_map);
    TMXLayer* runGroup = near_map->getLayer("run");
    runGroup->setVisible(false);
    GlobalInfo::getInstance()->map_tiled_width = near_map->getTileSize().width;
    GlobalInfo::getInstance()->map_tiled_height = near_map->getTileSize().height;
    _mapWidth =  near_map->getMapSize().width * GlobalInfo::getInstance()->map_tiled_width;
    _mapHeight = near_map->getMapSize().height * GlobalInfo::getInstance()->map_tiled_height;
 
    HomeHeroManager::getInstance()->_mapWidth = _mapWidth;
    HomeHeroManager::getInstance()->_mapHeight = _mapHeight;
    Size size = near_map->getContentSize();
    m_mapContainer->setContentSize(size);

    
    m_mapContainer->setScale(scaleMax,scaleMax);
    size.width *= scaleMax;
    size.height *= scaleMax;
    m_mapContainer->setContentSize(size);
    this->setContentSize(size);
    
    
}
void HomeMapUI::setCloseMapZorder()
{
    Vector<Node*> list = near_map->getChildren();
    string nodeName = "";
    for(auto node : list)
    {
        nodeName = typeid(*node).name();
       
        if(nodeName.find("TMXLayer") != string::npos)
        {
            TMXLayer* layer= (TMXLayer*)node;
            float y = _mapHeight - layer->getProperty("y").asFloat();
            node->setZOrder(_maxZorder -  y);
            
        }
        else
        {
            node->setZOrder(_maxZorder - node->getPositionY());
        }
        
    }
}


void HomeMapUI::mySelfBorn()
{
    TMXObjectGroup* group = near_map->getObjectGroup("hero");
    if(!group)
    {
        return;
    }
    ValueMap object = group->getObject("1");
    float xx = object.at("x").asFloat();
    float yy = object.at("y").asFloat();
    mySelfHero = Hero::create(GlobalInfo::getInstance()->gameRole->mainHeroDictID);
    if(!mySelfHero)
    {
        return;
    }
    mySelfHero->setScale(GlobalInfo::getInstance()->m_avatarScale);
    mySelfHero->setAnchorPoint(Point::ZERO);
    mySelfHero->_walkSpeed = mySelfHero->getDictHero()->moveSpeed * GlobalInfo::getInstance()->m_avatarScale;
    mySelfHero->_wayNumber = 1;
    CC_SAFE_RETAIN(mySelfHero);
    near_map->addChild(mySelfHero,10);
    if(INITPOINT != Point::ZERO)
    {
        xx = INITPOINT.x;
        yy = INITPOINT.y;
    }
    mySelfHero->_destinatsionPostion = (Point(xx,yy));
   
    mySelfHero->setPosition(xx,yy);
}
void HomeMapUI::NpcBorn()
{
    _NpcList->clear();
    TMXObjectGroup* group = near_map->getObjectGroup("NPC");
    auto& objs = group->getObjects();
    Npc* npc = NULL;
    int npcID = 0;
    for (auto& obj : objs)
    {
        ValueMap& object = obj.asValueMap();
       
        npcID = object.at("npcID").asInt();
        npc = Npc::create(npcID);
        
        float xx = object.at("x").asFloat();
        float yy = object.at("y").asFloat();
        npc->setPosition(xx,yy);
        npc->_destinatsionPostion = (Point(xx,yy));
        npc->setScale(GlobalInfo::getInstance()->m_avatarScale);
        near_map->addChild(npc);
        npc->setZOrder(_maxZorder - yy);
        _NpcList->pushBack(npc);
        
    }
}

void HomeMapUI::update(float dt)
{
    if(!mySelfHero)
    {
        return;
    }
    this->mySelfHero->updatePositon(dt);
  
    //设置英雄位置
    float posX = MIN(_mapWidth - mySelfHero->_centerToSide,MAX(mySelfHero->_centerToSide,mySelfHero->_destinatsionPostion.x));
    float posY = MIN(_mapHeight - mySelfHero->_centerToBottom,MAX(mySelfHero->_centerToBottom,mySelfHero->_destinatsionPostion.y));
    this->mySelfHero->setPosition(posX,posY);
    INITPOINT.x = posX;
    INITPOINT.y = posY;
    setViewPointCenter();
    setCloseMapZorder();
    HomeHeroManager::getInstance()->updateHeroList(dt);
}
void HomeMapUI::setViewPointCenter(bool isTween)
{
    Point position = this->mySelfHero->getPosition();
    float centerX = mySelfHero->isLeft? m_winSize.width - m_winSize.width/3: m_winSize.width / 3;
    float x = MAX(position.x, centerX);
    float y = MAX(position.y, m_winSize.height / 2);
    x = MIN(x, _mapWidth - centerX);
  
    y = MIN(y, _mapHeight * GlobalInfo::getInstance()->m_mapScale  - m_winSize.height / 2);
    
    
    auto actualPosition = Point(x, y);
    auto centerOfView = Point(centerX, m_winSize.height / 2);
    auto viewPoint = centerOfView - actualPosition;

    
//    near_map-> setPosition(viewPoint);
//    near_map->setPositionX(viewPoint.x);
    isTween ? near_map->setPositionX(near_map->getPositionX() + (viewPoint.x - near_map->getPositionX()) * .2) : near_map->setPositionX(near_map->getPositionX() + (viewPoint.x - near_map->getPositionX()));
   
    if(near_map->getPositionX() <  m_winSize.width  - near_map->getContentSize().width)
    {
        near_map->setPositionX(m_winSize.width  - near_map->getContentSize().width);
    }
    else
    {
        if(GlobalInfo::getInstance()->isInNewVillage)
        {
            bg_map->setPositionX(viewPoint.x * BG_RATE);
        }
        else
        {
            bg_map->setPositionX(viewPoint.x * BG_RATE);
        }
        
        if(close_map)
        {
            this->close_map->setPositionX(viewPoint.x * CLOSE_RATE);
        }
        if(mid_map)
        {
            //      mid_map->setPosition(viewPoint * MID_RATE);
            this->mid_map->setPositionX(viewPoint.x * MID_RATE);
        }
    }
    if(bg_map->getPositionX() < m_winSize.width  - bg_map->getContentSize().width)
    {
        bg_map->setPositionX(m_winSize.width - bg_map->getContentSize().width);
    }
//    if(bg_map->getPositionY() < m_winSize.height - bg_map->getContentSize().height)
//    {
//  
//        bg_map->setPositionY(m_winSize.height - bg_map->getContentSize().height);
//    }
 
//

}
void HomeMapUI::clearResourcePerson()//清除人物资源
{
   
    DictHero* dictHero = DictHeroManager::getInstance()->getData(GlobalInfo::getInstance()->gameRole->mainHeroDictID);
    string path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictHero->resource.c_str());
    ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
    
    
    Vector<RoleData*>* list = GlobalInfo::getInstance()->mainSceneHeroList;
    ssize_t len = list->size();

    for(int i = 0; i < len; i++)//第一的位置为自己的位置
    {
        dictHero = DictHeroManager::getInstance()->getData(list->at(i)->mainHeroDictID);
        if(!dictHero)
        {
            break;
        }
        path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictHero->resource.c_str());
        ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
    }

    
    
    TMXObjectGroup* group = near_map->getObjectGroup("NPC");
    auto& objs = group->getObjects();
    DictNPC* dictNPC = NULL;
    int npcID = 0;
    for (auto& obj : objs)
    {
        ValueMap& object = obj.asValueMap();
        
        npcID = object.at("npcID").asInt();
        dictNPC = DictNPCManager::getInstance()->getData(npcID);
        if(dictNPC)
        {
            path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictNPC->resource.c_str());
            ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
        }
        
    }
    
    
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("");
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    Director::getInstance()->purgeCachedData();
    ArmatureDataManager::destroyInstance();
}

////////////////////

void HomeMapUI::didChangeDirectorTo(SimplePad* simplepad,Point direction)
{
    if(!this->mySelfHero)
    {
        return;
    }

    this->mySelfHero->walkWithDirection(direction,simplepad->isHold);
    
}
void HomeMapUI::isHoldingDirector(SimplePad* simplepad,Point direction)
{
    didChangeDirectorTo(simplepad,direction);
}
void HomeMapUI::simplePadTouchEnded(SimplePad* simplepad)
{
    stopWalk();
}

void HomeMapUI::stopWalk()
{
    if(this->mySelfHero)
    {
        this->mySelfHero->idle();
    }
}

//屏幕点击
bool HomeMapUI::onTouchBegan(Touch *touch, Event *unused_event)
{
//    float sx=GlobalInfo::getInstance()->screenScaleX;
    if(!close_map)
    {
        return false;
    }
    Point mouseDownPoint= touch->getLocation();
    
    Point downStart=close_map->convertToNodeSpace(mouseDownPoint);
    
    
    if (abs(downStart.x-this->mySelfHero->getPositionX())<this->mySelfHero->_centerToSide*scaleMax) {
        return true;
    }
    if (downStart.x>this->mySelfHero->getPosition().x) {
        if (downStart.y>this->mySelfHero->getPosition().y) {
            this->mySelfHero->walkWithDirection(Point(1,1),true);
        }else
        {
            this->mySelfHero->walkWithDirection(Point(1,-1),true);
        }
        
    }
    else
    {
        if (downStart.y>this->mySelfHero->getPosition().y) {
            this->mySelfHero->walkWithDirection(Point(-1,1),true);
        }else
        {
            this->mySelfHero->walkWithDirection(Point(-1,-1),true);
        }
    }
    mouseDownPoint.x-=near_map->getPositionX();

    
    return true;
}
void HomeMapUI::onTouchMoved(Touch *touch, Event *unused_event)
{
    
}
void HomeMapUI::onTouchEnded(Touch *touch, Event *unused_event)
{
    Point downStart= touch->getLocation();
}
void HomeMapUI::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    Touch* touch = touches.at(0);
    onTouchBegan(touch,unused_event);
}
void HomeMapUI::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    
}
void HomeMapUI::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    Touch* touch = touches.at(0);
    onTouchEnded(touch,unused_event);
   
}