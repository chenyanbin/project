//
//  GeneralsData.h
//  FightPass
//
//  Created by 超 顾 on 15/8/6.
//
//

#ifndef __FightPass__CardPropertyData__
#define __FightPass__CardPropertyData__
#include "cocos2d.h"
#include "KarmaData.h"
USING_NS_CC;
using namespace std;

struct SkillData
{
    string skillName;//技能名字
    string skillDesc;//技能描述
};

class CardPropertyData:public Ref
{
public:
    CardPropertyData()
    :heroId(0)
    ,heroDictId(-1)
    ,heroName("")
    ,prestige()
    ,leadership(0)
    ,combatPower(0)
    ,level(0)
    ,levelMax(0)
    ,quality(0)
    ,hp(0)
    ,attack(0)
    ,defend(0)
    ,crit(0)
    ,tenaci(0)
    ,hit(0)
    ,block(0)
    ,backPackOrder(0)
    ,attackStrengh(0)
    ,fireResist(0)
    ,iceResist(0)
    ,boltResist(0)
    ,windResist(0)
    ,poisonResist(0)
    ,cardLocation(0)
    ,cardOldLocation(0)
    ,cardGetExperience(0)
    ,cardGetExpValue(1)
    ,cardConsumeCoin(0)
    ,heroExperience(20)
    ,heroMaxExperience(200)
    ,heroForce(-1)
    ,isSelect(false)
    ,freeExp(0)
    ,nextStepExp(0)
    ,nextLevelExp(0)
    ,headstatus(0)
    ,prestigeStatus(0)
    {
        karmList=new vector<KarmaData*>() ;
    }
    virtual void release()
    {
        Ref::release();
    }
    ~CardPropertyData()
    {
        skillList.clear();
        karmList->clear();
    }
    int heroId;//武将ID
    int heroDictId;//武将原型ID
    string heroName;//武将名字
    
    int cardLocation;//卡在历练栏牌位置 0代表没有装备
    bool isSelect;//是否选择了这个武将
    int cardOldLocation;//卡牌在历练栏原始位置；
    
    int freeExp;//	int	Y	当前武将池中可用经验
    int nextStepExp;//		int	Y	下一步需要经验，点击一下升级按钮，从武将经验池消耗多少经验放到经验条上
    int nextLevelExp;//		int	Y	升级到下个等级需要的经验 检验条满时的经验
    int cardGetExperience;//吞噬我你能得到多少经验
    float cardGetExpValue;
    int cardConsumeCoin;//吞噬我你花费多少铜钱
    
    int heroExperience;//当前卡牌经验
    int heroMaxExperience;//当前卡牌最大经验
    int heroForce;//当前所属势力   1魏
                  //             2吴
                  //             3蜀
    short prestige;//卡牌声望 现在是星级了
    int leadership;//卡牌领导力
    int combatPower;//卡牌战斗力
    int backPackOrder;//背包顺序
    int level;//卡牌等级
    int levelMax;//卡牌最大等级
    int quality; //卡牌品质
    int hp;//生命
    int attack;//攻击
    int defend;//防御
    int crit;//暴击加成
    int tenaci;//韧性加成
    int hit;//精准加成
    int block;//格挡加成
    int attackStrengh;//攻击强度
    int fireResist;//火焰抗性
    int iceResist;//冰冻抗性
    int boltResist;//雷暴抗性
    int windResist;//烈风抗性
    int poisonResist;//巫毒抗性
    int headstatus;//头像红点状态
    int prestigeStatus;//升级红点状态
    vector<SkillData> skillList;//技能
    vector<KarmaData*> *karmList;//缘分
};

#endif /* defined(__FightPass__GeneralsData__) */
