//
//  MarqueeManager.h
//  SuiTang
//
//  Created by zhangxiaobin on 14/12/27.
//
//

#ifndef __SuiTang__MarqueeManager__
#define __SuiTang__MarqueeManager__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "MarqueeLayer.h"
class MarqueeData:public Ref
{
public:
    MarqueeData():mode(1),content(""),marqueeID(0),op(1),loopTimes(0),loopInterval(0),loopCount(1),marqueeType(1),dictTipsID(0)
    {
        
    }
    ~MarqueeData()
    {
        log("~MarqueeData~MarqueeData");
    }
    short marqueeType;//1,全局跑马灯，所有scense都接收2，单服跑马灯指定单个scense接收，3，系统跑马灯，scense内部产生
    string content;
    short mode;//循环模式 1，只显示一次，2，循环显示，gm发出
    int marqueeID; //消息id
    short op;//针对循环消息的操 1新消息，2删除此id的消息 ，3更新此id的消息
    int loopTimes;//循环持续时间，单位：秒 从当前时间开始，loopTimes秒后停止
    int loopInterval;//循环间隔秒数，每隔这个时间显示一次 单位：秒
    short loopCount;//显示次数 -1无限次数
    int dictTipsID;//DictTips表中的id
};


class MarqueeManager
{
public:
    static MarqueeManager* getInstance();
    void addContent(MarqueeData* data);
    void nextContent();
    void show();
    //请求服务器列表
    void requestMarqueeMsg();
private:
    MarqueeManager();
    ~MarqueeManager();
    void hideMarquee();
    void updataData(MarqueeData* data);
    static MarqueeManager* _instance;
private:
    MarqueeLayer* marqueeLayer;
    Vector<MarqueeData*>* msgList;
    ssize_t m_nowIndex;
//    queue<Color3B>* colorList;
};


#endif /* defined(__SuiTang__MarqueeManager__) */
