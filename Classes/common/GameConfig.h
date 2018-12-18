//
//  GameConfig.h
//
//游戏配置类用于一些宏定义
//  Created by mac on 14-5-7.
//
//
#ifndef __GAMECONFIG_H__
#define __GAMECONFIG_H__
#define VERSION_FLAG  "EMINDSOFT_QXSG_VERSION"
#define YUNWA_APPID 1000157
#define HEART_INTERVAL		   60
#define SEX_GIRL_FROMINDEX 100        //小于此数的为男性，大于等于此数的为女性

#define SEX_WOMEN 2
#define SEX_MAN 1

//玩家角色属性
typedef enum _RoleBaseAttrib
{

    RoleAttrib_EXP = 1,//经验
    RoleAttrib_GOLD = 2,//元宝
    RoleAttrib_COIN = 3,//铜钱
    RoleAttrib_POWER = 4,//体力
    RoleAttrib_GLORY = 5,//荣誉
    RoleAttrib_Honor = 6,//军功
    RoleAttrib_Level = 7,//等级
    RoleAttrib_VIPLevel = 8,//vip等级
    RoleAttrib_VIPExp = 9,//vip经验
    RoleAttrib_CurHeroCount = 10,// 当前武将数量
    RoleAttrib_HeroCountLimt = 11,// 武将数量上限
    RoleAttrib_CurEquipCount = 12,// 当前装备数量
    RoleAttrib_EquipCountLimt = 13// 装备数量上限
    
}RoleBaseAttrib;

typedef enum _RechargeType
{
    kRecharge_type_gold = 1,//元宝充值
    kRecharge_type_monthCard = 2,//月卡充值
    kRecharge_type_other = 3//其他充值 玩家自定义
    
}RechargeType;


static const int SCENE_TAG_INIT = 0;
static const int SCENE_TAG_LOADING = 1;
static const int SCENE_TAG_MAINUI = 2;
static const int SCENE_TAG_BATTLE = 3;
static const int SCENE_TAG_CHAPTER = 4;
static const int SCENE_TAG_LINEUP = 5;//阵容层
static const int SCENE_TAG_SETTLE = 6;//结算层
static const int SCENE_TAG_SWEEP = 7;//扫荡层
static const int SCENE_TAG_EQUIPMENT = 8;
static const int SCENE_TAG_GENERALS = 9;//所属层
static const int SCENE_TAG_GENERALSCARD=10;//所属第一级其他层
static const int SCENE_TAG_MARKET=11;
static const int SCENE_TAG_TASK=12;//任务层
static const int SCENE_TAG_DAILYTASK = 13;//日常任务
static const int SCENE_TASK_REWARDTASK = 14;//悬賞任务
static const int SCENE_TAG_GOTOBATTLE = 15;//征战
static const int SCENE_TAG_CHOOSEEQUIP=16;//所属第二级其他层
static const int SCENE_TAG_ZHENRONGHEROLIST=17;//阵容武将列表
static const int SCENE_TAG_REBORN = 18;//复活提示框
static const int SCENE_TAG_GETPATH=19;//获取路径层
static const int SCENE_TAG_MUSOU = 20;//三国无双界面
static const int SCENE_TAG_GENERALS_LATER = 21;//所属层书信
static const int SCENE_TAG_GENERALS_EQUIP = 22;//所属层装备
static const int SCENE_TAG_GENERALS_MATERIAL = 23;//所属层材料
static const int SCENE_TAG_GENERALS_PROPS = 24;//所属层道具
static const int SCENE_TAG_GENERALS_STRONG=25;//所属道具强化；
static const int SCENE_TAG_RANK=26;//名战役排名
static const int SCENE_TAG_FAMOUSE = 27;//名将传
static const int SCENE_TAG_BOSSCOME = 28;//名将来袭
static const int SCENE_TAG_ARENA = 29;//竞技场

static const int LAYER_LOADING = 100;//正在加载
static const int LAYER_DIALOG = 101;//弹 出框
static const int LAYER_SERVER_LOADING = 102;//通信中。。。
static const int LAYER_ENTER_GAME = 103;//进入游戏
static const int LAYER_INPUT_UESRNAME = 104;//登陆输入框
static const int LAYER_USER_POPUP = 105;//开启弹出框
//场景层级
static const int SCENE_LAYER_ZORDER = 100;//模块层
static const int SCENE_TWOLAYER_ZORDER = 200;//二级弹框
static const int SCENE_CHAT_ZORDER = 400;//聊天层
static const int SCENE_POPLAYER_ZORDER = 500;//提示框
static const int SCENE_NOTICE_ZORDER = 600;//提示层

static const int SCENE_LAYERLOADING_ZORDER = 3000;//资源加载loading层。挡住所有界面不让操作

//场景层级tag
static const int SCENE_MODULAR_TAG = 100;//模块层起始tag + 功能id


#define SKILL1_OPEN_QUALITY 1 //技能1开放品质
#define SKILL2_OPEN_QUALITY 2 //技能2开放品质
#define SKILL3_OPEN_QUALITY 4 //技能3开放品质
//背景音乐文件名
#define MUSIC_MAINSCENE  "mainscene" //大厅背景音乐
#define MUSIC_BATTLE  "music_battle" //普通战斗
#define MUSIC_STAGE "stage"//关卡战斗
#define MUSIC_LOGIN "login"

//音效文件名
#define EFFECT_ENTER_SCENE "enter"
#define EFFECT_RELIVE "enter"
#define EFFECT_NUMBER "number"
#define EFFECT_JUMP "jump"
#define EFFECT_CLICK "effect_click"//点击按钮
#define EFFECT_REBORN "reborn" // 重生
#define EFFECT_STAR "star"
#define EFFECT_LOSE "lose"// 失败
#define EFFECT_WIN "effect_win"//胜利
#define EFFECT_KEEPOFF "gedang"//格档
#define EFFECT_QIANGHUA_SUC "qianghuachenggong"      //强化成功
#define EFFECT_QIANGHUA_FAILED "qianghuashibai"   //强化失败
#define EFFECT_UI_OPEN "open_UI"   //打开UI
#define EFFECT_UI_CLOSE "close_UI"   //关闭UI
#define EFFECT_AWAKEN_SU "awaken"     //觉醒成功
#define EFFECT_EQUIP_UP "equip_Up"     //装备升级
#define EFFECT_EQUIP_FORGE "equip_Forge"     //装备熔炼
#define EFFECT_GET_PAGE "get_Page"     //领取页面
#define EFFECT_HERO_EXPERIENCE "experience"     //武将历练

#define EFFECT_FUNCTIONOPEN "functionOpen1" //功能开启
#define EFFECT_UPLV "levelup" //主公升级

//luckReward1.mp3
//talentUp2.mp3
//functionOpen1.mp3
//getHero1.mp3
//player_lv_up.mp3
//导航栏按钮标志

#define MENUBAR_SUPREMACY 0  //霸业
#define MENUBAR_STAGEBATTLE 1 //关卡征战

#define MENUBAR_BUZHEN 2 //布阵

#define MENUBAR_BAG 5   //背包

#define MENU_MARKET 7//集市
#define MENUBAR_BACKCITY 8//回城
#define LAYER_WUJIANG_CARD 9//武将卡牌
#define LAYER_WUJIANG_BASE 10//武将
#define LAYER_WUJIANG_PROPERTY 11//武将属性
#define LAYER_WUJIANG_SKILL 12//武将技能
#define LAYER_WUJIANG_EXPERIENCE 13//武将历练
#define LAYER_WUJIANG_AWAKE 14//武将觉醒
#define MENUBAR_TASK 14  //任务
#define MENUBAR_ACTIVE 15 //活动
#define LAYER_EQUIP_STRONG 16//装备强化
#define LAYER_EQUIP_SMELT 17//装备熔炼
#define LAYER_MARKET_JUXIAN 18//聚贤
#define LAYER_MARKET_PAIMAI 19//拍卖
#define LAYER_ZHENRONG 20//阵容
#define LAYER_WUJIANG 21//武将
#define LAYER_EQUIP 22//装备
#define LAYER_WEAL 23//福利
#define LAYER_PRAY 24//祈福
#define LAYER_LIMIT 25//限时
#define LAYER_FIGHT 26//竞技场

#define BTN_BOOK 100//书卷伸缩按钮
#define COLOR_ORANGE 0xFF7B00
#define COLOR_RICE_YELLOW 0xffd68e            

#define COLOR_BUTTON_WHITE 0x004a23 //按钮白
#define COLOR_DEEP_RED 0x9d0202  //深红
#define COLOR_LOW_RED 0x9f0000  //小红
#define COLOR_DEEP_ORANGEYELLOW 0xe07434 //深桔黄
#define COLOR_LOW_BLUE 0x036188 //浅蓝
#define COLOR_PINK 0xffcbbb//粉色
#define COLOR_BROWN 0x412f24// 棕色
#define COLOR_BROWN_WORD 0x411a00  //棕字体
#define COLOR_MILK_WHITE 0xfae3bf     //乳白
#define COLOR_GREEN_WORD 0x00ff96     //绿色文字
#define COLOR_DARK_GREEN 0x4cff00//深绿
#define COLOR_BROWN_YELLOW 0xd78142   //棕黄
#define COLOR_ORANGE_YELLOW 0xFFE507//橘黄
#define COLOR_BROWN_WHITE 0xffe1c9//棕白
#define COLOR_GOLDEN_YELLOW 0xfdfdbd //金黄
#define COLOR_BROWN_BLACK  0x5d2300 //棕黑色
#define COLOR_BROWM_WRITE  0xe0c750 //
#define COLOR_LIGHT_RED  0xff6000 //浅红
#define COLOR_BLACK_BROWN  0x512200 //棕黑色
#define COLOR_WRITE_YELLOW  0xfffbcd //
#define COLOR_WRITE_PINK  0xff78c7 //粉紫色
#define COLOR_BROWN_HESE  0x8a9a7e //灰褐色
#define COLOR_YELLOW_ORANGEYELLOW  0xfa7511 //橘黄色
#define COLOR_WRITE_DEEP  0xfffdd5 //白黄色
#define COLOR_BRITE_DEEP  0x552c00 //色
#define COLOR_DEEP_BROWN  0x5d0018 //深棕色
#define COLOR_GREEN_BLUE  0x8fe0ca //蓝绿色
#define COLOR_GOLD_LIGHT  0xfffc00 //金色
#define COLOR_NOTIC_GREEN  0xf5ea07 //公告标题黄


//#define COLOR_GREEN 0x6DDD57//绿色
#define COLOR_HERLIST_BLACK 0x1d1900//武将列表黑色
#define COLOR_HEAD_WHITE 0xfff1bb//头像等级白
#define COLOR_KARMA_FLOUR 0xeb4cc0//粉色
#define COLOR_SKILL_LIGHT_YELLOW 0xfff3bb//技能浅黄色
#define COLOR_BLUE_FLOUR 0x2fe0d1//蓝色
#define COLOR_YELLOW_FLOUR 0xfff1d0//浅黄
#define COLOR_NORMAL_YELLOW 0xffea00//黄色
#define COLOR_YELLOW_WHITE 0xf1d391//黄白
#define COLOR_SERVERNAME_WHITE 0xfffbe8//进入游戏服务器名字的白色
#define COLOR_NPC_NAME 0xd4fcff//npc名字颜色
#define COLOR_WHITE_YELLOW 0xffebc5//白黄




////////////////errorid////////////////////
#define ERROR_HTTP_NODATA "1"
#define ERROR_HTTP_FAILED "2"
#define ERROR_SOCKET_FAILED "3"


#endif