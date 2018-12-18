//
//  RotateMenu.h
//  FightPass
//
//  Created by chenyanbin on 15/6/24.
//
//

#ifndef __FightPass__RotateMenu__
#define __FightPass__RotateMenu__

#include "cocos2d.h"
#include "../../BaseLayer.h"
class RotateMenu :public BaseLayer{
public:
    RotateMenu();
    ~RotateMenu();
    //构造方法
    CREATE_FUNC(RotateMenu);
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
    
    void  onMsgProcess(EventCustom* msg);
    virtual void addEventListener();
    virtual void removeEventListener();
    
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
    bool isturn;//是否滑动
    
    

    
};

#endif /* defined(__FightPass__RotateMenu__) */
