//
//  YayaLoginListen.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/13.
//
//

#ifndef YayaLoginListen_hpp
#define YayaLoginListen_hpp
#include "../../YVSDK/YVSDK.h"
#include "cocos2d.h"
USING_NS_CC;
class YayaLoginListen:
public YVSDK::YVListern::YVCPLoginListern,
public YVSDK::YVListern::YVYYLoginListern,
public YVSDK::YVListern::YVGetCpuUserListern,
public YVSDK::YVListern::YVChannalloginListern
{
public:
    static YayaLoginListen* getInstance();
    static void destroyInstance();
    void initListener();
public:
    void onCPLoginListern(YVSDK::CPLoginResponce*);
    void onYYLoginListern(YVSDK::LoginResponse*);
    void onGetCpuUserListern(YVSDK::GetCpmsgRepond*);
    void onChannalloginListern(YVSDK::ChanngelLonginRespond*);
private:
    YayaLoginListen();
    ~YayaLoginListen();
    static YayaLoginListen* _instance;
};

#endif /* YayaLoginListen_hpp */
