//
//  VipTequanLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/12.
//
//

#include "VipTequanLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../commonData/dictData/DictVip/DictVipManager.h"
#include "../../../commonData/dictData/DictVipGift/DictVipGiftManager.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../common/StringUtil.h"
#include "../../tips/TipsLayer.h"
#include "../VipLayer.h"
VipTequanLayer::VipTequanLayer()
:TAG_VIPLEVEL(10)
,m_level(0)
,giftList(NULL)
,TAG_MINLEVEL(11)
,TAG_LEVEL(12)
,TAG_ADDLEVEL(13)
,TAG_NODE(14)
,TAG_DEXLEVEL(15)
{
    giftList = DictVipGiftManager::getInstance()->getDataList();
    
    giftListitem = new Vector<DictVipGift*>();
}
VipTequanLayer::~VipTequanLayer()
{
    CC_SAFE_DELETE(giftList);
    giftList = NULL;
    giftListitem->clear();
    CC_SAFE_DELETE(giftListitem);
}
bool VipTequanLayer::init( int _level)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        m_level = _level;
        this->setBackground(IMG_VIP_TEQUANBG,Point::ZERO,true);
        this->setClickEnabled(true);
        this->isClickClose = true;
        this->isShowGrayBg = true;
        setButton();
        setVIPlevel();
        setGiftHead();
        bref = true;
    } while (false);
    return bref;
}
VipTequanLayer* VipTequanLayer::create(int _level)
{
    VipTequanLayer* layer= new VipTequanLayer();
    if(layer && layer->init(_level))
    {
        layer->autorelease();
        
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}

void VipTequanLayer::show(int _level)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    VipTequanLayer* layer = VipTequanLayer::create(_level);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}
void VipTequanLayer::setButton()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Button* leftBtn = Button::create(IMG_STAGE_RIGHTBTN,IMG_STAGE_RIGHTBTN,CC_CALLBACK_1(VipTequanLayer::leftPage, this));
    leftBtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(leftBtn);
    leftBtn->setRotation(180);
    leftBtn->setPosition(leftBtn->getContentSize().width + 20*sx,this->getContentSize().height/2-leftBtn->getContentSize().height/2+leftBtn->getContentSize().height);
    this->addChild(leftBtn,5);
    
    Button* rightBtn = Button::create(IMG_STAGE_RIGHTBTN,IMG_STAGE_RIGHTBTN,CC_CALLBACK_1(VipTequanLayer::rightPage, this));
    rightBtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(rightBtn);
    rightBtn->setPosition(this->getContentSize().width -rightBtn->getContentSize().width - 20*sx,this->getContentSize().height/2-rightBtn->getContentSize().height/2);
    
    this->addChild(rightBtn,5);
}
void VipTequanLayer::leftPage(Ref* psender)
{
    if (m_level == 0) {
        m_level = 0;
        return;
    }
    m_level -= 1;
    setGiftHead();
    
}
void VipTequanLayer::rightPage(Ref* psender)
{
    int len = giftList->at(0)->day;
    log("%d",len);
    if (m_level == len) {
        return;
    }
    m_level += 1;
    setGiftHead();
}
void VipTequanLayer::setVIPlevel()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* vipSpr = (Sprite*)this->getChildByTag(TAG_VIPLEVEL);
    if (!vipSpr) {
        vipSpr = Sprite::create(IMG_VIP_RECHARGE_VIPBG);
        vipSpr->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(vipSpr);
        vipSpr->setPosition(this->getContentSize().width/2-180*sx,this->getContentSize().height-150*sx);
        this->addChild(vipSpr, 1, TAG_VIPLEVEL);
        log("dfdsf");
        
        Sprite* vip1 = Sprite::create(IMG_VIP_RECHARGE_VIPBG);
        vip1->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(vip1);
        vip1->setScale(.8*sx);
        vip1->setPosition(this->getContentSize().width/2-150*sx,this->getContentSize().height/2-105*sx);
        this->addChild(vip1, 1);
        Sprite* viptequan = Sprite::create(IMG_PUBLIC_LABEL_TEQUANLIBAO);
        viptequan->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(viptequan);
        viptequan->setPosition(vip1->getPositionX()+vip1->getContentSize().width-10*sx,vip1->getPositionY()-5*sx);
        this->addChild(viptequan, 1);
        
        Button* btn = Button::create(IMG_PUBLIC_BUTTON_FOUR_GREEN, IMG_PUBLIC_BUTTON_FOUR_GREEN, CC_CALLBACK_1(VipTequanLayer::onclick, this));
        btn->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(btn);
        btn->setPosition(this->getContentSize().width/2-btn->getContentSize().width/2,30*sx);
        this->addChild(btn,1);
        Sprite* btnword = Sprite::create(IMG_PUBLIC_LABEL_GOUMAILIBAO);
        btnword->setAnchorPoint(Point::ZERO);
        btnword->setPosition(Point::ZERO);
        btn->addChild(btnword,4);
    }
}
void VipTequanLayer::onclick(Ref* pSender)
{
    VipLayer::show(SCENE_TAG_MAINUI,VipLayer::TAG_LIBAO);
}
void VipTequanLayer::setGiftHead()                                                                                                                                                                                                                                   
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    //当前等级
    string level = StringUtils::format("%d",m_level);
    Label* levelLabel = (Label*)this->getChildByTag(TAG_LEVEL);
    if (levelLabel) {
        levelLabel->setString(level);
    }else{
        levelLabel = PublicShowUI::getLabel(level.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT),40,false,false);
        levelLabel->setAnchorPoint(Point(Point::ZERO));
        PublicShowUI::setTargetScale(levelLabel);
        this->addChild(levelLabel,2,TAG_LEVEL);
    }
    levelLabel->setPosition(this->getContentSize().width/2-85*sx,this->getContentSize().height-152*sx);
    
    //上一等级
    string levelmin = StringUtils::format("%d",m_level-1);
    levelmin = "VIP"+levelmin;
    Label* levelLabelmin = (Label*)this->getChildByTag(TAG_MINLEVEL);
    if (levelLabelmin) {
        levelLabelmin->setString(levelmin);
    }else{
        levelLabelmin = PublicShowUI::getLabel(levelmin.c_str(),PublicShowUI::getColor3b(COLOR_DEEP_BROWN),20,false,false);
        levelLabelmin->setAnchorPoint(Point(Point::ZERO));
        PublicShowUI::setTargetScale(levelLabelmin);
        this->addChild(levelLabelmin,2,TAG_MINLEVEL);
    }
    levelLabelmin->setPosition(30*sx,this->getContentSize().height/2 + 30*sx);
    if (m_level == 0) {
        levelLabelmin->setVisible(false);
    }else{
        levelLabelmin->setVisible(true);
    }
    
    //下一等级
    string leveladd = StringUtils::format("%d",m_level+1);
    leveladd = "VIP"+leveladd;
    Label* levelLabeladd = (Label*)this->getChildByTag(TAG_ADDLEVEL);
    if (levelLabeladd) {
        levelLabeladd->setString(leveladd);
    }else{
        levelLabeladd = PublicShowUI::getLabel(leveladd.c_str(),PublicShowUI::getColor3b(COLOR_DEEP_BROWN),20,false,false);
        levelLabeladd->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(levelLabeladd);
        this->addChild(levelLabeladd,2,TAG_ADDLEVEL);
    }
    levelLabeladd->setPosition(this->getContentSize().width -levelLabeladd->getContentSize().width-40*sx,this->getContentSize().height/2+30*sx);
    if (m_level == giftList->at(0)->day) {
        levelLabeladd->setVisible(false);
    }else{
        levelLabeladd->setVisible(true);
    }
    
    
    int index = 0;
    Node* container =(Node*)this->getChildByTag(TAG_NODE);
    if (container) {
        this->removeChildByTag(TAG_NODE);
    }
    container =  Node::create();
    container->setAnchorPoint(Point::ZERO);
    const char* path = NULL;
    UserEquipLayer* head = NULL;
    giftListitem->clear();
    for (DictVipGift* data : *giftList)
    {
        if(data->day == m_level)
        {
            path = PublicShowUI::getGoods(data->itemType, data->itemId);
            int quality = PublicShowUI::getQuality(data->itemType, data->itemId);
            head = UserEquipLayer::create(path,quality,false);
            if(head)
            {
                head->setAnchorPoint(Point::ZERO);
                if (data->itemType == 4) {
                    head->setFragment();
                }else if (data->itemType == 3)
                {
                    head->setLetterFragment();
                }
                PublicShowUI::setTargetScale(head);
                head->setPositionX(index * (head->getContentSize().width+20*sx));
                head->addTouchBegainCallBack(this, callfuncN_selector(VipTequanLayer::onitemClick));
                container->addChild(head,1,index);
                giftListitem->pushBack(data);
                index++;
            }
        }
    }
    if(head)
    {
        Size size = head->getContentSize();
        size.width = head->getPositionX() + head->getContentSize().width;
        container->setContentSize(size);
        container->setPosition(140*sx, this->getContentSize().height/2-container->getContentSize().height/2 - 170*sx);
        this->addChild(container,10,TAG_NODE);
    }

    //描述
    
    string leveldex = DictVipManager::getInstance()->getData(m_level)->desc;
    vector<string> list = StringUtil::split(leveldex, "；");
    ssize_t len = list.size();
    string str = "";
    for(int i = 0; i < len; i++)
    {
        if(i < len - 1)
        {
             str += list[i] + ";\n";
        }
        else
        {
            str += list[i];
        }
    }
    Label* leveldesLabel = (Label*)this->getChildByTag(TAG_DEXLEVEL);
    if (leveldesLabel) {
        leveldesLabel->setString(str);
    }else{
    
    leveldesLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_DEEP_BROWN),24,false,false);
//    leveldesLabel->setAnchorPoint(Point(Point::ZERO));
    PublicShowUI::setTargetScale(leveldesLabel);
    leveldesLabel->setMaxLineWidth(500*sx);
    this->addChild(leveldesLabel,2,TAG_DEXLEVEL);
    }
    leveldesLabel->setPosition(this->getContentSize().width/2, this->getContentSize().height/2 + 40*sx);
    
    list.clear();
}
void VipTequanLayer::onitemClick(Node* pSender)
{
    log("%d",pSender->getTag());
    TipsLayer::show(giftListitem->at(pSender->getTag())->itemType,giftListitem->at(pSender->getTag())->itemId,0 );
}
void VipTequanLayer::onEnter()
{
    BaseLayer::onEnter();
}
void VipTequanLayer::onExit()
{
    BaseLayer::onExit();
}
void VipTequanLayer::onEnterTransitionDidFinish()
{
    
    BaseLayer::onEnterTransitionDidFinish();
    
}
void VipTequanLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}

bool VipTequanLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    touchBeginPos = touch->getLocation();

    return true;
}
void VipTequanLayer::onTouchMoved(Touch *touch, Event *unused_event)
{

}
void VipTequanLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    if(touch->getLocation().x - touchBeginPos.x > 20)
    {
        leftPage(NULL);
        log("right");
    }
    else if(touch->getLocation().x - touchBeginPos.x < -20)
    {
        rightPage(NULL);
        log("left");
    }
    BaseLayer::onTouchEnded(touch, unused_event);
}
