//
//  AMOperationItemView1.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-31.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMOperationItemView1.h"
#import <QuartzCore/QuartzCore.h>
#import "ConstDef.h"
#import "UIHelp.h"

@implementation AMOperationItemView1
@synthesize imageView1 = _imageView1;
@synthesize imageView2 = _imageView2;
@synthesize label = _label;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}
- (id)init {
	self = [super init];
	
	if (self) {
        NSArray *views = [[NSBundle mainBundle] loadNibNamed:@"AMOperationItemView1" owner:self options:nil];
        
        self = [[views objectAtIndex:0] retain];  
        self.label.textColor = [UIHelp colorWithHexString:@"0x64300b"];
	}
	
	return self;
}

- (void)dealloc {
    AM_RELEASE_SAFELY(_imageView2);
    AM_RELEASE_SAFELY(_imageView1);
    AM_RELEASE_SAFELY(_label);
	[super dealloc];
}

/*
 // Only override drawRect: if you perform custom drawing.
 // An empty implementation adversely affects performance during animation.
 - (void)drawRect:(CGRect)rect
 {
 // Drawing code
 }
 */

@end
