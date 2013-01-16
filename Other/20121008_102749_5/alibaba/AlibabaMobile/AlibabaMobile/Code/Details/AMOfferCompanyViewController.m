//
//  AMOfferCompanyViewController.m
//  AlibabaMobile
//
//  Created by mardin partytime on 2/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "AMOfferCompanyViewController.h"
#import "AMOfferDetail.h"
#import "SystemUtils.h"
#import "AliMemberContactView.h"

@implementation AMOfferCompanyViewController

@synthesize  mMainScrollView;


- (void) dealloc
{
    [mOfferDetail release];
    [mMainScrollView release];
    
    [super dealloc];
}


#pragma mark - View lifecycle


- (void)viewDidLoad
{
    [super viewDidLoad];
    
     mOfferDetail = [self.dataDict objectForKey:TAB_VIEW_DATA_OFFER_DETAIL];
    
    if(mOfferDetail != nil
       && mOfferDetail.companyBrief != nil ){
        
        AliMemberContactView * contactView = [[AliMemberContactView alloc] initWithFrame:CGRectMake(0, 40, 320, 377)];
        [contactView setNavigationController:self.navigationController];
        [self.mMainScrollView addSubview:contactView];
        [contactView setContactInfo:mOfferDetail.companyBrief memberId:mOfferDetail.memberId];
        [contactView reloadData];
        
        [self.view addSubview:contactView];
        [contactView release];
        
        
    }
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
