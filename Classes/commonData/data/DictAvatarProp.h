//
//  DictHeroProp.h
//  FightPass
//英雄基础属性
//  Created by zhangxiaobin on 15/8/3.
//
//

#ifndef FightPass_DictHeroProp_h
#define FightPass_DictHeroProp_h
class DictAvatarProp:public Ref
{
public:
    DictAvatarProp()
    :id(0)
    ,type(0)
    ,dictID(0)
    ,quality(0)
    ,walkSpeed(0)
    ,prestige(0)//声望
    ,level(0)
    ,health(0)//生命
    ,attack(0)//攻击
    ,defend(0)//防御
    ,critic(0)//暴击率
    ,tenaci(0)//韧性率
    ,hit(0)//命中率
    ,block(0)//格挡率
    ,damageAdd(0)//伤害加成率
    ,fireResist(0)//火焰抗性率
    ,iceResist(0)//冰霜抗性率
    ,boltResist(0)//雷电抗性率
    ,windResist(0)//飓风抗性率
    ,poisonResist(0)//巫毒抗性率
    {};
    int id;
    short type;//1,英雄，2，monster
    int dictID;
    int quality;
    int walkSpeed;
    short prestige;
    short level;
    int health;
    int attack;
    int defend;
    double critic;
    double tenaci;
    double hit;
    double block;
    double damageAdd;
    double fireResist;
    double iceResist;
    double boltResist;
    double windResist;
    double poisonResist;
    ~DictAvatarProp()
    {
//        log("~DictAvatarProp ~DictAvatarProp");
    }
    DictAvatarProp* clone()
    {
        DictAvatarProp* prop = new DictAvatarProp();
        prop->autorelease();
        
        
        prop->id = this->id;
        prop->dictID = this->dictID;
        prop->type = this->type;
        prop->prestige = this->prestige;
        prop->level = this->level;
        prop->health = this->health;
        prop->attack = this->attack;
        prop->defend = this->defend;
        prop->critic = this->critic;
        prop->tenaci = this->tenaci;
        prop->hit = this->hit;
        prop->block = this->block;
        prop->damageAdd = this->damageAdd;
        prop->fireResist = this->fireResist;
        prop->iceResist = this->iceResist;
        prop->boltResist = this->boltResist;
        prop->windResist = this->windResist;
        prop->poisonResist = this->poisonResist;
        prop->quality = this->quality;
        return prop;
    }
};

#endif
