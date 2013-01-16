//
//  searchBarSelectView.h
//  AlibabaMobile
//
//  Created by alimobile on 12-4-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface searchBarSelectView : UIControl

@property (retain, nonatomic) IBOutlet UILabel *content;
@property (retain, nonatomic) IBOutlet UIImageView *identifyImage;
@property (nonatomic) NSUInteger selectedState;
+(id)createView;
@end
