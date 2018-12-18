//
//  ItemData.h
//  FightPass
//道具数量s
//  Created by zhangxiaobin on 15/9/28.
//
//

#ifndef ItemData_h
#define ItemData_h
class ItemData:public Ref
{
public:
    ItemData():itemType(0),itemId(0),itemCount(0),itemQuality(0)
    {
        
    }
    ~ItemData()
    {
        
    }
public:
    int itemType;//DictItemTypeEnum
    int itemId;//道具id
    int itemCount;//道具数量
    int itemQuality;//道具品质
};

#endif
