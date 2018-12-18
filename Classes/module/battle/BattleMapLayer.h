//
//  BattleMapLayer.h
//  FightPass
//
//  Created by zhangxiaobin on 15/5/24.
//
//

#ifndef __FightPass__BattleMapLayer__
#define __FightPass__BattleMapLayer__

#include "../BaseLayer.h"
#include "../../avatar/hero/Hero.h"
#include "../../avatar/monster/Monster.h"
#include "simplePad/SimplePad.h"
#include "../../common/TouchSprite/Button.h"
#include "../../commonData/dictData/DictHero/DictHeroManager.h"
#include "data/MapDataManager.h"
#include "skillEffectLayer/SkillEffectLayer.h"
#include "../../commonData/dictData/DictStageBattleMonster/DictStageBattleMonsterManager.h"
#include "../../commonData/dictData/DictMusouBattleMonster/DictMusouBattleMonsterManager.h"
#include "../../commonData/dictData/DictBattleReborn/DictBattleRebornManager.h"
#include "../../commonData/dictData/DictStageBattle/DictStageBattleManager.h"
#include "../../commonData/dictData/DictMusouBattle/DictMusouBattleManager.h"
#include "../../commonData/dictData/DictLegendBattle/DictLegendBattleManager.h"
#include "../../common/Dialog/Dialog.h"
#include "action/Shake.h"
#include "action/CameraIn.h"
#include "../../net/bytestream.h"
#define BG_RATE .03
#define MID_RATE .6
#define NEAR_RATE 1
#define CLOSE_RATE 1

USING_NS_CC;

class BattleMapLayer:public BaseLayer,public SimplePadDelegate
{
public:
    BattleMapLayer();
    ~BattleMapLayer();
    virtual bool init(int battleID,Vector<DictAvatarProp*>* heroPropList);
    static BattleMapLayer* create(int battleID,Vector<DictAvatarProp*>* heroPropList);
    
    virtual void didChangeDirectorTo(SimplePad* simplepad,Point direction);
    virtual void isHoldingDirector(SimplePad* simplepad,Point direction);
    virtual void simplePadTouchEnded(SimplePad* simplepad);
public:
    void onAttack();//攻击
    void onJump();//跳
    void onSkill(int buttonType);//必杀技
    void onSkill4Over();
    void onProtected();
    void onReleaseProtected();
    void pauseOtherAvatar(Avatar* selfAvatar);//暂停其他人物的动作
    void resumeOtherAvatar();
    void goonAvatarAction();//继续人物动作
    void onShowOtherAvatar(Avatar* selfAvatar);
    void onHideOtherAvatar(Avatar* selfAvatar);
    
    void changeMainHero(Hero* hero);//更换主将
    void onTargetFlashMove(Avatar* target);
    void onFocusToEnemy(Avatar* target);
    void onFocusToSelf(Avatar* target);
    void onFocusUp(Avatar* target);
    void onFocusDown(Avatar* target);
    void onFocusReset(Avatar* target);
    void onChangeSkillBg(Avatar* target);
    void onSkillBgFrame(Bone *bone, const std::string& evt, int origin, int current);
    void onSkillBgUpDown(int offY);
    void onReleaseBigSkill(Avatar* target);
    void onMonsterDead(Avatar* target);
    void onHeroDead(Hero* hero);
    void onHeroRemove(Hero* hero);
    void onHeroRemoveDelay(Hero* hero);
    void onRePlay();
    void onEatBlood();
    void onHeroBloodReset();
    void playShakeScreen();
    Hero* getMainHero();
    inline bool avatarIsHurt(Avatar* target,SkillAttackData* attackData); //是否被击中
    inline bool avatarIsBomb(Avatar* target,SkillAttackData* attackData);//是否被爆点击中
    inline void onMonsterHurt(Avatar* monster,SkillAttackData* attackData,float damage); //怪物被击中
    inline void onHeroHurt(Hero* hero,SkillAttackData* attackData,float damage);//英雄被击中
    
    
protected:

    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    
    void update(float dt);
    
    void onMsgProcess(EventCustom* message);
    void onAvatarPostionMove(EventCustom* message);
    void playAvatarSound(EventCustom* message);
    void onSortBornMonster(EventCustom* msg = NULL);
    void onSummonedHelper(EventCustom* msg = NULL);// 昭唤技能
    void createSummonHero(Avatar* caller,Point startPostion,int heroDictID,int row,int colum,int lifetime);//创建援助
    void showMonsterDrops(ByteStream* bytestream);
protected:
    void delayBattleWin(float dt);
    void onBattleStart();
    void onBattleOver();
    void pauseBattle();
    void gotoBattle(EventCustom* msg = NULL);
    void showGoEffect();//显示go
    void showNextWaveMonsters();//显示下一波怪
    void showNextBlockMonsters();//显示下一区域怪物
    inline bool hasDelayMonster();//是否有延时怪
    void showDelayMonster(float dt = 0);//显示延时出现的怪物
    void showMonster(Monster* monster);
    void setBackground();
    void setPlayerBorn();//英雄出生点
    void onPlayerPosition(Ref* target);//英雄就位
    void setMonsterBorn();//怪物出生点
    void setTestMonsterBorn();//测试怪出生点
    void setSceneEffectBorn();//场景特效出生点
    void loadSceneEffect(TMXTiledMap* mapLayer);
    void loadResource();
    void onDataLoaded(float percent);
    void onSetMonsterBorn();
    void clearResourcePerson();
    
    void onAvatarUseSkill(Avatar* target,int skillID,int team);
    void onHeroAttack(SkillAttackData* attackData);//英雄攻击
    void onMonsterAttack(SkillAttackData* attackData);//怪物攻击
    
    void onAttackSelf(SkillAttackData* attackData);//攻击自身

    void onHeroAttackMinBlood(SkillAttackData* attackData);//攻击最小血量的怪
    void onMonsterAttackMinBlood(SkillAttackData* attackData);//攻击最小血量的英雄
 
    
    void onEnvironmentMonsterDead(Monster* monster);
    Point getTargetPointByTarget(Avatar* target,int gridNum,bool isLeft);//得到目标格坐标
    void attack1();//攻击1
    void attack2();//攻击2
    void attack3();//攻击3
    void attack4();//攻击4
    void attack5();//攻击5
    void onJumpAttack();//跳击
    
    void flySkillName(Avatar* target);
    void playBigSkill(Avatar* target);
    void onAttackTimer();
    void startTimeing(float dt);
    void clearAttackCount(float dt);
    
    void onHeroActionFinished(Ref* hero);
    void onHeroSkillAttackCallBack(Ref* hero);//技能攻击
    void onMonsterAttackCallBack(Ref* monster);
    
    void onSkillAttackCallBack(EventCustom* event);
    void onSkillAttack(int skillID);
    void setNextMainHero();//设置下一个主将
   
    void onHeroArrived();//英雄到达停止点
    void onNextBlockArea(float toPosX);//进入下一区域
    void onNextBlockEnd(float toPosX);
    
    inline void isMonsterInView();
    inline void setViewPointCenter(float dt,Avatar* target);//设置地图位置
    inline void updateShipView(float dt,Avatar* target);//更新船体视图
  
    void onShakeEnd();
    
    void onTransferPoint(Point gridPoint);//传送到下一个点
    
    void onHeroWin();
    void showBattleWin();
    void onHeroReBorn(EventCustom* msg);
    void resetUesrControl();//恢复玩家操作
    void onHeroRebornCancel(EventCustom* msg);
    void showRebornDialog();//显示复活弹框
    void onSkillBuff(Avatar* hurtAvatar,SkillAttackData* attackData,float damage,int buffID);//技能buff效果
    
    void showBornEffect(Point cp);
    void onEffectCompleted(Armature *armature, MovementEventType movementType, const std::string& movementId);
    void onUpdateMainHero();
    void onHeroAddAngry(Hero* hero);
    void showBossComeWarning(Monster* monster);//boss警告
    inline bool hasBornCommonMonster();//是否有未死普通怪
    inline bool hasCommonMonster();//场景中是否还有普通怪
    void delayBroadMsg();
    void onDropItemCollect(Node* target);
    void onHeroDashCompleted(Hero* hero);
    float getMonsterDashTime(Monster* monster);
    float getHeroDashTime(Hero* hero);
    void onDashClick();
    inline int getLengendHurtRate(int heroID);//名将传伤害倍数
    void onCountDownOver(EventCustom* msg);//倒计时结束
    void onAvatarPassSkill(Avatar* target);//使用被动技能
    void onBossDead(Avatar* boss);
public:
     int m_bloodBottle;//血瓶数量
private:
    PopupLoading* popUpLoading;
    int m_stageBattleID;//战斗id
    Node* m_mapContainer;//地图容器
    Sprite* m_backGround;//背景层
    TMXTiledMap* midLayer;  //1层
    TMXTiledMap* nearLayer;//2层
    TMXTiledMap* closeLayer;//3层
    int m_loaded;
    Node* bigSkillLayer;//大招特效层
//    Node* fightObjLayer;//战斗对象层
    Node* fightObjLayer;//战斗对象层
    SkillEffectLayer* skillEffectLayer;// 技能特效层
    Node* sceneEffecdtLayer;//场景特效层

    Sequence* shakeAction;
    Hero* m_Hero;
    Vector<DictAvatarProp*>* _heroPropList;
    __Set* _monsterList;//怪物列表
    Vector<Hero*>* _heroList;//英雄列表
    Vector<Avatar*>* _bornMonsterList;//出生了的怪物列表
    __Set* _blockMonsterList;//阻挡怪物列表
    Vector<Armature*>* _sceneEffecctList;//场景特效
    Vector<Armature*>* _midLayerEffectList;//mid层场景特效
    Map<string,__Bool*> loadingList;
    float _mapWidth;
    float _mapHeight;
    float m_scaleX;
    float bigSkillTime;//连携技能时间
    int m_attackClickCount;//攻击按钮点击次数
   
    int m_buyBloodCount;//购买血的次数、
    int m_totalBuyBloodCount;//共可以购买血的次数
    int m_totalBloodBottle;
    float blockEndPos;//地图块结束位置
    bool m_isbigSkilling;//是否在大招中
    bool m_isInTimeing;//是否计时中。。。。
    bool isArrivingEnd;//是否到头了
    
    Size m_winSize;//屏幕大小
    Point screenViewCenter;//当前地图的屏幕中心
    int MAP_TILED_WIDTH ;
    int MAP_TILED_HEIGHT;
    BattleMode _battleMode;//当前战斗形式
    int _tureWaves;//当前波次
    bool _hasNextWave;
    float m_totalHealth;//总血量
    float m_curHealth;//当前血量
    float m_starProgress;//星级进度
    bool screenIsMoving;
    int m_mainHeroID;
    bool heroIsBorn;//英雄是否复活
    bool bossComeIsWarning;//是否预警了
    CC_SYNTHESIZE_RETAIN(DictBattleReborn*,_battleReborn, BattleReborn);
    int m_nowReviceCount;//当前复活次数
    int m_resourceTotal;
    Point rewardMonsterPoint;//奖励怪坐标
    int dropCoin;//掉落铜币
    long m_startTime;//开始时间
    int bossBlood;
    long m_leftTime;//秒
    long m_victoryTime;//秒 胜利时间 撑过这段时间后就胜利
    bool isTimeWinMode;//是否是时间模式，支撑多长时间后就算胜利
    Vector<Node*>* dropList;//掉落物品列表
    bool m_isLeft;
    float _frameInit;
private:
    int TAG_BIGSKILL_EFFECTBG;//
    int TAG_BORNEFFECT;
    int TAG_GOEFFECT;
    
    
};

#endif /* defined(__FightPass__BattleMapLayer__) */
