//
//  ArenaExplainLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/30.
//
//

#include "ArenaExplainLayer.hpp"
#include "../../common/TouchSprite/Button.h"
#include "../../commonData/dictData/DictSkill/DictSkillManager.h"
#include "../../common/StringUtil.h"
ArenaExplainLayer::ArenaExplainLayer()
:sx(0)
{
    
}
ArenaExplainLayer::~ ArenaExplainLayer()
{
    
}
void ArenaExplainLayer::onExit()
{
    BaseLayer::onExit();
}
void ArenaExplainLayer::onEnter()
{
    BaseLayer::onEnter();
}
void ArenaExplainLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void ArenaExplainLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
bool ArenaExplainLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        
        this->setBackground(IMG_LIMITCARD_SKILLBG);
        this->isAnimation = false;
        this->isClickClose=true;
        this->setClickEnabled(true);
        this->isShowGrayBg = true;
        this->createLayer();
        
        bref = true;
    } while (false);
    return bref;
}
ArenaExplainLayer* ArenaExplainLayer::create()
{
    ArenaExplainLayer* layer = new ArenaExplainLayer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void ArenaExplainLayer::show( )
{
    ArenaExplainLayer* layer = ArenaExplainLayer::create();
    if(layer)
    {
        Scene* scene = Director::getInstance()->getRunningScene();
        layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2,VisibleRect::center().y - layer->getContentSize().height/2);
        scene->addChild(layer,SCENE_LAYER_ZORDER);
    }
}
void ArenaExplainLayer::createLayer( )
{
    Sprite* layerbg = (Sprite*)this->getChildByTag(TAG_BG);
   
    
//    Sprite* titlebg = Sprite::create(IMG_LIMITCARD_SKILLONETITLEBG);
//    titlebg->setAnchorPoint(Point::ZERO);
//    titlebg->setPosition(15,this->getContentSize().height/sx-titlebg->getContentSize().height-15);
//    layerbg->addChild(titlebg,1);
//    
//    Sprite* title = Sprite::create(IMG_LIMITCARD_SKILLONETITLE);
//    title->setAnchorPoint(Point::ZERO);
//    title->setPosition(20,8);
//    titlebg->addChild(title);
    
    string nameStr = "竞技场说明";//StringUtils::format("");
    Label* nameLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_WHITE),28,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition((layerbg->getContentSize().width/sx-nameLabel->getContentSize().width)/2,layerbg->getContentSize().height/sx - nameLabel->getContentSize().height - 30);
    layerbg->addChild(nameLabel,2);
    
    string titleStr = "●竞技场通用规则";//StringUtils::format("");
    Label* titleLabel = PublicShowUI::getLabel(titleStr.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_WHITE),26,false,false);
    titleLabel->setAnchorPoint(Point::ZERO);
    titleLabel->setPosition(50,380);
    layerbg->addChild(titleLabel,2);
    
    
    string expStr = "1.每日21点按照名次通过邮件发放奖励 \n2.竞技场中的战斗自动进行，不能进行手动操作 \n3.功能挑战排名高于自己的对手时,双方排名互换 \n4.战斗超时算作进攻方失败 \n5.玩家可随时调整自己的队伍阵容 \n6.竞技场战斗后可以获得荣誉，荣誉可以用于兑换道具";
    vector<string> list = StringUtil::split(expStr, " ");
    ssize_t len = list.size();
    string str = "";
    for(int i = 0; i < len; i++)
    {
        if(i < len - 1)
        {
            str += list[i] + "\n";
        }
        else
        {
            str += list[i];
        }
    }
    Label* expLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_WHITE),20,false,false);
    expLabel->setAnchorPoint(Point::ZERO);
    expLabel->setPosition(50,70);
    layerbg->addChild(expLabel,2);
    
    
  }

