//
//  SkillEffect.h
//  FightPass
//
//  Created by zhangxiaobin on 15/6/16.
//
//

#ifndef __FightPass__SkillEffect__
#define __FightPass__SkillEffect__

#include "editor-support/cocostudio/CCArmature.h"
using namespace cocostudio;
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class SkillEffect:public Node
{
public:
    SkillEffect();
    ~SkillEffect();
    virtual bool init(const char* _name,float offPosY = 0,bool isLoop = false);
    //name 资源名字
    //offPosY 资源高度偏移
    static SkillEffect* create(const char* _name,float offPosY = 0,bool isLoop = false);
    bool isPlayOver();
    void pauseAnimation();
    void playAnimation();
public:
    ccMenuCallback m_actionAttackCallBack;//判断攻击回调
    ccMenuCallback m_actionMovementCallBack;//播放结束回调
private:
    void setArmature();
    
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    
    void onMovementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
    void onFrameEvent(Bone *bone, const std::string& evt, int origin, int current);
    
private:
    string m_name;
    bool m_isPlayOver;//是否播放结束
    Armature* _armature;
    float m_offPosY;
    bool m_isLoop;
};

#endif /* defined(__FightPass__SkillEffect__) */
