#ifndef _YVSDK_YVPATH_H_
#define _YVSDK_YVPATH_H_
#include <string>
#include "YVDef.h"
#include "../YVUtils/YVUtil.h"

namespace YVSDK
{
	//�ļ�״̬
	enum YVFileState
	{
		UnkownState ,

		DownLoadingState,                //���ص���
		UpdateLoadingState ,              //�ϴ�����

		DownLoadErroSate ,                //����ʧ��
		UpdateLoadErrorState,

		OnlyLocalState  ,                  //�����ڱ���״̬
		OnlyNetWorkState,                //����������״̬

		BothExistState ,                  //���缰����״̬����
	};

	//�ļ�·�����ͣ������ļ��뱾���ļ�һ��һ����
	class _YVFilePath
	{
	public:
		_YVFilePath(const char* path, const char* url);
		//��ȡ����·��
		std::string& getLocalPath();
		//��ȡ����·��
		std::string& getUrlPath();
		//���ñ���·��
		void setLocalPath(std::string& path);
		//��������·��
		void setUrlPath(std::string& url);
		//��ȡ�ļ�״̬
		YVFileState getState();
		//��ȡ�ļ�Ψһid(�Լ��������SDK�޹�)
		uint64 getPathId();
		//�����ļ�״̬
		void setState(YVFileState);
	private:
		YVFileState m_state;	//�ļ�״̬����
		uint64 m_id;            //�ļ���������Ψһ��id.���ظ�
		std::string m_path;		//���ص�ַ
		std::string m_url;      //�����ַ
	};

	//����Ϊ֪��ָ��
	WISDOM_PTR(_YVFilePath, YVFilePathPtr);
}
#endif
