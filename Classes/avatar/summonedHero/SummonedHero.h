//
//  SummonedHero.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/2/2.
//技能昭唤英雄
//

#ifndef SummonedHero_hpp
#define SummonedHero_hpp

#include "../hero/Hero.h"
class SummonedHero:public Hero
{
public:
    SummonedHero();
    ~SummonedHero();
    virtual bool init(int heroID,int lifeTime);
    static SummonedHero* create(int heroID,int lifeTime);
    virtual char* class_name(){return "SummonedHero";};
public:
     void idle(); 
      void dead();
    bool skill1();
    bool skill2();
    bool skill3();
    bool skill4();
    bool attack1();
    bool attack2();
    bool attack3();
    bool attack4();
    bool attack5();
    void onActionCompleted();
private:
    void onDelay();
protected:
    void onEnter();
    void onExit();
public:
    int lifeTime;//生命周期，秒
};

#endif /* SummonedHero_hpp */
