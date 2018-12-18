//
//  LineupPage.cpp
//  FightPass
//
//  Created by chenyanbin on 15/6/23.
//
//

#include "LineupPage.h"
#include "../../VisibleRect.h"
#include "../../common/PublicShowUI.h"
#include "../../common/ImagePath.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "../battle/BattleLoader.h"
#include "../lineup/LineupLayer.h"
#include "../userWealth/UserHeadLayer.h"
#include "../../protocol/UserCustomEvent.h"
LineupPage::LineupPage()
:m_totalCellSize(0)
{
    
}
LineupPage::~LineupPage()
{
    log("~~~~LineupPage ~~~~LineupPage");
}
bool LineupPage::init(int idx,int totalCellCount)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Node::init());
        
        this->m_totalCellSize = totalCellCount;
        setPage(idx);
        bref = true;
    } while (false);
    return  bref;
}
LineupPage* LineupPage::create(int idx,int totalPage)
{
    LineupPage* node = new LineupPage();
    if(node && node->init(idx,totalPage))
    {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    node = NULL;
    return NULL;
}
void LineupPage::setPage(int idx)
{
    Node* container = Node::create();
    container->setAnchorPoint(Point::ZERO);
    int nowIndex = 0;
    nowIndex = idx ;
    if(nowIndex >= m_totalCellSize)
    {
        return;
    }
    UserHeadLayer* userHead = UserHeadLayer::create("zhenji");
    userHead->addTouchBegainCallBack(this, callfuncN_selector(LineupPage::onClick));
    userHead->setAnchorPoint(Point::ZERO);
    userHead->setPositionY(0);
    container->addChild(userHead,1,idx);
    this->addChild(container);
    
    Size size = SDResource.size;
    size.width = userHead->getContentSize().width;
    size.height = userHead->getContentSize().height+20;
    this->setContentSize(size);
}
void LineupPage::onClick(Node* psender)
{
    int cardId = psender->getTag();
    log("node==%d",cardId);
}

