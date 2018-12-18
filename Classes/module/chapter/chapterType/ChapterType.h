//
//  ChapterType.h
//  FightPass
//
//  Created by zhangxiaobin on 15/8/17.
//
//

#ifndef __FightPass__ChapterType__
#define __FightPass__ChapterType__
#include "cocos2d.h"
USING_NS_CC;
class ChapterType:public Layer
{
public:
    ChapterType();
    ~ChapterType();
    virtual bool init();
    CREATE_FUNC(ChapterType);
protected:
    virtual void onEnter();
    virtual void onExit();
    void onMsgProcess(EventCustom* message);
private:
    void setBg();
    void setComBoBtn();
    void onBtnClick(Ref* pSender);
private:
//    Sprite* m_selectedEffect;
private:
    int TAG_COMBOBTN;
    int TAG_SELECTEFFECT;
};

#endif /* defined(__FightPass__ChapterType__) */
