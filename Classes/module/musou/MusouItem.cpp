//
//  MusouItem.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/17.
//
//
#include "../../VisibleRect.h"
#include "../../common/PublicShowUI.h"
#include "../../common/ImagePath.h"

#include "../battle/BattleLoader.h"
#include "MusouItem.h"

#include "MusouStageNode.h"
MusouItem::MusouItem()
:m_page(0)
,m_totalCellSize(0)
,pageNum(3)
,m_battleList(NULL)
{
    
}
MusouItem::~MusouItem()
{
    m_battleList = NULL;
}
bool MusouItem::init(int page,Vector<MusouStageData*>* musouList)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Node::init());
        this->m_battleList = musouList;
        this->m_totalCellSize = m_battleList->size();
        m_page = page;
        setPage();
        bref = true;
    } while (false);
    return  bref;
}
MusouItem* MusouItem::create(int page,Vector<MusouStageData*>* battleList)
{
    MusouItem* node = new MusouItem();
    if(node && node->init(page,battleList))
    {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    node = NULL;
    return NULL;
}
//void MusouItem::setPage()
//{
//    int nowIndex = 0;
//    Node* node = NULL;
//
// 
//    MusouStageData* stageData = NULL;
//    float _width = 340;
//    float _height = 280;
//
//    string timeStr = "";
//    for(int i = 0; i < pageNum; i++)
//    {
//     
//        nowIndex = m_page * pageNum + i;
//        if(nowIndex >= m_totalCellSize)
//        {
//            break;
//        }
//        
//        stageData = m_battleList->at(nowIndex);
//
//        node = MusouStageNode::create(stageData);
//        node->setAnchorPoint(Point::ZERO);
//
//        int index = i / 2;
//        if(nowIndex % 2 == 0)
//        {
//            node->setPosition(index * _width + node->getContentSize().width * .5, _height + _height/2);
//            
//        }
//        else
//        {
//            node->setPosition(index * _width + node->getContentSize().width * .5, _height/2);
//        }
//        this->addChild(node,i);
//        
//    }
//     Size size = SDResource.size;
//    if(node)
//    {
//       
//        size.height = _height + _height/2 + node->getContentSize().height * .5;
//       
//    }
//     this->setContentSize(size);
//   
//}

void MusouItem::setPage()
{
    int nowIndex = 0;
    Node* node = NULL;
    
    
    MusouStageData* stageData = NULL;
    float _width = 340;
    float _height = 100;
    
    string timeStr = "";
    for(int i = 0; i < pageNum; i++)
    {
        
        nowIndex = m_page * pageNum + i;
        if(nowIndex >= m_totalCellSize)
        {
            break;
        }
        
        stageData = m_battleList->at(nowIndex);
        
        node = MusouStageNode::create(stageData);
        node->setAnchorPoint(Point::ZERO);
        node->setPosition(50 + i * _width  , _height+node->getContentSize().height);
        log("%f,%f",node->getContentSize().width,node->getContentSize().height);
        this->addChild(node,i);
        
    }
    Size size = SDResource.size;
    if(node)
    {
        
        size.height = _height + node->getContentSize().height;
        
    }
    this->setContentSize(size);
}



































