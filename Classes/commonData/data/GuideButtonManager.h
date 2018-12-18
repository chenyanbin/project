//
//  GuideButtonManager.hpp
//  FightPass
//新手引导按钮管理
//  Created by zhangxiaobin on 15/11/9.
//
//

#ifndef GuideButtonManager_hpp
#define GuideButtonManager_hpp

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "../enum/DictNewGuideEventEnum.h"

class GuideButtonManager
{
public:
    void destroyInstance();

    static GuideButtonManager* getInstance();
    Node* getButton(int buttonID);
    void registerButton(int buttonID,Node* btn);
    void removeButton(int buttonID);
    Point getButtonPosition(int buttonID);
private:
    static GuideButtonManager* _instance;
    Map<int,Node*>* data_list;
protected:
    GuideButtonManager();
    ~GuideButtonManager();
};
#endif /* GuideButtonManager_hpp */
