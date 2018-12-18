//
//  ExperienceEffect.cpp
//  FightPass
//
//  Created by 超 顾 on 15/10/15.
//
//

#include "ExperienceEffect.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "editor-support/cocostudio/CCArmature.h"
#include "../../../avatar/hero/Hero.h"
#include "../../../common/commonEffect/CommonEffect.h"
#include "../../../common/NumberChange.h"
#include "../../../commonData/dictData/DictHeroQuality/DictHeroQualityManager.h"
ExperienceEffect::ExperienceEffect()
:experience_ago(NULL)
,experience_after(NULL)
,cardName("")
,sx(1)
,TAG_CARDBG(1)
,TAG_LEVELABEL(2)//当前等级
,TAG_MAXLEVELABEL(3)//最大等级
,TAG_NAMELABEL(4)//名字
,TAG_PRESTLABEL(5)//声望
,TAG_MILITLABEL(6)//战力
,TAG_PROGRESS(7)//经验进度
,TAG_LEADLABEL(8)//领导力
{
    
}
ExperienceEffect::~ExperienceEffect()
{
    experience_ago=NULL;
    experience_after=NULL;
}
void ExperienceEffect::onExit()
{
    BaseLayer::onExit();
}
void ExperienceEffect::onEnter()
{
    BaseLayer::onEnter();
}
void ExperienceEffect::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void ExperienceEffect::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    
}
bool ExperienceEffect::init(CardPropertyData* _ago,CardPropertyData* _after)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        experience_ago=_ago;
        experience_after=_after;
        this->isClickClose=true;
        this->setGrayBg();
        this->setClickEnabled(true);
        this->startLayer();
        bref = true;
    } while (false);
    return bref;
}

ExperienceEffect* ExperienceEffect::create(CardPropertyData* _ago,CardPropertyData* _after)
{
    ExperienceEffect* layer = new ExperienceEffect();
    if(layer && layer->init(_ago,_after))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void ExperienceEffect::startLayer()
{
    Sprite* cardBg=Sprite::create(IMG_GENERALS_CARD_BG);
    PublicShowUI::setTargetScale(cardBg,false,false);
    this->addChild(cardBg,0,TAG_BG);
    this->setContentSize(cardBg->getContentSize()*sx);
    this->showExperienceSound();
    
    cardBg->setScale(0, 0);
    CommonEffect* commonEffect = CommonEffect::create("lilianrenwushenji",false,true,NULL);
    commonEffect->setAnchorPoint(Point(0.5,0.5));
    PublicShowUI::setTargetScale(commonEffect);
    commonEffect->setPosition(60*sx,20*sx);
    this->addChild(commonEffect,2);
    
    CallFunc* funcall = CallFunc::create(CC_CALLBACK_0(ExperienceEffect::createLayer, this));
    FiniteTimeAction * seq = CCSequence::create(DelayTime::create(2),funcall,NULL);
    this->runAction(seq);
}
void ExperienceEffect::showExperienceSound()
{
    SoundManager::playEffectMusic(EFFECT_HERO_EXPERIENCE);
}
void ExperienceEffect::createLayer()
{
    Sprite* cardBg=(Sprite*)this->getChildByTag(TAG_BG);
    //背景云层
    Sprite* cardBg2=Sprite::create(IMG_GENERALS_CARD_BG2);
    cardBg2->setAnchorPoint(Point::ZERO);
    cardBg2->setPosition(13,2);
    cardBg->addChild(cardBg2,1);
    //卡牌框上层
    Sprite* cardBox=Sprite::create(IMG_GENERALS_CARD_BOX2);
    cardBox->setAnchorPoint(Point::ZERO);
    cardBox->setPosition(0,5);
    cardBg->addChild(cardBox,2);
    //卡牌品质框
    char stt[100]="";
    sprintf(stt,IMG_PUBLIC_HEADBIGFRAME,experience_ago->quality);
    Sprite* headBox=Sprite::create(stt);
    if(headBox)
    {
        headBox->setAnchorPoint(Point::ZERO);
        cardBg->addChild(headBox,3);
    }
   
    
    //卡牌
    int tempNum=experience_ago->heroDictId;
    DictHero* dictHero = DictHeroManager::getInstance()->getData(tempNum);
    const char* imgPath = PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH, dictHero->halfbodyrResource.c_str());
    
    Sprite* tempCard=Sprite::create(imgPath);
    tempCard->setAnchorPoint(Point::ZERO);
    tempCard->setPosition(-50,0);
    cardBg->addChild(tempCard,4);
    //卡牌下层
    Sprite* cardBox2=Sprite::create(IMG_GENERALS_CARD_BOX);
    cardBox2->setAnchorPoint(Point::ZERO);
    cardBox2->setPosition(0,5);
    cardBg->addChild(cardBox2,5);
    //卡牌名字
    
    sprintf(stt,IMG_PUBLIC_HEADNAMEBG,experience_ago->quality);
    Sprite* headNameBg=Sprite::create(stt);
    headNameBg->setAnchorPoint(Point::ZERO);
    headNameBg->setPosition(40,112);
    cardBg->addChild(headNameBg,6);
    
    int typeNum =  DictHeroManager::getInstance()->getData(experience_ago->heroDictId)->attackType;
    if (typeNum<1) {
        typeNum = 1;
    }
    sprintf(stt,IMG_PUBLIC_HEROINFO_ATTACTTYPE,typeNum);
    Sprite* forceSprite=Sprite::create(stt);
    forceSprite->setAnchorPoint(Point::ZERO);
    forceSprite->setPosition(40,416);
    cardBg->addChild(forceSprite,5);
    //名字
    string str="";
    str=this->experience_ago->heroName;
    DictHeroQuality* qualityData =DictHeroQualityManager::getInstance()->getData(experience_ago->quality);
    if (qualityData) {
        str=qualityData->name+"  "+this->experience_ago->heroName;
    }
    Label* nameLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),22,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition((cardBg->getContentSize().width-nameLabel->getContentSize().width)/2,190);
//    nameLabel->setAlignment(TextHAlignment::CENTER);
//    nameLabel->setPosition(0,195);
    cardBg->addChild(nameLabel,6,TAG_NAMELABEL);
    //等级
    str=PublicShowUI::numberToString(experience_ago->level)+"/"+PublicShowUI::numberToString(experience_ago->levelMax);
    Label* lvLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),20,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    lvLabel->setPosition(318,108);
    cardBg->addChild(lvLabel,6,TAG_LEVELABEL);
    
    //领导力
    str=PublicShowUI::numberToString(experience_ago->leadership);
    Label* leadLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),18,false,false);
    leadLabel->setAnchorPoint(Point(0.5,0.5));
    leadLabel->setPosition(182,107);
    cardBg->addChild(leadLabel,6,TAG_LEADLABEL);
    
    //声望
    str=PublicShowUI::numberToString(experience_ago->prestige);
    Label* prestLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),18,false,false);
    prestLabel->setAnchorPoint(Point::ZERO);
    prestLabel->setPosition(170,59);
    cardBg->addChild(prestLabel,6,TAG_PRESTLABEL);
    
    //战力
    str=PublicShowUI::numberToString(experience_ago->combatPower);
    Label* militaryLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),18,false,false);
    militaryLabel->setAnchorPoint(Point::ZERO);
    militaryLabel->setPosition(310,59);
    cardBg->addChild(militaryLabel,6,TAG_MILITLABEL);
    
    //进度条
    float totalExperence =experience_ago->heroMaxExperience;
    float percent = (float)experience_ago->heroExperience / totalExperence;
    
    ProgressTimer* expProgress = ProgressTimer::create(Sprite::create(IMG_GENERALS_CARD_PROGRESS));
    expProgress->setType(ProgressTimer::Type::BAR);
    expProgress->setMidpoint(Point(0,1));
    expProgress->setBarChangeRate(Point(1,0));
    expProgress->setAnchorPoint(Point(0 ,0));
    expProgress->setPosition(120,37);
    cardBg->addChild(expProgress,6,TAG_PROGRESS);
    expProgress->setPercentage(percent * 100);
    
    ScaleTo* scaleTo = ScaleTo::create(0.2, sx, sx);
    CallFunc* funcall = CallFunc::create(CC_CALLBACK_0(ExperienceEffect::completeScale, this));
    FiniteTimeAction * seq = CCSequence::create(scaleTo,funcall,NULL);
    cardBg->runAction(seq);
}
void ExperienceEffect::completeScale()
{
    this->experEffect();
}
void ExperienceEffect::loadPerson()
{
    string resource="";
    Vector<DictHero*>* heroList=DictHeroManager::getInstance()->getDataList();
    for (DictHero* stage : *heroList ) {
        if (stage->id == experience_ago->heroDictId) {
            cardName=stage->resource;
            break;
        }
    }
    CC_SAFE_DELETE(heroList);
    heroList = NULL;
    string path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,cardName.c_str());
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(ExperienceEffect::onDataLoaded));
}
void ExperienceEffect::onDataLoaded(float percent)
{
    if(percent >= 1)
    {
        Sprite* cardBg=(Sprite*)this->getChildByTag(TAG_BG);
        if (cardBg) {
            if (cardBg->getChildByTag(88)) {
                cardBg->removeChildByTag(88);
            }
            Hero* cardHero=NULL;
            if (experience_ago) {
                cardHero=Hero::create(experience_ago->heroDictId);
            }else
            {
                cardHero=Hero::create(111030);
            }
            cardHero->setScale(0.7);
            cardHero->setPosition(108, 115);
            cardBg->addChild(cardHero,3,88);
        }
    }
}

void ExperienceEffect::clearResourcePerson(string str)//清除人物资源
{
    string path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,cardName.c_str());
    cocostudio::ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
    
    cocostudio::ArmatureDataManager::getInstance()->removeArmatureFileInfo("");
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    
}
void ExperienceEffect::experEffect()
{
    Sprite* cardBg=(Sprite*)this->getChildByTag(TAG_BG);
    //刷新经验条
    ProgressTimer* expProgress = (ProgressTimer*)cardBg->getChildByTag(TAG_PROGRESS);
    //获取经验条的 往返几次的动作
    
    int len = experience_after->level-experience_ago->level;
    if (len>4)len=4;
    Vector<ActionInterval*> *actionInterval = new Vector<ActionInterval*>();
    
//    float totalExperence =experience_ago->heroMaxExperience;
//    float percent = (float)experience_ago->heroExperience / totalExperence;
    
    float percentage=expProgress->getPercentage();
    float bili=(float)experience_after->heroExperience/(float)experience_after->heroMaxExperience;
        for(int i=0;i<=len;i++)
        {
            float began = 0;
            float endel = 100;
            float time=1;
            if(i==0)
            {
                began = percentage;//上次位置
                time=1-(began/100);
            }
            if(i+1 > len)
            {
                endel = bili*100;
                if (endel<100) {
                    time=1-((endel-began)/100);
                }
                
            }
            ActionInterval* action_progress_from_to = ProgressFromTo::create(time, began, endel);
            actionInterval->pushBack(action_progress_from_to);
        }

    expProgress->setPercentage(percentage);
    //取经验条的动作
    if(actionInterval->size() > 0)
    {
        expProgress->runAction(CCSequence::create(actionInterval->at(0),DelayTime::create(0.05),CallFuncN::create(CC_CALLBACK_1(ExperienceEffect::deleteActionInterval, this, actionInterval)), NULL));
    }
    //---------------------------------------------------------------------其他刷新动画---------------------------------------------------------------------//
    float duration = 1.0f;
    //等级刷新
    int fromNum = experience_ago->level; //开始数字
    int toNUm = experience_after->level; //结束数字
//    if (toNUm-fromNum>0) {
//        CallFunc* funcall = CallFunc::create(CC_CALLBACK_0(ExperienceEffect::onLeveUpEffect, this));
//        FiniteTimeAction * seq = CCSequence::create(DelayTime::create(duration),funcall,NULL);
//        this->runAction(seq);
//    }
    if (toNUm>fromNum) {
        NumberChange *pChange = NumberChange::create(duration, fromNum, toNUm);
        Label* lvLabel = (Label*)cardBg->getChildByTag(TAG_LEVELABEL);
        lvLabel->runAction(pChange);
    }
    //领导力
    fromNum = experience_ago->leadership; //开始数字
    toNUm = experience_after->leadership; //结束数字
    if (toNUm>fromNum) {
        NumberChange *pChange = NumberChange::create(duration, fromNum, toNUm);
        Label* lvLabel = (Label*)cardBg->getChildByTag(TAG_LEADLABEL);
        lvLabel->runAction(pChange);
    }
    //战力
    fromNum = experience_ago->combatPower; //开始数字
    toNUm = experience_after->combatPower; //结束数字
    if (toNUm>fromNum) {
        NumberChange *pChange = NumberChange::create(duration, fromNum, toNUm);
        Label* lvLabel = (Label*)cardBg->getChildByTag(TAG_MILITLABEL);
        lvLabel->runAction(pChange);
    }
    //声望
    fromNum = experience_ago->prestige; //开始数字
    toNUm = experience_after->prestige; //结束数字
    if (toNUm>fromNum) {
        NumberChange *pChange = NumberChange::create(duration, fromNum, toNUm);
        Label* lvLabel = (Label*)cardBg->getChildByTag(TAG_PRESTLABEL);
        lvLabel->runAction(pChange);
    }
}
void ExperienceEffect::onLeveUpEffect()
{
    Sprite* cardBg=(Sprite*)this->getChildByTag(TAG_BG);
    Label* lvLabel = (Label*)cardBg->getChildByTag(TAG_PROGRESS);
    if (lvLabel) {
        CommonEffect* commonEffect = CommonEffect::create("kapaiyoushangjiao",false,false);
        commonEffect->setAnchorPoint(Point(0.5,0.5));
        commonEffect->setPosition(lvLabel->getPositionX()+lvLabel->getContentSize().width-35,lvLabel->getPositionY()+25);
        cardBg->addChild(commonEffect,12);

    }
}
//删除动画列表
void ExperienceEffect::deleteActionInterval(Node* pSprite,Vector<ActionInterval*> *actionInterval)
{
    if(actionInterval->size() > 0)
    {
        actionInterval->erase(0);
    }
    
    if(actionInterval->size() > 0)
    {
        onLeveUpEffect();
        pSprite->runAction(CCSequence::create(actionInterval->at(0),DelayTime::create(0.05),CallFuncN::create(CC_CALLBACK_1(ExperienceEffect::deleteActionInterval, this, actionInterval)), NULL));
    }else
    {
        
    }
}
