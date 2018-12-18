//
//  Button.h
//  SuiTang
//
//  Created by zhangxiaobin on 14/10/29.
//
//

#ifndef __SuiTang__Button__
#define __SuiTang__Button__

#include "cocos2d.h"
USING_NS_CC;
#include "../GraySprite/GraySprite.h"

class Button:public Node
{
public:
    
    enum
    {
        STATE_NONE = 0,
        STATE_SELECTED = 1,   //选择状态
        STATE_UNSELECTED = 2,  //未选择状态
        STATE_DISABLED = 3,    //禁用状态
        STATE_PARTDISABLED = 4 //部分禁用状态，只灰，不影响点击
        
    };
    
    Button();
    ~Button();
    virtual bool init(const std::string&normalImage, const std::string&selectedImage, const ccMenuCallback& callback);
    /** creates a menu item with a normal and selected image with a callable object */
    static Button* create(const std::string&normalImage, const std::string&selectedImage, const ccMenuCallback& callback);
    
    virtual void selected();
    virtual void unselected();
    virtual void setEnabled(bool bEnabled,bool isGray = true);
    virtual void setPartEnabled(bool bEnabled);
    virtual void setOpacity(float opacity);
    virtual void updateDisplayedOpacity(GLubyte parentOpacity);
    void disableTouchEvent();//取消点击事件
    void enableTouchEvent();//响应点击事件
    
    void setNormalImage(const std::string& normalImage );
    void setSelectedImage(const std::string& selectedImage );
   
   
    
    inline void setUserData(void* data) { m_userData = data; };
    
    /** Gets user data */
    inline void* getUserData() const { return m_userData; };
    
    
    virtual void setAnchorPoint(const Point& anchorPoint);
    virtual Point getAnchorPoint();
    virtual void setScale(float scale);
    void setScaleX(float scaleX)
    {
        if (_scaleX == scaleX)
            return;
        
        _scaleX = scaleX;
        _transformUpdated = _transformDirty = _inverseDirty = true;
    }
    
    Node* getDisAbleImage();
    Node* getNormalImage();
    Node* getSelectedImage();
    
    EventListenerTouchOneByOne* getTouchListener();
public:
    ccMenuCallback onReleaseOutSide;//在按钮外面释放回调
    ccMenuCallback onTouchPress;//移进按钮
    bool isShowClickSound;//是否播放按钮音效
    
protected:
    virtual bool ccTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void ccTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void ccTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void ccTouchCancelled(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    void hideAll(bool isAction = true);
    bool isClickSprite(cocos2d::Touch* pTouch);
   
protected:
    /** the image used when the item is not selected */
    Node* _normalImage;
    /** the image used when the item is selected */
    Node* _selectedImage;
    /** the image used when the item is disabled */
    Node* _disabledImage;
private:
   
    ccMenuCallback m_callBack;
    
    EventListenerTouchOneByOne* touchListener;
    
    void* m_userData;
    
    int m_state;
    float m_scale;
    bool isBegainThis;//touchdown的时候是否点击的自己
    std::string imagePath;
    Point m_anchorPoint;
    bool m_touchEventIsEnabled;//是否响应点击事件
    float m_selectedScale;
};

#endif /* defined(__SuiTang__Button__) */
