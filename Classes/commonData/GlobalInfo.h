//
//  GlobalInfo.h
//
//
//  Created by zxb on 14-5-27.
//
//

#ifndef __TwoMahjong__GlobalInfo__
#define __TwoMahjong__GlobalInfo__


#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "RoleData.h"
typedef enum _BattleMode
{
    kBattleModeHeroRun = 1,//英雄跑酷模式，地图根据英雄移动
    kBattleModeMapRun,     //跑步机模式，地图推动英雄移动
    kBattleModeUser,        //玩家模式，玩家控制英雄移动
    kBattleModeShip,          //行船模式，玩家只在船内移动，前景不动。中景移动
} BattleMode;
typedef enum _StageMode
{//关卡模式
    kStageModeCommon = 1,//普通
    kStageModeBest = 2//精英模式
}StageMode;

typedef enum _BattleType
{
    kBattleType_None = 0,
    kBattleType_MingZhanYi = 1,//名战役
    kBattleTYPe_SanGuoWushuan = 2,//三国无双
    kBattleType_MingJiangZhuan = 3,//名将传
    kBattleType_LoginBattle = 4,//登陆战斗，客户端自己配的一场
    kBattleType_ArenaBattle = 5,//竞技场
    kBattleType_TestBattle = 6//战斗测试
} BattleType;

class GlobalInfo
{
public:
    GlobalInfo();
    ~GlobalInfo();
    int battleTimeScale;//关卡加速倍数
    bool isSdkMode;//是否是调度模式
    bool isNativeMode;//是否是本地调试
    float screenScaleX;
    float screenScaleY;
    int map_tiled_width;//地图块宽
    int map_tiled_height;//地图块高
    static GlobalInfo* getInstance();
    static void destroyInstance();//删除单例
    int curHeroCount;//当前武将数量
    int maxHeroCount;//总武将数量
    int curEquipCount;//当前装备数量
    int equipCountLimit;//最大装备数量上限
    int odSocketErr;
   
    bool isFirstEnterMainScene;// 是否第一次进入主界面 不是第一次注册
    bool isNewEnterGame;//是否是新登陆的游戏 是否第一次进入游戏
    std::vector<int> stageBattleList;
    bool isShowReconnect;
    bool isReceivedDataEnabled;//是否接受协议、、用于根据一些事件，完成后才继续解析协议
    string gameID;
    string addressIP;
    int port;
    string nowServerID;//当前选择的服务器id
    string nowServerName;//当前服务器名字
    string uid;
    string token;
    string sessionID;
    string gameSessionId;//第二次连接传入次sessionId, 无需passport验证
    string version;
    bool isUpdateVersion;//是否更新版本中。
    bool chatChannelIsOk;//聊天频道是否成功返回
    std::vector<string> domainList;//域名列表
    std::vector<string> resourceDomainList;//资源更新域名列表
    string _domainURL;//域名服务器
    string loginPort;//登陆端口号
    string subChannelActive;//子渠道激活
    string subChannel;//子渠道编号
    string resourceDomainURL;//资源更新域名
    string gamePackUrl;//游戏包下载地址
    bool isAutoDownClient;//是否自动更新客户端
    
    string deviceUUID;//设备id
   
    int vipId;//vip编号
    int vipLevel;//vip等级
    float vipExp;//vip经验
    double bodyPower;//玩家体力
    double bodyPowerMax;//最大体力
    double userCopper;//玩家铜币
    double userGold;//玩家元宝
    int bloodBottle;//血瓶数量
    int raidsCard;//扫荡令个数
    int firstRechargeStatus;//首充图标状态 1、可充值   2、可领取   3、已领取
    int sevendayActivity;//七日图标状态
    
    RoleData* gameRole;
    Vector<RoleData*>* mainSceneHeroList;//主场景武将
    void setIsPlayBackMusic(bool enabled);//是否播放背景音乐
    bool getIsPlayBackMusic();
    
    void setIsPlayEffectMusic(bool enabled);
    bool getIsPlayEffectMusic();//是否播放音效
    
    int chapterOpenStage;//进入章节界面默认打开的关卡界面
    int taskInStageBattle;//任务关卡
    int selectedStageBattle;//默认选中哪个关卡战斗
    //0-绿色，1-黄色，2-红色
    int addictedLevel;//防沉迷等级 0，没有沉迷 ，1，轻度沉迷 2，重度沉迷 
    string addictedMsg;//防沉迷提示
    float m_mapScale;
    float m_avatarScale;
    BattleMode battleMode;
    BattleType battleType;
    StageMode stageMode;
    bool isPlayedGuideBattle;//是否做过了新手战斗
    bool isShowStoryTalk;//是否显示剧情动画
    bool isInNewVillage;//是否在新手村
    bool isShowGuide;//是否显示新手引导
    bool isGuiding;//是否在引导中。
    bool isEnterLogin;//是否进入了登陆界面
    bool isDebug;
    string sdkURL;
    string noSdkUrl;
    string serverListURL;
    string dictDataVersion;
    //初始化红点变量
    string dotStr;
    void initDotList(string value);
    const char*  dotList;
    void initIs();
    float getMapScaleValue();//得到屏幕缩放比例值
    int famouseBossID;//名将传bossID
   
    int famouseBossLevel;//名将传boss等级
    int famousePeroid;//名将传期数
    string famouseName;//名将传名称
    int famouseBossBlood;//名将传boss血量
    long famouseLeftSeconds;//名将传boss剩余秒数
    int famouseChallengeCount;//名将传挑战次数
    int luckyLeftTime;//祈福剩余时间(秒）
private:
    static GlobalInfo* _instance;
};
#endif /* defined(__TwoMahjong__GlobalInfo__) */
