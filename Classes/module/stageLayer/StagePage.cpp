//
//  StagePage.cpp
//  FightPass
//
//  Created by chenyanbin on 15/6/13.
//
//

#include "StagePage.h"
#include "../../VisibleRect.h"
#include "../../common/PublicShowUI.h"
#include "../../common/ImagePath.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "../battle/BattleLoader.h"
#include "../musou/MusouLayer.h"
#include "../chapter/ChapterLayer.h"
#include "../../common/noticeManager/NoticeManager.h"
StagePage::StagePage()
:m_page(0)
,m_totalCellSize(0)
,pageNum(3)
,m_battleList(NULL)
{
        
}
StagePage::~StagePage()
{
    m_battleList = NULL;
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumSanguoWarriors);
}
bool StagePage::init(int page,vector<BattleType>* battleList)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Node::init());
        this->m_battleList = battleList;
        this->m_totalCellSize = m_battleList->size();
        m_page = page;
        setPage();
        bref = true;
    } while (false);
    return  bref;
}
StagePage* StagePage::create(int page,vector<BattleType>* battleList)
{
    StagePage* node = new StagePage();
    if(node && node->init(page,battleList))
    {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    node = NULL;
    return NULL;
}
void StagePage::setPage()
{
    Node* container = Node::create();
    container->setAnchorPoint(Point::ZERO);
    int nowIndex = 0;
    TouchSprite* node = NULL;
//    Sprite* centerImage = nullptr;
 //   Sprite* frontImage = NULL;
    BattleType battleType = kBattleType_None;
    for(int i = 0; i < pageNum; i++)
    {
        nowIndex = m_page * pageNum + i;
        if(nowIndex >= m_totalCellSize)
        {
            break;
        }
        battleType = m_battleList->at(nowIndex);
        const char* path = PublicShowUI::getResImgPath(IMG_STAGE_LISTBG,PublicShowUI::numberToString(battleType).c_str());
//        centerImage = Sprite::create(path);
        node = TouchSprite::createWithPic(path, this, callfuncN_selector(StagePage::onClick));
        node->setAnchorPoint(Point::ZERO);
        node->isButtonMode = true;
        if(battleType == kBattleTYPe_SanGuoWushuan)
        {
            GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumSanguoWarriors, node);
        }
//        node->addChild(centerImage,1);
//        centerImage->setPosition(node->getContentSize().width/2, node->getContentSize().height/2);
//        
//        frontImage = Sprite::create(IMG_STAGE_ITEMFRONT);
//        frontImage->setPosition(node->getContentSize().width/2, node->getContentSize().height/2);
//        node->addChild(frontImage,2);
        
        
        node->setPositionX(i * (node->getContentSize().width - 80 ));
        node->setPositionY(((i + 1) % 2) * 30);
//        path = PublicShowUI::getResImgPath(IMG_STAGE_LISTNAME, PublicShowUI::numberToString(battleType).c_str());
//        Sprite* nameSpr = Sprite::create(path);
//        if(nameSpr)
//        {
//            nameSpr->setPosition(node->getContentSize().width/2, node->getContentSize().height - nameSpr->getContentSize().height - 5);
//            node->addChild(nameSpr,3);
//        }
//        path = PublicShowUI::getResImgPath(IMG_STAGE_DESCRIPT, PublicShowUI::numberToString(battleType).c_str());
//        Sprite* desSpr = Sprite::create(path);
//        desSpr->setPosition(node->getContentSize().width/2, 50);
//        node->addChild(desSpr,4);
        
//        if(nowIndex >= 2)
//        {
//            Sprite* lock = Sprite::create(IMG_STAGE_ITEMLOCK);
//            node->addChild(lock,6);
//            lock->setPosition(node->getContentSize().width/2, node->getContentSize().height/2);
//        }
        
        container->addChild(node,1,battleType);
//        Sprite* particleSpr = Sprite::create(IMG_STAGE_PARTICLE);
//        particleSpr->setPosition(node->getContentSize().width/2-20,80);
//        node->addChild(particleSpr,-1);

    }
    this->addChild(container);
    Size size = SDResource.size;
    size.height = node->getContentSize().height;
    this->setContentSize(size);
}
void StagePage::onClick(Node* psender)
{
    int tag = psender->getTag();
    
    if(tag == kBattleType_MingZhanYi)
    {
        GlobalInfo::getInstance()->battleType = kBattleType_MingZhanYi;
        ChapterLayer::requestChapterByID();
    }
    else if(tag == kBattleTYPe_SanGuoWushuan)
    {
        GlobalInfo::getInstance()->battleType = kBattleTYPe_SanGuoWushuan;
        MusouLayer::requestMuouList();
    }
    else if(tag == kBattleType_MingJiangZhuan)
    {
        NoticeManager::getInstance()->showNotice("精彩，敬请期待！");
        GlobalInfo::getInstance()->battleType = kBattleType_MingJiangZhuan;
    }

    
}
