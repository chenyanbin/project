//
//  GotoModule.cpp
//  FightPass
//
//  Created by 超 顾 on 15/9/11.
//
//

#include "GotoModule.h"
#include "../../commonData/GlobalInfo.h"
#include "../../commonData/enum/DictFunctionEnum.h"
#include "../../commonData/dictData/DictStageBattle/DictStageBattleManager.h"
#include "../lineup/LineupLayer.h"
#include "../chapter/ChapterLayer.h"
#include "../market/MarketLayer.h"
#include "../generals/generalsCard/GeneralsCard_Layer.h"
#include "../generals/generalsEquip/GeneralsEquip_Scene.h"
#include "../generals/Generals_Layer.h"
#include "../task/TaskLayer.h"
#include "../famousGeneral/GeneralScene.hpp"
#include "../task/signin/Signin_Scene.h"
#include "../setup/SetupLayer.h"
#include "../login/LoginLayer.h"
#include "../musou/MusouLayer.h"
#include "../arena/ArenaLayer.hpp"
#include "../../commonData/data/FunctionOpenManager.h"
#include "../dart/DartLayer.hpp"
void* GotoModule::param1 = NULL;
void* GotoModule::param2 = NULL;
void* GotoModule::param3 = NULL;
void GotoModule::gotoModuleByFunctionID(int functionID,int fromeModule)
{
    if(!FunctionOpenManager::getInstance()->functionIsOpened(functionID))
    {
        FunctionOpenManager::getInstance()->showNoOpenNotice(functionID);
        return;
    }
    switch (functionID)
    {
        case DictFunctionEnumLineup://阵容
            LineupLayer::show(fromeModule,1,0);
            break;
        case DictFunctionEnumCampaign://名战役
        {
            GlobalInfo::getInstance()->stageMode = StageMode::kStageModeCommon;
            if(param1 == NULL)
            {
                 ChapterLayer::requestChapterByID();
            }
            else
            {
                int stageID = ((__Integer*)param1)->getValue();
                if(stageID)
                {
                     ChapterLayer::requestStageBattle(stageID,GlobalInfo::getInstance()->stageMode);
                }
                else
                {
                      ChapterLayer::requestChapterByID(0);
                }
              
                param1 = NULL;
            }
        }
        break;
        case DictFunctionEnumCampaignElite://精英关卡
            GlobalInfo::getInstance()->stageMode = StageMode::kStageModeBest;
            if(param1 == NULL)
            {
                ChapterLayer::requestChapterByID();
            }
            else
            {
                int stageID = ((__Integer*)param1)->getValue();
                if(stageID)
                {
                    ChapterLayer::requestStageBattle(stageID,GlobalInfo::getInstance()->stageMode);
                }
                else
                {
                    ChapterLayer::requestChapterByID(0);
                }
             
                param1 = NULL;
            }
            break;
        case DictFunctionEnumCampaignChapter://名战役章节
        {
            GlobalInfo::getInstance()->stageMode = StageMode::kStageModeCommon;
            if(param1)
            {
                int chapterID = ((__Integer*)param1)->getValue();
                ChapterLayer::requestChapterByID(chapterID);
            }
            else
            {
                ChapterLayer::requestChapterByID();
            }
            param1 = NULL;
            
        }
            break;
        case DictFunctionEnumCampaignStage:
        {
            DictStageBattle* stageBattle = NULL;
            GlobalInfo::getInstance()->stageMode = StageMode::kStageModeCommon;
            if(param1)
            {
                int stageBattleID = ((__Integer*)param1)->getValue();
                stageBattle = DictStageBattleManager::getInstance()->getData(stageBattleID);
            }
            if(stageBattle)
            {
                ChapterLayer::requestChapterByID(stageBattle->inChapterId);
            }
            else
            {
                 ChapterLayer::requestChapterByID();
            }
            param1 = NULL;
            
        }
        break;
        case DictFunctionEnumCampaignEliteChapter:
        {
            GlobalInfo::getInstance()->stageMode = StageMode::kStageModeBest;
            if(param1)
            {
                int chapterid = ((__Integer*)param1)->getValue();
                ChapterLayer::requestChapterByID(chapterid);
            }
            else
            {
                 ChapterLayer::requestChapterByID();
            }
            param1 = NULL;
           
        }
            break;
        case DictFunctionEnumCampaignEliteStage:
        {
            GlobalInfo::getInstance()->stageMode = StageMode::kStageModeBest;
            DictStageBattle* stageBattle = NULL;
            if(param1)
            {
                int stageBattleID = ((__Integer*)param1)->getValue();
                stageBattle = DictStageBattleManager::getInstance()->getData(stageBattleID);
            }
            if(stageBattle)
            {
                GlobalInfo::getInstance()->taskInStageBattle = stageBattle->inStageId;
                ChapterLayer::requestChapterByID(stageBattle->inChapterId);
            }
            else
            {
                ChapterLayer::requestChapterByID();
            }
            param1 = NULL;
        }
            break;
        case DictFunctionEnumLead://举贤
            MarketLayer::show(fromeModule,MarketLayer::TAG_XUNFANG);
            break;
        case DictFunctionEnumFind://寻访
            MarketLayer::show(fromeModule,MarketLayer::TAG_JUXIAN);
            break;
        case DictFunctionEnumShopping://商店
            MarketLayer::show(fromeModule,MarketLayer::TAG_SHANGDIAN);
            break;
        case DictFunctionEnumBlackShop://黑市
            MarketLayer::show(fromeModule,MarketLayer::TAG_BLACKSHOP);
            break;
        case DictFunctionEnumMarket://拍卖
            MarketLayer::show(fromeModule,MarketLayer::TAG_PAIMAI);
            break;
        case DictFunctionEnumHeroPrestige://历炼

            GeneralsCard_Layer::show(fromeModule, DictFunctionEnumHeroPrestige);
            break;
        case DictFunctionEnumHeroQuality://觉醒
             GeneralsCard_Layer::show(fromeModule, DictFunctionEnumEquip);
            break;
        case DictFunctionEnumEquipHarden://强化

             GeneralsEquip_Scene::show(SCENE_TAG_GENERALS_EQUIP, LAYER_EQUIP_STRONG);
            break;
        case DictFunctionEnumEquipForge://熔炼
            GeneralsEquip_Scene::show(SCENE_TAG_GENERALS_EQUIP, LAYER_EQUIP_SMELT);
            break;
        case DictFunctionEnumHero://所属武将
//            Generals_Layer::show(fromeModule,Generals_Layer::PAGE_TAG_GENERAL);
            GeneralsCard_Layer::show(SCENE_TAG_MAINUI, DictFunctionEnumEquip);
            break;
        case DictFunctionEnumEquip://装备
            Generals_Layer::show(fromeModule,Generals_Layer::PAGE_TAG_EQUIP);
            break;
        case DictFunctionEnumHeroProp://武将属性
            GeneralsCard_Layer::show(fromeModule, DictFunctionEnumHeroProp);
            break;
        case DictFunctionEnumMater://所属材料
             Generals_Layer::show(fromeModule,Generals_Layer::PAGE_TAG_MATERIAL);
            break;
        case DictFunctionEnumBook://书信
            Generals_Layer::show(fromeModule,Generals_Layer::PAGE_TAG_LETTER);
            break;
        case DictFunctionEnumTaskCommon:
            TaskLayer::show(fromeModule, TaskLayer::TAG_PUTONG);
            break;
        case DictFunctionEnumTaskDaily:
             TaskLayer::show(fromeModule, TaskLayer::TAG_RICHANG);
            break;
        case DictFunctionEnumSign://签到
             Signin_Scene::show(fromeModule,Signin_Scene::TAG_EVERYDAY);
            break;
        case DictFunctionEnumSetting:
            SetupLayer::show();
            break;
        case DictFunctionEnumTheMainCity:
             LoginLayer::enterMainUI();
            break;
        case DictFunctionEnumMusou:
        
            MusouLayer::requestMuouList();
            break;
        case DictFunctionEnumLegend://名将传
             GeneralScene::show(SCENE_TAG_MAINUI);
            break;
        case DictFunctionEnumArena:
             ArenaLayer::show(ArenaLayer::PAGE_ARENALIST);
            break;
        case DictFunctionEnumGemstoneMine:
            DartLayer::show();
            break;
       
        default:
            break;
    }
}