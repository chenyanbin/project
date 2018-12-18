//
//  Chat_Scene.cpp
//  FightPass
//
//  Created by 超 顾 on 15/11/20.
//
//

#include "Chat_Scene.h"
#include "../../common/TouchSprite/Button.h"
#include "../../common/Dialog/Dialog.h"
#include "data/MessageData.h"
#include "messageList/MessageList_Layer.h"
#include "findFriendList/FindFriendList_Layer.h"
#include "friendList/FriendList_Layer.h"
#include "friendApplyList/FriendApplyList_Layer.h"
#include "chatContent/ChatContent_Layer.h"
#include "chatContent/FriendChatCont_Layer.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../commonData/dictData/DictHero/DictHeroManager.h"
#include "selectHead/SelectHeadLayer.h"
#include "../../message/Decoding/chat/FriendMyInfoMsg.h"
#include "../../message/Decoding/chat/UpdateYaYaIdMsg.h"
Chat_Scene::Chat_Scene()
:sx(1)
,editbox(NULL)
,listBg(NULL)
,headImg(NULL)
,myHeadId(0)
,boxBtn(NULL)
,TAG_COMBOBOXBTN(0)//listbg 下的tag值保留3位
,TAG_TRAN(5)
,TAG_SEARCH(6)
,TAG_LAYER(7)
,TAG_CHATCONTENT(8)
,TAG_SHEJIAOBTN(9)
,TAG_MESSAGELAYER(100)
,TAG_FRIENDLAYER(101)
,TAG_APPLYLAYER(102)
,TAG_SEARCHLAYER(103)
,selectBtn(0)
,chatFriendId(0)
{
    btnList = new Vector<TouchSprite*>();
    
}
Chat_Scene::~Chat_Scene()
{
    btnList->clear();
    CC_SAFE_DELETE(btnList);
    btnList = NULL;
}
bool Chat_Scene::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx= GlobalInfo::getInstance()->screenScaleX;
        this->createLayer();
        
        bref = true;
    } while (false);
    return bref;
}
void Chat_Scene::onEnter()
{
    BaseLayer::onEnter();

}
void Chat_Scene::onExit()
{
    BaseLayer::onExit();
}
void Chat_Scene::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestMyInfoMsg();
}
void Chat_Scene::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
   
}
Chat_Scene* Chat_Scene::create()
{
    Chat_Scene* layer = new Chat_Scene();
    if(layer && layer->init())
    {
        layer->autorelease();
        
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}

//社交按钮返回
void Chat_Scene::onSocialBtnClick(Ref* psender)
{
    Button* btn=(Button*)this->getChildByTag(TAG_SHEJIAOBTN);
    Node* layer=(Node*)this->getChildByTag(TAG_CHATCONTENT);
    if (!layer) {
         layer=(Node*)this->getChildByTag(TAG_FRIENDCHAT);
    }
    if (!listBg) {
        return;
    }
    FiniteTimeAction* move=NULL;
    FiniteTimeAction* move2=NULL;
    FiniteTimeAction * seq =NULL;
    CallFunc* funcall = NULL;
    btn->stopAllActions();
    listBg->stopAllActions();
    
    if (btn->getPositionX()==0) {
        this->setGrayBg();
        this->setClickEnabled(true);
        move =MoveTo::create(0.2, Point(listBg->getContentSize().width-7*sx,btn->getPositionY()));
        move2 =MoveTo::create(0.2, Point(-2,listBg->getPositionY()));
        funcall = CallFunc::create(CC_CALLBACK_0(Chat_Scene::callbackC, this));
    }else
    {
        this->removeGrayBg();
        this->setClickEnabled(false);
        move =MoveTo::create(0.2, Point(0,btn->getPositionY()));
        move2 =MoveTo::create(0.2, Point(-listBg->getContentSize().width+7*sx,listBg->getPositionY()));
        if (layer) {
            MoveTo* move1=MoveTo::create(0.2, Point(-layer->getContentSize().width, layer->getPositionY()));
          
            seq = Sequence::create(move1,funcall,NULL);
            layer->runAction(seq);
        }
    }
    btn->runAction(move);
//    listBg->runAction(move2->clone());
    listBg->runAction(Sequence::create(move2,funcall, NULL));
    
}
void Chat_Scene::callbackC()
{
    onSelectMessageCallBack(NULL);
}
//聊天界面
void Chat_Scene::createLayer()
{
    listBg=Sprite::create(IMG_CHAT_LISTBG);
    listBg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(listBg);
    listBg->setPosition(-listBg->getContentSize().width,VisibleRect::center().y-listBg->getContentSize().height/2);
    this->addChild(listBg,2);
    
    TouchSprite* touchSp=TouchSprite::createWithPic(IMG_CHAT_LISTBG, this,NULL);
    touchSp->setAnchorPoint(Point::ZERO);
    listBg->addChild(touchSp);
    
    //头像背景
    char sttr[100]="";
    sprintf(sttr,IMG_PUBLIC_HEROHEADFRAMEBG,0);
    TouchSprite* headBg=TouchSprite::createWithPic(sttr, this, callfuncN_selector(Chat_Scene::onUserClick));
    headBg->setPosition(38,500);
    headBg->setAnchorPoint(Point::ZERO);
    listBg->addChild(headBg,1);
    //头像框
    char stt[100]="";
    sprintf(stt,IMG_PUBLIC_HEADTALENTFRAME,0);
    Sprite* headBox=Sprite::create(stt);
    headBox->setAnchorPoint(Point::ZERO);
    headBox->setPosition(38,500);
    listBg->addChild(headBox,2);
    
    //头像
    string headStr=GlobalInfo::getInstance()->gameRole->headID;
    int headId=atoi(headStr.c_str());
    DictHero* data=DictHeroManager::getInstance()->getData(headId);
    if (data) {
        const char* imgPath = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH, data->headResource.c_str());
        headImg = Sprite::create(imgPath);
        if(headImg)
        {
            headImg->setAnchorPoint(Point::ZERO);
            float scaleX=(headBox->getContentSize().width-3)/headImg->getContentSize().width;
            float scaleY=(headBox->getContentSize().height-3)/headImg->getContentSize().height;
            headImg->setScale(scaleX,scaleY);
            headImg->setPosition(38,503);
            listBg->addChild(headImg,1);
        }
       
    }
    
   
    
    string str = GlobalInfo::getInstance()->gameRole->name;
    log("dsfdsfdsfGlobalInfo::getInstance()->===============%s",GlobalInfo::getInstance()->gameID.c_str());
    if (str=="") {
        str=PublicShowUI::numberToString(GlobalInfo::getInstance()->gameRole->roleID);
    }
    Label* nameLabel=PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0x000000),20,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(176,585);
    listBg->addChild(nameLabel);
    
    Sprite* lv=Sprite::create(IMG_CHAT_LV);
    lv->setAnchorPoint(Point::ZERO);
    lv->setPosition(172,537);
    listBg->addChild(lv);
    int num = GlobalInfo::getInstance()->gameRole->level;
    str=PublicShowUI::numberToString(num);
    Label* lvLabel=PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0x000000),20,false,false);
    lvLabel->setAnchorPoint(Point::ZERO);
    lvLabel->setPosition((lv->getContentSize().width)/2,(lv->getContentSize().height-lvLabel->getContentSize().height)/2);
    lv->addChild(lvLabel);
    
    
    Sprite* combatPower=Sprite::create(IMG_PUBLIC_MILITARY);
    combatPower->setAnchorPoint(Point::ZERO);
    combatPower->setPosition(172,500);
    listBg->addChild(combatPower);
    num = GlobalInfo::getInstance()->gameRole->combatPower;
    str=PublicShowUI::numberToString(num);
    Label* powerLabel=PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(0x000000),20,false,false);
    powerLabel->setAnchorPoint(Point::ZERO);
    powerLabel->setPosition((combatPower->getContentSize().width)/2,(combatPower->getContentSize().height-powerLabel->getContentSize().height)/2);
    combatPower->addChild(powerLabel);
    
    
    Button* addfriend=Button::create(IMG_CHAT_ADDFRIEND,IMG_CHAT_ADDFRIEND,CC_CALLBACK_1(Chat_Scene::onFriendBtnClick, this));
    addfriend->setPosition(400,598);
    listBg->addChild(addfriend);
    //列表底层
    Sprite* friendBg=Sprite::create(IMG_CHAT_FRIENDBG);
    friendBg->setAnchorPoint(Point::ZERO);
    friendBg->setPosition(0,415);
    listBg->addChild(friendBg);
    
    const char* pathList[3] = {IMG_CHAT_MESSAGELISTLABEL2,IMG_CHAT_FRIENDLISTLABEL2,IMG_CHAT_FRIENDAPPLYLABEL2};
    const char* pathList2[3] = {IMG_CHAT_MESSAGELISTLABEL,IMG_CHAT_FRIENDLISTLABEL,IMG_CHAT_FRIENDAPPLYLABEL};
    int functionList[3] = {TAG_MESSAGELAYER,TAG_FRIENDLAYER,TAG_APPLYLAYER};
    boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 0, CC_CALLBACK_1(Chat_Scene::onComboBoxBtnClick, this));
    for (int i = 0; i<3; i++) {
        boxBtn->addBtn(pathList[i], pathList2[i], "",false,functionList[i]);
    }
    boxBtn->setAnchorPoint(Point::ZERO);
    boxBtn->setPosition(22,420);
    boxBtn->selectAtByTag(TAG_MESSAGELAYER);
    listBg->addChild(boxBtn,3);

    Sprite* tran=Sprite::create(IMG_CHAT_CONTENTSELECTED);
    tran->setAnchorPoint(Point::ZERO);
    tran->setPosition(45, 416);
    listBg->addChild(tran,4,TAG_TRAN);
    
    
    Sprite* flower1=Sprite::create(IMG_CHAT_FLOWERSIDE);
    flower1->setAnchorPoint(Point::ZERO);
    flower1->setRotationSkewX(180);
    flower1->setPosition(6,35);
    listBg->addChild(flower1,5);
    
    Sprite* flower2=Sprite::create(IMG_CHAT_FLOWERSIDE);
    flower2->setAnchorPoint(Point::ZERO);
    flower2->setRotation(180);
    flower2->setPosition(461,35);
    listBg->addChild(flower2,5);
   
    
    //社交按钮
    Button* socialBtn=Button::create(IMG_CHAT_SOCIALBTN,IMG_CHAT_SOCIALBTN,CC_CALLBACK_1(Chat_Scene::onSocialBtnClick, this));
    socialBtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(socialBtn);
    socialBtn->setPosition(0,VisibleRect::center().y-socialBtn->getContentSize().height/2);
    this->addChild(socialBtn,1,TAG_SHEJIAOBTN);
}
//点击头像
void Chat_Scene::onUserClick(Node* pSender)
{
    SelectHeadLayer* layer=SelectHeadLayer::create();
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
    Scene* scene=Director::getInstance()->getRunningScene();
    scene->addChild(layer);
}
//加好友按钮返回
void Chat_Scene::onFriendBtnClick(Ref* psender)
{
    Sprite* searchBg=(Sprite*)listBg->getChildByTag(TAG_SEARCH);
    Button* btn=(Button*)psender;
    if (searchBg) {
        listBg->removeChildByTag(TAG_SEARCH);
        btn->setNormalImage(IMG_CHAT_ADDFRIEND);
        boxBtn->setVisible(true);
        boxBtn->selectAtByTag(TAG_MESSAGELAYER);
    }else
    {
        boxBtn->setVisible(false);
        boxBtn->resetAllBtn();
        btn->setNormalImage(IMG_PUBLIC_BACKBTN);
        //列表底层
        searchBg=Sprite::create(IMG_CHAT_FRIENDBG);
        searchBg->setAnchorPoint(Point::ZERO);
        searchBg->setPosition(0,415);
        listBg->addChild(searchBg,12,TAG_SEARCH);
        
        Button* searchBtn=Button::create(IMG_CHAT_SEARCH, IMG_CHAT_SEARCH, CC_CALLBACK_1(Chat_Scene::onSearchBtnClick, this));
        searchBtn->setAnchorPoint(Point::ZERO);
        searchBtn->setPosition(30,7);
        searchBg->addChild(searchBtn);
        
        Sprite* line=Sprite::create(IMG_CHAT_LINE);
        line->setAnchorPoint(Point::ZERO);
        line->setPosition(166,13);
        searchBg->addChild(line);
        
        editbox = EditBox::create(Size(line->getContentSize().width,44), Scale9Sprite::create());
        editbox->setAnchorPoint(Point::ZERO);
        editbox->setText("请输入玩家昵称");
        editbox->setInputMode(EditBox::InputMode::ANY);
        editbox->setDelegate(this);
        editbox->setPosition(Point(166,16));
        searchBg->addChild(editbox,1);
        
        this->hideOtherLayer(TAG_SEARCHLAYER);
    }
}
//打开世界聊天框
void Chat_Scene::onSelectMessageCallBack(EventCustom* msg)
{
    Sprite* contentLayer=(Sprite*)this->getChildByTag(TAG_CHATCONTENT);
    if (contentLayer) {
        Button* btn=(Button*)this->getChildByTag(TAG_SHEJIAOBTN);
        FiniteTimeAction* move=NULL;
        FiniteTimeAction* move2=NULL;
        btn->stopAllActions();
        move =MoveTo::create(0.2, Point(listBg->getContentSize().width-7*sx,contentLayer->getPositionY()));
        move2 =MoveTo::create(0.2, Point(listBg->getContentSize().width+contentLayer->getContentSize().width-9*sx,btn->getPositionY()));
        btn->runAction(move2->clone());
        contentLayer->runAction(move->clone());
        return;
    }
    Sprite* layer=(Sprite*)this->getChildByTag(TAG_FRIENDCHAT);
    if (layer) {
        Button* btn=(Button*)this->getChildByTag(TAG_SHEJIAOBTN);
        MoveTo* move2 =MoveTo::create(0.1, Point(listBg->getContentSize().width-7*sx,btn->getPositionY()));
        btn->runAction(move2);
        
        MoveTo* move=MoveTo::create(0.1, Point(-layer->getContentSize().width, layer->getPositionY()));
        //    CCCallFunc
        //    作用：创建一个回调动作（调用不带参数的回调方法）；
        //    参数1：目标动作
        //    参数2：目标回调函数
        CallFunc* funcall = CallFunc::create(CC_CALLBACK_0(Chat_Scene::WorldCallBackC, this));
        FiniteTimeAction * seq = Sequence::create(move,funcall,NULL);
        layer->runAction(seq);
    }else{
        this->SetChatLayer(0);
    }
}
//点击好友聊天了
void Chat_Scene::onSelectFriendMessageCallBack(EventCustom* msg)
{
    __Integer* inter = (__Integer*)msg->getUserData();
    chatFriendId = inter->getValue();
    
    Sprite* layer=(Sprite*)this->getChildByTag(TAG_FRIENDCHAT);
    Sprite* layer2=(Sprite*)this->getChildByTag(TAG_CHATCONTENT);
    
    if (layer) {
        
        Button* btn=(Button*)this->getChildByTag(TAG_SHEJIAOBTN);
        MoveTo* move2 =MoveTo::create(0.1, Point(listBg->getContentSize().width-7*sx,btn->getPositionY()));
        btn->runAction(move2);
        
        MoveTo* move=MoveTo::create(0.1, Point(-layer->getContentSize().width,layer->getPositionY()));
        //    CCCallFunc
        //    作用：创建一个回调动作（调用不带参数的回调方法）；
        //    参数1：目标动作
        //    参数2：目标回调函数
        CallFunc* funcall = CallFunc::create(CC_CALLBACK_0(Chat_Scene::FriendcallbackC, this));
        FiniteTimeAction * seq = Sequence::create(move,funcall,NULL);
        layer->runAction(seq);
    }
    if (layer2) {
        
        Button* btn=(Button*)this->getChildByTag(TAG_SHEJIAOBTN);
        MoveTo* move2 =MoveTo::create(0.1, Point(listBg->getContentSize().width-7*sx,btn->getPositionY()));
        btn->runAction(move2);
        
        
        MoveTo* move=MoveTo::create(0.1, Point(-layer2->getContentSize().width, layer2->getPositionY()));
        //    CCCallFunc
        //    作用：创建一个回调动作（调用不带参数的回调方法）；
        //    参数1：目标动作
        //    参数2：目标回调函数
        CallFunc* funcall = CallFunc::create(CC_CALLBACK_0(Chat_Scene::FriendcallbackC, this));
        FiniteTimeAction * seq = Sequence::create(move,funcall,NULL);
        layer2->runAction(seq);
    }
    
    if (!layer and !layer2) {
        this->SetChatLayer(1);
    }
    
}
/**
 ** 0代表世界聊天框
 ** 1代表好友聊天框
 **/
void Chat_Scene::SetChatLayer(int isSelect)
{
    //聊天框
    Node* chatLayer=NULL;
    int tagValue=0;
    if (isSelect) {
        chatLayer=FriendChatCont_Layer::create(chatFriendId);
        tagValue=TAG_FRIENDCHAT;
    }else
    {
        chatLayer=ChatContent_Layer::create(kChatChannel_World);
        tagValue=TAG_CHATCONTENT;
    }
    
    chatLayer->setAnchorPoint(Point::ZERO);
    log("VisibleRect::center().y======================%f",VisibleRect::center().y);
    log("chatLayer->getContentSize().heigh======================%f",chatLayer->getContentSize().height/2);
    chatLayer->setPosition(-chatLayer->getContentSize().width,VisibleRect::center().y-chatLayer->getContentSize().height/2);
    this->addChild(chatLayer,1,tagValue);
    
    Button* btn=(Button*)this->getChildByTag(TAG_SHEJIAOBTN);
    FiniteTimeAction* move=NULL;
    FiniteTimeAction* move2=NULL;
    btn->stopAllActions();
    move =MoveTo::create(0.2, Point(listBg->getContentSize().width-7*sx,chatLayer->getPositionY()));
    move2 =MoveTo::create(0.2, Point(listBg->getContentSize().width+chatLayer->getContentSize().width-9*sx,btn->getPositionY()));
    btn->runAction(move2->clone());
    chatLayer->runAction(move->clone());
}
void Chat_Scene::WorldCallBackC()
{
    Sprite* layer=(Sprite*)this->getChildByTag(TAG_FRIENDCHAT);
    if (layer) {
        this->removeChildByTag(TAG_FRIENDCHAT);
    }
    
    Sprite* layer2=(Sprite*)this->getChildByTag(TAG_CHATCONTENT);
    if (layer2) {
        this->removeChildByTag(TAG_CHATCONTENT);
    }
    
    this->SetChatLayer(0);
}
void Chat_Scene::FriendcallbackC()
{
    Sprite* layer=(Sprite*)this->getChildByTag(TAG_FRIENDCHAT);
    if (layer) {
        this->removeChildByTag(TAG_FRIENDCHAT);
    }
    
    Sprite* layer2=(Sprite*)this->getChildByTag(TAG_CHATCONTENT);
    if (layer2) {
        this->removeChildByTag(TAG_CHATCONTENT);
    }
    
    this->SetChatLayer(1);
}
void Chat_Scene::onAlterHeadCallBack(EventCustom* msg)
{
    __Integer* inter = (__Integer*)msg->getUserData();
    int heroId = inter->getValue();
    GlobalInfo::getInstance()->gameRole->headID=PublicShowUI::numberToString(heroId);
    
    DictHero* data=DictHeroManager::getInstance()->getData(heroId);
    if (data) {
//        GlobalInfo::getInstance()->gameRole->headID=data->resource;
        const char* imgPath = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH, data->headResource.c_str());
        headImg->setTexture(imgPath);
    }

}
void Chat_Scene::onSearchBtnClick(Ref* psender)
{
    if (!listBg) {
        return;
    }
    FindFriendList_Layer* searchLayer= (FindFriendList_Layer*)listBg->getChildByTag(TAG_LAYER);
    if (searchLayer and editbox) {
        string name = editbox->getText();
        searchLayer->requestFindFriendListMsg(name);
    }
}


void Chat_Scene::editBoxEditingDidBegin(EditBox* editBox)
{
    editBox->setText("");
}
void Chat_Scene::hideOtherLayer(int tag)
{
    Sprite* layer=(Sprite*)listBg->getChildByTag(TAG_LAYER);
    if (layer and listBg) {
        listBg->removeChildByTag(TAG_LAYER);
    }
    if (tag==TAG_SEARCHLAYER) {//查询好友页
        FindFriendList_Layer* searchLayer=FindFriendList_Layer::create();
        searchLayer->setPosition(0,15);
        listBg->addChild(searchLayer,2,TAG_LAYER);
    }else if (tag==TAG_MESSAGELAYER)//消息列表页面
    {
        MessageList_Layer* messageLayer=MessageList_Layer::create(1);
        messageLayer->setPosition(0,15);
        listBg->addChild(messageLayer,2,TAG_LAYER);
        
    }else if (tag==TAG_FRIENDLAYER)//好友列表页面
    {
        FriendList_Layer* frendLayer=FriendList_Layer::create(1);
        frendLayer->setPosition(0,15);
        listBg->addChild(frendLayer,2,TAG_LAYER);
    }else if (tag==TAG_APPLYLAYER)//好友申请页面
    {
        FriendApplyList_Layer* applyLayer=FriendApplyList_Layer::create(1);
        applyLayer->setPosition(0,15);
        listBg->addChild(applyLayer,2,TAG_LAYER);
    }
    /*FindFriendList_Layer* searchLayer=(FindFriendList_Layer*)listBg->getChildByTag(TAG_SEARCHLAYER);
    if (searchLayer) {
        searchLayer->setVisible(false);
    }
    MessageList_Layer* messageLayer=(MessageList_Layer*)listBg->getChildByTag(TAG_MESSAGELAYER);
    if (messageLayer) {
        messageLayer->setVisible(false);
    }
    FriendList_Layer* frendLayer=(FriendList_Layer*)listBg->getChildByTag(TAG_FRIENDLAYER);
    if (frendLayer) {
        frendLayer->setVisible(false);
    }
    FriendApplyList_Layer* applyLayer=(FriendApplyList_Layer*)listBg->getChildByTag(TAG_APPLYLAYER);
    if (applyLayer) {
        applyLayer->setVisible(false);
    }
    
    if (tag==TAG_SEARCHLAYER) {//查询好友页
        if (searchLayer) {
            searchLayer->setVisible(true);
        }else
        {
            searchLayer=FindFriendList_Layer::create();
            searchLayer->setPosition(0,15);
            listBg->addChild(searchLayer,2,TAG_SEARCHLAYER);
        }
    }else if (tag==TAG_MESSAGELAYER)//消息列表页面
    {
        if (messageLayer) {
            messageLayer->setVisible(true);
        }else
        {
            messageLayer=MessageList_Layer::create(1);
            messageLayer->setPosition(0,15);
            listBg->addChild(messageLayer,2,TAG_MESSAGELAYER);
        }
       
    }else if (tag==TAG_FRIENDLAYER)//好友列表页面
    {
        if (frendLayer) {
            frendLayer->setVisible(true);
        }else
        {
            frendLayer=FriendList_Layer::create(1);
            frendLayer->setPosition(0,15);
            listBg->addChild(frendLayer,2,TAG_FRIENDLAYER);
        }
    }else if (tag==TAG_APPLYLAYER)//好友申请页面
    {
        if (applyLayer) {
            applyLayer->setVisible(true);
        }else
        {
            applyLayer=FriendApplyList_Layer::create(1);
            applyLayer->setPosition(0,15);
            listBg->addChild(applyLayer,2,TAG_APPLYLAYER);
        }
    }*/
}
//
void Chat_Scene::onComboBoxBtnClick(Ref* psender)
{
    Node* sp=(Node*)psender;
    int tag=sp->getTag();
    this->hideOtherLayer(tag);
}

//------------------------后台交互部分--------------------------------//
void Chat_Scene::requestMyInfoMsg()
{
    FriendMyInfoMsg* msg = new FriendMyInfoMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void Chat_Scene::updateYaYaIdMsg(int yayaId)
{
    UpdateYaYaIdMsg* msg = new UpdateYaYaIdMsg(yayaId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void Chat_Scene::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_FRIEND_FriendMyInfoPageResp)
    {
        int yayaId=message->byteStream->getInt();
        int roleYaYaId=GlobalInfo::getInstance()->gameRole->yayaId;
        if (yayaId!=roleYaYaId && roleYaYaId > 0) {
            this->updateYaYaIdMsg(roleYaYaId);
        }
    }else if (message->messageID == SCENSE_CLIENT_FRIEND_FriendUpdateYaYaIdResp)
    {
        
    }
}

bool Chat_Scene::onTouchBegan(Touch *touch, Event *unused_event)
{
   
    return true;
}
void Chat_Scene::onTouchMoved(Touch *touch, Event *unused_event)
{
    
}
void Chat_Scene::onTouchEnded(Touch *touch, Event *unused_event)
{
    this->onSocialBtnClick();
}
void Chat_Scene::addEventListener()
{
    addUserMsg(CUSTOM_CHAT_MESSAGE_CLICK,CC_CALLBACK_1(Chat_Scene::onSelectMessageCallBack, this));
    addUserMsg(CUSTOM_CHAT_FRIEND_CLICK,CC_CALLBACK_1(Chat_Scene::onSelectFriendMessageCallBack, this));
    addUserMsg(CUSTOM_ALTER_HEAD,CC_CALLBACK_1(Chat_Scene::onAlterHeadCallBack, this));
    
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FRIEND_FriendUpdateYaYaIdResp).c_str(), CC_CALLBACK_1(Chat_Scene::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FRIEND_FriendMyInfoPageResp).c_str(), CC_CALLBACK_1(Chat_Scene::onMsgProcess, this));
}
void Chat_Scene::removeEventListener()
{
    BaseLayer::removeEventListener();
}