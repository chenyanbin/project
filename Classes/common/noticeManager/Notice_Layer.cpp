//
//  Notice_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 16/1/26.
//
//

#include "Notice_Layer.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../message/Decoding/notice/NoicePageMsg.h"
#include "../../net/HttpURLManager.h"
#include "../../common/md5/MD5.h"
#include "../../common/Dialog/Dialog.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "../../common/StringUtil.h"

#include "cocostudio/DictionaryHelper.h"
#include "../TouchSprite/Button.h"
Notice_Layer::Notice_Layer()
:viewNode(NULL)
,sx(1)
,TAG_TABLEVIEW(1)
,noticeMold(-1)
{
    noticeList= NULL;
}
Notice_Layer::~Notice_Layer(){
    CC_SAFE_DELETE(noticeList);
}
void Notice_Layer::onExit(){
    BaseLayer::onExit();
}
void Notice_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void Notice_Layer::onExitTransitionDidStart(){
    BaseLayer::onExitTransitionDidStart();
}
void Notice_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->initTableView();
}
bool Notice_Layer::init(Vector<NoticeData*> * value){
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        noticeList=value;
        sx=GlobalInfo::getInstance()->screenScaleX;
        this->setClickEnabled(true);
        this->isClickClose=true;
        this->isShowGrayBg=true;
        initLayer();
        
        bref = true;
    } while (false);
    return bref;

}
Notice_Layer* Notice_Layer::create(Vector<NoticeData*> * value){
    Notice_Layer* layer = new Notice_Layer();
    if(layer && layer->init(value))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void Notice_Layer::show(Vector<NoticeData*> * value){
    
    Scene* scene = Director::getInstance()->getRunningScene();
    Notice_Layer* layer=Notice_Layer::create(value);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,SCENE_NOTICE_ZORDER ,SCENE_LAYERLOADING_ZORDER);

   
}
void Notice_Layer::initLayer()
{
    this->setBackground(IMG_PUBLIC_LAYER_NOTICE);
    this->createLayer();
    
}
void Notice_Layer::createLayer()
{
    Sprite* titleLabel=Sprite::create(IMG_PUBLIC_LABEL_NOTICE);
    titleLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(titleLabel);
    titleLabel->setPosition((this->getContentSize().width-titleLabel->getContentSize().width)/2,430*sx);
    this->addChild(titleLabel,3);
    
    Button* exitBtn=Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(Notice_Layer::onClick, this));
    exitBtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(exitBtn);
    exitBtn->setPosition((this->getContentSize().width-exitBtn->getContentSize().width)/2,16*sx);
    this->addChild(exitBtn,3);
    
    Sprite* exitBtnLabel=Sprite::create(IMG_PUBLIC_LABEL_CAN);
    exitBtnLabel->setAnchorPoint(Point::ZERO);
    exitBtnLabel->setPosition((exitBtn->getContentSize().width/sx-exitBtnLabel->getContentSize().width)/2,(exitBtn->getContentSize().height/sx-exitBtnLabel->getContentSize().height)/2);
    exitBtn->addChild(exitBtnLabel,2);
}
void Notice_Layer::onClick(Ref* pSender)
{
    this->backScene();
}
Node* Notice_Layer::initView()
{
    
    Sprite* tempSprite=Sprite::create(IMG_PUBLIC_LAYER_NOTICE);
    viewNode=Node::create();
    viewNode->setAnchorPoint(Point(0,1));
    viewNode->setContentSize(tempSprite->getContentSize());
    
    int sizeInt=(int)noticeList->size();
    int labelHeight=0;
    //技能
    for (int i=0; i<sizeInt; i++) {
        
        string name= noticeList->at(i)->NoticeName;
        int start=name.find("#");
        int valueInt=-1;
        if (start==0) {
            string value=name.substr(start,start+3);
            name=name.substr(start+3,name.size());
            if (value=="#01") {
                valueInt=-1;
            }else if (value=="#02")
            {
                valueInt=2;
            }else if (value=="#03")
            {
                valueInt=3;
            }
        }
        Label* nameLabel = PublicShowUI::getLabel(name.c_str(),PublicShowUI::getColor3b(COLOR_NOTIC_GREEN),24,false,false);
        nameLabel->setAnchorPoint(Point::ZERO);
        if (valueInt==-1) {
            nameLabel->setPosition(25,-30-labelHeight);
        }else if (valueInt==2)
        {
            nameLabel->setPosition((this->getContentSize().width-nameLabel->getContentSize().width)/2,-30-labelHeight);
        }else if (valueInt==3)
        {
            nameLabel->setPosition(this->getContentSize().width-nameLabel->getContentSize().width-20,-30-labelHeight);
        }
        viewNode->addChild(nameLabel,2);
        labelHeight+=nameLabel->getContentSize().height;
        
        int len=(int)noticeList->at(i)->DescList->size();
        for (int j=0; j<len; j++) {
            string descStr=noticeList->at(i)->DescList->at(j);
            Label* descLabel = PublicShowUI::getLabel(descStr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),20,false,false);
            descLabel->setAnchorPoint(Point(0,1));
            descLabel->setPosition(50,-labelHeight);
            descLabel->setMaxLineWidth(500);
            labelHeight+=descLabel->getContentSize().height+10;
            
            viewNode->addChild(descLabel,2);
        }
    }
    Size size=viewNode->getContentSize();
    size.height=labelHeight+20;
    viewNode->setContentSize(size);
    return viewNode;
}

//--------------------------------列表部分-------------------------------------------------------//
void Notice_Layer::initTableView()
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
    _size.height=350;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(0,70);
    listBg->addChild(_tableView,2,TAG_TABLEVIEW);
}
TableViewCell* Notice_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
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
Size Notice_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
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
ssize_t Notice_Layer::numberOfCellsInTableView(TableView *table)
{
    return 1;
}
//点击cell事件
void Notice_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}