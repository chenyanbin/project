//
//  Avatar.h
//  FightPass
//
//  Created by zhangxiaobin on 15/5/24.
//
//

#ifndef __FightPass__Avatar__
#define __FightPass__Avatar__
#include "../common/PublicShowUI.h"
#include "../common/TimeUtil.h"
#include "../protocol/UserCustomEvent.h"
#include "../commonData/dictData/DictSkill/DictSkillManager.h"
#include "../commonData/dictData/DictBuff/DictBuffManager.h"
#include "../soundManager/SoundManager.h"
#include "../commonData/data/DictAvatarProp.h"
#include "../module/battle/skillEffectLayer/SkillEffect.h"
#include "../common/ImagePath.h"
#include "../commonData/data/BuffEffectData.h"
#include "../commonData/enum/DictBuffTypeEnum.h"
#include "cocos2d.h"
USING_NS_CC;
#include "../module/battle/data/BattleDefine.h"
#include "editor-support/cocostudio/CCArmature.h"
using namespace cocostudio;
using namespace std;
#include "editor-support/cocostudio/CCSkin.h"
#define AN_STAND					"Stand"//待机
#define AN_MOVE						"Move"//移动
#define AN_PREPAERED                "Prepared"//准备攻击  ？
#define MONSTER_ATTACK              "Attack"//怪物攻击
#define AN_ATTACK					"Attack1"//普通攻击1
#define AN_ATTACK2                  "Attack2"//普通攻击2
#define AN_ATTACK3                  "Attack3"//普通攻击3
#define AN_ATTACK4                  "Attack4"//普通攻击3
#define AN_ATTACK5                  "Attack5"//普通攻击3

#define AN_SKILL					"Skill"//技能攻击
#define AN_SKILL1					"Skill1"//技能攻击
#define AN_SKILL2					"Skill2"//技能攻击
#define AN_SKILL3					"Skill3"//技能攻击
#define AN_SKILL4					"Skill4"//技能攻击
#define AN_HURT1                     "Hurt1"//受伤
#define AN_HURT2                     "Hurt2"//受伤
#define AN_DEAD                     "Dead"//死亡
#define AN_JUMP                     "Jumping"//跳
#define AN_JUMP_ATTACT              "JumpingAttack"//跳击
#define AN_DASH                     "dash"// 无
#define AN_DOWN                     "Falling"//下落
#define AN_WIN                      "Victory"//胜利
#define AN_BLOCK                    "Block"//格档
#define AN_DUCK                     "Duck"//闪避
#define BONE_WEAPON_IDLE    "weapon"
#define BONE_WEAPON_WALK    "walkweapon"
#define BONE_WEAPON_ATTACK  "attackweapon"
class Avatar;
typedef enum _AvatarType
{
    AVATAR_TYPE_NONE = 0,
    AVATAR_TYPE_HERO = 1,
    AVATAR_TYPE_MONSTER,
    AVATAR_TYPE_NPC 
}AvatarType;
typedef enum _avatarTeam
{
    AVATAR_TEAM_NONE = 0,
    AVATAR_TEAM_LEFT = 1,  //左边队伍
    AVATAR_TEAM_RIGHT = 2 //右边队伍
}AvatarTeam;
typedef enum _ActionState
{
    kActionStateNone = 0,
    kActionStateIdle = 1,
    kActionStateAttack1 = 2,
    kActionStateAttack2 = 3,
    kActionStateAttack3 = 4,
    kActionStateAttack4 = 5,
    kActionStateAttack5 = 6,
    kActionStateWalk = 7,
    kActionStateHurt = 8,
    kActionStateDead = 9,
    kActionStateJump = 10,
//    kActionStateDash = 11,       //冲撞
    kActionStatePrePareJumpAttack = 12,//将要跳击，准备跳击
    kActionStateJumpAttact = 13, //跳击
    kActionStateRebom = 14,
    kActionStateSkill1 = 15,
    kActionStateSkill2 = 16,
    kActionStateSkill3 = 17,
    kActionStateSkill4 = 18,
    kActionStateDown = 19,
    kActionStateKnockDown = 20,//击倒
    kActionStateKnockFly = 21,//击飞
    kActionStateKnockBack = 22,//击退
    kActionStateWin      = 23,//胜利动作
    kActionStateBlock = 24,//格档
    kActionStateDuck = 25//闪避

}ActionState;//行为基础状态

typedef enum _TaskState
{
    kTaskStateNone = 0,//无任务状态，待机
    kTaskStateGuard ,  //警戒态
    kTaskStatePatrol ,//巡逻状态
    kTaskStateEscape ,//逃跑状态
    kTaskStateAttack ,//进攻状态
    kTaskStateFollowMainHero,// 追随主将状态
}TaskState;//当前任务状态
typedef enum _AttackDelayState
{
    kdelayStateNone = 0,
    kdelayStateIdle,//原地站立
    kdelayStateWalkOn,//来回走
    kdelayStateWalkBack,//绕到敌方背后
    kdelayStateSlowAway//慢速远离
}AttackDelayState;

typedef struct
{
    Rect actual; //实际坐标相对于地图
    Rect original;//自身的坐标和矩形大小
}BoundingBox;


class Avatar:public Node
{
public:
    Avatar();
    ~Avatar();
    bool init(const std::string& name);
    virtual void onEnterScene();//进入视野
    virtual void onExitScene();//退出视野
    virtual void updateShadow();
    virtual void updateBossShadow();
    virtual void showName();//显示名字
    virtual char* class_name(){return "Avatar";};
public:
    void setFrameScale(float value);//设置播放帧速
    virtual void setTouchEnabled(bool _enabled);
    virtual void onBuff(int buffID,double damage);
    virtual void onBuff(int buffID,double damage,Avatar* attacker);
    void removeBuffByType(int buffType);
    virtual void addEffect(const char* effectName,float offY = 0 ,bool isAdded = false);//增加一些特效 ,isAdded表示是否可以垒加
    void hideShadow();
    void setUID(int ID);
    int getUID();
    bool hasBuffState(int buffState);//是否中了此buff效果类型
   
    virtual void pauseAction();//暂停动作
    virtual void resumeAction();//恢复动作
    virtual void idle();//空闲，站立
   
    void onFiveAttack();
    virtual void setDirection(Point direction);
    virtual bool attack1();//攻击
    virtual bool attack2();// 攻击2
    virtual bool attack3();// 攻击3
    virtual bool attack4();// 攻击4
    virtual bool attack5();// 攻击5
    virtual void hurtWithDamage(float damage,bool isCrit,bool isBlock,bool isSkillAttack);//受伤
    virtual void knockDown(float damage,bool isCrit,bool isBlock,bool isSkillAttack);//击倒
    virtual void knockFly(float damage,bool isCrit,bool isBlock,bool isSkillAttack);//击飞
    virtual void knockBack(float damage,Point targetPoint,bool isCrit,bool isBlock,bool isSkillAttack);//击退
    
    virtual void showBloodPlus(float value);//加血
    
    virtual void win();
    virtual void dead();//死亡
    virtual void walkWithDirection(Point direction,bool isHold);//行走
    virtual void jump();//跳 6.1
    virtual void jumpDown();//落
    virtual void jumpAttact(float delayTime);//跳击
    virtual void prepareJumpAttack(float delayTime);//准备跳击
    virtual void dash(float distance,float time = -1);//冲撞的距离
    virtual bool skill1();//必杀技1
    virtual bool skill2();//必杀技2
    virtual bool skill3();//必杀技3
    virtual bool skill4();//特大招
    virtual void unBlock();//解除格档
    virtual bool block(bool isAutoUnBlock = true);//格档
    virtual bool duck(float distance,float time);//闪避
    virtual bool usePassSkill();//使用被动技能
    virtual void onFlashMove(DictSkill* dictSkill) ;
    virtual void setActionState(ActionState state);
    ActionState getActionState();
    bool isPauseState();//是否是定身状态
    void updatePositon(float dt);
    void changeWeapon(const char* weaponName);//更换武器
    virtual void setPosition(float xx,float yy);
    virtual void update(float dt);
    virtual bool getIsCDState(int skillID);//是否cd中。。。
    virtual bool getIsDashing();
    virtual void onActionCompleted();
    
public:
       
    bool ableAction();//是否可以操作
    bool ableHurt();//是否可以受伤害
    void onAddSpeedBuff(int buffType,int value);//速度buff
    void onMinusSpeedBuff(int buffType,int value);
    void onSpeedReset(int buffType);
    void onTruntReset(int buffType);
    void onShieldBuffReset(int buffType);//护盾buff重置
    void onShieldBuff(int buffType,int addLife);//护盾buff
    void onAddAttribBuff(int buffType,int value);//增加属性buff
    void onMinusAttribBuff(int buffType,int value);//属性减少buff
    
    void onAddAttribReset(int buffType);//增加属性到期
    void onMinusAttribBuff(int buffType);//减少属性到期
    
    virtual void onAddBloodBuff(int buffType); //持续回血
    virtual void onHurtBloodBuff(int buffType);//持续伤害
    
    virtual void onTruntBuff(int buffType,Avatar* attacker);//嘲讽buff
    
    virtual int getCurSkillID();
    Point getGridPoint();
    BuffEffectData* getBuffEffectData(int buffType);
public:
  
protected:
    
    void onMovementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
    void onFrameEvent(Bone *bone, const std::string& evt, int origin, int current);
    void onEnter();
    void onExit();
    
    void onSkillEffectMoventEvent(Ref* target);
    void onAvatarResume(int oldDirection,bool isCallBack);//恢复动作
    BoundingBox createBoundingBoxWithOrigin(Point origin,Size size);
    void transformBoxes();
   
    void setAvatar();
    void changWeaponByBone(Bone* bone);
    
    void onHurtReset();//恢复受伤变红效果
    //减血效果
    void showBloodMinus(float damageNum,bool isCrit,bool isBlock ,bool isSkillAttack);
    void onJumpEnded();//跳跃结束
    
    void onBuffShadeIn(int buffTag);//渐入
    void onShadeOut(int buffTag);
    void clearBuff();
    void onBuffAttribInfo(int buffID);
    void setBloodProgress();
    void updateBlood();
    void setAbleJumpAttackFlag(bool flag);
    void addShieldBlood();//添加护盾血条
public:
    
    float _totalHitPoints;//总血量
    Point _destinatsionPostion;//目标位置
    float _centerToSide;  //中心到精灵边的距离
    float _centerToBottom;//中心到精灵底部的距离
    Armature* m_avatar;
    Avatar* trunter;//嘲讽者
    AvatarType _avatarType;
    AvatarTeam _avatarTeam;
    TaskState _taskState;
    AttackDelayState _delayState;
    int _dashSkillID;//冲撞用的技能
    int _wayNumber;//路径编号
    float _walkSpeed;//实际行走速率
    float _baseSpeed;//基础属性值 行走速率
    Point _velocity;//移动速度
    float _warningRange;//警戒范围
    BoundingBox _hitBox;//精灵的身体
    BoundingBox _attackBox;//精灵的手
    bool isLeft;//true 左  flase右
    string _frameEvent;//帧事件
    string _frameParam;//参数
   
    int m_avatarPosY;
    int m_avatarPosX;
    int m_initAvatarPosX;
    bool isCamreIn;//拉动了摄像机
    bool _isAbleJumpAttack;//是否可以跳击
    bool isShowBlood;//是否显示血条
    int _enterWay;
    
    float _followMainHeroDistance;//跟随主将距离
    double _nextDecisionTime;//下次决择时间
    
    bool isBossShadow;//是否显示boss阴影
    
    bool isNewEnter;//是否是第一次进入场景
    int aiID;//DictAiSkillCastManager 的aiID
protected:
    bool isAblePlayAction();//是否可以被打断当前动作
    void loopAction(int startFrameIndex);
    void onLoopActionEnd();
    void onShieldAttack(float dt);//护盾攻击
protected:
    CC_SYNTHESIZE_RETAIN(DictAvatarProp*, _avatarProp, AvatarProp);//基础属性
    CC_SYNTHESIZE_RETAIN(DictAvatarProp*, _baseAvatarProp, BaseAvatarProp);//基础属性
   
    string _weaponName;
    string _chanedBoneName;//已经换过的骨骼名字
    string m_resourceName;//资源名字
    string _avatarName;//
    MovementEventType movementType;//
    Node* buffContainer;//buff层
    Node* buffIconContainer;
    Node* bloodContainer;//伤害数字层
    bool m_isHolding;//是否一直按着摇杆

    int m_uid;//唯一对象id
    float m_jumpAttackTime;//跳击时间
    bool _isPause;//是否暂停状态
    bool _isInRoad;//是否在地上
    bool _isDashing;//是否冲撞中
    int _jumpHeight;//跳跃高度
    int _knockFlyCount;//击飞次数
    long _blockStartTime;//开始格档时间
    long _acitonLoopTime;//动作开始循环时间
    double _shieldBlood;//护盾血量
     ActionState _actionState;
    ActionState _preActionState;//上一动作
    map<int,long long>* skillCDMap;
    Map<int,BuffEffectData*>* buffListMap;//buff列表
    
    Color3B originColor;//原始颜色
    EventListenerTouchOneByOne* m_eventDispatcher;
    ProgressTimer* m_bloodPt;
    
 
protected:
    
    Sequence* flyAction;//击飞动作
    Sequence* deadAction;//死亡动作
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
public:
    ccMenuCallback m_actionFinishedCallBack;//动作完成回调
    ccMenuCallback m_actionAttackCallBack;//判断攻击回调
    ccMenuCallback m_touchCallBack;//点击回调
protected:
    int TAG_SHADOWE;
    int TAG_EFFECT;
    int TAG_BUFFEFFECT;
    int TAG_KNOCKBACK_ACTION;
    int TAG_NAME;
    int TAG_BLOCKACTION;
    int TAG_BLOCKDELAY;
    int TAG_BLOOD;
    int TAG_SHIELD_BLOOD;//护盾血量
    
    
};

#endif /* defined(__FightPass__Avatar__) */
