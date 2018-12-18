//
//  GeneralsBase_Layer.h
//  FightPass
//觉醒
//  Created by 超 顾 on 15/7/29.
//
//

#ifndef __FightPass__GeneralsBase_Layer__
#define __FightPass__GeneralsBase_Layer__
#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "../data/BaseEquipData.h"
#include "../data/KarmaData.h"
#include "../../../common/TouchSprite/Button.h"
USING_NS_CC_EXT;
USING_NS_CC;

class GeneralsBase_Layer:public BaseLayer
{
public:
    GeneralsBase_Layer();
    ~GeneralsBase_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(int cardId);
    static GeneralsBase_Layer* create(int cardId);
//    CREATE_FUNC(GeneralsBase_Layer);
private:
    void createLayer();
    void onBtnClick(Ref* pSender);
    void onButtonClick(Node* pSender);
    void onButtonMaterialClick(Node* pSender);
    void requestMsg();
    void oneKeyPutOnMsg();
    void wakeUpMsg();
    void oneKeyStrongMsg();
    void showEquipLvUpSound();
    
    void onMsgProcess(EventCustom* msg);

    void addEventListener();
    void removeEventListener();
    void updateEquip();
    void setBottomBtn();
    void onAwakeBtnClick(Ref* pSender);
    void onUpStarBtnClick(Ref* pSender);
    void updateAwakeProgress();
    void updateUpStarProgress();
    void onUpStarSuc(EventCustom* msg);
    void onItemClick(Node* pSender);
    void onPlusClick(Node* psender);
private:
    int TAG_EQUIPMENT;
    int TAG_STRONG;
    int TAG_AWAKEN;
    int TAG_EQUIPS;
    int TAG_GOLDLABEL;
    int TAG_AWAKELABEL;
    int TAG_UPSTARLABEL;
    int TAG_PLUSBTN;
    int _cardId;
    int heroDictId;
    int heroID;
    Button* upStartBtn;
    Button* awakeBtn;
    
    int hasBaseEquip;//是否有高级装备配置
    int oneKeyHardenCost;//是否可强化
    vector<BaseEquipData*> *equipList;
//    vector<KarmaData*> *karmaList;
    
    ProgressTimer* awakePt;
    ProgressTimer* upStarPt;
    
    
    int starUpBookId;//	升星需要武将书信id   DictBook.id 不能升星返回0
    float starUpBookCount;//		short	Y	升星需要武将书信数量 不能升星返回0
    float starUpBookCountOwn;//		short	Y	升星需要武将书信，目前拥有的数量 不能升星返回0
    int wakeUpItemId;//		int	Y	觉醒需要道具id（4个道具中的第1个 DictItem.id 不能觉醒返回0
    float wakeUpItemCount;//		short	Y	觉醒需要道具数 不能觉醒返回0 （4个道具中的第1个）
    float wakeUpItemCountOwn;//		short	Y	觉醒需要道具，目前拥有的数量（4个道具中的第1个）不能觉醒返回0
    int starStatus;//	升星状态	byte	Y	1,有红点
    int quailtyStatus;//	觉醒状态	byte	Y	1,有红点
    int lineupStatus;//上阵状态

   
    
    
};
#endif /* defined(__FightPass__GeneralsBase_Layer__) */
