 //
//  MapDataManager.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/6/16.
//
//

#include "MapDataManager.h"
#include "../../../common/StringUtil.h"
#include "../../../avatar/blockMonster/BlockMonster.h"
MapDataManager* MapDataManager::_instance = NULL;
MapDataManager::MapDataManager()
:m_map(NULL)
,m_tiledWidth(0)
,m_tiledHeight(0)
,roadLayer(NULL)
,_mapHeight(0)
,m_heroLayer(NULL)
,_nowBlockNum(0)
,_blockMonsterList(NULL)
,_leftBlockPos(0)
{
    _blockAvatars = new Map<Avatar*,__Bool*>();
}
MapDataManager::~MapDataManager()
{
    m_map = NULL;
    roadLayer = NULL;
    m_heroLayer = NULL;
    _blockMonsterList = NULL;
    CC_SAFE_DELETE(_blockAvatars);
    _blockAvatars = NULL;
}
MapDataManager* MapDataManager::getInstance()
{
    if(!_instance)
    {
        _instance = new MapDataManager();
    }
    return _instance;
}
void MapDataManager::destoryInstance()
{
    if(_instance)
    {
        delete _instance;
        _instance = NULL;
    }
}
void MapDataManager::setMapData(TMXTiledMap* _map)
{
    m_map = _map;
    m_tiledWidth= m_map->getTileSize().width;
    m_tiledHeight = m_map->getTileSize().height;
    _mapHeight = m_map->getMapSize().height * m_tiledHeight;
    roadLayer = m_map->getLayer("run");
    if(roadLayer)
    {
         roadLayer->setVisible(false);
    }
   

}

Point MapDataManager::positionToSelfPostion(Avatar* selfAvatar,Point postion)
{
    Point nowGrid;
    nowGrid.x = int(postion.x / m_tiledWidth);
    nowGrid.y = int((_mapHeight - postion.y) / m_tiledHeight);
   
    if(isValiledPoint(nowGrid))
    {
     
        int gridWay = MapDataManager::getInstance()->getWayNumberByPoint(nowGrid);
        if(gridWay != 0)
        {
            return postion;
        }
//        if(gridWay == selfAvatar->_wayNumber)
//        {
//            return postion;
//        }
//        else if(gridWay > 0)
//        {
//            int selfGridWay = selfAvatar->_wayNumber;
//            postion.y = postion.y - (selfGridWay -gridWay) * m_tiledHeight;
//            return postion;
//        }
       
    }
    return selfAvatar->getPosition();
}
Point MapDataManager::getAvatarPosition(Point mapPos,int way,bool isLeft,Avatar* selfAvatar)
{
    if(!roadLayer || way <= 0)
    {
        return mapPos;
    }
    Point nowPoint;
    nowPoint.x = int(mapPos.x / m_tiledWidth);
    nowPoint.y = int((_mapHeight -  mapPos.y) / m_tiledHeight);
//    int wayNumber = 0;
    if(isValiledPoint(nowPoint,isLeft,selfAvatar))
    {
//        if(MapDataManager::getInstance()->getWayNumberByPoint(nowPoint) == way)
//        {
//            return mapPos;
//        }
  
        if(MapDataManager::getInstance()->getWayNumberByPoint(nowPoint))
        {
            return mapPos;
        }
        
    }
    return Point::ZERO;
//下
//    Point toPoint = Point(nowPoint.x,nowPoint.y - 1);
//    if(isValiledPoint(toPoint,isLeft))
//    {
//        wayNumber =  this->getWayNumberByPoint(toPoint);
//        if(wayNumber)
//        {
//             mapPos.y = _mapHeight - toPoint.y * m_tiledHeight;
//            return mapPos;
//        }
//    }
//    //下
//    toPoint = Point(nowPoint.x,nowPoint.y + 1);
//    if(isValiledPoint(toPoint,isLeft))
//    {
//         wayNumber =  this->getWayNumberByPoint(toPoint);
//        if(wayNumber != 0)
//        {
//             mapPos.y = _mapHeight - toPoint.y * m_tiledHeight;
//            return mapPos;
//        }
//    }
//    //左右
//    toPoint = nowPoint;
//    toPoint.x = isLeft ? toPoint.x - 1 : toPoint.x + 1;
//    if(isValiledPoint(toPoint,isLeft))
//    {
//        wayNumber =  this->getWayNumberByPoint(toPoint);
//        if(wayNumber != 0)
//        {
//            mapPos.x = toPoint.x * m_tiledWidth;
//            return mapPos;
//        }
//    }
//    
//    return Point::ZERO;
}
//Point MapDataManager::getAvatarWalkDirection(Avatar* avatar,bool isLeft)
//{
//    int tiledX = (avatar->getPositionX() / m_tiledWidth);
//    int tiledY = ((_mapHeight - avatar->getPositionY()) / m_tiledHeight);
//    Point toPoint = Point::ZERO;
//
//    if(isLeft)
//    {
//        
//        toPoint = Point(tiledX -1 ,tiledY);
//        if(isValiledPoint(toPoint,isLeft))
//        {
////            //左边
//            if(avatar->_wayNumber == this->getWayNumberByPoint(toPoint))
//            {
//                return Point(-1,0);
//            }
//        }
//        //上
//        toPoint = Point(tiledX,tiledY - 1);
//        if(isValiledPoint(toPoint,isLeft))
//        {
//            if(avatar->_wayNumber == this->getWayNumberByPoint(toPoint))
//            {
//                return Point(0,1);
//            }
//        }
//        //下
//        toPoint = Point(tiledX,tiledY + 1);
//        if(isValiledPoint(toPoint,isLeft))
//        {
//            if(avatar->_wayNumber == this->getWayNumberByPoint(toPoint))
//            {
//                return Point(0,-1);
//            }
//        }
//        
//        //左上
//        toPoint = Point(tiledX -1 ,tiledY - 1);
//        if(isValiledPoint(toPoint,isLeft))
//        {
//            if(avatar->_wayNumber == this->getWayNumberByPoint(toPoint))
//            {
//                return Point(-1,1);
//            }
//        }
//        
//        //左下
//        toPoint = Point(tiledX -1 ,tiledY + 1);
//        if(isValiledPoint(toPoint,isLeft))
//        {
//            if(avatar->_wayNumber == this->getWayNumberByPoint(toPoint))
//            {
//                 return Point(-1,-1);
//            }
//        }
//    }
//    else
//    {
//        //右边
//        toPoint = Point(tiledX +1 ,tiledY);
//        if(isValiledPoint(toPoint,isLeft))
//        {
//            if(avatar->_wayNumber == this->getWayNumberByPoint(toPoint))
//            {
//                return Point(1,0);
//            }
//        }
//        //上
//        toPoint = Point(tiledX,tiledY - 1);
//        if(isValiledPoint(toPoint,isLeft))
//        {
//            if(avatar->_wayNumber == this->getWayNumberByPoint(toPoint))
//            {
//                return Point(0,1);
//            }
//        }
//        //下
//        toPoint = Point(tiledX,tiledY + 1);
//        if(isValiledPoint(toPoint,isLeft))
//        {
//            if(avatar->_wayNumber == this->getWayNumberByPoint(toPoint))
//            {
//                return Point(0,-1);
//            }
//        }
//
//        //右上
//        toPoint = Point(tiledX +1 ,tiledY - 1);
//        if(isValiledPoint(toPoint,isLeft))
//        {
//            if(avatar->_wayNumber == this->getWayNumberByPoint(toPoint))
//            {
//                return Point(1,1);
//            }
//        }
//        
//        //右下
//        toPoint = Point(tiledX +1 ,tiledY + 1);
//        if(isValiledPoint(toPoint,isLeft))
//        {
//            if(avatar->_wayNumber == this->getWayNumberByPoint(toPoint))
//            {
//                return Point(1,-1);
//            }
//        }
//        
//    }
//    return Point::ZERO;
//}
Point MapDataManager::getAvatarWalkDirection(Avatar* avatar,bool isLeft,Point byPostion)
{

    if(byPostion == Point::ZERO)
    {
        byPostion = avatar->getPosition();
    }
    int tiledX = (byPostion.x / m_tiledWidth);
    int tiledY = ((_mapHeight - byPostion.y) / m_tiledHeight);
    
    Point toPoint = Point::ZERO;
    
    if(isLeft)
    {
        
        toPoint = Point(tiledX -1 ,tiledY);
        if(isValiledPoint(toPoint,isLeft))
        {
            //            //左边
            if(this->getWayNumberByPoint(toPoint) != 0)
            {
                return Point(-1,0);
            }
        }
        //上
        toPoint = Point(tiledX,tiledY - 1);
        if(isValiledPoint(toPoint,isLeft))
        {
            if(this->getWayNumberByPoint(toPoint) != 0)
            {
                return Point(0,1);
            }
        }
        //下
        toPoint = Point(tiledX,tiledY + 1);
        if(isValiledPoint(toPoint,isLeft))
        {
            if(this->getWayNumberByPoint(toPoint) != 0)
            {
                return Point(0,-1);
            }
        }
        
        //左上
        toPoint = Point(tiledX -1 ,tiledY - 1);
        if(isValiledPoint(toPoint,isLeft))
        {
            if(this->getWayNumberByPoint(toPoint) != 0)
            {
                return Point(-1,1);
            }
        }
        
        //左下
        toPoint = Point(tiledX -1 ,tiledY + 1);
        if(isValiledPoint(toPoint,isLeft))
        {
            if(this->getWayNumberByPoint(toPoint) != 0)
            {
                return Point(-1,-1);
            }
        }
    }
    else
    {
        //右边
        toPoint = Point(tiledX +1 ,tiledY);
        if(isValiledPoint(toPoint,isLeft))
        {
            if(this->getWayNumberByPoint(toPoint) != 0)
            {
                return Point(1,0);
            }
        }
        //上
        toPoint = Point(tiledX,tiledY - 1);
        if(isValiledPoint(toPoint,isLeft))
        {
            if(this->getWayNumberByPoint(toPoint) != 0)
            {
                return Point(0,1);
            }
        }
        //下
        toPoint = Point(tiledX,tiledY + 1);
        if(isValiledPoint(toPoint,isLeft))
        {
            if(this->getWayNumberByPoint(toPoint) != 0)
            {
                return Point(0,-1);
            }
        }
        
        //右上
        toPoint = Point(tiledX +1 ,tiledY - 1);
        if(isValiledPoint(toPoint,isLeft))
        {
            if(this->getWayNumberByPoint(toPoint) != 0)
            {
                return Point(1,1);
            }
        }
        
        //右下
        toPoint = Point(tiledX +1 ,tiledY + 1);
        if(isValiledPoint(toPoint,isLeft))
        {
            if(this->getWayNumberByPoint(toPoint) != 0)
            {
                return Point(1,-1);
            }
        }
        
    }
    return Point::ZERO;
}

Point MapDataManager::getFlashMovePostion(Avatar* target,Avatar* selfAvatar)//得到目标附近的英雄位置
{
    Point direction = Point::ZERO;
    Point nowPoint = Point::ZERO;
    nowPoint.x = int(target->getPositionX() /m_tiledWidth);
    nowPoint.y = int(target->getPositionY() / m_tiledHeight);
    int diffWay = target->_wayNumber - selfAvatar->_wayNumber;
    direction = MapDataManager::getInstance()->getAvatarWalkDirection(target, target->getPositionX() < selfAvatar->getPositionX());
    if(direction != Point::ZERO)
    {
        direction.y = direction.y + diffWay;
    }
    
    nowPoint.x = (nowPoint.x + direction.x ) * m_tiledWidth;
    nowPoint.y = (nowPoint.y + direction.y) * m_tiledHeight;
    
    return nowPoint;
}

inline bool MapDataManager::isValiledPoint(Point pos,bool isLeft,Avatar* selfAvatar )//是否是有效的位置
{
    if(!roadLayer)
    {
        return true;
    }
    Size _layerSize = roadLayer->getLayerSize();
    bool bref = pos.x < _layerSize.width && pos.y < _layerSize.height && pos.x >=0 && pos.y >=0;
    
    if(_blockMonsterList)
    {
        BlockMonster* monster = NULL;
        for(__SetIterator it = this->_blockMonsterList->begin(); it != _blockMonsterList->end();   it++)
        {
            monster = (BlockMonster*)*it;
            if(pos == monster->_gridBlockPoint)
            {
                return false;
            }
        }
    }
    Point cp ;
    float distance = 0;
    float effectRange = 0;
    BuffEffectData* buffEffect = NULL;
    for(auto avatar : *_blockAvatars)
    {
        Avatar* target = avatar.first;
        
        if(target != selfAvatar )
        {
            if(selfAvatar && target->_avatarTeam != selfAvatar->_avatarTeam)
            {
                buffEffect = target->getBuffEffectData(DictBuffTypeEnumBlock);
                
                effectRange = buffEffect ? buffEffect->getDictBuff()->effect : GlobalInfo::getInstance()->map_tiled_width;
            
                distance = target->getPosition().getDistance(selfAvatar->getPosition());
                if(selfAvatar->isLeft && distance >= -effectRange && distance < 0)
                {
                    return false;
                }
                else if(!selfAvatar->isLeft && distance <= effectRange && distance > 0)
                {
                    return false;
                }
                cp = target->getGridPoint();
                if(pos == cp)
                {
                    return false;
                }
            }
            
         
        }
       
    }
    
    if(isLeft)
    {
//        int blockNum = getBlockNum(pos);
//        if(blockNum && _nowBlockNum != blockNum)
//        {
//            return false;
//        }
//        else if(blockNum && _nowBlockNum == blockNum)
//        {
//            return bref;
//        }
          return bref;
    }
    else
    {
        float rightPostion = getBlockRightPos();
        return pos.x * m_tiledWidth < rightPostion && bref;
    }
    
    return bref;
}

int MapDataManager::getWayNumberByPoint(Point gridPoint)
{
 
    int tileGid = roadLayer->getTileGIDAt(gridPoint);
    if(tileGid)
    {
        auto properties = m_map->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty())
        {
            int isRun = properties["cross"].asInt();
//            log("return waynumber===%d",isRun);
            return isRun;
        }
    }
    
    return 0;
}
Point MapDataManager::isTransferPoint(Point selfGrid)//是否是传送点
{
    TMXObjectGroup* group = m_map->getObjectGroup("Transfer");
    if(group)
    {
        Point gridPoint;
        ValueVector vector = group->getObjects();
        for(auto object : vector)
        {
            ValueMap& dict = object.asValueMap();
            
            gridPoint.x = int(dict.at("x").asInt() / m_tiledWidth);
            gridPoint.y = int(dict.at("y").asInt() / m_tiledHeight);
            if(gridPoint == selfGrid)
            {
                string str = dict.at("Transfer").asString();
                gridPoint.x = atof(StringUtil::split(str, ",")[0].c_str());
                gridPoint.y = atof(StringUtil::split(str, ",")[1].c_str());
                return gridPoint;
            }
        }
    }

    return Point::ZERO;

}
int MapDataManager::getBlockNum(Point selfGird)//得到所在格子的区域号
{
    TMXObjectGroup* group = m_map->getObjectGroup("block");
    if(group)
    {
        Point gridPoint;
        ValueVector vector = group->getObjects();
        for(auto object : vector)
        {
            ValueMap& dict = object.asValueMap();
            
            gridPoint.x = int(dict.at("x").asFloat() / m_tiledWidth);
            gridPoint.y = int((_mapHeight - dict.at("y").asFloat()) / m_tiledHeight);
            if(gridPoint == selfGird)
            {
                int blockNum = dict.at("block").asInt();
                return blockNum;
            }
        }
    }
    return 0;
}
float MapDataManager::getBlockLeftPos()//得到区域左边位置
{
    return this->_leftBlockPos;
   
}
float MapDataManager::setBlockLeftPos()
{
    TMXObjectGroup* group = m_map->getObjectGroup("block");
    if(group)
    {
        Point gridPoint;
        ValueVector vector = group->getObjects();
        for(auto object : vector)
        {
            ValueMap& dict = object.asValueMap();
            if(dict.find("block") != dict.end())
            {
                int blockNum = dict.at("block").asInt();
                if(blockNum == _nowBlockNum - 1)
                {
                    this->_leftBlockPos = dict.at("x").asFloat() + m_tiledWidth + 50;
                    break;
                }
            }
           
        }
    }
    return _leftBlockPos;
}
float MapDataManager::getBlockRightPos()//得到当前区域的边缘位置
{
    TMXObjectGroup* group = m_map->getObjectGroup("block");
    if(group)
    {
        Point gridPoint;
        ValueVector vector = group->getObjects();
        for(auto object : vector)
        {
            ValueMap& dict = object.asValueMap();
            int blockNum = dict.at("block").asInt();
            if(blockNum == _nowBlockNum)
            {
                return dict.at("x").asFloat() + m_tiledWidth ;
            }
        }
    }
    return m_map->getContentSize().width;
}
