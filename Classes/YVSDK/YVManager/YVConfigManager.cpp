/*********************************************************************************
*Copyright(C), 2015 YUNVA Company
*FileName:  RespondFactory.cpp
*Author:  Matt
*Version:  1.0.0
*Date:  2015-5-6
*Description:  SDK�����÷���
**********************************************************************************/

#include "YVConfigManager.h"
#include <stdarg.h> 
using namespace YVSDK;

void  YVConfigManager::setConfig(ConfigType type, ...)
{
	va_list ap;
	va_start(ap, type);			
	switch (type)
	{
	case ConfigAppid:
	{
		appid =	va_arg(ap, int);
		break;
	}
	case ConfigChannelKey:
	{
	    char* str = NULL;
		std::string stdstr;
		do 
		{
			str = NULL;
			str = (char*)va_arg(ap, char*);
			if (str == NULL || strcmp(str, "") == 0) break;
			stdstr.clear();
			stdstr.append(str);
			channelKey.push_back(stdstr);
		} while (true);
	    break;
	}
	case ConfigTempPath:
	{
		this->tempPath.clear();
		this->tempPath.append(va_arg(ap, char*));
		break;
	}
	case ConfigIsTest:
	{
		//��android����bool�ͻ�ң����Ǹĳ�int��������
		this->isTest = va_arg(ap, int);
		break;
	}
	case ConfigServerId:
	{
		this->serverid.clear();
		this->serverid.append(va_arg(ap, char*));
	    break;
	}
	case ConfigReadstatus:
	{
		this->readstatus = va_arg(ap, int);
		break;
	}
	case ConfigFriendChatCacheNum:
	{
		this->friendChatCacheNum = va_arg(ap, uint32);
		break;
	}
	case ConfigFriendHistoryChatNum:
	{
		this->friendHistoryChatNum = va_arg(ap, uint32);
		break;
	}
	case ConfigChannelChatCacheNum:
	{
		this->channelChatCacheNum = va_arg(ap, uint32);
		break;
	}
	case ConfigChannelHistoryChatNum:
	{
		this->channelHistoryChatNum = va_arg(ap, uint32);
		break;
	}
	case ConfigSpeechWhenSend:
	{
		this->speechWhenSend = va_arg(ap, int);
	}
	default:
		break;
	}

	va_end(ap);
}

YVConfigManager::YVConfigManager()
{
	//һֱ������Ĭ��ֵ�趨
	appid = 0;                 
	isTest = true;			
	readstatus = true;	
	serverid.append("0");

	friendChatCacheNum = 200;          
	channelChatCacheNum = 200;         

	friendHistoryChatNum = 5;  
	channelHistoryChatNum = 20; 
}