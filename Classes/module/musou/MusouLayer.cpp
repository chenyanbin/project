//
//  MusouLayer.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/17.
//
//

#include "MusouLayer.h"
#include "../userWealth/UserWealthLayer.h"
#include "MusouItemList.h"
#include "../../message/Decoding/musou/RequesMusouListMsg.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../common/Dialog/Dialog.h"
#include "../musouBattle/MusouBattleLayer.h"
MusouLayer::MusouLayer()
{
    
}
MusouLayer::~MusouLayer()
{
    
}
bool MusouLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->isAnimation = false;
        setBg();
       
        float sx = GlobalInfo::getInstance()->screenScaleX;
        this->setBackBtn(20 * sx,15 * sx);
        setUserWealth();
      
        bref = true;
    } while (false);
    return bref;
}
void MusouLayer::setBg()
{
    this->setBackground(IMG_PUBLIC_STAGEBG,Point::ZERO,false);
    Sprite* bg = (Sprite*)this->getChildByTag(TAG_BG);
    PublicShowUI::setTargetScale(bg,true,true);
    this->setContentSize(bg->getContentSize());
}
void MusouLayer::requestMuouList()
{
    GlobalInfo::getInstance()->battleType = kBattleTYPe_SanGuoWushuan;
    Dialog::showServerLoading();
    log("requestMuouList requestMuouList requestMuouList");
    RequesMusouListMsg* msg = new RequesMusouListMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
//    ByteStream* byteStream = new ByteStream();
//    byteStream->put(9);
//    for(int i = 0; i < 9 ; i++)
//    {
//        byteStream->putInt( i + 1);
//        byteStream->put(1);
//        byteStream->putInt(200);
//    }
//    byteStream->setPosition(0);
//    show(byteStream);
    msg = NULL;
}
void MusouLayer::show(ByteStream* byteStream)
{
  
    log("MusouLayer::show( MusouLayer::show(" );
    Director::getInstance()->purgeCachedData();
     MusouLayer* layer = MusouLayer::create();
    layer->setFromScene(SCENE_TAG_MAINUI);
    layer->initWithByteStream(byteStream);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    log("MusouLayer::show( MusouLayer::show(22222222222" );
    Scene* scene = Scene::create();
    scene->addChild(layer,0,SCENE_TAG_MUSOU);
    
    Director::getInstance()->replaceScene(scene);
}
void MusouLayer::initWithByteStream(ByteStream* byteStream)
{
    MusouItemList* layer = MusouItemList::create();
    layer->setListData(byteStream);
    layer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(layer);
    layer->setPositionX(VisibleRect::center().x - layer->getContentSize().width/2);
    layer->setPositionY(VisibleRect::center().y - layer->getContentSize().height/2 - 80 * GlobalInfo::getInstance()->screenScaleX);
    this->addChild(layer,5);
    
    Sprite* arrow = Sprite::create(IMG_GENERALSLIST_ARROW);
    PublicShowUI::setTargetScale(arrow);
    arrow->setAnchorPoint(Point::ZERO);
    arrow->setRotation(90);
    arrow->setPosition(VisibleRect::right().x - arrow->getContentSize().width - 30 * GlobalInfo::getInstance()->screenScaleX,  VisibleRect::center().y - arrow->getContentSize().height/2 );
    this->addChild(arrow,6);
    
    MoveBy* moveby = MoveBy::create(.5, Point(20,0));
    arrow->runAction(RepeatForever::create(Sequence::create(moveby,moveby->reverse(), NULL)));

    
    Sprite* leftarrow = Sprite::create(IMG_GENERALSLIST_ARROW);
    PublicShowUI::setTargetScale(leftarrow);
    leftarrow->setAnchorPoint(Point::ZERO);
    leftarrow->setRotation(-90);
    leftarrow->setPosition(50 * GlobalInfo::getInstance()->screenScaleX,  VisibleRect::center().y - leftarrow->getContentSize().height/2 );
    this->addChild(leftarrow,6);
    
    MoveBy* moveby2 = MoveBy::create(.5, Point(-20,0));
    leftarrow->runAction(RepeatForever::create(Sequence::create(moveby2,moveby2->reverse(), NULL)));
}
void MusouLayer::setUserWealth()
{
    UserWealthLayer* layer = UserWealthLayer::create(UserWealthLayer::STAGE);
    PublicShowUI::setTargetScale(layer);
    layer->setTitle(IMG_PUBLIC_SANGUOWUSHUANG);
    layer->setPositionX(VisibleRect::left().x);
    layer->setPositionY(VisibleRect::top().y - layer->getContentSize().height);
    this->addChild(layer,4);
}
void MusouLayer::onMsgProcess(EventCustom* message)
{
    MessageReceive* msg = (MessageReceive*)message->getUserData();
    if(msg->messageID == SCENSE_CLIENT_MUSOU_MusouBattlePageResp)
    {
        if(msg->state)
        {
            MusouBattleLayer::show(msg->byteStream);
        }
   }
}
void MusouLayer::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_MUSOU_MusouBattlePageResp).c_str(), CC_CALLBACK_1(MusouLayer::onMsgProcess, this));
}
void MusouLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}