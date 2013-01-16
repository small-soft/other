//
//  AMBeginerNavigateViewControl.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-9-3.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMBeginerNavigateViewControl.h"
#import "UserDataUtils.h"

@interface AMBeginerNavigateViewControl ()
@property (nonatomic,retain) NSMutableArray *contentData;
@property (nonatomic,retain) NSArray *sourceData;
@end

@implementation AMBeginerNavigateViewControl
@synthesize gallaryView = _gallaryView;
@synthesize contentData = _contentData;
@synthesize quitButton = _quitButton;
@synthesize sourceData = _sourceData;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
//    _gallaryView = [[AMPageControlView alloc]init];
//    self.gallaryView.frame = CGRectMake(self.view.frame.origin.x,self.view.frame.origin.y, self.view.frame.size.width, self.view.frame.size.height);
    self.gallaryView.showPageControl=YES;
    self.gallaryView.autoScroll=YES;
    self.gallaryView.delegate=self;
    [self.view addSubview:self.gallaryView];
    
    _quitButton = [[UIButton alloc] init];
    self.quitButton.backgroundColor = [UIColor clearColor];
    self.quitButton.frame = CGRectMake(75, 276, 170, 100);
//    [self.quitButton setTitle:@"点击退出" forState:UIControlStateNormal];
    [self.quitButton setBackgroundImage:[UIImage imageNamed:@"button.png"] forState:UIControlStateNormal];
    [self.quitButton setBackgroundImage:[UIImage imageNamed:@"button_press.png"] forState:UIControlStateHighlighted];
    [self.quitButton addTarget:self action:@selector(quitAction:) forControlEvents:UIControlEventTouchUpInside];
    
    _contentData = [[NSMutableArray alloc]init];
    for (int index = 0; index < BEGINER_NAVIGATE_IMAGEVIEW_COUNT; index++) {
        UIImageView *view = [[UIImageView alloc] initWithImage:[UIImage imageNamed: [[self.sourceData objectAtIndex:index] objectForKey:@"imageName"]]];
        view.frame = self.view.frame;
        [self.contentData addObject:view];
        [view release];
    }
    UIView *view = [[UIView alloc] initWithFrame:self.view.frame];
    UIImageView *view1 = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"image1.jpg" ]];
    view1.frame = self.view.frame;
    [view addSubview:view1];
    [view addSubview:self.quitButton];
    self.quitButton.hidden = NO;
    [self.contentData addObject:view];
    [view1 release];
    [view release];
//    [self.view addSubview:self.quitButton];
//    [self.navigationController setNavigationBarHidden:YES animated:YES];
//    [UserDataUtils setFirstLaunch:YES];
//    self.tabBarController.tabBar.hidden = YES;
//    [self.gallaryView reloadData];
    if ([[[UIDevice currentDevice] systemVersion] floatValue] < 5.0)
    {
        [self.navigationController setNavigationBarHidden:YES animated:YES];
        //    [UserDataUtils setFirstLaunch:YES];
        self.tabBarController.tabBar.hidden = YES;
        [self.gallaryView reloadData];
    }
    
}

- (void)viewDidUnload
{
    self.gallaryView = nil;
    self.contentData = nil;
    self.sourceData = nil;
    self.quitButton = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

-(void)viewWillAppear:(BOOL)animated
{
    [self.navigationController setNavigationBarHidden:YES animated:YES];
//    [UserDataUtils setFirstLaunch:YES];
    self.tabBarController.tabBar.hidden = YES;
    [self.gallaryView reloadData];
////    [self.gallaryView reloadData];
//    //    if(YES){
//    if(industrySelectNumber == 0){
//        [self.gallaryView reloadData];
//    }
//    else {
//        [self quitAction:self.quitButton];
//    }

}

- (void)viewWillDisappear:(BOOL)animated
{
    [self.navigationController setNavigationBarHidden:NO animated:YES];
}


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

-(void)dealloc
{
    [_gallaryView release];
    [_contentData release];
    [_quitButton release];
    [_sourceData release];
    [super dealloc];
}
#pragma mark system method end
#pragma mark setMethod
-(NSArray*)sourceData
{
    if (!_sourceData) {
        _sourceData = [[NSArray alloc]initWithObjects:
                       [NSDictionary dictionaryWithObjectsAndKeys:@"image0.jpg", @"imageName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"image1.jpg", @"imageName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"image2", @"imageName",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"image3", @"imageName",nil],nil ];
    }
    return _sourceData;
}
#pragma mark button action
-(void) quitAction: (id)sender;
{
    NSLog(@"成功退出！");
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_HOME_SELECT object:self];
    
}
#pragma mark AliGallary delegate method start
-(void)AliGallaryView:(UIView*)gallaryView didAtIndex:(NSUInteger)itemIndex
{
    return;
}
- (NSUInteger)numberOfSectionsInGallaryView:(UIView*)gallaryView
{
    if ([self.contentData count] > 0) {
        return [self.contentData count];
    }
    else {
        return 2;
    }
    
}
- (UIControl*)AliGallaryView:(UIView*)gallaryView atIndex:(NSUInteger)itemIndex
{
    UIImageView *view = [self.contentData objectAtIndex:itemIndex];
//    if (self.gallaryView.pageControl.currentPage == [self.contentData count] - 1) {
//        self.quitButton.hidden = NO;
//    }
//    else {
//        self.quitButton.hidden = YES;
//    }
    return (UIControl*)view;
}

-(void)AliGallaryView:(UIView*)gallaryView didAtEndIndex:(BOOL)isEndIndex
{
//    if (isEndIndex) {
//        self.quitButton.hidden = NO;
//    }
//    else {
//        self.quitButton.hidden = YES;
//    }
}

@end
