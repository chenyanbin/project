//
//  PublicShowUI.cpp
//  TwoMahjong
//
//  Created by mac on 14-4-27.
//
//

#include "PublicShowUI.h"
#include "../VisibleRect.h"
#include "../commonData/GlobalInfo.h"
#include "../common/ImagePath.h"
#include "../common/StringUtil.h"
#include "../common/GraySprite/GraySprite.h"
#include "../commonData/enum/DictItemTypeEnum.h"
#include "../commonData/enum/DictFightPropEnum.h"
#include "../commonData/dictData/DictHero/DictHeroManager.h"

#include "../commonData/dictData/DictHeroEquip/DictHeroEquipManager.h"
#include "../commonData/dictData/DictItemEquip/DictItemEquipManager.h"
#include "../commonData/dictData/DictitemMater/DictItemMaterManager.h"
#include "../commonData/dictData/DictItem/DictItemManager.h"
#include "../commonData/dictData/DictItemBook/DictItemBookManager.h"
#include "../commonData/dictData/DictResource/DictResourceManager.h"
#include "../commonData/dictData/DictHeroQuality/DictHeroQualityManager.h"
#include "../commonData/dictData/DictItemQuality/DictItemQualityManager.h"
#include "../commonData/enum/DictEquipPartsEnum.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "../common/GlobalAppController.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include <platform/android/jni/JniHelper.h>
#include <android/log.h>

#if 1
#define  LOG_TAG    "JniHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...)
#endif
#endif

Sprite* PublicShowUI::setTagScale(Sprite* tagSprite)
{
    float sx = getTagScale(tagSprite);
    if(sx < 1)
    {
        sx = 1;
    }
    tagSprite->setScale(sx);
    return tagSprite;
    
}
void PublicShowUI::setGray(Sprite* sprite)
{
    if(sprite)
    {
        string pszFragSource =
        "#ifdef GL_ES \n \
        precision mediump float; \n \
        #endif \n \
        uniform sampler2D u_texture; \n \
        varying vec2 v_texCoord; \n \
        varying vec4 v_fragmentColor; \n \
        void main(void) \n \
        { \n \
        // Convert to greyscale using NTSC weightings \n \
        vec4 col = texture2D(u_texture, v_texCoord); \n \
        float grey = dot(col.rgb, vec3(0.299, 0.587, 0.114)); \n \
        gl_FragColor = vec4(grey, grey, grey, col.a); \n \
        }";
        GLProgram* pProgram = new GLProgram();
        pProgram->initWithByteArrays(ccPositionTextureColor_vert, pszFragSource.c_str());
    
//        CHECK_GL_ERROR_DEBUG();
//        pProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
//        pProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
//        pProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        CHECK_GL_ERROR_DEBUG();
        pProgram->link();
        CHECK_GL_ERROR_DEBUG();
        pProgram->updateUniforms();
        CHECK_GL_ERROR_DEBUG();
        sprite->setShaderProgram(pProgram);
        pProgram->release();
//        sprite->setPosition(sprite->getPositionX() - sprite->getContentSize().width, sprite->getPositionY());
        
    }
}
Sprite* PublicShowUI::AddColorGray(Sprite * sp)
{
    
     sp->setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
//    Sprite* sprite_chess = Sprite::createWithSpriteFrame(sp->getSpriteFrame());
//
//    sprite_chess->retain();
//    RenderTexture *render = RenderTexture::create(sprite_chess->getContentSize().width, sprite_chess->getContentSize().height,Texture2D::PixelFormat::RGBA8888);
//    render->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
//    sprite_chess->visit();
//    render->end();
//    
//    Director::getInstance()->getRenderer()->render();
//    
//    Image *finalImage = render->newImage();
//    
//    unsigned char *pData = finalImage->getData();
//    
//    int iIndex = 0;
//    
//    for (int i = 0; i < finalImage->getHeight(); i ++)
//    {
//        for (int j = 0; j < finalImage->getWidth(); j ++)
//        {
//            // gray
//            int iBPos = iIndex;
//            
//            unsigned int iB = pData[iIndex];
//            
//            iIndex ++;
//            
//            unsigned int iG = pData[iIndex];
//            
//            iIndex ++;
//            
//            unsigned int iR = pData[iIndex];
//            
//            iIndex ++;
//            iIndex ++;
//            
//            unsigned int iGray = 0.3 * iR + 0.6 * iG + 0.1 * iB;
//            
//            pData[iBPos] = pData[iBPos + 1] = pData[iBPos + 2] = (unsigned char)iGray;
//        }
//        
//    }
//    
//    
//    Texture2D *texture = new Texture2D;
//    
//    texture->initWithImage(finalImage);
//    
//    auto pSprite = Sprite::createWithTexture(texture);
//    
//    delete finalImage;
//    
//    texture->release();
//    
//    return pSprite;
}

void PublicShowUI::RemoveColorGray(Sprite * spr)
{
    spr->setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
}
float PublicShowUI::getTagScale(Node* tagSprite)
{
    float X2 = tagSprite->getContentSize().width;
    float Y2 = tagSprite->getContentSize().height;
    float last_X = ( (float)VisibleRect::getVisibleRect().size.width/X2) ;
    float last_Y = ( (float)VisibleRect::getVisibleRect().size.height/Y2);
    
    if(last_X > last_Y)
    {
        return last_X;
    }
    else
    {
        return last_Y;
    }
    return 1;
}
Color3B PublicShowUI::getColor3b(unsigned long color)
{
    int R = (color & 0xFF0000 )>>16;
    int G = (color & 0x00FF00 )>>8;
    int B =  color & 0x0000FF;
    
    Color3B rgb(R,G,B);// = {R,G,B};
    return rgb;
}
Color4B PublicShowUI::getColor4b(unsigned long color)
{
    int R = (color & 0xFF0000 )>>16;
    int G = (color & 0x00FF00 )>>8;
    int B =  color & 0x0000FF;
    
    Color4B rgb(R,G,B,255);
    return rgb;
}
const char* PublicShowUI::getResImgPath(const char* formatPre,const char* content)
{
    static char buf[2000];
    memset(buf, 0, 2000);
    sprintf(buf, formatPre,content);
    return buf;
}
const char* PublicShowUI::getAvatarPath(const char* formatPre,const char* content)
{
    string str = content;
    str = str + "/" + str;
    return getResImgPath(formatPre,str.c_str());
}
/******************
 *获取屏幕分辨率
 *根据分辨率计算使用哪一套资源
 ******************/
int PublicShowUI::getInch(void)
{
    int lastinch = -1;
    Size winSizeInPixels = VisibleRect::getVisibleRect().size;
    
//    static Resource smallResource  =  { cocos2d::Size(480, 320),   "iphone" };
//    static Resource mediumResource =  { cocos2d::Size(1024, 768),  "ipad"   };
//    static Resource largeResource  =  { cocos2d::Size(2048, 1536), "ipadhd" };
//    static Resource SDResource     =  { cocos2d::Size(1136, 640),  "images"   };
    //static Resource SDResource     =  { cocos2d::Size(960, 640),  "images"   };
    if(winSizeInPixels.width<=480)
    {
        lastinch = INCH_1;//ipod 480*320
    }
    else if(winSizeInPixels.width>=800&&winSizeInPixels.width<960)
    {
        lastinch = INCH_2;//ihpone3.5寸
    }
    else if(winSizeInPixels.width>=960&&winSizeInPixels.width<=1279)
    {
        lastinch = INCH_3;//ihpone4寸及大部分android4寸左右屏幕+
    }
    else if(winSizeInPixels.width>1279&&winSizeInPixels.width<=2448)
    {
        lastinch = INCH_MAX;//超高清屏幕(小米3=1920，Ipad Retina=2048)
        if(winSizeInPixels.height<=720)
        {
            lastinch = INCH_3;
        }
    }
    else
    {
        lastinch = INCH_3;
    }
    log(" screen width=%f,height=%f ,lastinch=%d",winSizeInPixels.width,winSizeInPixels.height,lastinch);
    return lastinch;
}
void PublicShowUI::setCameraDistance(float distance)
{
   
//    Camera* camera = Camera::create();
//    camera->setCameraFlag(CameraFlag::USER1);
//    this->addChild(camera);
//    sprite->setCameraMask(2);    //因为2 & CameraFlag::USER1 !=0，所以cameraMask=2与CameraFlag::USER1匹配，sprite将使用上面创建的camera
//    Vec3 eyePosOld=camera->getPosition3D();
//    Vec3 eyePos=Vec3(x,y,eyePosOld.z);
//    camera->setPosition3D(eyePos);
//    assert(eyePos.z>0);
//    camera->lookAt(Vec3(eyePos.x,eyePos.y,0), Vec3(0, 1, 0));
}
void PublicShowUI::setTargetScale(Node* target,bool isLashen,bool isSetContentSize)
{
    if(!target)
    {
        return;
    }
    float sx = GlobalInfo::getInstance()->screenScaleX;
    float sy = GlobalInfo::getInstance()->screenScaleY;
    
    Size size = target->getContentSize();
    if(isLashen){
           //拉伸 不保持宽高比
        size.setSize(size.width*sx,size.height*sy);
        target->setScale(sx,sy);
    }else{
       //不拉伸 保持宽高比 默认值
    
        size.setSize(size.width*sx,size.height*sx);

        target->setScale(sx);
    }
    if(isSetContentSize)
        
    {
         target->setContentSize(size);
    }
}
Rect PublicShowUI::getRect(Node* spr)
{
    //获取精灵区域大小
    return Rect(spr->getPositionX()- spr->getContentSize().width  * spr->getAnchorPoint().x,spr->getPositionY()-spr->getContentSize().height* spr->getAnchorPoint().y,spr->getContentSize().width, spr->getContentSize().height);
}
string PublicShowUI::numberToTwoDecimalPlaces(float number)
{
    static char str[10];
    memset(str, 0, 10);
    sprintf(str,"%.2f",number);
    return str;
}
string PublicShowUI::numberToString(int number)
{
 
    stringstream ss;
    ss << number;
    return ss.str();
//    static char str[50];
//    memset(str, 0, 50);
//    sprintf(str, "%d",number);
//    return str;
}
string PublicShowUI::numberToString(long number)
{
    stringstream ss;
    ss << number;
    return ss.str();
//    static char str[50];
//    memset(str, 0, 50);
//    sprintf(str, "%ld",number);
//    return str;
}
string PublicShowUI::numberToBigNumString(int number)
{
    stringstream ss;
    ss << number;
    return ss.str();
//    static char str[50];
//    memset(str, 0, 50);
//    sprintf(str, "%d",number);
//    return str;
}
string PublicShowUI::numberToString(long long number)
{
    stringstream ss;
    ss << number;
    return ss.str();
//    static char str[100];
//    memset(str, 0, 50);
//    sprintf(str, "%lld",number);
//    return str;
}
string PublicShowUI::numberToString(double number)
{
    if(number < 0.0001)
    {
        return "0";
    }
    static char str[50];
    memset(str, 0, 50);
//    sprintf(str, "%.1f",number);
    sprintf(str, "%.0f",number);

    return str;
//    stringstream
}
string PublicShowUI::numberToString(float number,int len)
{
    if(number < 0.0001)
    {
        return "0";
    }
    char str[50] = {"0"};
    if(len == 1)
    {
        sprintf(str, "%.1f",number);
    }
    else
    {
        sprintf(str, "%.5f",number);
    }
    
    return str;
    
}
string PublicShowUI::numberToString(long number,int size)
{
    char str[20] = {0};
    char numStr[20]={0};
	sprintf(numStr,"%ld",number);
    int index = size - strlen(numStr);
    
    for(int i = 0; i < size; i++)
    {
        if(i < index)
        {
            str[i] = '0';
        }
        else
        {
            str[i] = numStr[i - index];
        }
    }
    return str;
}
long PublicShowUI::stringToNumber(string str)
{
    long number;
    stringstream ss;
    ss<<str;
    ss>>number;
    if (ss.bad()) {
        return 0;
    }
    ss<<number;
    if (ss.bad()) {
        return 0;
    }
    return number;
}
unsigned long PublicShowUI::hexToULong(string str)
{
    const char* szValue = str.c_str();
    char ch[32];
    int nValude = 0;
    sscanf(szValue,"%x",&nValude); //十六进制转数字
    sprintf(ch,"%d",nValude); //数字转字符
    log("%d/n",nValude);
    return nValude;
}
string PublicShowUI::getEquipProerty(int num)
{
    string name;
    switch (num) {
        case DictFightPropEnumHealth:
            name="生命";
            break;
        case DictFightPropEnumAttack:
            name="攻击";
            break;
        case DictFightPropEnumDefend:
            name="防御";
            break;
        case DictFightPropEnumCritic:
            name="暴击";
            break;
        case DictFightPropEnumTenaci:
            name="韧性";
            break;
        case DictFightPropEnumHit:
            name="精准";
            break;
        case DictFightPropEnumBlock:
            name="格挡";
            break;
        case DictFightPropEnumDamageAdd:
            name="伤害";
            break;
        case DictFightPropEnumFireResist:
            name="火焰抗性率";
            break;
        case DictFightPropEnumIceResist:
            name="冰霜抗性率";
            break;
        case DictFightPropEnumBoltResist:
            name="雷电抗性率";
            break;
        case DictFightPropEnumWindResist:
            name="飓风抗性率";
            break;
        case DictFightPropEnumPoisonResist:
            name="巫毒抗性率";
            break;
        default:
            break;
    }
    return name;
};
string PublicShowUI::getEquipParts(int num)
{
    string name;
    switch (num) {
        case DictEquipPartsEnumEquipSlot1EquipID:
            name="武器";
            break;
        case DictEquipPartsEnumEquipSlot2EquipID:
            name="头盔";
            break;
        case DictEquipPartsEnumEquipSlot3EquipID:
            name="腰带";
            break;
        case DictEquipPartsEnumEquipSlot4EquipID:
            name="铠甲";
            break;
        case DictEquipPartsEnumEquipSlot5EquipID:
            name="项链";
            break;
        case DictEquipPartsEnumEquipSlot6EquipID:
            name="锦囊";
            break;
        default:
            break;
    }
    return name;
}
/*target 那个组件加，
 point 坐标。（0，0）是右上。
 bol是否需要缩小true：是 。false：不需要；
 functionId ：红点出现和那个功能有关系
 */
void PublicShowUI::setDot(Node* target,Point point,bool bol, int functionId1 ,int functionId2 ,int functionId3,int functionId4,int functionId5 ,int functionId6 )
{
    if (target==NULL) {
        return;
    }
    float sx=GlobalInfo::getInstance()->screenScaleX;
    float sy=GlobalInfo::getInstance()->screenScaleY;
    const char*  list = GlobalInfo::getInstance()->dotList;
    char value = '1';
    Sprite* dot=(Sprite*)target->getChildByTag(1024);
    if (dot) {
        target->removeChildByTag(1024);
    }
    if (list[functionId1]==value or list[functionId2]==value or list[functionId3]==value or list[functionId4]==value or list[functionId5]==value or list[functionId6]==value) {
        Sprite* dotSprite=Sprite::create(IMG_CHAT_REDDOT);
        dotSprite->setAnchorPoint(Point::ZERO);
        if (bol) {
            dotSprite->setPosition(target->getContentSize().width/sx-dotSprite->getContentSize().width-point.x,target->getContentSize().height/sy-dotSprite->getContentSize().height-point.y);
        }else
        {
            dotSprite->setPosition(target->getContentSize().width-dotSprite->getContentSize().width-point.x,target->getContentSize().height-dotSprite->getContentSize().height-point.y);
        }
        
        target->addChild(dotSprite,15,1024);
    }
}
void PublicShowUI::refreshDot(Node* target,Point point,int functionId1 ,int functionId2 ,int functionId3)
{
    
}
Label* PublicShowUI::getLabel(const char* labelText,Color3B color,int fontSize,bool isShadow,bool isAutoScale,Size _size,TextHAlignment hAlignment)
{
    if(isAutoScale)
    {
        fontSize = fontSize * GlobalInfo::getInstance()->screenScaleX;
    }
    
    Label* label = Label::createWithTTF(labelText,"fonts/YABold.ttf",fontSize,_size,hAlignment);
    label->setColor(color);
    
    if(isShadow)
    {
        label->enableShadow(Color4B::BLACK,Size(3,-3));
        label->enableGlow(Color4B::BLACK);
    }
    return label;
}
Label* PublicShowUI::getLabelNumber(const char* labelText,Color3B color,int fontSize,bool isShadow,bool isAutoScale)
{
    if(isAutoScale)
    {
        fontSize = fontSize * GlobalInfo::getInstance()->screenScaleX;
    }
    
    
    Label* label = Label::createWithTTF(labelText,"fonts/YABold.ttf",fontSize);
    label->setColor(color);
    
    if(isShadow)
    {
        label->enableShadow(Color4B::BLACK,Size(3,-3));
        label->enableGlow(Color4B::BLACK);
    }
    return label;
}
Sprite* PublicShowUI::getAttribLabel(const char* title,const char* value,Color3B titleColor,Color3B valueColor,bool shadow,int titleSize,int valueSize,bool isAutoScale)
{
    Sprite* item = Sprite::create();
    item->setAnchorPoint(Point::ZERO);
    Label* label = Label::createWithTTF( title,"fonts/YABold.ttf",titleSize);
    label->setAnchorPoint(Point::ZERO);
    label->setColor(titleColor);
    if(shadow)
    {
        label->enableGlow(Color4B::BLACK);
        label->enableShadow(Color4B::BLACK);
    }
    
    item->addChild(label,1,2);
    Size size = label->getContentSize();
    if(value && strcmp(value, "") != 0)
    {
        Label* valueLabel = Label::createWithTTF( value,"fonts/YABold.ttf",valueSize);
        valueLabel->setAnchorPoint(Point::ZERO);
        valueLabel->setColor(valueColor);
        valueLabel->setPositionX(label->getContentSize().width +1);
        if(shadow)
        {
            valueLabel->enableGlow(Color4B::BLACK);
            valueLabel->enableShadow(Color4B::BLACK);
        }
        
        item->addChild(valueLabel);
        valueLabel->setTag(1);
        size.width = valueLabel->getPositionX() + valueLabel->getContentSize().width;
    }
    
    
    item->setContentSize(size);
    if(isAutoScale)
    {
        PublicShowUI::setTargetScale(item);
    }
    
    return item;
}
Node* PublicShowUI::getNumbers(int value,const char* numberPath,bool isGray,int space)
{
    //CCSprite* numbers = CCSprite::create();
    char numStr[20]={0};
	sprintf(numStr,"%d",value);
    //获取整张素材图片，图片内容为-0123456789；
    const char * path = NULL;
    if(numberPath == NULL)
    {
        path = IMG_PUBLIC_NUMBER1;
    }
    else
    {
        path = numberPath;
    }
    Sprite* numbers = Sprite::create();
    numbers->setAnchorPoint(Point::ZERO);
    Sprite* number_all = NULL;
    isGray ? number_all = GraySprite::create(path) : number_all = Sprite::create(path);
  
    number_all->setAnchorPoint(Point::ZERO);
    //获取整张图片长宽
	float allWidth= number_all->getContentSize().width;
	float allHeight= number_all->getContentSize().height;
	//获取单张图片长宽
	float width = allWidth/10;
	float height = allHeight;
    Rect rect;
    if(value <= -1)
    {
        rect = Rect(0,0,width,height);
		Sprite* numbers_now = Sprite::create(path,rect);
        numbers_now->setAnchorPoint(Point::ZERO);
		numbers_now->setPosition(Point::ZERO);
		numbers->addChild(numbers_now,0,0);
        numbers->setContentSize(Size(width,height));
        return numbers;
    }
    int len = strlen(numStr);
    int nowValue;
    int i = 0;
    for(i = 0; i < len; i++)
    {
        char nowNumber =  numStr[i];
        nowValue = nowNumber - '0';
		rect = Rect(width * nowValue,0,width,height);
        Sprite* numbers_now =   Sprite::createWithTexture(number_all->getTexture(), rect);
        numbers_now->setAnchorPoint(Point::ZERO);
        
		numbers_now->setPosition(Point(i*(width + space),0));
		numbers->addChild(numbers_now,i,i);
    }
    numbers->setContentSize(Size(i*width,height));
    return numbers;
}

Sprite* PublicShowUI::getBloodNumber(float value)
{
    int tvalue = int(value);
    Sprite* number = Sprite::create();
//    number->setDirty(true);
    Sprite* nowLabel = NULL;
    if(tvalue < 0)
    {
        nowLabel = Sprite::create(IMG_BATTLE_HURTMINUS);
    }
    else
    {
        nowLabel = Sprite::create();//IMG_HURT_PLUS
    }

    nowLabel->setAnchorPoint(Point::ZERO);
    number->addChild(nowLabel);
    number->setContentSize(nowLabel->getContentSize());
    
    string numberStr = PublicShowUI::numberToString(abs(tvalue));
    size_t len = numberStr.length();
    int nowValue = -1;
    Size size;
    for(int i = 0; i < len; i++)
    {
         char path[500] = {0};
        size = number->getContentSize();
        char nowNumber =  numberStr[i];
        nowValue = nowNumber - '0';
        sprintf(path, IMG_BATTLE_HURTNUM,nowValue);
        nowLabel = Sprite::create(path);
        nowLabel->setAnchorPoint(Point::ZERO);
        nowLabel->setPositionX(size.width);
        size.width = size.width + nowLabel->getContentSize().width;
        number->setContentSize(size);
        number->addChild(nowLabel);
    }
    return number;
}
Node* PublicShowUI::getVipLevelImage(int level)
{
//    int max = 16;
//    Sprite* vipLabelImage = Sprite::create(IMG_PUBLIC_VIPLABELIMAGE);
//    vipLabelImage->setAnchorPoint(Point::ZERO);
//    Size size = vipLabelImage->getContentSize();
//    
//    float _width = size.width / max;
//    int posX = _width * level;
//    
//    SpriteFrame* spriteFrame = SpriteFrame::create(IMG_PUBLIC_VIPLABELIMAGE, Rect(posX, 0, _width, size.height));
//    //等级
//    Sprite* imageLabel = Sprite::createWithSpriteFrame(spriteFrame);
//    imageLabel->setAnchorPoint(Point::ZERO);
//    return imageLabel;
    return NULL;
}
const char* PublicShowUI::converToChinese(const char* str)
{
	if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
	}
	else
	{
		return str;
	}
}
const char* PublicShowUI::getString(const string& name)
{
    return name.c_str();
}
Color3B PublicShowUI::getNameColor(int dictItemTypeID,int quality)
{
    string colorName = "";
    Color3B color = Color3B::WHITE;
    if(dictItemTypeID == DictItemTypeEnumItemHero)
    {
        DictHeroQuality* heroQuality = DictHeroQualityManager::getInstance()->getData(quality);
        colorName = heroQuality ? heroQuality->levelColour : "";
    }
    else if(dictItemTypeID == DictItemTypeEnumItem)
    {
        DictItemQuality* itemQuality = DictItemQualityManager::getInstance()->getData(quality);
        colorName = itemQuality ? itemQuality->levelColour : "";
    }

    if(colorName == "white")
    {
         color = Color3B::WHITE;
    }
    else if(colorName == "green")
    {
        color = PublicShowUI::getColor3b(0x0cb100);
    }
    else if(colorName == "blue")
    {
        color = PublicShowUI::getColor3b(0x00baff);
    }
    else if(colorName == "purple")
    {//紫
         color = PublicShowUI::getColor3b(0xc850ff);
    }
    else if(colorName == "orange")
    {
         color = PublicShowUI::getColor3b(0xff7800);
    }
    else if(colorName == "red")
    {
         color = PublicShowUI::getColor3b(0xff0000);
    }

    return color;
}
int PublicShowUI::getColorIndexByQuality(int dictItemTypeID,int quality)
{
    int index = 1;
    string colorName = "";
    if(dictItemTypeID == DictItemTypeEnumItemHero)
    {
        DictHeroQuality* heroQuality = DictHeroQualityManager::getInstance()->getData(quality);
        colorName = heroQuality ? heroQuality->levelColour : "";
    }
    else if(dictItemTypeID == DictItemTypeEnumItem)
    {
        DictItemQuality* itemQuality = DictItemQualityManager::getInstance()->getData(quality);
        colorName = itemQuality ? itemQuality->levelColour : "";
    }
    
    
    if(colorName.size() <= 0)
    {
        return index;
    }
    if(colorName == "white")
    {
        index = 1;
    }
    else if(colorName == "green")
    {
        index = 2;
    }
    else if(colorName== "blue")
    {
        index = 3;
    }
    else if(colorName == "purple")
    {//紫
        index = 4;
    }
    else if(colorName == "orange")
    {
        index = 5;
    }
    else
    {
          index = 5;
    }
    
    return index;

}
int PublicShowUI::getItemColorIndexByQuality(int itemId,int quality)//装备框颜色
{
    int index = 1;
    string colorName = "";
    
    DictItemEquip* data = DictItemEquipManager::getInstance()->getData(itemId);
    if (data) {
        colorName = data->levelColour;
    }
    
    if(colorName.size() <= 0)
    {
        return index;
    }
    if(colorName == "white")
    {
        index = 1;
    }
    else if(colorName == "green")
    {
        index = 2;
    }
    else if(colorName== "blue")
    {
        index = 3;
    }
    else if(colorName == "purple")
    {//紫
        index = 4;
    }
    else if(colorName == "orange")
    {
        index = 5;
    }
    else
    {
        index = 5;
    }
    
    return index;
    
}
float PublicShowUI::getFloorNumber(float number)
{
    string str = numberToString(number,5);
    vector<string> list = StringUtil::split(str, ".");
    str = list[1];
    str = str.replace(1, str.size(), "");
    str = list[0] + "." + str;
    float value =  atof(str.c_str());

    return value;
}
char* PublicShowUI::getUpperlimit(long price)
{
    char *stt=new char[120];
    memset(stt, 0, 120);
    int num = price / 1000000;
    if(num < 1)
    {
        ::sprintf(stt, "%ld",price);
    }
    else
    {
        float priceValue = price / 10000.0;//取有多少百万，的float
        num = price % 1000000 / 1000000;//最后一位
        if(num > 0)
        {
            priceValue = getFloorNumber(priceValue);
            sprintf(stt, "%.1f万",priceValue);
        }
        else
        {
           sprintf(stt, "%.0f万",priceValue);
        }
    }
    return stt;
}
//char* PublicShowUI::getUpperlimit(long price)
//{
//    char *stt=new char[120];
//    memset(stt, 0, 120);
//    int num = price / 1000000;
//    if(num < 1)
//    {
//        ::sprintf(stt, "%ld",price);
//    }
//    else if(num < 1000000.0)
//    {
//        num = price % 1000000 / 1000000;//最后一位
//        
//        float priceValue = price/1000000.0;//取有多少百万，的float
//        
//        
//        if(num > 0)
//        {
//            priceValue = getFloorNumber(priceValue);
//            sprintf(stt, "%.1f百万",priceValue);
//        }
//        else
//        {
//           sprintf(stt, "%.0f百万",priceValue);
//        }
//       
//    }
//    else if(price/100000000.0 >= 1)
//    {
//        float num = price %100000000/10000000;//最后一位
//        
//        float priceValue = price/100000000.0;//取有多少万，的float
//        
//        if(num > 0)
//        {
//            priceValue = getFloorNumber(priceValue);
//            sprintf(stt, "%.1f亿",priceValue);
//        }
//        else
//        {
//            sprintf(stt, "%.0f亿",priceValue);
//        }
//    }
//    return stt;
//}
//让某个物品摇动
void PublicShowUI::setTargetSwing(Node* target)
{
    float duration = .04;
    float rotation1 = -10;
    float rotation2 = 0;
    float rotation3 = 10;
    
    
    RotateTo* move_1 = RotateTo::create(duration,rotation1);
    RotateTo* move_2 = RotateTo::create(duration,rotation2);
    RotateTo* move_3 = RotateTo::create(duration,rotation3);
    DelayTime* delay = DelayTime::create(2);
    Sequence* sequence = Sequence::create(move_1,move_2,move_3,move_2,move_1,NULL);
    
    sequence = Sequence::create(sequence,sequence,sequence,move_2,delay,NULL);
    
    RepeatForever* repeat = RepeatForever::create(sequence);
    target->runAction(repeat);
}
void PublicShowUI::stopTargetSwing(Node* target)
{
    target->setRotation(0);
    target->stopAllActions();
}
//根据头衔id获得颜色
Color3B PublicShowUI::getTitleColor3B(int titleId)
{
    Color3B colo;
    switch (titleId) {
        case 1:
            colo = PublicShowUI::getColor3b(0Xffffff);
            break;
        case 2:
            colo = PublicShowUI::getColor3b(0X09ff03);
            break;
        case 3:
            colo = PublicShowUI::getColor3b(0X003603);
            break;
        case 4:
            colo = PublicShowUI::getColor3b(0X03cdff);
            break;
        case 5:
            colo = PublicShowUI::getColor3b(0X003f6b);
            break;
        case 6:
            colo = PublicShowUI::getColor3b(0Xcf97ff);
            break;
        case 7:
            colo = PublicShowUI::getColor3b(0X4b006e);
            break;
        case 8:
            colo = PublicShowUI::getColor3b(0Xfff000);
            break;
        case 9:
            colo = PublicShowUI::getColor3b(0Xfff88f);
            break;
        case 10:
            colo = PublicShowUI::getColor3b(0Xff9600);
            break;
        case 11:
            colo = PublicShowUI::getColor3b(0X581f00);
            break;
        default:
            colo = Color3B::WHITE;
            break;
    }
    return colo;
}
//根据剩余毫秒数，获得剩余时分秒
string PublicShowUI::getTime(long time,int type)
{
    char str[100] = "";
    if(type == 3)
    {
        sprintf(str, "%02ld:%02ld:%02ld",time/3600000,time%3600000/60000,time%3600000%60000/1000);
    }
    else if(type == 2)
    {
        sprintf(str, "%02ld:%02ld",time/60000,time%60000/1000);
    }
    else if(type == 1)
    {
        if(time/60000 > 59)
        {
            return PublicShowUI::numberToString(ceil(time/60000/(double)60))+"小时";
        }
        else
        {
            return PublicShowUI::numberToString(ceil(time/(double)60000))+"分钟";
        }
    }
    else if(type == 4)
    {//按天算
        int day = time / (3600000 * 24);
        int hour = (time - day * (3600000 * 24))/3600000; //(time % (3600000 * 24)) / 3600000;
        int minutes = (time - day * 3600000 * 24 - hour * 3600000)/60000;
        
        sprintf(str, "%d天%d小时%d分",day,hour,minutes);
    }
    return str;
}
//根据属性类型，和属性值，得到是否带%的值
string PublicShowUI::getAttributeVaule(int type,float vaule)
{
    string stt = "";
    char str [50]="";
    if(type == 6 || type == 7 || type == 8)
    {
        sprintf(str, "%.1f",(vaule * 100));
        stt = str;
        stt += "%";
    }
    else
    {
        stt = PublicShowUI::numberToString((long)vaule);
    }
    return stt;
}
//根据string参数的里面有没有%决定是否需要*100
string  PublicShowUI::getStringConVal(string conVal,const char* st)
{
    int len = (int)conVal.length();
    int point = (int)conVal.find(st);
    
    if(point >=0 && point <= len)
    {
        return conVal;
    }
    else
    {
        return PublicShowUI::numberToString((int)(std::atof(conVal.c_str())*100)) + "%";
    }
}

static bool __hasRunSRAND = false;
int PublicShowUI::genRandom(int min, int max)
{
    if (!__hasRunSRAND)
    {
        __hasRunSRAND = true;
        srand(time(NULL));
    }
  
    return rand() % (max - min + 1) + min;
}

//拼装数组类型JSON格式字符
const char* PublicShowUI::makeJosnData(const char* keystr,const char* value)
{

    string str = "\"" + string(keystr) + "\"" + ":"  + "\"" + string(value) + "\"";
    return str.c_str();
}

RenderTexture* PublicShowUI::createStroke(Sprite* label, int size, Color3B color, GLubyte opacity)
{
//    RenderTexture* rt = RenderTexture::renderTextureWithWidthAndHeight(
//                                                                           label->getTexture()->getContentSize().width + size * 2,
//                                                                           label->getTexture()->getContentSize().height+size * 2
//                                                                           );
    RenderTexture* rt = RenderTexture::create(label->getTexture()->getContentSize().width + size * 2, label->getTexture()->getContentSize().height + size * 2 );
    
    Point originalPos = label->getPosition();
    
    Color3B originalColor = label->getColor();
    
    GLubyte originalOpacity = label->getOpacity();
    
    bool originalVisibility = label->isVisible();
    
    label->setColor(color);
    
    label->setOpacity(opacity);
    
    label->setVisible(true);
    
    BlendFunc originalBlend = label->getBlendFunc();
    
    BlendFunc bf = {GL_SRC_ALPHA, GL_ONE};
    
    label->setBlendFunc(bf);
    
    Point bottomLeft = Point(
                             label->getTexture()->getContentSize().width * label->getAnchorPoint().x + size,
                             label->getTexture()->getContentSize().height * label->getAnchorPoint().y + size);
    
//    Point positionOffset= Point(
//                                - label->getTexture()->getContentSize().width / 2,
//                                - label->getTexture()->getContentSize().height / 2);
    
    Point positionOffset= Point(0,0);
    
    Point position = originalPos - positionOffset;//(originalPos, positionOffset);
    
    rt->begin();
    
    for (int i=0; i<360; i+= 15) // you should optimize that for your needs
    {
        label->setPosition(
                           Point(bottomLeft.x + sin(CC_DEGREES_TO_RADIANS(i))*size, bottomLeft.y + cos(CC_DEGREES_TO_RADIANS(i))*size)
                           );
        label->visit();  
    }  
    rt->end();  
    
    label->setPosition(originalPos);  
    label->setColor(originalColor);  
    label->setBlendFunc(originalBlend);  
    label->setVisible(originalVisibility);
    label->setOpacity(originalOpacity);  
    
    rt->setPosition(position);  
    
    return rt;
}
DictItemHero* PublicShowUI::getItemHeroByDictId(int id)
{
    DictItemHero* tempItem = NULL;
    Vector<DictItemHero*>* itemHeroList = DictItemHeroManager::getInstance()->getDataList();
    for(DictItemHero* item : *itemHeroList)
    {
        if(item->heroId == id)
        {
            tempItem = item;
            break;
        }
    }
    CC_SAFE_DELETE(itemHeroList);
    itemHeroList = NULL;
    return tempItem;
}
int PublicShowUI::getQuality(int typeId,int id)
{
    switch (typeId) {
        case DictItemTypeEnumItemHero://英雄
        {
            DictItemHero* dictItemHero = DictItemHeroManager::getInstance()->getData(id);
            return dictItemHero ? dictItemHero->quality :  1;
        }
            break;
        case DictItemTypeEnumItemEquip://装备
        {
            DictItemEquip* itemEquip =  DictItemEquipManager::getInstance()->getData(id);
            return itemEquip ? itemEquip->quality : 1;
        }
            break;
        case DictItemTypeEnumItem://道具
        {
            DictItem* dictItem = DictItemManager::getInstance()->getData(id);
            return dictItem ? dictItem->quality : 1;
        }
            break;
        case DictItemTypeEnumItemMater://材料
        {
            DictItemMater* itemMater = DictItemMaterManager::getInstance()->getData(id);
            return itemMater ? itemMater->quality : 1;
        }
            break;
        case DictItemTypeEnumItemBook://书信
        {
            DictItemBook* itemBook = DictItemBookManager::getInstance()->getData(id);
            return itemBook ? itemBook->quality : 1;
        }
            break;
        case DictItemTypeEnumRoleResource://角色资源
        {
            DictResource* itemMater = DictResourceManager::getInstance()->getData(id);
            return itemMater ? itemMater->quality : 1;
        }
            break;
        default:
            break;
    }
    return 1;
}
const char* PublicShowUI::getName(int typeID,int id)
{
    switch (typeID) {
        case DictItemTypeEnumItemHero://英雄
        {
            DictItemHero* dictItemHero = DictItemHeroManager::getInstance()->getData(id);
            return dictItemHero ? dictItemHero->name.c_str() :  "";
        }
            break;
        case DictItemTypeEnumItemEquip://装备
        {
            DictItemEquip* itemEquip = DictItemEquipManager::getInstance()->getData(id);
            return itemEquip ? itemEquip->name.c_str() : "";
        }
            break;
        case DictItemTypeEnumItem://道具
        {
            DictItem* dictItem = DictItemManager::getInstance()->getData(id);
            return dictItem ? dictItem->name.c_str() : "";
        }
            break;
        case DictItemTypeEnumItemMater://材料
        {
            DictItemMater* itemMater = DictItemMaterManager::getInstance()->getData(id);
            return itemMater ? itemMater->name.c_str() : "";
        }
            break;
        case DictItemTypeEnumItemBook://书信
        {
            DictItemBook* itemBook = DictItemBookManager::getInstance()->getData(id);
            return itemBook ? itemBook->name.c_str() : "";
        }
            break;
        case DictItemTypeEnumRoleResource://角色资源
        {
            DictResource* itemMater = DictResourceManager::getInstance()->getData(id);
            return itemMater ? itemMater->name.c_str() : "";
        }
            break;
        default:
            break;
    }
    return "";

}
//根据物品类型 物品id,得到描述
string PublicShowUI::getDescription(int typeId,int id)
{
    switch (typeId) {
        case DictItemTypeEnumItemHero://英雄
        {
            DictItemHero* dictItemHero = DictItemHeroManager::getInstance()->getData(id);
            return dictItemHero ? dictItemHero->desc :  "";
        }
            break;
        case DictItemTypeEnumItemEquip://装备
            return DictItemEquipManager::getInstance()->getData(id)->desc;
            break;
        case DictItemTypeEnumItem://道具
        {
            DictItem* dictItem = DictItemManager::getInstance()->getData(id);
            return dictItem ? dictItem->desc : "";
        }
            break;
        case DictItemTypeEnumItemMater://材料
        {
            DictItemMater* itemMater = DictItemMaterManager::getInstance()->getData(id);
            return itemMater ? itemMater->desc : "";
        }
            break;
        case DictItemTypeEnumItemBook://书信
        {
            DictItemBook* itemBook = DictItemBookManager::getInstance()->getData(id);
            return itemBook ? itemBook->desc : "";
        }
            break;
        case DictItemTypeEnumRoleResource://角色资源
        {
            DictResource* itemMater = DictResourceManager::getInstance()->getData(id);
            return itemMater ? itemMater->desc : "";
        }
            break;
        default:
            break;
    }
    return "";


}
string PublicShowUI::getItemType(int typeId,int id)
{
    switch (typeId) {
        case DictItemTypeEnumItemHero://英雄
        {
            return "英雄";
        }
            break;
        case DictItemTypeEnumItemEquip://装备
           return "装备";
            break;
        case DictItemTypeEnumItem://道具
        {
            return "道具";
        }
            break;
        case DictItemTypeEnumItemMater://材料
        {
            return "材料";
        }
            break;
        case DictItemTypeEnumItemBook://书信
           return "书信";
            break;
        case DictItemTypeEnumRoleResource://角色资源
        {
           return "角色资源";
        }
            break;
        default:
            break;
    }
    return "其他";

}
//根据物品类型，物品id，获得物品得资源
const char* PublicShowUI::getGoods(int typeId,int id)
{
    switch (typeId) {
        case DictItemTypeEnumItemHero://英雄
        {
            DictItemHero* dictItemHero = DictItemHeroManager::getInstance()->getData(id);
            if (dictItemHero) {
                return PublicShowUI::getResImgPath(AVATAR_HEAD_PATH,dictItemHero->resource.c_str());
            }else
            {
               DictHero*dictHero= DictHeroManager::getInstance()->getData(id);
               return dictHero ? PublicShowUI::getResImgPath(AVATAR_HEAD_PATH,dictHero->headResource.c_str()) :  "";
                
            }
            
        }
        break;
        case DictItemTypeEnumItemEquip://装备
        {
            DictItemEquip* itemEquip = DictItemEquipManager::getInstance()->getData(id);
            return itemEquip ? PublicShowUI::getResImgPath(IMG_PUBLIC_ITEM,itemEquip->resource.c_str()) :  "";
        }
        break;
        case DictItemTypeEnumItem://道具
        {
            DictItem* dictItem = DictItemManager::getInstance()->getData(id);
            return dictItem ?PublicShowUI::getResImgPath(IMG_PUBLIC_ITEM, dictItem->resource.c_str()) : "";
        }
        break;
        case DictItemTypeEnumItemMater://材料
        {
            DictItemMater* itemMater = DictItemMaterManager::getInstance()->getData(id);
            return itemMater ? PublicShowUI::getResImgPath(IMG_PUBLIC_ITEM,itemMater->resource.c_str()) : "";
        }
        break;
        case DictItemTypeEnumItemBook://书信
        {
            DictItemBook* itemBook = DictItemBookManager::getInstance()->getData(id);
            return itemBook ? PublicShowUI::getResImgPath(AVATAR_HEAD_PATH,itemBook->resource.c_str()) : "";
        }
        break;
        case DictItemTypeEnumRoleResource://角色资源
        {
            DictResource* itemMater = DictResourceManager::getInstance()->getData(id);
            return itemMater ? PublicShowUI::getResImgPath(IMG_PUBLIC_ITEM,itemMater->resource.c_str()) : "";
        }
            break;
        default:
            break;
    }
    return "";
}
Node* PublicShowUI::getAvatarHead(const char* name,int level,int prestige)
{
    Sprite* headBg = Sprite::create(IMG_MARKET_AUCTION_HEADBG);
    headBg->setAnchorPoint(Point::ZERO);
    const char* path = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH, name);
    Sprite* head = Sprite::create(path);
    if(head)
    {
        headBg->addChild(head);
        head->setScale(0.75);
        head->setPosition(headBg->getContentSize().width/2, headBg->getContentSize().height/2);

    }
    Sprite* headForm = Sprite::create(IMG_PUBLIC_HEROHEADBOX);
    headBg->addChild(headForm);
    headForm->setPosition(headBg->getContentSize().width/2, headBg->getContentSize().height/2);

    
    return headBg;
}
Node* PublicShowUI::getIconByTypeID(int typeId,int id,int quality)
{
    //头像背景
    quality = getColorIndexByQuality(typeId,quality);
    char sttr[100] = "";
    memset(sttr, 0, 100);
    sprintf(sttr,IMG_PUBLIC_HEROHEADFRAMEBG,quality);
    Sprite* iconBg=Sprite::create(sttr);
   
    if(!iconBg)
    {
        return NULL;
    }
    iconBg->setAnchorPoint(Point::ZERO);
    const char* path = getGoods(typeId,id);
    if(strcmp(path, "") != 0)
    {
        Sprite* icon = Sprite::create(path);
        if(icon)
        {
            float _scaleX = (iconBg->getContentSize().width - 5) / icon->getContentSize().height;
            icon->setScale(_scaleX);
            icon->setPosition(iconBg->getContentSize().width/2, iconBg->getContentSize().height/2);
            iconBg->addChild(icon);
        }
    }
    
    memset(sttr, 0, 100);
    sprintf(sttr,IMG_PUBLIC_HEADTALENTFRAME,quality);
    Sprite* headForm=Sprite::create(sttr);

    headForm->setPosition(iconBg->getContentSize().width/2, iconBg->getContentSize().height/2);
    iconBg->addChild(headForm);
    return iconBg;
}
string PublicShowUI::getUUID()
{
    string uuid = "";
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
       uuid = GlobalAppController::getUUID();
       uuid = "IOS&" + uuid;
    #endif
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    jobject jobj;
    //getStaticMethodInfo方法是调用静态类的，也可以不用调用静态类的getMethodInfo
  
    bool b = JniHelper::getStaticMethodInfo(minfo,
                                            "org.cocos2dx.cpp.AppActivity", //类路径
                                            "getUUID", //静态方法名
                                            "()Ljava/lang/String;");//括号里的是参数，后面的是返回值。

    if(b)
    {
        std::string ret;
        
        jstring jret = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
        ret = JniHelper::jstring2string(jret);
        minfo.env->DeleteLocalRef(jret);
        minfo.env->DeleteLocalRef(minfo.classID);
        uuid = "ANDROID&" + ret;
    }
    else
    {
        log("JniHelper::getMethodInfo error...");
    }
#endif
    return uuid;
}
string PublicShowUI::getSelfChannelLabel()
{
     string channelLabel = "emind";
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo info;
        bool ret = JniHelper::getStaticMethodInfo(info,"org.cocos2dx.cpp.AppActivity","getObj","()Ljava/lang/Object;");
        //先获得类的对象，然后用这个对象去调用它的非静态函
        jobject jobj;
        if(ret)
        {
            log("call static method");
            jobj = info.env->CallStaticObjectMethod(info.classID,info.methodID);
        }
        //getMethodInfo判断java定义的类非静态函数是否存在，返回bool
        ret = JniHelper::getMethodInfo(info,"org.cocos2dx.cpp.AppActivity","getSelfChannelLabel","()Ljava/lang/String;");
        if(ret)
        {
            log("call no-static method");
            //非静态函数调用的时候，需要的是对象，所以与静态函数调用的第一个参数不同
             jstring channel =  static_cast<jstring>(info.env->CallObjectMethod(jobj,info.methodID));
             channelLabel = JniHelper::jstring2string(channel);
//             info.env->DeleteLocalRef(channel);
//             info.env->DeleteLocalRef(info.classID);
        }
    #endif
    #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        channelLabel = GlobalAppController::getChannelLabel();
    #endif
    log("getSelfChannelLabel ====%s",channelLabel.c_str());
    return channelLabel;
}
void PublicShowUI::broadUserMsg(const char* msg,void* userData)
{
    EventCustom event(msg);
    event.setUserData(userData);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}
bool PublicShowUI::getProbability(int value)
{
    int num = PublicShowUI::genRandom(0,10000);

    return num <= value;
}