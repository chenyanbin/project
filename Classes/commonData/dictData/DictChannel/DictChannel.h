#ifndef __DictChannel__
#define __DictChannel__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictChannel:public Ref
{
public:
	DictChannel():	
	id(0)//id		
	,channelID("")//channelID		
	,channelName("")//渠道名		
	,url("")//url		
	{};

	int id;
	string channelID;
	string channelName;
	string url;
};
#endif
