//
//  LetterDataManager.h
//  FightPass
//
//  Created by 超 顾 on 15/8/19.
//
//

#ifndef __FightPass__LetterDataManager__
#define __FightPass__LetterDataManager__

#include "cocos2d.h"
USING_NS_CC;
#include "LetterData.h"
class LetterDataManager
{
public:
    
    ~LetterDataManager();
    static LetterDataManager* getInstance();
    void addData(LetterData* data);
    void removeData(int _heroId);
    int getIndexByCardID(int _heroId);
    LetterData* getCardDataByIndex(int index);
    void setChangeCardDataByIndex(int index,LetterData* data);
    Vector<LetterData*>* getDataList();
    void clearCardList();
    
    //
    //当前武将
    void setPresentData(LetterData* data);
    LetterData* getPresentData();
protected:
    LetterDataManager();
private:
    
    LetterData* presentData;//当前书信属性
    
    Vector<LetterData*>* letterList;
    
    static LetterDataManager* _instance;
};


#endif /* defined(__FightPass__LetterDataManager__) */
