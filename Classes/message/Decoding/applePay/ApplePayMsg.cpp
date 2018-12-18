//
//  ApplePayMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/5/20.
//
//

#include "ApplePayMsg.hpp"
ApplePayMsg::ApplePayMsg(int _charge_type, int _charge_id, int _card_id, int _fee,string _channel_code, string _channel_label, string _ipa_varify_str, int _is_sandbox)
:channel_code(_channel_code)
,channel_label(_channel_label)
,charge_type(_charge_type)
,charge_id(_charge_id)
,card_id(_card_id)
,fee(_fee)
,iap_verify_str(_ipa_varify_str)
,is_sandbox(_is_sandbox)

{
    
}
ApplePayMsg::~ ApplePayMsg()
{
    
}
ByteStream *ApplePayMsg::encodingData()
{
    MessageSendI::encodingData(ApplePayCreateOrderReq);
    headBufferee->put(charge_type);
    headBufferee->put(charge_id);
    headBufferee->put(card_id);
    headBufferee->putInt(fee);
    headBufferee->putUTF8(channel_code.c_str());
    headBufferee->putUTF8(channel_label.c_str());
    headBufferee->putUTF8(iap_verify_str.c_str());
    headBufferee->put(is_sandbox);
//    headBufferee->pu
    
    SetMessageLength();
}