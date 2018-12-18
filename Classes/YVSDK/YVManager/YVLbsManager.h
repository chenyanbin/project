#ifndef __LBSMANAGER_H_
#define __LBSMANAGER_H_

#include <string>
#include <vector>
#include "../YVType/YVType.h"
#include "../YVListern/YVListern.h"


namespace YVSDK
{
	struct YaYaRespondBase;
	class YVLbsManager
	{
	public:
		bool init();
		bool destory();
		//���µ���λ������//
		bool Updatelocation(std::string attach = "");
		//��ȡλ����Ϣ����//
		bool Getlocation();
		//�������������û�(��������λ��)//
		bool SearchAround(std::string  city, uint8	sex, uint32	pageIndex, uint32 theDistance);
		//���ص���λ��//
		bool LbsShare(uint8	hide);
		//��ȡ֧�ֵģ�����������������Ϣ�ȣ����ػ������б�//
		bool LbsGetSupportlang();
		//����LBS���ػ�����//
		bool LbsSetLocalLang(std::string lang_code, std::string lang_name);
		//���ö�λ��ʽ//
		bool LbsSetLocating(uint8 locate_gps, uint8 locate_wifi, uint8 locate_cell, uint8 locate_network);

		//��Ӧ//
		void UpdatelocationCallback(YaYaRespondBase*);
		void GetlocationCallback(YaYaRespondBase*);
		void SearchAroundCallback(YaYaRespondBase*);
		void LbsShareCallback(YaYaRespondBase*);
		void LbsGetSupportlangCallback(YaYaRespondBase*);
		void LbsSetLocalLangCallback(YaYaRespondBase*);
		void LbsSetLocatingCallback(YaYaRespondBase*);


		//InitListern(CloundMsgConfirm, CloundMsgReadStatusbackRequest*);
		//InitListern(CloundMsg, CloundMsgNotify*);
		//InitListern(FriendChat, YVMessagePtr);

		InitListern(Getlocation, GetlocationRespond*);
		InitListern(Updatelocation, UpdatelocationRespond*);
		InitListern(SearchAround, SearchAroundRespond*);
		InitListern(LbsSetLocalLang, LbsSetLocalLangRespond*);
		InitListern(LbsShare, LbsShareRespond*);

		InitListern(LbsGetSupportlang, LbsGetSupportlangRespond*);
		InitListern(LbsSetLocating, LbsSetLocatingRespond*);

	private:
		bool addFriendInfo(YVUInfoPtr info);
		bool delFriendInfo(uint32 uid);
		bool addBlackInfo(YVUInfoPtr info);
		bool delBlackInfo(uint32 uid);

		void delAllBlackInfo();
		void delAllFriendInfo();

		YVUInfoMap m_friendInfos;
		YVUInfoMap m_blackInfos;
		YVUInfoMap m_nearInfos;

		void insertMessage(uint32 chatWithId, YVMessagePtr messageBase, bool isCallFriendChatListern = true);
		//����Ϣ
		YVMessageListPtr Notifymsglist;
	};
}
#endif