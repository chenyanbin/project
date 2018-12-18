//
//  LineupHeroLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/6/24.
//
//

#include "LineupHeroLayer.h"

#include "../../../avatar/npc/Npc.h"
#include "../../../avatar/hero/Hero.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../wujiangList/LineupAllHeroLayer.h"
#include "../../../protocol/Protocal.h"
#include "../../../message/Decoding/lineup/lineupPage/LineupPageMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/lineup/LineupSetLocationMsg/LineupSetLocationMsg.h"
#include "../lineup_data/LineupPageDataManger.h"
LineupHeroLayer::LineupHeroLayer()
:m_isPos(false)
,m_location(1)
,m_heroType(1)
,m_tag_heroPos(1)
,m_turn(0)
,m_nowPage(1)
,popUpLoading(NULL)
,m_leadership(0)
,TAG_MENU(110)
,TAG_SHADOWE(111)
,m_index(0)
{
    lineipPageList=new Vector<LineupPageData*>() ;
    lineupCheerList = new Vector<LineupPageData*>();
}
LineupHeroLayer::~LineupHeroLayer()
{
    log("~~LineupHeroLayer ~~LineupHeroLayer");
    lineipPageList->clear();
    CC_SAFE_DELETE(lineipPageList);
    lineipPageList = NULL;
    lineupCheerList->clear();
    CC_SAFE_DELETE(lineupCheerList);
    lineupCheerList = NULL;
   
    popUpLoading = NULL;
    LineupPageDataManger::getInstance()->destroyInstance();
    
}

bool LineupHeroLayer::init(int nowPage)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->isAnimation = false;
        
        m_nowPage = nowPage;
       
        bref = true;
    } while (false);
    return bref;
}

LineupHeroLayer* LineupHeroLayer::create(int nowPage)
{
    LineupHeroLayer* layer = new LineupHeroLayer();
    if(layer && layer->init(nowPage))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}

void LineupHeroLayer::setBackGround()
{
//    Sprite* bg = Sprite::create(IMG_LINEUP_BG);
//    bg->setAnchorPoint(Point::ZERO);
//    Size size = bg->getContentSize();
//    bg->setPosition(Point::ZERO);
//    this->setContentSize(bg->getContentSize());


}
void LineupHeroLayer::onEnter()
{
    BaseLayer::onEnter();
    
}
void LineupHeroLayer::onExit()
{
    BaseLayer::onExit();
    
}
void LineupHeroLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void LineupHeroLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    clearResourcePerson();
    removeEventListener();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumTeamHead);
}
void LineupHeroLayer::zhujiangPOs()//设置点击位置
{
    
    if(this->getChildByTag(TAG_SHADOWE))
    {
        return;
    }
    Node* footShadow = Node::create();
    footShadow->setAnchorPoint(Point::ZERO);
    for (int i = 0; i<3; i++)
    {
        if (i == 0)
        {
           
            Sprite* particle = Sprite::create(IMG_LINEUP_HEROPAR);
            particle->setAnchorPoint(Point::ZERO);
            particle->setPosition((this->getContentSize().width - particle->getContentSize().width)/2 + 78,60);
            footShadow->addChild(particle,0);
            
            Sprite* zjWord = Sprite::create(IMG_LINEUP_ZJWORD);
            zjWord->setAnchorPoint(Point::ZERO);
            zjWord->setPosition((particle->getContentSize().width - zjWord->getContentSize().width)/2, 0);
            particle->addChild(zjWord,5);
            
            TouchSprite* touchbg = TouchSprite::createWithPic(IMG_LINEUP_UNGRAYHERO, this, callfuncN_selector(LineupHeroLayer::onPosClick));
            touchbg->setAnchorPoint(Point::ZERO);
            touchbg->setOpacity(0);
            touchbg->setPosition((particle->getContentSize().width-touchbg->getContentSize().width)/2,10);
            particle->addChild(touchbg,5,1);
        }
        else if(i == 1)
        {
           
            Sprite* particle1 = Sprite::create(IMG_LINEUP_HEROPAR);
            particle1->setAnchorPoint(Point::ZERO);
            particle1->setPosition((this->getContentSize().width - particle1->getContentSize().width)/2 + 250,220);
            footShadow->addChild(particle1,0);
            
            Sprite* fjWord = Sprite::create(IMG_LINEUP_FJWORD);
            fjWord->setAnchorPoint(Point::ZERO);
            fjWord->setPosition((particle1->getContentSize().width - fjWord->getContentSize().width)/2, 0);
            particle1->addChild(fjWord,2);
            
            TouchSprite* touchbg1 = TouchSprite::createWithPic(IMG_LINEUP_UNGRAYHERO, this, callfuncN_selector(LineupHeroLayer::onPosClick));
            touchbg1->setAnchorPoint(Point::ZERO);
            touchbg1->setOpacity(0);
            touchbg1->setPosition((particle1->getContentSize().width-touchbg1->getContentSize().width)/2,10);
            particle1->addChild(touchbg1,5,2);
            
        }
        else if (i == 2)
        {
            
            Sprite* particle2 = Sprite::create(IMG_LINEUP_HEROPAR);
            particle2->setAnchorPoint(Point::ZERO);
            particle2->setPosition((this->getContentSize().width - particle2->getContentSize().width)/2 - 150,220);
            footShadow->addChild(particle2,0);
            
            Sprite* fjWord = Sprite::create(IMG_LINEUP_FJWORD);
            fjWord->setAnchorPoint(Point::ZERO);
            fjWord->setPosition((particle2->getContentSize().width - fjWord->getContentSize().width)/2, 0);
            particle2->addChild(fjWord,2);
            
            TouchSprite* touchbg2 = TouchSprite::createWithPic(IMG_LINEUP_UNGRAYHERO, this, callfuncN_selector(LineupHeroLayer::onPosClick));
            touchbg2->setAnchorPoint(Point::ZERO);
            touchbg2->setOpacity(0);
            touchbg2->setPosition((particle2->getContentSize().width-touchbg2->getContentSize().width)/2,10);
            particle2->addChild(touchbg2,5,3);
            GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumTeamHead, touchbg2);
            
        }
    }
    this->addChild(footShadow,0,TAG_SHADOWE);
    NewPlayerGuild::getInstance()->showNowGuide();
}

void LineupHeroLayer::setHeroPos()
{
    if(popUpLoading && popUpLoading->getParent())
    {
        Dialog::hideLoading();
        popUpLoading = NULL;
    }
    if (m_isPos) {
            this->removeChildByTag(TAG_MENU);
    }
    m_isPos = true;
    
    RotateMenu *menu = RotateMenu::create();
    menu->setAnchorPoint(Point::ZERO);
    Node* item = NULL;
    int tag = 0;
    ssize_t len = lineipPageList->size();
    for (int i = 0; i < len; i++) {
        item = this->getItem(lineipPageList->at(i));
        tag = lineipPageList->at(i)->heroId == 0 ? i : lineipPageList->at(i)->heroId;
        menu->addMenuItem((MenuItem*)item,i,tag);
    }
    this->setContentSize(menu->getContentSize());
    this->addChild(menu, 2,TAG_MENU);

}
//位置点击
void LineupHeroLayer::onPosClick(Node* psender)
{
    m_location = psender->getTag();
    log("wujiangweizhi================%d",m_location);
    broadMsg(CUSTOM_LINEUP_ENTERHEROLIST);
     NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumTeamHead);
     LineupAllHeroLayer::show(m_nowPage,m_heroType,m_location,m_leadership);
   
}

void LineupHeroLayer::loadPerson()
{
    DictHero* dictHero = NULL;
    ssize_t len = lineipPageList->size();
    const char* path = NULL;
    bool hasHero = false;
    popUpLoading = Dialog::showLoading();

    for (int i = 0; i < len; i ++)
    {
        LineupPageData* data = lineipPageList->at(i);
        
        dictHero = DictHeroManager::getInstance()->getData(data->heroDictId);
        if(dictHero)
        {
          
            hasHero = true;
            path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictHero->resource.c_str());
            log("path=%s",path);
            ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(LineupHeroLayer::onDataLoaded));
        }
    }
    if(!hasHero)
    {
        this->setHeroPos();
        zhujiangPOs();
    }
}
//得到一个武将
Node* LineupHeroLayer::getItem(LineupPageData* data)
{

    Node* item = Node::create();
    Sprite* bg = Sprite::create(IMG_LINEUP_ADDHERO);
    item->addChild(bg);
    item->setContentSize(bg->getContentSize());
    bg->setAnchorPoint(Point::ZERO);
    if(data->heroDictId)
    {
        bg->setOpacity(0);
        Hero* hero  = Hero::create(data->heroDictId);
       
        item->addChild(hero);
        hero->setPosition(item->getContentSize().width/2, 0);
    }
    
    item->setAnchorPoint(Point(0,0));
    return item;
}
void LineupHeroLayer::onDataLoaded(float percent)
{
    log("perdent==%f",percent);
    if(popUpLoading && popUpLoading->getParent())
    {
        popUpLoading->setProgressPercent(percent * 100);
    }
    if(percent >= 1)
    {
        this->setHeroPos();
        zhujiangPOs();
    }
}

void LineupHeroLayer::clearResourcePerson()//清除人物资源
{
    DictHero* dictHero = NULL;
    ssize_t len = lineipPageList->size();
    const char* path = NULL;
    for(int i = 0; i < len; i++)
    {
        LineupPageData* data = lineipPageList->at(i);
        dictHero = DictHeroManager::getInstance()->getData(data->heroDictId);
        if(dictHero)
        {
            path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictHero->resource.c_str());
            ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
        }
        ArmatureDataManager::getInstance()->removeArmatureFileInfo("");
        Director::getInstance()->getTextureCache()->removeUnusedTextures();
    }
    ArmatureDataManager::destroyInstance();
    
}
void LineupHeroLayer::onChangeHeroPos()
{
    int heroId1 = NULL;
    int heroId2 = NULL;
    int heroId3 = NULL;
    int dictHeroId = 0;
    log("==================%d",m_turn);
    if (m_turn == 0) {
        heroId1 =lineipPageList->at(0)->heroId;
        heroId2 = lineipPageList->at(1)->heroId;
        heroId3 = lineipPageList->at(2)->heroId;
        dictHeroId = lineipPageList->at(0)->heroDictId;
        m_index = 0;
    }else if (m_turn == 2 || m_turn == -2)
    {
        heroId1 = lineipPageList->at(2)->heroId;
        heroId2 = lineipPageList->at(0)->heroId;
        heroId3 = lineipPageList->at(1)->heroId;
        dictHeroId = lineipPageList->at(2)->heroDictId;
        m_index = 2;
    }else if (m_turn ==1 || m_turn == -1)
    {
        heroId1 = lineipPageList->at(1)->heroId;
        heroId2 = lineipPageList->at(2)->heroId;
        heroId3 = lineipPageList->at(0)->heroId;
        dictHeroId = lineipPageList->at(1)->heroDictId;
        m_index = 1;
    }

   
    requestLocationMsg(m_nowPage,heroId1,heroId2,heroId3);
}
void LineupHeroLayer::onChangePageCallBack(EventCustom* msg)//接受消息，更新HeroPos，接收当前页
{
    __Integer* inter = (__Integer*)msg->getUserData();
    lineipPageList->clear();
    lineupCheerList->clear();
    m_nowPage = inter->getValue();
    log("shoudaoxiaoxi===%d",m_nowPage);
    requestPageMsg(m_nowPage);
}
void LineupHeroLayer::changeLinguoHero(EventCustom* msg)//接收消息，获取武将位置改变信息
{
    __Integer* inter = (__Integer*)msg->getUserData();
    m_turn = inter->getValue();
    onChangeHeroPos();
}
//-----------------------------------------------访问服务器-------------------------------------------------------//

void LineupHeroLayer::requestPageMsg(int team)//切换阵容信息
{
    Dialog::showServerLoading(.5);
    LineupPageMsg* msg = new LineupPageMsg(team);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void LineupHeroLayer::onMsgProcess(EventCustom* msg)//接受消息阵容变化
{
    Dialog::hideServerLoading();
    LineupPageDataManger::getInstance()->clearPagelist();
    LineupPageDataManger::getInstance()->clearKarmaData();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(!message->state)
    {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_LINEUP_LineupPageResp)
    {
        int isDefault = message->byteStream->getByte();
        int roleLeadership = message->byteStream->getInt();
        int masterSize=message->byteStream->getByte();
        for (int i =0; i<masterSize; i++) {
            LineupPageData* data=new LineupPageData();
            data->autorelease();
            data->heroId=message->byteStream->getInt();
            data->heroDictId=message->byteStream->getInt();
            data->quality=message->byteStream->getByte();
            data->heroName=message->byteStream->getUTF8();
            data->level=message->byteStream->getInt();
            data->leadership = message->byteStream->getInt();
            data->combatPower = message->byteStream->getInt();
            data->karmaDesc1 = message->byteStream->getUTF8();
            data->own1 = message->byteStream->getByte();
            data->karmaDesc2 = message->byteStream->getUTF8();
            data->own2 = message->byteStream->getByte();
            data->skillName = message->byteStream->getUTF8();
            data->skilldesc = message->byteStream->getUTF8();
            data->skillOwn = message->byteStream->getByte();
            LineupPageDataManger::getInstance()->addData(data);
            lineipPageList->pushBack(data);
        }
        int cheerSize = message->byteStream->getByte();
        for (int i = 0; i < cheerSize; i++) {
            LineupPageData* data = new LineupPageData();
            data->autorelease();
            data->heroId=message->byteStream->getInt();
            data->heroDictId=message->byteStream->getInt();
            data->quality=message->byteStream->getByte();
            data->level=message->byteStream->getInt();
            data->leadership = message->byteStream->getInt();
            data->combatPower = message->byteStream->getInt();
            data->hp = message->byteStream->getInt();
            data->attack = message->byteStream->getInt();
            data->defend = message->byteStream->getInt();
            lineupCheerList->pushBack(data);
        }
        int leadership = 0;//领导力
        int _combatPower = 0;//战力
        ssize_t len = lineipPageList->size();
        for (int i = 0; i< len; i ++) {
            leadership += lineipPageList->at(i)->leadership;
            leadership += lineupCheerList->at(i)->leadership;
            _combatPower += lineipPageList->at(i)->combatPower;
        }
        m_leadership = leadership;

        broadMsg(CUSTOM_LINEUP_FIGHTORWITE,__Integer::create(isDefault));//发布开战还是待战信息
        broadMsg(CUSTOM_LINEUP_ROLELEADERSHIP,__Integer::create(roleLeadership));//发布角色领导力
        broadMsg(CUSTOM_LINEUP_LEADERSHIP,__Integer::create(leadership));//发布领导力
        broadMsg(CUSTOM_LINEUP_ZHANLI,__Integer::create(_combatPower));//发布战力
        broadMsg(CUSTOM_LINEUP_SAHNGZHENWUJIANG,__Integer::create(0));//发布上阵武将消息
        broadMsg(CUSTOM_LINEUP_ZHUZHENWUJIANG,lineupCheerList);//发布助阵武将消息
    
        loadPerson();
      
        
        
        
    }

}

void LineupHeroLayer::requestLocationMsg(int lineupNo, int heroId1, int heroId2,int heroId3)//发送武将位置数据
{
    Dialog::showServerLoading(.5);
   
    LineupSetLocationMsg* msg = new LineupSetLocationMsg(lineupNo,heroId1,heroId2,heroId3);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void LineupHeroLayer::ontouchchangeProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(!message->state)
    {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_LINEUP_LineupSetLocationResp)
    {
        broadMsg(CUSTOM_LINEUP_SAHNGZHENWUJIANG,__Integer::create(m_index));//切换
    }

}
void LineupHeroLayer::addEventListener()//添加监听
{
    addUserMsg(CUSTOM_LINEUP_QIEHUANWUJIANG, CC_CALLBACK_1(LineupHeroLayer::changeLinguoHero, this));//接收消息，获取武将位置改变信息
    addUserMsg(CUSTOM_CHANGE_TEAMPAGE, CC_CALLBACK_1(LineupHeroLayer::onChangePageCallBack, this));//接受消息，更新HeroPos，接收当前页
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LINEUP_LineupPageResp).c_str(), CC_CALLBACK_1(LineupHeroLayer::onMsgProcess, this));//接受消息阵容变化
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LINEUP_LineupSetLocationResp).c_str(), CC_CALLBACK_1(LineupHeroLayer::ontouchchangeProcess, this));//接受消息阵容变化
}
void LineupHeroLayer::removeEventListener()//清除监听
{
    BaseLayer::removeEventListener();
}

