//
//  AliBannerView.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliBannerView.h"

@implementation AliBannerView
@synthesize contentView=_contentView;
@synthesize params=_params;

+(id)createView
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliBannerView" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AliBannerView class]])
        {
            return  (AliBannerView *)oneObject;
        }
    }
    return nil;
}

- (void)dealloc {
    [_contentView release];
    [_params release];
    [super dealloc];
}

-(void)setParams:(NSDictionary *)params
{
    _params = params;
    [self.contentView clear];
    self.contentView.url = [NSURL URLWithString:[params objectForKey:BANNER_PARAMS_URL]];
    self.contentView.mode = UIViewContentModeScaleToFill;
}
@end
