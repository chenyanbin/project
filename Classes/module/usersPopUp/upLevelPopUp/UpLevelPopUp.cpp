//
//  UpLevelPopUp.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/9.
//
//

#include "UpLevelPopUp.hpp"
#include "editor-support/cocostudio/CCArmature.h"
#include "../../../common/commonEffect/CommonEffect.h"
#include "../../../commonData/dictData/DictRoleLevel/DictRoleLevelManager.h"
#include "../../../commonData/dictData/DictFunction/DictFunctionManager.h"
using namespace cocostudio;
UpLevelPopUp::UpLevelPopUp()
:effectName("shengjitexiao")
,m_level(0)
{
    
}
UpLevelPopUp::~UpLevelPopUp()
{
    
}
bool UpLevelPopUp::init(int newLevel)
{
    m_level = newLevel;
    this->setBackground(IMG_DIALOG_BG);
    this->isAnimation = true;
    setItems();
    setTitle();
//    Node* level = PublicShowUI::getNumbers(GlobalInfo::getInstance()->gameRole->level,IMG_PUBLIC_NUMBER2);
//    level->setAnchorPoint(Point::ZERO);
//    level->setScale(.3 * sx);
//    level->setPosition(this->getContentSize().width/2 + 15 * sx + (150  - level->getContentSize().width) / 2 * sx, 15 * sx);
//    this->addChild(level,3);
    
    
    return true;
}
UpLevelPopUp* UpLevelPopUp::create(int newLevel)
{
    UpLevelPopUp* layer = new UpLevelPopUp();
    if(layer && layer->init(newLevel))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void UpLevelPopUp::setItems()
{
    Sprite* itemBg = Sprite::create(IMG_LEVELUP_ITEMS);
    itemBg->setAnchorPoint(Point::ZERO);
    float startX = this->getContentSize().width / GlobalInfo::getInstance()->screenScaleX /2 - 160;
    float startY = 5;
    DictRoleLevel* oldRoleLevel = DictRoleLevelManager::getInstance()->getData(GlobalInfo::getInstance()->gameRole->level);
    DictRoleLevel* newRoleLevel = DictRoleLevelManager::getInstance()->getData(m_level);
    
    
    Node* node = getFunctionOpenNode(newRoleLevel->openFunction);
    itemBg->addChild(node,1);
    
    node->setPosition(startX, startY);
    Node* preNode = node;
    const char* list[4] = {"当前体力:","体力上限体力:","总领导力:","队伍等级:"};
    int nowPower = GlobalInfo::getInstance()->bodyPower;
    int valueList[4] = {nowPower,oldRoleLevel->powerRecoverLimit,oldRoleLevel->leadership,GlobalInfo::getInstance()->gameRole->level};
    int newValueList[4] = {nowPower + newRoleLevel->powerBonus,newRoleLevel->powerRecoverLimit,newRoleLevel->leadership,m_level};
    for(int i = 0; i < 4; i++)
    {
        node = getItemNode(list[i], valueList[i], newValueList[i]);
        itemBg->addChild(node,i);
        node->setPosition(startX, preNode->getPositionY() + preNode->getContentSize().height + 22);
        preNode = node;
    }
    PublicShowUI::setTargetScale(itemBg);
    itemBg->setPosition((this->getContentSize().width - itemBg->getContentSize().width)/2, (this->getContentSize().height - itemBg->getContentSize().height)/2);
    this->addChild(itemBg,3);
}
Node* UpLevelPopUp::getItemNode(const char* title,int preValue,int nowValue)
{
    Node* node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    Label* titleLabel = PublicShowUI::getLabel(title,PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),20,false,false);
    titleLabel->setAnchorPoint(Point::ZERO);
    node->addChild(titleLabel,0);
    
    string str = PublicShowUI::numberToString(preValue);
    Label* preLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0xffde44),20,false,false);
    preLabel->setAnchorPoint(Point::ZERO);
    preLabel->setPosition(titleLabel->getContentSize().width + 10, preLabel->getPositionY());
    node->addChild(preLabel,1);
    
    
    
    Sprite* arrow = Sprite::create(IMG_GENERALS_EXPERIENCE_ARROW);
    arrow->setAnchorPoint(Point::ZERO);
    node->addChild(arrow,3);
    arrow->setPosition(preLabel->getPositionX() + preLabel->getContentSize().width + 20, preLabel->getPositionY() + 4);
    
    
    str = PublicShowUI::numberToString(nowValue);
    Label* nowLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0x06ffb0),20,false,false);
    nowLabel->setAnchorPoint(Point::ZERO);
    nowLabel->setPosition(arrow->getPositionX() + arrow->getContentSize().width + 20, preLabel->getPositionY());
    node->addChild(nowLabel,1);
    node->setContentSize(nowLabel->getContentSize());
    return node;
    
}
Node* UpLevelPopUp::getFunctionOpenNode(int functionId)
{
    Node* node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    Label* titleLabel = PublicShowUI::getLabel("功能开启：",PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),20,false,false);
    titleLabel->setAnchorPoint(Point::ZERO);
    node->addChild(titleLabel,0);
    
    DictFunction* dictFunction = DictFunctionManager::getInstance()->getData(functionId);
    string functionName = dictFunction ? dictFunction->name : "无";
    Label* functionLabel = PublicShowUI::getLabel(functionName.c_str(),PublicShowUI::getColor3b(0xff9138),20,false,false);
    functionLabel->setAnchorPoint(Point::ZERO);
    functionLabel->setPosition(titleLabel->getContentSize().width + 10, 0);
    node->addChild(functionLabel,3);
    node->setContentSize(titleLabel->getContentSize());
    return node;
}
void UpLevelPopUp::setTitle()
{
    Size size = this->getContentSize();
    Sprite* title = Sprite::create(IMG_PUBLIC_LEVELUP);
    title->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(title);
    title->setPosition((size.width - title->getContentSize().width)/2, size.height - 5);
    this->addChild(title,4);
    
    size.height = title->getPositionY() + title->getContentSize().height;
    this->setContentSize(size);
}
void UpLevelPopUp::onEnter()
{
    UserPopUp::onEnter();
}
void UpLevelPopUp::onExit()
{
     UserPopUp::onExit();
}
void UpLevelPopUp::onExitTransitionDidStart()
{
     UserPopUp::onExitTransitionDidStart();
    const char* path = PublicShowUI::getAvatarPath(IMG_PUBLIC_EFFECT, effectName.c_str());
    ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
}
void UpLevelPopUp::onEnterTransitionDidFinish()
{
    UserPopUp::onEnterTransitionDidFinish();
    SoundManager::playEffectMusic(EFFECT_UPLV);
    
    const char* path = PublicShowUI::getAvatarPath(IMG_PUBLIC_EFFECT, effectName.c_str());
    ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
    // 连接该骨骼动画的资源
    
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(UpLevelPopUp::onDataLoaded));
    SoundManager::playEffectMusic(EFFECT_FUNCTIONOPEN);
   delayClickClose();
}
void UpLevelPopUp::onDataLoaded(float percent)
{
    if(!this->getParent())
    {
        return;
    }
    if(percent < 1)
    {
        return;
    }
    CommonEffect* commonEffect = CommonEffect::create(effectName.c_str(),false,true);
     commonEffect->setAnchorPoint(Point(.5,0));
    PublicShowUI::setTargetScale(commonEffect);
   
    commonEffect->setPosition(this->getContentSize().width/2, 20 * GlobalInfo::getInstance()->screenScaleX );
    this->addChild(commonEffect,4);
    
}