//
//  AliImageMagazineCategoryItem.m
//  AlibabaMobile
//
//  Created by  on 12-2-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliImageMagazineItem.h"
#import "UIHelp.h"

@interface AliImageMagazineItem()

- (void) initContentView;

@end

@implementation AliImageMagazineItem

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
    
    
    self.titleLabel = [[UILabel alloc] initWithFrame:CGRectMake(4, 140, 110, 20)];
    self.titleLabel.numberOfLines = 0;
    self.titleLabel.lineBreakMode = UILineBreakModeWordWrap;
    self.titleLabel.backgroundColor = [UIColor clearColor];
    self.titleLabel.textColor = [UIColor blackColor];
    self.titleLabel.font = [UIFont systemFontOfSize:12.0f];
    self.titleLabel.textAlignment = UITextAlignmentLeft;

    [self addSubview:self.titleLabel];
    
}

- (void) setSubject:(NSString *) subject
{
    self.titleLabel.text = subject;
    int textHeight = [UIHelp getLabelSizeWithFont:self.titleLabel.font labelString:self.titleLabel.text labelWidth:self.titleLabel.frame.size.width].height;
    textHeight = (textHeight<30?textHeight:30);
    self.titleLabel.frame = CGRectMake(self.titleLabel.frame.origin.x, self.titleLabel.frame.origin.y, self.titleLabel.frame.size.width, textHeight);
}

- (void) dealloc
{
    self.titleLabel = nil;
    self.imageView = nil;
    
    [super dealloc];
}


@end
