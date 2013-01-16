//
//  AMOfferWebDetailViewController.h
//  AlibabaMobile
//
//  Created by  on 12-2-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AMOfferTabViewController.h"
#import "AliTabContentViewController.h"

@class AMOfferDetail;

@interface AMOfferWebDetailViewController : AliTabContentViewController

@property (nonatomic, retain) AMOfferDetail * mOfferDetail;
@property (nonatomic, retain) IBOutlet UIWebView * mWebView;


@end
