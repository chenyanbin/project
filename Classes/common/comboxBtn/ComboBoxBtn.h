//
//  ComboBoxBtn.h
//  SuiTang
//组合框按钮
//  Created by zhangxiaobin on 15/1/30.
//
//

#ifndef __SuiTang__ComboBoxBtn__
#define __SuiTang__ComboBoxBtn__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "../customButton/CustomButton.hpp"

class ComboBoxBtn:public Node
{
public:
     enum class ASIDE
    {
        ASIDE_HORIZONTAL = 0,//行排列
        ASIDE_VERTICAL,///竖排列
    };
    enum class ALIGN
    {
        ALIGN_UP = 0,//上对齐
        ALIGN_CENT,//中间对齐
        ALIGN_DOWN,//底部对齐
        ALIGN_LEFT,//左对齐
        ALIGN_RIGHT,//右对齐
        
    };
    
    ComboBoxBtn();
    ~ComboBoxBtn();
    bool init(ASIDE aside,float distance,const ccMenuCallback& callback, ALIGN align);
    //定制按钮，标题有选中效果
    CustomButton* addCustomBtn(const std::string&normalImage, const std::string&selectedImage,const string& normalTitleImage,const string& selectedTitleImage,bool isScale = false,int tag = -1);
    //抬起，按下，和标题
    CustomButton* addBtn(const std::string&normalImage, const std::string&selectedImage,const string& titleImage,bool isScale = false,int tag = -1);//按钮标题文字
    //排列距离（排列方式，间距，整体回调）
    static ComboBoxBtn* create(ASIDE aside, float distance,const ccMenuCallback& callback, ALIGN align=ALIGN::ALIGN_DOWN);
    
    
    
    //给第几个按钮添加红点
    void addRedPointAt(int index);
    void removePointAt(int index);
    void selectedAt(int index);
    void selectAtByTag(int tag);
    void resetAllBtn();
    Button* getButtonAt(int index);
    Button* getNowSelected();
    Button* getButtonByTag(int tag);
private:
    
    void onComBtnClick(Ref* pSender);
    void onBtnOutSide(Ref* pSender);
private:
    Vector<Button*>* btnList;
 
    ccMenuCallback m_callBack;
    ASIDE m_asideType;//排列方式
    float m_distance;
    ALIGN m_alignType;//对齐方式
    
    Button* m_selectedBtn;
    
private:
    int TAG_REDPOINT;
};

#endif /* defined(__SuiTang__ComboBoxBtn__) */
