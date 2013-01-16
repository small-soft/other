//
//  AMOfferWebDetailViewController.m
//  AlibabaMobile
//
//  Created by  on 12-2-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMOfferWebDetailViewController.h"
#import "AMOfferDetail.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"

@implementation AMOfferWebDetailViewController

@synthesize mWebView,mOfferDetail;

- (void)viewWillAppear:(BOOL)animated
{
    [AMLogUtils appendLog:APP_PRD_DETAL_ELEVEN];
}

- (void) dealloc
{
    [mOfferDetail release];
    [mWebView release];
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
     mOfferDetail = [self.dataDict objectForKey:TAB_VIEW_DATA_OFFER_DETAIL];
    
    NSString *content = self.mOfferDetail.detail;
    content = (content?content:@"");
    
    [self.mWebView loadHTMLString:content baseURL:nil];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end
