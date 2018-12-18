//
//  MarketRotateLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/9/28.
//
//

#ifndef __FightPass__MarketRotateLayer__
#define __FightPass__MarketRotateLayer__

#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;

/*
 *模仿乱斗西游主界面的旋转菜单
 */
class RotateDeleate
{
public:

    virtual void tableCellTouched(Ref*) = 0;
    virtual void scrollViewDidScroll(Ref*) = 0;


};
class MarketRotateLayer :public BaseLayer
{
public:
    MarketRotateLayer();
    ~MarketRotateLayer();
    //构造方法
    CREATE_FUNC(MarketRotateLayer);
    //添加菜单项
    void addMenuItem(cocos2d::MenuItem *item);
    void addMenuItem(cocos2d::MenuItem *item, int zOrder);
    void addMenuItem(cocos2d::MenuItem *item, int zOrder, int tag);
    
    //更新位置
    void updatePosition();
    //更新位置，有动画
    void updatePositionWithAnimation();
    //位置矫正  修改角度 forward为移动方向  当超过1/3，进1
    //true 为正向  false 负
    void rectify(bool forward);
    //初始化
    virtual bool init();
    //重置  操作有旋转角度设为0
    void reset();
    int getSelected();
    void setDelegate(RotateDeleate* delegate);
private:
    //监听函数
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
   

    //设置角度 弧度
    void setAngle(float angle);
    float getAngle();
    //设置单位角度 弧度
    void setUnitAngle(float angle);
    float getUnitAngle();
    //滑动距离转换角度,转换策略为  移动半个Menu.width等于_unitAngle
    float disToAngle(float dis);
    //返回被选中的item
    cocos2d::MenuItem * getCurrentItem();
    void onMoveEnded(int nextSelected);
    void clickTurnrRight();
    void clicktTurnLeft();
private:
    //菜单已经旋转角度 弧度
    float _angle;
    //菜单项集合,_children顺序会变化，新建数组保存顺序
    cocos2d::Vector<cocos2d::MenuItem *> _items;
    int m_nowSelectedIndex;
    //单位角度 弧度
    float _unitAngle;
    //动画运行时间
    float animationDuration = 0.2f;
    Point touchBeginPos;
    RotateDeleate* m_delegate;
    int m_index;
    bool m_touch;//触摸滑动
    bool m_isRight;//是否向左
    bool m_ischange;
    bool m_isdianjizhong;
    float sx;
    int oldindex;
    
};


#endif /* defined(__FightPass__MarketRotateLayer__) */
