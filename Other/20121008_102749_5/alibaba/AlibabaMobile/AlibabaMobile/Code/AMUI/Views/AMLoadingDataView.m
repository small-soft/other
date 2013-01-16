//
//  AMLoadingDataView.m
//  AlibabaMobile
//
//  Created by  on 12-7-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMLoadingDataView.h"
#import "ConstDef.h"

@implementation AMLoadingDataView

- (void)dealloc {
    AM_RELEASE_SAFELY(_noDataView);
    AM_RELEASE_SAFELY(_noDataMessageLabel);
    AM_RELEASE_SAFELY(_loadingView);
    [super dealloc];
}

-(void)showLoadingView
{
    [self setHidden:NO];
    [_loadingView setHidden:NO];
    [_noDataView setHidden:YES];
}

-(void)endLoadingView
{
    [self setHidden:YES];
}

-(void)showNodataMessage
{
    [self setHidden:NO];
    [_loadingView setHidden:YES];
    [_noDataView setHidden:NO];
}
@end
