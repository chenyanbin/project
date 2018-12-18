//
//  GeneralsExperience_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/7/31.
//
//

#ifndef __FightPass__GeneralsExperience_Layer__
#define __FightPass__GeneralsExperience_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../data/CardPropertyData.h"
#include "../../../commonData/dictData/DictHeroPrestigeUpCost/DictHeroPrestigeUpCostManager.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
class GeneralsExperience_Layer:public BaseLayer
{
public:
    GeneralsExperience_Layer();
    ~GeneralsExperience_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    CREATE_FUNC(GeneralsExperience_Layer);
    void headAction();
private:
    void createLayer();
    void onButtonClick(Node* pSender);
    void onBtnClick(Ref* pSender);
    Sprite* getNode(const char* iconPath,const char* labelStr,bool isHaveBtn,bool isPower);
    void requestListMsg();
    
    void deleteAction(Node* pSprite);
    void updataCardLocation(CardPropertyData* data);
    void updataData();
    void onMsgProcess(EventCustom* msg);
    void onChooseCard(EventCustom* msg);
    void onAddCardFun(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    int setCardInfoData(string valueStr , int value);
    
private:
    int cardId;
    int heroDictId;//当前武将ID
    short heroLeve;//当前武将等级；
    int heroPrestige;//当前武将声望
    int nextLevel;//升级后等级
    short prestigeAdd;//声望提升
    int cost;//花费铜钱或元宝
    
    int TAG_UPLEVEL;//升级后TAG
    int TAG_ADDPRESTIGE;//加声望
    int TAG_CONSUME;//需要铜钱
    int TAG_CURRENTLV;//当前经验
    
    int cardLeve;
    vector<CardPropertyData*> *cardList;
};

#endif /* defined(__FightPass__GeneralsExperience_Layer__) */
