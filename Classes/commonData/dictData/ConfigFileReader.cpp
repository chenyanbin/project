#include "ConfigFileReader.h"
#include "editor-support/spine/Json.h"
#include "DictHeroPropLevel/DictHeroPropLevelManager.h"
#include "DictHeroPropPrestige/DictHeroPropPrestigeManager.h"
#include "DictMonsterPropLevel/DictMonsterPropLevelManager.h"
#include "DictRoleLevel/DictRoleLevelManager.h"
#include "DictRandomName/DictRandomNameManager.h"
#include "DictGlobalFormula/DictGlobalFormulaManager.h"
#include "DictBattleReborn/DictBattleRebornManager.h"
#include "DictBattleRebornCost/DictBattleRebornCostManager.h"
#include "DictBattlePotion/DictBattlePotionManager.h"
#include "DictBattlePotionCost/DictBattlePotionCostManager.h"
#include "DictWay/DictWayManager.h"
#include "DictHero/DictHeroManager.h"
#include "DictHeroLevel/DictHeroLevelManager.h"
#include "DictHeroPrestige/DictHeroPrestigeManager.h"
#include "DictHeroQuality/DictHeroQualityManager.h"
#include "DictHeroEquip/DictHeroEquipManager.h"
#include "DictHeroLineupKarma/DictHeroLineupKarmaManager.h"
#include "DictHeroPrestigeUpCost/DictHeroPrestigeUpCostManager.h"
#include "DictHeroQualityUp/DictHeroQualityUpManager.h"
#include "DictHeroQualityUpCost/DictHeroQualityUpCostManager.h"
#include "DictMonster/DictMonsterManager.h"
#include "DictNPC/DictNPCManager.h"
#include "DictSkill/DictSkillManager.h"
#include "DictBuff/DictBuffManager.h"
#include "DictSkillKarma/DictSkillKarmaManager.h"
#include "DictItem/DictItemManager.h"
#include "DictItemHero/DictItemHeroManager.h"
#include "DictItemEquip/DictItemEquipManager.h"
#include "DictItemBook/DictItemBookManager.h"
#include "DictItemMater/DictItemMaterManager.h"
#include "DictResource/DictResourceManager.h"
#include "DictEquipForge/DictEquipForgeManager.h"
#include "DictEquipForgeCost/DictEquipForgeCostManager.h"
#include "DictEquipCompose/DictEquipComposeManager.h"
#include "DictEquipHardenLevel/DictEquipHardenLevelManager.h"
#include "DictEquipHardenFightProp/DictEquipHardenFightPropManager.h"
#include "DictEquipHardenCost/DictEquipHardenCostManager.h"
#include "DictItemQuality/DictItemQualityManager.h"
#include "DictBookCost/DictBookCostManager.h"
#include "DictBookUpper/DictBookUpperManager.h"
#include "DictItemUseReward/DictItemUseRewardManager.h"
#include "DictTaskCommonType/DictTaskCommonTypeManager.h"
#include "DictTaskCommonTypeMsg/DictTaskCommonTypeMsgManager.h"
#include "DictTaskCommon/DictTaskCommonManager.h"
#include "DictTaskCommonReward/DictTaskCommonRewardManager.h"
#include "DictTaskDayType/DictTaskDayTypeManager.h"
#include "DictTaskDay/DictTaskDayManager.h"
#include "DictTaskDayTypeMsg/DictTaskDayTypeMsgManager.h"
#include "DictTaskDayProgressReward/DictTaskDayProgressRewardManager.h"
#include "DictTaskDayReward/DictTaskDayRewardManager.h"
#include "DictTaskWanted/DictTaskWantedManager.h"
#include "DictTaskWantedProgressReward/DictTaskWantedProgressRewardManager.h"
#include "DictTaskWantedReward/DictTaskWantedRewardManager.h"
#include "DictFindCost/DictFindCostManager.h"
#include "DictFindReward/DictFindRewardManager.h"
#include "DictFindLootWeight/DictFindLootWeightManager.h"
#include "DictFindOpenCost/DictFindOpenCostManager.h"
#include "DictLeadCost/DictLeadCostManager.h"
#include "DictLeadReward/DictLeadRewardManager.h"
#include "DictLeadLootWeight/DictLeadLootWeightManager.h"
#include "DictShopping/DictShoppingManager.h"
#include "DictShoppingVipTimes/DictShoppingVipTimesManager.h"
#include "DictMarket/DictMarketManager.h"
#include "DictChapter/DictChapterManager.h"
#include "DictStage/DictStageManager.h"
#include "DictStageBattle/DictStageBattleManager.h"
#include "DictStageBattleMonster/DictStageBattleMonsterManager.h"
#include "DictStageBuilding/DictStageBuildingManager.h"
#include "DictStageStarReward/DictStageStarRewardManager.h"
#include "DictChapterStarReward/DictChapterStarRewardManager.h"
#include "DictStageBattleReward/DictStageBattleRewardManager.h"
#include "DictStageBattlePrestigeReward/DictStageBattlePrestigeRewardManager.h"
#include "DictMusou/DictMusouManager.h"
#include "DictMusouBattle/DictMusouBattleManager.h"
#include "DictMusouBattleMonster/DictMusouBattleMonsterManager.h"
#include "DictMusouBattleReward/DictMusouBattleRewardManager.h"
#include "DictMusouBattlePrestigeReward/DictMusouBattlePrestigeRewardManager.h"
#include "DictLineupOpenCost/DictLineupOpenCostManager.h"
#include "DictArenaBot/DictArenaBotManager.h"
#include "DictArenaBattleReward/DictArenaBattleRewardManager.h"
#include "DictArenaRankDayReward/DictArenaRankDayRewardManager.h"
#include "DictArenaRankWeeksReward/DictArenaRankWeeksRewardManager.h"
#include "DictArenaGloryShop/DictArenaGloryShopManager.h"
#include "DictArenaGloryShopResetCost/DictArenaGloryShopResetCostManager.h"
#include "DictStory/DictStoryManager.h"
#include "DictNewGuide/DictNewGuideManager.h"
#include "DictFunction/DictFunctionManager.h"
#include "DictStartRole/DictStartRoleManager.h"
#include "DictStartHero/DictStartHeroManager.h"
#include "DictStartLineup/DictStartLineupManager.h"
#include "DictVip/DictVipManager.h"
#include "DictCardCost/DictCardCostManager.h"
#include "DictChargeCost/DictChargeCostManager.h"
#include "DictBlackshop/DictBlackshopManager.h"
#include "DictBlackshopResetCost/DictBlackshopResetCostManager.h"
#include "DictVipGift/DictVipGiftManager.h"
#include "DictVipGiftCost/DictVipGiftCostManager.h"
#include "DictVipBoonReward/DictVipBoonRewardManager.h"
#include "DictVipBoonWeekReward/DictVipBoonWeekRewardManager.h"
#include "DictSignReward/DictSignRewardManager.h"
#include "DictSignEliteReward/DictSignEliteRewardManager.h"
#include "DictFirstChargeReward/DictFirstChargeRewardManager.h"
#include "DictLuckyGoldReward/DictLuckyGoldRewardManager.h"
#include "DictLuckyGoldTotalReward/DictLuckyGoldTotalRewardManager.h"
#include "DictFundCost/DictFundCostManager.h"
#include "DictFundReward/DictFundRewardManager.h"
#include "DictFundPublicReward/DictFundPublicRewardManager.h"
#include "DictWeekLoginReward/DictWeekLoginRewardManager.h"
#include "DictWeekChargeReward/DictWeekChargeRewardManager.h"
#include "DictWeekCostReward/DictWeekCostRewardManager.h"
#include "DictWeekTask/DictWeekTaskManager.h"
#include "DictWeekTaskReward/DictWeekTaskRewardManager.h"
#include "DictWeekShopReward/DictWeekShopRewardManager.h"
#include "DictStageBattleMonsterReward/DictStageBattleMonsterRewardManager.h"
#include "DictCdkeyReward/DictCdkeyRewardManager.h"
#include "DictLegend/DictLegendManager.h"
#include "DictLegendBattle/DictLegendBattleManager.h"
#include "DictLegendBattleMonster/DictLegendBattleMonsterManager.h"
#include "DictLegendBattleTimes/DictLegendBattleTimesManager.h"
#include "DictLegendTouchOdds/DictLegendTouchOddsManager.h"
#include "DictLegendBattleTouch/DictLegendBattleTouchManager.h"
#include "DictLegendDamageReward/DictLegendDamageRewardManager.h"
#include "DictLegendMonsterLoot/DictLegendMonsterLootManager.h"
#include "DictLegendPrestigeLoot/DictLegendPrestigeLootManager.h"
#include "DictLegendMonsterReward/DictLegendMonsterRewardManager.h"
#include "DictLegendRank/DictLegendRankManager.h"
#include "DictCdkeyRandomReward/DictCdkeyRandomRewardManager.h"
#include "DictChannel/DictChannelManager.h"
#include "DictSummonSkill/DictSummonSkillManager.h"
#include "DictArenaMatchingRule/DictArenaMatchingRuleManager.h"
#include "DictArenaRankFirstRiseReward/DictArenaRankFirstRiseRewardManager.h"
#include "DictArenaTimesBuy/DictArenaTimesBuyManager.h"
#include "DictArenaTimesReset/DictArenaTimesResetManager.h"
#include "DictAiSkillCast/DictAiSkillCastManager.h"
#include "DictAiWaitTime/DictAiWaitTimeManager.h"
#include "DictTips/DictTipsManager.h"
#include "DictHeroStar/DictHeroStarManager.h"
#include "DictHeroStarUpCost/DictHeroStarUpCostManager.h"
#include "DictGemstoneMine/DictGemstoneMineManager.h"
#include "DictGemstoneMineRate/DictGemstoneMineRateManager.h"
#include "DictBuyStamina/DictBuyStaminaManager.h"
#include "DictWeekTag/DictWeekTagManager.h"
#include "DictLuckyGoldTime/DictLuckyGoldTimeManager.h"
#include "DictEquipSoldReturn/DictEquipSoldReturnManager.h"
#include "DictLeadLootPool/DictLeadLootPoolManager.h"
#include "DictLeadLootSlots/DictLeadLootSlotsManager.h"
#include "DictLeadLootPhase/DictLeadLootPhaseManager.h"
#include "DictStageBattleFKReward/DictStageBattleFKRewardManager.h"
#include "DictLineupAuxiliary/DictLineupAuxiliaryManager.h"
#include "DictAiWaitPerformance/DictAiWaitPerformanceManager.h"


ConfigFileReader* ConfigFileReader::_instance = NULL;
ConfigFileReader::ConfigFileReader()
{
}
ConfigFileReader::~ConfigFileReader()
{
	 _instance=NULL;
}
ConfigFileReader* ConfigFileReader::getInstance()
{
	if(_instance != NULL)
	{
		_instance = new ConfigFileReader();
	}
	return _instance;
}
void ConfigFileReader::destroyInstance()
{
	if(_instance != NULL)
	{
		 delete _instance;
	}
}
void ConfigFileReader::loadConfig()
{
	const char* path = "dictData.json";
	unsigned char* pBuffer = NULL;
	long bufferSize = 0;
	pBuffer = FileUtils::getInstance()->getFileData(path, "r", &bufferSize);
	parse((const char*)pBuffer);
	if (pBuffer) {
		delete [] pBuffer;
		pBuffer = NULL;
	}
}
void ConfigFileReader::parse(const char* pBuffer)
{
	Json* root = Json_create(pBuffer);
	Json* item = root->child;
	while(item)
	{
		string key = item->name;
		if(key == "DictHeroPropLevel")//武将属性库level
		{
			DictHeroPropLevelManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictHeroPropPrestige")//武将属性库prestige
		{
			DictHeroPropPrestigeManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictMonsterPropLevel")//怪物属性库level
		{
			DictMonsterPropLevelManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictRoleLevel")//角色等级表
		{
			DictRoleLevelManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictRandomName")//随机姓名表
		{
			DictRandomNameManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictGlobalFormula")//全局标量公式表
		{
			DictGlobalFormulaManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictBattleReborn")//战斗结关次数表
		{
			DictBattleRebornManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictBattleRebornCost")//战斗结关次数花费表
		{
			DictBattleRebornCostManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictBattlePotion")//战斗药水购买次数表
		{
			DictBattlePotionManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictBattlePotionCost")//战斗药水购买花费表
		{
			DictBattlePotionCostManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictWay")//通用途径表
		{
			DictWayManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictHero")//武将表
		{
			DictHeroManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictHeroLevel")//武将等级表
		{
			DictHeroLevelManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictHeroPrestige")//武将声望表
		{
			DictHeroPrestigeManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictHeroQuality")//武将品质表
		{
			DictHeroQualityManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictHeroEquip")//武将装备表
		{
			DictHeroEquipManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictHeroLineupKarma")//武将阵容缘分表
		{
			DictHeroLineupKarmaManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictHeroPrestigeUpCost")//武将历练花费表
		{
			DictHeroPrestigeUpCostManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictHeroQualityUp")//武将觉醒
		{
			DictHeroQualityUpManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictHeroQualityUpCost")//武将觉醒花费
		{
			DictHeroQualityUpCostManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictMonster")//怪物表
		{
			DictMonsterManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictNPC")//NPC表
		{
			DictNPCManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictSkill")//技能表
		{
			DictSkillManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictBuff")//技能状态效果表
		{
			DictBuffManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictSkillKarma")//技能连携表
		{
			DictSkillKarmaManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictItem")//道具表
		{
			DictItemManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictItemHero")//道具武将表
		{
			DictItemHeroManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictItemEquip")//道具装备表
		{
			DictItemEquipManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictItemBook")//道具书信表
		{
			DictItemBookManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictItemMater")//道具材料表
		{
			DictItemMaterManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictResource")//资源包表
		{
			DictResourceManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictEquipForge")//装备熔炼表
		{
			DictEquipForgeManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictEquipForgeCost")//装备熔炼表
		{
			DictEquipForgeCostManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictEquipCompose")//装备合成表
		{
			DictEquipComposeManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictEquipHardenLevel")//装备强化等级表
		{
			DictEquipHardenLevelManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictEquipHardenFightProp")//装备强化属性表
		{
			DictEquipHardenFightPropManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictEquipHardenCost")//装备强化花费表
		{
			DictEquipHardenCostManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictItemQuality")//道具品质表
		{
			DictItemQualityManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictBookCost")//武将书信送礼花费表
		{
			DictBookCostManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictBookUpper")//武将书信友好度上限表
		{
			DictBookUpperManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictItemUseReward")//道具使用表
		{
			DictItemUseRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictTaskCommonType")//普通任务完成接口表
		{
			DictTaskCommonTypeManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictTaskCommonTypeMsg")//普通任务完成对msg表
		{
			DictTaskCommonTypeMsgManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictTaskCommon")//普通任务表
		{
			DictTaskCommonManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictTaskCommonReward")//普通任务奖励表
		{
			DictTaskCommonRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictTaskDayType")//日常任务完成接口表
		{
			DictTaskDayTypeManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictTaskDay")//日常任务表
		{
			DictTaskDayManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictTaskDayTypeMsg")//日常任务request关系
		{
			DictTaskDayTypeMsgManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictTaskDayProgressReward")//日常任务进度奖励表
		{
			DictTaskDayProgressRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictTaskDayReward")//日常任务奖励表
		{
			DictTaskDayRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictTaskWanted")//悬赏任务表
		{
			DictTaskWantedManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictTaskWantedProgressReward")//悬赏任务进度奖励表
		{
			DictTaskWantedProgressRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictTaskWantedReward")//悬赏任务奖励表
		{
			DictTaskWantedRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictFindCost")//搜寻花费表
		{
			DictFindCostManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictFindReward")//搜寻掉落表
		{
			DictFindRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictFindLootWeight")//搜寻掉落品权重表
		{
			DictFindLootWeightManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictFindOpenCost")//搜寻栏开启花费表
		{
			DictFindOpenCostManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLeadCost")//举贤花费表
		{
			DictLeadCostManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLeadReward")//举贤掉落表
		{
			DictLeadRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLeadLootWeight")//举贤掉落品权重表
		{
			DictLeadLootWeightManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictShopping")//商店售卖表
		{
			DictShoppingManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictShoppingVipTimes")//商店售卖VIP次数表
		{
			DictShoppingVipTimesManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictMarket")//拍卖售卖表
		{
			DictMarketManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictChapter")//章节表
		{
			DictChapterManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictStage")//关卡表
		{
			DictStageManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictStageBattle")//关卡战斗表
		{
			DictStageBattleManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictStageBattleMonster")//关卡怪物表
		{
			DictStageBattleMonsterManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictStageBuilding")//关卡建筑表
		{
			DictStageBuildingManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictStageStarReward")//关卡进度奖励表
		{
			DictStageStarRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictChapterStarReward")//章节进度奖励表
		{
			DictChapterStarRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictStageBattleReward")//关卡掉落表
		{
			DictStageBattleRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictStageBattlePrestigeReward")//关卡声望掉落表
		{
			DictStageBattlePrestigeRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictMusou")//无双表
		{
			DictMusouManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictMusouBattle")//无双战斗表
		{
			DictMusouBattleManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictMusouBattleMonster")//无双怪物表
		{
			DictMusouBattleMonsterManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictMusouBattleReward")//无双掉落表
		{
			DictMusouBattleRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictMusouBattlePrestigeReward")//无双声望掉落表
		{
			DictMusouBattlePrestigeRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLineupOpenCost")//阵容花费表
		{
			DictLineupOpenCostManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictArenaBot")//演武场机器人配置表
		{
			DictArenaBotManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictArenaBattleReward")//演武场战斗奖励表
		{
			DictArenaBattleRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictArenaRankDayReward")//演武场排名每日奖励表
		{
			DictArenaRankDayRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictArenaRankWeeksReward")//演武场排名两周奖励表
		{
			DictArenaRankWeeksRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictArenaGloryShop")//演武场荣誉商店表
		{
			DictArenaGloryShopManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictArenaGloryShopResetCost")//演武场荣誉商店刷新表
		{
			DictArenaGloryShopResetCostManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictStory")//剧情表
		{
			DictStoryManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictNewGuide")//新手指引表
		{
			DictNewGuideManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictFunction")//功能表
		{
			DictFunctionManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictStartRole")//玩家初始表
		{
			DictStartRoleManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictStartHero")//武将初始表
		{
			DictStartHeroManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictStartLineup")//阵容初始表
		{
			DictStartLineupManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictVip")//VIP表
		{
			DictVipManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictCardCost")//月卡花费返现表
		{
			DictCardCostManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictChargeCost")//充值花费返现表
		{
			DictChargeCostManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictBlackshop")//黑市售卖表
		{
			DictBlackshopManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictBlackshopResetCost")//黑市刷新花费表
		{
			DictBlackshopResetCostManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictVipGift")//VIP礼包表
		{
			DictVipGiftManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictVipGiftCost")//VIP礼包花费表
		{
			DictVipGiftCostManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictVipBoonReward")//VIP每日福利表
		{
			DictVipBoonRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictVipBoonWeekReward")//VIP周福利表
		{
			DictVipBoonWeekRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictSignReward")//每日签到表
		{
			DictSignRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictSignEliteReward")//豪华签到表
		{
			DictSignEliteRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictFirstChargeReward")//首充奖励表
		{
			DictFirstChargeRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLuckyGoldReward")//祈福单次获得表
		{
			DictLuckyGoldRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLuckyGoldTotalReward")//祈福累计获得表
		{
			DictLuckyGoldTotalRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictFundCost")//开服基金花费表
		{
			DictFundCostManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictFundReward")//开服基金返利表
		{
			DictFundRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictFundPublicReward")//全民福利返利表
		{
			DictFundPublicRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictWeekLoginReward")//七日活动登录奖励表
		{
			DictWeekLoginRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictWeekChargeReward")//七日活动充值得礼表
		{
			DictWeekChargeRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictWeekCostReward")//七日活动元宝消费表
		{
			DictWeekCostRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictWeekTask")//七日活动任务表
		{
			DictWeekTaskManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictWeekTaskReward")//七日活动任务奖励表
		{
			DictWeekTaskRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictWeekShopReward")//七日活动半价抢购表
		{
			DictWeekShopRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictStageBattleMonsterReward")//关卡环境道具掉落表
		{
			DictStageBattleMonsterRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictCdkeyReward")//礼包码奖励物品表
		{
			DictCdkeyRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLegend")//名将传基础表
		{
			DictLegendManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLegendBattle")//名将传战斗表
		{
			DictLegendBattleManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLegendBattleMonster")//名将传怪物表
		{
			DictLegendBattleMonsterManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLegendBattleTimes")//名将传战斗次数表
		{
			DictLegendBattleTimesManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLegendTouchOdds")//名将传触发战斗几率表
		{
			DictLegendTouchOddsManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLegendBattleTouch")//名将传触发
		{
			DictLegendBattleTouchManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLegendDamageReward")//名将传伤害掉落表
		{
			DictLegendDamageRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLegendMonsterLoot")//名将传怪物权重表
		{
			DictLegendMonsterLootManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLegendPrestigeLoot")//名将传声望权重表
		{
			DictLegendPrestigeLootManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLegendMonsterReward")//名将传怪物掉落表
		{
			DictLegendMonsterRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLegendRank")//名将传排名奖励表
		{
			DictLegendRankManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictCdkeyRandomReward")//随机字段礼包码奖励物品表
		{
			DictCdkeyRandomRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictChannel")//渠道更新表
		{
			DictChannelManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictSummonSkill")//召唤助手表
		{
			DictSummonSkillManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictArenaMatchingRule")//演武场匹配逻辑表
		{
			DictArenaMatchingRuleManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictArenaRankFirstRiseReward")//演武场首次最高排名奖励表
		{
			DictArenaRankFirstRiseRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictArenaTimesBuy")//演武场战斗次数购买表
		{
			DictArenaTimesBuyManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictArenaTimesReset")//演武场冷却重置购买表
		{
			DictArenaTimesResetManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictAiSkillCast")//AI技能释放表
		{
			DictAiSkillCastManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictAiWaitTime")//AI犯傻时间表
		{
			DictAiWaitTimeManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictTips")//通用提示表
		{
			DictTipsManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictHeroStar")//武将升星表
		{
			DictHeroStarManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictHeroStarUpCost")//武将升星消耗表
		{
			DictHeroStarUpCostManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictGemstoneMine")//矿车获得表
		{
			DictGemstoneMineManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictGemstoneMineRate")//矿车倍率成长表
		{
			DictGemstoneMineRateManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictBuyStamina")//体力购买表
		{
			DictBuyStaminaManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictWeekTag")//七日活动标签表
		{
			DictWeekTagManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLuckyGoldTime")//祈福间隔时长表
		{
			DictLuckyGoldTimeManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictEquipSoldReturn")//装备铜钱返还系数
		{
			DictEquipSoldReturnManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLeadLootPool")//新抽卡库表
		{
			DictLeadLootPoolManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLeadLootSlots")//新10连空位表
		{
			DictLeadLootSlotsManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLeadLootPhase")//新抽卡价值段表
		{
			DictLeadLootPhaseManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictStageBattleFKReward")//关卡首次掉落表
		{
			DictStageBattleFKRewardManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictLineupAuxiliary")//助阵位表
		{
			DictLineupAuxiliaryManager::getInstance()->setConfigData(item);
		}
		else if(key == "DictAiWaitPerformance")//AI犯傻行为表
		{
			DictAiWaitPerformanceManager::getInstance()->setConfigData(item);
		}
		item = item->next;
	}
	Json_dispose(root);
}
