//
//  PageNode.h
//  SuiTang
//
//  Created by zhangxiaobin on 14-7-8.
//
//

#ifndef __SuiTang__PageNode__
#define __SuiTang__PageNode__

#include "cocos2d.h"
USING_NS_CC;
class PageNode:public Node
{
public:
    ~PageNode();
    bool init(int totalPage,int curPage);
    static PageNode* create(int totalPage,int curPage);
    static PageNode* create(int totalPage);
    
    void setCurPage(int page);
private:
    void initDots();
protected:
    PageNode();
    
private:
    int m_totalPage;
    int m_curPage;
};

#endif /* defined(__SuiTang__PageNode__) */
