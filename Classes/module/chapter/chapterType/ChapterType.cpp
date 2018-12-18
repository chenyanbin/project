//
//  ChapterType.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/8/17.
//
//

#include "ChapterType.h"
#include "../../../common/ImagePath.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../VisibleRect.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../common/PublicShowUI.h"
#include "../ChapterLayer.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../commonData/data/FunctionOpenManager.h"
#include "../../../common/noticeManager/NoticeManager.h"
ChapterType::ChapterType()
:TAG_COMBOBTN(1)
,TAG_SELECTEFFECT(2)
{
    
}
ChapterType::~ChapterType()
{
//    CC_SAFE_RELEASE_NULL(m_selectedEffect);
}
bool ChapterType::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
//        m_selectedEffect = Sprite::create(IMG_CHAPTER_SELECTEFFECT);
//        m_selectedEffect->setAnchorPoint(Point::ZERO);
//        m_selectedEffect->retain();
        this->setBg();
        setComBoBtn();
        bref = true;
    } while (false);
    return bref;
}
void ChapterType::setBg()
{
//    Sprite* bg = Sprite::create(IMG_PUBLIC_COMBOBOX_BG);
//    bg->setAnchorPoint(Point::ZERO);
//    Size size = bg->getContentSize();
//    this->addChild(bg,0);
//    float sx = GlobalInfo::getInstance()->screenScaleX;
//    float sy = .4 * GlobalInfo::getInstance()->screenScaleX;
//    bg->setScale(sx, sy);
//    size.setSize(size.width * sx, size.height * sy);
//    this->setContentSize(size);
}

void ChapterType::setComBoBtn()
{
//    ArmatureDataManager::getInstance()->removeArmatureFileInfo(IMG_CHAPTER_BESTBTNEFFECT);
//    ArmatureDataManager::getInstance()->addArmatureFileInfo(IMG_CHAPTER_BESTBTNEFFECT);
//    ArmatureDataManager::getInstance()->removeArmatureFileInfo(IMG_CHAPTER_COMMONBTNEFFECT);
//    ArmatureDataManager::getInstance()->addArmatureFileInfo(IMG_CHAPTER_COMMONBTNEFFECT);
    
    ComboBoxBtn* comboBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_VERTICAL, 0, CC_CALLBACK_1( ChapterType::onBtnClick, this));
    comboBtn->setAnchorPoint(Point::ZERO);
//    comboBtn->addBtn(IMG_CHAPTER_BESTWORD, "","");
//    comboBtn->addBtn(IMG_CHAPTER_COMMONWORD, "","");
    comboBtn->addBtn(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE,IMG_PUBLIC_COMBOBOX_BTNCHOSE, IMG_CHAPTER_BESTWORD,true);
    comboBtn->addBtn(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE,IMG_PUBLIC_COMBOBOX_BTNCHOSE, IMG_CHAPTER_COMMONWORD,true);

    this->addChild(comboBtn,1,TAG_COMBOBTN);
    
    PublicShowUI::setTargetScale(comboBtn);
    this->setContentSize(comboBtn->getContentSize());
    if(GlobalInfo::getInstance()->stageMode == StageMode::kStageModeCommon)
    {
        comboBtn->selectedAt(1);
    }
    else if(GlobalInfo::getInstance()->stageMode == StageMode::kStageModeBest)
    {
        comboBtn->selectedAt(0);
    }
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumEliteTag, comboBtn->getButtonAt(0));

}
void ChapterType::onBtnClick(Ref* pSender)
{
//    ArmatureDataManager::getInstance()->removeArmatureFileInfo(IMG_CHAPTER_BESTBTNEFFECT);
//    ArmatureDataManager::getInstance()->addArmatureFileInfo(IMG_CHAPTER_BESTBTNEFFECT);
//    ArmatureDataManager::getInstance()->removeArmatureFileInfo(IMG_CHAPTER_COMMONBTNEFFECT);
//    ArmatureDataManager::getInstance()->addArmatureFileInfo(IMG_CHAPTER_COMMONBTNEFFECT);
    Button* btn = (Button*)pSender;
    Node* parent = btn->getParent();
    string str = GlobalInfo::getInstance()->stageMode == StageMode::kStageModeBest ? "jingyingdikuang" : "putongxuanzhongkuang";
//    Armature* armature = Armature::create(str);
//    if(parent && parent->getChildByTag(TAG_SELECTEFFECT))
//    {
//        parent->removeChildByTag(TAG_SELECTEFFECT);
//    }
//    
//    armature->setPosition(btn->getPositionX() + (btn->getContentSize().width)/2 + 11, btn->getPositionY() + (btn->getContentSize().height)/2 + 10);
//    parent->addChild(armature,-1,TAG_SELECTEFFECT);
//    armature->getAnimation()->playWithIndex(0);
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumEliteTag);
    if(btn->getTag() == 0)
    {
       
        if( GlobalInfo::getInstance()->stageMode == StageMode::kStageModeBest)
        {
            return;
        }
        
        if(FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumCampaignEliteChapter))
        {
        
            GlobalInfo::getInstance()->stageMode = StageMode::kStageModeBest;
        }
        else
        {
            GlobalInfo::getInstance()->stageMode = StageMode::kStageModeCommon;
            onMsgProcess(NULL);
            FunctionOpenManager::getInstance()->showNoOpenNotice();
            return;
        }
        
    }
    else if(btn->getTag() == 1)
    {
        if( GlobalInfo::getInstance()->stageMode == StageMode::kStageModeCommon)
        {
            return;
        }
        GlobalInfo::getInstance()->stageMode = StageMode::kStageModeCommon;
   
    }

    string str1 = GlobalInfo::getInstance()->stageMode == StageMode::kStageModeBest ? "jingyingdikuang" : "putongxuanzhongkuang";

//    if(str != str1)
//    {
//        parent->removeChildByTag(TAG_SELECTEFFECT);
//        
//        armature = Armature::create(str1);
//        
//        armature->setPosition(btn->getPositionX() + (btn->getContentSize().width)/2 + 11, btn->getPositionY() + (btn->getContentSize().height)/2 + 10);
//        parent->addChild(armature,-1,TAG_SELECTEFFECT);
//        armature->getAnimation()->playWithIndex(0);
//    }
    
    ChapterLayer::requestChapterByID();

}
void ChapterType::onMsgProcess(EventCustom* message)
{
    ComboBoxBtn* comboBtn = (ComboBoxBtn*)this->getChildByTag(TAG_COMBOBTN);
    if(GlobalInfo::getInstance()->stageMode == StageMode::kStageModeCommon)
    {
        comboBtn->selectedAt(1);
    }
    else if(GlobalInfo::getInstance()->stageMode == StageMode::kStageModeBest)
    {
        comboBtn->selectedAt(0);
    }
}
void ChapterType::onEnter()
{
    Layer::onEnter();
    _eventDispatcher->addCustomEventListener(CUSTOM_RESET_CHAPTER_TYPE, CC_CALLBACK_1(ChapterType::onMsgProcess, this));
 
}
void ChapterType::onExit()
{
    Layer::onExit();
     _eventDispatcher->removeCustomEventListeners(CUSTOM_RESET_CHAPTER_TYPE);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumEliteTag);
//    ArmatureDataManager::getInstance()->removeArmatureFileInfo(IMG_CHAPTER_BESTBTNEFFECT);
//    ArmatureDataManager::getInstance()->removeArmatureFileInfo(IMG_CHAPTER_COMMONBTNEFFECT);
}