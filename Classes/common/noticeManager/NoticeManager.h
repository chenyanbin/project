//
//  NoticeManager.h
//  SuiTang
//
//  Created by mac on 14-6-4.
//
//

#ifndef __SuiTang__NoticeManager__
#define __SuiTang__NoticeManager__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include <vector>
#include "../../module/data/BaseTypeData.h"
#include "../../VisibleRect.h"
class NoticeMsg:public Ref
{
public:
    NoticeMsg():content(""),fontSize(26),showBg(true)
    {
        
    }
    string content;
    Color3B color;
    Point fromCp;
    Point toCp;
    int fontSize;
    bool showBg;
};

class NoticeManager:public Node
{
public:
    enum
    {
        COLOR_WHITE = 1,
        COLOR_YELLOW = 2,
        COLOR_GREEN = 3,
        COLOR_RED = 4
    };
    NoticeManager();
    ~NoticeManager();
    void showNotice(const char* content,int colorFlag = 4);
    void showNotice(const char* content,int colorFlag, Point fromCp,Point toCp,int fontSize,bool showBg);
    void showNotice(Vector<BaseTypeData*> m_baseList);
    void showNoOpenFunctionNotice(int functionID);
    void showDictTipsMsg(int dictTipsID);
//    显示弹框提示， dialogID为弹框标识
    void showConfirmDialog(const char* content,int dialogID = 0);
    static NoticeManager* getInstance();
private:
    void onMoveEnd();
    void start();
    void stop();
    void update(float dt);
    void onDialogBack(Node* pSender);
private:
//    queue<string>* msgList;
//    queue<Color3B>* colorList;
    queue<Sprite*>* spriteList;
    queue<NoticeMsg*>* msgList;
    static NoticeManager* _instance;
    bool isStart;
    
    int m_dialogID;
};

#endif /* defined(__SuiTang__NoticeManager__) */
