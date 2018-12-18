//
//  VideoPlayer.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/14.
//
//

#ifndef VideoPlayer_hpp
#define VideoPlayer_hpp

#include "cocos2d.h"
USING_NS_CC;
class VideoPlayer:public Node
{
public:
    VideoPlayer();
    ~VideoPlayer();
    virtual bool init();
    CREATE_FUNC(VideoPlayer);
public:
    void play(const char* path);
    ccMenuCallback onPlayFinished;
    void update(float dt);
protected:
    virtual void onEnter();
    virtual void onExit();
private:
    void setJumpBtn();
    void onJumpClick(Ref* pSender);
};


#endif /* VideoPlayer_hpp */
