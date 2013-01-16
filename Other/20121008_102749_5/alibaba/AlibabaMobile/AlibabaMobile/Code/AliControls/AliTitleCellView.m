//
//  AliTitleCellView.m
//  AlibabaMobile
//
//  Created by  on 12-2-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliTitleCellView.h"
#import "UIHelp.h"

@implementation AliTitleCellView

@synthesize titleLabel = _titleLabel;
@synthesize subTitleLabel = _subTitleLabel;
@synthesize  paddingLeft = _paddingLeft;

- (void) setPaddingLeft:(int)paddingLeft
{   _paddingLeft = paddingLeft;
    if(self.titleLabel != nil){
       
        self.titleLabel.frame = CGRectMake(_paddingLeft, self.titleLabel.frame.origin.y, self.titleLabel.frame.size.width, self.titleLabel.frame.size.height);
    }
}

- (id)initWithFrame:(CGRect)frame
{
    [super initWithFrame:frame];
    if(self){
        self.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"bg_subtitle"] ];
        _paddingLeft = 20;
        
        self.titleLabel = [[UILabel alloc] initWithFrame:CGRectMake(_paddingLeft, 0, 10, self.frame.size.height) ];
        self.subTitleLabel = [[UILabel alloc] initWithFrame:CGRectMake(self.frame.size.width-20, 0, 10, self.frame.size.height) ];
        
    }
    return self;
}

- (void) setSubTitle:(NSString *)subTitle
{

    self.subTitleLabel.backgroundColor = [UIColor clearColor];
    self.subTitleLabel.font = [UIFont boldSystemFontOfSize:9.0f];
    self.subTitleLabel.textColor = [UIHelp colorWithHexString:@"0x999999"];
    self.subTitleLabel.text = subTitle;
    [self.subTitleLabel sizeToFit];
     self.subTitleLabel.frame = CGRectMake(self.titleLabel.frame.origin.x+ self.titleLabel.frame.size.width, 0, self.subTitleLabel.frame.size.width, self.frame.size.height);
    
    [self addSubview:self.subTitleLabel];
    
    
}

- (void) setTitle:(NSString *)title
{
    
    self.titleLabel.backgroundColor = [UIColor clearColor];
    self.titleLabel.font = [UIFont boldSystemFontOfSize:16.0f];
    self.titleLabel.textColor = [UIHelp colorWithHexString:@"0x333333"];
    self.titleLabel.text = title;
    [self.titleLabel sizeToFit];
    self.titleLabel.frame = CGRectMake(_paddingLeft, 0, self.titleLabel.frame.size.width, self.frame.size.height);    
    [self addSubview:self.titleLabel];
    
    if(self.subTitleLabel!=nil){
        self.subTitleLabel.frame = CGRectMake(self.titleLabel.frame.origin.x+ self.titleLabel.frame.size.width, 0,  self.subTitleLabel.frame.size.width,self.frame.size.height);
    }
}

-(void) dealloc
{
    self.titleLabel = nil;
    self.subTitleLabel = nil;
    [super dealloc];
}

@end
