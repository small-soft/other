//
//  AliChannelCellBlock.m
//  AlibabaMobile
//
//  Created by alimobile on 12-5-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliChannelCellBlock.h"
#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]
@interface AliChannelCellBlock()

@property (nonatomic,retain)UIImageView *identifyImage;

@end
@implementation AliChannelCellBlock
@synthesize title=_title;
@synthesize identifyImage = _identifyImage;

-(void)dealloc
{
    [_title release];
    [_identifyImage release];
    [super dealloc];
}

-(void)setupBG
{
    self.backgroundColor = [UIColor clearColor]; 
}
-(UIImageView*)identifyImage
{
    if (!_identifyImage) {
        _identifyImage = [[UIImageView alloc]init];
    }
    return _identifyImage;
}
-(void)setupIdentifyImage
{
    self.identifyImage.image = [UIImage imageNamed:@"icon_listarrow"];
    CGSize imageSize = [self.identifyImage.image size];
    self.identifyImage.frame = CGRectMake(self.frame.size.width - imageSize.width-20.0, (self.frame.size.height - imageSize.height)/2, imageSize.width, imageSize.height);
    [self addSubview:self.identifyImage];
    
}

-(UILabel*)title
{
    if (!_title) {
        _title = [[UILabel alloc]init];
    }
    return _title;
}
-(void)setupTitle
{
    self.title.frame = CGRectMake(20.0, 0.0, self.identifyImage.frame.origin.x - 20.0, self.frame.size.height);

    self.title.textColor = RGB(0x33,0x33,0x33);
    self.title.highlightedTextColor = RGB(0x33,0x33,0x33);
    self.title.backgroundColor = [UIColor clearColor];
    self.title.font = [UIFont systemFontOfSize:18.0];
    [self addSubview:self.title];
    
}

-(void)setupView
{
    [self setupBG];
    [self setupIdentifyImage];
    [self setupTitle];
}
-(void)awakeFromNib
{
    [super awakeFromNib];
    [self setupView];
}
@end
