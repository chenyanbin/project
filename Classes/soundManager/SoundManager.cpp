//
//  SoundManager.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 14-8-4.
//
//



#include "SoundManager.h"
#include "../common/GameConfig.h"
#include "SimpleAudioEngine.h"
#include "../commonData/GlobalInfo.h"
//import <AudioToolbox/AudioToolbox.h>
const char* SoundManager::nowMusic = NULL;

SoundManager::SoundManager(void)
{
    
}
SoundManager::~SoundManager(void)
{
    
}

//预加载所有背景音乐和音效文件
void SoundManager::preload(void)
{
  
    // preload background music and effect
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(getFilePath(MUSIC_LOGIN));
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(getFilePath(MUSIC_MAINSCENE));
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(getFilePath(MUSIC_BATTLE));

//
//    // set default volume
   CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1);
   CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1);

}
void SoundManager::setBackgroundMusicVolume(float volume)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
}
void SoundManager::resetBackgroundMusicVolume()//重置背景音乐
{
    setBackgroundMusicVolume(1);
}
void SoundManager::preLoad(const char* fileName)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(getFilePath(fileName));
}
//播放背景音乐文件,循环
void SoundManager::playBackgroundMusic(const char* fileName)
{
    if(GlobalInfo::getInstance()->getIsPlayBackMusic())
    {
       if(nowMusic != NULL && strcmp(fileName, nowMusic) == 0)
       {
           return;
       }
    
       nowMusic = fileName;
       stopBackgroundMusic();
       CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(getFilePath(fileName),true);
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(getFilePath(fileName),true);
        pauseBackgroundMusic();
    }
}

//停止背景音乐
void SoundManager::stopBackgroundMusic(void)
{
   
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
//暂停背景音乐
void SoundManager::pauseBackgroundMusic(void)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
//恢复背景音乐
void SoundManager::resumeBackgroundMusic(void)
{
    if(GlobalInfo::getInstance()->getIsPlayBackMusic())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
    
}
//是否正在播放背景音乐
bool SoundManager::isBackgroundMusicPlaying(void)
{
    return CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
}

//播放音效文件,播放一次
void SoundManager::playEffectMusic(const char* fileName,bool isLoop )
{
    if(GlobalInfo::getInstance()->getIsPlayEffectMusic())
    {
        if(strcmp(fileName, "") == 0)
        {
            return;
        }
//        log(" sound fileName==%s",fileName);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(getFilePath(fileName), isLoop);
    }
}
//停止音效
void SoundManager::stopEffectMusic(void)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}
//暂停音效
void SoundManager::pauseEffectMusic(void)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
}
//恢复音效
void SoundManager::resumeEffectMusic(void)
{
    if(GlobalInfo::getInstance()->getIsPlayEffectMusic())
    {
         CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
    }
}
//播放系统震动声音
void SoundManager::vibration(void)
{
   
//    CocosDenshion::SimpleAudioEngine::getInstance()->vibrate();
}
//根据不同平台获取实际文件路径
char* SoundManager::getFilePath(const char* fileName)
{
    static char filePath[100] = "/0";
    sprintf(filePath,"music/%s/%s.%s",MUSIC_EXT,fileName,MUSIC_EXT);
    
    return filePath;
   
}
