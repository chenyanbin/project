//
//  GlobalAppController.h
//  SuiTang
//
//  Created by zhangxiaobin on 14-8-6.
//
//

#ifndef __SuiTang__GlobalAppController__
#define __SuiTang__GlobalAppController__

class GlobalAppController
{
public:
    static void openAPPStore(const char* url);
    static const char* getUUID();
    static const char* getChannelLabel();
};

#endif /* defined(__SuiTang__GlobalAppController__) */
