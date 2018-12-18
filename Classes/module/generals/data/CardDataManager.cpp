//
//  CardDataManager.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/13.
//
//

#include "CardDataManager.h"
CardDataManager* CardDataManager::_instance = NULL;

CardDataManager::CardDataManager()
:chooseEquipList(NULL)
,presentData(NULL)
{
    chooseEquipList = new Vector<CardPropertyData*>();
    heroList= new Vector<CardPropertyData*>();
    letterList=new Vector<LetterData*>();
    
}
CardDataManager::~CardDataManager()
{
    chooseEquipList->clear();
    CC_SAFE_DELETE(chooseEquipList);
    chooseEquipList = NULL;
    
    heroList->clear();
    CC_SAFE_DELETE(heroList);
    heroList = NULL;
    
    letterList->clear();
    CC_SAFE_DELETE(letterList);
    letterList = NULL;
    presentData = NULL;
}
CardDataManager* CardDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new CardDataManager();
    }
    return _instance;
}
void CardDataManager::addData(CardPropertyData* data)
{
    chooseEquipList->pushBack(data);
}
void CardDataManager::removeData(int _heroId)
{
    int index = this->getIndexByCardID(_heroId);
    if(index >= 0)
    {
        chooseEquipList->erase(index);
    }
}
int CardDataManager::getIndexByCardID(int _heroId)
{
    int len = (int)chooseEquipList->size();
    for(int i = 0; i < len; i++)
    {
        if(chooseEquipList->at(i)->heroId == _heroId)
        {
            return i;
        }
    }
    return -1;
}
CardPropertyData* CardDataManager::getCardDataByIndex(int index)
{
    if(index < 0 || index > this->chooseEquipList->size())
    {
        return NULL;
    }
    return this->chooseEquipList->at(index);
}
Vector<CardPropertyData*>* CardDataManager::getDataList()
{
    return this->chooseEquipList;
}
void CardDataManager::clearCardList()
{
    this->chooseEquipList->clear();
}


void CardDataManager::setChangeCardDataByIndex(int index,CardPropertyData* data)
{
    CardPropertyData* tempdata = chooseEquipList->at(index);
    if(tempdata)
    {
        chooseEquipList->erase(index);
    }
    this->chooseEquipList->insert(index, data);
}


void CardDataManager::setPresentData(CardPropertyData* data)
{
    this->presentData=NULL;
    this->presentData=data;
}
CardPropertyData* CardDataManager::getPresentData()
{
    return this->presentData;
}


//所有武将
void CardDataManager::addHeroData(CardPropertyData* data)
{
    heroList->pushBack(data);
}
void CardDataManager::removeHeroData(int _heroId)
{
    int index = this->getIndexByCardID(_heroId);
    if(index >= 0)
    {
        heroList->erase(index);
    }
}
int CardDataManager::getIndexByHeroID(int _heroId)
{
    int len = (int)heroList->size();
    for(int i = 0; i < len; i++)
    {
        if(heroList->at(i)->heroId == _heroId)
        {
            return i;
        }
    }
    return -1;
}
CardPropertyData* CardDataManager::getHeroDataByIndex(int index)
{
    if(index < 0 || index > this->heroList->size())
    {
        return NULL;
    }
    return this->heroList->at(index);
}
Vector<CardPropertyData*>* CardDataManager::getHeroDataList()
{
    return this->heroList;
}
void CardDataManager::clearHeroList()
{
    this->heroList->clear();
}

//
//
void CardDataManager::copyData(CardPropertyData* data1,CardPropertyData* data2)
{
    data1->heroId=data2->heroId;
    data1->heroDictId=data2->heroDictId;
    data1->heroName=data2->heroName;
    data1->prestige=data2->prestige;
    data1->leadership=data2->leadership;
    data1->combatPower=data2->combatPower;
    data1->level=data2->level;
    data1->levelMax=data2->levelMax;
    data1->quality=data2->quality;
    data1->hp=data2->hp;
    data1->attack=data2->attack;
    data1->defend=data2->defend;
    data1->crit=data2->crit;
    data1->tenaci=data2->tenaci;
    data1->hit=data2->hit;
    data1->block=data2->block;
    data1->attackStrengh=data2->attackStrengh;
    data1->fireResist=data2->fireResist;
    data1->iceResist=data2->iceResist;
    data1->boltResist=data2->boltResist;
    data1->windResist=data2->windResist;
    data1->poisonResist=data2->poisonResist;
    data1->cardLocation=data2->cardLocation;
    data1->cardOldLocation=data2->cardOldLocation;
    data1->cardGetExperience=data2->cardGetExperience;
    data1->cardGetExpValue=data2->cardGetExpValue;
    data1->cardConsumeCoin=data2->cardConsumeCoin;
    data1->heroExperience=data2->heroExperience;
    data1->heroMaxExperience=data2->heroMaxExperience;
    data1->heroForce=data2->heroForce;
    data1->isSelect=data2->isSelect;
}
