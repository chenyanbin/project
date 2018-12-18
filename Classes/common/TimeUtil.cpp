//
//  TimeUtil.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 14-7-22.
//
//

#include "TimeUtil.h"
long time_diff = 0;
#include "StringUtil.h"
struct tm* TimeUtil::getDateByTimestamp(long long timeStamp)
{
//   long nativtime =  getNativeTime();
    struct tm *tm;
//    long* addr = &timeStamp;
	tm = localtime((time_t*)&timeStamp);
    return tm;
}
const char* TimeUtil::getDateString(long long timeStamp)
{
    tm* tm = getDateByTimestamp(timeStamp);
    
    int year = tm->tm_year + 1900;
    int month = tm->tm_mon + 1;
    int day = tm->tm_mday;
    int hour=tm->tm_hour;
    int min=tm->tm_min;
    int second=tm->tm_sec;
   log("%d-%02d-%02d %02d:%02d:%02d",year,month,day,hour,min,second);
    char* _day = new char[30];
//    sprintf(_day,"%d-%02d-%02d",year,month,day);
    sprintf(_day,"%d.%d.%d %d:%d",year,month,day,hour,min);
    return _day;
}
long long TimeUtil::getNativeTime()
{
    struct timeval tv;
     gettimeofday(&tv, NULL);
    long long  time = ((long long)tv.tv_sec) * 1000+ tv.tv_usec / 1000;
    return time;
}
struct tm* TimeUtil::getNativeTimeStruct()
{
    struct tm *tm;
	time_t timep;
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        time(&timep);
    #else
        struct timeval now;
        gettimeofday(&now, NULL);
        timep = now.tv_sec;
    #endif
	tm = localtime(&timep);
    return tm;
}
void TimeUtil::setServerTime(const char* timeStr)
{
    
//    long timep =  getNativeTime();
//    
//    std::string server_time = timeStr;
//    std::vector<std::string> timeArr = CommenFIleUtile::split(server_time, " ");
//    vector<string> dateArr = CommenFIleUtile::split(timeArr[0],"-");
//    vector<string> hourTime = CommenFIleUtile::split(timeArr[1],":");
//    
//    struct tm tm;
//    tm.tm_year = atoi(dateArr.at(0).c_str()) - 1900;
//    tm.tm_mon = atoi(dateArr.at(1).c_str()) - 1;
//    tm.tm_mday = atoi(dateArr.at(2).c_str());
//    
//    tm.tm_hour = atoi(hourTime.at(0).c_str());
//    tm.tm_min = atoi(hourTime.at(1).c_str());
//    tm.tm_sec = atof(hourTime.at(2).c_str());
//    tm.tm_isdst = 0;
//    long serverTime = mktime(&tm);
//    tm.tm_year = tm.tm_year + 1900;
//    tm.tm_mon = tm.tm_mon  + 1;
//    
//  
//    
//    //
//    time_diff = serverTime - timep;
}
struct tm * TimeUtil::getServerTime()
{
//    long long serverTime = getTimestamp();
    
//	struct tm *tm = localtime(&serverTime);
//    tm->tm_year = tm->tm_year + 1900;
//    tm->tm_mon = tm->tm_mon  + 1;
   
//    return tm;
    return NULL;
}
//得到服务器时间戳
long long TimeUtil::getTimestamp()
{
    long long timep =  getNativeTime();
    long long serverTime = timep + time_diff;
    return serverTime;
}
//得到毫秒
double TimeUtil::getMilliSecond()
{
    struct timeval tv;
    memset(&tv, 0, sizeof(tv));
    gettimeofday(&tv, NULL);
    
    double f1 = (double)tv.tv_sec + (float)(tv.tv_usec/1000)/(float)1000;
//    double f = tv.tv_sec*1000 + tv.tv_usec/1000;
    return f1;
}
//得到微秒
double TimeUtil::getMicroSecond()
{
    struct timeval tv;
    memset(&tv, 0, sizeof(tv));
    gettimeofday(&tv, NULL);
    
    double f = (double)tv.tv_sec + (float)tv.tv_usec/(float)1000000;
    
    return f;
}

/*
 @param       date
 @param       formart  of date
 @return      time_t
 @author      yangqijun@outlook.com
 */
time_t TimeUtil::strtotime(const char* date,const char*  format)
{
   
    vector<string> dateArr = StringUtil::split(date,"-");


    struct tm tm;
    tm.tm_year = atoi(dateArr.at(0).c_str()) - 1900;
    tm.tm_mon = atoi(dateArr.at(1).c_str()) - 1;
    tm.tm_mday = atoi(dateArr.at(2).c_str());

    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    tm.tm_isdst = 0;
    time_t time = mktime(&tm);
    return time;
  
}



string  TimeUtil::timetodate(time_t  timer)
{//需要秒
    struct tm *l=localtime(&timer);
    
    char buf[128];
    snprintf(buf,sizeof(buf),"%04d-%02d-%02d %02d:%02d:%02d",l->tm_year+1900,l->tm_mon+1,l->tm_mday,l->tm_hour,l->tm_min,l->tm_sec);
    string s(buf);
    return s;
}
