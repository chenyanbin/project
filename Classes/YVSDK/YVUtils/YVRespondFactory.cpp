/*********************************************************************************
*Copyright(C), 2015 YUNVA Company
*FileName:  RespondFactory.cpp
*Author:  Matt
*Version:  1.0.0
*Date:  2015-5-5
*Description:  定义协议的调用结构体
**********************************************************************************/

#include "YVRespondFactory.h"
#include "../YVProtocol/YVProtocol.h"
namespace YVSDK
{
	RespondFactory* RespondFactory::m_respondFactoryPtr = NULL;

	//云娃帐号登录回应
	AutoRegisterRespond(IM_LOGIN_RESP, LoginResponse);
	//CP帐号登录回应
	AutoRegisterRespond(IM_THIRD_LOGIN_RESP, CPLoginResponce);

	AutoRegisterRespond(IM_FRIEND_ADD_RESP, AddFriendRepond);
	AutoRegisterRespond(IM_FRIEND_ADD_NOTIFY, AddFriendNotify);
	AutoRegisterRespond(IM_FRIEND_ACCEPT_RESP, FriendAcceptRespond);
	//被好友删除通知（好友要求你从他的好友列表里移除）
	AutoRegisterRespond(IM_FRIEND_DEL_NOTIFY, DelFriendNotify);
	AutoRegisterRespond(IM_FRIEND_RECOMMAND_RESP, RecommendFriendRespond);
	AutoRegisterRespond(IM_FRIEND_SEARCH_RESP, SearchFriendRespond);
	AutoRegisterRespond(IM_FRIEND_OPER_RESP, BlackControlRespond);
	//好友删除回应
	AutoRegisterRespond(IM_FRIEND_DEL_RESP, DelFriendRespond);
	//好友列表推送
	AutoRegisterRespond(IM_FRIEND_LIST_NOTIFY, FriendListNotify);
	//黑名单推送
	AutoRegisterRespond(IM_FRIEND_BLACKLIST_NOTIFY, BlackListNotify);
	//好友状态通知
	AutoRegisterRespond(IM_FRIEND_STATUS_NOTIFY, FriendStatusNotify);
	//AutoRegisterRespond(IM_CLOUDMSG_NOTIFY, CloundMsgNotify);
	//好友消息通知
	AutoRegisterRespond(IM_CHAT_FRIEND_NOTIFY, FriendChatNotify);
	//频道消息通知
	AutoRegisterRespond(IM_CHANNEL_MESSAGE_NOTIFY, ChannelMessageNotify);
	//频道历史消息
	AutoRegisterRespond(IM_CHANNEL_HISTORY_MSG_RESP, ChannelHistoryNotify);
	//录音结束地址通知
	AutoRegisterRespond(IM_RECORD_STOP_RESP, RecordStopNotify);
	//播放语音完成	
	AutoRegisterRespond(IM_RECORD_FINISHPLAY_RESP, StartPlayVoiceRespond);
	//停止语音识别回应
	AutoRegisterRespond(IM_SPEECH_STOP_RESP, SpeechStopRespond);
	//下载文件回应
	AutoRegisterRespond(IM_DOWNLOAD_FILE_RESP, DownLoadFileRespond);
	//云消息推送
	AutoRegisterRespond(IM_CLOUDMSG_NOTIFY, CloundMsgNotify);
	//云消息请求返回
	AutoRegisterRespond(IM_CLOUDMSG_LIMIT_RESP, CloundMsgRepond);
	//云消息确认返回
	AutoRegisterRespond(IM_CLOUDMSG_READ_RESP, CloundMsgReadStatusbackRequest);
	//云消息限制推送返回
	AutoRegisterRespond(IM_CLOUDMSG_LIMIT_NOTIFY, CloundMsgLimitNotify);
	//用户资料信息获取 
	AutoRegisterRespond(IM_USER_GETINFO_RESP, GetUserInfoFriendRespond);
	//重连实现
	AutoRegisterRespond(IM_RECONNECTION_NOTIFY, ReconnectionNotify);
	//频道消息状态
	AutoRegisterRespond(IM_CHANNEL_SENDMSG_RESP, ChannelMessageStateNotify);
	//好友消息状态
	AutoRegisterRespond(IM_CHATT_FRIEND_RESP, FriendMsgStateNotify);
	//网络状态
	AutoRegisterRespond(IM_NET_STATE_NOTIFY, NetWorkStateNotify);
	//最近联系人
	AutoRegisterRespond(IM_FRIEND_NEARLIST_NOTIFY, RecentListNotify);
	//频道登录回应
	AutoRegisterRespond(IM_CHANNEL_LOGIN_RESP, ChanngelLonginRespond);
	//频道修改回应
	AutoRegisterRespond(IM_CHANNEL_MODIFY_RESP, ModChannelIdRespond);
	//用第三方UID取回YV信息返回
	AutoRegisterRespond(IM_GET_THIRDBINDINFO_RESP, GetCpmsgRepond);

	//上传文件回应
	AutoRegisterRespond(IM_UPLOAD_FILE_RESP, UpLoadFileRespond);

	//录音音量大小回应
	AutoRegisterRespond(IM_RECORD_VOLUME_NOTIFY, RecordVoiceNotify);


	//更新地理位置返回
	AutoRegisterRespond(IM_LBS_UPDATE_LOCATION_RESP, UpdatelocationRespond);
	//获取位置信息请求回应
	AutoRegisterRespond(IM_LBS_GET_LOCATION_RESP, GetlocationRespond);
	//搜索好友回应
	AutoRegisterRespond(IM_LBS_SEARCH_AROUND_RESP, SearchAroundRespond);
	//隐藏地理位置完成
	AutoRegisterRespond(IM_LBS_SHARE_LOCATION_RESP, LbsShareRespond);
	//获取语言完成
	AutoRegisterRespond(IM_LBS_GET_SUPPORT_LANG_RESP, LbsGetSupportlangRespond);
	//设置LBS本地化语言完成
	AutoRegisterRespond(IM_LBS_SET_LOCAL_LANG_RESP, LbsSetLocalLangRespond);
	//设置定位方式完成
	AutoRegisterRespond(IM_LBS_SET_LOCATING_TYPE_RESP, LbsSetLocatingRespond);

};
