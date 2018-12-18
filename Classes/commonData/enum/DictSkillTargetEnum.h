#ifndef __IpGame__DictSkillTargetEnum__
#define __IpGame__DictSkillTargetEnum__

enum DictSkillTargetEnum {
	
	DictSkillTargetEnumEnemy=1,//敌方
	DictSkillTargetEnumAlly=2,//友方
	DictSkillTargetEnumParty=3,//队友
	DictSkillTargetEnumSelf=4,//自身
	DictSkillTargetEnumLeastHealth=5,//敌方血量最少
	DictSkillTargetEnumTotal=6,//敌我所有
	DictSkillTargetEnumAllyLeastHealth=7,//友方血量最少
	DictSkillTargetEnumSkillTarget=8//技能目标
};
#endif