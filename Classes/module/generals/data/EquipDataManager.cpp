//
//  EquipDataManager.cpp
//  FightPass
//
//  Created by 超 顾 on 15/9/1.
//
//

#include "EquipDataManager.h"
EquipDataManager* EquipDataManager::_instance = NULL;

EquipDataManager::EquipDataManager()
:chooseEquipList(NULL)
,presentData(NULL)
{
    chooseEquipList = new Vector<BaseEquipData*>();
    equipList= new Vector<BaseEquipData*>();
    
}
EquipDataManager::~EquipDataManager()
{
    chooseEquipList->clear();
    CC_SAFE_DELETE(chooseEquipList);
    chooseEquipList = NULL;
    
    equipList->clear();
    CC_SAFE_DELETE(equipList);
    equipList = NULL;
    CC_SAFE_RELEASE_NULL(presentData);

}
EquipDataManager* EquipDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new EquipDataManager();
    }
    return _instance;
}
void EquipDataManager::addData(BaseEquipData* data)
{
    chooseEquipList->pushBack(data);
}
void EquipDataManager::removeData(int _equipId)
{
    int index = this->getIndexByCardID(_equipId);
    if(index >= 0)
    {
        chooseEquipList->erase(index);
    }
}
int EquipDataManager::getIndexByCardID(int _equipId)
{
    int len = (int)chooseEquipList->size();
    for(int i = 0; i < len; i++)
    {
        if(chooseEquipList->at(i)->equipId == _equipId)
        {
            return i;
        }
    }
    return -1;
}
BaseEquipData* EquipDataManager::getCardDataByIndex(int index)
{
    if(index < 0 || index > this->chooseEquipList->size())
    {
        return NULL;
    }
    return this->chooseEquipList->at(index);
}
Vector<BaseEquipData*>* EquipDataManager::getDataList()
{
    return this->chooseEquipList;
}
void EquipDataManager::clearCardList()
{
    if (this->chooseEquipList->size()>0) {
        this->chooseEquipList->clear();
    }
    
}


void EquipDataManager::setChangeCardDataByIndex(int index,BaseEquipData* data)
{
    BaseEquipData* tempdata = chooseEquipList->at(index);
    if(tempdata)
    {
        chooseEquipList->erase(index);
    }
    this->chooseEquipList->insert(index, data);
}


void EquipDataManager::setPresentData(BaseEquipData* data)
{
    CC_SAFE_RELEASE_NULL(this->presentData);
    presentData = data;
    CC_SAFE_RETAIN(this->presentData);

}
BaseEquipData* EquipDataManager::getPresentData()
{
    return this->presentData;
}


//所有武将
void EquipDataManager::addEquipData(BaseEquipData* data)
{
    equipList->pushBack(data);
}
void EquipDataManager::removeEquipData(int _heroId)
{
    int index = this->getIndexByEquipID(_heroId);
    if(index >= 0)
    {
        equipList->erase(index);
    }
}
int EquipDataManager::getIndexByEquipID(int _equipId)
{
    int len = (int)equipList->size();
    for(int i = 0; i < len; i++)
    {
        if(equipList->at(i)->equipId == _equipId)
        {
            return i;
        }
    }
    return -1;
}
BaseEquipData* EquipDataManager::getEquipDataByIndex(int index)
{
    if(index < 0 || index > this->equipList->size())
    {
        return NULL;
    }
    return this->equipList->at(index);
}
BaseEquipData* EquipDataManager::getEquipDataByEquipID(int _equipId)
{
    int index = this->getIndexByEquipID(_equipId);
    
    if(index < 0 || index > this->equipList->size())
    {
        return NULL;
    }
    return this->equipList->at(index);
}

Vector<BaseEquipData*>* EquipDataManager::getEquipDataList()
{
    return this->equipList;
}
void EquipDataManager::clearEquipList()
{
    if ((int)this->equipList->size()!=0) {
        this->equipList->clear();
    }
    
}