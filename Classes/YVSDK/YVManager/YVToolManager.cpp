/*********************************************************************************
*Copyright(C), 2015 YUNVA Company
*FileName:  YVProtocol.h
*Author:  Matt
*Version:  1.0.0
*Date:  2015-5-5
*Description: �������ʵ��, ¼�����ϴ����ص�
**********************************************************************************/

#include "YVToolManager.h"
#include "../YVSDK.h"
#include <assert.h>
using namespace YVSDK;

bool YVToolManager::init()
{
	_isPlaying = false;
	_isSDKInit = false;
	_isUsedSchedule = false;
	_isLoginSuccess = false;
	_isRecording = false;
	_lockInit = false;

	registerMsgCallBack();
	return true;
}

bool YVToolManager::destory()
{
	unRegisterMsgCallBack();
	return true;
}

void YVToolManager::registerMsgCallBack()
{
	YVMsgDispatcher*  msgDispatcher = YVPlatform::getSingletonPtr()->getMsgDispatcher();

	/*�������Ϣ����*/
	msgDispatcher->registerMsg(IM_RECORD_STOP_RESP, this, &YVToolManager::stopRecordRespond);
	msgDispatcher->registerMsg(IM_RECORD_FINISHPLAY_RESP, this, &YVToolManager::finishPlayRespond);
	msgDispatcher->registerMsg(IM_SPEECH_STOP_RESP, this, &YVToolManager::finishSpeechRespond);
	msgDispatcher->registerMsg(IM_UPLOAD_FILE_RESP, this, &YVToolManager::upLoadFileRespond);
	msgDispatcher->registerMsg(IM_DOWNLOAD_FILE_RESP, this, &YVToolManager::downLoadFileRespond);
	msgDispatcher->registerMsg(IM_RECORD_VOLUME_NOTIFY, this, &YVToolManager::recordVoiceRespond);

	msgDispatcher->registerMsg(IM_NET_STATE_NOTIFY, this, &YVToolManager::NetStateRespond);  //����״̬
}

void YVToolManager::unRegisterMsgCallBack()
{
	YVMsgDispatcher*  msgDispatcher = YVPlatform::getSingletonPtr()->getMsgDispatcher();
	msgDispatcher->unregisterMsg(IM_RECORD_STOP_RESP, this);
	msgDispatcher->unregisterMsg(IM_RECORD_FINISHPLAY_RESP, this);
	msgDispatcher->unregisterMsg(IM_SPEECH_STOP_RESP, this);
	msgDispatcher->unregisterMsg(IM_UPLOAD_FILE_RESP, this);
	msgDispatcher->unregisterMsg(IM_DOWNLOAD_FILE_RESP, this);
	msgDispatcher->unregisterMsg(IM_RECORD_VOLUME_NOTIFY, this);
	msgDispatcher->unregisterMsg(IM_NET_STATE_NOTIFY, this);  //����״̬
}

bool YVToolManager::setRecordTime(unsigned int timeNum, int volume)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	SetRecordRequest q;
	q.times = timeNum;
	q.volume = volume;

	return msgDispatcher->send(&q);
}

bool YVToolManager::startRecord()
{
	if (_isRecording) return false;
	_isRecording = true;

	//��ȡһ��������ļ���
	YVFilePathPtr path = YVPlatform::getSingletonPtr()->getYVPathByRand("amr");
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();
	StartRecordRequest q;
	q.strFilePath.append(path->getLocalPath());
	//��id��¼����
	uint64 fileId = path->getPathId();
	q.ext.append(toString(fileId));
	_recordingPath.push_back(path);
	return msgDispatcher->send(&q);
}

bool YVToolManager::stopRecord()
{
	if (!_isRecording) return false;
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	StopRecordRequest q;
	_isRecording = false;

	return msgDispatcher->send(&q);
}

bool YVToolManager::playRecord(YVFilePathPtr path)
{
	if (path == NULL) return false;
	if (_isPlaying) return false;
	_isPlaying = true;

	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	_playingPath.push_back(path);

	StartPlayVoiceRequest q;

	//����ط��������ʹ��url���ŵĻ����ײ��Ҫ�ṩ�ӿڣ������غõĵ�ַ�����ϵ�����ַ�ϡ�
	q.strfilepath.append(path->getLocalPath());
	q.strUrl.append(path->getUrlPath());
	//��id��¼����
	_fileId = path->getPathId();
	q.ext.append(toString(_fileId));
	return msgDispatcher->send(&q);
}

bool YVToolManager::stopPlay()
{
	if (!_isPlaying) return false;
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();
	StopPlayVoiceRequest q;
	return msgDispatcher->send(&q);
}

bool YVToolManager::setSpeechType(SpeechLanguageType type)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();
	
	SpeechSetRequest q;
	q.language = (yvimspeech_language)type;

	return msgDispatcher->send(&q);
}

bool YVToolManager::speechVoice(YVFilePathPtr path)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();
		//printf_s("----speeh voice---");
	assert((path->getState() == BothExistState || path->getState() == OnlyLocalState));
	_speechingPath.push_back(path);
	//����ȱ����һ����ʶ��
	SpeechStartRequest q;
	q.strfilepath.append(path->getLocalPath());
	uint64 pathId = path->getPathId();
	//��id��¼����
	q.ext.append(toString(pathId));
	q.type = speech_file_and_url;
	return msgDispatcher->send(&q);
}


bool YVToolManager::upLoadFile(YVFilePathPtr file)
{
	if (file == NULL)
	{
		return false;
	}
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	UpLoadFileRequest q;
	q.filename.append(file->getLocalPath());
	char ch[30] = {};
	sprintf(ch, "%d", file->getPathId());
	q.fileid.append(ch);
	return msgDispatcher->send(&q);
}

bool  YVToolManager::downLoadFile(YVFilePathPtr file)
{
	//�����ļ��Ƿ��������ػ����Ѿ�����������
	if (file == NULL || file->getState() == DownLoadingState
		|| file->getState() == OnlyLocalState)
	{
		return true;
	}
	if (file->getUrlPath().length()==0)
		return true;
	//�仯״̬
	file->setState(DownLoadingState);
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	DownLoadFileRequest q;
	q.url.append(file->getUrlPath());
	q.filename.append(file->getLocalPath());
	uint64 fileId = file->getPathId();
	q.fileid.append(toString(fileId));

	_downloadingPath.push_back(file);

		//printf("LocalPath = s% /n", file->getLocalPath());

	return msgDispatcher->send(&q);
}

bool  YVToolManager::setDeviceInfo(std::string imsi, std::string imei, std::string mac,
	std::string appVersion, std::string networkType)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	SetDeviceInfoReqeust q;
	q.imsi.append(imsi);
	q.imei.append(imei);
	q.mac.append(mac);
	q.appVersion.append(appVersion);
	q.networkType.append(networkType);

	return msgDispatcher->send(&q);
}

void YVToolManager::stopRecordRespond(YaYaRespondBase* respond)
{
	_isRecording = false;
	RecordStopNotify* r = static_cast<RecordStopNotify*>(respond);
	//����¼���Ļص���ȡ��¼��ʱ����ļ�·��
	uint64 id = 0;
	id = toNumber(r->ext);
	
	for (std::vector<YVFilePathPtr>::iterator it = _recordingPath.begin();
		it != _recordingPath.end(); ++it)
	{
		if ((*it)->getPathId() == id)
		{
			r->strfilepath = (*it);
			callStopRecordListern(r);
			_recordingPath.erase(it);
			break;
		}
	}
}

void YVToolManager::finishPlayRespond(YaYaRespondBase* respond)
{
	StartPlayVoiceRespond* r = static_cast<StartPlayVoiceRespond*>(respond);
	_isPlaying = false;
	
	uint64 id = 0;
	id = toNumber(r->ext);
	
	for (std::vector<YVFilePathPtr>::iterator it = _playingPath.begin();
		it != _playingPath.end(); ++it	)
	{
		if ((*it)->getPathId() == id)
		{
			r->filePath = (*it);

			callFinishPlayListern(r);
			_playingPath.erase(it);
			break;
		}
	}
}

void YVToolManager::finishSpeechRespond(YaYaRespondBase* respond)
{
	SpeechStopRespond* r = static_cast<SpeechStopRespond*>(respond);	
	
	uint64 id = 0;
	id = toNumber(r->ext);
	
	for (std::vector<YVFilePathPtr>::iterator it = _speechingPath.begin();
		it != _speechingPath.end(); ++it)
	{
		if ( (*it)->getPathId() == id)
		{
			r->filePath = (*it);
			r->filePath->setUrlPath(r->url);
			_speechingPath.erase(it);
			callFinishSpeechListern(r);
			break;
		}
	}
}

void YVToolManager::upLoadFileRespond(YaYaRespondBase* respond)
{
	UpLoadFileRespond* r = static_cast<UpLoadFileRespond*>(respond);

	//assert (r->fileid.length() <= sizeof(uint64));
	//uint64 id = 0;
	//memcpy(&id, r->fileid.c_str(), r->fileid.length());
	//YVFilePathPtr path = new _YVFilePath(r->fileurl.c_str(), r->fileurl.c_str());
	//
	//if (path == NULL) return;
	callUpLoadFileListern(r);
	
}

void YVToolManager::downLoadFileRespond(YaYaRespondBase* respond)
{
	DownLoadFileRespond* r = static_cast<DownLoadFileRespond*>(respond);
	uint64 id = 0;
	id = toNumber(r->fileid);
	
	for (std::vector<YVFilePathPtr>::iterator it = _downloadingPath.begin();
		it != _downloadingPath.end(); ++it)
	{
		if ((*it)->getPathId() == id)
		{
			YVFilePathPtr path = (*it);
			if (path == NULL) return;
			path->setState(r->result == 0 ? BothExistState : DownLoadErroSate);
			callDownLoadFileListern(path);

			_downloadingPath.erase(it);
			break;
		}
	}
}

void YVToolManager::recordVoiceRespond(YaYaRespondBase* respond)
{
	RecordVoiceNotify* r = static_cast<RecordVoiceNotify*>(respond);
	callRecordVoiceListern(r);
}

void YVToolManager::NetStateRespond(YaYaRespondBase* respond)
{
	NetWorkStateNotify* r = static_cast<NetWorkStateNotify*>(respond);
	//callNetStateListern(r);
	//if (r->state)
	NetState = r->state;
}

