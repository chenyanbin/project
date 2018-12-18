//
//  GuideContent.h
//  SuiTang
//引导内容框
//  Created by zhangxiaobin on 14-9-17.
//
//

#ifndef __SuiTang__GuideContent__
#define __SuiTang__GuideContent__

#include "../BaseLayer.h"
#include "../../commonData/dictData/DictNewGuide/DictNewGuideManager.h"
#include "../../common/commonEffect/CommonEffect.h"
class GuideContent:public BaseLayer
{
public:
    GuideContent();
    ~GuideContent();
    virtual bool init();
    CREATE_FUNC(GuideContent);
    
    void updateGuideData(DictNewGuide* data);
    void showGuider();//显示新手引导人
private:
    void updateContent();
    void setPlayerGuilderPosition();
    void setGotoBtn();//前往按钮
    void onBtnClick(Ref* pSender);
    
private:
    DictNewGuide* m_data;
    Sprite* playerGuilder;
    float playerScale;
    int heroID;
    int TAG_LABEL;
    int TAG_HAlFBODY;
    int TAG_GOTOBTN;
    
};

#endif /* defined(__SuiTang__GuideContent__) */
