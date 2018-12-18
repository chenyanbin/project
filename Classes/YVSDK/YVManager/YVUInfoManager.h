#ifndef _YVSDK_YVUINFOMANAGER_H_
#define _YVSDK_YVUINFOMANAGER_H_
#include <string>
#include <vector>
#include <map>

#include "../YVType/YVType.h"
#include "../YVUtils/YVUtil.h"
#include "../YVListern/YVListern.h"

namespace YVSDK
{
	class YVUInfoManager
	{
	public:
		//ͨ��uid��ȡ�û���Ϣ
		YVUInfoPtr getUInfoById(uint32 id);
		//�����ڴ��е��û���Ϣ��������û������ڣ������.
		//ע�⣬��װ�����У����б�ʵʱ������Ϣ����ʷ������Ϣ���ô˽ӿ�
		void updateUInfo(YVUInfoPtr);
	private:
		typedef std::map<uint32, YVUInfoPtr> UInfoMap;
		//���е��û���Ϣ
		UInfoMap m_uinfos;
	};
}

#endif