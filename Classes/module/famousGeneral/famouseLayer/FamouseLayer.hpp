//
//  FamouseLayer.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/7.
//
//

#ifndef FamouseLayer_hpp
#define FamouseLayer_hpp

#include "../../BaseLayer.h"
class FamouseLayer:public BaseLayer
{
public:
   
    FamouseLayer();
    ~FamouseLayer();
    virtual bool init();
    CREATE_FUNC(FamouseLayer);
public:
    void setInitPage(int page);
private:
    void setComboBtn();
    void onComboClick(Ref* pSender);
    void setOrderBtn();
    void onOrderBtnClick(Ref* pSender);
private:
    int TAG_COMBOBTN;
    Node* pageNode;
};

#endif /* FamouseLayer_hpp */
