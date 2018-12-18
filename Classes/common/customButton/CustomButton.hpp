//
//  CustomButton.hpp
//  FightPass
//
//  Created by chenyanbin on 16/1/5.
//
//

#ifndef CustomButton_hpp
#define CustomButton_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "../GraySprite/GraySprite.h"
#include "../TouchSprite/Button.h"
class CustomButton:public Button
{
public:

    CustomButton();
    ~CustomButton();
    virtual bool init(const std::string&normalImage, const std::string&selectedImage, const ccMenuCallback& callback);
    /** creates a menu item with a normal and selected image with a callable object */
    static CustomButton* create(const std::string&normalImage, const std::string&selectedImage, const ccMenuCallback& callback);
    
    void addTitle(const std::string& normalTitle,const std::string& selectedTitle);
    
    void setNormalTitle(const std::string& normalImage );
    void setSelectedTitle(const std::string& selectedImage );
    
    void selected();
    void unselected();
    void setEnabled(bool bEnabled,bool isGray = true);
    void setPartEnabled(bool bEnabled);
    void setOpacity(float opacity);
protected:
    void hideTitles();
private:
    virtual bool ccTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void ccTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void ccTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void ccTouchCancelled(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    /** the image used when the item is not selected */
    Node* _normalTitle;
    /** the image used when the item is selected */
    Node* _selectedTitle;
    /** the image used when the item is disabled */
    Node* _disabledTitle;
    std::string _titlePath;//
};


#endif /* CustomButton_hpp */
