//
//  AsssetsDownLoad.h
//  SuiTang
//
//  Created by zhangxiaobin on 15/1/21.
//
//

#ifndef __SuiTang__AsssetsDownLoad__
#define __SuiTang__AsssetsDownLoad__

#include "cocos2d.h"
USING_NS_CC;
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
#include "../BaseLayer.h"
#include <network/HttpRequest.h>
#include <network/HttpResponse.h>
#include <network/HttpClient.h>
#include "../../common/Dialog/Dialog.h"
#include "editor-support/spine/Json.h"



class AssetsDownLoad:public BaseLayer ,AssetsManagerDelegateProtocol
{
public:
    AssetsDownLoad();
    ~AssetsDownLoad();
    bool init();
    static AssetsDownLoad* create();
    
    virtual void onError(int errorCode);
    virtual void onProgress(int percent);
    virtual void onSuccess();
    virtual void onEnter();  
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
private:
    
    void createDownloadedDir(string url);//设置下载保存目录
    void setUpdatePath(const char* zipResourceUrl,const char* versionUrl);//设置更新的资源地址
    void checkUpdate(Node* target = NULL);
    void showLoading();
    void openApkUrl(string url);
    void onClientDialogClick(Node* pSender);
    
    void onReLogin(Node* pSender);
    string getUpdateUrl();
private:
    void requestClientVersion();//是否有新版本更新
    void onClientVersionInit(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);
    void onClientVersionFailed();
    
    void requestDictDataVersion();//更新策划数据表资源
    void onDictDataVersionInit(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);
    void onDictVersionFailed();
    
    void requestAvatarVersion();//更新角色资源
    void onAvatarVersionInit(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);
    void onAvatarVersionFailed();
private:
    string pathToSave;
    AssetsManager* pAssetsManager;
    LoadingPage* popupLoading;
  
    string configInfoUrlToSave;
    string imagesPackUrlToSave;
    Label* m_progressLabel;
    bool dictDataIsSuc;//数据资源是否ok
    bool resourceIsSuc;//美术资源是否ok
    bool appVerionIsSuc;//客户端版本是否ok
    int m_domainIndex;//域名下标
    string appVersionURL;
    string dictDataVersionURL;
    string resourceVersionURL;
};




#endif /* defined(__SuiTang__AsssetsDownLoad__) */
