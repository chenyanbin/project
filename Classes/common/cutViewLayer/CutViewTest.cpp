//
//  CutViewTest.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 14-7-28.
//
//

#include "CutViewTest.h"
CutViewTest::CutViewTest()
{
    
}
CutViewTest::~CutViewTest()
{
    
}
bool CutViewTest::init()
{
    CutViewLayer::init();
    this->setCutRect(Rect(200,50,700,100));
    
    Label* label = Label::create();
    label->setAnchorPoint(Point::ZERO);
    label->setString("test test test test");
    label->setSystemFontSize(30);
    this->addChild(label);
    label->setPosition(200, 50);
    
    MoveTo* moveto = MoveTo::create(5, Point(900,50));
    label->runAction(moveto);
    
    return true;
}