/*********************************************************************************
*Copyright(C), 2015 YUNVA Company
*FileName:  YVLbsManager.Cpp
*Author:  Matt
*Version:  1.0.3
*Date:  2015-8-10
*Description:  LBS������
**********************************************************************************/

#include "YVLbsManager.h"
#include "../YVSDK.h"

using namespace YVSDK;

bool YVLbsManager::init()
{
	YVMsgDispatcher*  msgDispatcher = YVPlatform::getSingletonPtr()->getMsgDispatcher();

	//���µ���λ��
	msgDispatcher->registerMsg(IM_LBS_UPDATE_LOCATION_RESP, this, &YVLbsManager::UpdatelocationCallback);
	//��ȡλ����Ϣ
	msgDispatcher->registerMsg(IM_LBS_GET_LOCATION_RESP, this, &YVLbsManager::GetlocationCallback);
	//�������������û�(��������λ��)
	msgDispatcher->registerMsg(IM_LBS_SEARCH_AROUND_RESP, this, &YVLbsManager::SearchAroundCallback);
	//���ص���λ��
	msgDispatcher->registerMsg(IM_LBS_SHARE_LOCATION_RESP, this, &YVLbsManager::LbsShareCallback);
	//��ȡ֧�ֵģ�����������������Ϣ�ȣ����ػ������б�
	msgDispatcher->registerMsg(IM_LBS_GET_SUPPORT_LANG_RESP, this, &YVLbsManager::LbsGetSupportlangCallback);
	//����LBS���ػ�����
	msgDispatcher->registerMsg(IM_LBS_SET_LOCAL_LANG_RESP, this, &YVLbsManager::LbsSetLocalLangCallback);
	//���ö�λ��ʽ//
	msgDispatcher->registerMsg(IM_LBS_SET_LOCATING_TYPE_RESP, this, &YVLbsManager::LbsSetLocatingCallback);

	Notifymsglist = new _YVMessageList();
	return true;
}

bool YVLbsManager::destory()
{
	YVMsgDispatcher*  msgDispatcher = YVPlatform::getSingletonPtr()->getMsgDispatcher();
	//���µ���λ��
	msgDispatcher->unregisterMsg(IM_LBS_UPDATE_LOCATION_RESP, this);
	//��ȡλ����Ϣ
	msgDispatcher->unregisterMsg(IM_LBS_GET_LOCATION_RESP, this);
	//�������������û�(��������λ��)
	msgDispatcher->unregisterMsg(IM_LBS_SEARCH_AROUND_RESP, this);
	//���ص���λ��
	msgDispatcher->unregisterMsg(IM_LBS_SHARE_LOCATION_RESP, this);
	//��ȡ֧�ֵģ�����������������Ϣ�ȣ����ػ������б�
	msgDispatcher->unregisterMsg(IM_LBS_GET_SUPPORT_LANG_RESP, this);
	//����LBS���ػ�����
	msgDispatcher->unregisterMsg(IM_LBS_SET_LOCAL_LANG_RESP, this);
	//���ö�λ��ʽ//
	msgDispatcher->unregisterMsg(IM_LBS_SET_LOCATING_TYPE_RESP, this);

	Notifymsglist->clear();

	return true;
}

bool YVLbsManager::Updatelocation(std::string attach)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	UpdatelocationRequest r;
	r.attach = attach;
	return 	msgDispatcher->send(&r);
}
bool YVLbsManager::Getlocation()
{
	//CCLOG("-----------------------------------------------------in bool YVLbsManager::Getlocation()");
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	GetlocationRequest r;
	return 	msgDispatcher->send(&r);
}
bool YVLbsManager::SearchAround(std::string  city, uint8 sex, uint32 pageIndex, uint32 thedistance)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	SearchAroundRequest r;
	r.city = city;
	r.sex = sex;
	r.range = thedistance;
	r.pageIndex = pageIndex;
	r.time = 2600;
	r.pageSize = 5;
	return 	msgDispatcher->send(&r);
}
bool YVLbsManager::LbsShare(uint8 hide)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	LbsShareRequest r;
	r.hide = hide;
	return 	msgDispatcher->send(&r);
}

bool YVLbsManager::LbsGetSupportlang()
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	LbsGetSupportlangRequest r;
	return 	msgDispatcher->send(&r);
}
bool YVLbsManager::LbsSetLocalLang(std::string lang_code, std::string lang_name)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	LbsSetLocalLangRequest r;
	r.lang_code = lang_code;
	r.lang_name = lang_name;
	return 	msgDispatcher->send(&r);
}
bool YVLbsManager::LbsSetLocating(uint8 locate_gps, uint8 locate_wifi, uint8 locate_cell, uint8 locate_network)
{
		YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	LbsSetLocatingRequest r;
	r.locate_gps = locate_gps;
	r.locate_wifi = locate_wifi;
	r.locate_cell = locate_cell;
	r.locate_network = locate_network;
	r.locate_bluetooth = 1;
	return 	msgDispatcher->send(&r);
}

void YVLbsManager::UpdatelocationCallback(YaYaRespondBase* request)
{
	UpdatelocationRespond* r = (UpdatelocationRespond*)request;

	printf("======================================================================================GetlocationCallback");
	if (r->result == 0)
	{

	}
	callUpdatelocationListern(r);
}
void YVLbsManager::GetlocationCallback(YaYaRespondBase* request)
{
	GetlocationRespond* r = (GetlocationRespond*)request;
//	CCLOG("r->result = %d", r->result);
//	CCLOG("------------------------GetlocationCallback--------------------------------------��ַ = %s", r->city);
	printf("======================================================================================GetlocationCallback");
	if (r->result == 0)
	{

	}
	callGetlocationListern(r);
}
void YVLbsManager::SearchAroundCallback(YaYaRespondBase* request)
{
	SearchAroundRespond* r = (SearchAroundRespond*)request;
	if (r->result == 0)
	{

	}
	callSearchAroundListern(r);
}
void YVLbsManager::LbsShareCallback(YaYaRespondBase* request)
{
	LbsShareRespond* r = (LbsShareRespond*)request;
	if (r->result == 0)
	{

	}
	callLbsShareListern(r);
}
void YVLbsManager::LbsGetSupportlangCallback(YaYaRespondBase* request)
{
	LbsGetSupportlangRespond* r = (LbsGetSupportlangRespond*)request;
	if (r->result == 0)
	{

	}
	callLbsGetSupportlangListern(r);
}
void YVLbsManager::LbsSetLocalLangCallback(YaYaRespondBase* request)
{
	LbsSetLocalLangRespond* r = (LbsSetLocalLangRespond*)request;
	if (r->result == 0)
	{

	}
	callLbsSetLocalLangListern(r);

}
void YVLbsManager::LbsSetLocatingCallback(YaYaRespondBase* request)
{
	LbsSetLocatingRespond* r = (LbsSetLocatingRespond*)request;
	if (r->result == 0)
	{

	}
	callLbsSetLocatingListern(r);
}
