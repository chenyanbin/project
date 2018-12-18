//
//  EquipDataManager.h
//  FightPass
//
//  Created by 超 顾 on 15/9/1.
//
//

#ifndef __FightPass__EquipDataManager__
#define __FightPass__EquipDataManager__

#include "cocos2d.h"
USING_NS_CC;
#include "BaseEquipData.h"
#include "LetterData.h"
class EquipDataManager
{
public:
    
    ~EquipDataManager();
    static EquipDataManager* getInstance();
    void addData(BaseEquipData* data);
    void removeData(int _equipId);
    int getIndexByCardID(int _equipId);
    BaseEquipData* getCardDataByIndex(int index);
    void setChangeCardDataByIndex(int index,BaseEquipData* data);
    Vector<BaseEquipData*>* getDataList();
    void clearCardList();
    
    //所有装备
    void addEquipData(BaseEquipData* data);
    void removeEquipData(int _heroId);
    int getIndexByEquipID(int _equipId);
    BaseEquipData* getEquipDataByEquipID(int _equipId);
    BaseEquipData* getEquipDataByIndex(int index);
    Vector<BaseEquipData*>* getEquipDataList();
    void clearEquipList();
    
    //当前装备
    void setPresentData(BaseEquipData* data);
    BaseEquipData* getPresentData();
    
    //
protected:
    EquipDataManager();
private:
    Vector<BaseEquipData*>* chooseEquipList;//被吞噬的装备
    
    BaseEquipData* presentData;//当前选择装备
    
    Vector<BaseEquipData*>* equipList;//所有装备列表
    
    
    static EquipDataManager* _instance;
};


#endif /* defined(__FightPass__EquipDataManager__) */
