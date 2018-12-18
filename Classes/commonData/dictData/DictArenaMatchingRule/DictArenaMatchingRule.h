#ifndef __DictArenaMatchingRule__
#define __DictArenaMatchingRule__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictArenaMatchingRule:public Ref
{
public:
	DictArenaMatchingRule():	
	id(0)//ID		
	,sectionMin(0)//区间下限		
	,sectionMax(0)//区间上限		
	,position1SectionMin(0)//位置1区间下限		
	,position1SectionMax(0)//位置1区间上限		
	,position2SectionMin(0)//位置2区间下限		
	,position2SectionMax(0)//位置2区间上限		
	,position3SectionMin(0)//位置3区间下限		
	,position3SectionMax(0)//位置3区间上限		
	,position4SectionMin(0)//位置4区间下限		
	,position4SectionMax(0)//位置4区间上限		
	,position5SectionMin(0)//位置5区间下限		
	,position5SectionMax(0)//位置5区间上限		
	{};

	int id;
	int sectionMin;
	int sectionMax;
	int position1SectionMin;
	int position1SectionMax;
	int position2SectionMin;
	int position2SectionMax;
	int position3SectionMin;
	int position3SectionMax;
	int position4SectionMin;
	int position4SectionMax;
	int position5SectionMin;
	int position5SectionMax;
};
#endif
