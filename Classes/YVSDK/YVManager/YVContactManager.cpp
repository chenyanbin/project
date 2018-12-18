/*********************************************************************************
*Copyright(C), 2015 YUNVA Company
*FileName:  YVProtocol.h
*Author:  Matt
*Version:  1.0.3
*Date:  2015-5-7
*Description:  ��ϵ�˹������Ѻ�������
**********************************************************************************/

#include "YVContactManager.h"
#include "../YVSDK.h"

using namespace YVSDK;

bool YVContactManager::init()
{
	YVMsgDispatcher*  msgDispatcher = YVPlatform::getSingletonPtr()->getMsgDispatcher();

	//�����б�
	msgDispatcher->registerMsg(IM_FRIEND_LIST_NOTIFY, this, &YVContactManager::friendsNotifyCallback);
	//�������б�
	msgDispatcher->registerMsg(IM_FRIEND_BLACKLIST_NOTIFY, this, &YVContactManager::blacksNotifyCallback);
	//�����ϵ���б�
	msgDispatcher->registerMsg(IM_FRIEND_NEARLIST_NOTIFY, this, &YVContactManager::nearsNotifyCallback);
	//��Ӻ��ѳɹ���Ӧ
	msgDispatcher->registerMsg(IM_FRIEND_ADD_RESP, this, &YVContactManager::addFriendCallback);
	//ɾ�����ѻ�Ӧ
	msgDispatcher->registerMsg(IM_FRIEND_DEL_RESP, this, &YVContactManager::delFriendCallback);
	//����������
	msgDispatcher->registerMsg(IM_FRIEND_OPER_RESP, this, &YVContactManager::blackControlCallback);
	//������ӽ��
	msgDispatcher->registerMsg(IM_FRIEND_ACCEPT_RESP, this, &YVContactManager::addFriendRetCallback);
	//�������ѽ��
	msgDispatcher->registerMsg(IM_FRIEND_SEARCH_RESP, this, &YVContactManager::searchResponceCallback);
	//�Ƽ��ý��
	msgDispatcher->registerMsg(IM_FRIEND_RECOMMAND_RESP, this, &YVContactManager::recommendNotifyCallback);
	//�鿴�û���Ϣ
	msgDispatcher->registerMsg(IM_USER_GETINFO_RESP, this, &YVContactManager::getUserInfoCallBack);
	//������ɾ����
	msgDispatcher->registerMsg(IM_FRIEND_DEL_NOTIFY, this, &YVContactManager::delFriendNotify);
	//����״̬����
	msgDispatcher->registerMsg(IM_FRIEND_STATUS_NOTIFY, this, &YVContactManager::friendStatusNotify);
	//����Ӻ���֪ͨ;
	msgDispatcher->registerMsg(IM_FRIEND_ADD_NOTIFY, this, &YVContactManager::begAddFriendNotify);
	//����Ϣȷ�ϻ�Ӧ
	msgDispatcher->registerMsg(IM_CLOUDMSG_READ_RESP, this, &YVContactManager::CloundMsgConfirmCallback);
	//����Ϣ����
	msgDispatcher->registerMsg(IM_CLOUDMSG_NOTIFY, this, &YVContactManager::CloundMsgNotifyCallback);

	Notifymsglist = new _YVMessageList();
	return true;
}

bool YVContactManager::destory()
{
	YVMsgDispatcher*  msgDispatcher = YVPlatform::getSingletonPtr()->getMsgDispatcher();
	//�����б�
	msgDispatcher->unregisterMsg(IM_FRIEND_LIST_NOTIFY, this);
	//�������б�
	msgDispatcher->unregisterMsg(IM_FRIEND_BLACKLIST_NOTIFY, this);
	//�����ϵ���б�
	msgDispatcher->unregisterMsg(IM_FRIEND_NEARLIST_NOTIFY, this);
	//��Ӻ��ѳɹ���Ӧ
	msgDispatcher->unregisterMsg(IM_FRIEND_ADD_RESP, this);
	//ɾ�����ѻ�Ӧ
	msgDispatcher->unregisterMsg(IM_FRIEND_DEL_RESP, this);
	//����������
	msgDispatcher->unregisterMsg(IM_FRIEND_OPER_RESP, this);
	//���˼Ӻ��Ѻ����ͬ����߾ܾ�
	msgDispatcher->unregisterMsg(IM_FRIEND_ACCEPT_RESP, this);
	//�������ѽ��
	msgDispatcher->unregisterMsg(IM_FRIEND_SEARCH_RESP, this);
	//�Ƽ��ý��
	msgDispatcher->unregisterMsg(IM_FRIEND_RECOMMAND_RESP, this);
	//�鿴�û���Ϣ
	msgDispatcher->unregisterMsg(IM_USER_GETINFO_RESP, this);
	//������ɾ����
	msgDispatcher->unregisterMsg(IM_FRIEND_DEL_NOTIFY, this);
	//����״̬����
	msgDispatcher->unregisterMsg(IM_FRIEND_STATUS_NOTIFY, this);
	//�������֪ͨ
	msgDispatcher->unregisterMsg(IM_FRIEND_ADD_NOTIFY, this);
	//����Ϣȷ�ϻ�Ӧ
	msgDispatcher->unregisterMsg(IM_CLOUDMSG_READ_RESP, this);
	//����Ϣ����
	msgDispatcher->unregisterMsg(IM_CLOUDMSG_NOTIFY, this);
	//�ڴ�����
	delAllBlackInfo();
	delAllFriendInfo();
	Notifymsglist->clear();
	return true;
}

bool YVContactManager::addFriend(uint32 uid, std::string greet)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	if (platform->getLoginUserInfo()->userid == uid)
	{
		return false;
	}

	AddFriendRequest r;
	r.userid = uid;
	r.greet = greet;
	return msgDispatcher->send(&r);
}

bool YVContactManager::delFriend(uint32 uid, bool isRmoveSelf)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	DelFriendRequest r;
	r.del_friend = uid;
	r.act = isRmoveSelf ? df_remove_from_list : df_exit_in_list;
	return  msgDispatcher->send(&r);
}

bool YVContactManager::addBlack(uint32 uid)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	
	BlackControlRequest r;
	r.operId = uid;
	r.userId = platform->getLoginUserInfo()->userid;
	r.act = oper_add_blacklist;

	return 	msgDispatcher->send(&r);
}

bool YVContactManager::delBlack(uint32 uid)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();


	BlackControlRequest r;
	r.operId = uid;
	r.userId = platform->getLoginUserInfo()->userid;
	r.act = oper_del_blacklist;

	return 	msgDispatcher->send(&r);
}

bool YVContactManager::opposeFriend(uint32 uid)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	FriendAcceptRequest q;
	q.affirm = af_refuse;
	q.userid = uid;

	return 	msgDispatcher->send(&q);
}

bool YVContactManager::agreeFriend(uint32 uid)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();
	
	FriendAcceptRequest q;
	q.affirm = af_agree_add;
	q.userid = uid;
	
	return 	msgDispatcher->send(&q);
}

bool YVContactManager::getUserInfoSync(uint32 uid)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	GetUserInfoRequest q;
	q.userid = uid;

	return 	msgDispatcher->send(&q);
}

bool YVContactManager::searchFiend(std::string& keyWord, int start, int count)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	SearchFriendRequest r;
	r.count = count;
	r.start = start;
	r.keyword.append(keyWord);

	return 	msgDispatcher->send(&r);
}

bool YVContactManager::recommendFriend(int start, int count)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	RecommendFriendRequest r;
	r.count = count;
	r.start = start;

	return 	msgDispatcher->send(&r);
}

void YVContactManager::friendsNotifyCallback(YaYaRespondBase* request)
{
	FriendListNotify* r = (FriendListNotify*)request;
	for (std::vector<YaYaUserInfo*>::iterator it = r->userInfos.begin();
		it != r->userInfos.end(); ++it)
	{
		YaYaUserInfo* _netUserInfo = (*it);   //���������յ����û���Ϣ
		
		YVUInfoPtr userInfo = new _YVUInfo();
		userInfo->userid = _netUserInfo->userid;
		userInfo->nickname.append(_netUserInfo->nickname);
		
		userInfo->header = YVPlatform::getSingletonPtr()->getYVPathByUrl(_netUserInfo->iconurl);
		/*userInfo->online = _netUserInfo->online;
		userInfo->userlevel.append(_netUserInfo->userlevel);
		userInfo->viplevel.append(_netUserInfo->viplevel);
		userInfo->shieldmsg = _netUserInfo->shieldmsg;
		userInfo->sex = _netUserInfo->sex;
		userInfo->ext.append(_netUserInfo->ext);
		userInfo->group.append(_netUserInfo->group);
		userInfo->note.append(_netUserInfo->note);*/
		
		addFriendInfo(userInfo);
	}
	callFriendListListern(r);
}

void YVContactManager::blacksNotifyCallback(YaYaRespondBase* request)
{
	//m_blackInfos.clear();
	BlackListNotify* r = (BlackListNotify*)request;

	for (std::vector<YaYaUserInfo*>::iterator it = r->userInfos.begin();
		it != r->userInfos.end(); ++it)
	{
		YaYaUserInfo* _netUserInfo = (*it);   //���������յ����û���Ϣ

		YVUInfoPtr userInfo = new _YVUInfo();
		userInfo->userid = _netUserInfo->userid;
		userInfo->nickname.append(_netUserInfo->nickname);

		userInfo->header = YVPlatform::getSingletonPtr()->getYVPathByUrl(_netUserInfo->iconurl);
		/*userInfo->headerPath = YVFilePath::getUrlPath(_netUserInfo->iconurl);
		userInfo->online = _netUserInfo->online;
		userInfo->userlevel.append(_netUserInfo->userlevel);
		userInfo->viplevel.append(_netUserInfo->viplevel);
		userInfo->shieldmsg = _netUserInfo->shieldmsg;
		userInfo->sex = _netUserInfo->sex;
		userInfo->ext.append(_netUserInfo->ext);
		userInfo->group.append(_netUserInfo->group);
		userInfo->note.append(_netUserInfo->note);*/

		addBlackInfo(userInfo);
	}
	callBlackListListern(r);
}

void YVContactManager::nearsNotifyCallback(YaYaRespondBase* respond)
{
	RecentListNotify* RecentNotify = (RecentListNotify*)respond;
	YVPlatform* platform = YVPlatform::getSingletonPtr();

	for (std::vector<YaYaRecentInfo*>::iterator it = RecentNotify->RecentConactList.begin();
		it != RecentNotify->RecentConactList.end(); ++it)
	{
		YaYaRecentInfo* _RecentInfo = (*it);
		_RecentInfo->unread;

 		YaYaP2PChatNotify* p2pmsg = static_cast<YaYaP2PChatNotify*> (_RecentInfo->Notifymsg);

		YVMessagePtr msg = NULL;

		switch (p2pmsg->type)
		{
		case chat_msgtype_text:
			msg = new _YVTextMessage(p2pmsg->data);
			break;
		case chat_msgtype_audio:
			msg = new _YVVoiceMessage(p2pmsg->data, true, p2pmsg->audiotime, p2pmsg->attach);
			break;
		case chat_msgtype_image:
			msg = new _YVImageMessage();
			break;
		default:
			break;
		}

		msg->sendTime = p2pmsg->sendtime;
		msg->state = p2pmsg->unread == 0 ? YVMessageStatusUnread : YVMessageStatusCreated;
		//msg->source = Notifymsg->source;
		if (platform->getLoginUserInfo()->userid == p2pmsg->userid)
		{
			msg->sendId = _RecentInfo->userinfo->userid;
			msg->recvId = p2pmsg->userid;
		}
		else
		{
			msg->sendId = _RecentInfo->userinfo->userid;
			msg->recvId = platform->getLoginUserInfo()->userid;
		}
		msg->index = _RecentInfo->unread;     //δ������
		msg->endId = _RecentInfo->endId;     
		msg->id = _RecentInfo->userinfo->userid;
		Notifymsglist->insertMessage(msg);

		//callFriendChatListern(msg);
		//onFriendChatListern(msg);

		//insertMessage(Notifymsg->id, msg, false);

		YVSDK::YVUInfoPtr uinfo = YVPlatform::getSingletonPtr()->getUInfoById(_RecentInfo->userinfo->userid);
		if (uinfo == NULL)
		{
			uinfo = new _YVUInfo();
			uinfo->header = platform->getYVPathByUrl(_RecentInfo->userinfo->iconurl);
			uinfo->nickname.append(_RecentInfo->userinfo->nickname);
			uinfo->userid = _RecentInfo->userinfo->userid;
			platform->updateUInfo(uinfo);
			//platform->getUserInfoSync(uinfo->userid);
		}

	}
	//m_nearInfos.clear();
}

void YVContactManager::addFriendRetCallback(YaYaRespondBase* respond)
{
	FriendAcceptRespond* r = (FriendAcceptRespond*)respond;
	YVAddFriendRetPtr ret = new _YVAddFriendRet;
	ret->way = ApplyAddFriend;  //��������ӵĺ���

	if (r->affirm == af_agree || r->affirm == af_agree_add)
	{
		//�ж��Ƿ��Ǻ�������Ա//
		YVUInfoPtr userInfo = getBlackInfo(r->userid);
		if (userInfo != NULL)
		{
			addFriendInfo(userInfo);
			delBlackInfo(r->userid);
		}
		else
		{
			//û�к������ݣ���������֮;
			userInfo = new _YVUInfo();
			userInfo->userid = r->userid;
			addFriendInfo(userInfo);
			getUserInfoSync(r->userid);
		}
		ret->ret = (r->affirm == af_agree_add ? BothAddFriend : OnlyAddFriend);
		ret->uinfo = userInfo;
	}
	else
	{
		YVUInfoPtr userInfo = new _YVUInfo();
		userInfo->userid = r->userid;
		getUserInfoSync(r->userid);
		ret->ret = RefuseAddFriend;
		ret->uinfo = userInfo;
	}
	callAddFriendRetListern(ret);
}

bool YVContactManager::DelRecent(uint32 uid)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	DelRecentRequest r;
	r.userid = uid;
	return  msgDispatcher->send(&r);
}

//ɾ�������ϵ�˻�Ӧ
void YVContactManager::DelRecentCallback(YaYaRespondBase* respond)    
{
	DelRecentRepond* r = (DelRecentRepond*)respond;
}

void YVContactManager::addFriendCallback(YaYaRespondBase* respond)
{
	AddFriendRepond* r = (AddFriendRepond*)respond;

	YVPlatform::getSingletonPtr()->sendConfirmMsg(r->indexId,r->source);   //����ȷ����Ϣ

	YVAddFriendRetPtr ret = new _YVAddFriendRet;
	ret->way = BegAddFriend;
	YVUInfoPtr userInfo = getBlackInfo(r->userid);
	if (userInfo == NULL)
	{
		userInfo = new _YVUInfo();
		userInfo->userid = r->userid;
		userInfo->nickname = r->name;
		if (r->url.length() > 0)
		{
			userInfo->header = YVPlatform::getSingletonPtr()->getYVPathByUrl(r->url);
		}
		//getUserInfoSync(r->userid);   //��ȡ���س�������
		YVPlatform::getSingletonPtr()->updateUInfo(userInfo);
	}

	//�ܾ��Ӻ���
	if (r->affirm == af_refuse)
	{
		ret->ret = RefuseAddFriend;
	}
	else
	{
		ret->ret = (r->affirm == af_agree_add) ? BothAddFriend : OnlyAddFriend;
		addFriendInfo(userInfo);
		callAddFriendListern(userInfo);
		delBlackInfo(r->userid);
	}
	ret->uinfo = userInfo;
	callAddFriendRetListern(ret);
}

void YVContactManager::delFriendCallback(YaYaRespondBase* request)
{
	DelFriendRespond* r = (DelFriendRespond*)request;
	delFriendInfo(r->del_friend);
}

void YVContactManager::blackControlCallback(YaYaRespondBase* request)
{
	BlackControlRespond* r = (BlackControlRespond*)request;

	if (r->act == oper_add_blacklist)
	{
		//���Һ����б��е�����
		YVUInfoPtr userinfo = getFriendInfo(r->operId);
		if (userinfo != NULL)
		{
			addBlackInfo(userinfo);
			delFriendInfo(r->operId);
		}
		else
		{
			//�����б���û�к�������Ϣ
			userinfo = new _YVUInfo();;
			userinfo->userid = r->operId;
			//userinfo->online = r->oper_state;
			addBlackInfo(userinfo);
			//��ȡ��������Ϣ
			getUserInfoSync(r->operId);
		}
	}
	else if (r->act == oper_del_blacklist)
	{
		delBlackInfo(r->operId);
	}
}

YVMessageListPtr YVContactManager::getNotifymsg()
{
	return Notifymsglist;
}
void YVContactManager::CloundMsgNotifyCallback(YaYaRespondBase* respond)
{
	CloundMsgNotify* Notifymsg = static_cast<CloundMsgNotify*>(respond);

//	return;
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	//platform->sendConfirmMsg(Notifymsg->id, Notifymsg->source);

	if (Notifymsg->unread == 0)
	{
		return;
	}
	//��Ϊ������Ϣʱ//
	if (Notifymsg->source == CLOUDMSG_FRIEND)
	{
		YaYaP2PChatNotify* p2pmsg = static_cast<YaYaP2PChatNotify*> (Notifymsg->packet);

		YVMessagePtr msg = NULL;

		switch (p2pmsg->type)
		{
		case chat_msgtype_text:
			msg = new _YVTextMessage(p2pmsg->data);
			break;
		case chat_msgtype_audio:
			msg = new _YVVoiceMessage(p2pmsg->data, true, p2pmsg->audiotime, p2pmsg->attach);
			break;
		case chat_msgtype_image:
			msg = new _YVImageMessage();
			break;
		default:
			break;
		}
		
		msg->sendTime = p2pmsg->sendtime;
		msg->state = p2pmsg->unread == 0 ? YVMessageStatusUnread : YVMessageStatusCreated;
		msg->source = Notifymsg->source;
		if (platform->getLoginUserInfo()->userid == p2pmsg->userid)
		{
			msg->sendId = p2pmsg->userid;
			msg->recvId = Notifymsg->id;
		}
		else
		{
			msg->sendId = Notifymsg->id;
			msg->recvId = platform->getLoginUserInfo()->userid;
		}
		msg->index = Notifymsg->unread;     //δ������
		msg->id = Notifymsg->id;
		msg->endId = Notifymsg->endid;
		Notifymsglist->insertMessage(msg);

		//callFriendChatListern(msg);
		//onFriendChatListern(msg);

		//insertMessage(Notifymsg->id, msg, false);

		YVSDK::YVUInfoPtr uinfo = YVPlatform::getSingletonPtr()->getUInfoById(Notifymsg->id);
		if (uinfo == NULL)
		{
			uinfo = new _YVUInfo();
			uinfo->header = platform->getYVPathByUrl(p2pmsg->headicon);
			uinfo->nickname.append(p2pmsg->name);
			uinfo->userid = Notifymsg->id;
			platform->updateUInfo(uinfo);
			//getUserInfoSync(Notifymsg->id);
		}
	} 
	if (Notifymsg->source == CLOUDMSG_SYSTEM)
	{

	}
	//Notifylist ��Ϣ�б���
	//callCloundMsgListern(Notifymsg);

}

void YVContactManager::insertMessage(uint32 chatWithId, YVMessagePtr messageBase, bool isCallFriendChatListern)
{

}

void YVContactManager::CloundMsgConfirmCallback(YaYaRespondBase* respond)
{
	CloundMsgReadStatusbackRequest* r = static_cast<CloundMsgReadStatusbackRequest*>(respond);
	callCloundMsgConfirmListern(r);
}

void YVContactManager::searchResponceCallback(YaYaRespondBase* respond)
{
	SearchFriendRespond* r = static_cast<SearchFriendRespond*>(respond);
	callSearchFriendRetListern(r);
}

void YVContactManager::recommendNotifyCallback(YaYaRespondBase* respond)
{
	RecommendFriendRespond* r = static_cast<RecommendFriendRespond*>(respond);
	callRecommendFriendRetListern(r);
}

void YVContactManager::begAddFriendNotify(YaYaRespondBase* respond)
{
	AddFriendNotify* r = static_cast<AddFriendNotify*>(respond);

	YVPlatform::getSingletonPtr()->sendConfirmMsg(r->indexId, r->source);   //����ȷ����Ϣ

	YVUInfoPtr uinfo = new _YVUInfo;
	if (r->url.length() > 0)
	{
		uinfo->header = YVPlatform::getSingletonPtr()->getYVPathByUrl(r->url);
	}
	uinfo->nickname.append(r->name);
	uinfo->userid = r->userid;
	YVBegFriendNotifyPtr notify = new _YVBegFriendNotify;
	notify->greet.append(r->greet);
	notify->uinfo = uinfo;

	//Notifymsglist->insertMessage(uinfo);

	callBegAddFriendListern(notify);
}

bool YVContactManager::addFriendInfo(YVUInfoPtr info)
{
	YVUInfoMap::iterator it = m_friendInfos.find(info->userid);
	if (it != m_friendInfos.end())
	{
		return false;
	}
	YVPlatform::getSingletonPtr()->updateUInfo(info);
	m_friendInfos.insert(std::make_pair(info->userid, info));
	return true;
}

bool YVContactManager::delFriendInfo(uint32 uid)
{
	YVUInfoMap::iterator it = m_friendInfos.find(uid);
	if (it == m_friendInfos.end())
	{
		return false;
	}
	YVUInfoPtr info =  it->second;
	m_friendInfos.erase(it);
	callDelFriendListern(info);
	return true;
}

bool YVContactManager::addBlackInfo(YVUInfoPtr info)
{
	if (info == NULL) return false;
	YVPlatform::getSingletonPtr()->updateUInfo(info);
	YVUInfoMap::iterator it = m_blackInfos.find(info->userid);
	if (it != m_blackInfos.end())
	{
		return false;
	}
	m_blackInfos.insert(std::make_pair(info->userid, info));	
	callAddBlackListern(info);
	return true;
}

bool YVContactManager::delBlackInfo(uint32 uid)
{
	YVUInfoMap::iterator it = m_blackInfos.find(uid);
	if (it == m_blackInfos.end())
	{
		return false;
	}
	YVUInfoPtr info = it->second;
	m_blackInfos.erase(it);
	callDelBlackListern(info);
	return true;
}

YVUInfoPtr YVContactManager::getFriendInfo(uint32 uid)
{
	YVUInfoMap::iterator it = m_friendInfos.find(uid);
	if (it == m_friendInfos.end())
	{
		return NULL;
	}
	return it->second;
}

YVUInfoPtr YVContactManager::getBlackInfo(uint32 uid)
{
	YVUInfoMap::iterator it = m_blackInfos.find(uid);
	if (it == m_blackInfos.end())
	{
		return NULL;
	}
	return it->second;
}

//��ȡ�������Ϸ���
void YVContactManager::getUserInfoCallBack(YaYaRespondBase* respond)
{
	GetUserInfoFriendRespond* r = static_cast<GetUserInfoFriendRespond*>(respond);
	
	//���º���������
	YVUInfoPtr blackInfo = getBlackInfo(r->userid);
	if (blackInfo != NULL)
	{
		
		blackInfo->nickname = r->nickname;
		blackInfo->header = YVPlatform::getSingletonPtr()->getYVPathByUrl(r->headicon);
		/*blackInfo->userlevel = r->userlevel;
		blackInfo->viplevel = r->viplevel;
		blackInfo->sex = r->sex;*/
		//��������
		callUpdateUserInfoListern(blackInfo);
		return;
	}

	//���º�������
	YVUInfoPtr friendInfo = getFriendInfo(r->userid);
	if (friendInfo != NULL)
	{
		
		friendInfo->nickname = r->nickname;
		friendInfo->header = YVPlatform::getSingletonPtr()->getYVPathByUrl(r->headicon);
		/*friendInfo->sex = r->sex;
		if (friendInfo->headerPath) friendInfo->headerPath->release();
		friendInfo->headerPath = YVFilePath::getUrlPath(r->headicon);
		friendInfo->userlevel = r->userlevel;
		friendInfo->viplevel = r->viplevel;*/
		callUpdateUserInfoListern(friendInfo);
		return;
	}

	//�Ǻ��ѷǺ�������Ա
	YVUInfoPtr userinfo = new _YVUInfo();
	userinfo->userid = r->userid;	
	userinfo->nickname = r->nickname;     //�ǳ�
	userinfo->header = YVPlatform::getSingletonPtr()->getYVPathByUrl(r->headicon);   //ͼ���ַ
	//userinfo->sex = r->sex;     //�Ա�
	//userinfo->userlevel = r->userlevel;     //�û��ȼ�
	//userinfo->viplevel = r->viplevel;     //�û�VIP�ȼ�
	//userinfo->ext = r->ext;     //��չ�ֶ�

	callUpdateUserInfoListern(userinfo);
	YVPlatform::getSingletonPtr()->updateUInfo(userinfo);
}

void YVContactManager::delFriendNotify(YaYaRespondBase* respond)
{
	DelFriendNotify* r = static_cast<DelFriendNotify*>(respond);
	if (r->del_fromlist == df_remove_from_list)
	{
		delFriendInfo(r->del_friend);
	}
}

void YVContactManager::friendStatusNotify(YaYaRespondBase* respond)
{
	FriendStatusNotify* r = static_cast<FriendStatusNotify*>(respond);

	//���º�������
	YVUInfoPtr friendInfo = getFriendInfo(r->userid);
	if (friendInfo != NULL)
	{
		friendInfo->online = r->status;
	}
	else
	{
		friendInfo = new _YVUInfo();
		friendInfo->userid = r->userid;
		friendInfo->online = r->status;
	}

	YVPlatform* yv = YVPlatform::getSingletonPtr();
	yv->updateUInfo(friendInfo);
	callUpdateUserInfoListern(friendInfo);

}

YVUInfoMap& YVContactManager::getAllFriendInfo()
{
	return m_friendInfos;
}

YVUInfoMap& YVContactManager::getAllBlackInfo()
{
	return m_blackInfos;
}

void YVContactManager::delAllBlackInfo()
{
	m_blackInfos.clear();
}

void YVContactManager::delAllFriendInfo()
{
	m_friendInfos.clear();
}