//
//  VipHeadGiftLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/30.
//
//

#include "VipHeadGiftLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../commonData/dictData/DictVip/DictVipManager.h"
#include "../../../commonData/dictData/DictVipGift/DictVipGiftManager.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../common/StringUtil.h"
#include "../../tips/TipsLayer.h"
VipHeadGiftLayer::VipHeadGiftLayer()
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
VipHeadGiftLayer::~VipHeadGiftLayer()
{
    CC_SAFE_DELETE(giftList);
    giftList = NULL;
    giftListitem->clear();
    CC_SAFE_DELETE(giftListitem);
}
bool VipHeadGiftLayer::init( int _level)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        m_level = _level;
        this->setBackground(IMG_DIALOG_BG,Point::ZERO,true);
        this->setClickEnabled(true);
        this->isClickClose = true;
        this->isShowGrayBg = true;
      
        setVIPlevel();
        setGiftHead();
        bref = true;
    } while (false);
    return bref;
}
VipHeadGiftLayer* VipHeadGiftLayer::create(int _level)
{
    VipHeadGiftLayer* layer= new VipHeadGiftLayer();
    if(layer && layer->init(_level))
    {
        layer->autorelease();
        
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}

void VipHeadGiftLayer::show(int _level)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    VipHeadGiftLayer* layer = VipHeadGiftLayer::create(_level);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}
void VipHeadGiftLayer::setVIPlevel()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* vipSpr = (Sprite*)this->getChildByTag(TAG_VIPLEVEL);
    if (!vipSpr) {
        vipSpr = Sprite::create(IMG_VIP_RECHARGE_VIPBG);
        vipSpr->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(vipSpr);
        vipSpr->setPosition(this->getContentSize().width/2-150*sx,this->getContentSize().height-100*sx);
        this->addChild(vipSpr, 1, TAG_VIPLEVEL);
        log("dfdsf");
        Sprite* viptequan = Sprite::create(IMG_PUBLIC_LABEL_TEQUANLIBAO);
        viptequan->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(viptequan);
        viptequan->setPosition(vipSpr->getPositionX()+vipSpr->getContentSize().width+50*sx,vipSpr->getPositionY());
        this->addChild(viptequan, 1);
    }
    
}
void VipHeadGiftLayer::setGiftHead()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;

    //当前等级
    string level = StringUtils::format("%d",m_level);
    Label* levelLabel = (Label*)this->getChildByTag(TAG_LEVEL);
    if (levelLabel) {
        levelLabel->setString(level);
    }else{
        levelLabel = PublicShowUI::getLabel(level.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT),30,false,false);
        levelLabel->setAnchorPoint(Point(Point::ZERO));
        PublicShowUI::setTargetScale(levelLabel);
        this->addChild(levelLabel,2,TAG_LEVEL);
    }
    levelLabel->setPosition(this->getContentSize().width/2-58*sx,this->getContentSize().height-100*sx);
    
    int index = 0;
    Node* container =(Node*)this->getChildByTag(TAG_NODE);
    if (container) {
        this->removeChildByTag(TAG_NODE);
    }
    container =  Node::create();
    container->setAnchorPoint(Point::ZERO);
    const char* path = NULL;
    UserEquipLayer* head = NULL;
    Label* countLabel = NULL;
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
                head->setPositionX(index * (head->getContentSize().width+10*sx));
                head->addTouchBegainCallBack(this, callfuncN_selector(VipHeadGiftLayer::onitemClick));
                container->addChild(head,1,index);
                giftListitem->pushBack(data);
                
                
                string countstr = StringUtils::format("x%d",data->itemNumber);
                countLabel = (Label*)this->getChildByTag(TAG_LEVEL);
                countLabel = PublicShowUI::getLabel(countstr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),22,false,false);
                countLabel->setAnchorPoint(Point(Point::ZERO));
                PublicShowUI::setTargetScale(countLabel);
                countLabel->setPosition(head->getPositionX()+head->getContentSize().width/2+15*sx,head->getPositionY()+60*sx);
                this->addChild(countLabel,2);
                
                index++;
            }
        }
    }
    if(head)
    {
        Size size = head->getContentSize();
        size.width = head->getPositionX() + head->getContentSize().width;
        container->setContentSize(size);
        container->setPosition(30*sx, this->getContentSize().height/2-container->getContentSize().height/2-10*sx );
        this->addChild(container,10,TAG_NODE);
    }
    
}
void VipHeadGiftLayer::onitemClick(Node* pSender)
{
    log("%d",pSender->getTag());
    TipsLayer::show(giftListitem->at(pSender->getTag())->itemType,giftListitem->at(pSender->getTag())->itemId,0 );
}
void VipHeadGiftLayer::onEnter()
{
    BaseLayer::onEnter();
}
void VipHeadGiftLayer::onExit()
{
    BaseLayer::onExit();
}
void VipHeadGiftLayer::onEnterTransitionDidFinish()
{
    
    BaseLayer::onEnterTransitionDidFinish();
    
}
void VipHeadGiftLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}

