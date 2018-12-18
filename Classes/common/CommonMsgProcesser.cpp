//
//  CommonMsgProcesser.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/8/15.
//
//

#include "CommonMsgProcesser.h"
#include "../module/login/LoginLayer.h"
#include "../module/chapter/ChapterLayer.h"
#include "../common/Dialog/Dialog.h"
#include "../module/battle/BattleLoader.h"
#include "../protocol/UserCustomEvent.h"
#include "../module/raidsLayer/RaidsLayer.h"
#include "../commonData/enum/DictRolePropEnum.h"
#include "../common/noticeManager/NoticeManager.h"
#include "../module/sweep/SweepLayer.h"
#include "../module/homeUI/HomeLoader.h"
#include "../module/musou/MusouLayer.h"
#include "../sdk/SdkManager.h"
#include "../common/GameConfig.h"
#include "../module/newPlayerGuide/NewPlayerGuild.h"
#include "../commonData/data/FunctionOpenManager.h"
#include "../YVSDK/YVSDK.h"
#include "../commonData/enum/DictItemTypeEnum.h"
#include "../module/awardBox/AwardBox_Layer.h"
#include "../tdTalkData/TDTalkDataManager.hpp"
#include "CustomMsgProcesser.h"
#include "../protocol/CustomProtocal.hpp"
#include "../module/famousGeneral/famouseBossCome/FamouseBossCome.hpp"
#include "../net/NetworkDataProcessing.h"
#include "../module/marquee/MarqueeManager.h"
#include "../module/stageBattleInfo/StageBattleInfo.hpp"
#include "../module/createRole/CreateRole.hpp"
void CommonMsgProcesser::onMsgProcess(MessageReceive* msg)
{
    Dialog::hideServerLoading();

    ByteStream* byteStream = msg->byteStream;
   if(msg->messageID == SCENSE_CLIENT_BATTLE_ChapterPageResp)
   {
     
       
       Scene* scene = Director::getInstance()->getRunningScene();
       ChapterLayer* layer = (ChapterLayer*)scene->getChildByTag(SCENE_TAG_CHAPTER);
       if(msg->state == false)
       {
           GlobalInfo::getInstance()->stageMode = kStageModeCommon;
           PublicShowUI::broadUserMsg(CUSTOM_RESET_CHAPTER_TYPE,NULL);
           return;
       }
       if(!layer)
       {
           layer = ChapterLayer::show();
       }
     
       layer->setSelectedChapter(byteStream);
   }
   else if(msg->messageID == SCENE_CLIENT_LOGIN_BACK)
   {
       if(!msg->state)
       {
           NetworkDataProcessing::getInstance()->closeNet();
           Dialog::show(msg->debugMsg.c_str());
           return;
       }
       //        uid	用户id	long	Y
       //        roleId	角色ID	long	Y	0 角色未创建
       //        gameSessionId	游戏服务器sessionId	string	Y	第二次连接传入次sessionId, 无需passport验证
       //        需要保存在客户端全局变量中，客户端重启清空此变量。
       long long uid = msg->byteStream->getLong();
       long long roleId = msg->byteStream->getLong();
       string nickName = msg->byteStream->getUTF8();
       string session = msg->byteStream->getUTF8();
       
       GlobalInfo::getInstance()->uid = PublicShowUI::numberToString(uid);
       GlobalInfo::getInstance()->gameRole->roleID = roleId;
       GlobalInfo::getInstance()->gameRole->name = nickName;
       
       GlobalInfo::getInstance()->gameSessionId = session;
       bool isInNewVillage = msg->byteStream->getByte();
       bool isFirstIn = msg->byteStream->getByte();
       
       GlobalInfo::getInstance()->isInNewVillage = isInNewVillage;
       GlobalInfo::getInstance()->isNewEnterGame = isFirstIn;
       
       int len = msg->byteStream->getByte();
    
       for(int i = 0; i < len; i++)
       {
        
           FunctionOpenManager::getInstance()->setFunctionStatus(i+1, msg->byteStream->getByte());
       }
       len = msg->byteStream->getByte();
        std::vector<int> funtionList ;
       
       for(int i = 0; i < len; i++)
       {
           funtionList.push_back(msg->byteStream->get());
       }
        len = msg->byteStream->getByte();
       std::vector<int> stepList;
       for(int i = 0; i < len; i++)
       {
           stepList.push_back(msg->byteStream->get());
       }
       for(int i = 0; i < len; i++)
       {
           NewPlayerGuild::getInstance()->addFunction(funtionList[i],stepList[i]);
       }
       if(!NetworkDataProcessing::getInstance()->isReconnect)
       {
           GlobalInfo::getInstance()->isFirstEnterMainScene = true;
           
           if(nickName == "")
           {
               CreateRole::show();
           }
           else
           {
                onStartLogin();
           }
        
       }
   }
   else if(msg->messageID == SCENSE_CLIENT_ACCOUNT_RoleInfoResp)
   {
       if(!msg->state)
       {
           return;
       }
       
       long long roleID = byteStream->getLong();
       string roleName = byteStream->getUTF8();
       int level = byteStream->getInt();
       int vipLevel = byteStream->getInt();
       int exp = byteStream->getInt();
       int vipExp = byteStream->getInt();
       int power=byteStream->getInt();
       int bodyPower = byteStream->getInt();
       int powerMax = byteStream->getInt();
       int coin = byteStream->getInt();
       int gold = byteStream->getInt();
       int glory = byteStream->getInt();//荣誉
       int honory = byteStream->getInt();//军功
       
       
       int curHeroCount = byteStream->getShort();
       int totalHeroCount = byteStream->getShort();
       int curEquipCount = byteStream->getShort();
       int equipCountLimit = byteStream->getShort();
       string userHead = byteStream->getUTF8();
       
       GlobalInfo::getInstance()->curHeroCount = curHeroCount;
       GlobalInfo::getInstance()->maxHeroCount = totalHeroCount;
       GlobalInfo::getInstance()->curEquipCount = curEquipCount;
       GlobalInfo::getInstance()->equipCountLimit = equipCountLimit;
        GlobalInfo::getInstance()->gameRole->expLoit = honory;
       GlobalInfo::getInstance()->gameRole->glory = glory;
       
       GlobalInfo::getInstance()->gameRole->roleID = roleID;
       GlobalInfo::getInstance()->gameRole->name = roleName;
       GlobalInfo::getInstance()->gameRole->level = level;
       GlobalInfo::getInstance()->vipLevel = vipLevel;
       GlobalInfo::getInstance()->gameRole->experience = exp;
       GlobalInfo::getInstance()->vipExp = vipExp;
       GlobalInfo::getInstance()->gameRole->combatPower=power;
       GlobalInfo::getInstance()->bodyPower = bodyPower;
       GlobalInfo::getInstance()->bodyPowerMax = powerMax;
       GlobalInfo::getInstance()->userCopper = coin;
       GlobalInfo::getInstance()->userGold = gold;
       GlobalInfo::getInstance()->gameRole->headID  = userHead;//头像url地址
       GlobalInfo::getInstance()->gameRole->mainHeroID = byteStream->getInt();//主将id
       int mainHeroDictID = byteStream->getInt();
       GlobalInfo::getInstance()->gameRole->mainHeroDictID = mainHeroDictID;//主将编号
       GlobalInfo::getInstance()->gameRole->quality = byteStream->getByte();
       string redPointStr = byteStream->getUTF8();//红点
       log("redPointStr=======================%s",redPointStr.c_str());
       GlobalInfo::getInstance()->initDotList(redPointStr);
       GlobalInfo::getInstance()->luckyLeftTime = byteStream->getInt();//祈福剩余时间
       
        log("GlobalInfo::getInstance()->luckyLeftTime=======================%d",GlobalInfo::getInstance()->luckyLeftTime);
       Scene* scene = Director::getInstance()->getRunningScene();
       if(scene->getChildByTag(SCENE_TAG_MAINUI))
       {
           return;
       }
       int len = byteStream->get();
       GlobalInfo::getInstance()->mainSceneHeroList->clear();
       RoleData* roleData = NULL;
       for(int i = 0; i < len; i++)
       {
           roleData = new RoleData();
           roleData->autorelease();
           roleData->roleID = i;
           roleData->mainHeroDictID = byteStream->getInt();
           GlobalInfo::getInstance()->mainSceneHeroList->pushBack(roleData);
       }
       int firstREchargeStatus = byteStream->getByte();//首充图标状态
       int sevendayAcativeStatus = byteStream->getByte();//七日图标状态
       GlobalInfo::getInstance()->firstRechargeStatus = firstREchargeStatus;
       GlobalInfo::getInstance()->sevendayActivity = sevendayAcativeStatus;
       
       Director::getInstance()->purgeCachedData();
       if(scene->getChildByTag(SCENE_TAG_LOADING))
       {
           SdkManager::getInstance()->setUserExtData(ENTER_SERVER);
           TDTalkDataManager::getInstance()->setAnncordID();
         
           TDTalkDataManager::getInstance()->setGameServer();
          
           TDTalkDataManager::getInstance()->setAccountType();
       }
       TDTalkDataManager::getInstance()->setAccountName();
       TDTalkDataManager::getInstance()->setLevel();
       
       
    
        HomeLoader::show(SCENE_TAG_LOADING);
     
       
   }
   else if(msg->messageID == SCENSE_CLIENT_BATTLE_StartBattleResp)
   {
       if(msg->state)
       {
           Scene* scene = Director::getInstance()->getRunningScene();
           ChapterLayer* layer = (ChapterLayer*)scene->getChildByTag(SCENE_TAG_CHAPTER);
           if(layer)
           {
               PublicShowUI::broadUserMsg(CUSTOM_ENTER_BATTLE,msg->byteStream);
           }
           else
           {
               BattleLoader::show(byteStream, SCENE_TAG_CHAPTER);
           }
       }
   }
   else if(msg->messageID == SCENSE_CLIENT_MUSOU_MusouStartBattleResp)
   {
       if(msg->state)
       {
           
           BattleLoader::show(byteStream, SCENE_TAG_MUSOU);
       }
   }
   else if(msg->messageID == SCENSE_CLIENT_LEGEND_LegendStartBattleResp)
   {
      
       if(msg->state)
       {
           GlobalInfo::getInstance()->battleType = kBattleType_MingJiangZhuan;
           Scene* scene = Director::getInstance()->getRunningScene();
           if(scene->getChildByTag(SCENE_TAG_FAMOUSE))
           {
                 BattleLoader::show(byteStream, SCENE_TAG_FAMOUSE);
           }
           else
           {
                 BattleLoader::show(byteStream, SCENE_TAG_CHAPTER);
           }
         
       }
       else
       {
           PublicShowUI::broadUserMsg(CUSTOM_BATTLE_QUITBATTLE,__Bool::create(false));
       }
   }
   else if(msg->messageID == SCENSE_CLIENT_BATTLE_SweptResp)
   {
       if(msg->state)
       {
           
          RaidsLayer::show(byteStream);
       }
   }
   else if(msg->messageID == CLIENT_GATE_DisconnectReq)
   {//服务器通知客户端断开连接
       Dialog::show("您被踢下了线，请注意您的帐号安全!");
   }
   else if(msg->messageID == SCENSE_CLIENT_BATTLE_StagePageResp)
   {
    
        if(msg->state)
        {
            StageBattleInfo::show(msg->byteStream);
//            SweepLayer::show(msg->byteStream);
        }
        
   }
   else if(msg->messageID == CLIENT_SCENSE_RolePropUpdateReq || msg->messageID == SCENSE_CLIENT_ADDITION_RolePropUpdateAdditionResp)
   {//通知客户端角色属性数值变
       parseRoleAttribMsg(msg->byteStream);
   }
    else if(msg->messageID == SCENSE_CLIENT_ADDITION_RoleFunctionOpenAdditionResp || msg->messageID == CLIENT_SCENSE_RoleFunctionOpenReq)
    {//通知客户端新功能开启
        parseFunctionOpenMsg(msg->byteStream);
    }
   else if(msg->messageID == SCENSE_CLIENT_MUSOU_MusouPageResp)
   {
       MusouLayer::show(msg->byteStream);
   }
   else if(msg->messageID == SCENSE_CLIENT_PAY_Sdk1PayCreateOrderResp)
   {
       if(msg->state)
       {
           parseRechargeMsg(msg->byteStream);
       }
   }
   else if(msg->messageID == SCENSE_CLIENT_BATTLE_RebornResp)
   {
       if(msg->state)
       {
           PublicShowUI::broadUserMsg(CUSTOM_BATTLE_HERO_REBORNCONFIRM, NULL);
       }
       else
       {
           NoticeManager::getInstance()->showNotice(msg->debugMsg.c_str(),NoticeManager::COLOR_RED);
            PublicShowUI::broadUserMsg(CUSTOM_BATTLE_HERO_REBORNCANCEL, NULL);
       }
   }
   else if(msg->messageID == SCENSE_CLIENT_LEGEND_LegendTouchBossResp)
   {
       //触发了名将来袭
       int bossID = msg->byteStream->getInt();
       int level = msg->byteStream->getShort();
       GlobalInfo::getInstance()->famouseBossID = bossID;
       GlobalInfo::getInstance()->famouseBossLevel = level;
       
       if(GlobalInfo::getInstance()->famouseBossID )
       {
           FamouseBossCome::show();
       }
   }
   else if(msg->messageID == SCENSE_CLIENT_ACCOUNT_MarqueePageResp)
   {//跑马灯列表
       parseMarqueeList(msg->byteStream);
   }
  else if(msg->messageID == CLIENT_GATE_MarqueeNotifyReq)
  {
      parseMarqueeData(msg->byteStream);
  }

   else if(msg->messageID == SCENSE_CLIENT_ACCOUNT_NewGuidePassResp)
   {
       if(GlobalInfo::getInstance()->isDebug)
       {
            NoticeManager::getInstance()->showNotice("通过了新手引导");
       }
    
   }
    else if(msg->messageID == SCENSE_CLIENT_PAY_PayCardReceiveResp)
    {
        //月卡领取返回
    }
    
   

}
void CommonMsgProcesser::parseMarqueeList(ByteStream* byteStream)
{
    int len = byteStream->get();
    MarqueeData* data = NULL;
    for(int i = 0; i <len; i++)
    {
        data = new MarqueeData();
        data->autorelease();
        data->marqueeType = byteStream->getByte();
        data->marqueeID = byteStream->getInt();
        data->content = byteStream->getUTF8();
        data->mode = byteStream->get();
        data->loopTimes = byteStream->getInt();
        data->loopInterval = byteStream->getInt();
        data->loopCount = byteStream->getByte();
        data->dictTipsID = byteStream->getInt();
        MarqueeManager::getInstance()->addContent(data);
    }
}
void CommonMsgProcesser::parseMarqueeData(ByteStream* byteStream)
{
    MarqueeData* data = new MarqueeData();
    data->autorelease();
    data->content = byteStream->getUTF8();
    data->mode = byteStream->get();
    data->marqueeType = byteStream->getByte();
    data->marqueeID = byteStream->getInt();
    data->op = byteStream->getByte();
    data->op = data->op <= 0 ? 1 : data->op;
    data->loopTimes = byteStream->getInt();
    data->loopInterval = byteStream->getInt();
    data->loopCount = byteStream->getByte();
    data->dictTipsID = byteStream->getInt();
    
    MarqueeManager::getInstance()->addContent(data);
}
void CommonMsgProcesser::parseFunctionOpenMsg(ByteStream* byteStream)
{
    int len = byteStream->get();
    int functionId = 0;
    DictFunction* functionOpen = NULL;
    for(int i = 0; i < len ; i++)
    {
        functionId = byteStream->get();
        FunctionOpenManager::getInstance()->setFunctionStatus(functionId, FunctionOpenData::STATUS_OPEN);
        functionOpen = DictFunctionManager::getInstance()->getData(functionId);
        if(!functionOpen)
        {
            continue;
        }
        NoticeManager::getInstance()->showNotice(functionOpen->openingtext.c_str(),NoticeManager::COLOR_GREEN);
        if(functionOpen->battleId > 0 || functionOpen->roleLevel > 0)
        {
            if(functionOpen->resource.size() > 0)
            {
               CustomMsgProcesser::getInstance()->addMessage(CUSTOM_PROTOCAL_FUNCTIONOPEN,functionId);
            }
            
        }
    }
}
void CommonMsgProcesser::parseRechargeMsg(ByteStream* byteStream)
{
    int chargeType = byteStream->get();
    string unitName = byteStream->getUTF8();//物品名称
    int moneyNum = byteStream->getInt();//单位分
    string orderID = PublicShowUI::numberToString(byteStream->getInt());
    string callbackInfo = byteStream->getUTF8();
    string callbackUrl = byteStream->getUTF8();
    
    switch (chargeType)
    {
        case kRecharge_type_gold://元宝充值
        {
            unitName = PublicShowUI::numberToString(moneyNum / 10) + "元宝";//元宝定额支付优惠10倍所以只是除以10
            SdkManager::getInstance()->createOrder(moneyNum , callbackInfo.c_str(),1, unitName.c_str(), callbackUrl.c_str());
            TDTalkDataManager::getInstance()->onChargeRequest(orderID.c_str(), unitName.c_str(), moneyNum / 100,"CNY",moneyNum / 10 , "定额支付");
        }
          
        break;
        case kRecharge_type_monthCard://月卡充值
        {
            unitName = PublicShowUI::numberToString(moneyNum / 100) + "月卡";
            SdkManager::getInstance()->createOrder(moneyNum,callbackInfo.c_str(), 1,unitName.c_str(), callbackUrl.c_str());
            TDTalkDataManager::getInstance()->onChargeRequest(orderID.c_str(), unitName.c_str(), moneyNum / 100,"CNY",moneyNum / 100 * 10 , "定额支付");
        }
           
        break;
        case kRecharge_type_other:
            SdkManager::getInstance()->startCharge(orderID.c_str(), callbackInfo.c_str(), callbackUrl.c_str());
            
            TDTalkDataManager::getInstance()->onChargeRequest(orderID.c_str(), "元宝", 1,"CNY",10, "不定额支付");
            break;
            
        default:
            break;
    }
    
}
void CommonMsgProcesser::onStartLogin()
{
    YVSDK::YVPlatform::getSingletonPtr()->cpLogin(PublicShowUI::numberToString( GlobalInfo::getInstance()->gameRole->roleID), GlobalInfo::getInstance()->gameRole->name);
    LoginLayer::enterMainUI();
    
    
}
void CommonMsgProcesser::parseRoleAttribMsg(ByteStream* byteStream)
{
    int len = byteStream->get();
    int propID = 0;
    int propValue = 0;
    int getValue = 0;
    bool heroCountUpdate = false;
    bool equipCountUpdate = false;
    string str = "";
    Node* inBattle = Director::getInstance()->getRunningScene()->getChildByTag(SCENE_TAG_BATTLE);
    for(int i = 0; i < len; i++)
    {
        str = "获得了";
        propID = byteStream->getByte();
        propValue = byteStream->getInt();
        getValue = 0;
        switch (propID)
        {
            case RoleAttrib_EXP:
                getValue = propValue - GlobalInfo::getInstance()->gameRole->experience;
                GlobalInfo::getInstance()->gameRole->experience = propValue;
                str += "经验";
                break;
            case RoleAttrib_GOLD:
                str += "元宝";
                getValue = propValue - GlobalInfo::getInstance()->userGold;
                GlobalInfo::getInstance()->userGold = propValue;
                if(getValue > 0)
                {
                    TDTalkDataManager::getInstance()->onReward(getValue, "服务器更新元宝");
                }
                else if(getValue < 0)
                {//消费铜币
                    TDTalkDataManager::getInstance()->onUse("元宝", abs(getValue));
                }
                break;
            case RoleAttrib_COIN:
                str += "铜币";
                getValue = propValue - GlobalInfo::getInstance()->userCopper;
                GlobalInfo::getInstance()->userCopper = propValue;
                if(getValue > 0)
                {
                    TDTalkDataManager::getInstance()->onReward(getValue, "服务器更新铜币");
                }
                else if(getValue < 0)
                {//消费铜币
                    TDTalkDataManager::getInstance()->onUse("铜币", abs(getValue));
                }
                break;
            case RoleAttrib_POWER:
                str += "体力";
                getValue = propValue - GlobalInfo::getInstance()->bodyPower;
                GlobalInfo::getInstance()->bodyPower = propValue;
                break;
            case RoleAttrib_GLORY://荣誉
                str += "荣誉";
                getValue = propValue - GlobalInfo::getInstance()->gameRole->glory;
                GlobalInfo::getInstance()->gameRole->glory = propValue;
                break;
            case RoleAttrib_Honor://军功
                str += "军功";
                getValue = propValue - GlobalInfo::getInstance()->gameRole->expLoit;
                GlobalInfo::getInstance()->gameRole->expLoit = propValue;
                break;
            case RoleAttrib_Level://等级
                str = "恭喜您升级了";
                if(propValue != GlobalInfo::getInstance()->gameRole->level)
                {
                 
//                      NoticeManager::getInstance()->showNotice(str.c_str(),NoticeManager::COLOR_GREEN);
                }
                onUserLevelUp(propValue, GlobalInfo::getInstance()->gameRole->level);
                GlobalInfo::getInstance()->gameRole->level = propValue;
                return;
            case RoleAttrib_VIPLevel:
                if( GlobalInfo::getInstance()->vipLevel != propValue)
                {
                    str = "您的vip等级升为VIP:";
                    getValue = propValue;
                    GlobalInfo::getInstance()->vipLevel = propValue;
                    PublicShowUI::broadUserMsg(CUSTOM_UPDATE_VIP_LEVEL, NULL);
                }
                else
                {
                    getValue = 0;
                }
               
                break;
            case RoleAttrib_VIPExp:
                str += "vip经验";
                if(GlobalInfo::getInstance()->vipExp != propValue)
                {
                    getValue = propValue - GlobalInfo::getInstance()->vipExp;
                    GlobalInfo::getInstance()->vipExp = propValue;
                    PublicShowUI::broadUserMsg(CUSTOM_UPDATE_VIP_LEVEL, NULL);
                }
                else
                {
                    getValue = 0;
                }
                
                break;
            case RoleAttrib_CurHeroCount:
                GlobalInfo::getInstance()->curHeroCount = propValue;
                heroCountUpdate = true;
                break;
            case RoleAttrib_HeroCountLimt:
                GlobalInfo::getInstance()->maxHeroCount = propValue;
                heroCountUpdate = true;
                break;
            case RoleAttrib_CurEquipCount:
                GlobalInfo::getInstance()->curEquipCount = propValue;
                equipCountUpdate = true;
                break;
            case RoleAttrib_EquipCountLimt:
                GlobalInfo::getInstance()->equipCountLimit = propValue;
                equipCountUpdate = true;
                break;
            default:
                continue;
                break;
        }
        if(getValue > 0 && !inBattle)
        {
            str += PublicShowUI::numberToString(getValue);
            NoticeManager::getInstance()->showNotice(str.c_str(),NoticeManager::COLOR_GREEN);
        }
       
    }
    PublicShowUI::broadUserMsg(CUSTOM_UPDATE_USERPROP_VALUE, NULL);
    if(heroCountUpdate && GlobalInfo::getInstance()->curHeroCount >= GlobalInfo::getInstance()->maxHeroCount)
    {
        
        Dialog::show("您的英雄数量已经达到上限，请清理武将或使用英雄扩充令扩充");
    }
    if(equipCountUpdate && GlobalInfo::getInstance()->curEquipCount >= GlobalInfo::getInstance()->equipCountLimit)
    {
        Dialog::show("您的装备数量已经达到上限，请清理装备或使用装备扩充令扩充");
    }
}

void CommonMsgProcesser::onUserLevelUp(int newLevel,int oldLevel)//玩家升级
{
    
    if(newLevel > oldLevel)
    {
        NewPlayerGuild::getInstance()->onUserLevelUp(newLevel);
        CustomMsgProcesser::getInstance()->addMessage(1000001,newLevel);
        GlobalInfo::getInstance()->gameRole->level = newLevel;
        SdkManager::getInstance()->setUserExtData(LEVELUP);
        PublicShowUI::broadUserMsg(CUSTOM_UPDATE_USERPROP_VALUE, NULL);
       
    }
    TDTalkDataManager::getInstance()->setLevel();
}
