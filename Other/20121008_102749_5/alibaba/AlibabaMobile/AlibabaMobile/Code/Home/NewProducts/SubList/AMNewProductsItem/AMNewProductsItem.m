//
//  AMNewProductsItem.m
//  AlibabaMobile
//
//  Created by  xiaowen on 12-5-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMNewProductsItem.h"
#import "UIHelp.h"

@interface AMNewProductsItem()

- (void) initContentView;

@end

@implementation AMNewProductsItem

@synthesize factoryLable = _factoryLable;
@synthesize factoryPreLable = _factoryPreLable;
@synthesize factoryEndLable = _factoryEndLable;
@synthesize titleLabel = _titleLabel;
@synthesize imageView = _imageView;


- (id)init{
    [super initWithFrame:CGRectMake(0, 0, 110, 170)];
    if(self){
        [self initContentView];
    }
    return self;
}

- (void) initContentView
{
    self.backgroundColor = [UIColor clearColor];
    
    UIImageView * bkImageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"bg_Album_track"]];
    bkImageView.backgroundColor = [UIColor clearColor];
    [bkImageView sizeToFit];
    bkImageView.frame = CGRectMake(0, 0,bkImageView.frame.size.width, bkImageView.frame.size.height);
    [self addSubview:bkImageView];
    [bkImageView release];
    
    self.imageView = [[HJManagedImageV alloc] initWithFrame:CGRectMake(9, 9, 90, 120)];
    self.imageView.backgroundColor = [UIColor clearColor];
    [self addSubview:self.imageView];
    
    
//    self.titleLabel = [[UILabel alloc] initWithFrame:CGRectMake(4, 140, 110, 20)];
//    self.titleLabel.numberOfLines = 0;
    self.titleLabel = [[UILabel alloc] initWithFrame:CGRectMake(4, 130, 110, 20)];
    self.titleLabel.numberOfLines = 1;
    self.titleLabel.lineBreakMode = UILineBreakModeTailTruncation;
    self.titleLabel.backgroundColor = [UIColor clearColor];
    self.titleLabel.textColor = [UIColor blackColor];
    self.titleLabel.font = [UIFont systemFontOfSize:12.0f];
    self.titleLabel.textAlignment = UITextAlignmentLeft;

    [self addSubview:self.titleLabel];
    
    {
        CGSize labelSize = [@"出厂价:" sizeWithFont:[UIFont systemFontOfSize:12.0f]];
        self.factoryPreLable = [[UILabel alloc] initWithFrame:CGRectMake(4, 150, labelSize.width, 20)];
        self.factoryPreLable.font = [UIFont systemFontOfSize:12.0f];
        self.factoryPreLable.numberOfLines = 1;
        self.factoryPreLable.lineBreakMode = UILineBreakModeWordWrap;
        self.factoryPreLable.backgroundColor = [UIColor clearColor];
        self.factoryPreLable.textColor = [UIColor blackColor];
        self.factoryPreLable.textAlignment = UITextAlignmentLeft;
        [self addSubview:self.factoryPreLable];
    }
    
    
}

- (void) setSubject:(NSString *) subject
{
    self.titleLabel.text = subject;
    int textHeight = [UIHelp getLabelSizeWithFont:self.titleLabel.font labelString:self.titleLabel.text labelWidth:self.titleLabel.frame.size.width].height;
    textHeight = (textHeight<30?textHeight:30);
    self.titleLabel.frame = CGRectMake(self.titleLabel.frame.origin.x, self.titleLabel.frame.origin.y, self.titleLabel.frame.size.width, textHeight);
    
    self.factoryPreLable.text = @"出厂价:";
    
}

- (void) setPriceAndUnit:(NSString *)price setUnit:(NSString*)unit
{
    
    {
        CGSize labelSize = [price sizeWithFont:[UIFont systemFontOfSize:12.0f]];
        self.factoryLable = [[UILabel alloc] initWithFrame:CGRectMake(4+self.factoryPreLable.frame.size.width, 150, labelSize.width, 20)];
        self.factoryLable.font = [UIFont systemFontOfSize:12.0f];
        self.factoryLable.numberOfLines = 1;
        self.factoryLable.lineBreakMode = UILineBreakModeWordWrap;
        self.factoryLable.backgroundColor = [UIColor clearColor];
        self.factoryLable.textColor = [UIColor redColor];
        self.factoryLable.textAlignment = UITextAlignmentLeft;
        [self addSubview:self.factoryLable];
        self.factoryLable.text = price;
    }
    
    {
        NSString * unitTotal = [NSString stringWithFormat:@"元/%@",unit];
        CGSize labelSize = [unitTotal sizeWithFont:[UIFont systemFontOfSize:12.0f]];
        self.factoryEndLable = [[UILabel alloc] initWithFrame:CGRectMake(4+self.factoryPreLable.frame.size.width+self.factoryLable.frame.size.width, 150, labelSize.width, 20)];
        self.factoryEndLable.font = [UIFont systemFontOfSize:12.0f];
        self.factoryEndLable.numberOfLines = 1;
        self.factoryEndLable.lineBreakMode = UILineBreakModeWordWrap;
        self.factoryEndLable.backgroundColor = [UIColor clearColor];
        self.factoryEndLable.textColor = [UIColor blackColor];
        self.factoryEndLable.textAlignment = UITextAlignmentLeft;
        [self addSubview:self.factoryEndLable];
        self.factoryEndLable.text = unitTotal;
    }
    
}


- (void) dealloc
{
    self.titleLabel = nil;
    self.imageView = nil;
    self.factoryLable = nil;
    self.factoryPreLable = nil;
    self.factoryEndLable = nil;
    [super dealloc];
}


@end
