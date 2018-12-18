//
//  PageNode.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 14-7-8.
//
//

#include "PageNode.h"
#include "../ImagePath.h"
#include "../../common/GraySprite/GraySprite.h"
PageNode::PageNode()
:m_totalPage(0)
,m_curPage(0)
{
    
}
PageNode::~PageNode()
{
    
}
bool PageNode::init(int totalPage,int curPage)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Node::init());
        this->m_totalPage= totalPage;
        this->m_curPage = curPage;
        initDots();
        bref = true;
    } while (false);
    return bref;
}
PageNode* PageNode::create(int totalPage,int curPage)
{
    PageNode* pRef = new PageNode();
    if(pRef && pRef->init(totalPage,curPage))
    {
        pRef->autorelease();
        return pRef;
    }
    CC_SAFE_DELETE(pRef);
    return NULL;
}
PageNode* PageNode::create(int totalPage)
{
    PageNode* pRef = PageNode::create(totalPage, 1);
    return pRef;
}
void PageNode::initDots()
{
    MenuItemLabel * itemLabel = NULL;
    Sprite* spr = NULL;
    for(int i = 0; i < this->m_totalPage; i++)
    {
//        if(i == m_curPage-1)
//        {
//            spr = Sprite::create(IMG_PUBLIC_PAGEDOT);
//        }
//        else
//        {
//            spr = GraySprite::create(IMG_PUBLIC_PAGEDOT);
//        }
      
        itemLabel = MenuItemLabel::create(spr, NULL);

        itemLabel->setAnchorPoint(Point::ZERO);
        itemLabel->unselected();
        itemLabel->setPositionX(i * (itemLabel->getContentSize().width + 6));
        itemLabel->setPositionY(0);
        this->addChild(itemLabel,i,i+1);
        
    }
    if(itemLabel)
    {
        Size size = itemLabel->getContentSize();
        size.width = itemLabel->getPositionX() + itemLabel->getContentSize().width;
        this->setContentSize(size);
    }
   
}
void PageNode::setCurPage(int page)
{
//    if(page < 0 || page > m_totalPage)
//    {
//        log("page out of the size");
//        return;
//    }
//    
//    MenuItemLabel * itemLabel  = (MenuItemLabel*)this->getChildByTag(this->m_curPage);
//    
//    if(itemLabel)
//    {
//        itemLabel->setLabel(GraySprite::create(IMG_PUBLIC_PAGEDOT));
//    }
//  
//    
//    itemLabel = (MenuItemLabel*)this->getChildByTag(page);
//
//    if(itemLabel)
//    {
//        itemLabel->setLabel(Sprite::create(IMG_PUBLIC_PAGEDOT));
//    }
//    
//    
//    
//    this->m_curPage = page;
}