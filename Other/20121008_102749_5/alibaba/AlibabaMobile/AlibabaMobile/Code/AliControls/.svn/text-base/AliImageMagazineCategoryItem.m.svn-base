//
//  AliImageMagazineCategoryItem.m
//  AlibabaMobile
//
//  Created by  on 12-2-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliImageMagazineCategoryItem.h"

@interface AliImageMagazineCategoryItem ()

- (void) initContentView;

@end

@implementation AliImageMagazineCategoryItem

@synthesize titleLabel = _titleLabel;
@synthesize imageView = _imageView;


- (id)init{
    [super initWithFrame:CGRectMake(0, 0, 130, 150)];
    if(self){
        [self initContentView];
    }
    return self;
}

- (void) initContentView
{
    self.backgroundColor = [UIColor clearColor];
    
    UIImageView * bkImageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"bg_Album_catalog"]];
    bkImageView.backgroundColor = [UIColor clearColor];
    [bkImageView sizeToFit];
    bkImageView.frame = CGRectMake(10, 10,bkImageView.frame.size.width, bkImageView.frame.size.height);
    [self addSubview:bkImageView];
    [bkImageView release];
    
    self.imageView = [[HJManagedImageV alloc] initWithFrame:CGRectMake(15, 15, 90, 120)];
    self.imageView.backgroundColor = [UIColor clearColor];
    [self addSubview:self.imageView];
    
    
    UIImageView *titleBkImg = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"bg_Album_catalogtitle"]];
    titleBkImg.backgroundColor = [UIColor clearColor];
    [titleBkImg sizeToFit];
    titleBkImg.frame = CGRectMake(5, 100, 80, 40);
    [self addSubview:titleBkImg];
    [titleBkImg release];
    
    self.titleLabel = [[UILabel alloc] initWithFrame:CGRectMake(15, 107, 63, 22)];
    self.titleLabel.backgroundColor = [UIColor clearColor];
    self.titleLabel.textColor = [UIColor whiteColor];
    self.titleLabel.font = [UIFont boldSystemFontOfSize:14.0f];
    self.titleLabel.textAlignment = UITextAlignmentCenter;
    [self addSubview:self.titleLabel];
    
}

- (void) dealloc
{
    [_titleLabel release];
    [_imageView release];
    
    [super dealloc];
}


@end
