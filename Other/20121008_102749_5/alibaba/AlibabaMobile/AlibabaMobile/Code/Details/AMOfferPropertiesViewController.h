//
//  AMOfferPropertiesViewController.h
//  AlibabaMobile
//
//  Created by xiejin on 2/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliTabContentViewController.h"
#import "AMOfferTabViewController.h"

@class AMOfferDetail;

@interface AMOfferPropertiesViewController : AliTabContentViewController
{
    AMOfferDetail * mOfferDetail;
}

@property (nonatomic, retain) IBOutlet UIScrollView * mMainScrollView;


@end
