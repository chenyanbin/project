#ifndef _YVSDK_YVBEGADDFRIENDRET_H_
#define _YVSDK_YVBEGADDFRIENDRET_H_
#include "../YVUtils/YVUtil.h"
#include "../YVType/YVUInfo.h"

namespace YVSDK
{

	//��Ϊ���ѵķ�ʽ 
	enum YVToFriendWay
	{
		BegAddFriend,        //�����������
		ApplyAddFriend,      //����������Ӻ���

	};

	//�Ӻ��ѵĽ��
	enum  YVToFriendRet
	{
		RefuseAddFriend,   //�ܾ���Ϊ����
		BothAddFriend,     //ͬ���Ϊ����,˫����Ϊ����
		OnlyAddFriend,     //���Լ���Ϊ�˺���
	};

	//����Ӻ��ѻ��߱��Ӻ��ѵĽ��
	class _YVAddFriendRet
	{
	public:
		YVToFriendRet ret;
		YVToFriendWay way;    //��Դ
		YVUInfoPtr uinfo;     
	};
	WISDOM_PTR(_YVAddFriendRet, YVAddFriendRetPtr);
	
	//����Ӻ��ѵ�֪ͨ
	class _YVBegFriendNotify
	{
	public:
		YVUInfoPtr uinfo;
		std::string greet;   //�Ӻ��ѵ��к��ı�
	};
	WISDOM_PTR(_YVBegFriendNotify, YVBegFriendNotifyPtr);

}
#endif