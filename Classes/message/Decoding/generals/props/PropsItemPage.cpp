//
//  PropsItemPage.cpp
//  FightPass
//
//  Created by 超 顾 on 15/9/23.
//
//

#include "PropsItemPage.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
PropsItemPage::PropsItemPage()
{
    
}
PropsItemPage::~PropsItemPage()
{
    
}
ByteStream *PropsItemPage::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_ITEM_ItemPageReq);
    SetMessageLength();
}