#ifndef _YVSDK_YVPLATFORM_H_
#define _YVSDK_YVPLATFORM_H_
#include "YVManager/YVManager.h"


namespace YVSDK
{
	class YVMsgDispatcher;
	
	class YVPlatform
		:public YVUInfoManager,
		public YVFileManager,
		public YVConfigManager,
		public YVPlayerManager,
		public YVContactManager,
		public YVChannalChatManager,
		public YVToolManager,
		public YVFriendChatManager,
		public YVLbsManager
	{
	public:
		static YVPlatform* getSingletonPtr();
		~YVPlatform();
		bool init();
		bool destory();

		//��ʹ�ö�ʱ��������������ÿ֡����һ��
		void updateSdk(float dt);
		//��ȡ�¼��ɷ���
		YVMsgDispatcher* getMsgDispatcher();
	private:
		YVPlatform();

		YVMsgDispatcher* m_msgDispatcher;
		static YVPlatform* s_YVPlatformPtr;
		bool _isInit;
	};
}
#endif