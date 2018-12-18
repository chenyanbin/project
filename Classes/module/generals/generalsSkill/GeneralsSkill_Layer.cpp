//
//  GeneralsBase_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/7/29.
//
//

#include "GeneralsSkill_Layer.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../message/Decoding/generals/skill/SkillMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../data/CardDataManager.h"
GeneralsSkill_Layer::GeneralsSkill_Layer()
:titleCount(0)
,sx(1)
,cardId(1)
,TAG_LISTBG(1)
,TAG_TABLEVIEW(2)
,cardData(NULL)
,viewNode(NULL)
{
    
}
GeneralsSkill_Layer::~GeneralsSkill_Layer()
{
    
}
void GeneralsSkill_Layer::onExit()
{
    BaseLayer::onExit();
}
void GeneralsSkill_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void GeneralsSkill_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void GeneralsSkill_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestListMsg();
}
bool GeneralsSkill_Layer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        this->setBackground(IMG_GENERALS_BG);
//        this->createLayer();
        bref = true;
    } while (false);
    return bref;
}
//void GeneralsSkill_Layer::createLayer()
//{
//    Sprite* bgSprite=(Sprite*) this->getChildByTag(TAG_BG);
//    Sprite* bgbox=Sprite::create(IMG_GENERALS_BASE_BGBOX);
//    bgbox->setAnchorPoint(Point::ZERO);
//    bgbox->setPosition(Point::ZERO);
//    bgSprite->addChild(bgbox);
//    Sprite* bg2=Sprite::create(IMG_GENERALS_BASE_BG2);
//    bg2->setAnchorPoint(Point::ZERO);
//    bg2->setPosition(Point::ZERO);
//    bgSprite->addChild(bg2,1);
//    
//}
Node* GeneralsSkill_Layer::initView()
{
    Sprite* tempSprite=Sprite::create(IMG_GENERALS_BASE_BG);
    viewNode=Node::create();
    viewNode->setAnchorPoint(Point(0,1));
    viewNode->setContentSize(tempSprite->getContentSize());
    
    Sprite* skillBg=Sprite::create(IMG_GENERALS_SKILL_NUM_BG);
    skillBg->setAnchorPoint(Point::ZERO);
    skillBg->setPosition(10,-skillBg->getContentSize().height);
    viewNode->addChild(skillBg,2);
    
    Sprite* skillLabel=Sprite::create(IMG_GENERALS_SKILL_LABEL1);
    skillLabel->setAnchorPoint(Point::ZERO);
    skillLabel->setPosition(10,-skillBg->getContentSize().height);
    viewNode->addChild(skillLabel,2);
    
    
    int sizeInt=(int)cardData->skillList.size();
    int labelHeight=0;
    //技能
    for (int i=0; i<sizeInt; i++) {
        if (i>=3) {
            
            Sprite* skillBg1=Sprite::create(IMG_GENERALS_SKILL_NUM_BG);
            skillBg1->setAnchorPoint(Point::ZERO);
            skillBg1->setPosition(10,skillBg->getPositionY()-20-labelHeight-32);
            viewNode->addChild(skillBg1,2);
            
            Sprite* skillLabel1=Sprite::create(IMG_GENERALS_SKILL_LABEL2);
            skillLabel1->setAnchorPoint(Point::ZERO);
            skillLabel1->setPosition(10,skillBg->getPositionY()-20-labelHeight-32);
            viewNode->addChild(skillLabel1,2);
            
            //分割线
            Sprite* line2Sprite=Sprite::create(IMG_GENERALS_SKILL_CONT_LINE);
            line2Sprite->setAnchorPoint(Point::ZERO);
            line2Sprite->setPosition((viewNode->getContentSize().width/sx-line2Sprite->getContentSize().width)/2, skillBg1->getContentSize().height+ skillBg->getPositionY()-20-labelHeight-33);
            viewNode->addChild(line2Sprite);
            
            labelHeight+=skillBg->getContentSize().height;
            
            

        }
        if (cardData->skillList.at(i).skillName=="") {
            continue;
        }
        string name= "["+cardData->skillList.at(i).skillName+"]";
        Label* nameLabel = PublicShowUI::getLabel(name.c_str(),PublicShowUI::getColor3b(COLOR_DEEP_RED),18,false,false);
        nameLabel->setAnchorPoint(Point::ZERO);
        nameLabel->setPosition(25,skillBg->getPositionY()-20-labelHeight);
        viewNode->addChild(nameLabel,2);
        string descStr="    "+cardData->skillList.at(i).skillDesc;
        Label* descLabel = PublicShowUI::getLabel(descStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
        descLabel->setAnchorPoint(Point(0,1));
        descLabel->setPosition(25,nameLabel->getPositionY()-8);
        descLabel->setMaxLineWidth(250);
        viewNode->addChild(descLabel,2);
        labelHeight+=descLabel->getContentSize().height+20+nameLabel->getContentSize().height;
    }
    
    //缘分
    Sprite* karmaBg=Sprite::create(IMG_GENERALS_SKILL_NUM_BG);
    karmaBg->setAnchorPoint(Point::ZERO);
    karmaBg->setPosition(10,skillBg->getPositionY()-20-labelHeight-32);
    viewNode->addChild(karmaBg,2);
    
    Sprite* karmaLabel=Sprite::create(IMG_GENERALS_KARMA_LABEL);
    karmaLabel->setAnchorPoint(Point::ZERO);
    karmaLabel->setPosition(10,skillBg->getPositionY()-20-labelHeight-32);
    viewNode->addChild(karmaLabel,2);
    //分割线
    Sprite* lineSprite=Sprite::create(IMG_GENERALS_SKILL_CONT_LINE);
    lineSprite->setAnchorPoint(Point::ZERO);
    lineSprite->setPosition((viewNode->getContentSize().width/sx-lineSprite->getContentSize().width)/2, karmaBg->getContentSize().height+ skillBg->getPositionY()-20-labelHeight-33);
    viewNode->addChild(lineSprite);
    
    labelHeight+=karmaLabel->getContentSize().height;
    
    
    
    sizeInt=(int)cardData->karmList->size();
    for (int i=0; i<sizeInt; i++) {
        Color3B color = cardData->karmList->at(i)->karmaOwn ? PublicShowUI::getColor3b(0xffc9b9) : Color3B::GRAY;
        string name= "["+cardData->karmList->at(i)->karmaName+"]";
        Label* nameLabel = PublicShowUI::getLabel(name.c_str(),color,18,false,false);
        nameLabel->setAnchorPoint(Point::ZERO);
        nameLabel->setPosition(25,skillBg->getPositionY()-20-labelHeight);
        viewNode->addChild(nameLabel,2);
        string descStr="    "+cardData->karmList->at(i)->karmaDesc;
        color = cardData->karmList->at(i)->karmaOwn ? PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW) : Color3B::GRAY;
        Label* descLabel = PublicShowUI::getLabel(descStr.c_str(),color,18,false,false);
        descLabel->setAnchorPoint(Point(0,1));
        descLabel->setPosition(25,nameLabel->getPositionY()-8);
        descLabel->setMaxLineWidth(250);
        viewNode->addChild(descLabel,2);
        labelHeight+=descLabel->getContentSize().height+20+nameLabel->getContentSize().height;
    }
    Size size=viewNode->getContentSize();
    size.height=labelHeight+skillBg->getContentSize().height+20;
    viewNode->setContentSize(size);
    return viewNode;
}
//-----------------------------------------------访问服务器-------------------------------------------------------//
void GeneralsSkill_Layer::requestListMsg()
{
    SkillMsg* msg = new SkillMsg(CardDataManager::getInstance()->getPresentData()->heroId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void GeneralsSkill_Layer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_HERO_HeroSkillPageResp)
    {
        cardData=new CardPropertyData();
        int sizeInt=message->byteStream->getByte();
        for (int i=0; i<sizeInt; i++) {
            struct SkillData _skill = {"",""};
            _skill.skillName=message->byteStream->getUTF8();
            _skill.skillDesc=message->byteStream->getUTF8();
            cardData->skillList.push_back(_skill);
        }
        sizeInt=message->byteStream->getByte();
        for (int i=0; i<sizeInt; i++) {
            KarmaData* _karma=new KarmaData();
            _karma->karmaName=message->byteStream->getUTF8();
            _karma->karmaDesc=message->byteStream->getUTF8();
            _karma->karmaOwn=message->byteStream->getByte()>0;
            cardData->karmList->push_back(_karma);
        }
    }
    this->initTableView();
}
void GeneralsSkill_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroSkillPageResp).c_str(), CC_CALLBACK_1(GeneralsSkill_Layer::onMsgProcess, this));
}
void GeneralsSkill_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}

//--------------------------------列表部分-------------------------------------------------------//
void GeneralsSkill_Layer::initTableView()
{
    Sprite* listBg=(Sprite*)this->getChildByTag(TAG_BG);
    TableView* _tableView = (TableView*)listBg->getChildByTag(TAG_TABLEVIEW);
    //
    if(_tableView)
    {
        Point cp=_tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=480;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(0,18);
    listBg->addChild(_tableView,2,TAG_TABLEVIEW);
}
TableViewCell* GeneralsSkill_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    if (idx==0) {
        Node* view=this->initView();
        view->setPosition(0,view->getContentSize().height*2);
        cell->addChild(view);
    }
   
    return cell;
}

//列表大小
Size GeneralsSkill_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    if (idx==0) {
        Node* temp;
        if (viewNode) {
            temp=viewNode;
        }else{
            temp=this->initView();
        }
        cellSize=temp->getContentSize();
    }else
    {
        cellSize=Point::ZERO;
    }
    return cellSize;
}
//获取view的长度
ssize_t GeneralsSkill_Layer::numberOfCellsInTableView(TableView *table)
{
    return 2;
}
//点击cell事件
void GeneralsSkill_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}


