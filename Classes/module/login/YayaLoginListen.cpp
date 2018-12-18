//
//  YayaLoginListen.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/13.
//
//

#include "YayaLoginListen.hpp"
#include "../../common/Dialog/Dialog.h"
#include "../../commonData/GlobalInfo.h"
#include "../../common/PublicShowUI.h"
#include "../../protocol/UserCustomEvent.h"
YayaLoginListen* YayaLoginListen::_instance = NULL;
YayaLoginListen::YayaLoginListen()
{
    
}
YayaLoginListen::~YayaLoginListen()
{
    YVSDK::YVPlatform::getSingletonPtr()->delCPLoginListern(this);
    YVSDK::YVPlatform::getSingletonPtr()->delYYLoginListern(this);
    YVSDK::YVPlatform::getSingletonPtr()->delChannalloginListern(this);
}
YayaLoginListen* YayaLoginListen::getInstance()
{
    if(!_instance)
    {
        _instance = new YayaLoginListen();
    }
    return _instance;
}
void YayaLoginListen::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}
void YayaLoginListen::initListener()
{
    YVSDK::YVPlatform * platform = YVSDK::YVPlatform::getSingletonPtr();
    
    platform->delCPLoginListern(this);
    platform->delYYLoginListern(this);
    platform->delChannalloginListern(this);
    
    platform->addCPLoginListern(this);
    platform->addYYLoginListern(this);
    platform->addChannalloginListern(this);
}
void YayaLoginListen::onCPLoginListern(YVSDK::CPLoginResponce* r)
{
    if (r->result != 0 && GlobalInfo::getInstance()->isDebug)
    {
        Dialog::show(r->msg.c_str());
        return;
    }
    GlobalInfo::getInstance()->gameRole->yayaId = r->userid;
}
void YayaLoginListen::onYYLoginListern(YVSDK::LoginResponse* r)
{
    
}
void YayaLoginListen::onGetCpuUserListern(YVSDK::GetCpmsgRepond* r)
{
    
}
void YayaLoginListen::onChannalloginListern(YVSDK::ChanngelLonginRespond* r)
{
    if(r->result == 0)
    {
         GlobalInfo::getInstance()->chatChannelIsOk = true;
        PublicShowUI::broadUserMsg(CUSTOM_YAYA_CHANNELLOGIN_SUC,NULL);
    }
    else if(GlobalInfo::getInstance()->isDebug)
    {
         GlobalInfo::getInstance()->chatChannelIsOk = false;
        Dialog::show(r->msg.c_str());
         PublicShowUI::broadUserMsg(CUSTOM_YAYA_CHANNELLOGIN_SUC,NULL);
    }
}