//
//  Chapter.h
//  FightPass
//
//  Created by zhangxiaobin on 15/8/8.
//每一章的内容
//

#ifndef __FightPass__Chapter__
#define __FightPass__Chapter__

#include "cocos2d.h"
USING_NS_CC;
#include "../../commonData/dictData/DictChapter/DictChapterManager.h"
#include "../../commonData/dictData/DictStage/DictStageManager.h"
#include "../../commonData/dictData/DictStageBuilding/DictStageBuildingManager.h"
#include "../../net/bytestream.h"


class StageStarData:public Ref
{
public:
    StageStarData():_stageID(0),star(0),state(0)
    {
        starList = new vector<int>();
    }
    ~StageStarData()
    {
        starList->clear();
        CC_SAFE_DELETE(starList);
        starList = NULL;
    }
    int _stageID;
    int star;
    int state;//1 通过   2 可进入 3 不可进入
    vector<int>* starList;
  
};
class StageBoxData:public Ref
{
public:
    enum
    {
        BOX_STATE_OPENED = 1,//已开
        BOX_STATE_NOOPEN = 2,//不可开
        BOX_STATE_ABLED = 3//可开
    };
    StageBoxData():_boxID(0),_state(0),requireStarCount(0)
    {
        
    }
    int _boxID;
    int _state;
    int requireStarCount;
};
class Chapter:public Layer
{
public:
    Chapter();
    ~Chapter();
    virtual bool init(int chapterID,ByteStream* bytestream);
    static Chapter* create(int chapterID,ByteStream* bytestream);
    void clear();
    void updateChapterStar(ByteStream* bytestream);//更新章节宝箱
private:
    void parseBytestream(ByteStream* bytestream);
    void setBg();
    void initStageList();
    void setStageBuild(DictStageBuilding* build);
    void setStageNameBtn(DictStage* stage);
    void onStageClick(Ref* pSender);
    void onEnterStageBattle(EventCustom* msg);
    void enterBattle(ByteStream* byteStream);
    void setBoss();
    void onBossLoaded(float percent);
    void setProgress();
    void setStarBox();
    void setStarLevel();//设置星级
    void onRequestChapterStar(Node* pSender);
    void onEffectFinised(int boxid);
protected:
    virtual void onEnter();
    virtual void onExit();
    
private:
    CC_SYNTHESIZE_RETAIN(DictChapter*, _chapter, Chapter);
    Sprite* _background;
    Sprite* _buildLayer;
    Sprite* _stageLayer;//关卡层
    Sprite* _frontLayer;
    Sprite* _skyLayer;
    
   
private:
    int m_nextStage;//下一个要进行的关卡
    int starCountMax;//当前章节最大星数，所有战役可得最大星数和
    int curStarCount;//当前章节已经得星数
    Vector<DictStage*>* stageList;
    Map<int, StageStarData*>* stageStarMap;
    Vector<StageBoxData*>* stageBoxList;
    int TAG_STAR_PROGRESS;
    int TAG_ARROW;
};

#endif /* defined(__FightPass__Chapter__) */
