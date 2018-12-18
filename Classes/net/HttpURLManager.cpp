//
//  HttpURLManager.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/7/16.
//
//

#include "HttpURLManager.h"
#include "NetworkDataProcessing.h"
#include "../common/Dialog/Dialog.h"
#include "../commonData/GlobalInfo.h"
#include "../common/GameConfig.h"
#include "../module/login/LoginLayer.h"
#include "../module/login/serverList/ServerListDataManager.h"
#include "../sdk/SdkManager.h"
#include "../common/md5/MD5.h"
#include "../module/login/serverList/EnterGameLayer.h"
#include "../common/TimeUtil.h"
#include "../common/noticeManager/Notice_Layer.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "../common/StringUtil.h"
#include "cocostudio/DictionaryHelper.h"

HttpURLManager* HttpURLManager::_instance = NULL;
HttpURLManager::HttpURLManager()
:m_loginIndex(0)
{
    
}
HttpURLManager::~HttpURLManager()
{
    m_loginIndex = 0;
    _instance = NULL;
}
void HttpURLManager::destoryInstance()
{
    if(_instance)
    {
        CC_SAFE_DELETE(_instance);
        _instance = NULL;
    }
}
HttpURLManager* HttpURLManager::getInstance()
{
    if(!_instance)
    {
        _instance = new HttpURLManager();
    }
    return _instance;
}

void HttpURLManager::login()
{
    Dialog::hideServerLoading();
    Dialog::showServerLoading(0);
    string gameId = GlobalInfo::getInstance()->gameID;
    string channelID = SdkManager::getInstance()->channel;
    string uid = GlobalInfo::getInstance()->uid;
    string accessKey = CLIENT_ACCESS_KEY;
    
    GlobalInfo::getInstance()->_domainURL = GlobalInfo::getInstance()->domainList[m_loginIndex] + "/";
    
    string url = GlobalInfo::getInstance()->_domainURL;
    string sign = "";
    if(GlobalInfo::getInstance()->isSdkMode)
    {
        url += GlobalInfo::getInstance()->sdkURL;
         url +=  this->getReleaseVersionURL();
    }
    else
    {
        url += GlobalInfo::getInstance()->noSdkUrl;
        url += getDebugVersionURL();
    }

   
    log("login url==%s",url.c_str());
    network::HttpRequest* request = new network::HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(network::HttpRequest::Type::POST);
    request->setResponseCallback(this, httpresponse_selector(HttpURLManager::onLoginCallBack));
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
}
std::string HttpURLManager::getDebugVersionURL()
{
    string gameId = GlobalInfo::getInstance()->gameID;
    string channelID = SdkManager::getInstance()->channel;
    string uid = GlobalInfo::getInstance()->uid;
    string accessKey = CLIENT_ACCESS_KEY;

//    string sign = "access_key=" + accessKey + "&channel=" + SdkManager::getInstance()->channel + "&game_id=" + gameId + "&passport_session_id=" + GlobalInfo::getInstance()->sessionID + "&secret_key=" + CLIENT_SECRET_KEY + "&username=" + GlobalInfo::getInstance()->uid;
//    log("sign==%s",sign.c_str());
//    sign = MD5(sign).toString();
    
    
    string url = "?game_id=" + gameId + "&channel=" + SdkManager::getInstance()->channel + "&username=" + GlobalInfo::getInstance()->uid + "&access_key="  + CLIENT_ACCESS_KEY + "&passport_session_id=" + GlobalInfo::getInstance()->sessionID;// + "&sign=" + sign;
    
   
    return url;
}
std::string HttpURLManager::getReleaseVersionURL()
{
    string gameId = GlobalInfo::getInstance()->gameID;
    string channelID = SdkManager::getInstance()->channel;
    string uid = GlobalInfo::getInstance()->uid;
    string accessKey = CLIENT_ACCESS_KEY;
    log("11111 token ==%s",GlobalInfo::getInstance()->token.c_str());
    string token = StringUtil::urlencode(GlobalInfo::getInstance()->token);
    log("222222 token ==%s",token.c_str());
    
//    string sign = "access_key="+accessKey + "&app=" + SdkManager::getInstance()->appid + "&channel_code="+ SdkManager::getInstance()->channel + + "&channel_token=" +  GlobalInfo::getInstance()->token + "&channel_user_id=" + SdkManager::getInstance()->channelUserID + "&channel_username=" +SdkManager::getInstance()->channelUserName  + "&passport_session_id=" + GlobalInfo::getInstance()->sessionID +  "&device_uid=" + PublicShowUI::getUUID()+ "&secret_key="+CLIENT_SECRET_KEY;
//    
//     log("getReleaseVersionURL sign==%s",sign.c_str());
//    sign = MD5(sign).toString();
    
    
    
    string url = "?app=" + SdkManager::getInstance()->appid + "&channel_code=" + channelID + "&channel_user_id=" + SdkManager::getInstance()->channelUserID + "&channel_username=" + SdkManager::getInstance()->channelUserName + "&channel_token=" + token + "&access_key=" + accessKey + "&passport_session_id=" + GlobalInfo::getInstance()->sessionID + "&device_uid=" + PublicShowUI::getUUID();// + "&sign=" + sign;
    
    return url;
}
void HttpURLManager::onLoginCallBack(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response)
{
    Dialog::hideServerLoading();
    string errorURL = "http获取地址返回参数错误，请重新登陆 errorid=";
    if (!response)
    {
        
        errorURL = errorURL + ERROR_HTTP_NODATA;
        Dialog::show(errorURL.c_str(),"",1,this,callfuncN_selector(HttpURLManager::onReLogin));
        return;
    }

    if (!response->isSucceed())
    {
        errorURL = errorURL+ ERROR_HTTP_FAILED;
        m_loginIndex ++;
        if(m_loginIndex >= GlobalInfo::getInstance()->domainList.size())
        {
           Dialog::show(errorURL.c_str(),"",1,this,callfuncN_selector(HttpURLManager::onReLogin));
            return;
        }
        login();
        return;
    }

    // dump data
    std::vector<char> *buffer = response->getResponseData();
    std::string rest(buffer->begin(),buffer->end());
    log("rest ==%s", rest.c_str());

    rapidjson::Document _doc;
    _doc.Parse<0>(rest.c_str());
    if (_doc.HasParseError())
    {
         Dialog::show("登陆json格式错误");
        return;
    }
    int retCode = _doc["ret_code"].GetInt();
    if(retCode != 0)
    {

        Dialog::show(_doc["debug_msg"].GetString());
        return;
    }
    string sessionID = "";
    if(_doc.HasMember("passportSessionId"))
    {
        sessionID = _doc["passportSessionId"].GetString();
    }
    else if(_doc.HasMember("sessionId"))
    {
        sessionID = _doc["sessionId"].GetString();
    }
    else
    {
        log("login 返回 sessionid为空");
    }
    
    GlobalInfo::getInstance()->sessionID = sessionID;
    this->requestNoticeData();
 
}
//
void HttpURLManager::requestServerList()
{

    Dialog::showServerLoading(0);
    string url = GlobalInfo::getInstance()->_domainURL + GlobalInfo::getInstance()->serverListURL;
    string gameId = GlobalInfo::getInstance()->gameID;
    string channel = SdkManager::getInstance()->channel;
    
//    string times = PublicShowUI::numberToString(TimeUtil::getTimestamp());
    string accessKey = CLIENT_ACCESS_KEY;
    
    
    string sign = "access_key=" + accessKey + "&channel=" + channel + "&game_id=" + gameId + "&passport_session_id=" + GlobalInfo::getInstance()->sessionID + "&secret_key=" + CLIENT_SECRET_KEY;
    sign = MD5(sign).toString();
    
    url += "?game_id=" + gameId + "&channel=" + channel + "&passport_session_id=" + GlobalInfo::getInstance()->sessionID + "&access_key="  + CLIENT_ACCESS_KEY + "&sign=" + sign;

    log("requestServerList URL==%s",url.c_str());
    network::HttpRequest* request = new network::HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(network::HttpRequest::Type::POST);
    request->setResponseCallback(this, httpresponse_selector(HttpURLManager::onServerListCallBack));
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
}
void HttpURLManager::onReLogin(Node* pSender)
{
      NetworkDataProcessing::sharedNet()->reLogin();
}

void HttpURLManager::onServerListCallBack(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response)
{
   
    Dialog::hideServerLoading();
  
    string errorURL = "http获取地址返回参数错误，请重新登陆 errorid=";
    if (!response)
    {
        
        errorURL = errorURL + ERROR_HTTP_NODATA;
        Dialog::show(errorURL.c_str(),"",1,this,callfuncN_selector(HttpURLManager::onReLogin));
        return;
    }
    if (!response->isSucceed())
    {
        errorURL = errorURL + ERROR_HTTP_FAILED;
        Dialog::show(errorURL.c_str(),"",1,this,callfuncN_selector(HttpURLManager::onReLogin));
        return;
    }
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    std::string rest(buffer->begin(),buffer->end());
     log("onServerListCallBack URL==%s",rest.c_str());
    ServerListDataManager::getInstance()->parseServerList(rest.c_str());

    EnterGameLayer::show();
    
    bool isActive = UserDefault::getInstance()->getBoolForKey(CLIENT_SUB_CHANNEL, false);
    if(!isActive)
    {
         this->subChannelActive();
    }
   
}
void HttpURLManager::subChannelActive()//激活子账号
{

    string url = GlobalInfo::getInstance()->_domainURL + GlobalInfo::getInstance()->subChannelActive;
    
    string gameId = GlobalInfo::getInstance()->gameID;
  
    
    string times = PublicShowUI::numberToString(TimeUtil::getTimestamp());
    string accessKey = CLIENT_ACCESS_KEY;
    
// access_key={}&game_id={}&passport_session_id={}&secret_key={}&sub_channel_code={}

    string sign = "access_key=" + accessKey  + "&game_id=" + gameId + "&passport_session_id=" + GlobalInfo::getInstance()->sessionID + "&secret_key=" + CLIENT_SECRET_KEY + "&sub_channel_code=" + GlobalInfo::getInstance()->subChannel;
    sign = MD5(sign).toString();
    
    url += "?game_id=" + gameId + "&sub_channel_code=" + GlobalInfo::getInstance()->subChannel + "&passport_session_id=" + GlobalInfo::getInstance()->sessionID + "&access_key="  + CLIENT_ACCESS_KEY + "&sign=" + sign;
    
    log("subChannelActive URL==%s",url.c_str());
    network::HttpRequest* request = new network::HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(network::HttpRequest::Type::POST);
    request->setResponseCallback(this, httpresponse_selector(HttpURLManager::onSubWayActiveBack));
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();

}
void HttpURLManager::onSubWayActiveBack(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response)
{

    string errorURL = "http获取地址返回参数错误，请重新登陆 errorid=";
    if (!response)
    {
        
        errorURL = errorURL + ERROR_HTTP_NODATA;
        Dialog::show(errorURL.c_str(),"",1,this,callfuncN_selector(HttpURLManager::onReLogin));
        return;
    }
    if (!response->isSucceed())
    {
        errorURL = errorURL+ ERROR_HTTP_FAILED;
       
        return;
    }
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    std::string rest(buffer->begin(),buffer->end());
    log("onSubWayActiveBack ==%s", rest.c_str());
    
    rapidjson::Document _doc;
    _doc.Parse<0>(rest.c_str());
    if (_doc.HasParseError())
    {
        Dialog::show("登陆json格式错误");
        return;
    }
    int retCode = _doc["ret_code"].GetInt();
    if(retCode != 0)
    {
//        Dialog::show(_doc["debug_msg"].GetString());
        return;
    }
    UserDefault::getInstance()->setBoolForKey(CLIENT_SUB_CHANNEL, true);
    UserDefault::getInstance()->flush();
}


void HttpURLManager::requestNoticeData()
{
    Dialog::showServerLoading();
    string url = GlobalInfo::getInstance()->_domainURL;
    string accessKey = CLIENT_ACCESS_KEY;
    string passortSessionID = GlobalInfo::getInstance()->sessionID;
    //access_key=ddcca99b729f592c71ad13e4106ef788&passport_session_id=07bea63c-e63a-4db4-a0e6-779f8ec0c2b5&secret_key=ceffaf03d3680824fb14a5260b6ffeb4
    string sign = "access_key=" + accessKey + "&passport_session_id=" + passortSessionID + "&secret_key="+ CLIENT_SECRET_KEY;
    log("requestNoticeByHttp sign==%s",sign.c_str());
    sign = MD5(sign).toString();
    string priex = "account/notice_page?" ;
    string param = priex + "access_key=" + accessKey + "&passport_session_id=" + passortSessionID + "&sign=" + sign;
    url += param;
    log("url==%s",url.c_str());
    network::HttpRequest* request = new network::HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(network::HttpRequest::Type::POST);
    request->setResponseCallback(this, httpresponse_selector(HttpURLManager::onNoticeCallBack));
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();

}
void HttpURLManager::onNoticeCallBack(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response)
{
    Dialog::hideServerLoading();
    this->requestServerList();//不管成功，失败，不影响获取服务器列表
    string errorURL = "http获取地址返回参数错误，请重新登陆 errorid=";
    if (!response)
    {
        return;
    }
    
    if (!response->isSucceed())
    {
        return;
    }
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    
    std::string rest(buffer->begin(),buffer->end());
    log("rest ==%s", rest.c_str());
    rapidjson::Document _doc;
    _doc.Parse<0>(rest.c_str());
    if (_doc.HasParseError())
    {
        return;
    }
    int retCode = _doc["ret_code"].GetInt();
    if(retCode != 0)
    {
        return;
    }
    Vector<NoticeData*> *noticeList = new Vector<NoticeData*>();
    int actionCount = cocostudio::DictionaryHelper::getInstance()->getArrayCount_json(_doc, "notices");
    
    for (int i=0; i<actionCount; i++)
    {
        
        const rapidjson::Value &actionDic = cocostudio::DictionaryHelper::getInstance()->getDictionaryFromArray_json(_doc, "notices", i);
        ;
        NoticeData* data=new NoticeData();
        data->autorelease();
        data->NoticeName=cocostudio::DictionaryHelper::getInstance()->getStringValue_json(actionDic, "title");
        string dec=cocostudio::DictionaryHelper::getInstance()->getStringValue_json(actionDic, "content");
        data->DescList->push_back(dec);
        noticeList->pushBack(data);
        
    }
    if(actionCount > 0)
    {
        Notice_Layer::show(noticeList);
    }
  
}

