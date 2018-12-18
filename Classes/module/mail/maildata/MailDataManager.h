//
//  MailDataManager.h
//  FightPass
//
//  Created by chenyanbin on 15/11/11.
//
//

#ifndef __FightPass__MailDataManager__
#define __FightPass__MailDataManager__

#include "cocos2d.h"
USING_NS_CC;
#include "MailData.h"
class MailDataManager
{
public:
    MailDataManager();
    
    ~MailDataManager();
    
    static void destroyInstance();
    
    static MailDataManager* getInstance();
    
    void addData(MailData* data);
    
    Vector<MailData*>* mailList;
    
    void clearMailList();
    
private:
    static MailDataManager* _instance;
};


#endif /* defined(__FightPass__MailDataManager__) */
