//
//  FamouseEndBattle.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/21.
//名将传结束战斗
//succ	是否成功	byte	Y	1 战斗结束, boss胜
//2 boss死亡
//3 boss 逃跑
//bossId	boss id	int	Y	攻击的boss id
//hurt	伤害	int	Y	对boss的伤害值，打掉血的值
//useHpBottleCount	使用血瓶数量	int	Y	战役中消耗的血瓶数量
//

#ifndef FamouseEndBattle_hpp
#define FamouseEndBattle_hpp

#include "../MessageSendI.h"
class FamouseEndBattle:public MessageSendI
{
public:
    
    FamouseEndBattle(int state,int bossID,int damage,int usedBloodBottle);
    ~FamouseEndBattle();
    ByteStream *encodingData();
private:
    int m_isSuc;
    int m_bossID;
    int m_damage;
    int m_usedBloodBottle;
};

#endif /* FamouseEndBattle_hpp */
