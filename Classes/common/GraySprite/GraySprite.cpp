//
//  GraySprite.cpp
//  SuiTang
//
//  Created by mac on 14-6-15.
//
//

#include "GraySprite.h"
#include "../PublicShowUI.h"
GraySprite::GraySprite()
{
    
}
GraySprite::~GraySprite()
{
    
}
bool GraySprite::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Sprite::init());
        bref = true;
    } while (false);
    return bref;
}
GraySprite* GraySprite::create(const char* pszFileName)
{
     GraySprite* spr = GraySprite::create();
//     SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pszFileName);
//    if(frame)
//    {
//        spr->initWithTexture2D(frame->getTexture());
//    }
//    else
//    {
    
         spr->initWithFile(pszFileName);
//    }
   
   
    return spr;
}
void GraySprite::initWithFile(const char* pszFileName)
{
  
    Image* pOriginalImage = NULL;
    
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pszFileName);
    if(frame)
    {
        this->initWithSpriteFrame(frame);
        setGray();
        return;
    
    }
    else
    {
        pOriginalImage = new Image();
        pOriginalImage->initWithImageFile(pszFileName);
        
    }
    
    pOriginalImage->autorelease();
    
    
	
    
	assert(pOriginalImage != NULL);
    
	unsigned char *pData = pOriginalImage->getData();
//    log("pdata====%s",pData);
	int index = 0;
	for (int i = 0; i < pOriginalImage->getHeight(); i ++)
	{
		for (int j = 0; j < pOriginalImage->getWidth(); j ++)
		{
			unsigned int pos = index;
			unsigned int blue = pData[index ++];
			unsigned int green = pData[index ++];
			unsigned int red = pData[index ++];
            
            
			if(pOriginalImage->getFileType() == Image::Format::PNG && pOriginalImage->hasAlpha())
				index ++;
            
//			unsigned int gray = blue * 0.2 + green * 0.4 + red * 0.2;
            unsigned int gray = blue * 0.299 + green * 0.587 + red * 0.114;
          
            
			pData[pos] = (unsigned char)gray;
			pData[pos + 1] = (unsigned char)gray;
			pData[pos + 2] = (unsigned char)gray;
		}
	}
	Texture2D *pTexture = new Texture2D;
	pTexture->autorelease();
	pTexture->initWithImage(pOriginalImage);
    Sprite::initWithTexture(pTexture);
}
void GraySprite::setGray()
{
    this->setShaderProgram( ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
    GLProgram * p = new GLProgram();
    p->initWithFilenames("configs/gray.vsh", "configs/gray.fsh");
    p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    p->link();
    p->updateUniforms();
    this->setShaderProgram(p);
}
GraySprite* GraySprite::createWithTexture(Texture2D* pTexture)
{
    GraySprite* spr = GraySprite::create();
    spr->initWithTexture2D(pTexture);
    return spr;
}
bool GraySprite::initWithTexture2D(Texture2D* pTexture)
{
    bool bref = false;  
    do {
        CC_BREAK_IF(!Sprite::initWithTexture(pTexture));
        std::string pszFragSource =
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
    this->setShaderProgram(pProgram);
    pProgram->release();
    CHECK_GL_ERROR_DEBUG();
    
    this->getShaderProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    this->getShaderProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    this->getShaderProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    CHECK_GL_ERROR_DEBUG();
    
    this->getShaderProgram()->link();
    CHECK_GL_ERROR_DEBUG();
    
    this->getShaderProgram()->updateUniforms();
    CHECK_GL_ERROR_DEBUG();

        
        bref = true;
    } while (false);
    return bref;


}


