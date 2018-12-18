//
//  ApplePayMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/5/20.
//
//

#ifndef ApplePayMsg_hpp
#define ApplePayMsg_hpp

#include "../MessageSendI.h"
class ApplePayMsg:public MessageSendI
{
public:
    ApplePayMsg(int _charge_type, int _charge_id, int _card_id, int _fee, string _channel_code, string _channel_label, string _ipa_varify_str, int _is_sandbox);
    ~ ApplePayMsg();
    ByteStream *encodingData();
private:
    int charge_type;//	支付类型	byte	Y
    int charge_id;//	支付id	byte	Y
    int card_id;//	包月卡id	byte	Y
    int fee;//	支付金额	int
    string channel_code;//	渠道编号	string	Y
    string channel_label;//	渠道名称	string	Y
    string iap_verify_str;//	iap验证字符串	string
    int is_sandbox;//	是否测试模式	int
    
};

#endif /* ApplePayMsg_hpp */
