//
//  FamouseLayer.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/7.
//
//

#include "FamouseLayer.hpp"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../rank/RankFightLayer.h"
#include "../famouseActive/FamouseActive.hpp"
#include "../famouseFightgo/FamouseFightGo.hpp"
#include "../famouseDetails/FamouseDetails.hpp"
#include "../famouseStats/FamouseStats.hpp"
#include "../famouseBossCome/FamouseBossCome.hpp"
#include "../GeneralScene.hpp"
FamouseLayer::FamouseLayer()
:TAG_COMBOBTN(1)
,pageNode(NULL)
{
    
}
FamouseLayer::~FamouseLayer()
{
    pageNode = NULL;
}
bool FamouseLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->isAnimation = false;
        this->setBackground(IMG_PUBLIC_LAYER_LISTBG);
        setComboBtn();
        setOrderBtn();
        pageNode = Node::create();
        pageNode->setAnchorPoint(Point::ZERO);
        this->addChild(pageNode,2);
        bref = true;
    } while (false);
    return bref;
}
void FamouseLayer::setComboBtn()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    
    Sprite* node = Sprite::create(IMG_PUBLIC_LAYER_LISTBGTITLEBG);
    node->setAnchorPoint(Point::ZERO);
   
    ComboBoxBtn* btn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 12, CC_CALLBACK_1(FamouseLayer::onComboClick, this));
    btn->setAnchorPoint(Point::ZERO);
    btn->addCustomBtn(IMG_BUTTON_FOUR_GREENBTN1, IMG_BUTTON_FOUR_GREENBTN2, IMG_PUBLIC_LABEL_ACTIVE1, IMG_PUBLIC_LABEL_ACTIVE2);
    btn->addCustomBtn(IMG_BUTTON_FOUR_GREENBTN1, IMG_BUTTON_FOUR_GREENBTN2, IMG_PUBLIC_LABEL_FIGHTGO1, IMG_PUBLIC_LABEL_FIGHTGO2);
    btn->addCustomBtn(IMG_BUTTON_FOUR_GREENBTN1, IMG_BUTTON_FOUR_GREENBTN2, IMG_PUBLIC_LABEL_DETAILS1, IMG_PUBLIC_LABEL_DETAILS2);
    btn->addCustomBtn(IMG_BUTTON_FOUR_GREENBTN1, IMG_BUTTON_FOUR_GREENBTN2, IMG_PUBLIC_LABEL_STATS1, IMG_PUBLIC_LABEL_STATS2);
    
    node->addChild(btn,1,TAG_COMBOBTN);
    btn->setPosition(0,(node->getContentSize().height - btn->getContentSize().height)/2 + 10 );
    
    
     PublicShowUI::setTargetScale(node);
    node->setPosition(18 * sx,  this->getContentSize().height - node->getContentSize().height - 20 * sx);
    this->addChild(node,1,TAG_COMBOBTN);
}
void FamouseLayer::setOrderBtn()
{
    Node* comBtn = this->getChildByTag(TAG_COMBOBTN);
    CustomButton* btn = CustomButton::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(FamouseLayer::onOrderBtnClick, this));
    btn->setAnchorPoint(Point::ZERO);
    btn->addTitle(IMG_PUBLIC_LABEL_ORDERNAME, IMG_PUBLIC_LABEL_ORDERNAME);
    this->addChild(btn,2);
    float sx = GlobalInfo::getInstance()->screenScaleX;
    PublicShowUI::setTargetScale(btn);
    btn->setPosition(comBtn->getContentSize().width - btn->getContentSize().width - 40 * sx, comBtn->getPositionY() + (comBtn->getContentSize().height - btn->getContentSize().height)/2 + 10 * sx);
}
void FamouseLayer::onOrderBtnClick(Ref* pSender)
{
    RankFightLayer::show(SCENE_TAG_FAMOUSE);
}
void FamouseLayer::onComboClick(Ref* pSender)
{
    BaseLayer* layer = NULL;
    pageNode->removeAllChildren();
    CustomButton* btn = (CustomButton*)pSender;
    int tag = btn->getTag();
    switch (tag) {
        case GeneralScene::PAGE_ACTIVE:
            layer = FamouseActive::create();
            break;
        case GeneralScene::PAGE_FIGHTGO:
            layer = FamouseFightGo::create();
            break;
        case GeneralScene::PAGE_DETAILS:
            layer = FamouseDetails::create();
            break;
        case GeneralScene::PAGE_STATS:
            layer = FamouseStats::create();
            break;
        default:
            break;
    }
    if(layer)
    {
        layer->setAnchorPoint(Point::ZERO);
        pageNode->addChild(layer,0);
        PublicShowUI::setTargetScale(layer);
        layer->setPosition((this->getContentSize().width - layer->getContentSize().width)/2, (this->getContentSize().height - layer->getContentSize().height)/2 -  15 * GlobalInfo::getInstance()->screenScaleX);
    }
}
void FamouseLayer::setInitPage(int page)
{
    Node* comboBtn = this->getChildByTag(TAG_COMBOBTN);
    ComboBoxBtn* btn = (ComboBoxBtn*)comboBtn->getChildByTag(TAG_COMBOBTN);
    btn->selectedAt(page);
    
}