//
//  AMOperationItemView2.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-9-5.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMOperationItemView2.h"
#import <QuartzCore/QuartzCore.h>
#import "ConstDef.h"
#import "UIHelp.h"

@implementation AMOperationItemView2
@synthesize imageView = _imageView;
@synthesize imageView1 = _imageView1;
@synthesize imageView2 = _imageView2;
@synthesize imageView3 = _imageView3;

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
        NSArray *views = [[NSBundle mainBundle] loadNibNamed:@"AMOperationItemView2" owner:self options:nil];
        
        self = [[views objectAtIndex:0] retain];  
        self.imageView3.backgroundColor = [UIHelp colorWithHexString:@"0xf75567"];
        self.imageView.userInteractionEnabled = NO;
        self.imageView2.contentMode = UIViewContentModeScaleToFill;
        self.imageView2.autoresizingMask = ( UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight );
	}
	
	return self;
}

- (void)dealloc {
    AM_RELEASE_SAFELY(_imageView);
    AM_RELEASE_SAFELY(_imageView2);
    AM_RELEASE_SAFELY(_imageView1);
    AM_RELEASE_SAFELY(_imageView3);
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
