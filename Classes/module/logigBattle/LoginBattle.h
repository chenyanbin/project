//
//  LoginBattle.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/11/9.
//首次登陆的战斗
//

#ifndef LoginBattle_hpp
#define LoginBattle_hpp
#include "../../net/bytestream.h"
#include "cocos2d.h"
using namespace std;
using namespace cocos2d;
class LoginBattle:public Scene
{
public:
    LoginBattle();
    ~LoginBattle();
    virtual bool init();
    CREATE_FUNC(LoginBattle);
private:
    void parseConfigXML();
    void parse(const char* content);
protected:
    virtual void onEnter();
    virtual void onExit();
private:
    ByteStream* _byteStream;
};

#endif /* LoginBattle_hpp */
