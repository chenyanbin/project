//
//  AwardBox_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/7.
//
//

#include "AwardBox_Layer.h"
#include "../userWealth/UserEquipLayer.h"
#include "../../commonData/enum/DictContTypeEnum.h"
#include "../../commonData/enum/DictRolePropEnum.h"
#include "../../commonData/enum/DictItemTypeEnum.h"
#include "../newPlayerGuide/NewPlayerGuild.h"
AwardBox_Layer::AwardBox_Layer()
:sx(0)
,TAG_ITEMS(1)
{
    m_list=new Vector<BaseTypeData*>;
}
AwardBox_Layer::~AwardBox_Layer()
{
//    m_list->clear();
//    CC_SAFE_DELETE(m_list);
}
void AwardBox_Layer::onExit()
{
    BaseLayer::onExit();
}
void AwardBox_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void AwardBox_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void AwardBox_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    Node* node = this->getChildByTag(TAG_ITEMS);
    node->setVisible(true);
    Point cp = Point((this->getContentSize().width-node->getContentSize().width)/2,node->getPositionY());
    DelayTime* delay = DelayTime::create(.25);
    MoveTo* moveto = MoveTo::create(.3, cp);
    EaseSineOut* sineOut = EaseSineOut::create(moveto);
    node->runAction(Sequence::create(delay,sineOut, NULL));
  
}
bool AwardBox_Layer::init(Vector<BaseTypeData*> *m_baseList)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        m_list=m_baseList;
        this->setBackground(IMG_PUBLIC_LAYER_GAIN_BG);
        this->isAnimation = true;
        this->isClickClose=true;
        this->setClickEnabled(true);
        this->setGrayBg();
        this->createLayer();
        bref = true;
    } while (false);
    return bref;
}
AwardBox_Layer* AwardBox_Layer::create(Vector<BaseTypeData*> *m_baseList)
{
    AwardBox_Layer* layer = new AwardBox_Layer();
    if(layer && layer->init(m_baseList))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void AwardBox_Layer::createLayer()
{
    if(!m_list)
    {
        return;
    }
    Sprite* labelSprite=Sprite::create(IMG_PUBLIC_LAYER_GAIN_LABEL);
    PublicShowUI::setTargetScale(labelSprite);
    labelSprite->setAnchorPoint(Point::ZERO);
    labelSprite->setPosition(this->getContentSize().width/2-labelSprite->getContentSize().width/2,this->getContentSize().height-labelSprite->getContentSize().height/2);
    this->addChild(labelSprite);
    
    this->showAwardBoxSound();
    
    Node* node=Node::create();
    int len=(int)m_list->size();
    for (int i=0; i<len; i++) {
        BaseTypeData* data =m_list->at(i);
        const char* str=PublicShowUI::getGoods(data->dataType, data->dataId);
        UserEquipLayer* userHead=UserEquipLayer::create(str,data->dataQuality,false);
        userHead->setAnchorPoint(Point::ZERO);
        if(data->dataType == DictItemTypeEnumItemMater)
        {
            userHead->setFragment();
        }
        else if(data->dataType == DictItemTypeEnumItemBook)
        {
            userHead->setLetterFragment();
        }
        PublicShowUI::setTargetScale(userHead);
        
        userHead->setPosition((i%7)*(userHead->getContentSize().width + 20 * sx),0 - floor(i/7)*(userHead->getContentSize().height+30));
        node->addChild(userHead);
        string name=data->dataName;
        if (data->dataCount>0) {
            name=data->dataName + "x" + PublicShowUI::numberToString(data->dataCount);
        }
            
        Label* countLabel = PublicShowUI::getLabel(name.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
        countLabel->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(countLabel);
        countLabel->setPosition(userHead->getPositionX()+(userHead->getContentSize().width-countLabel->getContentSize().width)/2,userHead->getPositionY()-countLabel->getContentSize().height-8*sx);
        node->addChild(countLabel);
        
        if (i<7) {
            Size _size=userHead->getContentSize();
            _size.width=userHead->getPositionX()+userHead->getContentSize().width;
            //        _size.height = userHead->getContentSize().height + abs(userHead->getPositionY());
            node->setContentSize(_size);
        }
    }
//    node->setPosition((this->getContentSize().width-node->getContentSize().width)/2,(this->getContentSize().height-node->getContentSize().height)/2);
    node->setPosition(-node->getContentSize().width, (this->getContentSize().height-node->getContentSize().height)/2);
    if (len>7) {
        node->setScale(0.8*sx);
        node->setPosition(100*sx-node->getContentSize().width, (this->getContentSize().height-node->getContentSize().height)/2+80*sx);
    }
    node->setVisible(false);
    this->addChild(node,2,TAG_ITEMS);
    
}
void AwardBox_Layer::showAwardBoxSound()
{
    SoundManager::playEffectMusic(EFFECT_GET_PAGE);
}