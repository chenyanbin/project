//
//  BuffEffectData.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/8/7.
//
//

#include "BuffEffectData.h"
#include "../../common/PublicShowUI.h"
#include "../../common/ImagePath.h"
BuffEffectData::BuffEffectData()
:_dictBuff(NULL)
,_skillEffect(NULL)
,endTime(0)
,m_buffID(0)
,damage(0)
,icon(NULL)
{
    
}
BuffEffectData::~BuffEffectData()
{
    CC_SAFE_RELEASE_NULL(_skillEffect);
    CC_SAFE_RELEASE_NULL(_dictBuff);
    CC_SAFE_RELEASE_NULL(icon);

}
 BuffEffectData* BuffEffectData::create(int buffID)
{
    BuffEffectData* data = new BuffEffectData();
    if(data && data->init(buffID))
    {
        data->autorelease();
        return data;
    }
    CC_SAFE_DELETE(data);
    data = NULL;
    return data;
}
void BuffEffectData::onExit()
{
    Node::onExit();
    if(icon && icon->getParent())
    {
        icon->removeFromParent();
    }
}
void BuffEffectData::onEnter()
{
    Node::onEnter();
}
void BuffEffectData::release()
{
  
    Node::release();
}
bool BuffEffectData::init(int buffID)
{
    m_buffID = buffID;
    DictBuff* buff = DictBuffManager::getInstance()->getData(buffID);
    this->setDictBuff(buff);
    if(buff->resource.size() > 0)
    {
        SkillEffect* skillEffect = SkillEffect::create(buff->resource.c_str(),0,buff->loopControl <= 0);
        skillEffect->m_actionMovementCallBack = CC_CALLBACK_1(BuffEffectData::onEffectCompleted, this);
        skillEffect->setAnchorPoint(Point::ZERO);
        this->addChild(skillEffect);
        skillEffect->setCascadeOpacityEnabled(true);
        float _scale = 1;
        if(buff->effectZoom)
        {
            _scale = buff->effectZoom / 10000;
            skillEffect->setScale(_scale);
        }
     
        
        this->setContentSize(skillEffect->getContentSize() * _scale);
    }
    const char* path = PublicShowUI::getResImgPath(IMG_BUFF_ICON, buff->iconResource.c_str());
    this->icon = Sprite::create(path);
    if(icon)
    {
        Sprite* form = Sprite::create(IMG_BUFF_FORM);
        icon->setAnchorPoint(Point::ZERO);
        icon->addChild(form,3);
        form->setPosition(icon->getContentSize().width/2, icon->getContentSize().height/2);
        icon->setScale(.3);
        icon->setContentSize(icon->getContentSize() * .3);
    }
    CC_SAFE_RETAIN(icon);
    
    return true;
}

void BuffEffectData::onEffectCompleted(Ref* target)
{
    if(this->getParent())
    {
        SkillEffect* skillEffect = (SkillEffect*)target;
        if(skillEffect)
        {
            skillEffect->playAnimation();
        }
    }

}