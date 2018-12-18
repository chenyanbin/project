//
//  MusouLayer.h
//  FightPass
//三国无双
//  Created by zhangxiaobin on 15/9/17.
//
//

#ifndef __FightPass__MusouLayer__
#define __FightPass__MusouLayer__

#include "../BaseLayer.h"
#include "../../net/bytestream.h"
class MusouLayer:public BaseLayer
{
public:
    MusouLayer();
    ~MusouLayer();
    virtual bool init();
    void initWithByteStream(ByteStream* byteStream);
    CREATE_FUNC(MusouLayer);
    static void requestMuouList();
    static void show(ByteStream* byteStream);
protected:
    virtual void addEventListener();
    virtual void removeEventListener();
    void onMsgProcess(EventCustom* message);
private:
    void setBg();
    void setUserWealth();
 
};

#endif /* defined(__FightPass__MusouLayer__) */
