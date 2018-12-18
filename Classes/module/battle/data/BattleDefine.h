//
//  BattleDefine.h
//  SuiTang
//
//  Created by mac on 14-6-9.
//
//

#ifndef __FightPass__BattleDefine__
#define __FightPass__BattleDefine__


enum __BattleTeam
{
    TEAM_TYPE_SELF = 1,//己方
    TEAM_TYPE_OTHER = 2//对方
};

typedef enum _MonsterEnterWay
{
    kEnterWayCommon = 1,//直接出现
    kEnterWayFlash = 2,//陷阱出现
    kEnterWayDelay = 3// 延时出现
}EnterWayState;
//战斗结果 1，胜利，2失败
enum FightResult
{
    RESULT_WIN = 1,
    RESULT_LOSE = 2
};
#define AVATAR_SPEED_SCALE 0.35f //人物慢动作

#define BIGSKILL_SKILLBG_EFFECT1 "beijingtiao"
#define BIGSKILL_SKILLBG_EFFECT2 "tiankongbeijing"

#define BOSS_BORN_EFFECT "bosschuchang"//boss出生特效
#define BOSS_COME_EFFECT "qiangdilaixi"//强敌来袭
#define BOSS_DEAD_EFFECT "huacai"
#define MONSTER_BORN_EFFECT "qunxiaoguaichuchang" //小怪出生特效

#define BIGSKILL_BTN_EFFECTBACK "dazhaoqiuhou" //大招按钮特效背面
#define BIGSKILL_BTN_EFFECTFRONT "dazhaoqiuqian" //大招按钮特效前面
#define AUTOFIGHT_EFFECT "gongnengxuanzhongkuang"//自动战斗特效

#define AVATAR_SHADOWE_MAINHERO "dangqianrenwudi"
#define AVATAR_SHADOWE_BOSS "hongserenwudiquan"
#define AVATAR_DEAD_WARNING "siwangjingshi" //死亡警示
#define AVATAR_BLOOD_EFFECT "xuepingdonghua"//血瓶加血提示
#define AVATAR_CHANGE_EVENT "change"
#define SKILL_ATTACK_EVENT "FrameAttack"//打出技能特效攻击
#define AVATAR_SLOWMONTION "slowMotion"
#define AVATAR_RESET_SLOWMONTION "resetSlowMotion"
#define AVATAR_ATTACK_EVENT "Attack"  //人物触发的attack
#define AVATAR_SHAKE_EVENT "shake"  //震屏
#define AVATAR_SOUND_EVENT "sound" //攻击音效
#define AVATAR_POSITIONMOVE_EVENT "postionMove"//位移
#define AVATAR_STOP_ACTION "stopAction"//定身半秒
#define AVATAR_STOP_DASH "stopDash"//停止冲撞
#define AVATAR_FLASHMOVE_EVENT "flashMove"//触发瞬移技能
#define AVATAR_HITFLY_EVENT "hitFly" //击飞事件
#define AVATAR_HIDE_OTHERAVATAR "hideOtherAvatar"//隐藏其他人物
#define AVATAR_SHOW_OTHERAVATAR "showOhterAvatar"//显示其他人物

#define AVATAR_CAMERA_MOVESELF "cameraMoveSelf"//摄像机移动到自己
#define AVATAR_CAMERA_MOVEENEMY "cameraMoveEnemy"//摄像机移动到敌方
#define AVATAR_CAMERA_MOVEUP "cameraMoveUp"//摄像机上移
#define AVATAR_CAMERA_MOVEDOWN "cameraMoveDown"//摄像机下移
#define AVATR_CAMERA_SCALE "cameraScale" //镜头拉近事件
#define BATTLE_SKILLBG_MOVE "BattleSkillMove"//技能背景偏移
#define AVATAR_CALL_HEALPER "callHealper"//昭唤助手
#define AVATAR_CHANGE_SKILLBG "changeBJ"
#define AVATAR_ACTION_LOOP "actionLoop"


#endif /* defined(__SuiTang__BattleDefine__) */
