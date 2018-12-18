//
//  GuideContent.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 14-9-17.
//
//

#include "GuideContent.h"
#include "../../common/TouchSprite/Button.h"
#include "NewPlayerGuild.h"
#include "../publicLayer/GotoModule.h"
#include "../../commonData/dictData/DictHero/DictHeroManager.h"
#include "extensions/GUI/CCControlExtension/CCScale9Sprite.h"
#include "../../common/StringUtil.h"
GuideContent::GuideContent()
:m_data(NULL)
,playerGuilder(NULL)
,TAG_LABEL(1)
,TAG_HAlFBODY(2)
,TAG_GOTOBTN(3)
,heroID(0)
,playerScale(0)
{
    
}
GuideContent::~GuideContent()
{
    CC_SAFE_RELEASE_NULL(m_data);
    playerGuilder = NULL;
}
bool GuideContent::init()
{
    bool bref = false;
    do
    {
        CC_BREAK_IF(!BaseLayer::init());
        this->isAnimation = false;
        this->isAbleGuiding = false;
        playerScale = 1.5 * GlobalInfo::getInstance()->screenScaleX;
//        this->isShowGrayBg = true;
        
//        Scale9Sprite* talkBg = Sprite::create(IMG_NEWGUIDE_TALKBG);
        cocos2d::extension::Scale9Sprite* talkBg = cocos2d::extension::Scale9Sprite::create(IMG_NEWGUIDE_TALKBG);
        talkBg->setAnchorPoint(Point::ZERO);
//        talkBg->setCapInsets(Rect(5, 30, talkBg->getContentSize().width - 5, talkBg->getContentSize().height - 30) );
        talkBg->setScale(GlobalInfo::getInstance()->screenScaleX);
//        PublicShowUI::setTargetScale(talkBg);
        talkBg->setOpacity(200);
        this->addChild(talkBg,1,TAG_BG);
        this->setContentSize(designResolutionSize);
        setGotoBtn();
        bref = true;
    } while (false);
    return bref;
}
void GuideContent::setGotoBtn()
{
    
    Button* btn = Button::create(IMG_PUBLIC_BUTTON_GOTO, "", CC_CALLBACK_1(GuideContent::onBtnClick, this));
    btn->setAnchorPoint(Point(.5,.5));
    btn->setScale(1.2 * GlobalInfo::getInstance()->screenScaleX);
    btn->setContentSize(btn->getContentSize() * 1.2 * GlobalInfo::getInstance()->screenScaleX);
    this->addChild(btn,3,TAG_GOTOBTN);
    btn->setPosition(-btn->getContentSize().width/2, -btn->getContentSize().height/2);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumGoTo, btn);
}
void GuideContent::onBtnClick(Ref* pSender)
{
    if(m_data->goFunction)
    {
        GotoModule::gotoModuleByFunctionID(m_data->goFunction, SCENE_TAG_MAINUI);
        NewPlayerGuild::getInstance()->next();
    }
}
void GuideContent::updateContent()
{
    string str = StringUtil::replace(m_data->desc, "&userName&", GlobalInfo::getInstance()->gameRole->name);
    cocos2d::extension::Scale9Sprite* talkBg = (cocos2d::extension::Scale9Sprite*)this->getChildByTag(TAG_BG);
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Label* label = (Label*)this->getChildByTag(TAG_LABEL);
    Button* btn = (Button*)this->getChildByTag(TAG_GOTOBTN);
    if(btn)
    {
        btn->setOpacity(0);
//          btn->setVisible(m_data->goFunction > 0);
    }
    
    if(label)
    {
        label->setString(m_data->desc);
    }
    else
    {//PublicShowUI::getColor3b(COLOR_BROWN_WORD)
        label = PublicShowUI::getLabel(m_data->desc.c_str(),Color3B::WHITE,20,false,true);
        label->setAnchorPoint(Point::ZERO);
        this->addChild(label,3,TAG_LABEL);
        uint _width = talkBg->getContentSize().width * .9 * sx;
        label->setMaxLineWidth(_width);
    }
    talkBg->setPositionY(300 * GlobalInfo::getInstance()->screenScaleX);
    float scaleY = label->getContentSize().height / talkBg->getContentSize().height * sx;
    scaleY = scaleY > 1 ? scaleY : sx;
    talkBg->setScaleY(scaleY );
    
  
    uint _width = talkBg->getContentSize().width * .9 * sx ;
    label->setMaxLineWidth(_width);
    
    
    if(m_data->place == 1)
    {
        talkBg->setScaleX(sx);
        talkBg->setPositionX(0);
        label->setPositionX(talkBg->getPositionX() + (talkBg->getContentSize().width * sx - label->getContentSize().width)/2 );
        btn->setPosition(talkBg->getPositionX() + talkBg->getContentSize().width * sx, talkBg->getPositionY() + btn->getContentSize().height/2);
    }
    else
    {
        talkBg->setScaleX(-sx);
        talkBg->setPositionX(VisibleRect::right().x);
        label->setPositionX(talkBg->getPositionX() - talkBg->getContentSize().width  * sx + (talkBg->getContentSize().width * sx- label->getContentSize().width)/2  );
        
        btn->setPosition(talkBg->getPositionX() - talkBg->getContentSize().width * sx, talkBg->getPositionY() + btn->getContentSize().height/2);
    }
   
    label->setPositionY(talkBg->getPositionY() + (talkBg->getContentSize().height * scaleY - label->getContentSize().height)/2 + 15 * GlobalInfo::getInstance()->screenScaleY);
    
    setPlayerGuilderPosition();
    
    Node* blackBg = this->getChildByTag(TAG_BLACKBG);
    if(blackBg)
    {
         blackBg->setVisible(m_data->arrow >  0);
    }
}
void GuideContent::showGuider()//显示新手引导人
{
    if(m_data->resource == 0)
    {
        if(playerGuilder)
        {
            playerGuilder->removeFromParent();
            playerGuilder = NULL;
        }
        return;
    }
  
    if(playerGuilder == NULL || m_data->resource != heroID)
    {
        DictHero* dictHero = DictHeroManager::getInstance()->getData(m_data->resource);
        if(dictHero)
        {
            const char* path = PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH, dictHero->halfbodyrResource.c_str());
            if(playerGuilder)
            {
                playerGuilder->removeFromParent();
                playerGuilder = NULL;
            }
            playerGuilder = Sprite::create(path);
            if(!playerGuilder)
            {
                path = PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH, "zhouyu");
                playerGuilder = Sprite::create(path);
            }
            playerGuilder->setAnchorPoint(Point(0,0));
            this->addChild(playerGuilder,0,TAG_HAlFBODY);
            playerGuilder->setScale(playerScale);
        }
        
        heroID = m_data->resource;
    }
    setPlayerGuilderPosition();

}
void GuideContent::setPlayerGuilderPosition()
{

    if(m_data && m_data->place == 1)
    {
        if(playerGuilder)
        {
            playerGuilder->setScaleX(1 * playerScale);
            playerGuilder->setPositionX(VisibleRect::left().x - playerGuilder->getContentSize().width * playerScale  / 2 + 100 * GlobalInfo::getInstance()->screenScaleX);
        }
        
    }
    else
    {
        if(playerGuilder)
        {
            playerGuilder->setScaleX(-1 *  playerScale);
            playerGuilder->setPositionX(VisibleRect::right().x + playerGuilder->getContentSize().width * playerScale / 2 - 100 * GlobalInfo::getInstance()->screenScaleX);
        }
        
    }
    if(playerGuilder)
    {
        playerGuilder->setPositionY( - playerGuilder->getContentSize().height * playerScale / 2);
    }
   
}
void GuideContent::updateGuideData(DictNewGuide* data)
{
    CC_SAFE_RELEASE_NULL(m_data);
    m_data = data;
    CC_SAFE_RETAIN(m_data);
    updateContent();
    showGuider();
}