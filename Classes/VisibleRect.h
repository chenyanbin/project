#ifndef __VISIBLERECT_H__
#define __VISIBLERECT_H__

#include "cocos2d.h"
USING_NS_CC;
#include "AppMacros.h"
class VisibleRect
{
public:
    static Rect getVisibleRect();

    static Point left();
    static Point right();
    static Point top();
    static Point bottom();
    static Point center();
    static Point leftTop();
    static Point rightTop();
    static Point leftBottom();
    static Point rightBottom();
//    static Point convertPointToDesign(const Point &point);
private:
    static void lazyInit();
    static Rect s_visibleRect;
};

#endif /* __VISIBLERECT_H__ */
