#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayer.h>      //导入视频播放库

@interface CustomMoviePlayerViewController : UIViewController
{
    MPMoviePlayerController *mp;
    NSURL *movieURL;                        //视频地址
    UIActivityIndicatorView *loadingAni;    //加载动画
    UILabel *label;                            //加载提醒
}
@property (nonatomic,retain) NSURL *movieURL;

//准备播放
- (void)readyPlayer;

@end