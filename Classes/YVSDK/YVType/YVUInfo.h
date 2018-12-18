#ifndef _YVSDK_YVUINFO_H_
#define _YVSDK_YVUINFO_H_
#include <map>
#include <string>
#include "../YVUtils/YVUtil.h"
#include "YVFilePath.h"

namespace YVSDK
{
	//���¼�û�֮��Ĺ�ϵ����
	enum YVRelation
	{
		FriendRelation,    //���ѹ�ϵ
		BlackRelation,     //������
		StrangerRelation,  //İ����
	};

	//�û���չ��Ϣ����
	enum  YVUExtInfoType
	{
		
	};

	//�û���Ϣ��ʵ��
	class _YVUInfo
	{
	public:
		uint32   userid;        //�û�id
		std::string nickname;   //�û��ǳ�
		YVFilePathPtr header;       //�û�ͼ���ַ
		int online;   //�Ƿ����ߣ����ֶκ��ѹ�ϵ����Ч
	private:
		std::map<YVUExtInfoType, std::string> m_uinfos;   //������������Ϣ����չ��Ϣ
	};

	//����Ϊ֪��ָ��
	WISDOM_PTR(_YVUInfo, YVUInfoPtr);
	
	//���û�UIΪkey���û���Ϣ����
	typedef  std::map<uint32, YVUInfoPtr> YVUInfoMap;
}
#endif