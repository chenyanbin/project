//
//  GuideButtonManager.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/11/9.
//
//

#include "GuideButtonManager.h"
#include "../../common/PublicShowUI.h"
#include "../../common/TouchSprite/Button.h"
GuideButtonManager* GuideButtonManager::_instance = NULL;
GuideButtonManager::GuideButtonManager()
{
    _instance = NULL;
    data_list = new Map<int, Node*>();
}
GuideButtonManager::~GuideButtonManager()
{
    CC_SAFE_DELETE(data_list);
    data_list = NULL;
}
void GuideButtonManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
}

GuideButtonManager* GuideButtonManager::getInstance()
{
    if(!_instance)
    {
        _instance = new GuideButtonManager();
    }
    return _instance;
}
Node* GuideButtonManager::getButton(int buttonID)
{
    return data_list->at(buttonID);
}
void GuideButtonManager::registerButton(int buttonID,Node* btn)
{
   if(!btn)
   {
       return;
   }
    data_list->insert(buttonID, btn);
}
void GuideButtonManager::removeButton(int buttonID)
{
    data_list->erase(buttonID);
}
Point GuideButtonManager::getButtonPosition(int buttonID)
{
    Node* btn = this->getButton(buttonID);
    if(btn)
    {
        Button* button = dynamic_cast<Button*>(btn);
        Rect rect;
        Point point ;

        if (button)
        {
            if(!button->getParent())
            {
                this->removeButton(buttonID);
               return Point(-1,-1);
            }
            rect = PublicShowUI::getRect(button);
            Point anchorPoint = button->getAnchorPoint();
            point .x = rect.getMidX() - btn->getContentSize().width * anchorPoint.x;
            point.y = rect.getMidY() - btn->getContentSize().height * anchorPoint.y;
            
            point = btn->getParent()->convertToWorldSpace(point);
//   

        }
        else
        {
            rect = PublicShowUI::getRect(btn);
            if(btn->getParent())
            {
                 point = btn->getParent()->convertToWorldSpace(Point(rect.getMidX(),rect.getMidY()));
            }
            else
            {
                 point = btn->convertToWorldSpace(Point(rect.getMidX(),rect.getMidY()));
            }
           
        }
       
        

        return point;
    }
    return Point(-1,-1);
    
}