#ifndef __DictRandomName__
#define __DictRandomName__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictRandomName:public Ref
{
public:
	DictRandomName():	
	id(0)//id		
	,surName("")//姓		
	,maleName("")//男名		
	,femaleName("")//女名		
	{};

	int id;
	string surName;
	string maleName;
	string femaleName;
};
#endif
