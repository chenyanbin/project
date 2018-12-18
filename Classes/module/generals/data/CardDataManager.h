//
//  CardDataManager.h
//  FightPass
//
//  Created by 超 顾 on 15/8/13.
//
//

#ifndef __FightPass__CardDataManager__
#define __FightPass__CardDataManager__
#include "cocos2d.h"
USING_NS_CC;
#include "CardPropertyData.h"
#include "LetterData.h"
class CardDataManager
{
public:
    
    ~CardDataManager();
    static CardDataManager* getInstance();
    void addData(CardPropertyData* data);
    void removeData(int _heroId);
    int getIndexByCardID(int _heroId);
    CardPropertyData* getCardDataByIndex(int index);
    void setChangeCardDataByIndex(int index,CardPropertyData* data);
    Vector<CardPropertyData*>* getDataList();
    void clearCardList();
    
    //所有卡牌
    void addHeroData(CardPropertyData* data);
    void removeHeroData(int _heroId);
    int getIndexByHeroID(int _heroId);
    CardPropertyData* getHeroDataByIndex(int index);
    Vector<CardPropertyData*>* getHeroDataList();
    void clearHeroList();
    
    //当前武将
    void setPresentData(CardPropertyData* data);
    CardPropertyData* getPresentData();
    
    //
    void copyData(CardPropertyData* data1,CardPropertyData* data2);
    
protected:
    CardDataManager();
private:
    Vector<CardPropertyData*>* chooseEquipList;//被历练的卡牌
    
    CardPropertyData* presentData;//当前卡牌属性
    
    Vector<CardPropertyData*>* heroList;//所有武将列表
    
    Vector<LetterData*>* letterList;
    
    static CardDataManager* _instance;
};

#endif /* defined(__FightPass__CardDataManager__) */
