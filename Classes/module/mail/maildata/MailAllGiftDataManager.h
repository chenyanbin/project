//
//  MailAllGiftDataManager.h
//  FightPass
//
//  Created by chenyanbin on 15/11/13.
//
//

#ifndef __FightPass__MailAllGiftDataManager__
#define __FightPass__MailAllGiftDataManager__

#include "cocos2d.h"
USING_NS_CC;
#include "MailAllGiftData.h"
class MailAllGiftDataManager
{
public:
    MailAllGiftDataManager();
    
    ~ MailAllGiftDataManager();
    
    static void destroyInstance();
    
    static MailAllGiftDataManager* getInstance();
    
    void addData(MailAllGiftData* data);
    
    void removeData(int _heroId);
    
    int getIndexByCardID(int _heroId);
    
    Vector<MailAllGiftData*>* giftList;
    
    void setGiftSizeData(int data);
    
    int getGiftSize();
    
    void clearfindList();
    
private:
    
    int m_size;
    static MailAllGiftDataManager* _instance;
};


#endif /* defined(__FightPass__MailAllGiftDataManager__) */
