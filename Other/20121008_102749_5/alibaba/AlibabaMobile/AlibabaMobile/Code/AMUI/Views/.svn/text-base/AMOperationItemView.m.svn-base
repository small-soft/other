//
//  AMOperationItemView.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-8-29.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMOperationItemView.h"
#import <QuartzCore/QuartzCore.h>
#import "ConstDef.h"
#import "UIHelp.h"

@implementation AMOperationItemView
@synthesize imageView = _imageView;
@synthesize label1 = _label1;
@synthesize label2 = _label2;

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
        NSArray *views = [[NSBundle mainBundle] loadNibNamed:@"AMOperationItemView" owner:self options:nil];
        
        self = [[views objectAtIndex:0] retain];   
        self.label2.textColor = [UIHelp colorWithHexString:@"666666"];
        self.label2.font = [UIFont systemFontOfSize:12.0f];
        self.label1.font = [UIFont fontWithName:@"Arial-BoldMT" size:15.0f];
	}
	
	return self;
}

- (void)dealloc {
    AM_RELEASE_SAFELY(_label2);
    AM_RELEASE_SAFELY(_imageView);
    AM_RELEASE_SAFELY(_label1);
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
