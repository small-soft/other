//
//  AdViewController.m
//  MobWinSample
//
//  Created by ben.zhaoguo on 11-12-26.
//  Copyright 2011 Tencent. All rights reserved.
//

#import "AdViewController.h"

@implementation AdViewController
@synthesize adType;

// The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
/*
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization.
    }
    return self;
}
*/


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];

	
    UIBarButtonItem *backButton = [[[UIBarButtonItem alloc] 
								  initWithTitle:@"返回" 
								  style:UIBarButtonItemStylePlain 
								  target:self 
								  action:@selector(backPressed:)] autorelease];
    self.navigationItem.hidesBackButton = YES;
    self.navigationItem.leftBarButtonItem = backButton;
	self.navigationItem.title = @"腾讯MobWIN v1.3.1";
	
	//
	// 腾讯MobWIN提示：开发者必须调用
	// adType {MobWINBannerSizeIdentifier320x50, MobWINBannerSizeIdentifier300x250,
	// MobWINBannerSizeIdentifier468x60, MobWINBannerSizeIdentifier728x90}
	//
	adBanner = [[MobWinBannerView alloc] initMobWinBannerSizeIdentifier:adType]; 
	adBanner.rootViewController = self;
	[adBanner setAdUnitID:@"A495798C12C030F28E7711F3613DFC1B"];
	[self.view addSubview:adBanner];
    
    //
	// 腾讯MobWIN提示：开发者可选调用
	// 获取MobWinBannerViewDelegate回调消息
	//
    adBanner.delegate = self;
    //
	// 腾讯MobWIN提示：开发者可选调用
	//
	adBanner.adGpsMode = NO;
	// adBanner.adTextColor = [UIColor whiteColor];
	// adBanner.adSubtextColor = [UIColor colorWithRed:255.0/255.0 green:162.0/255.0 blue:0.0/255.0 alpha:1];
	// adBanner.adBackgroundColor = [UIColor colorWithRed:2.0/255.0 green:12.0/255.0 blue:15.0/255.0 alpha:1];
	//
	
	//
	// 腾讯MobWIN提示：开发者必须调用
	//
	// 发起广告请求方法
	//
	[adBanner startRequest];	
	[adBanner release];
}

- (void)viewWillDisappear:(BOOL)animated {	
}

// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return YES;
}


- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}

- (IBAction)backPressed:(id)sender {
	[self.navigationController popViewControllerAnimated:YES];
}

- (void)bannerViewDidReceived {
    NSLog(@"MobWIN %s", __FUNCTION__);
}

- (void)bannerViewFailToReceived {
    NSLog(@"MobWIN %s", __FUNCTION__);
}

- (void)bannerViewDidPresentScreen {
    NSLog(@"MobWIN %s", __FUNCTION__);
}

- (void)bannerViewDidDismissScreen {
    NSLog(@"MobWIN %s", __FUNCTION__);
}

- (void)bannerViewWillLeaveApplication {
    NSLog(@"MobWIN %s", __FUNCTION__);
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
	//
	// 腾讯MobWIN提示：开发者必须调用 
	// 可在viewDidUnload调用或者在应用页面返回时调用或者在dealloc中调用
	// 目前已在viewWillDisappear中调用
	//
	[adBanner stopRequest];
	[adBanner removeFromSuperview];
	[super dealloc];
}


@end
