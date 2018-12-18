//
//  LimitCardSkillLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/1/4.
//
//

#include "LimitCardSkillLayer.h"
#include "../../common/TouchSprite/Button.h"
#include "../../commonData/dictData/DictSkill/DictSkillManager.h"
LimitCardSkillLayer::LimitCardSkillLayer()
:sx(0)
{
    
}
LimitCardSkillLayer::~ LimitCardSkillLayer()
{
    
}
void LimitCardSkillLayer::onExit()
{
    BaseLayer::onExit();
}
void LimitCardSkillLayer::onEnter()
{
    BaseLayer::onEnter();
}
void LimitCardSkillLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void LimitCardSkillLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
bool LimitCardSkillLayer::init(int _skill1, int _skill2, int _skill3, int _skill4 )
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        
        this->setBackground(IMG_LIMITCARD_SKILLBG);
        this->isAnimation = false;
        this->isClickClose=true;
        this->setClickEnabled(true);
        this->isShowGrayBg = true;
        this->createLayer(_skill1, _skill2, _skill3, _skill4);
    
        bref = true;
    } while (false);
    return bref;
}
LimitCardSkillLayer* LimitCardSkillLayer::create(int _skill1, int _skill2, int _skill3, int _skill4)
{
    LimitCardSkillLayer* layer = new LimitCardSkillLayer();
    if(layer && layer->init(_skill1, _skill2, _skill3, _skill4))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void LimitCardSkillLayer::show(int _skill1, int _skill2, int _skill3, int _skill4 )
{
    LimitCardSkillLayer* layer = LimitCardSkillLayer::create(_skill1, _skill2, _skill3, _skill4);
    if(layer)
    {
        Scene* scene = Director::getInstance()->getRunningScene();
        layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2,VisibleRect::center().y - layer->getContentSize().height/2);
        scene->addChild(layer,SCENE_LAYER_ZORDER);
    }
}
void LimitCardSkillLayer::createLayer(int _skill1, int _skill2, int _skill3, int _skill4 )
{
    Sprite* layerbg = (Sprite*)this->getChildByTag(TAG_BG);
    Sprite* titlebg = Sprite::create(IMG_LIMITCARD_SKILLONETITLEBG);
    titlebg->setAnchorPoint(Point::ZERO);
    titlebg->setPosition(15,this->getContentSize().height/sx-titlebg->getContentSize().height-15);
    layerbg->addChild(titlebg,1);
    Sprite* title = Sprite::create(IMG_LIMITCARD_SKILLONETITLE);
    title->setAnchorPoint(Point::ZERO);
    title->setPosition(20,8);
    titlebg->addChild(title);
    

    ValueVector m_skillList;
    m_skillList.push_back(Value(_skill1));
    m_skillList.push_back(Value(_skill2));
    m_skillList.push_back(Value(_skill3));
    m_skillList.push_back(Value(_skill4));
    int skill = 0;
    Sprite* skillPic = NULL;
    for (int i = 0; i<4; i++) {
        skill = m_skillList.at(i).asInt();
        skillPic = setskilldesc(i,skill);
        skillPic->setAnchorPoint(Point::ZERO);
        skillPic->setPosition(20,340-i*(skillPic->getContentSize().height+10));
        layerbg->addChild(skillPic,2);
    }
}

Sprite* LimitCardSkillLayer::setskilldesc(int index, int _skill)
{
    Sprite *skillbg = Sprite::create(IMG_LIMITCARD_SKILLONEBG);
    DictSkill* skill = DictSkillManager::getInstance()->getData(_skill);
   
    if (skill) {
        const char* iconPath = PublicShowUI::getResImgPath(IMG_SKILL_ICON, skill->icon.c_str());
        Sprite* skillPic = Sprite::create(iconPath);
        skillPic->setAnchorPoint(Point::ZERO);
        if (index == 3) {
            skillPic->setScale(0.7);
        }
        skillPic->setPosition(5,5);
        skillbg->addChild(skillPic,1);
        
        string desc = skill->desc;
        Label* descLabel = PublicShowUI::getLabel(desc.c_str(),PublicShowUI::getColor3b(COLOR_HEAD_WHITE),20,false,false);
        descLabel->setAnchorPoint(Point(0,1));
        descLabel->setMaxLineWidth(530);
        descLabel->setPosition(100, skillbg->getContentSize().height-20);
        skillbg->addChild(descLabel,1);
    }
    return skillbg;
}
