//
//  GlobalAppController.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 14-8-6.
//
//

#include "GlobalAppController.h"
#import "AppController.h"

void GlobalAppController::openAPPStore(const char* url)
{
    NSString* strNSString = [[NSString alloc] initWithUTF8String:url];
    AppController *app = (AppController*) [[UIApplication sharedApplication] delegate];
    [app openURL:(strNSString)];
}

const char* GlobalAppController::getUUID()
{
    AppController *app = (AppController*) [[UIApplication sharedApplication] delegate];
    NSString* uuidStr = [app getUUID];
    return [uuidStr UTF8String];
}

const char* GlobalAppController::getChannelLabel()
{
    NSDictionary * dict = [[NSBundle mainBundle] infoDictionary];
    NSString* key = @"channelLabel";
    NSObject* object= [dict objectForKey:key];
    if(object != nullptr)
    {
        NSString* channel = (NSString*)object;
        return [channel UTF8String];
    }
    return "apple";
}
