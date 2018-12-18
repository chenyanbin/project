//
//  MailCellDataManager.h
//  FightPass
//
//  Created by chenyanbin on 15/11/13.
//
//

#ifndef __FightPass__MailCellDataManager__
#define __FightPass__MailCellDataManager__

#include "cocos2d.h"
USING_NS_CC;
#include "MailCellData.h"
class MailCellDataManager
{
public:
    MailCellDataManager();
    
    ~MailCellDataManager();
    
    static void destroyInstance();
    
    static MailCellDataManager* getInstance();
    
    void addData(MailCellData* data);
    
    Vector<MailCellData*>* mailCellList;
    
    void clearMailCellList();
    
private:
    static MailCellDataManager* _instance;
};


#endif /* defined(__FightPass__MailCellDataManager__) */
