//
//  AwakeLayer.hpp
//  FightPass
//
//  Created by zhangbin on 16/3/25.
//
//

#ifndef AwakeLayer_hpp
#define AwakeLayer_hpp

#include "../../BaseLayer.h"
#include "../data/CardPropertyData.h"
#include "../../../net/bytestream.h"
class AwakeItemData:public Ref
{
public:
    int itemId;//		道具 id
    int itemCount;//	道具数量
    int nowItemCount;//目前拥有数量
 
};
class AwakeLayer:public BaseLayer
{
public:
    AwakeLayer();
    ~AwakeLayer();
    virtual bool init(int heroID,int heroDictID);
    static AwakeLayer* create(int heroID,int heroDictID);
    static void show(int heroID,int heroDictID);

protected:
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
    
    void requestPageMsg();
    void requestAwakeMsg();
    void onMsgProcess(EventCustom* message);
    void parsePageMsg(ByteStream* byteStream);
    
private: 
    void setLeftHero();
    void setRightHero();
    
    Label* getNameLabel(string nameStr,int quality);
 
    Node* getHeroImage(int quality);
  
    void onAwakeBtnClick(Ref* pSender);
    void setItems();
    Node* getItemIcon(const char* path,int quality,int value,int totalValue);
    void setAttribs();//设置属性
    Node* getAttribNode(const char* attribStr,int value,int newValue);
    void onHeroHeadClick(Node* node);
    void updateCooperCost();
    void updateHeroQuanlity();
    
    void showIconEffect();
    void showAwakeEffect();
    void onEffectCompleted();
    void onUpdateItems();
private:
    int m_heroID;
    int m_heroDictID;
    CardPropertyData* propertyData;
    CardPropertyData* propertyNewData;
    int TAG_ATTRIB_NODE;
    int TAG_ITEMS;
    int TAG_COOPER;
    int TAG_LEFTNAME;
    int TAG_RIGHTNAME;
    int TAG_AWAKEBTN;
    int TAG_LEFTHERO;
    int TAG_RIGHTHERO;
    Vector<AwakeItemData*>* awakeItemList;
    int curQuality;//
    int coin;
    bool isInited;
    bool isUpdateItems;
};

#endif /* AwakeLayer_hpp */
