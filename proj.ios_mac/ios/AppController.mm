/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "AppController.h"
#import "CCEAGLView.h"
#import "cocos2d.h"
#import "AppDelegate.h"
#import "RootViewController.h"
#if TARGET_IPHONE_SIMULATOR//模拟器
#elif TARGET_OS_IPHONE//真机
    #import <OnlineAHelper/YiJieOnlineHelper.h>
#endif

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    

    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];

    // Init the CCEAGLView
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGB565
                                     depthFormat: GL_DEPTH24_STENCIL8_OES
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples: 0];
    [eaglView  setMultipleTouchEnabled:YES];//设置多点触摸
    // Use RootViewController manage CCEAGLView 
    _viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    _viewController.wantsFullScreenLayout = YES;
    _viewController.view = eaglView;

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: _viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:_viewController];
    }

    [window makeKeyAndVisible];

    [[UIApplication sharedApplication] setStatusBarHidden:true];
   // 禁止ios设备锁屏
    [[UIApplication sharedApplication] setIdleTimerDisabled: YES];
    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
    cocos2d::GLView *glview = cocos2d::GLView::createWithEAGLView(eaglView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);

    cocos2d::Application::getInstance()->run();
//    #if TARGET_IPHONE_SIMULATOR//模拟器
//    #elif TARGET_OS_IPHONE
//       [[YJAppDelegae Instance] application:application didFinishLaunchingWithOptions:launchOptions];
//    #endif
   
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->pause(); */
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->resume(); */
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::Application::getInstance()->applicationWillEnterForeground();
}

/////////////////////////////////////以下是易接加的///////////////////////////////////////////////////////////////////////

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation NS_AVAILABLE_IOS(4_2){
    BOOL yjResult = true;
    #if TARGET_IPHONE_SIMULATOR//模拟器
    #elif TARGET_OS_IPHONE
     yjResult = [[YJAppDelegae Instance] application:application openURL:url sourceApplication:sourceApplication annotation:annotation];
   
    #endif
    return yjResult;
}

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
    
    #if TARGET_IPHONE_SIMULATOR//模拟器
    #elif TARGET_OS_IPHONE
    [[YJAppDelegae Instance] application:application didRegisterForRemoteNotificationsWithDeviceToken:deviceToken];
    #endif
    
    
}
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {
    
#if TARGET_IPHONE_SIMULATOR//模拟器
#elif TARGET_OS_IPHONE
     [[YJAppDelegae Instance] application:application didReceiveRemoteNotification:userInfo];
#endif
    
}
- (NSUInteger)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window {
    
    NSLog(@"demo application supportedInterfaceOrientationsForWindow！");
    #if TARGET_IPHONE_SIMULATOR//模拟器
    #elif TARGET_OS_IPHONE
    return [[YJAppDelegae Instance] application:application supportedInterfaceOrientationsForWindow:window];
    #endif
    
    return 0;
    
}
- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url{
    // Will be deprecated at some point, please replace with application:openURL:sourceApplication:annotation:
    #if TARGET_IPHONE_SIMULATOR//模拟器
    #elif TARGET_OS_IPHONE
        return  [[YJAppDelegae Instance] application:application handleOpenURL:url];
    #endif
    
    return true;
}

////////////以上是易接加的////////////////////////////////////////////////////////////////////



- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
       NSLog(@"applicationWillTerminate applicationWillTerminate");
    #if TARGET_IPHONE_SIMULATOR//模拟器
    #elif TARGET_OS_IPHONE
        return  [[YJAppDelegae Instance] applicationDidEnterBackground:application];
    #endif
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
    NSLog(@"applicationDidReceiveMemoryWarning applicationDidReceiveMemoryWarning");
}


- (void)dealloc {
    [window release];
    [super dealloc];
}

-(void)openURL:(NSString *)url
{
    NSString *iTunesLink = url;
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:iTunesLink]];
}

-(NSString*) getUUID
{
    UIDevice *myDevice = [UIDevice currentDevice];
    NSString *uuid = nil;
    
    
    if ([[myDevice systemVersion] floatValue] < 6.0)
    {
        uuid = [NSString obtainMacAddress]; // 6.0以前用MAC地址作为UID
    } else
    {
        // identifierForVendor 6.0后可用
        uuid = [[myDevice identifierForVendor] UUIDString];
    }
    
    return uuid;
}

@end
