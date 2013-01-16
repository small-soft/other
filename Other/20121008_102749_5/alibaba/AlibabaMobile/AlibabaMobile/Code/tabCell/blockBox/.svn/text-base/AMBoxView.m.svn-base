//
//  AMBoxView.m
//  AlibabaMobile
//
//  Created by zzh on 12-3-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMBoxView.h"
#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]
@interface AMBoxView()

@end

@implementation AMBoxView
@synthesize boxIcon=_boxIcon;
@synthesize boxTitle=_boxTitle;
@synthesize boxFocusIcon=_boxFocusIcon;


-(void)awakeFromNib
{
    [super awakeFromNib];
    [self addSubview:self.boxFocusIcon];
    [self addSubview:self.boxIcon];


}
-(UIImageView*)boxIcon
{
    if (!_boxIcon) {
        _boxIcon = [[UIImageView alloc] init];
        _boxIcon.frame = CGRectMake(0,10,55,55);
       // [self addSubview:_boxIcon];
    }
    return _boxIcon;
}

-(UIImageView*)boxFocusIcon
{
    if (!_boxFocusIcon) {
        _boxFocusIcon = [[UIImageView alloc] init];
        _boxFocusIcon.frame = CGRectMake(0,10,55,55);
        _boxFocusIcon.backgroundColor = [UIColor clearColor];
     
    }
    return _boxFocusIcon;
}

-(UILabel*)boxTitle
{
    if (!_boxTitle) {
        _boxTitle = [[UILabel alloc] init];
        _boxTitle.frame = CGRectMake(0,65,55,22);
        _boxTitle.textColor = RGB(0x66,0x66,0x66) ;
        _boxTitle.font=[UIFont  fontWithName:@"Helvetica-Bold"  size:12];
        _boxTitle.textAlignment = UITextAlignmentCenter;
        [self addSubview:_boxTitle];
    }
    return _boxTitle;
}


- (void)dealloc {
    [_boxIcon release];
    [_boxTitle release];
    [_boxFocusIcon release];
    [super dealloc];
}
@end
