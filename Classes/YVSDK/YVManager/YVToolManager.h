#ifndef YunVaSDKUtils_h__
#define YunVaSDKUtils_h__

/************************************************************************/
/* �����������뵥Ԫ                                                     */
/************************************************************************/
#include <map>
#include <vector>
#include "../YVType/YVType.h"
#include "../YVListern/YVListern.h"

namespace YVSDK
{
	/*����ʶ������*/
	enum SpeechLanguageType
	{
		speech_zn_type = 1, //����
		speech_ct_type = 2, //����
		speech_en_type = 3, //Ӣ��
	};

	class YVToolManager
	{
	public:
		bool init();
		bool destory();

	
		/*¼��ʱ��,��λΪ��,Ĭ����60��*/
		bool setRecordTime(uint32 timeNum, int volume);

		/*��ʼ¼��*/
		bool startRecord();

		/*����¼��*/
		bool stopRecord();

		/*����¼��*/
		bool playRecord(YVFilePathPtr);

		/*��������*/
		bool stopPlay();

		/*��������ʶ������*/
		bool setSpeechType(SpeechLanguageType type);

		/*����ʶ��*/
		bool speechVoice(YVFilePathPtr);

		/*�����ϴ��ļ�*/
		bool upLoadFile(YVFilePathPtr);
		///*�����ϴ��ļ�*/
		//void upLoadFile(std::string path, std::string fileid = "");

		/*���������ļ�*/
		bool downLoadFile(YVFilePathPtr path);

		//�����豸��Ϣ
		bool setDeviceInfo(std::string imsi, std::string imei, std::string mac,
			std::string appVersion, std::string networkType);

		InitListern(StopRecord, RecordStopNotify*);
		InitListern(FinishSpeech, SpeechStopRespond*);
		InitListern(FinishPlay, StartPlayVoiceRespond*);
		InitListern(UpLoadFile, UpLoadFileRespond*);
		InitListern(DownLoadFile, YVFilePathPtr);
		InitListern(RecordVoice, RecordVoiceNotify*);
		//InitListern(NetState, NetWorkStateNotify*);
	public:
		/*ֹͣ¼������*/
		void stopRecordRespond(YaYaRespondBase* respond);

		/*����¼����ɷ���*/
		void finishPlayRespond(YaYaRespondBase* respond);

		/*����ʶ����ɷ���*/
		void finishSpeechRespond(YaYaRespondBase* respond);

		/*�ϴ��ļ����󷵻�*/
		void upLoadFileRespond(YaYaRespondBase* respond);

		/*�����ļ����󷵻�*/
		void downLoadFileRespond(YaYaRespondBase* respond);

		/*¼������֪ͨ*/
		void recordVoiceRespond(YaYaRespondBase* respond);

		/*����״̬֪ͨ*/
		void NetStateRespond(YaYaRespondBase* respond);

		bool GetNetState(){ return NetState; };
	public:
		bool isPlaying(){ return _isPlaying; }
		uint64 PlayingId(){ return _fileId; }
	private:
		void registerMsgCallBack();
		void unRegisterMsgCallBack();

		bool _isSDKInit;  //SDK�Ƿ��ʼ�����
		bool _isLoginSuccess; //CP��¼�Ƿ�ɹ�
		bool _isRecording; //����¼��
		bool _isPlaying;  //�Ƿ����ڲ���
		bool _isUsedSchedule;
		bool _lockInit;
		bool NetState;  //����״̬
		uint64 _fileId;

		std::vector<YVFilePathPtr>  _recordingPath;
		std::vector<YVFilePathPtr>  _speechingPath;
		std::vector<YVFilePathPtr>  _downloadingPath;
		std::vector<YVFilePathPtr>  _playingPath;
	};
}
#endif // YunVaSDKUtils_h__

