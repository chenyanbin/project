//
//  MarketGetEquipLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/6.
//
//

#include "MarketGetEquipLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../marketData/MarketFindResultDataManager.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../tips/TipsLayer.h"
MarketGetEquipLayer::MarketGetEquipLayer()
:m_allGoods(7)
,m_iscloseScene(true)
{
    
}

MarketGetEquipLayer::~MarketGetEquipLayer()
{
}
bool MarketGetEquipLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        
        this->isAnimation = false;
        this->isClickClose = true;
        this->setBackground(IMG_PUBLIC_LAYER_GAIN_BG);
        
        setBackg();
        setCardItem();

        bref = true;
    } while (false);
    return bref;
}

MarketGetEquipLayer* MarketGetEquipLayer::create()
{
    MarketGetEquipLayer* list = new MarketGetEquipLayer();
    if(list && list->init())
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void MarketGetEquipLayer::onEnter()
{
    BaseLayer::onEnter();
    setClickEnabled(true);

}
void MarketGetEquipLayer::onExit()
{
    BaseLayer::onExit();
    setClickEnabled(false);

}
void MarketGetEquipLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void MarketGetEquipLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void MarketGetEquipLayer::show()
{
    Scene* scene = Director::getInstance()->getRunningScene();
    MarketGetEquipLayer* layer = MarketGetEquipLayer::create();
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,SCENE_POPLAYER_ZORDER);

}
void MarketGetEquipLayer::setBackg()
{
//    Size size = VisibleRect::getVisibleRect().size;
//    LayerColor* layer = LayerColor::create(Color4B(0,0,0,200), size.width, size.height);
//    layer->setAnchorPoint(Point::ZERO);
//    this->addChild(layer,-2,TAG_BLACKBG);
//    
//    
//    Sprite* bg = Sprite::create(IMG_PUBLIC_MODULE_BG);
//    bg->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(bg,true,true);
//    bg->setPosition(Point::ZERO);
//    this->setContentSize(bg->getContentSize());
    
    Sprite* spr = Sprite::create(IMG_PUBLIC_LAYER_GAIN_LABEL);
    spr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(spr);
    spr->setPosition((this->getContentSize().width-spr->getContentSize().width)/2,this->getContentSize().height-spr->getContentSize().height/2);
    this->addChild(spr);
}
void MarketGetEquipLayer::setCardItem()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    
    int itemType = MarketFindResultDataManager::getInstance()->getFindTypeData();
    int itemdict =MarketFindResultDataManager::getInstance()->dumpList->at(0)->dictId;
    int itemquality = MarketFindResultDataManager::getInstance()->dumpList->at(0)->quality;
    const char* resource = PublicShowUI::getGoods(itemType, itemdict);
    UserEquipLayer* head = UserEquipLayer::create(resource,itemquality,false);
    head->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(head);
    if (itemType == 4) {
        head->setFragment();
    }else if (itemType == 3)
    {
        head->setLetterFragment();
    }
    
    head->setPosition(Point(0,(this->getContentSize().height-head->getContentSize().height)/2));
    MoveTo* move2 = MoveTo::create(0.2, Point((this->getContentSize().width-head->getContentSize().width)/2,(this->getContentSize().height-head->getContentSize().height)/2));
    head->runAction(move2);
    head->addTouchBegainCallBack(this, callfuncN_selector(MarketGetEquipLayer::onHeadClick));//
    this->addChild(head,2);
    
    
//    //确认按钮
//    Sprite* buyWord = Sprite::create(IMG_MARKET_MARKETFIND_EQUIPBUTTON);
//    buyWord->setAnchorPoint(Point::ZERO);
//    buyWord->setPosition(this->getContentSize().width/2-buyWord->getContentSize().width/2,this->getContentSize().height/2-170*sx);
//    this->addChild(buyWord);
//    Button * surebuy = Button::create(IMG_BUTTON_CONFIRM_LABEL, IMG_BUTTON_CONFIRM_LABEL, CC_CALLBACK_1(MarketGetEquipLayer::onClick, this));
//    surebuy->setAnchorPoint(Point::ZERO);
//    surebuy->setPosition(Point::ZERO);
//    buyWord->addChild(surebuy,2);
    
//    Sprite* juxianbg = Sprite::create(IMG_MARKET_MARKETFIND_EQUIPBG);
//    juxianbg->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(juxianbg);
//    juxianbg->setPosition((this->getContentSize().width-juxianbg->getContentSize().width)/2,(this->getContentSize().height-juxianbg->getContentSize().height)/2);
//    this->addChild(juxianbg);
//    
//    int itemType = MarketFindResultDataManager::getInstance()->getFindTypeData();
//    int itemdict =MarketFindResultDataManager::getInstance()->dumpList->at(0)->dictId;
//    int itemquality = MarketFindResultDataManager::getInstance()->dumpList->at(0)->quality;
//    const char* resource = PublicShowUI::getGoods(itemType, itemdict);
//    UserEquipLayer* head = UserEquipLayer::create(resource,itemquality,false);
//    head->setAnchorPoint(Point::ZERO);
//    if (itemType == 4) {
//        head->setFragment();
//    }else if (itemType == 3)
//    {
//        head->setLetterFragment();
//    }
//    head->setPosition(juxianbg->getContentSize().width/sx/2-head->getContentSize().width/2,juxianbg->getContentSize().height/sx/2-head->getContentSize().height/2+110);
//    juxianbg->addChild(head,2);
//    
//    string typeStr = "";
//    if(itemType == DictItemTypeEnumItemEquip)
//    {
//        typeStr ="装备";
//    }
//    else if (itemType == DictItemTypeEnumItemBook)
//    {
//        typeStr = "书信";
//    }
//    else if (itemType == DictItemTypeEnumItemMater)
//    {
//        typeStr = "材料";
//    }
//    else if (itemType == DictItemTypeEnumItem)
//    {
//        typeStr = "道具";
//    }
//    else if (itemType == DictItemTypeEnumRoleResource)
//    {
//        typeStr = "资源";
//    }
//    Label* typeLabel = PublicShowUI::getLabel(typeStr.c_str(),PublicShowUI::getColor3b(COLOR_BLACK_BROWN),24,false,false);
//    typeLabel->setAnchorPoint(Point::ZERO);
//    typeLabel->setPosition(25,juxianbg->getContentSize().height/sx-typeLabel->getContentSize().height-35);
//    typeLabel->setMaxLineWidth(30);
//    juxianbg->addChild(typeLabel,4);
//    //名字
//    string sellnameStr =MarketFindResultDataManager::getInstance()->dumpList->at(0)->name;
//    Label* sellnameLabel = PublicShowUI::getLabel(sellnameStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),16,false,false);
//    sellnameLabel->setAnchorPoint(Point::ZERO);
//    sellnameLabel->setPosition(juxianbg->getContentSize().width/sx/2-sellnameLabel->getContentSize().width/2,juxianbg->getContentSize().height/sx/2-sellnameLabel->getContentSize().height/2+29);
//    juxianbg->addChild(sellnameLabel,4);
//    
//    string pinzhiStr ="品质";
//    Label* pinzhiLabel = PublicShowUI::getLabel(pinzhiStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),16,false,false);
//    pinzhiLabel->setAnchorPoint(Point::ZERO);
//    pinzhiLabel->setPosition(juxianbg->getContentSize().width/sx/2-pinzhiLabel->getContentSize().width/2-75,juxianbg->getContentSize().height/sx/2-pinzhiLabel->getContentSize().height/2-3);
//    juxianbg->addChild(pinzhiLabel,4);
//    
//    //品质
//    int  pingzhiNum= MarketFindResultDataManager::getInstance()->dumpList->at(0)->quality;
//    string pinzhicountStr =StringUtils::format("%d",pingzhiNum);
//    Label* pinzhicountLabel = PublicShowUI::getLabel(pinzhicountStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),16,false,false);
//    pinzhicountLabel->setAnchorPoint(Point::ZERO);
//    pinzhicountLabel->setPosition(juxianbg->getContentSize().width/sx/2-pinzhicountLabel->getContentSize().width/2+10,juxianbg->getContentSize().height/sx/2-pinzhicountLabel->getContentSize().height/2-5);
//    juxianbg->addChild(pinzhicountLabel,4);
//    //描述
//    string  itemdescStr= MarketFindResultDataManager::getInstance()->dumpList->at(0)->itemDesc;
//    Label* itemdescLabel = PublicShowUI::getLabel(itemdescStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),16,false,false);
//    itemdescLabel->setAnchorPoint(Point(0,1));
//    itemdescLabel->setMaxLineWidth(180);
//    itemdescLabel->setPosition(juxianbg->getContentSize().width/sx/2-90,juxianbg->getContentSize().height/sx/2-30);
//    juxianbg->addChild(itemdescLabel,4);
//    
//    //确认按钮
//    Sprite* buyWord = Sprite::create(IMG_MARKET_MARKETFIND_EQUIPBUTTON);
//    buyWord->setAnchorPoint(Point::ZERO);
//    buyWord->setPosition(juxianbg->getContentSize().width/sx/2-buyWord->getContentSize().width/2,juxianbg->getContentSize().height/sx/2-170);
//    juxianbg->addChild(buyWord);
//    Button * surebuy = Button::create(IMG_BUTTON_CONFIRM_LABEL, IMG_BUTTON_CONFIRM_LABEL, CC_CALLBACK_1(MarketGetEquipLayer::onClick, this));
//    surebuy->setAnchorPoint(Point::ZERO);
//    surebuy->setPosition(Point::ZERO);
//    buyWord->addChild(surebuy,2);
//    
//    Sequence* seq = Sequence::create(ScaleBy::create(.15, 1.1),ScaleBy::create(.1, .9), NULL);
//    juxianbg->runAction(seq);
    
}
void MarketGetEquipLayer::onHeadClick(Node* pSender)
{
    m_iscloseScene = false;
    TipsLayer::show(MarketFindResultDataManager::getInstance()->getFindTypeData(), MarketFindResultDataManager::getInstance()->dumpList->at(0)->dictId,1);
}
void MarketGetEquipLayer::onClick(Ref* psender)
{
    log("aaaaaa");
    this->removeFromParent();
}
bool MarketGetEquipLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    return  true;
}
void MarketGetEquipLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    
}
void MarketGetEquipLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    if(m_iscloseScene == true)
    {
        backScene();
    }
    m_iscloseScene = true;
}
void MarketGetEquipLayer::backScene()
{
    this->removeFromParent();
}
