//
//  ChallengeNode.cpp
//  FightPass
//
//  Created by zhangbin on 16/3/9.
//
//

#include "ChallengeNode.hpp"
#include "../../../common/ImagePath.h"
#include "../../../common/PublicShowUI.h"
#include "../../../commonData/dictData/DictMonster/DictMonsterManager.h"
#include "../../../common/customButton/CustomButton.hpp"
#include "../../../common/GameConfig.h"
#include "../../../common/TimeUtil.h"
#include "../arenaData/ArenaDataManager.hpp"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../battleTest/PlayerDataManager.hpp"
#include "../../newPlayerGuide/NewPlayerGuild.h"
ChallengeNode::ChallengeNode()
:m_index(0)
{
    
}
ChallengeNode::~ChallengeNode()
{
  
}
ChallengeNode* ChallengeNode::create(ssize_t idx)
{
    ChallengeNode* node = new ChallengeNode();
    if(node && node->init(idx))
    {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    node = NULL;
    return NULL;
}
bool ChallengeNode::init(ssize_t idx)
{
  
    m_index = idx;
    Sprite* bg = Sprite::create(IMG_PUBLIC_LAYER_RANKCELLBG);
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg,0);
    
    Sprite*titlebg = Sprite::create(IMG_PUBLIC_LAYER__CELLTITLEBG);
    titlebg->setAnchorPoint(Point::ZERO);
    titlebg->setPosition(177,bg->getContentSize().height - titlebg->getContentSize().height-10);
    bg->addChild(titlebg);
    
    this->setContentSize(bg->getContentSize());
    
    setHead();
    setName();
    setBtn();
    setPrizeValue();
    return true;
}
void ChallengeNode::setHead()
{
    ArenaListData* data = ArenaDataManager::getInstance()->arenaList->at(m_index);
    DictHero* dictMonster = DictHeroManager::getInstance()->getData(data->heroDictId);
    const char* path = dictMonster ? dictMonster->headResource.c_str() : "zhaoyun";
    path = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH,path);
    Sprite* head = Sprite::create(path);
    if(head)
    {
        
        Sprite* headbg = Sprite::create(IMG_ARENALIST_HEADBG);
        headbg->setAnchorPoint(Point::ZERO);
        this->addChild(head,1);
        head->setPosition(37,(this->getContentSize().height - head->getContentSize().height)/2);
        
        head->setAnchorPoint(Point::ZERO);
        this->addChild(head,2);
        head->setPosition(37,(this->getContentSize().height - head->getContentSize().height)/2);
        
        Sprite* headbox = Sprite::create(IMG_ARENALIST_HEADBOX);
        headbox->setAnchorPoint(Point::ZERO);
        headbox->setScale(0.9);
        this->addChild(headbox,3);
        headbox->setPosition(37,(this->getContentSize().height - head->getContentSize().height)/2);
    }
   
}
void ChallengeNode::setName()
{
    ArenaListData* data = ArenaDataManager::getInstance()->arenaList->at(m_index);
    int fontSize = 20;
    string str =  data->roleName;
    Label* nameLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),fontSize,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(198,this->getContentSize().height - nameLabel->getContentSize().height - 13);
    this->addChild(nameLabel,1);

    
    //boss等级
    str = "LV " + PublicShowUI::numberToString(data->roleLevel);
    Label* label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),fontSize,false,false);
    label->setAnchorPoint(Point::ZERO);
    this->addChild(label,3);
    label->setPosition(370, this->getContentSize().height - label->getContentSize().height - 13);

    
    
    //排名
    Sprite* rank = Sprite::create(IMG_ARENALIST_RANK);
    rank->setAnchorPoint(Point::ZERO);
    rank->setScale(1.2);
    rank->setPosition(label->getPositionX() + label->getContentSize().width+50,label->getPositionY());
    this->addChild(rank);
    
    string numStr = StringUtils::format(" %d",data->rank);
    Label* ranklabel = PublicShowUI::getLabel(numStr.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),fontSize,false,false);
    ranklabel->setAnchorPoint(Point::ZERO);
    ranklabel->setPosition(rank->getPositionX() + rank->getContentSize().width+10 , label->getPositionY());
    this->addChild(ranklabel,5);
    
    //战斗力
    Sprite* fight = Sprite::create(IMG_ARENA_BGE);
    fight->setAnchorPoint(Point::ZERO);
    fight->setPosition(180,40);
    this->addChild(fight);
    
    str =  PublicShowUI::numberToString(data->power);
    Label* fightlabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),22,false,false);
    fightlabel->setAnchorPoint(Point::ZERO);
    this->addChild(fightlabel,3);
    fightlabel->setPosition(fight->getPositionX() + fight->getContentSize().width,fight->getPositionY());
    this->addChild(fightlabel,1);
    
    //排名
//    Sprite* rankbg = Sprite::create(IMG_ARENALIST_RANKBG);
//    rankbg->setAnchorPoint(Point::ZERO);
//    rankbg->setPosition(100,10);
//    this->addChild(rankbg,5);
//    str = PublicShowUI::numberToString(data->rank);
//    Label* ranklabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT),fontSize,false,false);
//    ranklabel->setAnchorPoint(Point::ZERO);
//    ranklabel->setPosition(rankbg->getContentSize().width/2-ranklabel->getContentSize().width/2,rankbg->getContentSize().height/2-ranklabel->getContentSize().height/2);
//    rankbg->addChild(ranklabel,1);
}
void ChallengeNode::setPrizeValue()
{
    ArenaListData* data = ArenaDataManager::getInstance()->arenaList->at(m_index);
    
    long herosize = data->heroHeadList.size();
    for (int i = 0; i< herosize; i++) {
        DictHero* dictMonster = DictHeroManager::getInstance()->getData(data->heroHeadList.at(i).herodict);
        if (dictMonster) {
            
            Sprite* headbg = Sprite::create(IMG_ARENALIST_HEADBG);
            headbg->setAnchorPoint(Point::ZERO);
            headbg->setScale(0.6);
            this->addChild(headbg,1);
            headbg->setPosition(340+i*(headbg->getContentSize().width-10),10);
           
            const char* path = dictMonster ? dictMonster->headResource.c_str() : "zhaoyun";
            path = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH,path);
            Sprite* head = Sprite::create(path);
            head->setAnchorPoint(Point::ZERO);
            head->setScale(0.65);
            head->setPosition(340+i*(headbg->getContentSize().width-10),10);
            this->addChild(head,2);
            
            
    
            Sprite* headbox = Sprite::create(IMG_ARENALIST_HEADBOX);
            headbox->setAnchorPoint(Point::ZERO);
            headbox->setScale(0.6);
            headbox->setPosition(340+i*(headbg->getContentSize().width-10),10);
            this->addChild(headbox,3);
        }
    }

    
    //排名奖励
//    Sprite* orderPrize = Sprite::create(IMG_ARENA_NOWORDERPRIZE);
//    orderPrize->setAnchorPoint(Point::ZERO);
//    orderPrize->setPosition(180, this->getContentSize().height /2 - 30);
//    this->addChild(orderPrize,3);
//    //荣誉值
//    Sprite* glorySpr = Sprite::create(IMG_ARENA_HONOR);
//    glorySpr->setAnchorPoint(Point::ZERO);
//    string str = PublicShowUI::numberToString(data->honor);
//    Label* gloryLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),24,false,false);
//    gloryLabel->setAnchorPoint(Point(0,.5));
//    glorySpr->addChild(gloryLabel,3);
//    gloryLabel->setPosition(glorySpr->getContentSize().width, glorySpr->getContentSize().height/2);
//    glorySpr->setPosition(orderPrize->getPositionX() + orderPrize->getContentSize().width, orderPrize->getPositionY());
//    Size size = glorySpr->getContentSize();
//    size.width = gloryLabel->getPositionX() + gloryLabel->getContentSize().width;
//    glorySpr->setContentSize(size);
//    this->addChild(glorySpr,4);
//    //元宝
//    Sprite* coinSpr = Sprite::create(IMG_ICON_PUBLIC_GOLD);
//    coinSpr->setAnchorPoint(Point::ZERO);
//    str = PublicShowUI::numberToString(data->coin);
//    Label* coinLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),24,false,false);
//    coinLabel->setAnchorPoint(Point(0,.5));
//    coinSpr->addChild(coinLabel,3);
//    coinLabel->setPosition(coinSpr->getContentSize().width, coinSpr->getContentSize().height/2);
//    coinSpr->setPosition(glorySpr->getPositionX() + glorySpr->getContentSize().width, glorySpr->getPositionY());
//    size = coinSpr->getContentSize();
//    size.width = coinLabel->getPositionX() + coinLabel->getContentSize().width;
//    coinSpr->setContentSize(size);
//    this->addChild(coinSpr,4);
    
}
void ChallengeNode::setBtn()
{
    CustomButton* btn = CustomButton::create(IMG_ARENALIST_TIAOZHAN, "", CC_CALLBACK_1(ChallengeNode::onBtnClick, this));
    btn->setPosition(this->getContentSize().width - btn->getContentSize().width /2 - 16 , this->getContentSize().height/2);
    this->addChild(btn,5,m_index);
    if(m_index == 2)
    {
        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumDekaronButton, btn);
    }
}
void ChallengeNode::onBtnClick(Ref* pSender)
{
     ArenaListData* data = ArenaDataManager::getInstance()->arenaList->at(m_index);
    PlayerDataManager::getInstance()->_targetRoleID = m_index+1;
     broadMsg(CUSTOM_ARENA_FIGHT_INDEX,__Integer::create(m_index));
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumDekaronButton);
}
void ChallengeNode::onEnter()
{
    BaseLayer::onEnter();
}
void ChallengeNode::onExit()
{
    BaseLayer::onExit();
}
void ChallengeNode::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void ChallengeNode::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}