//
//  SKViewController.m
//  Shake
//
//  Created by 佳 刘 on 12-10-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "SKViewController.h"
#import <AudioToolbox/AudioServices.h>

@interface SKViewController ()

@end

@implementation SKViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

-(void)play {
    NSString *path = [[NSBundle mainBundle]pathForResource:@"win" ofType:@"wav"];
    SystemSoundID soundId;
    AudioServicesCreateSystemSoundID((CFURLRef)[NSURL fileURLWithPath:path], &soundId);
    // 只播放声音
    //    AudioServicesPlaySystemSound(soundId);
    
    // 播放声音并且震动
    AudioServicesPlayAlertSound(soundId);
    
    // 只震动
//    AudioServicesPlayAlertSound(kSystemSoundID_Vibrate);
}
@end
