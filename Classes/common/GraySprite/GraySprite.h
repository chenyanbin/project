//
//  GraySprite.h
//  SuiTang
//
//  Created by mac on 14-6-15.
//
//

#ifndef __SuiTang__GraySprite__
#define __SuiTang__GraySprite__

#include "cocos2d.h"
USING_NS_CC;
class GraySprite:public Sprite
{
public:
    GraySprite();
    ~GraySprite();
    virtual bool init();
    CREATE_FUNC(GraySprite);
    
  	static GraySprite* create(const char* pszFileName);
    void initWithFile(const char* pszFileName);
    
    static GraySprite* createWithTexture(Texture2D* pTexture);
    bool initWithTexture2D(Texture2D* pTexture);
private:
    void setGray();
    
};
#endif /* defined(__SuiTang__GraySprite__) */
