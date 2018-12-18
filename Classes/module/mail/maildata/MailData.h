//
//  MailData.h
//  FightPass
//
//  Created by chenyanbin on 15/11/11.
//
//

#ifndef FightPass_MailData_h
#define FightPass_MailData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class MailData:public Ref
{
public:
    MailData()
    :mailId(0)
    ,type(1)
    ,typeText("")
    ,itemName("")
    ,itemtitle("")
    ,status(0)
    {
        
    }
    ~MailData()
    {
        
    }
    int mailId;//邮件id
    int type ;//邮件类型
    string typeText;//类型文字
    string itemName;//发件人
    string itemtitle;//邮件标题
    int status;//状态 1 可领取,带附件邮件 2 未读，游戏公告 3 已读，游戏公告
    
    
};


#endif
