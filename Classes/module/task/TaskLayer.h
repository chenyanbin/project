//
//  TaskLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/8/17.
//
//

#ifndef __FightPass__TaskLayer__
#define __FightPass__TaskLayer__

#include "cocos2d.h"
#include "../BaseLayer.h"
#include "../../common/comboxBtn/ComboBoxBtn.h"
class TaskLayer:public BaseLayer
{
public:
    enum TAG_LAYER
    {
        TAG_XUANSHANG = 10,
        TAG_RICHANG,
        TAG_PUTONG
    };
    TaskLayer();
    ~TaskLayer();
    virtual bool init(int openLayer);
    static TaskLayer* create(int openLayer);
    static void show(int fromScene,int openLayer);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void setbackGround();
    void setUserWealth();
    void setRightBtn();
    void onRightBtnClick(Ref* psender);
   
    void addPutongLayer();
    void addRichangLayer();
    void addXuansahngLayer();
    
    void onRefreshDot(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
private:
    int m_tagLayer;
    int TAG_NAMEBG;
    int TAG_RIGHTBTN;
    
 };

#endif /* defined(__FightPass__TaskLayer__) */
