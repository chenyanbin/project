//
//  JuxianListData.h
//  FightPass
//
//  Created by chenyanbin on 15/9/7.
//
//

#ifndef FightPass_JuxianListData_h
#define FightPass_JuxianListData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class JuxianListData:public Ref
{
public:
    JuxianListData()
    :freeCount(0)
    ,freecountMsx(1)
    ,recruitCommandCount(1)
    ,ConId(0)
    ,oneConVal(0)
    ,tenConVal()
    ,remainingTimes(0)
    {
        
    }
    ~JuxianListData()
    {
        
    }
    int freeCount;//免费次数
    int freecountMsx ;//最大免费次数
    int recruitCommandCount;//聚仙令数量
    int ConId;//举贤一次花费类型
    int oneConVal;//举贤一次花费数量
    int tenConVal;//举贤十次花费数量
    int remainingTimes;//恢复一次需要的时间

};


#endif
