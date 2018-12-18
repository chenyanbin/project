//
//  TimeUtil.h
//  SuiTang
//
//  Created by zhangxiaobin on 14-7-22.
//
//

#ifndef __SuiTang__TimeUtil__
#define __SuiTang__TimeUtil__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class TimeUtil
{
public:
    
    static void setServerTime(const char* timeStr);
    static struct tm * getServerTime();
    static long long getNativeTime();
    static long long getTimestamp();
    
    static struct tm* getNativeTimeStruct();
    
    static struct tm* getDateByTimestamp(long long timeStamp);
    static const char* getDateString(long long timeStamp);
    
    
    static double getMicroSecond();
    static double getMilliSecond();
    //时间转日期
    static string timetodate(time_t  timer);
    //日期转秒
    static time_t strtotime(const char* date,const char*  format ="%Y-%m-%d-%H:%M:%S");
};

#endif /* defined(__SuiTang__TimeUtil__) */
