//
//  BodyPowerPanel.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/12/29.
//
//

#include "BodyPowerPanel.hpp"
#include "../../common/Dialog/Dialog.h"
#include "../publicLayer/GotoModule.h"
#include "../../commonData/enum/DictFunctionEnum.h"
#include "../../module/buyPower/BuyPowerLayer.hpp"
BodyPowerPanel::BodyPowerPanel()
:m_fromeMoudle(0)
,TAG_PANEL(1)
{
    
}
BodyPowerPanel::~BodyPowerPanel()
{
    
}
bool BodyPowerPanel::init()
{
    return true;
}
void BodyPowerPanel::initFromeMoudle(int fromeMoudle)
{
    this->m_fromeMoudle = fromeMoudle;
}
void BodyPowerPanel::gotoMall(Node* pSender)
{
   if(pSender->getTag() == 1)
   {
       BuyPowerLayer::show();
//      GotoModule::gotoModuleByFunctionID(DictFunctionEnumShopping, m_fromeMoudle);
   }
  else
  {
      this->runAction(Sequence::create(DelayTime::create(.1),RemoveSelf::create(), NULL));
 
  }
}
void BodyPowerPanel::show(int fromeMoudle)
{
    // pl = createPopLayer(content,title,target,callfun);
//    if(buttonCount == 1)
//    {
//        pl->addButton(IMG_BUTTON_CONFIRM_LABEL, 1,IMG_PUBLIC_BUTTON_TWO_ORANGE);
//    }
//    else if(buttonCount == 2)
//    {
//        pl->addButton(IMG_BUTTON_CANCEL_LABEL, 2,IMG_PUBLIC_BUTTON_TWO_RED);
//        pl->addButton(IMG_BUTTON_CONFIRM_LABEL, 1,IMG_PUBLIC_BUTTON_TWO_ORANGE);
//    }
//    
//    pl->setPositionX(VisibleRect::center().x - pl->getContentSize().width/2);
//    pl->setPositionY(VisibleRect::center().y - pl->getContentSize().height/2);
//    scene->addChild(pl,SCENE_POPLAYER_ZORDER,LAYER_DIALOG);
//    

    Scene* scene = Director::getInstance()->getRunningScene();
    BodyPowerPanel* panel = BodyPowerPanel::create();
    panel->initFromeMoudle(fromeMoudle);
    scene->addChild(panel,SCENE_LAYER_ZORDER);

}
void BodyPowerPanel::onEnter()
{
    BaseLayer::onEnter();
    
    PopUpLayer* layer = Dialog::createPopLayer("体力不足，点击\"确定\"按钮，可购买更多体力。", "",this,callfuncN_selector(BodyPowerPanel::gotoMall));
    layer->addButton(IMG_BUTTON_CANCEL_LABEL, 2,IMG_PUBLIC_BUTTON_TWO_RED);
    layer->addButton(IMG_BUTTON_CONFIRM_LABEL, 1,IMG_PUBLIC_BUTTON_TWO_ORANGE);
    layer->setPositionX(VisibleRect::center().x - layer->getContentSize().width/2);
    layer->setPositionY(VisibleRect::center().y - layer->getContentSize().height/2);
    this->addChild(layer,0,TAG_PANEL);
}
void BodyPowerPanel::onExit()
{
    BaseLayer::onExit();
}