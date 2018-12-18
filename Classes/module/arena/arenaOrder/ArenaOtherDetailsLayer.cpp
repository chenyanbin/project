//
//  ArenaOtherDetailsLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/22.
//
//

#include "ArenaOtherDetailsLayer.hpp"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../commonData/dictData/DictHeroQuality/DictHeroQualityManager.h"
#include "../../../message/Decoding/arena/FindUserMessageMsg.hpp"
#include "../../../common/Dialog/Dialog.h"
#include "../arenaData/RoleMessageDataManager.hpp"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
ArenaOtherDetailsLayer::ArenaOtherDetailsLayer()
:m_nowcount(1)
,TAG_COUNT(2)
,TAG_ALLCOUNT(3)
,m_roleId(0)
,m_owngold(1100)
,TAG_NODE(100)
{
    
}

ArenaOtherDetailsLayer::~ArenaOtherDetailsLayer()
{
    
}


bool ArenaOtherDetailsLayer::init(int idType,int roleId)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        m_roleId = roleId;
        this->setBackground(IMG_GENERALS_CARD_BG,Point::ZERO,true);
        this->isAnimation = false;
        this->setClickEnabled(true);
        this->isClickClose = true;//点击外面自动关闭
        this->isShowGrayBg = true;
        setBgLayer();
        requestAccelerMsg(idType,m_roleId);
        bref = true;
    } while (false);
    return bref;
}

ArenaOtherDetailsLayer* ArenaOtherDetailsLayer::create(int idType,int roleId)
{
    ArenaOtherDetailsLayer* list = new ArenaOtherDetailsLayer();
    if(list && list->init(idType,roleId))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void ArenaOtherDetailsLayer::show(int idType,int roleId)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    ArenaOtherDetailsLayer* layer = ArenaOtherDetailsLayer::create(idType,roleId);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}

void ArenaOtherDetailsLayer::onEnter()
{
    BaseLayer::onEnter();
}
void ArenaOtherDetailsLayer::onExit()
{
    BaseLayer::onExit();
}
void ArenaOtherDetailsLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void ArenaOtherDetailsLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}

void ArenaOtherDetailsLayer::setBgLayer()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* layerbg = (Sprite*)this->getChildByTag(TAG_BG);
    Size size = layerbg->getContentSize();
    size.width = layerbg->getContentSize().width+ 105;
    this->setContentSize(size);
}
void ArenaOtherDetailsLayer::setHeroHead()
{
    size_t count = RoleMessageDataManager::getInstance()->roleList->size();
    Node* node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    Size size = node->getContentSize();
    UserHeadLayer* userHead = NULL;
    for (int i = 0;  i < count; i ++ ) {
        RoleMessageData* data = RoleMessageDataManager::getInstance()->roleList->at(i);
        DictHero* dictHero = DictHeroManager::getInstance()->getData(data->heroDictId);
        if (dictHero) {
            userHead=UserHeadLayer::create(dictHero->resource.c_str(),data->heroQuality);
            userHead->setHeadInfo(data->leadership, data->prestige);
            userHead->setPositionY(i*(userHead->getContentSize().height+10));
            node->addChild(userHead,2,i);
            userHead->addTouchBegainCallBack(this, callfuncN_selector(ArenaOtherDetailsLayer::onUserClick));
        }
    }
    if(userHead)
    {
        size.width = userHead->getContentSize().width;
        size.height = userHead->getPositionY() + userHead->getContentSize().height;
        node->setContentSize(size);
        this->addChild(node,2);
        node->setPosition(this->getContentSize().width-userHead->getContentSize().width,this->getContentSize().height-node->getContentSize().height-30);
    }
    
    
}
void ArenaOtherDetailsLayer::onUserClick(Node* pSender)
{
    setOneHeroMessage(pSender->getTag());
}
void ArenaOtherDetailsLayer::setOneHeroMessage(int index)
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* layerbg = (Sprite*)this->getChildByTag(TAG_BG);
    
    
    
    RoleMessageData* data = RoleMessageDataManager::getInstance()->roleList->at(index);
    if(layerbg->getChildByTag(TAG_NODE))
    {
        layerbg->removeChildByTag(TAG_NODE);
    }
    Node* node = Node::create();
    node->setAnchorPoint(Point::ZERO);

    Sprite* cardbg2=Sprite::create(IMG_GENERALS_CARD_BG2);
    cardbg2->setAnchorPoint(Point::ZERO);
    cardbg2->setPosition(Point::ZERO);
    node->addChild(cardbg2,1);
    
    Sprite* cardBox=Sprite::create(IMG_GENERALS_CARD_BOX2);
    cardBox->setAnchorPoint(Point::ZERO);
    cardBox->setPosition(Point::ZERO);
    node->addChild(cardBox,2);
    
    //卡牌下层
    Sprite* cardBox2=Sprite::create(IMG_GENERALS_CARD_NEWHALFBOX);
    cardBox2->setAnchorPoint(Point::ZERO);
    cardBox2->setPosition(0,5);
    node->addChild(cardBox2,5);

    
    //卡牌品质框
    char stt[100]="";
    int quality=data->heroQuality;
    quality=quality==0?1:quality;
    quality = PublicShowUI::getColorIndexByQuality(DictItemTypeEnumItemHero,quality);
    sprintf(stt,IMG_PUBLIC_HEADBIGFRAME,quality);
    Sprite* headBox=Sprite::create(stt);
    headBox->setAnchorPoint(Point::ZERO);
    node->addChild(headBox,3);
    //卡牌
    DictHero* dictHero = DictHeroManager::getInstance()->getData(data->heroDictId);
    if(dictHero)
    {
        const char* path  = PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH,dictHero->halfbodyrResource.c_str());
        Sprite* tempCard=Sprite::create(path);
        tempCard->setAnchorPoint(Point::ZERO);
        tempCard->setPosition(-50,0);
        node->addChild(tempCard,4);
    }
    
    
    //势力范围
    //    int typeNum =  DictHeroManager::getInstance()->getData(2)->attackType;
    //    if (typeNum<1) {
    //        typeNum = 1;
    //    }
    //    sprintf(stt,IMG_PUBLIC_HEROINFO_ATTACTTYPE,typeNum);
    //    Sprite* forceSprite=Sprite::create(stt);
    //    forceSprite->setAnchorPoint(Point::ZERO);
    //    forceSprite->setPosition(43,410);
    //    layerbg->addChild(forceSprite,7);
    
    //卡牌名字背景
    sprintf(stt,IMG_PUBLIC_HEADNAMEBG,quality);
    Sprite* headNameBg=Sprite::create(stt);
    headNameBg->setAnchorPoint(Point::ZERO);
    headNameBg->setPosition(40,112);
    node->addChild(headNameBg,7);
    
    //名字
    string str=data->heroName;
    DictHeroQuality* datalabel =DictHeroQualityManager::getInstance()->getData(quality);
    if (data) {
        str=datalabel->name+"  "+str;
    }
    Label* nameLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),22,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    //    nameLabel->setAlignment(TextHAlignment::CENTER);
    nameLabel->setPosition((layerbg->getContentSize().width/sx-nameLabel->getContentSize().width)/2,188);
    node->addChild(nameLabel,8);
    
    //战斗力
    string leadStr = StringUtils::format("%d",data->combatPower);
    Label* leadLabel = PublicShowUI::getLabel(leadStr.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),20,false,false);
    leadLabel->setAnchorPoint(Point(0.5,0.5));
    leadLabel->setPosition(185,105);
    node->addChild(leadLabel,10);
    
    //领导力
    string levelCard = StringUtils::format("%d",data->leadership);
    Label* levelLabel = PublicShowUI::getLabel(levelCard.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),20,false,false);
    levelLabel->setAnchorPoint(Point(0.5,0.5));
    levelLabel->setPosition(320,105);
    node->addChild(levelLabel,10);
    
    //等级
    string prestStr = StringUtils::format("%d",data->heroLevel);
    Label* prestLabel = PublicShowUI::getLabel(prestStr.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),20,false,false);
    prestLabel->setAnchorPoint(Point::ZERO);
    prestLabel->setPosition(130,53);
    node->addChild(prestLabel,10);
    
    Sprite* tittleBg = Sprite::create(IMG_GENERALS_CARD_TITTLEBG);
    tittleBg->setAnchorPoint(Point::ZERO);
    node->addChild(tittleBg,10);
    tittleBg->setPosition(200,30);
    
    
    DictHero* hero = DictHeroManager::getInstance()->getData(data->heroDictId);
    if (hero) {
        float percentatact = hero->attackEvaluate ;
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
    
    layerbg->addChild(node,3,TAG_NODE);
}
/**************------------------------------------服务器-----------------------------------*****************/
void ArenaOtherDetailsLayer::requestAccelerMsg(int m_idType,long roleId)
{
    Dialog::showServerLoading();
    FindUserMessageMsg* msg = new FindUserMessageMsg(m_idType,roleId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void ArenaOtherDetailsLayer::onAccelerMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    RoleMessageDataManager::getInstance()->destroyInstance();
    if(message->messageID == SCENSE_CLIENT_ARENA_ArenaLookUpRoleInfoResp)
    {
        if(message->state)//返回成功
        {

            int roleSize = message->byteStream->getByte();
            for (int i = 0; i < roleSize; i ++)
            {
                RoleMessageData* data = new RoleMessageData();
                data->autorelease();
                data->heroId = message->byteStream->getInt();
                data->heroDictId = message->byteStream->getInt();
                data->force = message->byteStream->getByte();
                data->heroName = message->byteStream->getUTF8();
                data->heroQuality = message->byteStream->getByte();
                data->heroLevel = message->byteStream->getInt();
                data->prestige = message->byteStream->getInt();
                data->combatPower = message->byteStream->getInt();
                data->leadership = message->byteStream->getInt();
                RoleMessageDataManager::getInstance()->addData(data);
            }
            if (roleSize>0) {
                setHeroHead();
                setOneHeroMessage(0);
            }
        }
    }
}
void ArenaOtherDetailsLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ARENA_ArenaLookUpRoleInfoResp).c_str(), CC_CALLBACK_1(ArenaOtherDetailsLayer::onAccelerMsgProcess, this));
}
void ArenaOtherDetailsLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
