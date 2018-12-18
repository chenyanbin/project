#ifndef __FRIENDMANAGER_H_
#define __FRIENDMANAGER_H_

#include <string>
#include <vector>
#include "../YVType/YVType.h"
#include "../YVListern/YVListern.h"

namespace YVSDK
{
	struct YaYaRespondBase;
	class YVContactManager
	{
	public:
		bool init();
		bool destory();
		//����Ӻ���//
		bool addFriend(uint32 uid, std::string greet = "");
		//ɾ������isRmoveSelf�Ƿ�Ҫ��Է�Ҳɾ����//
		bool delFriend(uint32 uid, bool isRmoveSelf = true);
		//���ں���//
		bool addBlack(uint32 uid);
		//�Ƴ�������//
		bool delBlack(uint32 uid);
		//ͬ��Ӻ���//
		bool agreeFriend(uint32 uid);
		//�ܾ��Ӻ���//
		bool opposeFriend(uint32 uid);
		//���Һ���//
		bool searchFiend(std::string& keyWord, int start, int count);
		//��ȡ�Ƽ�����//
		bool recommendFriend(int start, int count);
		//����������ȡ��ȡ�û�����Ϣ//
		bool getUserInfoSync(uint32 uid);
		//ɾ�������ϵ��//
		bool DelRecent(uint32 uid);

		YVUInfoPtr getFriendInfo(uint32 uid);
		YVUInfoPtr getBlackInfo(uint32 uid);

		YVUInfoMap& getAllFriendInfo();
		YVUInfoMap& getAllBlackInfo();
	public:
		void friendsNotifyCallback(YaYaRespondBase*);
		void blacksNotifyCallback(YaYaRespondBase*);
		void nearsNotifyCallback(YaYaRespondBase*);
		void addFriendCallback(YaYaRespondBase*);
		void delFriendCallback(YaYaRespondBase*);
		void blackControlCallback(YaYaRespondBase*);
		//����ͬ��Ӻ���//
		void addFriendRetCallback(YaYaRespondBase*);
		void searchResponceCallback(YaYaRespondBase*);
		void recommendNotifyCallback(YaYaRespondBase*);
		//��ȡ�������Ϸ���//
		void getUserInfoCallBack(YaYaRespondBase*);
		//����ɾ����//
		void delFriendNotify(YaYaRespondBase*);
		//����״̬ //
		void friendStatusNotify(YaYaRespondBase*);
		//����Ӻ���//
		void begAddFriendNotify(YaYaRespondBase*);
		//����Ϣȷ�ϻ�Ӧ
		void CloundMsgConfirmCallback(YaYaRespondBase*);
		//����Ϣ����
		void CloundMsgNotifyCallback(YaYaRespondBase*);
		//ɾ�������ϵ�˻�Ӧ
		void DelRecentCallback(YaYaRespondBase*);

		YVMessageListPtr getNotifymsg();

	public:
		InitListern(AddFriend, YVUInfoPtr);
		InitListern(DelFriend, YVUInfoPtr);
		InitListern(DelBlack, YVUInfoPtr);
		InitListern(AddBlack, YVUInfoPtr);
		InitListern(UpdateUserInfo, YVUInfoPtr);
		InitListern(RecommendFriendRet, RecommendFriendRespond*);
		InitListern(SearchFriendRet, SearchFriendRespond*);
		
		InitListern(BegAddFriend, YVBegFriendNotifyPtr);
		InitListern(AddFriendRet, YVAddFriendRetPtr);

		InitListern(FriendList, FriendListNotify*);
		InitListern(BlackList, BlackListNotify*);

		InitListern(CloundMsgConfirm, CloundMsgReadStatusbackRequest*);
		InitListern(CloundMsg, CloundMsgNotify*);
		//InitListern(FriendChat, YVMessagePtr);

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