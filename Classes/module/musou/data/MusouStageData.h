//
//  MusouStageData.h
//  FightPass
//
//  Created by zhangxiaobin on 15/10/13.
//
//

#ifndef MusouStageData_h
#define MusouStageData_h
#include "../../../common/TimeUtil.h"
class MusouStageData:public Ref
{
public:
    MusouStageData():stageID(0),status(0),endTime(0)
    {
        
    }
    ~MusouStageData()
    {
        
    }
    enum
    {
        STAGE_OPEN = 1,
        STAGE_CLOSE = 2//
    };
public:
    int stageID;
    int status;//	状态	 1开启 2未开启;
    long long getLeftTime()//得到剩余时间
    {
        if(endTime > 0)
        {
            return (endTime - TimeUtil::getNativeTime()) / 1000;
        }
        return 0;
    };
    void setLeftTimes(long long time)//设置剩余时间 //单位 秒
    {
        log("TimeUtil::getNativeTime()==%lld",TimeUtil::getNativeTime());
        endTime = TimeUtil::getNativeTime() + time * 1000;
        log("endTime==%lld",endTime);
    }
   
    long long endTime;//到期时间
};

#endif /* MusouStageData_h */
