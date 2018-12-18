//
//  BattleLayer.h
//  FightPass
//
//  Created by zhangxiaobin on 15/5/23.
//
//

#ifndef __FightPass__BattleLayer__
#define __FightPass__BattleLayer__

#include "../BaseLayer.h"
#include "BattleMapLayer.h"
#include "simplePad/SimplePad.h"
#include "battleUI/HeroHeadListLayer.h"
#include "battleUI/BossBloodManager.h"
#include "../../net/bytestream.h"
class BattleScene:public BaseLayer
{
public:
    BattleScene();
    ~BattleScene();
    virtual bool init(ByteStream* byteStream);
    static BattleScene* create(ByteStream* byteStream);
    static Scene* createScene(ByteStream* byteStream,int fromScene);
    
    //显示控制摇杆
    void showControlBar(EventCustom* event = NULL);
private:
    void parseMsg(ByteStream* byteStream);
    void setMapLayer();
    void setMaskLayer();//遮罩
    void setControlBar();//设置摇杆
    void setControlButton();//技能按钮
    void setheadListLayer();//设置头像层
    void createEnvirEffects();
    void setBattleName();
    void onControlBtnClick(Ref* pSender);
    void onControlBtnRelease(Ref* pSender);
    void showFullScreenSkill(EventCustom* msg);//全屏技能特效，位于场景最高层
    void showBossComeEffect(EventCustom* msg);//boss来袭提示
    void onCameraIn(EventCustom* msg);
    void onCameraReset(EventCustom* msg);
    void onSkill1Cd(EventCustom* msg);
    void onSkill2Cd(EventCustom* msg);
    void onSkill3Cd(EventCustom* msg);
    void onSkill4Cd(EventCustom* msg);
    void onSkill5Cd(EventCustom* msg);
    void onChangeMainHero(EventCustom* msg);
    void onTargetFlashMove(EventCustom* msg);
    void onSkill4Over(EventCustom* msg);
    void pauseAvatarAction(EventCustom* msg);
    void resetAvatarAction(EventCustom* msg);
    void stopActionMovent(EventCustom* msg);//定身半秒钟
    void onShakeScreen(EventCustom* msg);
    void onCameraSelf(EventCustom* msg);//摄像机移动到自己身上
    void onCameraEnemy(EventCustom* msg);//摄像机移动到敌方身上
    void onCameraScale(EventCustom* msg);//镜头缩放
   
    void onCameraMoveUp(EventCustom* msg);//摄像机上移
    void onCameraMoveDown(EventCustom* msg);//摄像机下移
    
    void hideSkyEffect(EventCustom* msg);//隐藏阳光层大招的时候隐藏
    void showSkyEffect(EventCustom* msg);//隐藏阳光层大招的时候隐藏
    void onChangeBigSkillBg(EventCustom* msg);
    void onReleaseBigSkill(EventCustom* msg);//释放大招
    void onShowOtherAvatar(EventCustom* msg);
    void onHideOtherAvatar(EventCustom* msg);
    void onMonsterDead(EventCustom* msg);
    void onHeroDead(EventCustom* msg);
    void onHeroRemove(EventCustom* msg);
    void onQuitBattle(EventCustom* msg);
    void onReplayBattle(EventCustom* msg);
    
    void showHealthWarning(EventCustom* msg);
    void hideHealthWarning(EventCustom* msg);
    void onBattleEatBloodBottle(EventCustom* msg);
    
    void setPauseBtn();
    void onPauseClick(Ref* pSender);
    void setAutoFightBtn();
    void onAutoFightClick(Ref* pSender);
    void onFamouseTouch();
    void setBloodBottle();
    void onBottleClick(Node* pSender);
    void updateBottleCount();
    
protected:
    void backScene();
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();

    virtual void addEventListener();
    virtual void removeEventListener();
protected:
    Vector<DictAvatarProp*>* heroPropList;
    BattleMapLayer* m_mapLayer;
    SimplePad* m_simplePad;
    long long m_lastAttackTime;//上次按攻击按钮的时间
    int m_battleID;
 
private:
    int TAG_CONTROLBUTTON;
    int TAG_FULLEFFECT;
    int TAG_BATTLENAME;
    int TAG_SKYEFFECT;
    int TAG_HEALTHWARNING;
    int TAG_BOSS_COME;
    int TAG_PAUSEBTN;
    int TAG_AUTOBTN;
    int TAG_BOTTLE;
    int TAG_BOTTLELABEL;
    int TAG_AUTOEFFECT;
};

#endif /* defined(__FightPass__BattleLayer__) */
