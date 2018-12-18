//
//  PublicShowUI.h
//  TwoMahjong
//
//  Created by mac on 14-4-27.
//
//

#ifndef __TwoMahjong__PublicShowUI__
#define __TwoMahjong__PublicShowUI__

#include "cocos2d.h"
USING_NS_CC;
#include <network/HttpRequest.h>
#include <network/HttpResponse.h>
#include <network/HttpClient.h>
#include "../commonData/dictData/DictItemHero/DictItemHeroManager.h"
#include "../commonData/GlobalInfo.h"

#define httpresponse_selector(_SELECTOR) (cocos2d::network::SEL_HttpResponse)(&_SELECTOR)
using namespace std;
static const int INCH_1 = 1;
//4英寸屏第二套图
static const int INCH_2 = 2;
//市面大部分尺寸
static const int INCH_3 = 3;
//MAX英寸屏高清套图
static const int INCH_MAX = 4;
class PublicShowUI
{
public:
    //将目标拉伸满屏幕
    static Sprite* setTagScale(Sprite* tagSprite);
    static float getTagScale(Node* tagSprite);
    static Color3B getColor3b(unsigned long color);
    static Color4B getColor4b(unsigned long color);
    static const char* getAvatarPath(const char* formatPre,const char* content);
    static const char* getResImgPath(const char* formatPre,const char* content);
    static int getInch();
    //target 目标对象  isLashen是否按场景比例拉伸 isSetContentSize 是否重设contentsize
    static void setTargetScale(Node* target,bool isLashen = false,bool isSetContentSize = true);
    static Rect getRect(Node* spr);
    static string numberToTwoDecimalPlaces(float number);
    static string numberToString(int number);
    static string numberToString(long number);
    static string numberToString(long long number);
    static string numberToString(double number);
    static string numberToString(float number,int len = 1);
    static string numberToBigNumString(int number);
    static long stringToNumber(string str);
    static unsigned long hexToULong(string str);
    //自动补零的字符串。size 为字符串长度
    static string numberToString(long number,int size);
    static float getFloorNumber(float number);
    static string getEquipProerty(int num);
    static string getEquipParts(int num);
    //isShadow 是否有阴影
    //isAutoScale是否自适应屏幕大小
    static Label* getLabel(const char* labelText,Color3B color = Color3B::WHITE,int fontSize = 12,bool isShadow = false ,bool isAutoScale = true,Size _size=Size::ZERO,TextHAlignment hAlignment=TextHAlignment::LEFT);

    //
    static Label* getLabelNumber(const char* labelText,Color3B color,int fontSize,bool isShadow,bool isAutoScale);
    static Sprite* getAttribLabel(const char* title,const char* value,Color3B titleColor = Color3B::RED,Color3B valueColor = Color3B::BLACK,bool shadow = false,int titleSize = 18,int valueSize=18,bool isAutoScale = true);
    
	static const char* converToChinese(const char* str);
    static const char* getString(const string& name);
    static Sprite* getBloodNumber(float value);
    static Node* getNumbers(int value,const char* numberPath = NULL,bool isGray = false,int space = 0);
    static Node* getVipLevelImage(int level);
    static void setGray(Sprite* node);
    static Sprite* AddColorGray(Sprite * spr);
    static void setDot(Node* target,Point point,bool bol,int functionId1 = 0,int functionId2 = 0,int functionId3 = 0,int functionId4 = 0,int functionId5 = 0,int functionId6 = 0);
    static void refreshDot(Node* target,Point point,int functionId1 = 0,int functionId2 = 0,int functionId3 = 0);
    
    static void RemoveColorGray(Sprite * spr);
    
    //根据战斗属性id获得string（普攻，技攻～）
    static string getAttfribName(int attfribId);
    //根据英雄id 获得职业id
    static int getOccupationId(int heroId);
    //根据质量得到道具名字颜色
    static Color3B getNameColor(int dictItemTypeID,int quality);
    //根据品质得到颜色下标
    static int getColorIndexByQuality(int dictItemTypeID,int quality);
    
    //装备框颜色
    static int  getItemColorIndexByQuality(int itemId,int quality);
   
    //根据属性类型，和属性值，得到是否带%的值
    static string getAttributeVaule(int type,float vaule);
    //根据数量，得到换算后的整数 100000（10万）
    static char* getUpperlimit(long price);
    //根据职业id得到职业。
    //根据头衔id获得颜色
    static Color3B getTitleColor3B(int titleId);
    //让某个物品摇动
    static void setTargetSwing(Node* target);
    static void stopTargetSwing(Node* target);
    //根据剩余毫秒数，获得剩余时分秒(参数一毫秒数，参数二 返回的最大是 小时还是分钟还是秒)
    static string getTime(long time,int type = 3);
    //根据string参数的里面有没有%决定是否需要*100
    static string  getStringConVal(string conVal,const char* st);
//    //刷物品(数量 ， 类型 ，id ，用户名)
//    static void getItem(int conVal = 50, int conTypeId = DictConTypedictBaseProp,int ccountId = DictBasePropyuanbao, string platformID = GlobalInfo::getInstance()->platformID);
    static void setCameraDistance(float distance);
        
    static int genRandom(int min, int max);
    
    static RenderTexture* createStroke(Sprite* label, int size, Color3B color, GLubyte opacity);
    static const char* makeJosnData(const char* keystr,const char* value);//格式化json数据
    
    static Node* getAvatarHead(const char* name,int level,int prestige);
    static const char* getGoods(int typeId,int id);
    static const char* getName(int typeID,int id);
    static string getItemType(int typeId,int id);
    static string getDescription(int typeId,int id);
    static DictItemHero* getItemHeroByDictId(int id);
    static int getQuality(int typeId,int id);

    static Node* getIconByTypeID(int typeID,int id,int quality);
    
    static bool getProbability(int value);//得到某个范围的几率
    static string getUUID();
    static string getSelfChannelLabel();//得到自已渠道的不同标识
    static void broadUserMsg(const char* msg,void* userData);
};

#endif /* defined(__TwoMahjong__PublicShowUI__) */
