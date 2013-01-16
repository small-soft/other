//
//  AliBannerView.h
//  AlibabaMobile
//
//  Created by alimobile on 12-4-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "HJManagedImageV.h"
#define BANNER_PARAMS_URL @"url"

@interface AliBannerView : UIControl
@property (nonatomic,retain)NSDictionary *params;
@property (retain, nonatomic) IBOutlet HJManagedImageV *contentView;
+(id)createView;
@end
