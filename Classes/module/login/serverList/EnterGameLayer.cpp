//
//  EnterGameLayer.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/7/21.
//
//

#include "EnterGameLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../LoginLayer.h"
#include "ServerListDataManager.h"
#include "ServerListLayer.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../common/commonEffect/CommonEffect.h"
#include "../../../common/Dialog/Dialog.h"
EnterGameLayer::EnterGameLayer()
{
    
}
EnterGameLayer::~EnterGameLayer()
{
    
}
bool EnterGameLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
       
        this->setContentSize(VisibleRect::getVisibleRect().size);
        this->isShowGrayBg = false;
        setBg();
//        setLogo();
        bref = true;
    } while (false);
    return bref;
}
void EnterGameLayer::show()
{
    Scene* scene = Director::getInstance()->getRunningScene();
    if(scene->getChildByTag(LAYER_ENTER_GAME))
    {
        return;
    }
    EnterGameLayer* layer = EnterGameLayer::create();
    layer->setAnchorPoint(Point::ZERO);
  
    layer->setPositionY(VisibleRect::bottom().y + 0 * GlobalInfo::getInstance()->screenScaleY);
    scene->addChild(layer,3,LAYER_ENTER_GAME);
}
void EnterGameLayer::hide()
{
     Scene* scene = Director::getInstance()->getRunningScene();
    if(scene->getChildByTag(LAYER_ENTER_GAME))
    {
        scene->removeChildByTag(LAYER_ENTER_GAME);
    }
}
void EnterGameLayer::setLogo()
{
//    Sprite* logo = Sprite::create(IMG_PUBLIC_LOGO);
//    logo->setAnchorPoint(Point::ZERO);
//    float _scale = .5 * GlobalInfo::getInstance()->screenScaleX;
//    logo->setScale(_scale);
//    logo->setPosition(this->getContentSize().width - logo->getContentSize().width  * _scale, this->getContentSize().height - logo->getContentSize().height * _scale );
//    this->addChild(logo,3);
}
void EnterGameLayer::setBg()
{
    
   
    Button* enterGame = Button::create(IMG_BUTTON_ENTERBTN, "", CC_CALLBACK_1(EnterGameLayer::onEnterGame, this));
    enterGame->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(enterGame);
    this->addChild(enterGame,1);
    enterGame->setPosition((this->getContentSize().width - enterGame->getContentSize().width)/2,0);
    
    CommonEffect* effect = CommonEffect::create("fuwuqianniu");
    effect->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(effect);
    this->addChild(effect,0);
    effect->setPosition(enterGame->getPositionX() + (enterGame->getContentSize().width - effect->getContentSize().width)/2, enterGame->getPositionY() + 20 * GlobalInfo::getInstance()->screenScaleX);
    
    TouchSprite* serverBg = TouchSprite::createWithPic(IMG_LOGIN_ENTERBG, this, callfuncN_selector(EnterGameLayer::onSelectedServer));
    serverBg->setAnchorPoint(Point::ZERO);
   
    serverBg->isButtonMode = true;
    this->addChild(serverBg,2,TAG_BG);
    
    ServerListData* data = ServerListDataManager::getInstance()->_nowServerData;
    if(!data)
    {
        return;
    }
    GlobalInfo::getInstance()->nowServerName = data->serverName;
    GlobalInfo::getInstance()->nowServerID = data->id;
    GlobalInfo::getInstance()->addressIP = data->IP;
    GlobalInfo::getInstance()->port = data->port;
  
    Label* serverName = PublicShowUI::getLabel(data->serverName.c_str(),PublicShowUI::getColor3b(COLOR_SERVERNAME_WHITE),25,false,false);
    serverName->setAnchorPoint(Point::ZERO);
    serverBg->addChild(serverName,2);
    serverName->setPosition((serverBg->getContentSize().width - serverName->getContentSize().width)/2 + 27, (serverBg->getContentSize().height - serverName->getContentSize().height)/2 +2);
  PublicShowUI::setTargetScale(serverBg);
    serverBg->setPosition(enterGame->getPositionX() + (enterGame->getContentSize().width - serverBg->getContentSize().width)/2,enterGame->getPositionY() + enterGame->getContentSize().height - 25 * GlobalInfo::getInstance()->screenScaleX);
    
    
}

//void EnterGameLayer::setSelectServerBtn()
//{
//    float sx = GlobalInfo::getInstance()->screenScaleX;
//    Button* btn = Button::create(IMG_SERVERLIST_ITEMBG1, IMG_SERVERLIST_ITEMBG2, CC_CALLBACK_1(EnterGameLayer::onSelectedServer, this));
//    btn->setAnchorPoint(Point::ZERO);
//    
//    
//    
//    Label* label = PublicShowUI::getLabel("选择服务器",PublicShowUI::getColor3b(COLOR_BROWN_WHITE),20,false,false);
//    btn->addChild(label,10);
//    label->setPosition(btn->getContentSize().width/2,btn->getContentSize().height/2 + 2);
//
//    
//    PublicShowUI::setTargetScale(btn);
//    btn->setPosition((this->getContentSize().width - btn->getContentSize().width)/2 - 30 * sx, (this->getContentSize().height - btn->getContentSize().height)/2);
//    this->addChild(btn,3);
//}
void EnterGameLayer::onSelectedServer(Node* pSender)
{
    ServerListLayer::show();
    this->hide();
}
void EnterGameLayer::onEnterGame(Ref* pSender)
{
    Dialog::showServerLoading();
    SoundManager::playEffectMusic(EFFECT_ENTER_SCENE);
    NetworkDataProcessing::getInstance()->connectServer();
}