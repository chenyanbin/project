   //
//  GeneralsBase_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/7/29.
//
//

#include "GeneralsCard_Layer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../common/ImagePath.h"
#include "../../../../Classes/VisibleRect.h"
#include "../../../common/GameConfig.h"
#include "../../../common/PublicShowUI.h"
#include "../../lineup/LineupChoseLayer.h"
#include "../../../../Classes/commonData/GlobalInfo.h"
#include "../generalsBase/GeneralsBase_Layer.h"
#include "../generalsExperience/GeneralsExperience_Layer.h"
#include "../generalsSkill/GeneralsSkill_Layer.h"
#include "../generalsProperty/GeneralsProperty_Layer.h"
#include "../generalsExperience/ChooseCard_layer.h"
#include "../generalsAwake/GeneralsAwake_Layer.h"
#include "../Generals_Layer.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../../userWealth/UserWealthLayer.h"
#include "editor-support/cocostudio/CCArmature.h"
#include "../../../avatar/hero/Hero.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../message/Decoding/generals/heroInfo/GeneralsHeroInfoMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/commonEffect/CommonEffect.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../commonData/data/FunctionOpenManager.h"
#include "../../../commonData/enum/DictFunctionEnum.h"
#include "../../../commonData/dictData/DictHeroQuality/DictHeroQualityManager.h"
#include "../../../message/Decoding/heroListMsg/heroListMsg.h"
#include "../../../message/Decoding/generals/experience/HeroAddExpMsg.hpp"
#include "../../../common/Dialog/Dialog.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../commonData/enum/DictFunctionEnum.h"
GeneralsCard_Layer::GeneralsCard_Layer()
:TAG_BG(1)
,TAG_CARDBG(2)
,TAG_RIGHTLAYER(3)
,TAG_RIGHTLIST(4)
,TAG_LEFTLIST(5)
,TAG_TOP(6)
,TAG_PRESTLABEL(7)
,TAG_MILITLABEL(8)
,TAG_LEADLABEL(9)
,TAG_LEVELABEL(10)
,TAG_MAXLEVELABEL(11)
,TAG_HEADNAMEBG(12)
,TAG_HEADBOX(13)
,TAG_FORCE(14)
,TAG_LEVELUPBTN(15)
,TAG_CHOOSECARD(10000)
,TAG_RIGHTBOX(10001)
,TAG_NAMELABEL(10002)
,TAG_PROGRESS(10003)
,TAG_HEROBIGCARD(10004)
,TAG_EXPERIENCE(10005)
,TAG_EXPLABEL(10006)
,TAG_LEVELPUP_NEED_EXP(10007)
,TAG_LEVELUPDELAY(10008)
,_valueId(0)
,allNum(4)
,cardName("")
,cardId(1)
,heroData(NULL)
,chooseId(-1)
,ExperBol(false)
,leftHeadList(NULL)
,_levelUpDelayTime(0)
,levelUpisPressed(false)
{
    heroData=new CardPropertyData();
    heroData->autorelease();
    CC_SAFE_RETAIN(heroData);
}
GeneralsCard_Layer::~GeneralsCard_Layer()
{
    CardDataManager::getInstance()->setPresentData(NULL);
    CC_SAFE_RELEASE_NULL(heroData);
    leftHeadList=NULL;
}
void GeneralsCard_Layer::onExit()
{
    BaseLayer::onExit();
}
void GeneralsCard_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void GeneralsCard_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumExpTag);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumExperience);
}
void GeneralsCard_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();

}
void GeneralsCard_Layer::requestHeroListMsg()//请求英雄列表
{
    heroListMsg* msg = new heroListMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
bool GeneralsCard_Layer::init(int valueId,string sortMode)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());        
//        heroList=DictHeroManager::getInstance()->getDataList();
        chooseId=valueId;
        
       
        sx=GlobalInfo::getInstance()->screenScaleX;
        
        this->setBackBtn(0,15*sx);
        this->topLayer();
        this->createLayer();
        this->addLeftList(sortMode);
        this->addRightList();
        bref = true;
    } while (false);
    return bref;
}

GeneralsCard_Layer* GeneralsCard_Layer::create(int valueId,string sortMode)
{
    GeneralsCard_Layer* layer = new GeneralsCard_Layer();
    if(layer && layer->init(valueId,sortMode))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}

void GeneralsCard_Layer::show(int fromeScene,int valueId,string sortMode)
{
    
    Director::getInstance()->purgeCachedData();
    GeneralsCard_Layer* layer=GeneralsCard_Layer::create(valueId,sortMode);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    layer->setFromScene(fromeScene);
    Scene* scene = Scene::create();
    scene->addChild(layer,0,SCENE_TAG_GENERALSCARD);
    Director::getInstance()->replaceScene(scene);
}
void GeneralsCard_Layer::topLayer()
{
    UserWealthLayer* layer = UserWealthLayer::create(UserWealthLayer::BELONG);
    PublicShowUI::setTargetScale(layer);
    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2, VisibleRect::top().y-layer->getContentSize().height);
    layer->setTitle(IMG_PUBLIC_HERO);
    this->addChild(layer,3,TAG_TOP);
    
}
//----------------------------------------------中间卡牌----------------------------------------------//
void GeneralsCard_Layer::createLayer()
{
 
    CardPropertyData* propData = CardDataManager::getInstance()->getPresentData();
    
    if(!propData)
    {
        propData = new CardPropertyData();
        propData->autorelease();
        propData->heroDictId = GlobalInfo::getInstance()->gameRole->mainHeroDictID;

    }
    Sprite* bg=Sprite::create(IMG_PUBLIC_MODULE_BG);
    PublicShowUI::setTargetScale(bg,true);
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg,0,TAG_BG);
    
    Sprite* cardBg=Sprite::create(IMG_GENERALS_CARD_BG);
    PublicShowUI::setTargetScale(cardBg);
    cardBg->setAnchorPoint(Point::ZERO);
    Sprite* topBg=(Sprite*)this->getChildByTag(TAG_TOP);
    cardBg->setPosition(180*sx,(this->getContentSize().height-topBg->getContentSize().height-cardBg->getContentSize().height)/2);
    this->addChild(cardBg,2,TAG_CARDBG);
    if (chooseId==DictFunctionEnumHeroPrestige) {
        cardBg->setVisible(false);
    }
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
    sprintf(stt,IMG_PUBLIC_HEADBIGFRAME,1);
    Sprite* headBox=Sprite::create(stt);
//    headBox->setVisible(false);
    headBox->setAnchorPoint(Point::ZERO);
    cardBg->addChild(headBox,3,TAG_HEADBOX);
//    headBox->setPositionX((cardBg->getContentSize().width - headBox->getContentSize().width)/2);
    //卡牌
    int tempNum=propData->heroDictId;
    if (tempNum!=-1) {
        DictHero* dictHero = DictHeroManager::getInstance()->getData(tempNum);
        if (!dictHero) {
            return;
        }
        const char* imgPath = PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH, dictHero->halfbodyrResource.c_str());
        Sprite* tempCard=Sprite::create(imgPath);
        tempCard->setAnchorPoint(Point::ZERO);
        tempCard->setPosition(-50,0);
        cardBg->addChild(tempCard,4,TAG_HEROBIGCARD);
        
        int typeNum =  dictHero->attackType;
        if (typeNum<1) {
            typeNum = 1;
        }
        sprintf(stt,IMG_PUBLIC_HEROINFO_ATTACTTYPE,typeNum);
        Sprite* forceSprite=Sprite::create(stt);
        forceSprite->setAnchorPoint(Point::ZERO);
        forceSprite->setPosition(40,416);
        forceSprite->setVisible(false);
        cardBg->addChild(forceSprite,5,TAG_FORCE);
    }
        //卡牌下层
    Sprite* cardBox2=Sprite::create(IMG_GENERALS_CARD_BOX);
    cardBox2->setAnchorPoint(Point::ZERO);
    cardBox2->setPosition(0,5);
    cardBg->addChild(cardBox2,5);
    //卡牌名字
    
    sprintf(stt,IMG_PUBLIC_HEADNAMEBG,1);
    Sprite* headNameBg=Sprite::create(stt);
    headNameBg->setAnchorPoint(Point::ZERO);
    headNameBg->setPosition(40,112);
    headNameBg->setVisible(false);
    cardBg->addChild(headNameBg,6,TAG_HEADNAMEBG);
    
    
    
    //名字
    Size _size;
    _size=cardBg->getContentSize()/sx;
    _size.height=30;
    string str="";
    Label* nameLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),22,false,false,_size,TextHAlignment::CENTER);
    nameLabel->setAnchorPoint(Point(0.5,0.5));
    
    nameLabel->setAlignment(TextHAlignment::CENTER);
    nameLabel->setPosition(0,190);
    cardBg->addChild(nameLabel,6,TAG_NAMELABEL);
    //等级
    Label* lvLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),20,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    lvLabel->setPosition(145,65);
    cardBg->addChild(lvLabel,6,TAG_LEVELABEL);
    
    //领导力
    Label* leadLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),18,false,false);
    leadLabel->setAnchorPoint(Point(0.5,0.5));
    leadLabel->setPosition(320,107);
    cardBg->addChild(leadLabel,6,TAG_LEADLABEL);
    
//    //星级
    
    Node* starSpr = Node::create();
    starSpr->setAnchorPoint(Point::ZERO);
    cardBg->addChild(starSpr,6,TAG_PRESTLABEL);
    starSpr->setPosition(170, 125);
    updateStarLevel();
    //战力
    Label* militaryLabel = PublicShowUI::getLabel("0",PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),18,false,false);
    militaryLabel->setAnchorPoint(Point::ZERO);
    militaryLabel->setPosition(165,93);
    cardBg->addChild(militaryLabel,6,TAG_MILITLABEL);
    
    //进度条
    
    float totalExperence =100;
    float percent =  100 / totalExperence;
    Sprite* spr = Sprite::create(IMG_GENERALS_CARD_PROGRESS);
    spr->setAnchorPoint(Point::ZERO);
   
    ProgressTimer* expProgress = ProgressTimer::create(spr);
    expProgress->setType(ProgressTimer::Type::BAR);
    expProgress->setMidpoint(Point(0,1));
    expProgress->setBarChangeRate(Point(1,0));
    expProgress->setAnchorPoint(Point(0 ,0));
    expProgress->setPosition(187,42);
    expProgress->setScaleX(.7);
   
    cardBg->addChild(expProgress,6,TAG_PROGRESS);
    expProgress->setPercentage(percent * 100);
  
    Label* expLabel = PublicShowUI::getLabel("999",PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),15,false,false);
    expLabel->setAnchorPoint(Point::ZERO);
    expLabel->setPosition(expProgress->getPositionX() + 40, expProgress->getPositionY() + expProgress->getContentSize().height );
    cardBg->addChild(expLabel,7,TAG_EXPLABEL);
    
    //升级所需经验w
    
    Label* needLabel = PublicShowUI::getLabel("999",PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),15,false,false);
    needLabel->setAnchorPoint(Point::ZERO);
    needLabel->setPosition(expProgress->getPositionX() + 40, expProgress->getPositionY() - needLabel->getContentSize().height + 2  );
    cardBg->addChild(needLabel,7,TAG_LEVELPUP_NEED_EXP);
    
    CustomButton* levelUpBtn = CustomButton::create(IMG_PUBLIC_BUTTON_TWO_SMALLORANGE, "", CC_CALLBACK_1(GeneralsCard_Layer::onLevelUpClick, this));
    levelUpBtn->addTitle(IMG_GENERALS_LEVELUPLABEL, IMG_GENERALS_LEVELUPLABEL);
    levelUpBtn->setPosition(expProgress->getPositionX() + expProgress->getContentSize().width   , expProgress->getPositionY() + 15);
    cardBg->addChild(levelUpBtn,8,TAG_LEVELUPBTN);
    if (heroData->prestigeStatus == 1) {
        PublicShowUI::setDot(levelUpBtn, Point(10,10), false,DictFunctionEnumHeroPrestige);
    }
    levelUpBtn->onTouchPress = CC_CALLBACK_1(GeneralsCard_Layer::onLevelUpPress, this);
    levelUpBtn->onReleaseOutSide = CC_CALLBACK_1(GeneralsCard_Layer::onLevelUpOutSide, this);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumExperience, levelUpBtn);
}
void GeneralsCard_Layer::onLevelUpPress(Ref* pSender)
{
    if(heroData->freeExp < heroData->nextStepExp)
    {
        NoticeManager::getInstance()->showNotice("武将池经验不足，不能升级！");
        return;
    }
//
    levelUpisPressed = true;
      Dialog::showServerLoading();
    _levelUpDelayTime = .5;
    requestLevelUpMsg();
}
void GeneralsCard_Layer::onLevelUpOutSide(Ref* pSender)
{
    levelUpisPressed = false;
    this->stopActionByTag(TAG_LEVELUPDELAY);
}
void GeneralsCard_Layer::updateStarLevel()
{
    if(!heroData)
    {
        return;
    }
    Node* cardBg = this->getChildByTag(TAG_CARDBG);
    Node* starLevel = cardBg->getChildByTag(TAG_PRESTLABEL);
    starLevel->removeAllChildren();
    Sprite* star = NULL;
    for(int i = 0; i < this->heroData->prestige; i++)
    {
        if(starLevel->getChildByTag(i))
        {
            continue;
        }
        star = Sprite::create(IMG_PUBLIC_STAR);
        star->setAnchorPoint(Point::ZERO);
        star->setPosition(starLevel->getChildrenCount() * (star->getContentSize().width + 5), 0);
        starLevel->addChild(star,i,i);
    }
    if(star)
    {
        Size size = star->getContentSize();
        size.width = star->getPositionX() + size.width;
        starLevel->setPositionX((cardBg->getContentSize().width / GlobalInfo::getInstance()->screenScaleX -size.width)/2 + 6);
    }
 
}
void GeneralsCard_Layer::onLevelUpClick(Ref* pSender)
{
    this->stopActionByTag(TAG_LEVELUPDELAY);
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumExperience);
    onLevelUpOutSide(pSender);
}
void GeneralsCard_Layer::requestLevelUpMsg()
{
    if(!levelUpisPressed)
    {
        this->stopActionByTag(TAG_LEVELUPDELAY);
        return;
    }
    HeroAddExpMsg* msg = new HeroAddExpMsg(heroData->heroId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
    
    
    
}
//----------------------------------------------中间卡牌选择卡牌----------------------------------------------//

void GeneralsCard_Layer::onChooseCard(EventCustom* msg)
{
    Sprite* chooseCard=(Sprite*)this->getChildByTag(TAG_CHOOSECARD);
    Sprite* cardBg=(Sprite*)this->getChildByTag(TAG_CARDBG);
    cardBg->setVisible(false);
    if (chooseCard) {
        this->removeChildByTag(TAG_CHOOSECARD);
    }
    ChooseCard_layer* layer=ChooseCard_layer::create(1);
    layer->setPosition(cardBg->getPosition());
    this->addChild(layer,2,TAG_CHOOSECARD);
}
//中间卡牌
void GeneralsCard_Layer::onChooseHeroCallBack(EventCustom* msg)
{
//    _valueId=0;
    __Integer* inter = (__Integer*)msg->getUserData();
    int _heroId = inter->getValue();
    this->requestHeroMsg(_heroId);
}
void GeneralsCard_Layer::updateCreateLayer()
{
    cardId=heroData->heroId;
    Sprite* cardBg=(Sprite*)this->getChildByTag(TAG_CARDBG);
    if(!cardBg)
    {
        return;
    }
    char stt[100]= {0};
    //势力
    Sprite* forceSprite=(Sprite*)cardBg->getChildByTag(TAG_FORCE);
    if (forceSprite)
    {
        DictHero* data=DictHeroManager::getInstance()->getData(heroData->heroDictId);
        if (!data) {
            return;
        }
        int typeNum =  data->attackType;
        if (typeNum<1) {
            typeNum = 1;
        }
        sprintf(stt,IMG_PUBLIC_HEROINFO_ATTACTTYPE,typeNum);
        forceSprite->setTexture(stt);
        forceSprite->setVisible(true);
       
    }
    //卡牌框
     int quality = PublicShowUI::getColorIndexByQuality(DictItemTypeEnumItemHero, heroData->quality);
    Sprite* headBox=(Sprite*)cardBg->getChildByTag(TAG_HEADBOX);
    if (headBox) {
       
        sprintf(stt,IMG_PUBLIC_HEADBIGFRAME,quality);
        headBox->setTexture(stt);
        headBox->setVisible(true);
    }
    
    //名字框
    Sprite* headNameBg=(Sprite*)cardBg->getChildByTag(TAG_HEADNAMEBG);
    if (headNameBg) {
        sprintf(stt,IMG_PUBLIC_HEADNAMEBG,quality);
        headNameBg->setTexture(stt);
        headNameBg->setVisible(true);
    }
    //声望 星级
    this->updateStarLevel();
    //战力
    Label* militaryLabel=(Label*)cardBg->getChildByTag(TAG_MILITLABEL);
    if (militaryLabel)
    {
        
        militaryLabel->setString(PublicShowUI::numberToString(heroData->combatPower));
    }
    //领导力
    Label* leadLabel=(Label*)cardBg->getChildByTag(TAG_LEADLABEL);
    if (leadLabel) {
        leadLabel->setString(PublicShowUI::numberToString(heroData->leadership));
    }
    //等级
    Label* leveLabel=(Label*)cardBg->getChildByTag(TAG_LEVELABEL);
    if (leveLabel) {
        string str=PublicShowUI::numberToString(heroData->level);//+"/"+PublicShowUI::numberToString(heroData->levelMax);
        leveLabel->setString(str);
    }
    Sprite* bigCard=(Sprite*)cardBg->getChildByTag(TAG_HEROBIGCARD);
    if (bigCard) {
        int tempNum=heroData->heroDictId;
        DictHero* dictHero = DictHeroManager::getInstance()->getData(tempNum);
        if (!dictHero) {
            return;
        }
        const char* imgPath = PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH, dictHero->halfbodyrResource.c_str());
        if(Director::getInstance()->getTextureCache()->addImage(imgPath))
        {
            bigCard->setTexture(imgPath);
        }
        
    }else
    {
        DictHero* dictHero = DictHeroManager::getInstance()->getData(heroData->heroDictId);
        if (!dictHero) {
            return;
        }
        const char* imgPath = PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH, dictHero->halfbodyrResource.c_str());
        Sprite* tempCard=Sprite::create(imgPath);
        tempCard->setAnchorPoint(Point::ZERO);
        tempCard->setPosition(-50,0);
        cardBg->addChild(tempCard,4,TAG_HEROBIGCARD);
    }
    //名字
    Label* nameLabel = (Label*)cardBg->getChildByTag(TAG_NAMELABEL);
    if (nameLabel) {
        
        string name="";
        DictHeroQuality* data=DictHeroQualityManager::getInstance()->getData(heroData->quality);
        name= heroData->heroName;
        if (name.size()) {
            name=data->name+"  "+heroData->heroName;
        }
        
//        if (heroData->quality>1) {
//            int tempNum=heroData->quality-1;
//            name= heroData->heroName+" +"+PublicShowUI::numberToString(tempNum);
//        }else
//        {
//            name= heroData->heroName;
//        }
        
        nameLabel->setString(name);
    }
    //刷新经验条
    ProgressTimer* expProgress = (ProgressTimer*)cardBg->getChildByTag(TAG_PROGRESS);
    if (expProgress)
    {
        float percent =(float)heroData->heroExperience/(float)heroData->heroMaxExperience;
        expProgress->runAction(ProgressFromTo::create(.3, expProgress->getPercentage(), percent * 100));
    }
    Label* expLabel = (Label*)cardBg->getChildByTag(TAG_EXPLABEL);
    if(expLabel)
    {
        string str = PublicShowUI::numberToString(heroData->freeExp);
        expLabel->setString(str);
    }

    Label* needLabel = (Label*)cardBg->getChildByTag(TAG_LEVELPUP_NEED_EXP);
    if(needLabel)
    {
        string str = PublicShowUI::numberToString(heroData->nextStepExp);
        needLabel->setString(str);
    }
    
    CardDataManager::getInstance()->setPresentData(heroData);
   
    //加右layer
    if(!ExperBol)
    {
        ComboBoxBtn* boxBtn=(ComboBoxBtn*)this->getChildByTag(TAG_RIGHTLIST);
        if (boxBtn) {
            boxBtn->resetAllBtn();
            boxBtn->selectAtByTag(chooseId);
        }
       
    }
    CustomButton* btn = (CustomButton*)this->getChildByTag(TAG_CARDBG)->getChildByTag(TAG_LEVELUPBTN);
    if (btn) {
        if (heroData->prestigeStatus == 1) {
            PublicShowUI::setDot(btn, Point(10,10), false,DictFunctionEnumHeroPrestige);
        }else
        {
            PublicShowUI::setDot(btn, Point(10,10), false);
        }
    }
     ExperBol = false;
}

//----------------------------------------------右卡牌属性----------------------------------------------//
void GeneralsCard_Layer::callbackC()
{
//    int functionList[5] = {0,DictFunctionEnumHeroProp,DictFunctionEnumHeroSkill,DictFunctionEnumHeroPrestige,DictFunctionEnumHeroQuality};
    Sprite* cardBg=(Sprite*)this->getChildByTag(TAG_CARDBG);
    if (cardBg and _valueId!=DictFunctionEnumHeroPrestige) {
        cardBg->setVisible(true);
    }
    Sprite* chooseCard=(Sprite*)this->getChildByTag(TAG_CHOOSECARD);
    if (chooseCard and _valueId!=DictFunctionEnumHeroPrestige) {
        this->removeChildByTag(TAG_CHOOSECARD);
    }
    
    Sprite* rightLayer=(Sprite*)this->getChildByTag(TAG_RIGHTLAYER);
    if (rightLayer) {
        this->removeChildByTag(TAG_RIGHTLAYER);
        switch (_valueId) {
            case DictFunctionEnumEquip:
                this->addBaseLayer();
                break;
            case DictFunctionEnumHeroSkill:
                this->addSkillLayer();
                break;
            case DictFunctionEnumHeroPrestige:
                this->addExperience();
                break;
            case DictFunctionEnumHeroProp:
                this->addPropertyLayer();
                break;
            case DictFunctionEnumHeroQuality:
                this->addAwake();
            default:
                break;
        }

    }
    
    
}
void GeneralsCard_Layer::addBaseLayer()
{

    Sprite* experLayer=(Sprite*)this->getChildByTag(TAG_EXPERIENCE);
    if (experLayer) {
        this->removeChildByTag(TAG_EXPERIENCE);
    }
    Sprite* cardBg=(Sprite*)this->getChildByTag(TAG_CARDBG);
    Sprite* rightLayer=(Sprite*)this->getChildByTag(TAG_RIGHTLAYER);
    if(cardBg)
    {
         cardBg->setVisible(true);
    }
   
    if (rightLayer)
    {
//        cardBg->removeAllChildren();
        MoveTo* move=MoveTo::create(0.1, Point(rightLayer->getPositionX()-rightLayer->getContentSize().width, rightLayer->getPositionY()));
        //    CCCallFunc
        //    作用：创建一个回调动作（调用不带参数的回调方法）；
        //    参数1：目标动作
        //    参数2：目标回调函数
//            CCCallFunc * funcall= CCCallFunc::create(this, callfunc_selector(GeneralsCard_Layer::callbackC));
        CallFunc* funcall = CallFunc::create(CC_CALLBACK_0(GeneralsCard_Layer::callbackC, this));
        FiniteTimeAction * seq = Sequence::create(move,funcall,NULL);
        rightLayer->runAction(seq);
    }
    else
    {
        GeneralsBase_Layer* baseLayer=GeneralsBase_Layer::create(cardId);
        baseLayer->setPosition(cardBg->getContentSize().width+cardBg->getPositionX()-10*sx-baseLayer->getContentSize().width,cardBg->getPositionY());
        this->addChild(baseLayer,1,TAG_RIGHTLAYER);
        CallFunc* funcall = CallFunc::create(CC_CALLBACK_0(NewPlayerGuild::showNowGuide, NewPlayerGuild::getInstance()));
        MoveTo* move=MoveTo::create(0.2, Point(cardBg->getContentSize().width+cardBg->getPositionX()-20*sx, cardBg->getPositionY()));
        baseLayer->runAction(Sequence::create(move,DelayTime::create(.1),funcall, NULL));
    }
    
}
void GeneralsCard_Layer::addPropertyLayer()
{
    if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumHeroProp))
    {
        FunctionOpenManager::getInstance()->showNoOpenNotice();
        return;
    }
    Sprite* experLayer=(Sprite*)this->getChildByTag(TAG_EXPERIENCE);
    if (experLayer) {
        this->removeChildByTag(TAG_EXPERIENCE);
    }
    
    Sprite* cardBg=(Sprite*)this->getChildByTag(TAG_CARDBG);
    if(!cardBg)
    {
        return;
    }
    Sprite* rightLayer=(Sprite*)this->getChildByTag(TAG_RIGHTLAYER);
    cardBg->setVisible(true);
    if (rightLayer) {
        //        cardBg->removeAllChildren();
        MoveTo* move=MoveTo::create(0.1, Point(rightLayer->getPositionX()-rightLayer->getContentSize().width, rightLayer->getPositionY()));
        //    CCCallFunc
        //    作用：创建一个回调动作（调用不带参数的回调方法）；
        //    参数1：目标动作
        //    参数2：目标回调函数
        //            CCCallFunc * funcall= CCCallFunc::create(this, callfunc_selector(GeneralsCard_Layer::callbackC));
        CallFunc* funcall = CallFunc::create(CC_CALLBACK_0(GeneralsCard_Layer::callbackC, this));
        FiniteTimeAction * seq = Sequence::create(move,funcall,NULL);
        rightLayer->runAction(seq);
    }else
    {
        GeneralsProperty_Layer* baseLayer=GeneralsProperty_Layer::create();
        baseLayer->setPosition(cardBg->getContentSize().width+cardBg->getPositionX()-10*sx-baseLayer->getContentSize().width,cardBg->getPositionY());
        this->addChild(baseLayer,1,TAG_RIGHTLAYER);
        MoveTo* move=MoveTo::create(0.2, Point(cardBg->getContentSize().width+cardBg->getPositionX()-20*sx, cardBg->getPositionY()));
        baseLayer->runAction(move);
    }
}
void GeneralsCard_Layer::addSkillLayer()
{
    if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumHeroSkill))
    {
        FunctionOpenManager::getInstance()->showNoOpenNotice();
        return;
    }
    Sprite* experLayer=(Sprite*)this->getChildByTag(TAG_EXPERIENCE);
    if (experLayer) {
        this->removeChildByTag(TAG_EXPERIENCE);
    }
    
    Sprite* cardBg=(Sprite*)this->getChildByTag(TAG_CARDBG);
    if(!cardBg)
    {
        return;
    }
    Sprite* rightLayer=(Sprite*)this->getChildByTag(TAG_RIGHTLAYER);
    cardBg->setVisible(true);
    if (rightLayer) {
//        cardBg->removeAllChildren();
        MoveTo* move=MoveTo::create(0.1, Point(rightLayer->getPositionX()-rightLayer->getContentSize().width, rightLayer->getPositionY()));
        //    CCCallFunc
        //    作用：创建一个回调动作（调用不带参数的回调方法）；
        //    参数1：目标动作
        //    参数2：目标回调函数
        CallFunc* funcall = CallFunc::create(CC_CALLBACK_0(GeneralsCard_Layer::callbackC, this));
        FiniteTimeAction * seq = Sequence::create(move,funcall,NULL);
        rightLayer->runAction(seq);
    }else{
        GeneralsSkill_Layer* skillLayer=GeneralsSkill_Layer::create();
        skillLayer->setPosition(cardBg->getContentSize().width+cardBg->getPositionX()-10*sx-skillLayer->getContentSize().width,cardBg->getPositionY());
        this->addChild(skillLayer,1,TAG_RIGHTLAYER);
        MoveTo* move=MoveTo::create(0.2, Point(cardBg->getContentSize().width+cardBg->getPositionX()-20*sx, cardBg->getPositionY()));
        skillLayer->runAction(move);
    }
}
void GeneralsCard_Layer::addExperience()
{
    if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumHeroPrestige))
    {
        FunctionOpenManager::getInstance()->showNoOpenNotice();
        return;
    }
    Sprite* rightLayer=(Sprite*)this->getChildByTag(TAG_RIGHTLAYER);
    if (rightLayer) {
        this->removeChildByTag(TAG_RIGHTLAYER);
    }
    Sprite* experLayer=(Sprite*)this->getChildByTag(TAG_EXPERIENCE);
    if (experLayer) {
        this->removeChildByTag(TAG_EXPERIENCE);
    }
    
    Sprite* cardBg=(Sprite*)this->getChildByTag(TAG_CARDBG);
    if (cardBg) {
        cardBg->setVisible(false);
    }
    
    ChooseCard_layer* layer=ChooseCard_layer::create(1);
    layer->setPosition((this->getContentSize().width-layer->getContentSize().width)/2,(this->getContentSize().height-layer->getContentSize().height)/2-15*sx);
    this->addChild(layer,2,TAG_EXPERIENCE);
    
}
void GeneralsCard_Layer::addAwake()
{
    if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumHeroQuality))
    {
        FunctionOpenManager::getInstance()->showNoOpenNotice();
        return;
    }
    Sprite* experLayer=(Sprite*)this->getChildByTag(TAG_EXPERIENCE);
    if (experLayer) {
        this->removeChildByTag(TAG_EXPERIENCE);
    }
    
    Sprite* cardBg=(Sprite*)this->getChildByTag(TAG_CARDBG);
    if(!cardBg)
    {
        return;
    }
    Sprite* rightLayer=(Sprite*)this->getChildByTag(TAG_RIGHTLAYER);
    cardBg->setVisible(true);
    if (rightLayer) {
        //        cardBg->removeAllChildren();
        MoveTo* move=MoveTo::create(0.1, Point(rightLayer->getPositionX()-rightLayer->getContentSize().width, rightLayer->getPositionY()));
        //    CCCallFunc
        //    作用：创建一个回调动作（调用不带参数的回调方法）；
        //    参数1：目标动作
        //    参数2：目标回调函数
        //            CCCallFunc * funcall= CCCallFunc::create(this, callfunc_selector(GeneralsCard_Layer::callbackC));
        CallFunc* funcall = CallFunc::create(CC_CALLBACK_0(GeneralsCard_Layer::callbackC, this));
        FiniteTimeAction * seq = Sequence::create(move,funcall,NULL);
        rightLayer->runAction(seq);
    }else
    {
        GeneralsAwake_Layer* baseLayer=GeneralsAwake_Layer::create();
        baseLayer->setPosition(cardBg->getContentSize().width+cardBg->getPositionX()-10*sx-baseLayer->getContentSize().width,cardBg->getPositionY());
        this->addChild(baseLayer,1,TAG_RIGHTLAYER);
        MoveTo* move=MoveTo::create(0.2, Point(cardBg->getContentSize().width+cardBg->getPositionX()-20*sx, cardBg->getPositionY()));
        baseLayer->runAction(move);
    }
}
//----------------------------------------------右边列表----------------------------------------------//
void GeneralsCard_Layer::addRightList()
{
    const int num = 3;
    const char* pathList[num] = {IMG_PUBLIC_LABEL_GENERAL_VER,IMG_PUBLIC_LABEL_PROPERTY_VER,IMG_PUBLIC_LABEL_SKILL_VER};
    int functionList[num] = {DictFunctionEnumEquip,DictFunctionEnumHeroProp,DictFunctionEnumHeroSkill};
    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_VERTICAL, -15, CC_CALLBACK_1(GeneralsCard_Layer::onComboBoxBtnClick, this));
    for (int i = 0; i<num; i++)
    {
//        if(FunctionOpenManager::getInstance()->functionIsOpened(functionList[num-i - 1]))
        {
            boxBtn->addBtn(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE,IMG_PUBLIC_COMBOBOX_BTNCHOSE, pathList[num-i -1],true,functionList[num-i -1]);
        }
    }
    

    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumExpTag, boxBtn->getButtonByTag(DictFunctionEnumHeroPrestige));
    PublicShowUI::setTargetScale(boxBtn);
    boxBtn->setPosition(this->getContentSize().width-boxBtn->getContentSize().width-10*sx,(this->getContentSize().height-boxBtn->getContentSize().height)/2);
    this->addChild(boxBtn,3,TAG_RIGHTLIST);
    

    
}
void GeneralsCard_Layer::onComboBoxBtnClick(Ref* psender)
{
    Node* sp=(Node*)psender;
    int tag=sp->getTag();

    chooseId=tag;
    switch (tag) {
        case DictFunctionEnumHeroQuality:
            this->addAwake();
            
            break;
        case DictFunctionEnumHeroPrestige:
            if(_valueId != DictFunctionEnumHeroPrestige)
            {
                _valueId=DictFunctionEnumHeroPrestige;
                NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumExpTag);
            }
            this->addExperience();
            break;
        case DictFunctionEnumHeroSkill:
            this->addSkillLayer();
            break;
        case DictFunctionEnumHeroProp:
            this->addPropertyLayer();
            break;
        case DictFunctionEnumEquip:
            this->addBaseLayer();
            break;
        default:
            break;
    }
    _valueId=tag;
}
//----------------------------------------------左边列表----------------------------------------------//
void GeneralsCard_Layer::addLeftList(string sortMode)
{
    if (leftHeadList) {
        leftHeadList->removeChildByTag(TAG_LEFTLIST);
        leftHeadList=NULL;
    }
    CardPropertyData* propData = CardDataManager::getInstance()->getPresentData();
    if(propData)
    {
        leftHeadList = HeroListBar_Layer::create(propData->heroId,sortMode);
    }
    else
    {
         leftHeadList = HeroListBar_Layer::create(-1,sortMode);
    }
   
    leftHeadList->setAnchorPoint(Point::ZERO);
    leftHeadList->setPositionX(VisibleRect::left().x);
    leftHeadList->setPositionY(VisibleRect::center().y - leftHeadList->getContentSize().height/2-42*sx);
    this->addChild(leftHeadList,3,TAG_LEFTLIST);
}
void GeneralsCard_Layer::onBackClick(Ref* pSender)
{
    Generals_Layer::show(SCENE_TAG_MAINUI);
}
//---------------------------------------------------服务器部分----------------------------------------------//
void GeneralsCard_Layer::requestHeroMsg(int _id)
{
    GeneralsHeroInfoMsg* msg = new GeneralsHeroInfoMsg(_id);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void GeneralsCard_Layer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    
    if(message->messageID == SCENSE_CLIENT_HERO_HeroInfoPageResp)
    {
        int combatChange = heroData->combatPower;;
        int heroID = heroData->heroId;
        int level = heroData->level;
        heroData->heroId=message->byteStream->getInt();
        heroData->heroDictId=message->byteStream->getInt();
        heroData->heroName=message->byteStream->getUTF8();
        heroData->level=message->byteStream->getShort();
        heroData->levelMax=message->byteStream->getShort();
        heroData->quality=message->byteStream->getByte();
        heroData->prestige=message->byteStream->getShort();//声望改成了星级
        heroData->leadership=message->byteStream->getInt();
        heroData->combatPower=message->byteStream->getInt();
        heroData->prestigeStatus = message->byteStream->getByte();
        heroData->heroExperience=message->byteStream->getInt();
        heroData->heroMaxExperience=message->byteStream->getInt();
        heroData->heroForce=message->byteStream->getByte();

        heroData->freeExp = message->byteStream->getInt();//		int	Y	当前武将池中可用经验
        heroData->nextStepExp = message->byteStream->getInt();//		int	Y	下一步需要经验，点击一下升级按钮，从武将经验池消耗多少经验放到经验条上
        heroData->nextLevelExp = message->byteStream->getInt();//		int	Y	升级到下个等级需要的经验
  
        this->updateCreateLayer();
     
        if(combatChange && heroID == heroData->heroId && heroID != 0)
        {
            onCombatChange(heroData->combatPower - combatChange);
            
            if(level > 0 && level < heroData->level)
            {
                experEffect(true);
                broadMsg(CUSTOM_UPDATE_HEROBASEPAGEMSG,__Integer::create(0));
            }
        }
       
            
    }
    else if(message->messageID == SCENSE_CLIENT_HERO_HeroAddExpResp)
    {
        ExperBol = true;
        int level = message->byteStream->getInt();
        requestHeroMsg(heroData->heroId);
        this->stopActionByTag(TAG_LEVELUPDELAY);
        if(_levelUpDelayTime <= .25)
        {
            _levelUpDelayTime = .25;
        }
        else
        {
            _levelUpDelayTime -= .01;
        }
        if(this->levelUpisPressed)
        {
            DelayTime* delayTime = DelayTime::create(_levelUpDelayTime);
            CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(GeneralsCard_Layer::requestLevelUpMsg, this));
            Sequence* sequence = Sequence::create(delayTime,callBack, NULL);
            sequence->setTag(TAG_LEVELUPDELAY);
            this->runAction(sequence);
        }
//        CustomButton* btn = (CustomButton*)this->getChildByTag(TAG_CARDBG)->getChildByTag(TAG_LEVELUPBTN);
//        if (btn) {
//            PublicShowUI::setDot(btn, Point::ZERO, false,DictFunctionEnumHeroPrestige);
//        }
 
    }
    
}
void GeneralsCard_Layer::onCombatChange(int value)//战力变化
{
     Node* cardBg = this->getChildByTag(TAG_CARDBG);
    Point fromCp = cardBg->getPosition();
    fromCp.x  += cardBg->getContentSize().width/2;
    Point topCp = fromCp;
    string content = "";
    int colorFlag = 0;
    if(value > 0)
    {
        fromCp.y = fromCp.y + cardBg->getContentSize().height/2;
        topCp.y = fromCp.y + 150 * GlobalInfo::getInstance()->screenScaleY;
        content = PublicShowUI::numberToString(value);
        colorFlag = NoticeManager::COLOR_GREEN;
        content = "战力+" + content;
    }
    else if(value < 0)
    {
        fromCp.y = fromCp.y + cardBg->getContentSize().height/2 + 150 * GlobalInfo::getInstance()->screenScaleY;
        topCp.y = fromCp.y - 150 * GlobalInfo::getInstance()->screenScaleY;
        content = PublicShowUI::numberToString(abs(value));
        colorFlag = NoticeManager::COLOR_RED;
        content = "战力-" + content;
    }
    if(value != 0)
    {
    
        NoticeManager::getInstance()->showNotice(content.c_str(), colorFlag, fromCp, topCp,48,false);
    }
}
//-------------------------------------------------------------历练特效-------------------------------------------------------//
void GeneralsCard_Layer::experEffect(bool levelUP)
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* rightLayer=(Sprite*)this->getChildByTag(TAG_RIGHTLAYER);
    rightLayer->setLocalZOrder(11);
    
    Sprite* chooseCard=(Sprite*)this->getChildByTag(TAG_CHOOSECARD);
    Sprite* cardBg=(Sprite*)this->getChildByTag(TAG_CARDBG);
    if (cardBg) {
        cardBg->setVisible(true);
    }
    if (chooseCard) {
        chooseCard->setVisible(false);
    }
    //获取经验条的 往返几次的动作
    int len = 0;
    if(levelUP)
    {
        //特效
        CommonEffect* commonEffect = CommonEffect::create("lilianrenwushenji",false,true);
        commonEffect->setAnchorPoint(Point(0.5,0.5));
        commonEffect->setPosition(cardBg->getContentSize().width / sx /2+100,cardBg->getContentSize().height / sx /2+40);
        cardBg->addChild(commonEffect,12);
        
        len = 1;
    }
  
    
    //刷新经验条
    ProgressTimer* expProgress = (ProgressTimer*)cardBg->getChildByTag(TAG_PROGRESS);
    if (expProgress) {
        float percent =(float)heroData->heroExperience/(float)heroData->heroMaxExperience;
        expProgress->setPercentage(percent * 100);
    }
    Label* expLabel = (Label*)cardBg->getChildByTag(TAG_EXPLABEL);
    if(expLabel)
    {
        string str = PublicShowUI::numberToString(heroData->freeExp) ;//+ "/" + PublicShowUI::numberToString(heroData->heroMaxExperience);
        expLabel->setString(str);
    }
  
    Vector<ActionInterval*> *actionInterval = new Vector<ActionInterval*>();
    float percentage= expProgress->getPercentage();
    float bili= (float)heroData->heroExperience / (float)heroData->heroMaxExperience;
    float time = .5;
    for(int i=0;i<=len;i++)
    {
        float began = 0;
        float endel = 100;
        
        if(i==0)
        {
            began = percentage;//上次位置
        }
        if(i+1 > len)
        {
            time = 0;
            endel = bili*100;
        }
        ActionInterval* action_progress_from_to = ProgressFromTo::create(time, began, endel);
        actionInterval->pushBack(action_progress_from_to);
    }
    expProgress->setPercentage(percentage);
    //取经验条的动作
    if(actionInterval->size() > 0)
    {
        expProgress->runAction(Sequence::create(actionInterval->at(0),DelayTime::create(0.05),CallFuncN::create(CC_CALLBACK_1(GeneralsCard_Layer::deleteActionInterval, this, actionInterval)), NULL));
    }
    
    GeneralsExperience_Layer* experienceLayer=(GeneralsExperience_Layer*)this->getChildByTag(TAG_RIGHTLAYER);
    if (experienceLayer) {
        experienceLayer->headAction();
    }
    
}

//删除动画列表
void GeneralsCard_Layer::deleteActionInterval(Node* pSprite,Vector<ActionInterval*> *actionInterval)
{
    if(actionInterval->size() > 0)
    {
        actionInterval->erase(0);
    }
    
    if(actionInterval->size() > 0)
    {
        pSprite->runAction(Sequence::create(actionInterval->at(0),DelayTime::create(0.05),CallFuncN::create(CC_CALLBACK_1(GeneralsCard_Layer::deleteActionInterval, this, actionInterval)), NULL));
    }else
    {
        
    }
}
//---------------------------------------------------点击历练确定返回----------------------------------------------//
void GeneralsCard_Layer::handerClickExperience()
{
    
    if (leftHeadList) {
        leftHeadList->setUpdata();
    }
}
void GeneralsCard_Layer::handerClickAwake(EventCustom* msg)
{
    SoundManager::playEffectMusic(EFFECT_AWAKEN_SU);

    
    if (leftHeadList) {
        leftHeadList->setUpdata();
    }

}
//--------------------
void GeneralsCard_Layer::handerEffectEnd()
{
    Sprite* rightLayer=(Sprite*)this->getChildByTag(TAG_RIGHTLAYER);
    rightLayer->setLocalZOrder(1);
    EventCustom* msg=NULL;
    _valueId=DictFunctionEnumHeroPrestige;
    this->onChooseCard(msg);
    this->addExperience();
}
//--------------------穿上脱下装备数值改变
void GeneralsCard_Layer::putOnUpData(EventCustom* msg)
{
    if (heroData) {
        this->requestHeroMsg(heroData->heroId);
    }
    
}
//----------------------------------------

void GeneralsCard_Layer::addEventListener()
{

    addUserMsg(CUSTOM_CHOOSE_HERO_FUN,CC_CALLBACK_1(GeneralsCard_Layer::onChooseHeroCallBack, this));
    
    addUserMsg(CUSTOM_HEROPUTONEQUIP,CC_CALLBACK_1(GeneralsCard_Layer::putOnUpData, this));
    
    addUserMsg(CUSTOM_AWAKE_FUN,CC_CALLBACK_1(GeneralsCard_Layer::handerClickAwake, this));
//
    _eventDispatcher->addCustomEventListener(CUSTOM_START_FUN, CC_CALLBACK_0(GeneralsCard_Layer::handerClickExperience, this));
//
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroInfoPageResp).c_str(), CC_CALLBACK_1(GeneralsCard_Layer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroAddExpResp).c_str(), CC_CALLBACK_1(GeneralsCard_Layer::onMsgProcess, this));
}
void GeneralsCard_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
    _eventDispatcher->removeCustomEventListeners(CUSTOM_START_FUN);
}