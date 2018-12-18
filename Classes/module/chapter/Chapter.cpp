//
//  Chapter.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/8/8.
//
//

#include "Chapter.h"
#include "../../common/PublicShowUI.h"
#include "../../common/ImagePath.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "../../common/commonEffect/CommonEffect.h"
#include "../../protocol/UserCustomEvent.h"
#include "../battle/action/CameraIn.h"
#include "../battle/BattleLoader.h"
#include "../../commonData/dictData/DictChapterStarReward/DictChapterStarRewardManager.h"
#include "../../avatar/monster/Monster.h"
#include "../../common/GraySprite/GraySprite.h"
#include "../newPlayerGuide/NewPlayerGuild.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../message/Decoding/stage/RequestChapterBoxMsg.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "ChapterLayer.h"
#include "../../commonData/dictData/DictTips/DictTipsManager.h"
Chapter::Chapter()
:_chapter(NULL)
,_background(NULL)
,_frontLayer(NULL)
,_skyLayer(NULL)
,_buildLayer(NULL)
,_stageLayer(NULL)
,stageList(NULL)
,stageStarMap(NULL)
,stageBoxList(NULL)

,TAG_STAR_PROGRESS(1)
,TAG_ARROW(2)
,m_nextStage(0)
,starCountMax(0)
,curStarCount(0)
{
    stageList = new Vector<DictStage*>();
    stageStarMap = new Map<int,StageStarData*>();
    stageBoxList = new Vector<StageBoxData*>();
}
Chapter::~Chapter()
{
    CC_SAFE_RELEASE_NULL(_chapter);
    _background = NULL;
    _frontLayer = NULL;
    _skyLayer   = NULL;
    _stageLayer = NULL;
    _buildLayer = NULL;
    stageList->clear();
    CC_SAFE_DELETE(stageList);
    stageList = NULL;
    stageStarMap->clear();
    CC_SAFE_DELETE(stageStarMap);
    stageStarMap = NULL;
    stageBoxList->clear();
    CC_SAFE_DELETE(stageBoxList);
    stageBoxList = NULL;
    
}
bool Chapter::init(int chapterID,ByteStream* bytestream)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        parseBytestream(bytestream);
        DictChapter* chapter = DictChapterManager::getInstance()->getData(chapterID);
        this->setChapter(chapter);
        setBg();

        bref = true;
    } while (false);
    return bref;
}
Chapter* Chapter::create(int chapterID,ByteStream* bytestream)
{
    Chapter* chapter = new Chapter();
    if(chapter && chapter->init(chapterID,bytestream))
    {
        chapter->autorelease();
        return chapter;
    }
    CC_SAFE_DELETE(chapter);
    chapter = NULL;
    return NULL;
}
void Chapter::parseBytestream(ByteStream* bytestream)
{
    if(!bytestream)
    {
        return;
    }
    stageBoxList->clear();
    stageStarMap->clear();
    m_nextStage =  bytestream->getInt();
    starCountMax = bytestream->getShort();
    curStarCount = bytestream->getShort();
    
    int len = bytestream->get();
    for(int i = 0; i < len; i++)
    {
        StageStarData* starData = new StageStarData();
        starData->autorelease();
        
        starData->_stageID = bytestream->getInt();
        starData->state = bytestream->get();
        starData->star  = bytestream->getShort();
        int starCountSize = bytestream->get();
     
        for(int j = 0; j < starCountSize; j++)
        {
            int starCount = bytestream->get();
           
            starData->starList->push_back(starCount);
        }
        stageStarMap->insert(starData->_stageID, starData);
     
    }
    len = bytestream->getByte();
    StageBoxData* boxData = NULL;
    for(int i =0; i < len; i++)
    {
        boxData = new StageBoxData();
        boxData->autorelease();
        boxData->_boxID = bytestream->getInt();
        boxData->_state = bytestream->get();
        boxData->requireStarCount = bytestream->get();
        stageBoxList->pushBack(boxData);
    }
}
void Chapter::updateChapterStar(ByteStream* bytestream)
{
    Sprite* progressBg = (Sprite*)this->getChildByTag(TAG_STAR_PROGRESS);
    int len = stageBoxList->size();
    StageBoxData* data = NULL;
    for(int i = 0; i < len; i++)
    {
        data = stageBoxList->at(i);
        progressBg->removeChildByTag(data->_boxID);
    }

    len = bytestream->get();
    for(int i =0; i < len; i++)
    {
        data = stageBoxList->at(i);
        data->_boxID = bytestream->getInt();
        data->_state = bytestream->get();
        data->requireStarCount = bytestream->get();
    }
    setProgress();
}
void Chapter::initStageList()
{
    ChapterLayer* chapterLayer =  (ChapterLayer*)Director::getInstance()->getRunningScene()->getChildByTag(SCENE_TAG_CHAPTER);
    chapterLayer->noLastStage();
    stageList->clear();
    Vector<DictStage*>* list = DictStageManager::getInstance()->getDataList();
    for(DictStage* stage : *list)
    {
        if(stage->inChaperId == this->getChapter()->id)
        {
            stageList->pushBack(stage);
            setStageNameBtn(stage);
        }
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    Vector<DictStageBuilding*>* _builds = DictStageBuildingManager::getInstance()->getDataList();
    for(DictStageBuilding* build : *_builds)
    {
        if(build->inChaperId == this->getChapter()->id)
        {
            setStageBuild(build);
        }
    }
    CC_SAFE_DELETE(_builds);
    _builds = NULL;
}

void Chapter::setBg()
{
    
    const char* path = PublicShowUI::getResImgPath(IMG_CHAPTER_BGPATHJPG, _chapter->resourceBg.c_str());
    _background = Sprite::create(path);
    float scaleY = GlobalInfo::getInstance()->getMapScaleValue() * GlobalInfo::getInstance()->screenScaleY;

    float scaleX = GlobalInfo::getInstance()->screenScaleX;
    _background->setScale(scaleX,scaleY);
    _background->setAnchorPoint(Point::ZERO);
    this->addChild(_background,0);
    
    Size size = _background->getContentSize();
    size.width = size.width * scaleX;
    size.height = size.height * scaleY;
    _background->setContentSize(size);
    this->setContentSize(size);
    _buildLayer = Sprite::create();
    _buildLayer->setAnchorPoint(Point::ZERO);
    _buildLayer->setPosition(Point::ZERO);
    this->addChild(_buildLayer,1);
    
  
    
    path = PublicShowUI::getResImgPath(IMG_CHAPTER_BGPATH, _chapter->resourceSky.c_str());
    _skyLayer = Sprite::create(path);
    if(_skyLayer)
    {
        _skyLayer->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(_skyLayer);
        this->addChild(_skyLayer,2);
        _skyLayer->setPositionY(this->getContentSize().height - _skyLayer->getContentSize().height);
    }
   
    
    _stageLayer = Sprite::create();
    _stageLayer->setAnchorPoint(Point::ZERO);
    this->addChild(_stageLayer,3);
    
    path = PublicShowUI::getResImgPath(IMG_CHAPTER_BGPATH, _chapter->resourceFront.c_str());
    _frontLayer = Sprite::create(path);
    if(_frontLayer)
    {
        _frontLayer->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(_frontLayer);
        this->addChild(_frontLayer,4);
    }
   
    
    
}
void Chapter::setStageBuild(DictStageBuilding* build)
{
    const char* path = PublicShowUI::getResImgPath(IMG_CHAPTER_BGPATH, build->resource.c_str());
    Sprite* spr = Sprite::create(path);
    spr->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(spr);
    float sx = GlobalInfo::getInstance()->screenScaleX;
    float scaleY = GlobalInfo::getInstance()->getMapScaleValue() * sx;
    spr->setScale(sx, scaleY);
    _buildLayer->addChild(spr,build->axisZ);
    
    spr->setPosition(build->axisX * sx, build->axisY * sx);
    
    MoveBy* moveby = MoveBy::create(2, Point(5,5));
    spr->runAction(RepeatForever::create(Sequence::create(moveby,moveby->reverse(),NULL)));

}
void Chapter::setStageNameBtn(DictStage* stage)
{
    StageStarData* starData = stageStarMap->at(stage->id);
    if(!starData)
    {
        return;
    }
    ChapterLayer* chapterLayer =  (ChapterLayer*)Director::getInstance()->getRunningScene()->getChildByTag(SCENE_TAG_CHAPTER);
    MenuItemLabel* nameBtn = NULL;
    Sprite* nameBg = Sprite::create(IMG_CHAPTER_STAGENAMEBG);
    nameBg->setAnchorPoint(Point(.5,.5));
  
    if(starData->state == 1)
    {//通过
        nameBtn = MenuItemLabel::create(nameBg,CC_CALLBACK_1(Chapter::onStageClick, this));
    }
    else if(starData->state == 2)
    {//可进入
        nameBtn = MenuItemLabel::create(nameBg, CC_CALLBACK_1(Chapter::onStageClick, this));
        
        chapterLayer->onLastStage(this->getChapter()->id);
    }
    else if(starData->state == 3)
    {
        nameBtn = MenuItemLabel::create(nameBg, CC_CALLBACK_1(Chapter::onStageClick, this));
        
        chapterLayer->onLastStage(this->getChapter()->id);
        nameBtn->setEnabled(false);
        nameBtn->setOpacity(180);
    }
   
    
    if(starData->_stageID == m_nextStage)
    {
        Sprite* arrow = NULL;
        if(stage->id == GlobalInfo::getInstance()->taskInStageBattle && GlobalInfo::getInstance()->taskInStageBattle != 0)
        {
            arrow = Sprite::create(IMG_PUBLIC_TASK_TARGET);
        }
        else
        {
            arrow = Sprite::create(IMG_PUBLIC_DOWNARROW);
        }
        arrow->setAnchorPoint(Point(.5,0));
        arrow->setPosition(30, nameBtn->getContentSize().height);
        nameBtn->addChild(arrow,4,TAG_ARROW);
        MoveBy * moveTo = MoveBy::create(.5,Point(0,50));
        arrow->runAction(RepeatForever::create(Sequence::create(moveTo,moveTo->reverse(),NULL)));
        
        ArmatureDataManager::getInstance()->removeArmatureFileInfo(IMG_CHAPTER_STAGEFORM);
        ArmatureDataManager::getInstance()->addArmatureFileInfo(IMG_CHAPTER_STAGEFORM);
        Armature* form = Armature::create("guankadituxuanzhong");
//        Sprite* form = Sprite::create(IMG_CHAPTER_STAGEFORM);
     
        form->setAnchorPoint(Point::ZERO);
        form->setPosition((nameBtn->getContentSize().width - form->getContentSize().width)/2,-1);
        nameBtn->addChild(form,-1);
        form->getAnimation()->playWithIndex(0);
//        FadeIn* fadeIn = FadeIn::create(1);
//        FadeOut* fadeOut = FadeOut::create(1);
//        RepeatForever* action = RepeatForever::create(Sequence::create(fadeOut,fadeIn, NULL));
//        form->runAction(action);
    }
    else if(stage->id == GlobalInfo::getInstance()->taskInStageBattle && GlobalInfo::getInstance()->taskInStageBattle != 0)
    {
        Sprite* arrow = Sprite::create(IMG_PUBLIC_TASK_TARGET);
        arrow->setAnchorPoint(Point(.5,0));
        arrow->setScale(.7);
        arrow->setPosition(20, nameBtn->getContentSize().height);
        nameBtn->addChild(arrow);
        
        MoveBy * moveTo = MoveBy::create(.5,Point(0,50));
        arrow->runAction(RepeatForever::create(Sequence::create(moveTo,moveTo->reverse(),NULL)));
    }
    else if(starData->state == 3)
    {//不可进入
        chapterLayer->onLastStage(this->getChapter()->id);
        return;
        nameBtn = MenuItemLabel::create(nameBg);
    }
    
    
    nameBtn->setAnchorPoint(Point(.5,.5));
    Label* number = PublicShowUI::getLabel(stage->showNumber.c_str(),Color3B::WHITE,17,false,false);
    number->setAnchorPoint(Point::ZERO);
    nameBtn->addChild(number,15);
    number->setPosition((nameBtn->getContentSize().width - number->getContentSize().width) /2, nameBtn->getContentSize().height - number->getContentSize().height - 10);
    
    Label* nameLabel = PublicShowUI::getLabel(stage->name.c_str(),Color3B::WHITE,17,false,false);
    nameLabel->setAnchorPoint(Point(0,0));
    nameBtn->addChild(nameLabel,16);
    nameLabel->setMaxLineWidth(25);
    nameLabel->setPosition(15, (nameBtn->getContentSize().height - nameLabel->getContentSize().height)/2 + 10);
    
    Sprite* starBg = Sprite::create();
    starBg->setAnchorPoint(Point::ZERO);
    Sprite* star = NULL;
    ssize_t len = starData->starList->size();
    for(int i = 0; i < len; i++)
    {
        if(starData->starList->at(i) == 0)
        {
            break;
        }
        star = Sprite::create(IMG_PUBLIC_STAR);
        star->setAnchorPoint(Point::ZERO);
        star->setScale(.5);
        Label* label = PublicShowUI::getLabel(PublicShowUI::numberToString(starData->starList->at(i)).c_str(),Color3B::BLACK,30,false,false);
        label->setPosition(star->getContentSize().width/2, star->getContentSize().height/2);
        star->addChild(label);
        
        star->setPosition(0, (len - 1 -i) * 25);
        starBg->addChild(star,i,i);
        
    }
    if(star)
    {
        star = (Sprite*)starBg->getChildByTag(0);
        Size size = star->getContentSize();
        size.width *= .5;
        size.height = star->getPositionY() + size.height * .5;
        starBg->setContentSize(size);
        starBg->setPosition(nameBtn->getContentSize().width/2 + 4, (nameBtn->getContentSize().height - starBg->getContentSize().height)/2);
        nameBtn->addChild(starBg,3);
    }
    
    if(stage->id == 1)
    {
        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumLunhuixiaojing, nameBtn);
    }
    else if(stage->id == 2)
    {
        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumMingyunzhilin, nameBtn);
    }
    else if(stage->id == 3)
    {
        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumChangshengjiangjun, nameBtn);
    }
    else if(stage->id == 4)
    {
        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumQixidiying, nameBtn);
    }
    Menu* menu = Menu::create();
    menu->setAnchorPoint(Point::ZERO);
  
    nameBtn->setPosition(stage->axisX + nameBtn->getContentSize().width/2, stage->axisY + nameBtn->getContentSize().height/2);
    menu->addChild(nameBtn,1,stage->id);
    PublicShowUI::setTargetScale(menu);
    menu->setPosition(0,0);
    _stageLayer->addChild(menu,1);
    
}
void Chapter::onStageClick(Ref* pSender)
{
    Dialog::showServerLoading(.5);
    MenuItemLabel* btn = (MenuItemLabel*)pSender;
    int stageID = btn->getTag();
    if(stageID == GlobalInfo::getInstance()->taskInStageBattle)
    {
        GlobalInfo::getInstance()->taskInStageBattle = 0;
    }
     NewPlayerGuild::getInstance()->next();
    ChapterLayer::requestStageBattle(stageID,GlobalInfo::getInstance()->stageMode);
    
}
void Chapter::onEnterStageBattle(EventCustom* msg)
{
    
    ChapterLayer* chapterLayer =  (ChapterLayer*)Director::getInstance()->getRunningScene()->getChildByTag(SCENE_TAG_CHAPTER);
    if(chapterLayer->_cloundArmature)
    {
        chapterLayer->setClickEnabled(false);
        chapterLayer->_cloundArmature->setVisible(true);
        chapterLayer->_cloundArmature->getAnimation()->playWithIndex(0);
    }

    
    ByteStream* byteStream = (ByteStream*)msg->getUserData();
    int len = byteStream->length();
    uint8_t* buf = new uint8_t[len];
    memcpy(buf, byteStream->getBuf(), len);
    ByteStream* _byteStream = new ByteStream(buf,len,true);
    _byteStream->setPosition(byteStream->_count);
    _stageLayer->removeFromParent();
    Vector<Node*> children = _buildLayer->getChildren();
    for(Node* node : children)
    {
        MoveBy* moveBy = NULL;
        if(node->getPositionX() < 500)
        {
            moveBy = MoveBy::create(1, Point(-150,0));
        }
        else
        {
            moveBy = MoveBy::create(1, Point(150,0));
        }
        node->runAction(moveBy);
        CameraIn* cameraIn = CameraIn::create(1, 200);
        this->runAction(cameraIn);
    }
    
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(Chapter::enterBattle, this,_byteStream));
    DelayTime* delay = DelayTime::create(.9);
    this->runAction(Sequence::create(delay,callBack, NULL));
  
}
void Chapter::enterBattle(ByteStream* byteStream)
{
     BattleLoader::show(byteStream, SCENE_TAG_CHAPTER);
    CC_SAFE_DELETE(byteStream);
}
void Chapter::setBoss()
{
    DictMonster* dictMonster = DictMonsterManager::getInstance()->getData(_chapter->bossId);
    if(dictMonster)
    {
        string path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictMonster->resource.c_str());
        ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
        ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(Chapter::onBossLoaded));
    }
  
}
void Chapter::onBossLoaded(float percent)
{
    if(percent < 1)
    {
        return;
    }
    Monster* monster = Monster::create(_chapter->bossId);
    monster->onEnterScene();
    monster->setDirection(Point(-1,0));
    PublicShowUI::setTargetScale(monster);
    monster->setPosition(_background->getContentSize().width-monster->getContentSize().width/2 ,50 * GlobalInfo::getInstance()->screenScaleX);//300 * GlobalInfo::getInstance()->screenScaleX - monster->getContentSize().height
    this->addChild(monster,5);
  

}
void Chapter::setProgress()
{
    if(this->getChildByTag(TAG_STAR_PROGRESS))
    {
        this->removeChildByTag(TAG_STAR_PROGRESS);
    }
    Sprite* progressBg = Sprite::create(IMG_CHAPTER_STARPROGRESSBG);
    
    progressBg->setAnchorPoint(Point::ZERO);
    this->addChild(progressBg,6,TAG_STAR_PROGRESS);
    Sprite* progress = Sprite::create(IMG_CHAPTER_STARPROGRESS);
    progress->setAnchorPoint(Point::ZERO);
    ProgressTimer* progressTimer = ProgressTimer::create(progress);
    progressTimer->setType(ProgressTimer::Type::BAR);
    progressTimer->setMidpoint(Point(0,1));
    progressTimer->setBarChangeRate(Point(1,0));
    progressTimer->setAnchorPoint(Point(0 ,0));
    progressBg->addChild(progressTimer,1,TAG_STAR_PROGRESS);
    progressTimer->setPosition(34, 34);

    float percent = curStarCount /starCountMax * 100 ;
    progressTimer->setPercentage(percent);
    
    setStarBox();
    setStarLevel();
    PublicShowUI::setTargetScale(progressBg);
    progressBg->setPositionX(VisibleRect::getVisibleRect().size.width  - progressBg->getContentSize().width);

}

void Chapter::setStarBox()
{
    Sprite* progressBg = (Sprite*)this->getChildByTag(TAG_STAR_PROGRESS);
    int len = stageBoxList->size();
    StageBoxData* data = NULL;
    Sprite* star = NULL;
    TouchSprite* box = NULL;
    Label* label = NULL;
    string str  = "";
    for(int i = 0 ;i < len; i++)
    {
        data = stageBoxList->at(i);
        if(data->_state == StageBoxData::BOX_STATE_OPENED)
        {
            box = TouchSprite::createWithPic(IMG_PUBLIC_BOXOPEN, this, callfuncN_selector(Chapter::onRequestChapterStar));
        }
        else if(data->_state == StageBoxData::BOX_STATE_NOOPEN)
        {
            box = TouchSprite::createWithPic(IMG_PUBLIC_BOXCLOSE, this, callfuncN_selector(Chapter::onRequestChapterStar));
        }
        else if(data->_state == StageBoxData::BOX_STATE_ABLED)
        {
            box = TouchSprite::createWithPic(IMG_PUBLIC_BOXCLOSE, this, callfuncN_selector(Chapter::onRequestChapterStar));
            PublicShowUI::setTargetSwing(box);
        }
        else
        {
            continue;
        }

        box->setScale(.5);
        box->setContentSize(box->getContentSize() * .5);
        box->setAnchorPoint(Point(.5,.5));
        box->setPosition(80 + ( i * 130), 100);
        progressBg->addChild(box,8,i);

        star = Sprite::create(IMG_PUBLIC_STAR);
        box->addChild(star);
        str = "X" + PublicShowUI::numberToString(data->requireStarCount);
        label = PublicShowUI::getLabel(str.c_str(),Color3B::WHITE,25,false,false);
        label->setAnchorPoint(Point::ZERO);
        star->addChild(label);
        label->setPosition(star->getContentSize().width, 0);
        star->setPosition(box->getContentSize().width/2, 0);
    }
}
void Chapter::onRequestChapterStar(Node* pSender)
{
    StageBoxData* data = stageBoxList->at(pSender->getTag());
    if(data->_state == StageBoxData::BOX_STATE_OPENED)
    {
        NoticeManager::getInstance()->showNotice("宝箱已经领取了哦。亲！");
        return;
    }
    else if(data->_state == StageBoxData::BOX_STATE_NOOPEN)
    {
        DictTips* data = DictTipsManager::getInstance()->getData(6001011);
        if (data) {
            string str = data->desc;
//            string oldStr = "#%d#";
//            int arr[3] = {gold,power,count};
//            for(int i=1; i<=3;i ++)
//            {
//                oldStr = StringUtils::format("#%d#",i);
//                str = StringUtil::replace(str, oldStr, StringUtils::format("%d",arr[i-1]));
//            }
//            str = StringUtil::replace(str, "<br>", "\n    ");

         NoticeManager::getInstance()->showNotice(str.c_str());
        }
        return;
    }
    Dialog::showServerLoading(3);
    CommonEffect* commonEffect = CommonEffect::create("baoxiangdonghua",false,true,CC_CALLBACK_0(Chapter::onEffectFinised, this,data->_boxID));
    commonEffect->setAnchorPoint(Point(0.5,0.5));
    PublicShowUI::setTargetScale(commonEffect);
    commonEffect->setPosition((this->getContentSize().width)/2,(this->getContentSize().height)/2);
    this->addChild(commonEffect,100);
    
}
void Chapter::onEffectFinised(int boxid)
{
    RequestChapterBoxMsg* msg = new RequestChapterBoxMsg(boxid);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void Chapter::setStarLevel()//设置星
{
    Sprite* progressBg = (Sprite*)this->getChildByTag(TAG_STAR_PROGRESS);
    
    Node* node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    string str =  PublicShowUI::numberToString(curStarCount);
    str += "/" + PublicShowUI::numberToString(starCountMax);
    Label* label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),24,false,false);
    label->setAnchorPoint(Point::ZERO);
    label->setPosition(Point::ZERO);
    node->addChild(label);
    
    Sprite* starSpr = Sprite::create(IMG_PUBLIC_STAR);
    starSpr->setAnchorPoint(Point::ZERO);
    starSpr->setPosition(label->getContentSize().width, (label->getContentSize().height - starSpr->getContentSize().height)/2);
    node->addChild(starSpr);
    Size size = starSpr->getContentSize();
    size.width = starSpr->getPositionX() + starSpr->getContentSize().width;
    node->setContentSize(size);
    
    node->setPosition(progressBg->getContentSize().width - node->getContentSize().width - 10, (progressBg->getContentSize().height -node->getContentSize().height)/2 - 5);
    progressBg->addChild(node);
}
void Chapter::clear()
{
    _eventDispatcher->removeCustomEventListeners(CUSTOM_ENTER_BATTLE);
    
    DictMonster* dictMonster = DictMonsterManager::getInstance()->getData(_chapter->bossId);
    if(dictMonster)
    {
        string path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH,dictMonster->resource.c_str());
        ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
    }
   
   
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
//    ArmatureDataManager::getInstance()->removeArmatureFileInfo("");
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumLunhuixiaojing);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumChangshengjiangjun);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumMingyunzhilin);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumQixidiying);
    
}
void Chapter::onEnter()
{
    Layer::onEnter();
    initStageList();
    _eventDispatcher->addCustomEventListener(CUSTOM_ENTER_BATTLE, CC_CALLBACK_1(Chapter::onEnterStageBattle, this));
    setProgress();
    setBoss();
    
    
}
void Chapter::onExit()
{
    Layer::onExit();
    
   
}