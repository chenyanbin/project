//
//  FunctionOpenManager.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/28.
//
//
#include "../../common/noticeManager/NoticeManager.h"
#include "FunctionOpenManager.h"
#include "../../commonData/dictData/DictTips/DictTipsManager.h"
#include "../../commonData/dictData/DictFunction/DictFunctionManager.h"
#include "../../common/StringUtil.h"
#include "../../common/PublicShowUI.h"
FunctionOpenManager* FunctionOpenManager::_instance = NULL;
FunctionOpenManager::FunctionOpenManager():_dataList(NULL)
{
    _dataList = new Map<int, FunctionOpenData*>;
}
FunctionOpenManager::~FunctionOpenManager()
{
    CC_SAFE_DELETE(_dataList);
    _dataList = NULL;
    _instance = NULL;
}
FunctionOpenManager* FunctionOpenManager::getInstance()
{
    if(!_instance)
    {
        _instance = new FunctionOpenManager();
    }
    return _instance;
}
void FunctionOpenManager::destoryInstance()
{
    CC_SAFE_DELETE(_instance);
}
void FunctionOpenManager::setFunctionStatus(int functionID,int status)
{
    FunctionOpenData* data = _dataList->at(functionID);
    if(data)
    {
        data->status = status;
    }
    else
    {
        data = new FunctionOpenData();
        data->status = status;
        data->autorelease();
        data->functionID = functionID;
        _dataList->insert(functionID, data);
    }
}

bool FunctionOpenManager::functionIsOpened(int functionID)
{
   FunctionOpenData* data = _dataList->at(functionID);
   return data ? data->status == FunctionOpenData::STATUS_OPEN : true;
}
void FunctionOpenManager::showNoOpenNotice(int functionID )
{
    DictTips* dictTips = DictTipsManager::getInstance()->getData(6001001);
    DictFunction* functionOpen = DictFunctionManager::getInstance()->getData(functionID);
    if(dictTips && functionOpen)
    {
        string str = StringUtil::replace(dictTips->desc, "#1#",PublicShowUI::numberToString(functionOpen->roleLevel));
        NoticeManager::getInstance()->showNotice(str.c_str());
    }
    else
    {
        NoticeManager::getInstance()->showNotice("尚未开启，征战打怪升级吧!");
    }
}