#ifndef __DictSkillKarma__
#define __DictSkillKarma__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictSkillKarma:public Ref
{
public:
	DictSkillKarma():	
	skillId(0)//技能ID		
	,heroName("")//技能拥有武将		
	,heroId(0)//技能拥有武将ID		
	,karmaHeroName("")//连携技对应武将		
	,karmaHeroId(0)//连携技对应武将ID		
	{};

	int skillId;
	string heroName;
	int heroId;
	string karmaHeroName;
	int karmaHeroId;
};
#endif
