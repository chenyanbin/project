/*********************************************************************************
*Copyright(C), 2015 YUNVA Company
*FileName:  RespondFactory.cpp
*Author:  Matt
*Version:  1.0.0
*Date:  2015-5-5
*Description:  ����Э��ĵ��ýṹ��
**********************************************************************************/

#include "YVRespondFactory.h"
#include "../YVProtocol/YVProtocol.h"
namespace YVSDK
{
	RespondFactory* RespondFactory::m_respondFactoryPtr = NULL;

	//�����ʺŵ�¼��Ӧ
	AutoRegisterRespond(IM_LOGIN_RESP, LoginResponse);
	//CP�ʺŵ�¼��Ӧ
	AutoRegisterRespond(IM_THIRD_LOGIN_RESP, CPLoginResponce);

	AutoRegisterRespond(IM_FRIEND_ADD_RESP, AddFriendRepond);
	AutoRegisterRespond(IM_FRIEND_ADD_NOTIFY, AddFriendNotify);
	AutoRegisterRespond(IM_FRIEND_ACCEPT_RESP, FriendAcceptRespond);
	//������ɾ��֪ͨ������Ҫ��������ĺ����б����Ƴ���
	AutoRegisterRespond(IM_FRIEND_DEL_NOTIFY, DelFriendNotify);
	AutoRegisterRespond(IM_FRIEND_RECOMMAND_RESP, RecommendFriendRespond);
	AutoRegisterRespond(IM_FRIEND_SEARCH_RESP, SearchFriendRespond);
	AutoRegisterRespond(IM_FRIEND_OPER_RESP, BlackControlRespond);
	//����ɾ����Ӧ
	AutoRegisterRespond(IM_FRIEND_DEL_RESP, DelFriendRespond);
	//�����б�����
	AutoRegisterRespond(IM_FRIEND_LIST_NOTIFY, FriendListNotify);
	//����������
	AutoRegisterRespond(IM_FRIEND_BLACKLIST_NOTIFY, BlackListNotify);
	//����״̬֪ͨ
	AutoRegisterRespond(IM_FRIEND_STATUS_NOTIFY, FriendStatusNotify);
	//AutoRegisterRespond(IM_CLOUDMSG_NOTIFY, CloundMsgNotify);
	//������Ϣ֪ͨ
	AutoRegisterRespond(IM_CHAT_FRIEND_NOTIFY, FriendChatNotify);
	//Ƶ����Ϣ֪ͨ
	AutoRegisterRespond(IM_CHANNEL_MESSAGE_NOTIFY, ChannelMessageNotify);
	//Ƶ����ʷ��Ϣ
	AutoRegisterRespond(IM_CHANNEL_HISTORY_MSG_RESP, ChannelHistoryNotify);
	//¼��������ַ֪ͨ
	AutoRegisterRespond(IM_RECORD_STOP_RESP, RecordStopNotify);
	//�����������	
	AutoRegisterRespond(IM_RECORD_FINISHPLAY_RESP, StartPlayVoiceRespond);
	//ֹͣ����ʶ���Ӧ
	AutoRegisterRespond(IM_SPEECH_STOP_RESP, SpeechStopRespond);
	//�����ļ���Ӧ
	AutoRegisterRespond(IM_DOWNLOAD_FILE_RESP, DownLoadFileRespond);
	//����Ϣ����
	AutoRegisterRespond(IM_CLOUDMSG_NOTIFY, CloundMsgNotify);
	//����Ϣ���󷵻�
	AutoRegisterRespond(IM_CLOUDMSG_LIMIT_RESP, CloundMsgRepond);
	//����Ϣȷ�Ϸ���
	AutoRegisterRespond(IM_CLOUDMSG_READ_RESP, CloundMsgReadStatusbackRequest);
	//����Ϣ�������ͷ���
	AutoRegisterRespond(IM_CLOUDMSG_LIMIT_NOTIFY, CloundMsgLimitNotify);
	//�û�������Ϣ��ȡ 
	AutoRegisterRespond(IM_USER_GETINFO_RESP, GetUserInfoFriendRespond);
	//����ʵ��
	AutoRegisterRespond(IM_RECONNECTION_NOTIFY, ReconnectionNotify);
	//Ƶ����Ϣ״̬
	AutoRegisterRespond(IM_CHANNEL_SENDMSG_RESP, ChannelMessageStateNotify);
	//������Ϣ״̬
	AutoRegisterRespond(IM_CHATT_FRIEND_RESP, FriendMsgStateNotify);
	//����״̬
	AutoRegisterRespond(IM_NET_STATE_NOTIFY, NetWorkStateNotify);
	//�����ϵ��
	AutoRegisterRespond(IM_FRIEND_NEARLIST_NOTIFY, RecentListNotify);
	//Ƶ����¼��Ӧ
	AutoRegisterRespond(IM_CHANNEL_LOGIN_RESP, ChanngelLonginRespond);
	//Ƶ���޸Ļ�Ӧ
	AutoRegisterRespond(IM_CHANNEL_MODIFY_RESP, ModChannelIdRespond);
	//�õ�����UIDȡ��YV��Ϣ����
	AutoRegisterRespond(IM_GET_THIRDBINDINFO_RESP, GetCpmsgRepond);

	//�ϴ��ļ���Ӧ
	AutoRegisterRespond(IM_UPLOAD_FILE_RESP, UpLoadFileRespond);

	//¼��������С��Ӧ
	AutoRegisterRespond(IM_RECORD_VOLUME_NOTIFY, RecordVoiceNotify);


	//���µ���λ�÷���
	AutoRegisterRespond(IM_LBS_UPDATE_LOCATION_RESP, UpdatelocationRespond);
	//��ȡλ����Ϣ�����Ӧ
	AutoRegisterRespond(IM_LBS_GET_LOCATION_RESP, GetlocationRespond);
	//�������ѻ�Ӧ
	AutoRegisterRespond(IM_LBS_SEARCH_AROUND_RESP, SearchAroundRespond);
	//���ص���λ�����
	AutoRegisterRespond(IM_LBS_SHARE_LOCATION_RESP, LbsShareRespond);
	//��ȡ�������
	AutoRegisterRespond(IM_LBS_GET_SUPPORT_LANG_RESP, LbsGetSupportlangRespond);
	//����LBS���ػ��������
	AutoRegisterRespond(IM_LBS_SET_LOCAL_LANG_RESP, LbsSetLocalLangRespond);
	//���ö�λ��ʽ���
	AutoRegisterRespond(IM_LBS_SET_LOCATING_TYPE_RESP, LbsSetLocatingRespond);

};
