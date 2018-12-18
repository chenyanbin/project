//
//  CutViewTest.h
//  SuiTang
//
//  Created by zhangxiaobin on 14-7-28.
//
//

#ifndef __SuiTang__CutViewTest__
#define __SuiTang__CutViewTest__

#include "CutViewLayer.h"
class CutViewTest:public CutViewLayer
{
public:
    CutViewTest();
    ~CutViewTest();
    virtual bool init();
    CREATE_FUNC(CutViewTest);
    
};

#endif /* defined(__SuiTang__CutViewTest__) */
