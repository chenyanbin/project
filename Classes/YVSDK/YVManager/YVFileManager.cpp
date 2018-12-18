#include "YVFileManager.h"
#include "../YVSDK.h"
#include <time.h>
#include <sstream>

using namespace  YVSDK;

YVFilePathPtr YVFileManager::getYVPathByUrl(std::string& url)
{
	for (FileMap::iterator it = m_files.begin();
		it != m_files.end(); ++it)
	{
		if (it->second->getUrlPath() == url)
		{
			return it->second;
		}
	}

	return newYVPath(NULL, url.c_str());
}

YVFilePathPtr YVFileManager::getYVPathByLocal(std::string& path)
{
	for (FileMap::iterator it = m_files.begin();
		it != m_files.end(); ++it)
	{
		if (it->second->getLocalPath() == path)
		{
			return it->second;
		}
	}

	return newYVPath(path.c_str(), NULL);
}

YVFilePathPtr YVFileManager::getYVPathById(uint64 id)
{
	for (FileMap::iterator it = m_files.begin();
		it != m_files.end(); ++it)
	{
		if (it->second->getPathId() == id)
		{
			return it->second;
		}
	}

	return NULL;
}

YVFilePathPtr YVFileManager::newYVPath(const char* localpath, const char* url)
{
	_YVFilePath*  _path = new _YVFilePath(localpath, url);
	YVFilePathPtr path = _path;
	m_files.insert(std::make_pair(path->getPathId(), path));
	return path;
}

YVFilePathPtr YVFileManager::getYVPathByRand(std::string extren)
{

	//��ʱ������ļ���
	time_t now;
	int timeStamp = time(&now);
	char timeStr[12] = { 0 };
	sprintf(timeStr, "%d", timeStamp);

	//�������·��
	YVConfigManager* platform = YVPlatform::getSingletonPtr();
	std::string pathStr;
	if (platform->tempPath.length() == 0)
	{
		printf("error:the yvsdk tmppath length is zero");
	}

	pathStr.append(platform->tempPath);
	pathStr.append(timeStr);

	//����ͻ��ʩ(�ͻ���Ӧ��������)
	static  uint32 _id = 0;
	std::stringstream ss;
	ss << "_" << _id ;
	pathStr.append(ss.str());

	//�����ļ���׺��
	pathStr.append(".");
	pathStr.append(extren);

	YVFilePathPtr  _path = new _YVFilePath(pathStr.c_str(), NULL);
	m_files.insert(std::make_pair(_path->getPathId(), _path));
	return _path;
}

// /**�����ļ������سɹ�ʧ��**/
// bool YVFileManager::createFile(string pFileName){
// 	FILE *fp = fopen(pFileName.c_str(), "w");
// 	bool bRet = false;
// 
// 	if (fp)
// 	{
// 		bRet = true;
// 		fclose(fp);
// 	}
// 
// 	return bRet;
// 
// };