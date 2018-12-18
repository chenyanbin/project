//
//  BaseEquipData.h
//  FightPass
//
//  Created by 超 顾 on 15/8/7.
//
//

#ifndef __FightPass__BaseEquipData__
#define __FightPass__BaseEquipData__
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

struct BaseEquipProperty
{
    int propertyType;//属性类型
    int propertyNum;//属性值
};

class BaseEquipData:public Ref
{
public:
    BaseEquipData()
    :equipId(0)
    ,equipName("")
    ,equipDictId(0)
    ,equipLevel(0)
    ,equipMaxLevel(0)
    ,typeId(DictItemTypeEnumItemEquip)
    ,heroId(0)
    ,heroName("")
    ,canStrengthen(false)
    ,canPutOn(false)
    ,equipStatus(0)
    ,cardLocation(0)
    ,cardOldLocation(0)
    ,exp(0)
    ,maxExp(0)
    ,quality(0)
    ,resource("")
    ,status(0)
    ,equipParts(0)
    ,finalLevel(0)
    ,backPackOrder(0)
    ,isSelect(false)
    ,isAbleStrong(false)
    {
        
    }
    virtual void release()
    {
        Ref::release();
    }
    ~BaseEquipData()
    {
        propertyList.clear();
    }
    bool isSelect;//是否选择了这个武将
    int equipId;//装备ID
    int equipDictId;//装备原型ID
    int typeId;//装备类型ID
    string equipName;//装备名称
    int equipParts;//装备位置
    int equipLevel;//装备等级
    int quality;//装备品质
    int equipMaxLevel; //装备最大等级
    int finalLevel;//装备所谓的最终等级
    int heroId;//装备武将ID  0:表示没有人装备
    string heroName;//装备武将名字
    bool canStrengthen;//是否可熔炼；0否 1是
    int backPackOrder;//背包顺序
    int exp;//当前经验
    int maxExp;//最大经验
    string resource;//素材名字
    int redCanHarden;//红点标志
    int status ;//1已装备
//                2可装备：拥有对应部位的装备
//                3可合成：有足够的材料合成一个对应部位的装备(与武将品质相同)
//                4无装备：没有任何对应部位的材料
    int equipStatus;//1 可装备：符合装备条件，并且没有在任何武将身上.
                    //2 可卸下：已经在某个武将身上，包括其他武将.
                    //3 不可装备：不符合dict定义.
    bool isAbleStrong;//是否可强化 红点
    bool canPutOn;//
    int cardLocation;//卡在历练栏牌位置 0代表没有装备
    int cardOldLocation;//卡牌在历练栏原始位置；
    vector<BaseEquipProperty> propertyList;//装备属性
    
//    BaseEquipData* clone()
//    {
//        BaseEquipData* data = new BaseEquipData();
//        data->autorelease();
////        data->
//        return data;
//    }
};


#endif /* defined(__FightPass__BaseEquipData__) */
