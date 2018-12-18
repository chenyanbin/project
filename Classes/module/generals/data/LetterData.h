//
//  LetterData.h
//  FightPass
//
//  Created by 超 顾 on 15/8/19.
//
//

#ifndef __FightPass__LetterData__
#define __FightPass__LetterData__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class LetterData:public Ref
{
public:
    LetterData()
    :bookId(0)
    ,heroDictId(0)
    ,heroQuality(0)
    ,heroName("")
    ,curBookCount(0)
    ,needBookCount(0)
    ,costCoin(0)
    ,resource("")
//    :letterId(-1)
//    ,letterHeroId(-1)
//    ,letterHeroDictId(-1)
//    ,letterHeroQuality(-1)
//    ,letterHeroName("")
//    ,letterHeroResource("")
//    ,letterHeroLevel(1)
//    ,letterHeroPrestige(1)
//    ,letterHeroFriends(-1)
//    ,letterHeroMaxFriends(-1)
//    ,letterHeroNumber(-1)
//    ,letterHeroConsume(-1)
//    ,letterCount(-1)
//    ,letterBackPackOrder(0)
    {
        
    }
    virtual void release()
    {
        Ref::release();
    }
    ~LetterData()
    {
        
    }
    int bookId;//	书信id	int
    int heroDictId;//	武将dictId	int
    int heroQuality;//	武将品质	byte
    string heroName;//	武将名字	string
    int curBookCount;//	当前书信数量	short
    int needBookCount;//	合成所需书信数量	short
    int costCoin;//	合成所需花费铜钱	int
    string resource;//	资源素材	string
    
//    int letterId;//书信ID
//    int letterHeroDictId;//书信武将原型ID
//    int letterHeroId;//书信武将ID
//    int letterHeroQuality;//武将品质
//    string letterHeroName;//书信武将名字
//    string letterHeroResource;//书信武将素材
//    int letterHeroLevel;//书信武将等级
//    int letterHeroPrestige;//书信武将声望
//    int letterHeroFriends;//书信武将好友度
//    int letterHeroMaxFriends;//书信武将最大好友度
//    int letterHeroNumber;//书信数量
//    int letterHeroConsume;//书信消耗
//    int letterCount;//书信次数
//    int letterBackPackOrder;//书信排序
    
};

#endif /* defined(__FightPass__LetterData__) */
