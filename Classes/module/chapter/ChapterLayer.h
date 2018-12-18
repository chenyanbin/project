//
//  ChapterLayer.h
//  FightPass
//章节模块
//  Created by chenyanbin on 15/7/29.
//
//

#ifndef __FightPass__ChapterLayer__
#define __FightPass__ChapterLayer__
#include "cocos2d.h"
#include "../BaseLayer.h"
#include "../../commonData/dictData/DictChapter/DictChapterManager.h"
#include "Chapter.h"
#include "editor-support/cocostudio/CCArmature.h"
using namespace cocostudio;
#define CLOUND_EFFECT "yundonghua"
class ChapterLayer:public BaseLayer
{
public:
    ChapterLayer();
    ~ChapterLayer();
    virtual bool init();
    static ChapterLayer* create();
    static ChapterLayer* show();
    static void requestChapterByID(int chapterID = 0);
    static void requestStageBattle(int stageID,StageMode stageMode);//打开关卡
    void setSelectedChapter(ByteStream* byteStream);
    
    void onLastStage(int chapterID);
    void noLastStage();
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
private:
    void showStageBattle();
    void setMask();
    void onMsgProcess(EventCustom* msg);
    void setChapterList();
    void onChapterClick(Ref* pSender);
    void enterChapter(int index);
    void showChapterType();
    void topLayer();//顶部层
    void onShowFun(EventCustom* msg);
    void onHideFun(EventCustom* msg);
    void loadClundEffect();
    void onCloundInit(float percent);
    void onNextChapter(int chapterID);
    void onCloundPlayEnded(Armature *armature, MovementEventType type, const std::string& name);
private:
    Vector<DictChapter*>* chapterList;
    Chapter* m_chapter;
    Point clickPoint;
    int m_nowIndex;
    bool isLastPage;//是否最后一页
public:
    
    Armature* _cloundArmature;//云动画
private:
    int TAG_USERWEALTH;
    int TAG_CHAPTERLIST;
};




#endif /* defined(__FightPass__ChapterLayer__) */
