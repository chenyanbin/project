//
//  StagePage.h
//  FightPass
//
//  Created by chenyanbin on 15/6/13.
//
//

#ifndef __FightPass__StagePage__
#define __FightPass__StagePage__

#include "cocos2d.h"
USING_NS_CC;
#include "../../commonData/dictData/DictStageBattle/DictStageBattleManager.h"
#include "../../commonData/GlobalInfo.h"
class StagePage:public Node
{
public:
    StagePage();
    ~StagePage();
    virtual bool init(int page,vector<BattleType>* battleList);
    static StagePage* create(int page,vector<BattleType>* battleList);
    
private:
    void setPage();
    void onClick(Node* psender);
private:
    int m_page;//当前页
    int m_totalCellSize;//总的结点个数
    int pageNum;
    vector<BattleType>* m_battleList;
};

#endif /* defined(__FightPass__StagePage__) */
