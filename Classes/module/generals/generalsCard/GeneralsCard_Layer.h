//
//  GeneralsCard_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/7/30.
//
//

#ifndef __FightPass__GeneralsCard_Layer__
#define __FightPass__GeneralsCard_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "../data/CardPropertyData.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../HeroListBar_Layer.h"
USING_NS_CC_EXT;
USING_NS_CC;
class GeneralsCard_Layer:public BaseLayer
{
public:
    GeneralsCard_Layer();
    ~GeneralsCard_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(int value,string sortMode);
    static GeneralsCard_Layer* create(int value,string sortMode);
//    CREATE_FUNC(GeneralsCard_Layer);
    static void show(int fromeScene,int valueId,string sortMode="level");
private:
    void createLayer();
    void updateCreateLayer();
    void requestHeroMsg(int _id);
    void onMsgProcess(EventCustom* msg);
    void topLayer();
    void addBaseLayer();
    void addSkillLayer();
    void addExperience();
    void addPropertyLayer();
    void addAwake();
    void addRightList();
    void addLeftList(string sortMode);
    void putOnUpData(EventCustom* msg);
//    void setBackBtn();
    void handerClickExperience();
    void handerEffectEnd();
    void handerClickAwake(EventCustom* msg);
    
    
    void onBackClick(Ref* pSender);
    void onComboBoxBtnClick(Ref* psender);
    void callbackC();
    void onChooseCard(EventCustom* msg);
    void onChooseHeroCallBack(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    void updateStarLevel();
    void experEffect(bool levelUP);
    void deleteActionInterval(Node* pSprite,Vector<ActionInterval*> *actionInterval);
    void requestHeroListMsg();//请求英雄列表
    
    void onLevelUpClick(Ref* pSender);
    void onLevelUpPress(Ref* pSender);
    void onLevelUpOutSide(Ref* pSender);
    void onCombatChange(int value);//战力变化
    void requestLevelUpMsg();
private:
    int TAG_BG;
    int TAG_CARDBG;
    int TAG_RIGHTLAYER;
    int TAG_EXPERIENCE;
    int TAG_RIGHTLIST;
    int TAG_LEFTLIST;
    int TAG_TOP;
    int TAG_RIGHTBOX;
    int TAG_CHOOSECARD;
    int TAG_PRESTLABEL;//声望tag
    int TAG_MILITLABEL;//战力tag
    int TAG_LEADLABEL;//领导力tag
    int TAG_LEVELABEL;//等级tag
    int TAG_MAXLEVELABEL;//最大等级tag
    int TAG_NAMELABEL;//武将名字
    int TAG_PROGRESS;//经验进度条；
    int TAG_HEADBOX;//卡牌品质看；
    int TAG_HEADNAMEBG;//卡牌名字背景；
    int TAG_HEROBIGCARD;//大卡片;
    int TAG_FORCE;//势力；
    int TAG_EXPLABEL;
    int TAG_LEVELPUP_NEED_EXP;
    int TAG_LEVELUPBTN;
    float sx;
    int _valueId;
    string cardName;
    int allNum;
    int cardId;
    int chooseId;
    bool ExperBol;
    CardPropertyData* heroData;
//    Vector<DictHero*>* heroList;
    
    HeroListBar_Layer* leftHeadList;//左头像列表
    float _levelUpDelayTime;
    int TAG_LEVELUPDELAY;
    bool levelUpisPressed;
};

#endif /* defined(__FightPass__GeneralsCard_Layer__) */
