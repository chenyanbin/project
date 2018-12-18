//
//  LHVideoPlayerImpl.m
//  VideoDemo
//
//  Created by LiuYanghui on 14-5-5.
//
//

#import "LHVideoPlayerImpl.h"
#import "LHVideoPlayer.h"

@implementation LHVideoPlayerImpl

static LHVideoPlayer *_videoPlayer = nil;

+ (void)playMP4WithName: (NSString *)name VideoFrame:(CGRect)rect
{
    if (!_videoPlayer) {
        _videoPlayer = [[LHVideoPlayer alloc] init];
//        [_videoPlayer retain];
    }
    [_videoPlayer playMP4WithName:name VideoFrame:rect];

}

+ (void)skipVideo
{
    if (_videoPlayer) {
        [_videoPlayer skipVideo];
    }
}
+ (void)release
{
    if(_videoPlayer)
    {
        [_videoPlayer release];
        _videoPlayer = NULL;
    }
}
+ (void)setSkipTitle: (NSString *)title
{
    if (_videoPlayer) {
        [_videoPlayer setSkipTitle:title];
    }
}
+ (BOOL)isPlayFinished
{
    if(_videoPlayer)
    {
        return [_videoPlayer isPlayFinished];
    }
    return false;
}
@end