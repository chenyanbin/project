//
//  MapDataManager.h
//  FightPass
//
//  Created by zhangxiaobin on 15/6/16.
//
//

#ifndef __FightPass__MapDataManager__
#define __FightPass__MapDataManager__

#include "cocos2d.h"
USING_NS_CC;
#include "../../../avatar/Avatar.h"
typedef enum _Cross
{
    CROSS_STATE_HERO = 1,  //英雄行走路线
    CROSS_STATE_MONSTER = 2 //怪物行走路线
} Cross;
class MapDataManager
{
public:
    ~MapDataManager();
    static MapDataManager* getInstance();
    static void destoryInstance();
    void setMapData(TMXTiledMap* _map);
    int getWayNumberByPoint(Point cp);//得到息的路径编号
    Point getAvatarPosition(Point mapPos,int wayNumber,bool isLeft,Avatar* selfAvatar = NULL);
    
    Point positionToSelfPostion(Avatar* selfAvatar,Point postion);
    Point getAvatarWalkDirection(Avatar* avatar,bool isLeft,Point byPostion = Point::ZERO);
    inline bool isValiledPoint(Point cp,bool isLeft = true,Avatar* selfAvatar = NULL);//是否是有效的位置
    
    Point getFlashMovePostion(Avatar* target,Avatar* selfAvatar);//得到目标附近的英雄位置
public:
    int _nowBlockNum;//当前所在地图区域
    Point isTransferPoint(Point selfGrid);//是否是传送点
    inline int getBlockNum(Point selfGird);//得到所在格子的区域号
    float getBlockRightPos();//得到当前区域的边缘位置
    float getBlockLeftPos();//得到区域左边位置
    float setBlockLeftPos();
    __Set* _blockMonsterList;//阻挡怪列表
 
    Map<Avatar*,__Bool*>* _blockAvatars;//中了阻挡buff的人物角色们
public:
      float _mapHeight;
private:
    MapDataManager();
    static MapDataManager* _instance;
    TMXTiledMap* m_map;
    
    float m_tiledWidth;
    float m_tiledHeight;
  
    float _leftBlockPos;
    TMXLayer* roadLayer;//线路层
    TMXLayer* m_heroLayer;
    
 };

#endif /* defined(__FightPass__MapDataManager__) */
