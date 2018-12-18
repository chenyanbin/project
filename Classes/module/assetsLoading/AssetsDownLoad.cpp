//
//  AsssetsDownLoad.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 15/1/21.
//
//
#include "../../commonData/GlobalInfo.h"
#include "AssetsDownLoad.h"

#include "../../common/PublicShowUI.h"
#include "../../commonData/data/ChannelDataManager.hpp"
#include "../login/LoginLayer.h"
#include <tinyxml2/tinyxml2.h>
#include "../../protocol/UserCustomEvent.h"
#include "../../common/StringUtil.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../sdk/SdkManager.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <dirent.h>
#include <sys/stat.h>
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "../../common/GlobalAppController.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include <platform/android/jni/JniHelper.h>
#include <android/log.h>

#if 1
#define  LOG_TAG    "JniHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...)
#endif
#endif

AssetsDownLoad::AssetsDownLoad()
:pathToSave("")
,pAssetsManager(NULL)
,popupLoading(NULL)
,configInfoUrlToSave("configs")
,imagesPackUrlToSave("imagesdir")
,m_domainIndex(0)
,m_progressLabel(NULL)
,dictDataIsSuc(false)
,resourceIsSuc(false)
,appVerionIsSuc(false)
,dictDataVersionURL("")
,resourceVersionURL("")
,appVersionURL("")
{
    
}
AssetsDownLoad::~AssetsDownLoad()
{
    if(pAssetsManager)
    {
        pAssetsManager->setDelegate(NULL);
        CC_SAFE_RELEASE_NULL(pAssetsManager);
    }
   
    popupLoading = NULL;
    CC_SAFE_RELEASE_NULL(m_progressLabel);
}

bool AssetsDownLoad::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->setClickEnabled(false);
        this->isAnimation = false;
        this->isShowGrayBg = false;
        this->isAbleGuiding = false;
        createDownloadedDir(configInfoUrlToSave);
        
        m_progressLabel = PublicShowUI::getLabel("             ",Color3B::MAGENTA,30,true,true);
        m_progressLabel->setPosition(VisibleRect::center().x ,VisibleRect::center().y - 200 * GlobalInfo::getInstance()->screenScaleX);
        this->addChild(m_progressLabel,20);
        CC_SAFE_RETAIN(m_progressLabel);
        
        bref = true;
    } while (false);
    return bref;
    
}
AssetsDownLoad* AssetsDownLoad::create()
{
    AssetsDownLoad* ref = new AssetsDownLoad();
    if(ref && ref->init())
    {
        ref->autorelease();
        return ref;
    }
    CC_SAFE_DELETE(ref);
    ref = NULL;
    return ref;
}
void AssetsDownLoad::setUpdatePath(const char* zipResourceUrl,const char* versionUrl)
{
    if(pAssetsManager)
    {
        pAssetsManager->setPackageUrl(zipResourceUrl);
        pAssetsManager->setVersionFileUrl(versionUrl);
    }
    else
    {
        pAssetsManager = AssetsManager::create(zipResourceUrl, versionUrl, pathToSave.c_str(),CC_CALLBACK_1(AssetsDownLoad::onError, this), CC_CALLBACK_1(AssetsDownLoad::onProgress, this), CC_CALLBACK_0(AssetsDownLoad::onSuccess, this));
         this->addChild(pAssetsManager,0);
         CC_SAFE_RETAIN(pAssetsManager);

    }
    
    pAssetsManager->setStoragePath(pathToSave.c_str());
}
void AssetsDownLoad::onEnter()
{
    BaseLayer::onEnter();
}
void AssetsDownLoad::onExit()
{
    BaseLayer::onExit();
}
void AssetsDownLoad::onExitTransitionDidStart()
{
    if(pAssetsManager)
    {
         pAssetsManager->setDelegate(NULL);
    }

    BaseLayer::onExitTransitionDidStart();

    this->setClickEnabled(false);
}
void AssetsDownLoad::onEnterTransitionDidFinish()
{
    dictDataIsSuc = false;
    resourceIsSuc = false;
    appVerionIsSuc = false;
    BaseLayer::onEnterTransitionDidFinish();
   
    m_domainIndex = 0;
   
    
    if(GlobalInfo::getInstance()->isAutoDownClient)
    {
        this->requestClientVersion();
    }
    else
    {
         onSuccess();
    }
    

}
void AssetsDownLoad::requestClientVersion()
{
    appVerionIsSuc = false;
    Dialog::hideServerLoading();
     Dialog::showServerLoading(0);
    GlobalInfo::getInstance()->resourceDomainURL = GlobalInfo::getInstance()->resourceDomainList[m_domainIndex] + "/";
    appVersionURL = GlobalInfo::getInstance()->resourceDomainURL + Configuration::getInstance()->getValue("appVersionName").asString();
    appVersionURL += "?t=" +PublicShowUI::numberToString(time(0));
    
    network::HttpRequest* _versionRequest = new network::HttpRequest();
    
    _versionRequest->setUrl(appVersionURL.c_str());
    _versionRequest->setRequestType(network::HttpRequest::Type::GET);
    log("requestClientVersion url===%s",appVersionURL.c_str());
    _versionRequest->setResponseCallback(this, httpresponse_selector(AssetsDownLoad::onClientVersionInit));
    _versionRequest->setTag("clientVersion");
    cocos2d::network::HttpClient::getInstance()->send(_versionRequest);
    _versionRequest->release();

}

void AssetsDownLoad::onClientVersionInit(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response)
{

    if (!response)
    {
        onClientVersionFailed();
        return;
    }
    if (!response->isSucceed())
    {
        onClientVersionFailed();
        return;
    }
    
    // dump data
    std::vector<char>* buffer = response->getResponseData();
    std::string content(buffer->begin(),buffer->end());
    
    rapidjson::Document _doc;
    _doc.Parse<0>(content.c_str());
    if (_doc.HasParseError())
    {
        Dialog::show("版本号获取返回格式错误");
        return;
    }
     m_domainIndex = 0;


    string version = _doc["version"].GetString();
    log("version=%s GlobalInfo::getInstance()->version  =%s",version.c_str(),GlobalInfo::getInstance()->version.c_str() );
    if(version != GlobalInfo::getInstance()->version && !GlobalInfo::getInstance()->isDebug)
    {
         Dialog::hideServerLoading();
        log("客户端有新版本");
        ChannelDataManager::getInstance()->loadData();
        Dialog::show("您的版本落伍啦，点击\"确定\",升级最新版本。","",1,this,callfuncN_selector(AssetsDownLoad::onClientDialogClick));
    }
    else
    {
        log("客户端没新版本");
        onSuccess();
    }
}
void AssetsDownLoad::onClientVersionFailed()
{

    m_domainIndex ++;
    if(m_domainIndex >= GlobalInfo::getInstance()->resourceDomainList.size())
    {
        Dialog::hideServerLoading();
        string errorURL = "http获取地址返回参数错误，请重新登陆 errorid=";
        errorURL = errorURL+ ERROR_HTTP_FAILED;
        Dialog::show(errorURL.c_str(),"",1,this,callfuncN_selector(AssetsDownLoad::onReLogin));
        this->removeFromParent();
        return;
    }
    requestClientVersion();
}

string AssetsDownLoad::getUpdateUrl()
{
  
    
    string url = "";
    string channelName = SdkManager::getInstance()->channelName;
      log("channelName===%s",channelName.c_str());
    Vector<DictChannel*>* list = ChannelDataManager::getInstance()->getDataList();
    for(DictChannel* channel : *list)
    {
       if(channel->channelID == channelName)
       {
           url = channel->url;
           break;
       }
    }
    CC_SAFE_DELETE(list);
    list= NULL;
    return url;
}


void AssetsDownLoad::onClientDialogClick(Node* pSender)
{
    string url = getUpdateUrl();
    log("versionUrl===%s",url.c_str());
    if(pSender->getTag() == 1)
    {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                m_progressLabel->setString("发现新版本，正在更新....");
                openApkUrl(url);
        #endif
                
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                GlobalAppController::openAPPStore(url.c_str());
        #endif
        GlobalInfo::getInstance()->isUpdateVersion = true;
        
    }
    else
    {
        m_domainIndex = 0;
    }
}
void AssetsDownLoad::openApkUrl(string url)
{
    if(url == "")
    {
        MessageBox("没有更新地址，请联系客服", "提示");
        return;
    }
    string channelName = SdkManager::getInstance()->channelName;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
//    jobject jobj;
    //getStaticMethodInfo方法是调用静态类的，也可以不用调用静态类的getMethodInfo
    bool b = JniHelper::getStaticMethodInfo(minfo,
                                            "org.cocos2dx.cpp.AppActivity", //类路径
                                            "openUrl", //静态方法名
                                            "(Ljava/lang/String;)V");
    if(!b){
        log("JniHelper::getMethodInfo error...");
    }else{
        
        jstring filePath=minfo.env->NewStringUTF(url.c_str());
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,filePath);
        minfo.env->DeleteLocalRef(filePath);
        minfo.env->DeleteLocalRef(minfo.classID);
    }
#endif
}
void AssetsDownLoad::requestDictDataVersion()
{

    GlobalInfo::getInstance()->resourceDomainURL = GlobalInfo::getInstance()->resourceDomainList[m_domainIndex] + "/";
    
    
    dictDataVersionURL = GlobalInfo::getInstance()->resourceDomainURL + Configuration::getInstance()->getValue("dictVersionName").asString();
  
    network::HttpRequest* _versionRequest = new network::HttpRequest();
    
    _versionRequest->setUrl(dictDataVersionURL.c_str());
    _versionRequest->setRequestType(network::HttpRequest::Type::GET);
    log("requestDictDataVersion url===%s",dictDataVersionURL.c_str());
    _versionRequest->setResponseCallback(this, httpresponse_selector(AssetsDownLoad::onDictDataVersionInit));

    cocos2d::network::HttpClient::getInstance()->send(_versionRequest);
    _versionRequest->release();
  
}
void AssetsDownLoad::onDictDataVersionInit(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response)
{
    if (!response)
    {
        
        onDictVersionFailed();
        return;
    }
    if (!response->isSucceed())
    {
        onDictVersionFailed();
        return;
    }

    // dump data
    std::vector<char>* buffer = response->getResponseData();
    std::string content(buffer->begin(),buffer->end());
    
    rapidjson::Document _doc;
    _doc.Parse<0>(content.c_str());
    if (_doc.HasParseError())
    {
        Dialog::show("版本号获取返回格式错误");
        return;
    }
    
    long long version = _doc["version"].GetUint64();
    
    string zipUrl = _doc["download_url"].GetString();
    string dictVersion = PublicShowUI::numberToString(version);
    this->setUpdatePath(zipUrl.c_str(),dictDataVersionURL.c_str());
    if(GlobalInfo::getInstance()->dictDataVersion != dictVersion)
    {
            checkUpdate(NULL);
    }
    else
    {
        onSuccess();
    }
//    GlobalInfo::getInstance()->version += PublicShowUI::numberToString(version);
    broadMsg(CUSTOM_UPDATE_VERSION);

 
}
void AssetsDownLoad::onDictVersionFailed()
{
       m_domainIndex ++;
    if(m_domainIndex >= GlobalInfo::getInstance()->resourceDomainList.size())
    {
        Dialog::hideServerLoading();
        string errorURL = "http获取地址返回参数错误，请重新登陆 errorid=";
        errorURL = errorURL+ ERROR_HTTP_FAILED;
         Dialog::show(errorURL.c_str(),"",1,this,callfuncN_selector(AssetsDownLoad::onReLogin));
        this->removeFromParent();
        return;
    }
 
    requestDictDataVersion();
 
}
void AssetsDownLoad::checkUpdate(Node* target)
{
    bool flag=pAssetsManager->checkUpdate();
    if(m_progressLabel)
    {
//        m_progressLabel->setString("检查资源更新。。。");
    }
    if(flag)
    {
        
        showLoading();
        pAssetsManager->update();
        
    }
    
}
void AssetsDownLoad::requestAvatarVersion()//更新角色资源
{
    Dialog::showServerLoading(0);
    
    
    GlobalInfo::getInstance()->resourceDomainURL = GlobalInfo::getInstance()->resourceDomainList[m_domainIndex] + "/";
    
    this->resourceVersionURL = GlobalInfo::getInstance()->resourceDomainURL + Configuration::getInstance()->getValue("resourceVersionName").asString() ;
    
    network::HttpRequest* _versionRequest = new network::HttpRequest();

    _versionRequest->setUrl(resourceVersionURL.c_str());
    _versionRequest->setRequestType(network::HttpRequest::Type::GET);
    _versionRequest->setResponseCallback(this, httpresponse_selector(AssetsDownLoad::onAvatarVersionInit));

    cocos2d::network::HttpClient::getInstance()->send(_versionRequest);
    _versionRequest->release();
}
void AssetsDownLoad::onAvatarVersionInit(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response)
{
    string errorURL = "http获取地址返回参数错误，请重新登陆 errorid=";
    if (!response)
    {
        onAvatarVersionFailed();
        return;
    }
    if (!response->isSucceed())
    {
        onAvatarVersionFailed();
        return;
    }
    
    long statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
    //    m_labelStatusCode->setString(statusString);
    log("response code: %ld", statusCode);
    // dump data
    std::vector<char>* buffer = response->getResponseData();
    std::string content(buffer->begin(),buffer->end());
    
    rapidjson::Document _doc;
    _doc.Parse<0>(content.c_str());
    if (_doc.HasParseError())
    {
        Dialog::show("版本号获取返回格式错误");
        return;
    }
    string zipUrl = _doc["download_url"].GetString();
    createDownloadedDir(imagesPackUrlToSave);
//    zipUrl = "http://36.110.17.45:7998/download/avatar.zip";
    this->setUpdatePath(zipUrl.c_str(),this->resourceVersionURL.c_str());
    
    
    checkUpdate(NULL);
    
    
}
void AssetsDownLoad::onReLogin(Node* pSender)
{
     NetworkDataProcessing::sharedNet()->reLogin();
}
void AssetsDownLoad::onAvatarVersionFailed()
{
       m_domainIndex ++;
    if(m_domainIndex >= GlobalInfo::getInstance()->resourceDomainList.size())
    {
         Dialog::hideServerLoading();
        string errorURL = "http获取地址返回参数错误，请重新登陆 errorid=";
        errorURL = errorURL+ ERROR_HTTP_FAILED;
        Dialog::show(errorURL.c_str(),"",1,this,callfuncN_selector(AssetsDownLoad::onReLogin));
        this->removeFromParent();
        return;
    }
 
    requestAvatarVersion();
}
void AssetsDownLoad::showLoading()
{
    Dialog::hideServerLoading();
    this->popupLoading = Dialog::showLoadingPage();
}
void AssetsDownLoad::createDownloadedDir(string url)
{
    pathToSave = FileUtils::getInstance()->getWritablePath();
    pathToSave += url;
    
    // Create the folder if it doesn't exist
    #if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
        DIR *pDir = NULL;
        pDir = opendir (pathToSave.c_str());
        if (! pDir)
        {
            mkdir(pathToSave.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
        }
    #else
        if ((GetFileAttributesA(pathToSave.c_str())) == INVALID_FILE_ATTRIBUTES)
        {
            CreateDirectoryA(pathToSave.c_str(), 0);
        }
    #endif
}
void AssetsDownLoad::onError(int errorCode)
{
  
    cocos2d::extension::AssetsManager::ErrorCode code = (cocos2d::extension::AssetsManager::ErrorCode )errorCode;
    if (code == AssetsManager::ErrorCode::NO_NEW_VERSION)
    {
        this->runAction(Sequence::create(DelayTime::create(.1),CallFunc::create(CC_CALLBACK_0(AssetsDownLoad::onSuccess, this)), NULL));
    }
    
    else if (code == AssetsManager::ErrorCode::NETWORK)
    {
//        m_progressLabel->setString("网络不稳，更新错误...");
        Dialog::show("网络不稳，下载错误!点击确定，重新更新","",1,this,callfuncN_selector(AssetsDownLoad::checkUpdate));
    }
    else if(code == AssetsManager::ErrorCode::UNCOMPRESS)
    {
//        m_progressLabel->setString("资源包错误，不能解压...");
        Dialog::show("资源包错误，不能解压,请联系客服!");
        this->runAction(Sequence::create(DelayTime::create(.1),CallFunc::create(CC_CALLBACK_0(AssetsDownLoad::onSuccess, this)), NULL));
    }
    else
    {
         Dialog::show("更新错误，请尝试重新登陆!","",1,this,callfuncN_selector(AssetsDownLoad::onReLogin));
    }
    
}
void AssetsDownLoad::onProgress(int percent)
{
//    string str = "别闹，办正经事呢 " + PublicShowUI::numberToString(percent) + "%";
    if(popupLoading)
    {
        this->popupLoading->setProgressPercent(percent);
    }
    if(m_progressLabel)
    {
//        m_progressLabel->setString(str.c_str());
    }
}

void AssetsDownLoad::onSuccess()
{
    if(!appVerionIsSuc)
    {
        log("appVerionIsSuc 更新成功");
        appVerionIsSuc = true;
      
        requestDictDataVersion();
       
    }
    else if(!dictDataIsSuc)
    {
        log("配置文件 更新成功");
        broadMsg(CUSTOM_CONFIG_UPDATE_SUC);
        dictDataIsSuc = true;
        m_domainIndex = 0;
        this->requestAvatarVersion();
        
    }
    else if(!resourceIsSuc)
    {
        log("avtar 更新成功");
        m_domainIndex = 0;
        resourceIsSuc = true;
//        this->broadMsg(CUSTOM_RESOURCE_UPDATE_SUC);
        this->broadMsg(CUSTOM_CLIENTAPP_SUC);
        Dialog::hideServerLoading();
        if(popupLoading && popupLoading->getParent())
        {
            popupLoading->removeFromParent();
        }
        this->removeFromParent();
    }

}