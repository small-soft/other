//
//  BrandView.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-8-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMBrandView.h"
#import "UIHelp.h"

@implementation AMBrandView

@synthesize boxIcon=_boxIcon;
@synthesize boxTitle=_boxTitle;
@synthesize boxFocusIcon=_boxFocusIcon;
@synthesize icon=_icon;
@synthesize keywords;
@synthesize catId;


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
        _boxIcon.frame = CGRectMake(0,0,self.frame.size.width,self.frame.size.height);
        // [self addSubview:_boxIcon];
    }
    return _boxIcon;
}

-(UIImageView*)boxFocusIcon
{
    if (!_boxFocusIcon) {
        _boxFocusIcon = [[UIImageView alloc] init];
        _boxFocusIcon.frame = CGRectMake(0,0,self.frame.size.width,self.frame.size.height);
        _boxFocusIcon.backgroundColor = [UIColor clearColor];
        
    }
    return _boxFocusIcon;
}

-(UILabel*)boxTitle
{
    if (!_boxTitle) {
        _boxTitle = [[UILabel alloc] init];
        _boxTitle.frame = CGRectMake(0,32,self.frame.size.width,15);
        _boxTitle.textColor = [UIHelp colorWithHexString:@"0x666666"] ;
        _boxTitle.font=[UIFont  fontWithName:@"Heiti SC"  size:8];
        _boxTitle.textAlignment = UITextAlignmentCenter;
        _boxTitle.backgroundColor = [UIColor clearColor];
        [self addSubview:_boxTitle];
    }
    return _boxTitle;
}

-(HJManagedImageV*)icon
{
    if (!_icon) {
        _icon = [[HJManagedImageV alloc ]init ];
        _icon.image = nil;
//        _icon.url = [NSURL URLWithString:data.logo];
        _icon.frame = CGRectMake(14,5,65,22);
        _icon.layer.masksToBounds = YES;
        _icon.backgroundColor = [UIColor clearColor];
        [self addSubview:_icon];
        

    }
    
    return _icon;
    
}


- (void)dealloc {
    [_boxIcon release];
    [_boxTitle release];
    [_boxFocusIcon release];
    [super dealloc];
}




@end
