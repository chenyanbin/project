//
//  HeroHeadListLayer.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/7/8.
//
//

#include "HeroHeadListLayer.h"
#include "../../../common/ImagePath.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../common/GameConfig.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../../common/GraySprite/GraySprite.h"
HeroHeadListLayer* HeroHeadListLayer::_instance = NULL;
HeroHeadListLayer::HeroHeadListLayer()
:heroList(NULL)
,m_isClickEnable(true)
,m_totalBlood(0)
,m_curBlood(0)
,bloodProgress(NULL)
,headContainer(NULL)
,m_bottleLabel(NULL)
,TAG_BOTTLE(1)
,TAG_BOTTLEEFFECT(2)
,TAG_PROGRESSTXT(3)
,m_bottleCount(0)
,headEffect(NULL)
{
    heroList = new Vector<Hero*>();
    headContainer = Node::create();
    headContainer->setAnchorPoint(Point::ZERO);
    this->addChild(headContainer,2);
    headEffect = CommonEffect::create("jiaoseqiehuantouxiangkuang");
    headEffect->setAnchorPoint(Point::ZERO);
    headEffect->retain();
    this->addChild(headEffect,4);
    headEffect->setVisible(false);

}
HeroHeadListLayer::~HeroHeadListLayer()
{
    CC_SAFE_RELEASE_NULL(headEffect);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumClickFightAvatar2);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumWaterButton);
    heroList->clear();
    CC_SAFE_DELETE(heroList);
    heroList = NULL;
    _instance = NULL;
}

HeroHeadListLayer* HeroHeadListLayer::getInstance()
{
    if(!_instance)
    {
        _instance = new HeroHeadListLayer();
        _instance->autorelease();
    }
    return _instance;
}
void HeroHeadListLayer::updateMainHero(Hero* hero)
{
      HeroHead* heroHead = (HeroHead*)headContainer->getChildByTag(hero->getUID());
    if(heroHead)
    {
        this->m_curBlood = hero->getAvatarProp()->health;
        this->m_totalBlood = hero->getBaseAvatarProp()->health;
        this->updateList(heroHead);
        
    }
}
void HeroHeadListLayer::addHero(Hero* hero)
{
    HeroHead* head = HeroHead::create(hero);
//    head->setAnchorPoint(Point::ZERO);
    head->setAnchorPoint(Point(.5,.5));
    if(hero->_isMainHero)
    {
        this->heroList->insert(0, hero);
        updateList(head);
        setHeroBlood();
        return;
    }
    else
    {
        this->heroList->pushBack(hero);
    }
    addHead(head);
    
}
void HeroHeadListLayer::setHeroBlood()
{
    if(this->bloodProgress)
    {
        return;
    }
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* bloodBg = Sprite::create(IMG_BATTLE_HEROBLOODBG);
    bloodBg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bloodBg);
    bloodBg->setPosition(94 * sx , 95 * sx - bloodBg->getContentSize().height);
    this->addChild(bloodBg,0);
    
    Sprite* blood = Sprite::create(IMG_BATTLE_HEROBLOOD);
    blood->setAnchorPoint(Point::ZERO);
    bloodProgress = ProgressTimer::create(blood);
    bloodProgress->setType(ProgressTimer::Type::BAR);
    bloodProgress->setMidpoint(Point(0,1));
    bloodProgress->setBarChangeRate(Point(1,0));

    bloodProgress->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bloodProgress);
    bloodProgress->setPosition(bloodBg->getPositionX() + (bloodBg->getContentSize().width - bloodProgress->getContentSize().width)/2,bloodBg->getPositionY() + bloodBg->getContentSize().height - bloodProgress->getContentSize().height);
    this->addChild(bloodProgress,1);
    bloodProgress->setPercentage(100);
    
//    TouchSprite* bloodBottle = TouchSprite::createWithPic(IMG_ICON_BLOODBOTTLE, this, callfuncN_selector(HeroHeadListLayer::onBottleClick));
//    bloodBottle->isButtonMode = true;
//    bloodBottle->setAnchorPoint(Point::ZERO);
//    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumWaterButton, bloodBottle);
//    Sprite* cdSprite = Sprite::create(IMG_ICON_BLOODBOTTLE);
//    cdSprite->setColor(Color3B::BLACK);
//    cdSprite->setOpacity(225);
//    ProgressTimer* pt = ProgressTimer::create(cdSprite);
//    //转圈的CD实现
//    pt->setPosition(bloodBottle->getContentSize().width/2, bloodBottle->getContentSize().height/2);
//    pt->setType(ProgressTimer::Type::RADIAL);
//    bloodBottle->addChild(pt,2,1);
//    pt->setPercentage(0);
//    
//    PublicShowUI::setTargetScale(bloodBottle);
//    bloodBottle->setPosition(bloodBg->getPositionX() + bloodBg->getContentSize().width - bloodBottle->getContentSize().width - 90 * sx, 0);
//    this->addChild(bloodBottle,4,TAG_BOTTLE);

    
}
void HeroHeadListLayer::onBottleClick(Node* pSender)
{

    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumWaterButton);

     PublicShowUI::broadUserMsg(CUSTOM_RESET_AVATAR_ACTION, NULL);
    ProgressTimer* pt = (ProgressTimer*)pSender->getChildByTag(1);
    if(pt->getPercentage() > 0)
    {
        NoticeManager::getInstance()->showNotice("血瓶使用中。。请等待！",NoticeManager::COLOR_RED);
        return;
    }
    if(m_bottleCount > 0)
    {
        PublicShowUI::broadUserMsg(CUSTOM_BATTLE_EAT_BLOODBOTTLE, NULL);
        
        pt->runAction(Sequence::create(ProgressFromTo::create(15, 100, 0),NULL));
    }
    else
    {
        NoticeManager::getInstance()->showNotice("血瓶不足，请到商城购买！",NoticeManager::COLOR_RED);
    }
   
 
}
void HeroHeadListLayer::showBloodEffect()
{
    if(this->m_bottleCount <= 0)
    {
        return;
    }
    Armature* armature = (Armature*)this->getChildByTag(TAG_BOTTLEEFFECT);
    if(armature)
    {
        return;
    }
    Node* blood = this->getChildByTag(TAG_BOTTLE);
   
    armature= Armature::create(AVATAR_BLOOD_EFFECT);
//    armature->setAnchorPoint(Point::ZERO);
    armature->setScale(.5 * GlobalInfo::getInstance()->screenScaleX);
    armature->getAnimation()->playWithIndex(0);
    armature->setPosition(blood->getPosition().x + blood->getContentSize().width/2 ,blood->getPositionY() + blood->getContentSize().height/2);
    this->addChild(armature,5,TAG_BOTTLEEFFECT);

   
}
void HeroHeadListLayer::hideBloodEffect()
{
    Armature* armature = (Armature*)this->getChildByTag(TAG_BOTTLEEFFECT);
    if(armature)
    {
        armature->pause();
        armature->getAnimation()->stop();
        armature->removeFromParent();
   
    }
}
void HeroHeadListLayer::addBuff(int heroID,int buffID)
{
     HeroHead* heroHead = (HeroHead*)headContainer->getChildByTag(heroID);
    if(heroHead)
    {
        heroHead->addBuff(buffID);
    }
}
void HeroHeadListLayer::setBlood(float _curBlood,float _totalBlood)
{
    if(_curBlood < 0)
    {
        _curBlood = 0;
    }
    this->m_curBlood = _curBlood;
    this->m_totalBlood = _totalBlood;
    
    if(bloodProgress)
    {
        bloodProgress->stopAllActions();
        float percent = m_curBlood / m_totalBlood * 100;
        ProgressFromTo* progress = ProgressFromTo::create(.2, bloodProgress->getPercentage(),percent );
        bloodProgress->runAction(progress);
        updateProgressText(percent);
    }
}
void HeroHeadListLayer::onReborn()
{
    for(Hero* hero : *heroList)
    {
        HeroHead* heroHead = (HeroHead*)headContainer->getChildByTag(hero->getUID());
        if(heroHead)
        {
            heroHead->onReborn();
        }
    }
}
void HeroHeadListLayer::resetBlood()
{
//    HeroHead* heroHead = (HeroHead*)headContainer->getChildByTag(hero->getUID());
//    if(heroHead)
//    {
//        this->updateList(heroHead);
//    }
    for(Hero* hero : *heroList)
    {
         HeroHead* heroHead = (HeroHead*)headContainer->getChildByTag(hero->getUID());
         if(heroHead)
         {
             heroHead->resetBlood();
         }
    }
}
void HeroHeadListLayer::updateBloodbottle(int count)//更新血瓶
{
    m_bottleCount = count;
    string str = "X" + PublicShowUI::numberToString(count);
    
    if(m_bottleLabel)
    {
        m_bottleLabel->setString(str);
    }
    else
    {
      
        Node* bottle = this->getChildByTag(TAG_BOTTLE);
        if(bottle)
        {
            float sx = GlobalInfo::getInstance()->screenScaleX;
            m_bottleLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_YELLOW_WHITE),18,false,true);
            m_bottleLabel->setAnchorPoint(Point::ZERO);
            m_bottleLabel->setPosition(bottle->getPositionX() + bottle->getContentSize().width + 12 * sx, bottle->getPositionY() + (bottle->getContentSize().height - m_bottleLabel->getContentSize().height)/2 + 10 * sx);
            this->addChild(m_bottleLabel, 5);
        }
    
    }
}
void HeroHeadListLayer::clear()
{
    heroList->clear();
    headContainer->removeAllChildren();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumClickFightAvatar2);
}
void HeroHeadListLayer::removeHero(Hero* hero)
{
    heroList->eraseObject(hero);

}
void HeroHeadListLayer::setClickEnable(bool enable)
{
    m_isClickEnable = enable;
}
bool HeroHeadListLayer::getClickEnable()
{
    return m_isClickEnable;
}
void HeroHeadListLayer::updateList(HeroHead* mainHead)
{
    this->heroList->eraseObject(mainHead->getHero());
    
    this->heroList->insert(0, mainHead->getHero());
    mainHead->removeAllChildren();
    headContainer->removeAllChildren();
   
    for (auto hero : * heroList) {
        HeroHead* head = HeroHead::create(hero);
//        head->setAnchorPoint(Point::ZERO);
        head->setAnchorPoint(Point(.5,.5));
        addHead(head);
    }
}
void HeroHeadListLayer::updateHeroPostion(HeroHead* mainHead)
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    this->heroList->eraseObject(mainHead->getHero());
    this->heroList->insert(0, mainHead->getHero());
    HeroHead* head = NULL;
    Hero* hero = NULL;
    for (int i = 0; i < heroList->size(); i++)
    {
        hero = heroList->at(i);
        head = (HeroHead*)headContainer->getChildByTag(hero->getUID());
        head->setAnchorPoint(Point(.5,.5));
        Size size = head->getContentSize();
      
        float _scale = i == 0 ? sx * .8 : sx * .6;
        size.setSize(size.width * _scale, size.height * _scale);
        head->runAction(ScaleTo::create(.3, _scale));
      
        if(head)
        {
            if(i == 0)
            {
                 head->setPosition(size.width / 2,size.height/2);
                head->setBloodVisible(false);
            }
            else
            {
                HeroHead* preHead = (HeroHead*)headContainer->getChildByTag(heroList->at(i-1)->getUID());
                
                head->setPositionX(preHead->getPositionX());
                head->setPositionY(preHead->getPositionY() -preHead->getContentSize().height * (i == 1 ? sx* .8 : sx * .6) / 2 - head->getContentSize().height * _scale / 2 - 10);
                 head->setBloodVisible(true);
                
            }
        }
    }
}
void HeroHeadListLayer::onHeroHurt(int heroUID,float damage)
{
   
//
    
    HeroHead* head = (HeroHead*)headContainer->getChildByTag(heroUID);
    if(head)
    {
        if(head->getHero()->_isMainHero)
        {
            this->m_curBlood =  head->getHero()->getAvatarProp()->health;
            if(m_curBlood <= 0)
            {
                m_curBlood = 0;
            }
            if(bloodProgress)
            {
                bloodProgress->stopAllActions();
                float percent = m_curBlood / head->getHero()->getBaseAvatarProp()->health * 100;
                ProgressFromTo* progress = ProgressFromTo::create(.2, bloodProgress->getPercentage(), percent);
                bloodProgress->runAction(progress);
                updateProgressText(percent);
            }
        }
   
        head->onHeroHurt();
    }
    else
    {
        log("lsdjklfL");
    }
}
void HeroHeadListLayer::onHeroAddBlood(int heroUID,float value)
{
    this->m_curBlood +=  abs(value);
    if(m_curBlood > m_totalBlood)
    {
        m_curBlood = m_totalBlood;
    }
    if(bloodProgress)
    {
        bloodProgress->stopAllActions();
        float percent = m_curBlood / m_totalBlood * 100;
        ProgressFromTo* progress = ProgressFromTo::create(.2, bloodProgress->getPercentage(), percent);
        bloodProgress->runAction(progress);
        updateProgressText(percent);
    }
    HeroHead* head = (HeroHead*)headContainer->getChildByTag(heroUID);
    if(head)
    {
        head->onHeroAddBlood(abs(value));
    }
    
}
void HeroHeadListLayer::updateProgressText(float percent)
{
    Label* label  = (Label*)this->getChildByTag(TAG_PROGRESSTXT);
    string str = PublicShowUI::numberToString((int)percent) + "%";
    if(label)
    {
        label->setString(str.c_str());
    }
    else
    {
        label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0xff3c00),20,false,false);
        this->addChild(label,4,TAG_PROGRESSTXT);
        label->setPosition(bloodProgress->getPositionX() + bloodProgress->getContentSize().width/2, bloodProgress->getPositionY()+ bloodProgress->getContentSize().height/2);
    }
//    if(label)
//    {
//        label->setString(PublicShowUI::numberToString(percent));
//    }
}
void HeroHeadListLayer::addHead(HeroHead* head)
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Size size = head->getContentSize();
    ssize_t childCount = headContainer->getChildrenCount();

    float _scale = childCount == 0 ? sx* .8 : sx * .6;
    head->setScale(_scale);

    size.setSize(size.width * _scale, size.height * _scale);

    
    if(childCount == 0)
    {
        head->setPosition(size.width / 2,size.height/2);
        if(headEffect)
        {
            
            float scaleX = head->getContentSize().width * _scale / headEffect->getContentSize().width * 1.6;
            headEffect->setScale(scaleX );
            headEffect->setVisible(true);

            headEffect->setPosition(head->getPositionX() - headEffect->getContentSize().width * scaleX / 2 - 11 , head->getPositionY() - headEffect->getContentSize().height * scaleX/2 );
  
        }
    }
    else
    {
        HeroHead* preHead = (HeroHead*)headContainer->getChildByTag(heroList->at(childCount-1)->getUID());
        
//         head->setPositionX(preHead->getPositionX() + (size.width - head->getContentSize().width)/2);
//         head->setPositionY(preHead->getPositionY() - size.height - 5);
        head->setPositionX(preHead->getPositionX() );

        head->setPositionY(preHead->getPositionY() -preHead->getContentSize().height * (childCount == 1 ? sx* .8 : sx * .6) / 2 - head->getContentSize().height * _scale / 2 - 10);
        
    }
    headContainer->addChild(head,(int)childCount,head->getHero()->getUID());
    
    if(childCount == 1)
    {
        GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumClickFightAvatar2);
        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumClickFightAvatar2, head);
    }

}
HeroHead::HeroHead()
:m_totalBlood(0)
,m_nowBlood(0)
,TAG_BLOOD_PROGRESS(1)
,TAG_BLACKMASK(2)
,TAG_HEAD(3)
,TAG_FORM(4)
,m_hero(NULL)
,buffContainer(NULL)
{
    
}
HeroHead::~HeroHead()
{
    CC_SAFE_RELEASE_NULL(m_hero);
}
bool HeroHead::init(Hero* hero)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Node::init());
        m_hero = hero;
        CC_SAFE_RETAIN(m_hero);
        m_totalBlood = hero->getBaseAvatarProp()->health;
        m_nowBlood = hero->getAvatarProp()->health;
        sethead();
        buffContainer = Node::create();
        buffContainer->setAnchorPoint(Point::ZERO);
        this->addChild(buffContainer,50);
        bref = true;
    } while (false);
    return bref;
}
HeroHead* HeroHead::create(Hero* hero)
{
    HeroHead* head = new HeroHead();
    if(head && head->init(hero))
    {
        head->autorelease();
        return head;
    }
    CC_SAFE_DELETE(head);
    head = NULL;
    return NULL;
}
Hero* HeroHead::getHero()
{
    return m_hero;
}
void HeroHead::addBuff(int buffID)
{
 
    DictBuff* dictBuff = DictBuffManager::getInstance()->getData(buffID);
    if(!dictBuff)
    {
        return;
    }
    if(!this->m_hero->hasBuffState(dictBuff->type))
    {
        return;
    }
    
    const char* path = PublicShowUI::getResImgPath(IMG_BUFF_ICON, dictBuff->iconResource.c_str());
    Sprite* icon = Sprite::create(path);
    if(!icon)
    {
        return;
    }
    this->removeBuff(dictBuff->type);
    Sprite* form = Sprite::create(IMG_BUFF_FORM);
    icon->setAnchorPoint(Point::ZERO);
    icon->addChild(form,3);
    form->setPosition(icon->getContentSize().width/2, icon->getContentSize().height/2);
    float _scale = .3/ this->getScale();
    icon->setScale(_scale);
    icon->setContentSize(icon->getContentSize() * _scale );
    
    
    icon->setPosition(buffContainer->getChildrenCount() * (icon->getContentSize().width + 5), 0);
    this->buffContainer->addChild(icon,1,dictBuff->type);
    
    
    DelayTime* delay = DelayTime::create((float)dictBuff->time);
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(HeroHead::removeBuff, this,dictBuff->type));
    icon->runAction(Sequence::create(delay,callback,NULL));
    
    buffContainer->setPosition(this->getContentSize().width, 0);

}
void HeroHead::removeBuff(int buffType)
{
    Node* icon = buffContainer->getChildByTag(buffType);
    if(icon)
    {
        icon->stopAllActions();
        buffContainer->removeChildByTag(buffType);
    }
}
void HeroHead::sethead()
{
    
    int quality = PublicShowUI::getColorIndexByQuality(DictItemTypeEnumItemHero,m_hero->getAvatarProp()->quality) ;

    
    char path[500] = "/0";
    sprintf(path,IMG_PUBLIC_HEROHEADFRAMEBG,quality);
    Sprite* bg = Sprite::create(path);
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg,0);


    sprintf(path,IMG_PUBLIC_HEADTALENTFRAME,quality);
    Sprite* bgForm = Sprite::create(path);
    bgForm->setAnchorPoint(Point::ZERO);
    this->addChild(bgForm,5,TAG_FORM);
    bg->setPosition((bgForm->getContentSize().width - bg->getContentSize().width)/2, (bgForm->getContentSize().height - bg->getContentSize().height)/2);
    Size size = bgForm->getContentSize();
    this->setContentSize(size);
    
    
    string str = m_hero->getDictHero()->headResource;
    str = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH, str.c_str());
    TouchSprite* head = TouchSprite::createWithPic(str.c_str(), this, callfuncN_selector(HeroHead::onHeadTouch));
    if(head)
    {
        ((TouchSprite*)head)->isButtonMode = true;
        head->setPosition(bgForm->getContentSize().width/2, bgForm->getContentSize().height/2);
        this->addChild(head,2,TAG_HEAD);
        float _scale = (bg->getContentSize().width - 5) / head->getContentSize().width;
        head->setScale(_scale);
        
        if(this->getHero()->getAvatarProp()->health <= 0)
        {
           addBlackMask();
        }
    }
    Sprite* progressBg = Sprite::create(IMG_BATTLE_HEROHEADBLOODBG);
    progressBg->setAnchorPoint(Point::ZERO);
    this->addChild(progressBg,11,TAG_BLOOD_PROGRESS);
    progressBg->setScale(1.2);
    progressBg->setPosition((bgForm->getContentSize().width - progressBg->getContentSize().width * 1.2)/2 ,-progressBg->getContentSize().height);
    Sprite* blood = Sprite::create(IMG_BATTLE_HEROHEADBLOOD);
    blood->setAnchorPoint(Point::ZERO);
    
    
    ProgressTimer* pt = ProgressTimer::create(blood);
    pt->setType(ProgressTimer::Type::BAR);
    pt->setMidpoint(Point(0,1));
    pt->setBarChangeRate(Point(1,0));
    pt->setAnchorPoint(Point::ZERO);
    
    
    pt->setPosition((progressBg->getContentSize().width - pt->getContentSize().width)/2 ,(progressBg->getContentSize().height - pt->getContentSize().height)/2);
    pt->setPercentage(m_nowBlood / m_totalBlood * 100);

    progressBg->addChild(pt,12,TAG_BLOOD_PROGRESS);
    
    setBloodVisible(!m_hero->_isMainHero);
    
}
void HeroHead::setBloodVisible(bool visible)
{
    Node* progressBg = this->getChildByTag(TAG_BLOOD_PROGRESS);
    progressBg->setVisible(visible);
}
void HeroHead::hideServerLoading()
{
    Dialog::hideServerLoading();
}
void HeroHead::onHeadTouch(Node* target)
{
    if(NewPlayerGuild::getInstance()->getNowData() && NewPlayerGuild::getInstance()->getNowData()->id < 8)
    {
        return;
    }
    if(m_hero->getAvatarProp()->health <= 0)
    {
        return;
    }
    if(!HeroHeadListLayer::getInstance()->getClickEnable() && GlobalInfo::getInstance()->battleType != kBattleType_LoginBattle)
    {
        return;
    }
    if(m_hero->getActionState() == kActionStateWin)
    {
        return;
    }
//    Dialog::showServerLoading(3);
//    DelayTime* delay = DelayTime::create(1);
//    this->runAction(Sequence::create(delay,CallFunc::create(CC_CALLBACK_0(HeroHead::hideServerLoading, this)), NULL));
    
    PublicShowUI::broadUserMsg(CUSTOM_BATTLE_CHANGE_MAINHERO, this->m_hero);
    HeroHeadListLayer* layer = (HeroHeadListLayer*)this->getParent()->getParent();
    if(layer)
    {
    
        NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumClickFightAvatar2);
       
        layer->updateHeroPostion(this);
     
        
    }
}
void HeroHead::addBlackMask()
{
    if(this->getChildByTag(TAG_BLACKMASK))
    {
        return;
    }
    Node* head = this->getChildByTag(TAG_FORM);
    Size size =head->getContentSize();
    LayerColor* colorLayer = LayerColor::create(Color4B(0,0,0,170),size.width,size.height);
//    colorLayer->setPosition( -size.width/2,-size.height/2);
    
    this->addChild(colorLayer,10,TAG_BLACKMASK);
}
void HeroHead::onHeroHurt()
{
    this->m_nowBlood  = this->m_hero->getAvatarProp()->health;
    if(m_nowBlood <= 0)
    {
        m_nowBlood = 0;
    }
    Sprite* progressbg = (Sprite*)this->getChildByTag(TAG_BLOOD_PROGRESS);
    if(!progressbg)
    {
        return;
    }
    ProgressTimer* pt = (ProgressTimer*)progressbg->getChildByTag(TAG_BLOOD_PROGRESS);
    float percent = m_nowBlood / m_hero->getBaseAvatarProp()->health * 100;
    pt->stopAllActions();
    
    ProgressFromTo* progress = ProgressFromTo::create(.2, pt->getPercentage(), percent);
    pt->runAction(progress);
    if(m_nowBlood <= 0)
    {
        addBlackMask();
    }
}
void HeroHead::onHeroAddBlood(float value)
{
    this->m_nowBlood += value;

    Sprite* progressBg = (Sprite*)this->getChildByTag(TAG_BLOOD_PROGRESS);
    ProgressTimer* pt = (ProgressTimer*)progressBg->getChildByTag(TAG_BLOOD_PROGRESS);
    float percent = m_nowBlood / m_totalBlood * 100;
    pt->stopAllActions();
    
    ProgressFromTo* progress = ProgressFromTo::create(.2, pt->getPercentage(), percent);
    pt->runAction(progress);
    
    if(this->getChildByTag(TAG_BLACKMASK))
    {
        this->removeChildByTag(TAG_BLACKMASK);
    }
}
void HeroHead::resetBlood()
{
    if(m_nowBlood <= 0)
    {
        return;
    }
    float value = m_hero->getBaseAvatarProp()->health - m_nowBlood;;

    onHeroAddBlood(value);
}
void HeroHead::onReborn()//重生
{
     this->m_nowBlood = 0;
    m_totalBlood = m_hero->getBaseAvatarProp()->health;
    onHeroAddBlood(m_hero->getBaseAvatarProp()->health);
}