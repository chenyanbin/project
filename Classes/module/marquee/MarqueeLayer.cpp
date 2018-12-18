//
//  MarqueeLayer.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 14/12/27.
//
//

#include "MarqueeLayer.h"
#include "../../commonData/GlobalInfo.h"
#include "../../VisibleRect.h"
#include "../../common/PublicShowUI.h"
#include "MarqueeManager.h"
#include "../../commonData/dictData/DictTips/DictTipsManager.h"
#include "../../common/StringUtil.h"
MarqueeLayer::MarqueeLayer()
:msgContainer(NULL)
{
    
}
MarqueeLayer::~MarqueeLayer()
{
    
}
bool MarqueeLayer::init()
{
    bool bref =false;
    do {
        CC_BREAK_IF(!CutViewLayer::init());
        
        CutViewLayer::init();
        float sx = GlobalInfo::getInstance()->screenScaleX;
        Size size = VisibleRect::getVisibleRect().size;
        size.width = size.width/2;
        size.height = 50 * sx;
        LayerColor* layer = LayerColor::create(Color4B(0,0,0,150), size.width, size.height);
        this->addChild(layer,0);
        this->setContentSize(size);
        this->setCutRect(Rect(0,0,size.width,size.height));
        
        msgContainer = Sprite::create();
        this->addChild(msgContainer,1);
        
        
        bref = true;
    } while (false);
    return bref;
}
void MarqueeLayer::addContent(int dictTipsID,std::string& paramsStr)
{
    vector<std::string> paramsList = StringUtil::split(paramsStr, "#");
    vector<string> marqueNewStr;
    vector<string> colorVec;
    ssize_t len = 0;
    if(dictTipsID > 0)
    {
        DictTips* dictTips = DictTipsManager::getInstance()->getData(dictTipsID);
        if(!dictTips)
        {
            return;
        }
        colorVec = StringUtil::split(dictTips->chRgb, ",");
        std::string demStr = "";
        std::string content = dictTips->desc;
     
        len = colorVec.size();
        for(int  i= 0; i <= len ; i++)
        {
            demStr = "#" + PublicShowUI::numberToString(i+1) + "#";
            ssize_t index = content.find(demStr);
            string str = content.substr(0,index);//StringUtil::replace(content, "#" + PublicShowUI::numberToString(i+1) + "#",paramList[i]);
            marqueNewStr.push_back(str);
            content = content.substr(index + demStr.size(),content.size());
        }
        
        
        
    }
    else
    {
        marqueNewStr.push_back(paramsStr);
        paramsList[0] = "";
        colorVec.push_back("#FFEFD5");
    }
    
    len = marqueNewStr.size();
    Node* node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    Size size;
    for(int i= 0; i < len; i++)
    {
         Color3B color = PublicShowUI::getColor3b(0xFFEFD5);
        Label* label = PublicShowUI::getLabel(marqueNewStr.at(i).c_str(),color,30,false,true);
        label->setAnchorPoint(Point::ZERO);
        
        node->addChild(label,i);
        
        label->setPosition(node->getContentSize().width, (this->getContentSize().height - label->getContentSize().height)/2);
        size.width = node->getContentSize().width + label->getContentSize().width;
       
        if(i < colorVec.size())
        {
            string colorValue = StringUtil::replace(colorVec[i] , "#", "0x");
            unsigned long ucolor = PublicShowUI::hexToULong(colorValue);
            color = PublicShowUI::getColor3b(ucolor);
        }
    
      
        if(paramsList.size() > i)
        {
            Label* paramLabel = PublicShowUI::getLabel(paramsList.at(i).c_str(),color,30,false,true);
            paramLabel->setAnchorPoint(Point::ZERO);
            node->addChild(paramLabel,i);
            paramLabel->setPosition(size.width, (this->getContentSize().height - label->getContentSize().height)/2);
             size.width = size.width + paramLabel->getContentSize().width;
        }
 
        
       
        node->setContentSize(size);
    }
    node->setPositionX(this->getContentSize().width);
    msgContainer->addChild(node,(int)msgContainer->getChildrenCount());
    
    MoveTo* moveTo = MoveTo::create(10, Point(-node->getContentSize().width,node->getPositionY()));
    CallFuncN* callFun = CallFuncN::create(CC_CALLBACK_1(MarqueeLayer::onMoveEnd, this));
    node->runAction(Sequence::create(moveTo,callFun, NULL));
    
}
void MarqueeLayer::onMoveEnd(Node* target)
{
    log("Moveend  tag===%d",target->getTag());
    target->removeFromParent();
    MarqueeManager::getInstance()->nextContent();
}
void MarqueeLayer::onEnter()
{
    CutViewLayer::onEnter();
}
void MarqueeLayer::onExit()
{
    CutViewLayer::onExit();
}
void MarqueeLayer::onExitTransitionDidStart()
{
    CutViewLayer::onExitTransitionDidStart();
    msgContainer->removeAllChildren();
}
void MarqueeLayer::onEnterTransitionDidFinish()
{
    CutViewLayer::onEnterTransitionDidFinish();
    MarqueeManager::getInstance()->nextContent();
}