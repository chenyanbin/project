#ifndef _YVSDK_YVPLAYERMANAGER_H_
#define _YVSDK_YVPLAYERMANAGER_H_
#include <string>
#include "../YVListern/YVListern.h"
namespace YVSDK
{
	struct YaYaRespondBase;

	class YVPlayerManager
	{
	public:
		bool init();
		bool destory();

		bool cpLogin(std::string uidStr, std::string nameStr);
		bool yyLogin(int userId, std::string passWord);

		void loginResponceCallback(YaYaRespondBase*);
		void cpLoginResponce(YaYaRespondBase*);

		const YVUInfoPtr getLoginUserInfo();
		bool cpLogout();
		bool GetCpuUserinfo(uint32 appid, std::string uid);
		void GetCpuUserinfoResponce(YaYaRespondBase* respond);

		InitListern(CPLogin, CPLoginResponce*);
		InitListern(YYLogin, LoginResponse*);
		InitListern(GetCpuUser, GetCpmsgRepond*);
	private:
		//��¼���Ǹ��û��Ļ�����Ϣ//
		YVUInfoPtr m_loginUserInfo;
	};
}
#endif