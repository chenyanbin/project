//
//  LimitCardLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/12/24.
//
//

#include "LimitCardLayer.h"
#include "../../common/TouchSprite/Button.h"
#include "LimitCardSkillLayer.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../message/Decoding/limittime/LimitTimeChoseCardMsg.hpp"
#include "../../message/Decoding/limittime/LimitTimeDetailMsg.hpp"
#include "../../common/Dialog/Dialog.h"
#include "../../commonData/dictData/DictSkill/DictSkillManager.h"
#include "../market/marketData/MarketFindResultDataManager.h"
#include "../market/marketFind/MarketGetEquipLayer.h"
#include "../market/marketFind/MarketGetHeroLayer.h"
#include "../market/marketJuxian/MarketGoodsLayer.h"
#include "../../commonData/dictData/DictHero/DictHeroManager.h"
LimitCardLayer::LimitCardLayer()
:sx(0)
,m_heroAttackType(0)
,m_heroName("")
,m_heroHp(0)
,m_herodefend(0)
,m_heroAttact(0)
,m_onecost(0)
,m_tencost(0)
,TAG_BTNONE(0)
,TAG_BTNTEN(1)
,m_skill1(0)
,m_skill2(0)
,m_skill3(0)
,m_skill4(0)
,m_activityStartTimes(0)
,m_activityEndTimes(0)
,m_iscloseScene(true)
{
   
}
LimitCardLayer::~LimitCardLayer()
{
   
}
void LimitCardLayer::onExit()
{
    BaseLayer::onExit();
}
void LimitCardLayer::onEnter()
{
    BaseLayer::onEnter();
    
}
void LimitCardLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void LimitCardLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
bool LimitCardLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;

        this->setBackground(IMG_LIMITCARD_BG);
        this->isAnimation = true;
        this->isClickClose=true;
        this->setClickEnabled(true);
        this->isShowGrayBg = true;
        this->createLayer();
        requestlimitCardMsg();
//        setItemPic();
        bref = true;
    } while (false);
    return bref;
}
LimitCardLayer* LimitCardLayer::create()
{
    LimitCardLayer* layer = new LimitCardLayer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void LimitCardLayer::show()
{
    LimitCardLayer* layer = LimitCardLayer::create();
    if(layer)
    {
        Scene* scene = Director::getInstance()->getRunningScene();
        layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2,VisibleRect::center().y - layer->getContentSize().height/2);
        scene->addChild(layer,SCENE_LAYER_ZORDER);
    }
}
void LimitCardLayer::createLayer()
{
    Sprite* layerbg = (Sprite*)this->getChildByTag(TAG_BG);
    
    
    //抽一次
    Button* btnone = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(LimitCardLayer::onClick, this));
    btnone->setAnchorPoint(Point::ZERO);
    btnone->setPosition(this->getContentSize().width/sx-btnone->getContentSize().width*2-240 ,20);
    layerbg->addChild(btnone,2,TAG_BTNONE);
    Sprite* ontWord = Sprite::create(IMG_LIMITCARD_ONETIME);
    ontWord->setAnchorPoint(Point::ZERO);
    ontWord->setPosition(Point(-10,0));
    btnone->addChild(ontWord,5);
    
    //抽十次
    Button* btnten = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(LimitCardLayer::onClick, this));
    btnten->setAnchorPoint(Point::ZERO);
    btnten->setPosition(btnone->getPositionX() + btnone->getContentSize().width+50,20);
    layerbg->addChild(btnten,2,TAG_BTNTEN);
    Sprite* tenword = Sprite::create(IMG_LIMITCARD_TENTIME);
    tenword->setAnchorPoint(Point::ZERO);
    tenword->setPosition(Point(-10,0));
    btnten->addChild(tenword,5);
    
    //伤害加成
//    Sprite* damage = Sprite::create(IMG_LIMITCARD_DENMAGEFIVE);
//    damage->setAnchorPoint(Point::ZERO);
//    damage->setPosition(this->getContentSize().width/sx/2-damage->getContentSize().width/2,this->getContentSize().height/sx/2-damage->getContentSize().height/2);
//    layerbg->addChild(damage,10);
    
    
    //技能查看
    Button* btnskill = Button::create(IMG_PUBLIC_BUTTON_FOUR_RED, IMG_PUBLIC_BUTTON_FOUR_RED, CC_CALLBACK_1(LimitCardLayer::onClickSkill, this));
    btnskill->setAnchorPoint(Point::ZERO);
    btnskill->setPosition(btnten->getPositionX() -100 ,btnten->getPositionY() + btnskill->getContentSize().height + 50);
    layerbg->addChild(btnskill);
    Sprite* skillWord = Sprite::create(IMG_LIMITCARD_SKILLSEE);
    skillWord->setAnchorPoint(Point::ZERO);
    skillWord->setPosition(Point::ZERO);
    btnskill->addChild(skillWord,5);
}
void LimitCardLayer::onClick(Ref* pSender)
{
    m_iscloseScene = false;
    Node* target = (Node*)pSender;
    switch (target->getTag()) {
        case 0:
            requestChoseCardMsg(1);
            break;
        case 1:
            requestChoseCardMsg(2);
            break;
        default:
            break; 
    }
}
void LimitCardLayer::onClickSkill(Ref* pSender)
{
     m_iscloseScene = false;
    LimitCardSkillLayer::show(m_skill1,m_skill2,m_skill3,m_skill4);
}
void LimitCardLayer::setItemPic(ValueVector &m_skillList)
{
    m_varlist = &m_skillList;
    Sprite* layerbg = (Sprite*)this->getChildByTag(TAG_BG);
    
    //开始时间
    struct tm *l=localtime(&m_activityStartTimes);
    char buf[128];
    snprintf(buf,sizeof(buf),"%02d.%02d/%02d:%02d",l->tm_mon+1,l->tm_mday,l->tm_hour,l->tm_min);
    string start(buf);
    start = start + " - ";
    Label* activityStartTimeslabel = PublicShowUI::getLabel(start.c_str(),PublicShowUI::getColor3b(COLOR_DEEP_RED),18,false,false);
    activityStartTimeslabel->setAnchorPoint(Point::ZERO);
    activityStartTimeslabel->setPosition(400,25);
    layerbg->addChild(activityStartTimeslabel,3);
    
    
    //结束时间
    l = localtime(&m_activityEndTimes);
    snprintf(buf,sizeof(buf),"%02d.%02d/%02d:%02d",l->tm_mon+1,l->tm_mday,l->tm_hour,l->tm_min);
    string end(buf);
    Label* endTimeslabel = PublicShowUI::getLabel(end.c_str(),PublicShowUI::getColor3b(COLOR_DEEP_RED),18,false,false);
    endTimeslabel->setAnchorPoint(Point::ZERO);
    endTimeslabel->setPosition(activityStartTimeslabel->getPositionX()+activityStartTimeslabel->getContentSize().width,activityStartTimeslabel->getPositionY());
    layerbg->addChild(endTimeslabel,3);
    
    //攻击类型
    int typeNum =  m_heroAttackType;
    if (typeNum<1) {
        typeNum = 1;
    }
    char stt[100]="";
    sprintf(stt,IMG_PUBLIC_HEROINFO_ATTACTTYPE,typeNum);
    Sprite* forceSprite=Sprite::create(stt);
    forceSprite->setAnchorPoint(Point::ZERO);
    forceSprite->setPosition(570,370);
    layerbg->addChild(forceSprite,7);
    //名字
    string name = m_heroName;
    Label* namelabel = PublicShowUI::getLabel(name.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_WHITE),18,false,false);
    namelabel->setAnchorPoint(Point(Point::ZERO));
    layerbg->addChild(namelabel,2);
    namelabel->setPosition(650,400);
    
    //血量
    string bleedstr = StringUtils::format("%d",m_heroHp);
    Label* bleedlabel = PublicShowUI::getLabel(bleedstr.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),18,false,false);
    bleedlabel->setAnchorPoint(Point(Point::ZERO));
    layerbg->addChild(bleedlabel,2);
    bleedlabel->setPosition(680,335);
    
    //防御
    string defundstr = StringUtils::format("%d",m_herodefend);
    Label* defandlabel = PublicShowUI::getLabel(defundstr.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),18,false,false);
    defandlabel->setAnchorPoint(Point(Point::ZERO));
    layerbg->addChild(defandlabel,2);
    defandlabel->setPosition(820,335);
    
    //攻击
    string attactstr = StringUtils::format("%d",m_heroAttact);
    Label* attactlabel = PublicShowUI::getLabel(attactstr.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),18,false,false);
    attactlabel->setAnchorPoint(Point(Point::ZERO));
    layerbg->addChild(attactlabel,2);
    attactlabel->setPosition(680,295);
    
    //抽一次花费元宝
    string costone = StringUtils::format("%d",m_onecost);
    Label* costonelabel = PublicShowUI::getLabel(costone.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),20,false,false);
    costonelabel->setAnchorPoint(Point(Point::ZERO));
    layerbg->addChild(costonelabel,10);
    costonelabel->setPosition(690,70);
    Sprite* gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    gold->setScale(0.8);
    layerbg->addChild(gold,10);
    gold->setPosition(costonelabel->getPositionX()+costonelabel->getContentSize().width+gold->getContentSize().width/2,costonelabel->getPositionY()+costonelabel->getContentSize().height/2);
    
    //抽十次花费元宝
    string costten = StringUtils::format("%d",m_tencost);
    Label* costtenlabel = PublicShowUI::getLabel(costten.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),20,false,false);
    costtenlabel->setAnchorPoint(Point(Point::ZERO));
    layerbg->addChild(costtenlabel,10);
    costtenlabel->setPosition(830,70);
    Sprite* goldten = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    goldten->setScale(0.8);
    layerbg->addChild(goldten,10);
    goldten->setPosition(costtenlabel->getPositionX()+costtenlabel->getContentSize().width+goldten->getContentSize().width/2,costtenlabel->getPositionY()+costtenlabel->getContentSize().height/2);
    
     
    //技能图标
    int skill = 0;
    const char* iconPath = NULL;
    Sprite* skillPic = NULL;
    for (int i = 0; i<4; i++) {
        skill = m_skillList.at(i).asInt();
        DictSkill* skill1 = DictSkillManager::getInstance()->getData(skill);
        iconPath = PublicShowUI::getResImgPath(IMG_SKILL_ICON, skill1->icon.c_str());
        skillPic = Sprite::create(iconPath);
        if (skillPic) {
            skillPic->setScale(.8);
            if (i == 3) {
                skillPic->setScale(0.55);
            }
            skillPic->setAnchorPoint(Point::ZERO);
            skillPic->setPosition(630+i*(skillPic->getContentSize().width+5),170);
            if(i == 3)
            {
                skillPic->setPosition(630+i*(skillPic->getContentSize().width-35),170);
            }
            layerbg->addChild(skillPic);
        }
    }
    
    //英雄大图
    DictHero* dictHero = DictHeroManager::getInstance()->getData(m_herodictid);
    if(dictHero)
    {
        const char* path  = PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH,dictHero->halfbodyrResource.c_str());
        log("path=%s",path);
        Sprite* heroPic = Sprite::create(path);
        if(heroPic)
        {
            heroPic->setAnchorPoint(Point::ZERO);
            heroPic->setPosition(Point::ZERO);
//            MoveBy* move1 = MoveBy::create(2, Point( 0,10));
//            MoveBy* move2 = MoveBy::create(2, Point(0,-10));
//            Sequence* seq = Sequence::create(move1,move2, NULL);
//            RepeatForever* rep = RepeatForever::create(seq);
//            heroPic->runAction(rep);
            layerbg->addChild(heroPic,1);
        }
    }
}
//-----------------------------------------------访问服务器-------------------------------------------------------//
void LimitCardLayer::requestlimitCardMsg()//请求列表信息
{
    Dialog::showServerLoading();
    LimitTimeDetailMsg* msg = new LimitTimeDetailMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void LimitCardLayer::onlimitCardProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_LEGEND_LegendLeadPageResp)
    {
        if(message->state)//返回成功
        {
            
            m_activityStartTimes = message->byteStream->getLong();
            m_activityEndTimes = message->byteStream->getLong();
            m_herodictid = message->byteStream->getInt();
            m_heroAttackType = message->byteStream->getByte();
            m_heroName = message->byteStream->getUTF8();
            m_heroHp = message->byteStream->getInt();
            m_herodefend = message->byteStream->getInt();
            m_heroAttact = message->byteStream->getInt();
            ValueVector m_skillList;
            m_skill1 = message->byteStream->getInt();
            m_skillList.push_back(Value(m_skill1));
            m_skill2 = message->byteStream->getInt();
            m_skillList.push_back(Value(m_skill2));
            m_skill3 = message->byteStream->getInt();
            m_skillList.push_back(Value(m_skill3));
            m_skill4 = message->byteStream->getInt();
            m_skillList.push_back(Value(m_skill4));
            m_onecost = message->byteStream->getInt();
            m_tencost = message->byteStream->getInt();
            setItemPic(m_skillList);
        }
    }
}

void LimitCardLayer::requestChoseCardMsg(int _costType)//抽卡
{
    Dialog::showServerLoading();
    LimitTimeChoseCardMsg* msg = new LimitTimeChoseCardMsg(_costType);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void LimitCardLayer::onChoseCardProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    MarketFindResultDataManager::getInstance()->clearDumpList();
    if(message->messageID == SCENSE_CLIENT_LEGEND_LegendLeadResp)
    {
        if(message->state)//返回成功
        {
            MarketFindResultData* data = new MarketFindResultData;
            data->autorelease();
//            int countMode = message->byteStream->getByte();
            int itemCount = message->byteStream->getByte();
            if (itemCount == 1)
            {
                data->itemType = message->byteStream->getByte();
                log("itemType===========%d",data->itemType);
                MarketFindResultDataManager::getInstance()->setfindTypeData(data->itemType);
                if (data->itemType == 1) {
                    data->heroId = message->byteStream->getInt();
                    data->dictId= message->byteStream->getInt();
                    data->heroForce = message->byteStream->getByte();
                    data->name = message->byteStream->getUTF8();
                    data->quality = message->byteStream->getByte();
                    data->level = message->byteStream->getInt();
                    data->prestige = message->byteStream->getInt();
                    data->combatPower = message->byteStream->getInt();
                    data->leaderShip = message->byteStream->getInt();
                    MarketFindResultDataManager::getInstance()->addData(data);
                    MarketGetHeroLayer::show(MarketFindResultDataManager::getInstance()->dumpList->at(0));
                }
                else if(data->itemType>1 && data->itemType<7){
                    data->dictId = message->byteStream->getInt();
                    data->name = message->byteStream->getUTF8();
                    data->quality = message->byteStream->getByte();
                    data->itemDesc = message->byteStream->getUTF8();
//                    MarketFindResultDataManager::getInstance()->addData(data);
//                    MarketGetEquipLayer::show();
                    
                    Vector<BaseTypeData*> *m_basegift = new Vector<BaseTypeData*>();
                    m_basegift->clear();
                    BaseTypeData* basedata = new BaseTypeData();
                    basedata->autorelease();
                    basedata->dataId = data->dictId;
                    basedata->dataName = data->name;// itemName;
                    basedata->dataType = data->itemType;
                    basedata->dataQuality = data->quality;
                    basedata->dataCount = 1;
                    m_basegift->pushBack(basedata);
                    AwardBox_Layer* layer=AwardBox_Layer::create(m_basegift);
                    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
                    Scene* scene=Director::getInstance()->getRunningScene();
                    scene->addChild(layer,100);
                    
                }else{
                    log("类型错误：itemType=====%d",data->itemType);
                }
            }
            else if (itemCount > 1)
            {
                for (int i = 0; i< itemCount; i++) {
                    MarketFindResultData* dataten = new MarketFindResultData;
                    dataten->autorelease();
                    dataten->itemType = message->byteStream->getByte();
                    if (dataten->itemType == 1) {
                        dataten->heroId = message->byteStream->getInt();
                        dataten->dictId = message->byteStream->getInt();
                        dataten->heroForce = message->byteStream->getByte();
                        dataten->name = message->byteStream->getUTF8();
                        dataten->quality = message->byteStream->getByte();
                        dataten->level = message->byteStream->getInt();
                        dataten->prestige = message->byteStream->getInt();
                        dataten->combatPower = message->byteStream->getInt();
                        dataten->leaderShip = message->byteStream->getInt();
                    }
                    else if(dataten->itemType>1 && dataten->itemType<7)
                    {
                        dataten->dictId = message->byteStream->getInt();
                        dataten->name = message->byteStream->getUTF8();
                        dataten->quality = message->byteStream->getByte();
                        dataten->itemDesc = message->byteStream->getUTF8();
                    }
                    MarketFindResultDataManager::getInstance()->addData(dataten);
                }
                MarketGoodsLayer* getHeroLayer = MarketGoodsLayer::create();
                getHeroLayer->setAnchorPoint(Point::ZERO);
                PublicShowUI::setTargetScale(getHeroLayer);
                getHeroLayer->setPositionX(VisibleRect::center().x-getHeroLayer->getContentSize().width/2);
                getHeroLayer->setPositionY(VisibleRect::center().y - getHeroLayer->getContentSize().height/2);
                Scene* scene = Director::getInstance()->getRunningScene();
                scene->addChild(getHeroLayer, SCENE_LAYER_ZORDER);
            }
        }
    }
}

void LimitCardLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LEGEND_LegendLeadPageResp).c_str(), CC_CALLBACK_1(LimitCardLayer::onlimitCardProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LEGEND_LegendLeadResp).c_str(), CC_CALLBACK_1(LimitCardLayer::onChoseCardProcess, this));
}
void LimitCardLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
bool LimitCardLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    return  true;
}
void LimitCardLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    
}
void LimitCardLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    if(m_iscloseScene == true)
    {
        backScene();
    }
    m_iscloseScene = true;
}
void LimitCardLayer::backScene()
{
    this->removeFromParent();
}
