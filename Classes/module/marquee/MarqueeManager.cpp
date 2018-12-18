//
//  MarqueeManager.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 14/12/27.
//
//

#include "MarqueeManager.h"
#include "../../commonData/GlobalInfo.h"
#include "../../VisibleRect.h"
#include "../../common/GameConfig.h"
#include "../../message/Decoding/marquee/RequestMarqueeMsg.hpp"
#include "../../net/NetworkDataProcessing.h"
#include "../../commonData/dictData/DictTips/DictTipsManager.h"

#include "../../common/PublicShowUI.h"
MarqueeManager* MarqueeManager::_instance = NULL;
MarqueeManager::MarqueeManager()
:marqueeLayer(NULL)
,msgList(NULL)
,m_nowIndex(0)
{
    marqueeLayer = MarqueeLayer::create();
    marqueeLayer->setCascadeColorEnabled(true);
    CC_SAFE_RETAIN(marqueeLayer);
    
    msgList = new Vector<MarqueeData*>();

}
MarqueeManager::~MarqueeManager()
{
    CC_SAFE_RELEASE_NULL(marqueeLayer);
    CC_SAFE_DELETE(msgList);
}
void MarqueeManager::requestMarqueeMsg()
{
    RequestMarqueeMsg* msg = new RequestMarqueeMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = nullptr;
}
void MarqueeManager::show()
{
    if(this->msgList->size() <= 0)
    {
        return;
    }
    marqueeLayer->stopAllActions();
    marqueeLayer->setOpacity(255);
    if(marqueeLayer->getParent() == NULL)
    {
        m_nowIndex = 0;
        marqueeLayer->setPosition(VisibleRect::center().x - marqueeLayer->getContentSize().width/2, VisibleRect::top().y - marqueeLayer->getContentSize().height - 100 * GlobalInfo::getInstance()->screenScaleY);
        Director::getInstance()->getRunningScene()->addChild(marqueeLayer,SCENE_NOTICE_ZORDER + 1);
    }
}
MarqueeManager* MarqueeManager::getInstance()
{
    if(!_instance)
    {
        _instance = new MarqueeManager();
    }
    return _instance;
}
void MarqueeManager::addContent(MarqueeData* data)
{
  
    updataData(data);
    if(msgList->size() == 1)
    {
        this->show();
    }
    
}
void MarqueeManager::updataData(MarqueeData* data)
{
    
    //1新消息，2删除此id的消息 ，3更新此id的消息
   if(data->op == 1)
   {
       msgList->pushBack(data);
   }
   else
   {
       ssize_t len = msgList->size();
       MarqueeData* temp = NULL;
       int i = 0;
       for(i = 0; i < len; i++)
       {
           temp = msgList->at(i);
           if(temp->marqueeID == data->marqueeID)
           {
               if(data->op == 2)
               {
                   msgList->eraseObject(temp);
               }
               else if(data->op == 3)
               {
                   msgList->eraseObject(temp);
                   msgList->insert(i, data);
               }
               break;
           }
       }
       if( i >= len && data->op == 3)
       {
           msgList->pushBack(data);
       }

   }
}
void MarqueeManager::hideMarquee()
{
    if(marqueeLayer && marqueeLayer->getParent())
    {
        RemoveSelf* remove = RemoveSelf::create();
        FadeOut* fadeout = FadeOut::create(1);
        marqueeLayer->runAction(Sequence::create(fadeout,remove ,NULL));
    }
    m_nowIndex = 0;
}
void MarqueeManager::nextContent()
{
    if(msgList->size() <= 0)
    {
        hideMarquee();
        return;
    }
    else if(marqueeLayer->getParent() == NULL)
    {
        this->show();
        return;
    }
    else
    {
        if(m_nowIndex >= msgList->size())
        {
            m_nowIndex = 0;
        }
        MarqueeData* data = msgList->at(m_nowIndex ++);

        
        
        
        marqueeLayer->addContent(data->dictTipsID,data->content);
        if(data->loopCount != -1)
        {
            data->loopCount --;
            if(data->loopCount <= 0)
            {
                msgList->eraseObject(data);
            }
        }
        
    }
    
}