//
//  LineupPageData.h
//  FightPass
//
//  Created by chenyanbin on 15/8/10.
//
//布阵阵容

#ifndef FightPass_LineupPage_h
#define FightPass_LineupPage_h
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class LineupPageData:public Ref
{
public:
    LineupPageData()
    :isDefault(0)
    ,lineupNo(1)
    ,masterSize(0)
    ,heroId(0)
    ,heroDictId(0)
    ,quality(0)
    ,heroName("")
    ,level(0)
    ,cheerSize(0)
    ,leadership(0)
    ,combatPower(0)
    ,karmaDesc1("")
    ,own1(0)
    ,karmaDesc2("")
    ,own2(0)
    ,skillName("")
    ,skilldesc("")
    ,skillOwn(0)
    ,hp(0)
    ,attack(0)
    ,defend(0)
    ,roleLeadership(0)
    {
        
    }
    virtual void release()
    {
        Ref::release();
    }
    ~LineupPageData()
    {
        
    }
    int isDefault;//是否默认阵容
    int lineupNo;//阵容编号（上传服务器）
    int masterSize;//上镇武将数量
    int heroId;//武将ID
    int heroDictId;//武将DictID
    int quality;//品质
    string heroName;//武将名字
    int level;//武将等级
    int leadership;//武将领导力
    int combatPower;//武将战力
    string karmaDesc1;
    int own1;
    string karmaDesc2;
    int own2;
    string skillName;
    string skilldesc;
    int skillOwn;
    int cheerSize;//助阵武将数量
    int hp;//生命
    int attack;//攻击
    int defend;//防御
    int roleLeadership;//角色领导力
};


#endif
