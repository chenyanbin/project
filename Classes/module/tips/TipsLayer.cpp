//
//  TipsLayer.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/11/3.
//
//

#include "TipsLayer.h"
TipsLayer::TipsLayer()
{
    
}
TipsLayer::~TipsLayer()
{
    
}
bool TipsLayer::init()
{
    if(!BaseLayer::init())
    {
        return false;
    }
    this->isShowGrayBg = false;
    isClickClose = true;
  
    isAbleGuiding = false;
    this->setBackground(IMG_PUBLIC_TIPSBG);
    return true;
}
void TipsLayer::show(int conTypeId,int conId,int conVal)
{
    TipsLayer* layer = TipsLayer::create(conTypeId, conId, conVal);
    
    if(layer)
    {
        Scene* scene = Director::getInstance()->getRunningScene();
        layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2,VisibleRect::center().y - layer->getContentSize().height/2);
        scene->addChild(layer,SCENE_POPLAYER_ZORDER);
    }
}
TipsLayer* TipsLayer::create(int conTypeId,int conId,int conVal)
{
    TipsLayer* pRef = new TipsLayer();
    if(pRef && pRef->init())
    {
        pRef->autorelease();
        pRef->setItemData(conTypeId, conId, conVal);
        
        return pRef;
    }
    CC_SAFE_DELETE(pRef);
    return NULL;
}
void TipsLayer::setItemData(int conTypeId,int conId,int conVal)
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    //图标
 
    Sprite* itemIco = Sprite::create(PublicShowUI::getGoods(conTypeId, conId));
    itemIco->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(itemIco);
    itemIco->setPosition(10*sx, this->getContentSize().height - itemIco->getContentSize().height -  10*sx);
    this->addChild(itemIco,1);
    
    //名称
    string stt = PublicShowUI::getName(conTypeId, conId);
    if(conVal > 1)
    {
        stt = stt + "X" + PublicShowUI::numberToString(conVal);
    }
    Label* itemName = PublicShowUI::getLabel(stt.c_str(),Color3B::WHITE,25,false,false);
    itemName->setAnchorPoint(Point::ZERO);
    itemName->setPositionX(itemIco->getContentSize().width/sx + 5);
    itemName->setPositionY(itemIco->getContentSize().height/sx - itemName->getContentSize().height - 5);
    itemIco->addChild(itemName,1);
    
    //类型
//    stt = "类型：" + PublicShowUI::getItemType(conTypeId, conId);
//    Label* itemType = PublicShowUI::getLabel(stt.c_str(),Color3B::WHITE,22,false,false);
//    itemType->setAnchorPoint(Point::ZERO);
//    itemType->setPositionX(itemIco->getContentSize().width/sx + 5);
//    itemType->setPositionY(itemName->getPositionY() - itemType->getContentSize().height - 5);
//    itemIco->addChild(itemType,1);
    
    //介绍
    stt = PublicShowUI::getDescription(conTypeId, conId);
    Label* itemDescription = PublicShowUI::getLabel(stt.c_str(),Color3B::WHITE,22,false,true);
    itemDescription->setAnchorPoint(Point::ZERO);
    
   
    float _width = itemDescription->getContentSize().width > this->getContentSize().width - 60*sx ?  this->getContentSize().width - 60*sx :  itemDescription->getContentSize().width;
    
    itemDescription->setMaxLineWidth(_width);
    
    itemDescription->setLineBreakWithoutSpace(true);//是否自动换行
   
    itemDescription->setPositionX((this->getContentSize().width - _width)/2);
    itemDescription->setPositionY((this->getContentSize().height/2 - itemDescription->getContentSize().height)/2);
    this->addChild(itemDescription,1);
    
    
//    //价格
//    DictItem* dictItem = DictItemManager::getInstance()->getData(conId);
//    
//    if(conTypeId == DictConTypedictItem && dictItem)
//    {
//        if(dictItem->isSale == 1)
//        {
//            //价值类型
//            Sprite* itemPriceType = Sprite::create(PublicShowUI::getGoods(DictConTypedictBaseProp, DictBasePropcoin,false));
//            PublicShowUI::setTargetScale(itemIco);
//            itemPriceType->setScale(0.8*sx);
//            itemPriceType->setPositionX(bg->getContentSize().width  - 110*sx);
//            itemPriceType->setPositionY(itemIco->getPositionY() + itemIco->getContentSize().height/sx/2);
//            this->addChild(itemPriceType,1);
//            //价格
//            Label* itemPriceValue = PublicShowUI::getLabel(PublicShowUI::getUpperlimit((int)dictItem->salePrice),Color3B::WHITE,22,false,true);
//            itemPriceValue->setAnchorPoint(Point(0,0.5));
//            itemPriceValue->setPositionX(itemPriceType->getPositionX() + 20*sx);
//            itemPriceValue->setPositionY(itemIco->getPositionY() + itemIco->getContentSize().height/sx/2);
//            this->addChild(itemPriceValue,1);
//        }
//        else
//        {
//            Label* itemPriceType = PublicShowUI::getLabel("不可出售",Color3B::WHITE, 22,false,true);
//            itemPriceType->setAnchorPoint(Point::ZERO);
//            itemPriceType->setPositionX(bg->getContentSize().width  - 110*sx);
//            itemPriceType->setPositionY(itemIco->getPositionY() + (itemIco->getContentSize().height - itemPriceType->getContentSize().height)/2);
//            this->addChild(itemPriceType,1);
//        }
//    }
    
}
void TipsLayer::onEnter()
{
    BaseLayer::onEnter();
}
void TipsLayer::onExit()
{
    BaseLayer::onExit();
}
void TipsLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
      setClickEnabled(false);
}
void TipsLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
      setClickEnabled(true);
}