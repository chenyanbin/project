//
//  FriendApplyNode.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/12/1.
//好友申请结点
//

#ifndef FriendApplyNode_hpp
#define FriendApplyNode_hpp
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "extensions/cocos-ext.h"
#include "../data/MessageData.h"
USING_NS_CC;
USING_NS_CC_EXT;

class FriendApplyNode:public BaseLayer ,public ScrollViewDelegate
{
public:
    FriendApplyNode();
    ~FriendApplyNode();
    virtual bool init(MessageData* data);
    static FriendApplyNode* create(MessageData* data);
protected:
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    void scrollViewDidScroll(ScrollView* view);
    void scrollViewDidZoom(ScrollView* view);
    
private:
    void setBg();
    void setContent();
    
    void requestRefuseMsg();
    void requestAgreeMsg();
    void onMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    
    void onBtnClick(Ref* psender);
    void onItemClick(Node* item);
    void onStatusApply(Node* psender);
    void onStatusApplyEnabled(Node* psender=NULL);
private:
    MessageData* m_data;
    int TAG_BG;
    int TAG_NICKNAME;
    int TAG_AGREE;
    int TAG_REFUSE;
    Sprite* cellNode;
    Sprite* cellBg2;
};


#endif /* FriendApplyNode_hpp */
