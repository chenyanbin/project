#ifndef __SuiTang__ConfigFileReader__
#define __SuiTang__ConfigFileReader__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class ConfigFileReader
{
public:
	ConfigFileReader();
	~ConfigFileReader();
	void loadConfig();
	static ConfigFileReader* getInstance();
	static void destroyInstance();
private:
	void parse(const char* pBuffer);
private:
	static ConfigFileReader* _instance;
};
#endif
