//
//  Protocal.h
//  FightPass
//
//  Created by zhangxiaobin on 15/6/12.
//
//

#ifndef FightPass_Protocal_h
#define FightPass_Protocal_h
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
//----------------------------------网关消息----------------------------------------------
//上行数据是正数。下行是上行的负数
const int SCENE_CLIENT_LOGIN_UP = 151200001;
const int SCENE_CLIENT_LOGIN_BACK = -151200001;


//客户端消息==============================================================
const int CLIENT_GATE_DisconnectReq=121500001;	//服务器通知客户端断开连接

// 为scense服务
const int CLIENT_SCENSE_RolePropUpdateReq=121400001;	//通知客户端角色属性更新
const int CLIENT_SCENSE_RolePropUpdateResp=-121400001;	//通知客户端角色属性更新

const int CLIENT_SCENSE_RoleFunctionOpenReq=121400002;	//通知客户端新功能开启
const int CLIENT_SCENSE_RoleFunctionOpenResp=-121400002;	//通知客户端新功能开启

const int CLIENT_GATE_MarqueeNotifyReq=121500002;	//跑马灯通知
const int CLIENT_GATE_MarqueeNotifyResp=-121500002;	//跑马灯通知

// 为客户端服务器的消息================================================
//-----------------------------------场景消息---------------------------------------------
// test 分类code:00 
const int SCENSE_CLIENT_TEST_TestRpcReq=141200001;	//测试Req
const int SCENSE_CLIENT_TEST_TestRpcResp=-141200001;	//测试Resp

// 账号account 分类code:01
const int SCENSE_CLIENT_ACCOUNT_RandomRoleNameReq=141201001;	//获取随机角色名Req
const int SCENSE_CLIENT_ACCOUNT_RandomRoleNameResp=-141201001;	//获取随机角色名Resp
const int SCENSE_CLIENT_ACCOUNT_CreateRoleReq=141201002;	//创建角色Req
const int SCENSE_CLIENT_ACCOUNT_CreateRoleResp=-141201002;	//创建角色Resp
const int SCENSE_CLIENT_ACCOUNT_RoleInfoReq=141201003;	//角色基本属性Req
const int SCENSE_CLIENT_ACCOUNT_RoleInfoResp=-141201003;	//角色基本属性Resp
const int SCENSE_CLIENT_ACCOUNT_NoticePageReq=141201006;	//公告页Req
const int SCENSE_CLIENT_ACCOUNT_NoticePageResp=-141201006;	//公告页Resp

const int SCENSE_CLIENT_ACCOUNT_NewGuidePassReq=141201005;	//新手引导通过Req
const int SCENSE_CLIENT_ACCOUNT_NewGuidePassResp=-141201005;	//新手引导通过Resp

const int SCENSE_CLIENT_ACCOUNT_MarqueePageReq=141201007;	//跑马灯列表Req
const int SCENSE_CLIENT_ACCOUNT_MarqueePageResp=-141201007;	//跑马灯列表Resp

// 支付 pay 分类code:02
const int SCENSE_CLIENT_PAY_PayPageReq=141202001;	//支付页面Req
const int SCENSE_CLIENT_PAY_PayPageResp=-141202001;	//支付页面Resp
//const int SCENSE_CLIENT_PAY_LengjingPayCreateOrderReq=141202002;	//棱镜支付创建订单Req
//const int SCENSE_CLIENT_PAY_LengjingPayCreateOrderResp=-141202002;	//棱镜支付创建订单Resp

const int SCENSE_CLIENT_PAY_Sdk1PayCreateOrderReq=141202003;	//易接支付创建订单Req
const int SCENSE_CLIENT_PAY_Sdk1PayCreateOrderResp=-141202003;	//易接支付创建订单Resp

// 支付 pay 分类code:02
const int SCENSE_CLIENT_PAY_PayCardReceiveReq=141202004;	//领取月卡元宝Req
const int SCENSE_CLIENT_PAY_PayCardReceiveResp=-141202004;	//领取月卡元宝Resp

//苹果支付
const int ApplePayCreateOrderReq = 141202005 ;	  // 苹果支付创建订单Req
const int ApplePayCreateOrderResp = -141202005 ;	   // 苹果支付创建订单Resp

// 武将hero 分类code:03
const int SCENSE_CLIENT_HERO_HeroListBarReq=141203001;	//武将头像列表Req
const int SCENSE_CLIENT_HERO_HeroListBarResp=-141203001;	//武将头像列表Resp
const int SCENSE_CLIENT_HERO_HeroListPageReq=141203002;	//武将列表页Req
const int SCENSE_CLIENT_HERO_HeroListPageResp=-141203002;	//武将列表页Resp
const int SCENSE_CLIENT_HERO_HeroInfoPageReq=141203003;	//武将信息页Req
const int SCENSE_CLIENT_HERO_HeroInfoPageResp=-141203003;	//武将信息页Resp
const int SCENSE_CLIENT_HERO_HeroBasePageReq=141203004;	//武将基础页Req
const int SCENSE_CLIENT_HERO_HeroBasePageResp=-141203004;	//武将基础页Resp
const int SCENSE_CLIENT_HERO_HeroEquipSelPageReq=141203005;	//武将装备选择页Req
const int SCENSE_CLIENT_HERO_HeroEquipSelPageResp=-141203005;	//武将装备选择页Resp
const int SCENSE_CLIENT_HERO_HeroPutOnReq=141203006;	//武将穿上装备Req
const int SCENSE_CLIENT_HERO_HeroPutOnResp=-141203006;	//武将穿上装备Resp
const int SCENSE_CLIENT_HERO_HeroTakeOffReq=141203007;	//武将脱掉装备Req
const int SCENSE_CLIENT_HERO_HeroTakeOffResp=-141203007;	//武将脱掉装备Resp
const int SCENSE_CLIENT_HERO_HeroOneKeyPutOnReq=141203008;	//一键装备Req
const int SCENSE_CLIENT_HERO_HeroOneKeyPutOnResp=-141203008;	//一键装备Resp
const int SCENSE_CLIENT_HERO_HeroWakeUpPageReq=141203009;	//武将觉醒页Req
const int SCENSE_CLIENT_HERO_HeroWakeUpPageResp=-141203009;	//武将觉醒页Resp
const int SCENSE_CLIENT_HERO_HeroWakeUpReq=141203010;	//武将觉醒Req
const int SCENSE_CLIENT_HERO_HeroWakeUpResp=-141203010;	//武将觉醒Resp
const int SCENSE_CLIENT_HERO_HeroPropertyPageReq=141203011;	//武将属性页Req
const int SCENSE_CLIENT_HERO_HeroPropertyPageResp=-141203011;	//武将属性页Resp
const int SCENSE_CLIENT_HERO_HeroSkillPageReq=141203012;	//武将技能页Req
const int SCENSE_CLIENT_HERO_HeroSkillPageResp=-141203012;	//武将技能页Resp
const int SCENSE_CLIENT_HERO_HeroMaterialSelPageReq=141203013;	//武将历练素材选择页Req
const int SCENSE_CLIENT_HERO_HeroMaterialSelPageResp=-141203013;	//武将历练素材选择页Resp
const int SCENSE_CLIENT_HERO_HeroStartPlacesReq=141203014;	//武将开始历练Req
const int SCENSE_CLIENT_HERO_HeroStartPlacesResp=-141203014;	//武将开始历练Resp
const int SCENSE_CLIENT_HERO_HeroSellPageReq=141203015;	//武将出售列表页Req
const int SCENSE_CLIENT_HERO_HeroSellPageResp=-141203015;	//武将出售列表页Resp
const int SCENSE_CLIENT_HERO_HeroSellReq=141203016;	//武将出售Req
const int SCENSE_CLIENT_HERO_HeroSellResp=-141203016;	//武将出售Resp
const int SCENSE_CLIENT_HERO_HeroOneKeyHardenReq=141203017;	//一键强化Req
const int SCENSE_CLIENT_HERO_HeroOneKeyHardenResp=-141203017;	//一键强化Resp

const int SCENSE_CLIENT_HERO_HeroWakeUpPage2Req=141203018;	//武将觉醒页Req
const int SCENSE_CLIENT_HERO_HeroWakeUpPage2Resp=-141203018;	//武将觉醒页Resp
const int SCENSE_CLIENT_HERO_HeroWakeUp2Req=141203019;	//武将觉醒Req
const int SCENSE_CLIENT_HERO_HeroWakeUp2Resp=-141203019;	//武将觉醒Resp
const int SCENSE_CLIENT_HERO_HeroStarUpPageReq=141203020;	//武将升星页Req
const int SCENSE_CLIENT_HERO_HeroStarUpPageResp=-141203020;	//武将升星页Resp
const int SCENSE_CLIENT_HERO_HeroStarUpReq=141203021;	//武将升星Req
const int SCENSE_CLIENT_HERO_HeroStarUpResp=-141203021;	//武将升星Resp
const int SCENSE_CLIENT_HERO_HeroAddExpReq=141203022;	//武将加经验Req
const int SCENSE_CLIENT_HERO_HeroAddExpResp=-141203022;	//武将加经验Resp

// 装备 分类code:04
const int SCENSE_CLIENT_EQUIP_EquipListPageReq=141204001;	//装备列表页Req
const int SCENSE_CLIENT_EQUIP_EquipListPageResp=-141204001;	//装备列表页Resp
const int SCENSE_CLIENT_EQUIP_EquipHardenPageReq=141204002;	//装备强化页Req
const int SCENSE_CLIENT_EQUIP_EquipHardenPageResp=-141204002;	//装备强化页Resp
const int SCENSE_CLIENT_EQUIP_EquipStartHardenReq=141204003;	//开始强化Req
const int SCENSE_CLIENT_EQUIP_EquipStartHardenResp=-141204003;	//开始强化Resp
const int SCENSE_CLIENT_EQUIP_EquipForgePageReq=141204004;	//熔炼页Req
const int SCENSE_CLIENT_EQUIP_EquipForgePageResp=-141204004;	//熔炼页Resp
const int SCENSE_CLIENT_EQUIP_EquipForgeReq=141204005;	//熔炼Req
const int SCENSE_CLIENT_EQUIP_EquipForgeResp=-141204005;	//熔炼Resp
const int SCENSE_CLIENT_EQUIP_EquipSellPageReq=141204006;	//装备出售列表页Req
const int SCENSE_CLIENT_EQUIP_EquipSellPageResp=-141204006;	//装备出售列表页Resp
const int SCENSE_CLIENT_EQUIP_EquipSellReq=141204007;	//装备出售Req
const int SCENSE_CLIENT_EQUIP_EquipSellResp=-141204007;	//装备出售Resp

// 阵容lineup 分类code:05
const int SCENSE_CLIENT_LINEUP_LineupListReq=141205001;	//阵容列表Req
const int SCENSE_CLIENT_LINEUP_LineupListResp=-141205001;	//阵容列表Resp
const int SCENSE_CLIENT_LINEUP_LineupPageReq=141205002;	//阵容页Req
const int SCENSE_CLIENT_LINEUP_LineupPageResp=-141205002;	//阵容页Resp
const int SCENSE_CLIENT_LINEUP_LineupHeroSelPageReq=141205003;	//阵容武将选择页Req
const int SCENSE_CLIENT_LINEUP_LineupHeroSelPageResp=-141205003;	//阵容武将选择页Resp
const int SCENSE_CLIENT_LINEUP_LineupSetReq=141205004;	//阵容上阵Req
const int SCENSE_CLIENT_LINEUP_LineupSetResp=-141205004;	//阵容上阵Resp
const int SCENSE_CLIENT_LINEUP_LineupDownReq=141205005;	//阵容下阵Req
const int SCENSE_CLIENT_LINEUP_LineupDownResp=-141205005;	//阵容下阵Resp
const int SCENSE_CLIENT_LINEUP_LineupSetLocationReq=141205006;	//阵容改变位置Req
const int SCENSE_CLIENT_LINEUP_LineupSetLocationResp=-141205006;	//阵容改变位置Resp
const int SCENSE_CLIENT_LINEUP_LineupCreateReq=141205007;	//创建新阵容Req
const int SCENSE_CLIENT_LINEUP_LineupCreateResp=-141205007;	//创建新阵容Resp
const int SCENSE_CLIENT_LINEUP_LineupSetDefaultReq=141205008;	//设置默认阵容Req
const int SCENSE_CLIENT_LINEUP_LineupSetDefaultResp=-141205008;	//设置默认阵容Resp

// 战役battle 分类code:06
const int SCENSE_CLIENT_BATTLE_ChapterPageReq=141206001;	//章节页Req
const int SCENSE_CLIENT_BATTLE_ChapterPageResp=-141206001;	//章节页Resp
const int SCENSE_CLIENT_BATTLE_StagePageReq=141206002;	//关卡页Req
const int SCENSE_CLIENT_BATTLE_StagePageResp=-141206002;	//关卡页Resp
const int SCENSE_CLIENT_BATTLE_ChapterOpenBoxReq=141206003;	//章节开宝箱Req
const int SCENSE_CLIENT_BATTLE_ChapterOpenBoxResp=-141206003;	//章节开宝箱Resp
const int SCENSE_CLIENT_BATTLE_StageOpenBoxReq=141206004;	//关卡开宝箱Req
const int SCENSE_CLIENT_BATTLE_StageOpenBoxResp=-141206004;	//关卡开宝箱Resp
const int SCENSE_CLIENT_BATTLE_StartBattleReq=141206005;	//开始战斗Req
const int SCENSE_CLIENT_BATTLE_StartBattleResp=-141206005;	//开始战斗Resp
const int SCENSE_CLIENT_BATTLE_EndBattleReq=141206006;	//结束战斗Req
const int SCENSE_CLIENT_BATTLE_EndBattleResp=-141206006;	//结束战斗Resp
const int SCENSE_CLIENT_BATTLE_SweptReq=141206007;	//扫荡Req
const int SCENSE_CLIENT_BATTLE_SweptResp=-141206007;	//扫荡Resp

const int SCENSE_CLIENT_BATTLE_RebornReq=141206008;	//战斗复活req
const int SCENSE_CLIENT_BATTLE_RebornResp=-141206008;	//战斗复活req
const int SCENSE_CLIENT_BATTLE_PotionReq=141206009;	//战斗买血瓶req
const int SCENSE_CLIENT_BATTLE_PotionResp=-141206009;	//战斗买血瓶req

const int SCENSE_CLIENT_BATTLE_BattleLootReq=141206010;	//战斗中掉落req
const int SCENSE_CLIENT_BATTLE_BattleLootResp=-141206010;	//战斗中掉落req

// 名将 famous 分类code:07

// 无双musou 分类code:08
const int SCENSE_CLIENT_MUSOU_MusouPageReq=141208001;	//关卡页Req
const int SCENSE_CLIENT_MUSOU_MusouPageResp=-141208001;	//关卡页Resp
const int SCENSE_CLIENT_MUSOU_MusouBattlePageReq=141208002;	//战斗页Req
const int SCENSE_CLIENT_MUSOU_MusouBattlePageResp=-141208002;	//战斗页Resp
const int SCENSE_CLIENT_MUSOU_MusouStartBattleReq=141208003;	//开始战斗Req
const int SCENSE_CLIENT_MUSOU_MusouStartBattleResp=-141208003;	//开始战斗Resp
const int SCENSE_CLIENT_MUSOU_MusouEndBattleReq=141208004;	//结束战斗Req
const int SCENSE_CLIENT_MUSOU_MusouEndBattleResp=-141208004;	//结束战斗Resp

// 书信 分类code:09
const int SCENSE_CLIENT_BOOK_BookPageReq=141209001;	//书信列表页面Req
const int SCENSE_CLIENT_BOOK_BookPageResp=-141209001;	//书信列表页面Resp
const int SCENSE_CLIENT_BOOK_BookDeliverReq=141209002;	//书信送信Req
const int SCENSE_CLIENT_BOOK_BookDeliverResp=-141209002;	//书信送信Resp
const int SCENSE_CLIENT_BOOK_BookGiftReq=141209003;	//书信送礼Req
const int SCENSE_CLIENT_BOOK_BookGiftResp=-141209003;	//书信送礼Resp
const int SCENSE_CLIENT_BOOK_BookInviteReq=141209004;	//书信出山Req
const int SCENSE_CLIENT_BOOK_BookInviteResp=-141209004;	//书信出山Resp
const int SCENSE_CLIENT_BOOK_BookHeroInfoReq=141209005;	//书信，获取新武将信息req
const int SCENSE_CLIENT_BOOK_BookHeroInfoResp=-141209005;	//书信，获取新武将信息req

const int SCENSE_CLIENT_BOOK_BookPage2Req=141209006;	//书信列表页面Req
const int SCENSE_CLIENT_BOOK_BookPage2Resp=-141209006;	//书信列表页面Resp
const int SCENSE_CLIENT_BOOK_BookInvite2Req=141209007;	//书信出山Req
const int SCENSE_CLIENT_BOOK_BookInvite2Resp=-141209007;	//书信出山Resp

// 寻访 分类code:10
const int SCENSE_CLIENT_FIND_FindPageReq=141210001;	//寻访页Req
const int SCENSE_CLIENT_FIND_FindPageResp=-141210001;	//寻访页Resp
const int SCENSE_CLIENT_FIND_FindExtendReq=141210002;	//领地扩展Req
const int SCENSE_CLIENT_FIND_FindExtendResp=-141210002;	//领地扩展Resp
const int SCENSE_CLIENT_FIND_FindHeroSelPageReq=141210003;	//选择寻访者列表Req
const int SCENSE_CLIENT_FIND_FindHeroSelPageResp=-141210003;	//选择寻访者列表Resp
const int SCENSE_CLIENT_FIND_FindHeroSelReq=141210004;	//选择寻访者Req
const int SCENSE_CLIENT_FIND_FindHeroSelResp=-141210004;	//选择寻访者Resp
const int SCENSE_CLIENT_FIND_FindStartReq=141210005;	//开始寻访Req
const int SCENSE_CLIENT_FIND_FindStartResp=-141210005;	//开始寻访Resp
const int SCENSE_CLIENT_FIND_FindSpeedUpReq=141210006;	//加速寻访Req
const int SCENSE_CLIENT_FIND_FindSpeedUpResp=-141210006;	//加速寻访Resp
const int SCENSE_CLIENT_FIND_FindResultReq=141210007;	//查询结果Req
const int SCENSE_CLIENT_FIND_FindResultResp=-141210007;	//查询结果Resp

// 举贤 分类code:11
const int SCENSE_CLIENT_LEAD_LeadPageReq=141211001;	//举贤列表Req
const int SCENSE_CLIENT_LEAD_LeadPageResp=-141211001;	//举贤列表Resp
const int SCENSE_CLIENT_LEAD_LeadReq=141211002;	//举贤Req
const int SCENSE_CLIENT_LEAD_LeadResp=-141211002;	//举贤Resp

// 商店 分类code:12
const int SCENSE_CLIENT_SHOP_ShopPageReq=141212001;	//商店列表Req
const int SCENSE_CLIENT_SHOP_ShopPageResp=-141212001;	//商店列表Resp
const int SCENSE_CLIENT_SHOP_ShopBuyReq=141212002;	//商店购买Req
const int SCENSE_CLIENT_SHOP_ShopBuyResp=-141212002;	//商店购买Resp

// 拍卖 分类code:13
const int SCENSE_CLIENT_MARKET_MarketSellPageReq=141213001;	//拍卖所Req
const int SCENSE_CLIENT_MARKET_MarketSellPageResp=-141213001;	//拍卖所Resp
const int SCENSE_CLIENT_MARKET_MarketToSellPageReq=141213002;	//去出售Req
const int SCENSE_CLIENT_MARKET_MarketToSellPageResp=-141213002;	//去出售Resp
const int SCENSE_CLIENT_MARKET_MarketMySellPageReq=141213003;	//上架中Req
const int SCENSE_CLIENT_MARKET_MarketMySellPageResp=-141213003;	//上架中Resp
const int SCENSE_CLIENT_MARKET_MarketBuyReq=141213004;	//购买Req
const int SCENSE_CLIENT_MARKET_MarketBuyResp=-141213004;	//购买Resp
const int SCENSE_CLIENT_MARKET_MarketSellReq=141213005;	//卖出Req
const int SCENSE_CLIENT_MARKET_MarketSellResp=-141213005;	//卖出Resp
const int SCENSE_CLIENT_MARKET_MarketPullOffReq=141213006;	//下架Req
const int SCENSE_CLIENT_MARKET_MarketPullOffResp=-141213006;	//下架Resp

// 任务 分类code:14
const int SCENSE_CLIENT_TASK_TaskCommonPageReq=141214001;	//普通任务列表Req
const int SCENSE_CLIENT_TASK_TaskCommonPageResp=-141214001;	//普通任务列表Resp
const int SCENSE_CLIENT_TASK_TaskCommonRewardReq=141214002;	//普通任务领取奖励Req
const int SCENSE_CLIENT_TASK_TaskCommonRewardResp=-141214002;	//普通任务领取奖励Resp
const int SCENSE_CLIENT_TASK_TaskDayPageReq=141214003;	//日常任务列表Req
const int SCENSE_CLIENT_TASK_TaskDayPageResp=-141214003;	//日常任务列表Resp
const int SCENSE_CLIENT_TASK_TaskDayRewardReq=141214004;	//日常任务领取奖励Req
const int SCENSE_CLIENT_TASK_TaskDayRewardResp=-141214004;	//日常任务领取奖励Resp
const int SCENSE_CLIENT_TASK_TaskDayProgressRewardReq=141214005;	//日常任务领取进度奖励Req
const int SCENSE_CLIENT_TASK_TaskDayProgressRewardResp=-141214005;	//日常任务领取进度奖励Resp

// 材料 分类code:15
const int SCENSE_CLIENT_MATER_MaterPageReq=141215001;	//材料列表页Req
const int SCENSE_CLIENT_MATER_MaterPageResp=-141215001;	//材料列表页Resp
const int SCENSE_CLIENT_MATER_MaterComposeReq=141215002;	//材料合成Req
const int SCENSE_CLIENT_MATER_MaterComposeResp=-141215002;	//材料合成Resp

// 道具 分类code:16
const int SCENSE_CLIENT_ITEM_ItemWayReq=141216001;	//物品获得途径Req
const int SCENSE_CLIENT_ITEM_ItemWayResp=-141216001;	//物品获得途径Resp
const int SCENSE_CLIENT_ITEM_ItemPageReq=141216002;	//道具列表页Req
const int SCENSE_CLIENT_ITEM_ItemPageResp=-141216002;	//道具列表页Resp
const int SCENSE_CLIENT_ITEM_ItemUseReq=141216003;	//道具使用Req
const int SCENSE_CLIENT_ITEM_ItemUseResp=-141216003;	//道具使用Resp
// 黑市 分类code:17
const int SCENSE_CLIENT_BLACK_BlackPageReq=141217001;	//黑市页Req
const int SCENSE_CLIENT_BLACK_BlackPageResp=-141217001;	//黑市页Resp
const int SCENSE_CLIENT_BLACK_BlackBuyReq=141217002;	//黑市购买Req
const int SCENSE_CLIENT_BLACK_BlackBuyResp=-141217002;	//黑市购买Resp

// addition 分类code:99

const int SCENSE_CLIENT_ADDITION_RolePropUpdateAdditionReq=141299001;	//通知客户端角色属性数值变化
const int SCENSE_CLIENT_ADDITION_RolePropUpdateAdditionResp=-141299001;	//通知客户端角色属性数值变化

const int SCENSE_CLIENT_ADDITION_RoleFunctionOpenAdditionReq=141299002;	//通知客户端角色新功能开启
const int SCENSE_CLIENT_ADDITION_RoleFunctionOpenAdditionResp=-141299002;	//通知客户端角色新功能开启


// 礼包 分类code:18
const int SCENSE_CLIENT_GIFT_GiftPageReq=141218001;	//礼包页Req
const int SCENSE_CLIENT_GIFT_GiftPageResp=-141218001;	//礼包页Resp
const int SCENSE_CLIENT_GIFT_GiftBuyReq=141218002;	//礼包购买Req
const int SCENSE_CLIENT_GIFT_GiftBuyResp=-141218002;	//礼包购买Resp


//修改角色名称
const int SCENSE_CLIENT_ACCOUNT_SetRolenameReq=141201004;	//修改角色名Req
const int SCENSE_CLIENT_ACCOUNT_SetRolenameResp=-141201004;	//修改角色名Resp

// 签到 分类code:19
const int SCENSE_CLIENT_SIGNDAY_SignDayPageReq=141219001;	//每日签到页Req
const int SCENSE_CLIENT_SIGNDAY_SignDayPageResp=-141219001;	//每日签到页Resp
const int SCENSE_CLIENT_SIGNDAY_SignDaySignReq=141219002;	//每日签到领取Req
const int SCENSE_CLIENT_SIGNDAY_SignDaySignResp=-141219002;	//每日签到领取Resp

// 豪华签到 分类code:20
const int SCENSE_CLIENT_SIGNELITE_SignElitePageReq=141220001;	//豪华签到页Req
const int SCENSE_CLIENT_SIGNELITE_SignElitePageResp=-141220001;	//豪华签到页Resp
const int SCENSE_CLIENT_SIGNELITE_SignEliteSignReq=141220002;	//豪华签到领取Req
const int SCENSE_CLIENT_SIGNELITE_SignEliteSignResp=-141220002;	//豪华签到领取Resp


// 邮件 分类code:21
const int SCENSE_CLIENT_MAIL_MailPageReq=141221001;	//列表页Req
const int SCENSE_CLIENT_MAIL_MailPageResp=-141221001;//列表页Resp
const int SCENSE_CLIENT_MAIL_MailContentReq=141221002;	//查看邮件Req
const int SCENSE_CLIENT_MAIL_MailContentResp=-141221002;	//查看邮件Resp
const int SCENSE_CLIENT_MAIL_MailReceiveItemReq=141221003;	//领取邮件物品Req
const int SCENSE_CLIENT_MAIL_MailReceiveItemResp=-141221003;	//领取邮件物品Resp
const int SCENSE_CLIENT_MAIL_MailReceiveAllItemReq=141221004;	//一键领取邮件物品Req
const int SCENSE_CLIENT_MAIL_MailReceiveAllItemResp=-141221004;	//一键领取邮件物品Resp


// 首冲 分类code:22
const int SCENSE_CLIENT_FIRSTCHARGE_FirstChargePageReq=141222001;	//首充礼包页面Req
const int SCENSE_CLIENT_FIRSTCHARGE_FirstChargePageResp=-141222001;	//首充礼包页面Resp
const int SCENSE_CLIENT_FIRSTCHARGE_FirstChargeReceiveReq=141222002;	//首充礼包领取Req
const int SCENSE_CLIENT_FIRSTCHARGE_FirstChargeReceiveResp=-141222002;	//首充礼包领取Resp

//七日 分类code:23
const int SCENSE_CLIENT_WEEK_WeekOpenDayReq=141223001;	//当前开启天数Req
const int SCENSE_CLIENT_WEEK_WeekOpenDayResp=-141223001;	//当前开启天数Resp
const int SCENSE_CLIENT_WEEK_WeekRewardPageReq=141223002;	//七日福利页Req
const int SCENSE_CLIENT_WEEK_WeekRewardPageResp=-141223002;	//七日福利页Resp
const int SCENSE_CLIENT_WEEK_WeekReceiveReq=141223003;	//七日领取奖励Req
const int SCENSE_CLIENT_WEEK_WeekReceiveResp=-141223003;	//七日领取奖励Resp
const int SCENSE_CLIENT_WEEK_WeekHalfPageReq=141223004;	//七日半价页Req
const int SCENSE_CLIENT_WEEK_WeekHalfPageResp=-141223004;	//七日半价页Resp
const int SCENSE_CLIENT_WEEK_WeekHalfBuyReq=141223005;	//七日半价购买Req
const int SCENSE_CLIENT_WEEK_WeekHalfBuyResp=-141223005;	//七日半价购买Resp
const int SCENSE_CLIENT_WEEK_WeekTaskPageReq=141223006;	//七日任务页Req
const int SCENSE_CLIENT_WEEK_WeekTaskPageResp=-141223006;	//七日任务页Resp

const int SCENSE_CLIENT_WEEK_WeekRedPointStatusReq=141223007;	//七日红点状态Req
const int SCENSE_CLIENT_WEEK_WeekRedPointStatusResp=-141223007;	//七日红点状态Resp

// 招财 分类code:24
const int SCENSE_CLIENT_LUCKY_LuckyPageReq=141224001;	//招财页面Req
const int SCENSE_CLIENT_LUCKY_LuckyPageResp=-141224001;	//招财页面Resp
const int SCENSE_CLIENT_LUCKY_LuckyGoReq=141224002;	//招财开始祈福Req
const int SCENSE_CLIENT_LUCKY_LuckyGoResp=-141224002;	//招财开始祈福Resp
const int SCENSE_CLIENT_LUCKY_LuckyReceiveAllReq=141224003;	//招财领取累积奖品Req
const int SCENSE_CLIENT_LUCKY_LuckyReceiveAllResp=-141224003;	//招财领取累积奖品Resp

// 好友 分类code:25
const int SCENSE_CLIENT_FRIEND_FriendMyInfoPageReq=141225001;	//好友基础页Req
const int SCENSE_CLIENT_FRIEND_FriendMyInfoPageResp=-141225001;	//好友基础页Resp
const int SCENSE_CLIENT_FRIEND_FriendUpdateYaYaIdReq=141225002;	//更新呀呀好友Req
const int SCENSE_CLIENT_FRIEND_FriendUpdateYaYaIdResp=-141225002;	//更新呀呀好友Resp
const int SCENSE_CLIENT_FRIEND_FriendMyPageReq=141225003;	//我的好友页Req
const int SCENSE_CLIENT_FRIEND_FriendMyPageResp=-141225003;	//我的好友页Resp
const int SCENSE_CLIENT_FRIEND_FriendHeadIconSelPageReq=141225004;	//头像选择列表Req
const int SCENSE_CLIENT_FRIEND_FriendHeadIconSelPageResp=-141225004;	//头像选择列表Resp
const int SCENSE_CLIENT_FRIEND_FriendSetIconReq=141225005;	//设置头像Req
const int SCENSE_CLIENT_FRIEND_FriendSetIconResp=-141225005;	//设置头像Resp
const int SCENSE_CLIENT_FRIEND_FriendDelReq=141225006;	//删除好友Req
const int SCENSE_CLIENT_FRIEND_FriendDelResp=-141225006;	//删除好友Resp
const int SCENSE_CLIENT_FRIEND_FriendSearchRoleReq=141225007;	//查询陌生玩家Req
const int SCENSE_CLIENT_FRIEND_FriendSearchRoleResp=-141225007;	//查询陌生玩家Resp
const int SCENSE_CLIENT_FRIEND_FriendAddReq=141225008;	//加好友Req
const int SCENSE_CLIENT_FRIEND_FriendAddResp=-141225008;	//加好友Resp
const int SCENSE_CLIENT_FRIEND_FriendAddAskPageReq=141225009;	//好友申请列表Req
const int SCENSE_CLIENT_FRIEND_FriendAddAskPageResp=-141225009;	//好友申请列表Resp
const int SCENSE_CLIENT_FRIEND_FriendAddAgreeReq=141225010;	   //好友申请同意Req
const int SCENSE_CLIENT_FRIEND_FriendAddAgreeResp=-141225010;	//好友申请同意Resp
const int SCENSE_CLIENT_FRIEND_FriendAddRefuseReq=141225011;	//好友申请拒绝Req
const int SCENSE_CLIENT_FRIEND_FriendAddRefuseResp=-141225011;	//好友申请拒绝Resp

// 福利 分类code：26
const int SCENSE_CLIENT_BOON_BoonDayPageReq=141226001;	//每日福利页面Req
const int SCENSE_CLIENT_BOON_BoonDayPageResp=-141226001;	//每日福利页面Resp
const int SCENSE_CLIENT_BOON_BoonDayReceiveReq=141226002;	//每日福利领取Req
const int SCENSE_CLIENT_BOON_BoonDayReceiveResp=-141226002;	//每日福利领取Resp
const int SCENSE_CLIENT_BOON_BoonWeekPageReq=141226003;	//周福利页面Req
const int SCENSE_CLIENT_BOON_BoonWeekPageResp=-141226003;	//周福利页面Resp
const int SCENSE_CLIENT_BOON_BoonWeekBuyReq=141226004;	//每周福利购买Req
const int SCENSE_CLIENT_BOON_BoonWeekBuyResp=-141226004;	//每周福利购买Resp
const int SCENSE_CLIENT_ACCOUNT_ReceivePowerPageReq=141201009;	//领取体力页Req
const int SCENSE_CLIENT_ACCOUNT_ReceivePowerPageResp=-141201009;	//领取体力页Resp
const int SCENSE_CLIENT_ACCOUNT_ReceivePowerReq=141201010;	//领取体力Req
const int SCENSE_CLIENT_ACCOUNT_ReceivePowerResp=-141201010;	//领取体力Resp

// 激活码code：27
const int SCENSE_CLIENT_CDKEY_CdkeyEnterReq=141227002;	//激活码输入Req
const int SCENSE_CLIENT_CDKEY_CdkeyEnterResp=-141227002;	//激活码输入Resp

//限时抽卡
const int SCENSE_CLIENT_LEGEND_LegendLeadPageReq=141228014;	//举贤页Req
const int SCENSE_CLIENT_LEGEND_LegendLeadPageResp=-141228014;	//举贤页Resp
const int SCENSE_CLIENT_LEGEND_LegendLeadReq=141228015;	//举贤Req
const int SCENSE_CLIENT_LEGEND_LegendLeadResp=-141228015;	//举贤Resp

// 名将传code：28
const int SCENSE_CLIENT_LEGEND_LegendHistoryPageReq=141228001;	//名将传历史页Req
const int SCENSE_CLIENT_LEGEND_LegendHistoryPageResp=-141228001;	//名将传历史页Resp
const int SCENSE_CLIENT_LEGEND_LegendBaseInfoReq=141228002;	//基础信息Req
const int SCENSE_CLIENT_LEGEND_LegendBaseInfoResp=-141228002;	//基础信息Resp
const int SCENSE_CLIENT_LEGEND_LegendActivityPageReq=141228003;	//活动Req
const int SCENSE_CLIENT_LEGEND_LegendActivityPageResp=-141228003;	//活动Resp
const int SCENSE_CLIENT_LEGEND_LegendBossPageReq=141228004;	//列表页Req
const int SCENSE_CLIENT_LEGEND_LegendBossPageResp=-141228004;	//列表页Resp
const int SCENSE_CLIENT_LEGEND_LegendBossCompletePageReq=141228005;	//Boss完成列表页Req
const int SCENSE_CLIENT_LEGEND_LegendBossCompletePageResp=-141228005;	//Boss完成列表页Resp
const int SCENSE_CLIENT_LEGEND_LegendRewardReq=141228006;	//领取奖励Req
const int SCENSE_CLIENT_LEGEND_LegendRewardResp=-141228006;	//领取奖励Resp
const int SCENSE_CLIENT_LEGEND_LegendRewardPageReq=141228007;	//奖励页Req
const int SCENSE_CLIENT_LEGEND_LegendRewardPageResp=-141228007;	//奖励页Resp
const int SCENSE_CLIENT_LEGEND_LegendRankFinalPageReq=141228008;	//名将传综合排名
const int SCENSE_CLIENT_LEGEND_LegendRankFinalPageResp=-141228008;	//名将传综合排名
const int SCENSE_CLIENT_LEGEND_LegendRankTodayPageReq=141228009;	//名将传每日排名
const int SCENSE_CLIENT_LEGEND_LegendRankTodayPageResp=-141228009;	//名将传每日排名
const int SCENSE_CLIENT_LEGEND_LegendTouchBossReq=141228010;	//触发bossReq
const int SCENSE_CLIENT_LEGEND_LegendTouchBossResp=-141228010;	//触发bossResp0
const int SCENSE_CLIENT_LEGEND_LegendBattlePageReq=141228011;	//战斗页Req
const int SCENSE_CLIENT_LEGEND_LegendBattlePageResp=-141228011;	//战斗页Resp
const int SCENSE_CLIENT_LEGEND_LegendStartBattleReq=141228012;	//名将传开始战斗
const int SCENSE_CLIENT_LEGEND_LegendStartBattleResp=-141228012;	//名将传开始战斗
const int SCENSE_CLIENT_LEGEND_LegendEndBattleReq=141228013;	//结束战斗Req
const int SCENSE_CLIENT_LEGEND_LegendEndBattleResp=-141228013;	//结束战斗Resp
const int SCENSE_CLIENT_LEGEND_LegendMyFriendPageReq=141228016;	//我的好友页Req
const int SCENSE_CLIENT_LEGEND_LegendMyFriendPageResp=-141228016;	//我的好友页Resp
const int SCENSE_CLIENT_LEGEND_LegendShareBossReq=141228017;	//分享BossReq
const int SCENSE_CLIENT_LEGEND_LegendShareBossResp=-141228017;	//分享BossResp
const int SCENSE_CLIENT_LEGEND_LegendRestoreAttackCountPageReq=141228018;	//恢复挑战次数页Req
const int SCENSE_CLIENT_LEGEND_LegendRestoreAttackCountPageResp=-141228018;	//恢复挑战次数页Resp

const int SCENSE_CLIENT_ACCOUNT_RedPointReq=141201008;	//红点触发Req
const int SCENSE_CLIENT_ACCOUNT_RedPointResp=-141201008;	//红点触发Resp


// 竞技场 code:30
const int SCENSE_CLIENT_ARENA_ArenaPageReq=141230001;	//竞技场列表页Req
const int SCENSE_CLIENT_ARENA_ArenaPageResp=-141230001;	//竞技场列表页Resp
const int SCENSE_CLIENT_ARENA_ArenaLineupHeroPageReq=141230002;	//上阵列表页Req
const int SCENSE_CLIENT_ARENA_ArenaLineupHeroPageResp=-141230002;	//上阵列表页Resp
const int SCENSE_CLIENT_ARENA_ArenaStartBattleReq=141230003;	//开始战斗Req
const int SCENSE_CLIENT_ARENA_ArenaStartBattleResp=-141230003;	//开始战斗Resp
const int SCENSE_CLIENT_ARENA_ArenaEndBattleReq=141230004;	//结束战斗Req
const int SCENSE_CLIENT_ARENA_ArenaEndBattleResp=-141230004;	//结束战斗Resp
const int SCENSE_CLIENT_ARENA_ArenaRankPageReq=141230005;	//排行榜Req
const int SCENSE_CLIENT_ARENA_ArenaRankPageResp=-141230005;	//排行榜Resp
const int SCENSE_CLIENT_ARENA_ArenaBattleRecordPageReq=141230006;	//对战记录Req
const int SCENSE_CLIENT_ARENA_ArenaBattleRecordPageResp=-141230006;	//对战记录Resp
const int SCENSE_CLIENT_ARENA_ArenaGloryShopReq=141230007;	//荣誉商店Req
const int SCENSE_CLIENT_ARENA_ArenaGloryShopResp=-141230007;	//荣誉商店Resp
const int SCENSE_CLIENT_ARENA_ArenaRewardReq=141230008;	//领取奖励Req
const int SCENSE_CLIENT_ARENA_ArenaRewardResp=-141230008;	//领取奖励Resp
const int SCENSE_CLIENT_ARENA_ArenaBuyReq=141230009;	//购买次数Req
const int SCENSE_CLIENT_ARENA_ArenaBuyResp=-141230009;	//购买次数Resp
const int SCENSE_CLIENT_ARENA_ArenaExchangeReq=141230010;	//兑换Req
const int SCENSE_CLIENT_ARENA_ArenaExchangeResp=-141230010;	//兑换Resp
const int SCENSE_CLIENT_ARENA_ArenaDayRewardCountDownReq=141230011;	//当日发放奖励倒计时Req
const int SCENSE_CLIENT_ARENA_ArenaDayRewardCountDownResp=-141230011;	//当日发放奖励倒计时Resp
const int SCENSE_CLIENT_ARENA_ArenaDayRewardReq=141230012;	//当日发放奖励Req
const int SCENSE_CLIENT_ARENA_ArenaDayRewardResp=-141230012;	//当日发放奖励Resp
const int SCENSE_CLIENT_ARENA_ArenaLookUpRoleInfoReq=141230013;	//查看角色信息Req
const int SCENSE_CLIENT_ARENA_ArenaLookUpRoleInfoResp=-141230013;	//查看角色信息Resp

//购买体力
const int SCENSE_CLIENT_ACCOUNT_BuyPowerPageReq=141201011;	//购买体力页Req
const int SCENSE_CLIENT_ACCOUNT_BuyPowerPageResp=-141201011;	//购买体力页Resp
const int SCENSE_CLIENT_ACCOUNT_BuyPowerReq=141201012;	//购买体力Req
const int SCENSE_CLIENT_ACCOUNT_BuyPowerResp=-141201012;	//购买体力Resp

//运镖
const int SCENSE_CLIENT_Gemstone_GemstonePageReq = 141240001;  //查看矿车页
const int SCENSE_CLIENT_Gemstone_GemstonePageResp =  -141240001; //查看矿车页
const int SCENSE_CLIENT_Gemstone_GemstoneGrabReq  = 141240002;  //抢夺
const int SCENSE_CLIENT_Gemstone_GemstoneGrabResp =  -141240002; //抢夺

#endif
