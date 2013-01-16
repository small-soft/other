//
//  VTViewController.m
//  VideoTest
//
//  Created by 刘 佳 on 13-1-4.
//  Copyright (c) 2013年 Small-Soft. All rights reserved.
//

#import "VTViewController.h"
#import "CustomMoviePlayerViewController.h"

@interface VTViewController ()

@end

@implementation VTViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    CustomMoviePlayerViewController *moviePlayer = [[[CustomMoviePlayerViewController alloc] init] autorelease];
    //将视频地址传过去
    moviePlayer.movieURL = [NSURL URLWithString:@"http://video.sina.com.cn/p/sports/k/v/2012-06-22/162361786435.html"];
    //然后播放就OK了
    [moviePlayer readyPlayer];
//    [self presentedViewController:moviePlayer];
    
    MPMoviePlayerViewController *controller = [[MPMoviePlayerViewController alloc]initWithContentURL:[NSURL URLWithString:@"http://v.youku.com/v_show/id_XMzk5NTUwNjk2.html?f=17834101"]];

    [self presentMoviePlayerViewControllerAnimated:controller];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
