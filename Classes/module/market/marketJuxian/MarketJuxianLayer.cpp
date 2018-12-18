//
//  MarketJuxianLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/4.
//
//

#include "MarketJuxianLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../message/Decoding/market/juxian/juxianListMsg/JuxianListMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/market/juxian/juxianTimeMSg/JuxianTimeMsg.h"
#include "../marketData/JuxianListDataManager.h"
#include "juxianWindowLayer.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../marketData/MarketFindResultDataManager.h"
#include "../../../commonData/enum/DictRolePropEnum.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../marketFind/MarketGetHeroLayer.h"
#include "../marketFind/MarketGetEquipLayer.h"
#include "../../data/BaseTypeData.h"
#include "../../awardBox/AwardBox_Layer.h"
MarketJuxianLayer::MarketJuxianLayer()
:TAG_LASTTIME(12)
,TAG_TIMELABEL(13)
,TAG_LABELWORD(14)
,TAG_TOKEN(16)
,TAG_ICON(17)
,TAG_PARTICLE(18)
,TAG_PARTICLE2(19)
,TAG_MENU(20)
,TAG_TIMEOUT(21)
,m_tag_time(1000)
,label(NULL)
,pTime(1)
,label2(NULL)
,pTime2(1)
,label3(NULL)
,pTime3(1)
,m_nextSelected(1)
,isfirst(true)
,TAG_DEXNODE(22)
{
    
}

MarketJuxianLayer::~MarketJuxianLayer()
{
    JuxianListDataManager::destroyInstance();
//    unschedule(schedule_selector(MarketJuxianLayer::update));
//    unschedule(schedule_selector(MarketJuxianLayer::update2));
//    unschedule(schedule_selector(MarketJuxianLayer::update3));
//    this->removeChildByTag(TAG_PARTICLE);
}

bool MarketJuxianLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        
        this->isAnimation = false;
        setBackground();
        setparticle();
        setCardPos();
        bref = true;
    } while (false);
    return bref;
}

MarketJuxianLayer* MarketJuxianLayer::create()
{
    MarketJuxianLayer* list = new MarketJuxianLayer();
    if(list && list->init())
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void MarketJuxianLayer::onEnter()
{
    BaseLayer::onEnter();
}
void MarketJuxianLayer::onExit()
{
    BaseLayer::onExit();
    clearResourcePerson();
}
void MarketJuxianLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestListMsg();
}
void MarketJuxianLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumCard1Times);
}

void MarketJuxianLayer::setBackground()
{
    Node* container = Node::create();
    container->setAnchorPoint(Point::ZERO);
    Sprite* bottombg = NULL;
    for(int i = 0; i < 3; i++)
    {
        
        bottombg = Sprite::create(IMG_MARKET_MARKETJUXIAN_BOTTOMBG);
        bottombg->setAnchorPoint(Point::ZERO);
        bottombg->setPositionX(i * (bottombg->getContentSize().width));
        if(i == 1){
            bottombg->setPositionY(-50);
        }
        container->addChild(bottombg,1,i);
        bottombg->setVisible(false);
    }
    this->addChild(container,1);
    Size size = bottombg->getContentSize();
    size.width = bottombg->getPositionX() + bottombg->getContentSize().width;
    container->setContentSize(size);
    this->setContentSize(size);
    
    Sprite* cardbg = Sprite::create(IMG_MARKET_CARDBG);
    cardbg->setAnchorPoint(Point::ZERO);
    this->addChild(cardbg,2);
    cardbg->setPosition(80,-50);
    
    
    Button* btnone = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(MarketJuxianLayer::onsetClick, this));
    btnone->setAnchorPoint(Point::ZERO);
    btnone->setPosition(180 ,-50);
    this->addChild(btnone,3,0);
    Sprite* ontWord = Sprite::create(IMG_LIMITCARD_ONETIME);
    ontWord->setAnchorPoint(Point::ZERO);
    ontWord->setPosition(Point(-10,0));
    btnone->addChild(ontWord,5);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumCard1Times, btnone);
    
    Button* btnten = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(MarketJuxianLayer::onsetClick, this));
    btnten->setAnchorPoint(Point::ZERO);
    btnten->setPosition(520,-50);
    this->addChild(btnten,3,1);
    Sprite* tenword = Sprite::create(IMG_LIMITCARD_TENTIME);
    tenword->setAnchorPoint(Point::ZERO);
    tenword->setPosition(Point(-10,0));
    btnten->addChild(tenword,5);
 
}

void MarketJuxianLayer::setparticle()
{
    
    Node* particle = (Node*)this->getChildByTag(TAG_PARTICLE);
    if (!particle) {
        particle = Node::create();
        particle->setAnchorPoint(Point::ZERO);
        ArmatureDataManager::getInstance()->addArmatureFileInfo(AVATAR_MARKET_CARDXUANZHONG);
        Armature* armature2 = Armature::create("kapaixuanzhong");
        armature2->getAnimation()->playWithIndex(0);
        armature2->setAnchorPoint(Point::ZERO);
        armature2->setPosition(227,-27);
        particle->addChild(armature2,5);
        this->addChild(particle,3,TAG_PARTICLE);
    }
//
//    
//    Node* particle2 = (Node*)this->getChildByTag(TAG_PARTICLE2);
//    if (!particle2) {
//        particle2 = Node::create();
//        particle2->setAnchorPoint(Point::ZERO);
//        for (int i = 0; i<2; i++)
//        {
//            ArmatureDataManager::getInstance()->addArmatureFileInfo(AVATAR_MARKET_CARDTURN);
//            Armature* armature = Armature::create("kapai360");
//            armature->getAnimation()->playWithIndex(0);
//            armature->setAnchorPoint(Point::ZERO);
//            armature->setPosition(-40+i*550,70);
//            particle2->addChild(armature,5);
//        }
//        this->addChild(particle2,5,TAG_PARTICLE2);
//
//    }
}

void MarketJuxianLayer::setCardPos()
{
    MarketRotateLayer *menu = MarketRotateLayer::create();
    menu->setDelegate(this);
    menu->setAnchorPoint(Point::ZERO);
    const char* pathList[3] = {IMG_ICON_QIEXIANRUOKE,IMG_ICON_WEICAISHIJU,IMG_ICON_LIXIANXIASHI};
    for (int i = 0; i < 3; i ++) {
        const char* path = PublicShowUI::getResImgPath(IMG_MARKET_MARKETJUXIAN_CARD,PublicShowUI::numberToString(i+1).c_str());
        Sprite* card = Sprite::create(path);
        menu->addMenuItem((MenuItem*)card,0,i);
        
        const char* colorpath = PublicShowUI::getResImgPath(IMG_MARKET_MARKETJUXIAN_CARDCLOR,PublicShowUI::numberToString(i+1).c_str());
        Sprite* colorspr = Sprite::create(colorpath);
        colorspr->setAnchorPoint(Point::ZERO);
        card->addChild(colorspr,3);
        colorspr->setPosition(card->getContentSize().width/2-145    ,-75 );
        
        //令牌
        Sprite* ling = Sprite::create(pathList[i]);
        ling->setAnchorPoint(Point::ZERO);
        ling->setScale(0.3);
        ling->setPosition(80,15);
        card->addChild(ling,4);
        
    }
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 5,TAG_MENU);
    log("%f,%f",menu->getContentSize().width,menu->getContentSize().height);
    menu->setPosition((this->getContentSize().width  - menu->getContentSize().width)/2,this->getContentSize().height-80);
    
//    Node* node = menu->getChildByTag(0);
//    MoveBy* move1 = MoveBy::create(2, Point( 0,10));
//    MoveBy* move2 = MoveBy::create(2, Point(0,-10));
//    Sequence* seq = Sequence::create(move1,move2, NULL);
//    RepeatForever* rep = RepeatForever::create(seq);
//    node->runAction(rep);
    
}

void MarketJuxianLayer::onsetClick(Ref* psender)
{
    if(!JuxianListDataManager::getInstance()->juxianList)
    {
        return;
    }
    if(GlobalInfo::getInstance()->curHeroCount >= GlobalInfo::getInstance()->maxHeroCount)
    {
        
        Dialog::show("亲~追随您的狐朋狗友过多，帐篷已经被顶穿，请及时清理或者用武将扩充令扩充上限");
        return;
    }
    if(GlobalInfo::getInstance()->curEquipCount >= GlobalInfo::getInstance()->equipCountLimit)
    {
        Dialog::show("亲~收集到的破铜烂铁过多，库房已经被扎爆，请及时清理或者用装备扩充令扩充上限");
        return;
    }
    
    Node* target = (Node*)psender;
    int m_tag = target->getTag();
    log("%d",m_tag);
    int m_freeCount = JuxianListDataManager::getInstance()->juxianList->at(m_nextSelected)->freeCount;//免费次数
    int recruitCommandCount = JuxianListDataManager::getInstance()->juxianList->at(m_nextSelected)->recruitCommandCount;//聚仙令
    int retime = JuxianListDataManager::getInstance()->juxianList->at(m_nextSelected)->remainingTimes;//剩余时间
    log("求贤若渴令数量：%d",recruitCommandCount);
    if (m_tag == 0) {
        if (recruitCommandCount == 0 && retime != 0 )//recruitCommandCount == 0 && m_freeCount == 0
        {
            juxianWindowLayer::show(m_nextSelected+1, 1);
        }else if(recruitCommandCount == 0 && m_freeCount == 0)
        {
            juxianWindowLayer::show(m_nextSelected+1, 1);
        }else
        {
            requesttimesMsg(m_nextSelected+1,1);
        }
    }else if (m_tag == 1)
    {
//        if (recruitCommandCount == 0 && m_freeCount == 0) {
            juxianWindowLayer::show(m_nextSelected+1, 2);
//        }
//        else
//        {
//             NoticeManager::getInstance()->showNotice("有免费次数或举贤令，不可以十连抽");
//        }
    }
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumCard1Times);
}


void MarketJuxianLayer::setGoldCount()
{
    Node* node = (Node*)this->getChildByTag(TAG_DEXNODE);
    if (node) {
        this->removeChildByTag(TAG_DEXNODE);
    }
    node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    
    JuxianListData* data = JuxianListDataManager::getInstance()->juxianList->at(m_nextSelected);
    int m_freeCount = data->freeCount;//免费次数
    int recruitCommandCount = data->recruitCommandCount;//聚仙令
    int retime = data->remainingTimes;//剩余时间
    string oneStr = "";
    if (recruitCommandCount <= 0   )//recruitCommandCount == 0 && m_freeCount == 0
    {
        if (retime != 0 || m_freeCount == 0 ) {
            if(data->ConId == DictRolePropEnumGold)
            {
                oneStr = StringUtils::format("花费%d元宝",JuxianListDataManager::getInstance()->juxianList->at(m_nextSelected)->oneConVal);
            }
            else if(data->ConId == DictRolePropEnumHonor)
            {
                oneStr = StringUtils::format("花费%d军工",JuxianListDataManager::getInstance()->juxianList->at(m_nextSelected)->oneConVal);
                
            }else if (data->ConId == DictRolePropEnumCoin)
            {
                oneStr = StringUtils::format("花费%d铜钱",JuxianListDataManager::getInstance()->juxianList->at(m_nextSelected)->oneConVal);
            }
        }
        else{
            oneStr = StringUtils::format("免费抽取");
        }
        
        
    }
    else{
        if (retime != 0) {
            oneStr = StringUtils::format("花费举贤令抽取");
        }
        else{
            oneStr = StringUtils::format("免费抽取");
        }
    }
    Label* label = PublicShowUI::getLabel(oneStr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
    label->setAnchorPoint(Point::ZERO);
    label->setPosition(Point::ZERO);
    node->addChild(label,3);
    
    
    //抽十次
    if(data->ConId == DictRolePropEnumGold)
    {
        oneStr = StringUtils::format("花费%d元宝",JuxianListDataManager::getInstance()->juxianList->at(m_nextSelected)->tenConVal);
    }
    else if(data->ConId == DictRolePropEnumHonor)
    {
        oneStr = StringUtils::format("花费%d军工",JuxianListDataManager::getInstance()->juxianList->at(m_nextSelected)->tenConVal);
        
    }else if (data->ConId == DictRolePropEnumCoin)
    {
        oneStr = StringUtils::format("花费%d铜钱",JuxianListDataManager::getInstance()->juxianList->at(m_nextSelected)->tenConVal);
    }
    Label* tenlabel = PublicShowUI::getLabel(oneStr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
    tenlabel->setAnchorPoint(Point::ZERO);
    tenlabel->setPosition(340,0);
    node->addChild(tenlabel,3);
    
    
    Size size = label->getContentSize();
    size.width = tenlabel->getPositionX()+ tenlabel->getContentSize().width;
    node->setContentSize(size);
    
    node->setPosition(180,-80);
    this->addChild(node,7,TAG_DEXNODE);
}

void MarketJuxianLayer::setFreeTimes()
{
    MarketRotateLayer *menu = (MarketRotateLayer*)this->getChildByTag(TAG_MENU);
    ssize_t len = JuxianListDataManager::getInstance()->juxianList->size();
    Node* card = NULL;

    for (int i = 0; i<len; i++) {
        if (i == 3) {
            return;
        }
        if (i == 0) {
            card = menu->getChildByTag(2);
            
        }else if (i == 1){
            card = menu->getChildByTag(0);
        }else if (i == 2){
            card = menu->getChildByTag(1);
        }
        int  m_freecount = JuxianListDataManager::getInstance()->juxianList->at(i)->freeCount;
        int  m_maxcount = JuxianListDataManager::getInstance()->juxianList->at(i)->freecountMsx;
        if (m_freecount < m_maxcount  &&  m_freecount > 0 && JuxianListDataManager::getInstance()->juxianList->at(i)->remainingTimes!=0)
        {
            card->removeChildByTag(TAG_TIMELABEL);
    
            if (i == 0) {
                setlastTime(2);
            }else if (i == 1){
                setlastTime(0);
            }else if (i == 2){
                setlastTime(1);
            }
            string wordStr="后免费";
            Label* labelword = (Label*)card->getChildByTag(TAG_LABELWORD);
            if (labelword)
            {
                labelword->setString(wordStr);
            }
            else
            {
                labelword = PublicShowUI::getLabel(wordStr.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),18,false,false);
                labelword->setAnchorPoint(Point::ZERO);
                card->addChild(labelword,10,TAG_LABELWORD);
            }
            labelword->setPosition(card->getContentSize().width/2+10,60);
            card->removeChildByTag(TAG_TIMELABEL);
        }else if(m_freecount <= 0  )
        {
            if(i == 0)
            {
                string wordStr="今日免费次数已用尽";
                Label* labelword = (Label*)card->getChildByTag(TAG_TIMEOUT);
                if (labelword)
                {
                    labelword->setString(wordStr);
                }
                else
                {
                    labelword = PublicShowUI::getLabel(wordStr.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),18,false,false);
                    labelword->setAnchorPoint(Point::ZERO);
                    card->addChild(labelword,10,TAG_TIMEOUT);
                }
                labelword->setPosition(card->getContentSize().width/2-labelword->getContentSize().width/2,60);
                card->removeChildByTag(TAG_TIMELABEL);
            }else{
                card->removeChildByTag(TAG_TIMELABEL);
                
                if (i == 0) {
                    setlastTime(2);
                }else if (i == 1){
                    setlastTime(0);
                }else if (i == 2){
                    setlastTime(1);
                }
                string wordStr="后免费";
                Label* labelword = (Label*)card->getChildByTag(TAG_LABELWORD);
                if (labelword)
                {
                    labelword->setString(wordStr);
                }
                else
                {
                    labelword = PublicShowUI::getLabel(wordStr.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),18,false,false);
                    labelword->setAnchorPoint(Point::ZERO);
                    card->addChild(labelword,10,TAG_LABELWORD);
                }
                labelword->setPosition(card->getContentSize().width/2+10,60);
                card->removeChildByTag(TAG_TIMELABEL);
            }
        }
        else
        {
            card->removeChildByTag(TAG_TIMELABEL);
            card->removeChildByTag(TAG_LABELWORD
                                   );
            string timesStr=StringUtils::format("%d/%d",m_freecount,m_maxcount);
            Label* timesLabel = (Label*)this->getChildByTag(TAG_TIMELABEL);
            timesStr = "免费抽取" + timesStr + "次";
            if(timesLabel)
            {
                timesLabel->setString(timesStr.c_str());
            }
            else
            {
                timesLabel = PublicShowUI::getLabel(timesStr.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),18,false,false);
                timesLabel->setAnchorPoint(Point::ZERO);
                card->addChild(timesLabel,10,TAG_TIMELABEL);
            }
            timesLabel->setPosition(card->getContentSize().width/2-65,60);
            card->removeChildByTag(TAG_LABELWORD);
        }
    }
}
void MarketJuxianLayer::settokencount()
{
    MarketRotateLayer *menu = (MarketRotateLayer*)this->getChildByTag(TAG_MENU);
    ssize_t len = JuxianListDataManager::getInstance()->juxianList->size();
    Node* card = NULL;
    int recruitCommandCount=0;
    for (int i = 0; i<len; i++) {
        if (i == 3) {
            return;
        }
        card = menu->getChildByTag(i);
        if(!card)
        {
            continue;
        }
        if (i==0) {
            recruitCommandCount = JuxianListDataManager::getInstance()->juxianList->at(1)->recruitCommandCount;
        }else if (i == 1){
            recruitCommandCount = JuxianListDataManager::getInstance()->juxianList->at(2)->recruitCommandCount;
        }else if (i == 2){
            recruitCommandCount = JuxianListDataManager::getInstance()->juxianList->at(0)->recruitCommandCount;
        }
        string wordStr = "";
        if (i == 2)
        {
             wordStr=StringUtils::format("       %d枚",recruitCommandCount);//普通招募令
        }
        else if (i == 0)
        {
             wordStr=StringUtils::format("       %d枚",recruitCommandCount);//高级招募令
        }
        else if (i == 1)
        {
             wordStr=StringUtils::format("       %d枚",recruitCommandCount);//超级招募令
        }
        Label* labelword = (Label*)card->getChildByTag(TAG_TOKEN);
        if (labelword)
        {
            labelword->setString(wordStr);
        }
        else
        {
            labelword = PublicShowUI::getLabel(wordStr.c_str(),PublicShowUI::getColor3b(COLOR_LIGHT_RED),18,false,false);
            labelword->setAnchorPoint(Point::ZERO);
            card->addChild(labelword,10,TAG_TOKEN);
        }
        labelword->setPosition(card->getContentSize().width/2-labelword->getContentSize().width/2 ,20);
    }
}

void MarketJuxianLayer::setlastTime(int nextSelected)
{
    MarketRotateLayer *menu = (MarketRotateLayer*)this->getChildByTag(TAG_MENU);
    Node* card = NULL;
    card = menu->getChildByTag(nextSelected);

    if (nextSelected==0) {
        if (this->getChildByTag(TAG_TIME2)) {
            return;
        }
        pTime2 = JuxianListDataManager::getInstance()->juxianList->at(1)->remainingTimes;
        string recuittime=StringUtils::format("%02ld:%02ld:%02ld",pTime2/3600, pTime2%3600/60,pTime2%60);
        if (label2) {
            label2->setString(recuittime);
        }else{
            label2 = PublicShowUI::getLabel(recuittime.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),18,false,false);
            label2->setAnchorPoint(Point::ZERO);
            card->addChild(label2,10,TAG_TIME2);
        }
        label2->setPosition(card->getContentSize().width/2-75,60);
        schedule(schedule_selector(MarketJuxianLayer::update2),1);
            
    }else if (nextSelected == 1){
        if (this->getChildByTag(TAG_TIME3)) {
            return;
        }
        pTime3 = JuxianListDataManager::getInstance()->juxianList->at(2)->remainingTimes;
        string recuittime=StringUtils::format("%02ld:%02ld:%02ld",pTime3/3600, pTime3%3600/60,pTime3%60);
        if (label3) {
            label3->setString(recuittime);
        }else{
            label3 = PublicShowUI::getLabel(recuittime.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),18,false,false);
            label3->setAnchorPoint(Point::ZERO);
            card->addChild(label3,10,TAG_TIME3);
        }
        label3->setPosition(card->getContentSize().width/2-75,60);
        schedule(schedule_selector(MarketJuxianLayer::update3),1);
    }else if (nextSelected == 2){
        if (this->getChildByTag(TAG_TIME1)) {
            return;
        }
        pTime = JuxianListDataManager::getInstance()->juxianList->at(0)->remainingTimes;
        string recuittime=StringUtils::format("%02ld:%02ld:%02ld",pTime/3600, pTime%3600/60,pTime%60);
        if (label) {
            label->setString(recuittime);
        }else{
            label = PublicShowUI::getLabel(recuittime.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),18,false,false);
            label->setAnchorPoint(Point::ZERO);
            card->addChild(label,10,TAG_TIME1);
        }
        label->setPosition(card->getContentSize().width/2-75,60);
        schedule(schedule_selector(MarketJuxianLayer::update),1);
    }else{
        return;
    }
}
void MarketJuxianLayer::update(float delta)
{
    pTime -= 1;
    if (pTime <= 0) {
        pTime =0;
        
        log("aaaaaaaaaaaaaaaa");
        
        unschedule(schedule_selector(MarketJuxianLayer::update));
        MarketRotateLayer *menu = (MarketRotateLayer*)this->getChildByTag(TAG_MENU);
        Node* card = NULL;
        card = menu->getChildByTag(2);
        Label* lab = (Label*)card->getChildByTag(TAG_LABELWORD);
        lab->setVisible(false);
        label->setVisible(false);
        requestListMsg();
        return;
    }
    char* mtime = new char[10];
    //显示小时，分钟，秒
    sprintf(mtime,"%02ld:%02ld:%02ld",pTime/3600, pTime%3600/60, pTime%60);
    label->setString(mtime);
}
void MarketJuxianLayer::update2(float delta)
{
    pTime2 -= 1;
    if (pTime2 <= 0){
        pTime2 =0;
         log("bbbbbbbbbbbbbbbbbbb");
        unschedule(schedule_selector(MarketJuxianLayer::update2));
        MarketRotateLayer *menu = (MarketRotateLayer*)this->getChildByTag(TAG_MENU);
        Node* card = NULL;
        card = menu->getChildByTag(0);
        Label* lab = (Label*)card->getChildByTag(TAG_LABELWORD);
        lab->setVisible(false);
        label2->setVisible(false);
        requestListMsg();
        return;
    }
    char*mtime = new char[10];
    //显示小时，分钟，秒
    sprintf(mtime,"%02ld:%02ld:%02ld",pTime2/3600, pTime2%3600/60,pTime2%60);
    label2->setString(mtime);
}
void MarketJuxianLayer::update3(float delta)
{
    pTime3 -= 1;
    if (pTime3 <= 0) {
        pTime3 =0;
         log("cccccccccccccccc");
        unschedule(schedule_selector(MarketJuxianLayer::update3));
        MarketRotateLayer *menu = (MarketRotateLayer*)this->getChildByTag(TAG_MENU);
        Node* card = NULL;
        card = menu->getChildByTag(1);
        Label* lab = (Label*)card->getChildByTag(TAG_LABELWORD);
        lab->setVisible(false);
        label3->setVisible(false);
       requestListMsg();
        return;
    }
    char*mtime = new char[10];
    //显示小时，分钟，秒
    sprintf(mtime,"%02ld:%02ld:%02ld",pTime3/3600, pTime3%3600/60,pTime3%60);
    label3->setString(mtime);
}
void MarketJuxianLayer::changeCardPosProcess(EventCustom* msg)//跟新卡牌位置消息
{
    __Integer* inter = (__Integer*)msg->getUserData();
    m_nextSelected = inter->getValue();
    
//        MarketRotateLayer *menu = (MarketRotateLayer*)this->getChildByTag(TAG_MENU);
//        Node* card = NULL;
//        card = menu->getChildByTag(m_nextSelected);
//        MoveBy* move1 = MoveBy::create(2, Point( 0,10));
//        MoveBy* move2 = MoveBy::create(2, Point(0,-10));
//        Sequence* seq = Sequence::create(move1,move2, NULL);
//        RepeatForever* rep = RepeatForever::create(seq);
//        card->runAction(rep);

    
    if (m_nextSelected == 0){
        m_nextSelected = 1;
    }else if(m_nextSelected == 1){
        m_nextSelected =2;
    }else if (m_nextSelected == 2){
        m_nextSelected = 0;
    }
}

/******---------------1111111111111--------1111--------------访问服务器---------------1111-------111111111111--------------*************/
void MarketJuxianLayer::requestListMsg()//请求列表信息
{
    Dialog::showServerLoading();
    JuxianListMsg* msg = new JuxianListMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void MarketJuxianLayer::onMsgProcess(EventCustom* msg)//获取列表信息返回值
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    JuxianListDataManager::getInstance()->clearjuxianList();
    
    if(message->messageID == SCENSE_CLIENT_LEAD_LeadPageResp)
    {
        if(message->state)//返回成功
        {
            int leadCount = message->byteStream->getByte();
            for (int i = 0; i < leadCount; i ++) {
                JuxianListData* data = new JuxianListData;
                data->autorelease();
                data->freeCount = message->byteStream->getInt();
                data->freecountMsx = message->byteStream->getInt();
                data->recruitCommandCount = message->byteStream->getInt();
                data->ConId = message->byteStream->getByte();
                data->oneConVal = message->byteStream->getInt();
                data->tenConVal = message->byteStream->getInt();
                data->remainingTimes = message->byteStream->getInt();
                JuxianListDataManager::getInstance()->addData(data);
            }
            this->setFreeTimes();
            this->settokencount();
            this->setGoldCount();
            broadMsg(CUSTOM_REFRESH_DOT,__Integer::create(DictFunctionEnumLead));
            
        }
    }
}

void MarketJuxianLayer::requesttimesMsg(int leadId, int countMode)//发送举贤次数
{
    Dialog::showServerLoading();
    JuxianTimeMsg* msg = new JuxianTimeMsg(leadId,countMode);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void MarketJuxianLayer::onTimeMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    MarketFindResultDataManager::getInstance()->clearDumpList();
    if(message->messageID == SCENSE_CLIENT_LEAD_LeadResp)
    {
        if(message->state)//返回成功
        {
            MarketFindResultData* data = new MarketFindResultData;
            data->autorelease();
            int countMode = message->byteStream->getByte();
            JuxianListDataManager::getInstance()->juxianList->at(m_nextSelected)->remainingTimes = message->byteStream->getInt();
            int itemCount = message->byteStream->getByte();
            if (countMode == 1) {//countMode=1 下行数据增加一个免费剩余时间
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
//                    broadMsg(CUSTOM_MARKER_HEROLAYER);//获得武将 
                    MarketGetHeroLayer::show(MarketFindResultDataManager::getInstance()->dumpList->at(0));
                }else if(data->itemType>1 && data->itemType<7){
                    data->dictId = message->byteStream->getInt();
                    data->name = message->byteStream->getUTF8();
                    data->quality = message->byteStream->getByte();
                    data->itemDesc = message->byteStream->getUTF8();
                    
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
                    scene->addChild(layer);
//                    MarketFindResultDataManager::getInstance()->addData(data);
//                    MarketGetEquipLayer::show();
//                    broadMsg(CUSTOM_MARKER_EQUIPLAYER);//获得物品
                }else{
                    log("类型错误：itemType=====%d",data->itemType);
                }
                requestListMsg();
//                broadMsg(CUSTOM_REFRESH_DOT,__Integer::create(DictFunctionEnumLead));
                
//                JuxianListData *data = JuxianListDataManager::getInstance()->juxianList->at(m_nextSelected);
//                if (data->freeCount > 0)
//                {
//                    data->freeCount -= 1;
//                }
//                else if (data->freeCount <= 0)
//                {
//                    if (data->recruitCommandCount > 0)
//                    {
//                        data->recruitCommandCount -= 1;
//                        requestListMsg();
//                        return;
//                    }
//                    else if (data->recruitCommandCount <= 0)
//                    {
//                        requestListMsg();
//                        return;
//                    }
//                }
//                this->setFreeTimes();
            }
            else if (countMode == 2) {
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
                
                broadMsg(CUSTOM_MARKER_CTEATTENITEM);
                requestListMsg();
            }
        }
    }
}
void MarketJuxianLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LEAD_LeadPageResp).c_str(), CC_CALLBACK_1(MarketJuxianLayer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LEAD_LeadResp).c_str(), CC_CALLBACK_1(MarketJuxianLayer::onTimeMsgProcess, this));
    this->addUserMsg(CUSTOM_MARKER_CHANGECARDPOS, CC_CALLBACK_1(MarketJuxianLayer::changeCardPosProcess, this));
}
void MarketJuxianLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}

void MarketJuxianLayer::clearResourcePerson()//清除人物资源
{
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("");
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    ArmatureDataManager::destroyInstance();
}

void MarketJuxianLayer::tableCellTouched(Ref* target)
{
    this->runAction(Sequence::create(DelayTime::create(.2), CallFunc::create(CC_CALLBACK_0(MarketJuxianLayer::changParticle, this)), NULL));
}
void MarketJuxianLayer::changParticle()
{
    setGoldCount();
    setparticle();
}
void MarketJuxianLayer::scrollViewDidScroll(Ref* target)
{

    this->removeChildByTag(TAG_PARTICLE);

}
void MarketJuxianLayer::setOrderCard(Node* parent,JuxianListData* data)
{
    //    this->removeChildByTag(TAG_ICON);
    //    Sprite* icon = NULL;
    ////    icon = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    //    if(data->ConId == DictRolePropEnumGold)
    //    {
    //        icon = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    //    }
    //    else if(data->ConId == DictRolePropEnumHonor)
    //    {
    //        icon = Sprite::create(IMG_ICON_JUNGONG);
    //    }
    //    else if(data->ConId == DictRolePropEnumRecruitCommand1)
    //    {
    //        icon = Sprite::create(IMG_ICON_QIEXIANRUOKE);
    //    }
    //    else if(data->ConId == DictRolePropEnumRecruitCommand2)
    //    {
    //        icon = Sprite::create(IMG_ICON_LIXIANXIASHI);
    //    }
    //    else if(data->ConId == DictRolePropEnumRecruitCommand3)
    //    {
    //        icon = Sprite::create(IMG_ICON_WEICAISHIJU);
    //    }
    //    icon->setAnchorPoint(Point::ZERO);
    //    icon->setScale(0.7);
    //    icon->setPosition(550,105);
    //    parent->addChild(icon,10,TAG_ICON);
}
void MarketJuxianLayer::settimesUpdata(int tag)
{
    
    //    if (!isfirst) {
    //        this->getChildByTag(m_tag_time)->setVisible(false);
    //    }
    //    switch (tag) {
    //        case 0:
    //            m_tag_time = TAG_TIME1;
    //            break;
    //        case 1:
    //            m_tag_time = TAG_TIME2;
    //            break;
    //        case 2:
    //            m_tag_time = TAG_TIME3;
    //            break;
    //        default:
    //            break;
    //    }
    //    this->getChildByTag(m_tag_time)->setVisible(true);
    //    isfirst = false;         
}
