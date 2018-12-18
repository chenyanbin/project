//
//  FriendItemNode.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/12/1.
//
//

#ifndef FriendItemNode_hpp
#define FriendItemNode_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "../../../YVSDK/YVPlatform.h"
#include "../data/MessageManager.h"
#include "../../BaseLayer.h"
using namespace YVSDK;
class FriendItemNode:public BaseLayer
{
public:
    FriendItemNode();
    ~FriendItemNode();
    virtual bool init(MessageData* data);
    static FriendItemNode* create(MessageData* data);
protected:
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void setBg();
    void setContent();

    void onItemClick(Node* item);
    void onBtnClick(Ref* psender);
private:
    YVUInfoPtr m_data;
    float sx;
    int TAG_BG;
    int TAG_NICKNAME;
    MessageData* friendData;
};

#endif /* FriendItemNode_hpp */
