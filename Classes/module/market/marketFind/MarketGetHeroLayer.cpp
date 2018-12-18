//
//  MarketGetHeroLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/7.
//
//

#include "MarketGetHeroLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../avatar/hero/Hero.h"
#include"../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../commonData/dictData/DictHeroQuality/DictHeroQualityManager.h"
#include "../../../commonData/dictData/DictHeroStar/DictHeroStarManager.h"
MarketGetHeroLayer::MarketGetHeroLayer()
:TAG_PATTICLE(1)
,TAG_CARDBG(2)
,TAG_PARTICLE2(3)
,TAG_PARTICLE3(4)
,TAG_PRESTLABEL(5)
,m_findData(NULL)
,m_callBack(NULL)
,isAnimationEnded(false)
{
    
}
MarketGetHeroLayer::~MarketGetHeroLayer()
{
    m_findData = NULL;
    m_callBack = NULL;
}


bool MarketGetHeroLayer::init(MarketFindResultData* finddata,std::function<void()> _callBack)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
      
        this->m_findData = finddata;
        this->isAnimation = false;
        this->m_callBack = _callBack;
        this->isClickClose = true;
        setBackground();
        
        setParticle();
        setGetCard();
        setParticle1();
        setChangeCard();
        bref = true;
    } while (false);
    return bref;
}

MarketGetHeroLayer* MarketGetHeroLayer::create(MarketFindResultData* finddata,std::function<void()> _callBack)
{
    MarketGetHeroLayer* list = new MarketGetHeroLayer();
    if(list && list->init(finddata,_callBack))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void MarketGetHeroLayer::show(MarketFindResultData* finddata,std::function<void()> _callBack )
{
    Scene* scene = Director::getInstance()->getRunningScene();
    MarketGetHeroLayer* layer = MarketGetHeroLayer::create(finddata,_callBack);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,SCENE_POPLAYER_ZORDER);
    
}
void MarketGetHeroLayer::onEnter()
{
    BaseLayer::onEnter();
   setClickEnabled(true);
}
void MarketGetHeroLayer::onExit()
{
    BaseLayer::onExit();
    this->setClickEnabled(false);
}
void MarketGetHeroLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
//    loadPerson();
    
}
void MarketGetHeroLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    clearResourcePerson();
}

void MarketGetHeroLayer::setBackground()
{

    Sprite* bg = Sprite::create(IMG_PUBLIC_MODULE_BG);
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg,0);
    PublicShowUI::setTargetScale(bg,true,true);
    this->setContentSize(bg->getContentSize());
   
}
void MarketGetHeroLayer::onRotateEnded()//旋转结束
{
    
    isAnimationEnded =true;
}
void MarketGetHeroLayer::setGetCard()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    isAnimationEnded = false;
    Sprite* cardBg=Sprite::create(IMG_GENERALS_CARD_BG);
    cardBg->setAnchorPoint(Point(0.5,0.5));
    cardBg->setScale(0.001 * sx);
    cardBg->setPosition(this->getContentSize().width/2-20,this->getContentSize().height/2);
    this->addChild(cardBg,6,TAG_CARDBG);
    
    DelayTime* delay = DelayTime::create(1.5);
    ActionInterval * scaleto1 = ScaleTo ::create(0.1, 1.3 * sx);
    ActionInterval * scaleto2 = ScaleTo ::create(0.1, 1 * sx);
//    ActionInterval * rotateto = RotateTo::create(0.5, 1080);
//    Spawn* spa = Spawn::create( scaleto1, rotateto, NULL);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(MarketGetHeroLayer::onRotateEnded, this));
    Sequence* seq = Sequence::create(delay,scaleto1,scaleto2,callBack, NULL);
    cardBg->runAction(seq);
    
    Sprite* cardbg2=Sprite::create(IMG_GENERALS_CARD_BG2);
    cardbg2->setAnchorPoint(Point::ZERO);
    cardbg2->setPosition(0,0);
    cardBg->addChild(cardbg2,1);
    
    Sprite* cardBox=Sprite::create(IMG_GENERALS_CARD_BOX2);
    cardBox->setAnchorPoint(Point::ZERO);
    cardBox->setPosition(0,0);
    cardBg->addChild(cardBox,2);
    
    //卡牌品质框
    char stt[100]="";
    int quality=m_findData->quality;
    quality=quality==0?1:quality;
    sprintf(stt,IMG_PUBLIC_HEADBIGFRAME,quality);
    Sprite* headBox=Sprite::create(stt);
    headBox->setAnchorPoint(Point::ZERO);
    cardBg->addChild(headBox,3);
    //卡牌
    DictHero* dictHero = DictHeroManager::getInstance()->getData(m_findData->dictId);
    if(dictHero)
    {
        const char* path  = PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH,dictHero->halfbodyrResource.c_str());
        Sprite* tempCard=Sprite::create(path);
        tempCard->setAnchorPoint(Point::ZERO);
        tempCard->setPosition(-50,0);
        cardBg->addChild(tempCard,4);
    }
    
//    sprintf(stt,IMG_GENERALS_CARD_TEMPCARD,3);
//    Sprite* tempCard=Sprite::create(stt);
//    tempCard->setAnchorPoint(Point::ZERO);
//    tempCard->setPosition(-50,0);
//    cardBg->addChild(tempCard,4);
    //卡牌下层
    Sprite* cardBox2=Sprite::create(IMG_GENERALS_CARD_NEWHALFBOX);
    cardBox2->setAnchorPoint(Point::ZERO);
    cardBox2->setPosition(0,5);
    cardBg->addChild(cardBox2,5);
    //势力范围
    int typeNum =  DictHeroManager::getInstance()->getData(m_findData->dictId)->attackType;
    if (typeNum<1) {
        typeNum = 1;
    }
    sprintf(stt,IMG_PUBLIC_HEROINFO_ATTACTTYPE,typeNum);
    Sprite* forceSprite=Sprite::create(stt);
    forceSprite->setAnchorPoint(Point::ZERO);
    forceSprite->setPosition(43,410);
    cardBg->addChild(forceSprite,7);
    //卡牌名字b
    sprintf(stt,IMG_PUBLIC_HEADNAMEBG,quality);
    Sprite* headNameBg=Sprite::create(stt);
    headNameBg->setAnchorPoint(Point::ZERO);
    headNameBg->setPosition(40,112);
    cardBg->addChild(headNameBg,7);
    //名字
    
    string str=this->m_findData->name;
    DictHeroQuality* data =DictHeroQualityManager::getInstance()->getData(quality);
    if (data) {
        str=data->name+"  "+this->m_findData->name;
    }
    Label* nameLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),22,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
//    nameLabel->setAlignment(TextHAlignment::CENTER);
    nameLabel->setPosition((cardBg->getContentSize().width-nameLabel->getContentSize().width)/2,188);
    cardBg->addChild(nameLabel,8);
    
    
    //星级
    Node* starSpr = Node::create();
    starSpr->setAnchorPoint(Point::ZERO);
    cardBg->addChild(starSpr,6,TAG_PRESTLABEL);
    starSpr->setPosition(170, 125);
    updateStarLevel();
    
    //zhanli
    string leadStr = StringUtils::format("%d",m_findData->combatPower);
    Label* leadLabel = PublicShowUI::getLabel(leadStr.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),20,false,false);
    leadLabel->setAnchorPoint(Point(0.5,0.5));
    leadLabel->setPosition(182,105);
    cardBg->addChild(leadLabel,10);
    //领导力
    string militaryStr = StringUtils::format("%d",m_findData->leaderShip);
    Label* militaryLabel = PublicShowUI::getLabel(militaryStr.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),20,false,false);
    militaryLabel->setAnchorPoint(Point(0.5,0.5));
    militaryLabel->setPosition(315,105);
    cardBg->addChild(militaryLabel,10);
    //等级
    int count = this->m_findData->level;
    string levelCard = StringUtils::format("%d",count);
    Label* levelLabel = PublicShowUI::getLabel(levelCard.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),20,false,false);
    levelLabel->setAnchorPoint(Point::ZERO);
    levelLabel->setPosition(142,50);
    cardBg->addChild(levelLabel,10);
    
    
    Sprite* tittleBg = Sprite::create(IMG_GENERALS_CARD_TITTLEBG);
    tittleBg->setAnchorPoint(Point::ZERO);
    cardBg->addChild(tittleBg,10);
    tittleBg->setPosition(180,30);
    
    
    DictHero* hero = DictHeroManager::getInstance()->getData(m_findData->dictId);
    if (hero) {
        float percentatact = hero->attackEvaluate;
        float percentDefent = hero->defenseEvaluate ;
        float percentEvaluate = hero->techniquesEvaluate ;
        
        //攻击
        Sprite* spr = Sprite::create(IMG_GENERALS_CARD_ATTACT);
        spr->setAnchorPoint(Point::ZERO);
        ProgressTimer* progressTimer = ProgressTimer::create(spr);
        progressTimer->setType(ProgressTimer::Type::BAR);
        progressTimer->setMidpoint(Point(0,1));
        progressTimer->setBarChangeRate(Point(1,0));
        progressTimer->setAnchorPoint(Point::ZERO);
        progressTimer->setPosition(40,43);
        tittleBg->addChild(progressTimer,5);
        progressTimer->setPercentage(percentatact);
        
        //防御
        Sprite* spr2 = Sprite::create(IMG_GENERALS_CARD_DEFENT);
        spr2->setAnchorPoint(Point::ZERO);
        ProgressTimer* progressTimer2 = ProgressTimer::create(spr2);
        progressTimer2->setType(ProgressTimer::Type::BAR);
        progressTimer2->setMidpoint(Point(0,1));
        progressTimer2->setBarChangeRate(Point(1,0));
        progressTimer2->setAnchorPoint(Point::ZERO);
        progressTimer2->setPosition(40,23);
        tittleBg->addChild(progressTimer2,5);
        progressTimer2->setPercentage(percentDefent);
        
        //生命
        Sprite* spr3 = Sprite::create(IMG_GENERALS_CARD_ALIVE);
        spr3->setAnchorPoint(Point::ZERO);
        ProgressTimer* progressTimer3 = ProgressTimer::create(spr3);
        progressTimer3->setType(ProgressTimer::Type::BAR);
        progressTimer3->setMidpoint(Point(0,1));
        progressTimer3->setBarChangeRate(Point(1,0));
        progressTimer3->setAnchorPoint(Point::ZERO);
        progressTimer3->setPosition(40,5);
        tittleBg->addChild(progressTimer3,5);
        progressTimer3->setPercentage(percentEvaluate);
    }

    
    
    if(m_findData->heroId == 0  )
    {
        
    }

}
void MarketGetHeroLayer::updateStarLevel()
{
    if(!m_findData)
    {
        return;
    }
    Node* cardBg = this->getChildByTag(TAG_CARDBG);
    Node* starLevel = cardBg->getChildByTag(TAG_PRESTLABEL);
    starLevel->removeAllChildren();
    Sprite* star = NULL;
    for(int i = 0; i < this->m_findData ->prestige; i++)
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
        starLevel->setPositionX((cardBg->getContentSize().width  -size.width)/2 + 6);
    }
    
}

void MarketGetHeroLayer::setParticle()//卡牌特效
{
    // 连接该骨骼动画的资源
    ArmatureDataManager::getInstance()->addArmatureFileInfo(AVATAR_MARKET_KAIPAIGUANXIAN);
    Armature* armature = Armature::create("kapaigusngxian");
    armature->getAnimation()->playWithIndex(0);
    armature->setAnchorPoint(Point(.5,.5));
    PublicShowUI::setTargetScale(armature,false,false);
    armature->setScale(2*GlobalInfo::getInstance()->screenScaleX);
    armature->setPosition(this->getContentSize().width/2,this->getContentSize().height/2);
    this->addChild(armature,7,TAG_PATTICLE);
    
    DelayTime* delay = DelayTime::create(1.5);
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(MarketGetHeroLayer::setclearPatticle, this));
    this->runAction(Sequence::create(delay,callback, NULL));
}

void MarketGetHeroLayer::setParticle1()
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo(AVATAR_MARKET_KAIPAIGUANQIU);
    Armature* armature2 = Armature::create("choukapai");
    armature2->getAnimation()->playWithIndex(0);
    armature2->setAnchorPoint(Point(0.5,0.5));
    armature2->setScale(GlobalInfo::getInstance()->screenScaleX * .001);
    armature2->setPosition(this->getContentSize().width/2-15*GlobalInfo::getInstance()->screenScaleX,this->getContentSize().height/2);
    this->addChild(armature2,5,TAG_PARTICLE3);
    
    DelayTime* delay = DelayTime::create(1.5);
    ActionInterval * scaleto = ScaleTo ::create(0, 1 * GlobalInfo::getInstance()->screenScaleX);
    DelayTime* delay2 = DelayTime::create(1.5);
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(MarketGetHeroLayer::setclearPatticle2, this));
    Sequence* seq = Sequence::create(delay, scaleto,delay2,callback, NULL);
    armature2->runAction(seq);
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo(AVATAR_MARKET_KAIPAIGUANQUAN);
    Armature* armature3 = Armature::create("choukapaiguangquan");
    armature3->getAnimation()->playWithIndex(0);
    armature3->setAnchorPoint(Point(0.5,0.5));
    armature3->setScale(GlobalInfo::getInstance()->screenScaleX * .001);
    armature3->setPosition(this->getContentSize().width/2-15*GlobalInfo::getInstance()->screenScaleX,this->getContentSize().height/2);
    this->addChild(armature3,8,TAG_PARTICLE2);
    
    DelayTime* delay11 = DelayTime::create(1.4);
    ActionInterval * scaleto11 = ScaleTo ::create(0, 1 * GlobalInfo::getInstance()->screenScaleX);
    DelayTime* delay22 = DelayTime::create(0.3);
    CallFunc* callback11 = CallFunc::create(CC_CALLBACK_0(MarketGetHeroLayer::setclearPatticle2, this));
    Sequence* seq11 = Sequence::create(delay11, scaleto11,delay22,callback11, NULL);
    armature3->runAction(seq11);

}

void MarketGetHeroLayer::setclearPatticle()
{
    this->removeChildByTag(TAG_PATTICLE);
    
}
void MarketGetHeroLayer::setclearPatticle2()
{
    this->removeChildByTag(TAG_PARTICLE2);
}
void MarketGetHeroLayer::setclearPatticle3()
{
    this->removeChildByTag(TAG_PARTICLE3);
    Sprite* cardBg=(Sprite*)this->getChildByTag(TAG_CARDBG);
    
    DictHeroStar* data = DictHeroStarManager::getInstance()->getData(m_findData->prestige);
    
    string str = StringUtils::format("已拥有此武将，%d星武将转化为%d个武将碎片\n          武将碎片可以用于武将升星",m_findData->prestige,data->toBook) ;
    Label* label = PublicShowUI::getLabelNumber(str.c_str(), PublicShowUI::getColor3b(COLOR_WRITE_DEEP), 22, false, false);
    label->setMaxLineWidth(440);
    label->setPosition(cardBg->getPositionX(),cardBg->getPositionY()-cardBg->getContentSize().height/2);
    this->addChild(label,10);
}
void MarketGetHeroLayer::setChangeCard()
{
    if (m_findData->heroId == 0) {
        Sprite* cardBg=(Sprite*)this->getChildByTag(TAG_CARDBG);
        DelayTime* time = DelayTime::create(2);
        ScaleTo* scale = ScaleTo::create(.2, .7);
        CallFunc* callback = CallFunc::create(CC_CALLBACK_0(MarketGetHeroLayer::setclearPatticle3, this));
        cardBg->runAction(Sequence::create(time,callback,scale, NULL) );
    }
}
void MarketGetHeroLayer::loadPerson()
{
    int dict = this->m_findData->dictId;
    DictHero* dictHero = DictHeroManager::getInstance()->getData(dict);
    if(dictHero)
    {
        const char* path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictHero->resource.c_str());
        log("path=%s",path);
        ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(MarketGetHeroLayer::onDataLoaded));
    }
}
void MarketGetHeroLayer::onDataLoaded(float percent)
{
    log("perdent==%f",percent);
    if(percent >= 1)
    {
        Sprite* cardBg=(Sprite*)this->getChildByTag(TAG_CARDBG);
        if (cardBg) {
            Hero* cardHero=Hero::create(m_findData->dictId);
            cardHero->setScale(0.5);
            cardHero->setPosition(108, 120);
            cardBg->addChild(cardHero,10);

        }
    }
}

void MarketGetHeroLayer::clearResourcePerson()//清除人物资源
{
    const char* path = NULL;
    int dict = m_findData->dictId;
    DictHero* dictHero = DictHeroManager::getInstance()->getData(dict);
    if(dictHero)
    {
        path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictHero->resource.c_str());
        ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
    }
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("");
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    ArmatureDataManager::destroyInstance();
    
}
bool MarketGetHeroLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    return  true;
}
void MarketGetHeroLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    
}
void MarketGetHeroLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    backScene();
}
void MarketGetHeroLayer::backScene()
{
    if(!isAnimationEnded)
    {
        return;
    }
    if(this->m_callBack)
    {
        this->m_callBack();
    }
    this->removeFromParent();
}

