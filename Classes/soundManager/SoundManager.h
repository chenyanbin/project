//
//  SoundManager.h
//  SuiTang
//
//  Created by zhangxiaobin on 14-8-4.
//
//

#ifndef __SuiTang__SoundManager__
#define __SuiTang__SoundManager__


#include "cocos2d.h"
USING_NS_CC;

//andorid是ogg，ios是mp3
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#define MUSIC_EXT "ogg"
//#else
//#define MUSIC_EXT "mp3"
//#endif
#define MUSIC_EXT "mp3"
class SoundManager:public Ref
{
public:
	SoundManager(void);
	~SoundManager(void);
    
    //预加载所有背景音乐和音效文件
	static void preload(void);
    static void preLoad(const char* fileName);
    //播放背景音乐文件,循环
	static void playBackgroundMusic(const char* fileName);
	//停止背景音乐
	static void stopBackgroundMusic(void);
	//暂停背景音乐
	static void pauseBackgroundMusic(void);
    //恢复背景音乐
	static void resumeBackgroundMusic(void);
    //是否正在播放背景音乐
    static bool isBackgroundMusicPlaying(void);
    static void setBackgroundMusicVolume(float volume);
    static void resetBackgroundMusicVolume();//重置背景音乐
    //播放音效文件,播放一次
	static void playEffectMusic(const char* fileName,bool isLoop = false);
	//停止音效
	static void stopEffectMusic(void);
	//暂停音效
	static void pauseEffectMusic(void);
    //恢复音效
	static void resumeEffectMusic(void);
    //播放系统震动声音
    static void vibration(void);
    
private:
    //根据不同平台获取实际文件路径
    static char* getFilePath(const char* fileName);
    
private:
   
    static const char* nowMusic;
    
};

#endif /* defined(__SuiTang__SoundManager__) */
