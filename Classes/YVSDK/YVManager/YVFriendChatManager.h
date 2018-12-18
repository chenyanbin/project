#ifndef _FRIENDCHATMANAGER_H_
#define _FRIENDCHATMANAGER_H_
#include <string>
#include "../YVType/YVType.h"
#include "../YVListern/YVListern.h"

namespace YVSDK
{
#define LINITMSGNUM  10

	struct YaYaRespondBase;
	class YVFriendChatManager 
		:public YVListern::YVFinishSpeechListern
	{
	public:
		bool init();
		bool destory();

		bool sendFriendText(uint32 chatWithUid, std::string text, std::string ext);

		bool sendFriendVoice(uint32 chatWithUid, YVFilePathPtr voicePath,
			uint32 voiceTime, std::string ext);

		//����ͼƬ��Ϣ��Ŀǰ����֧��// 
		bool sendFriendImage(uint32 chatWithUid, YVFilePathPtr path);

		//�����һ����Ϣ��һ��
		bool getFriendChatHistoryData(uint32 chatWithUid, int index);
		
		//��������֪ͨ
		void friendMessageNotifyCallback(YaYaRespondBase*);
		
		//����Ϣ֪ͨ//
		void cloundMsgNotifyCallback(YaYaRespondBase*);

		//��Ϣ����״̬֪ͨ
		void friendMessageStateCallback(YaYaRespondBase*);

		//������ȷ����Ϣ��
		bool sendConfirmMsg(uint32 ID, std::string source);

		//���������ط�
		void SendMsgCache(uint32 chatWithUid, YVMessagePtr msg);

		bool SendMsgfriendVoice(uint32 chatWithUid, uint64 id, std::string text, YVFilePathPtr voicePath,
			uint32 voiceTime, std::string ext);
		bool SendMsgfriendText(uint32 chatWithUid, uint64 id, std::string text, std::string ext);

		YVMessageListPtr getFriendChatListById(uint32 uid);

		FriendChatMessageMap getfriendchatmsg();

		InitListern(FriendHistoryChat, YVMessageListPtr);
		InitListern(FriendChat, YVMessagePtr);
		InitListern(FriendChatState, YVMessagePtr)
	protected:
		//����ʶ��ӿ�
		void onFinishSpeechListern(SpeechStopRespond*);
		std::string expand;
		//������Ϣ, isCallFriendChatListern�Ǹ���ʷ ��Ϣʹ�õģ���ʷ��Ϣ���Լ��Ļص�//
		void insertMessage(uint32 chatWithId, YVMessagePtr messageBase, bool isCallFriendChatListern = true);
		//������Ϣ����//
		FriendChatMessageMap m_friendChatMap; 
		//�����е���Ϣ����//
		YVMessageListPtr m_sendMsgCache; 
		//������ʷ��Ϣ����,������ȡ��ʷ��Ϣʹ��
		FriendChatMessageMap m_historyCache;

		uint8 PlatState;    //��Ϣ�Ĳ���״̬ 0���Ѳ��ţ� 1��δ����
	};
}
#endif