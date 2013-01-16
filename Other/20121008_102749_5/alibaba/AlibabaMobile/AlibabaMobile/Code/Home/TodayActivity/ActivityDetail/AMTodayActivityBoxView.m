//
//  AMTodayActivityBoxView.m
//  AlibabaMobile
//
//  Created by amon on 12-8-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMTodayActivityBoxView.h"
#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]
@interface AMTodayActivityBoxView()

@end

@implementation AMTodayActivityBoxView
@synthesize leaveFactoryImage=_leaveFactoryImage;
@synthesize subject=_subject;
@synthesize leaveFactoryImageFocusIcon=_leaveFactoryImageFocusIcon;
@synthesize leaveFactoryPrice = _leaveFactoryPrice;
@synthesize leaveFactoryPricePre = _leaveFactoryPricePre;
@synthesize unit = _unit;
@synthesize listImg = _listImg;
@synthesize blockBackImg = _blockBackImg;
@synthesize loadingTextNotify = _loadingTextNotify;

-(void)awakeFromNib
{
    [super awakeFromNib];
    [self initBackGround];
    [self addSubview:self.loadingTextNotify];
//    [self addSubview:self.leaveFactoryImageFocusIcon];
//    [self addSubview:self.leaveFactoryImage];
    [self addSubview:self.listImg];
    [self addSubview:self.leaveFactoryPricePre];
//    [self addSubview:self.leaveFactoryPrice];
//    [self addSubview:self.unit];
    
//    [self initBackGround];
    [self insertSubview:self.blockBackImg atIndex:0];//放到最底层


}


-(HJManagedImageV*)listImg
{
    if (!_listImg) {
        _listImg = [[HJManagedImageV alloc] init];
        _listImg.frame = CGRectMake(0,0,147,145);
    }
    return _listImg;
}

-(UILabel*)subject
{
    if (!_subject) {
        _subject = [[UILabel alloc] init];
        _subject.frame = CGRectMake(10,150,137,15);
        _subject.textColor = RGB(0x33,0x33,0x33) ;
        _subject.numberOfLines = 1;
        _subject.font=[UIFont  fontWithName:@"Helvetica-Bold"  size:12];
        _subject.textAlignment = UITextAlignmentCenter;
        [self addSubview:_subject];
    }
    return _subject;
}

-(UILabel*)leaveFactoryPricePre
{
    if (!_leaveFactoryPricePre) {
        _leaveFactoryPricePre = [[UILabel alloc] init];
        NSString *leaveFactoryPricePreString = @"出厂价:";
        CGSize labelSize = [leaveFactoryPricePreString sizeWithFont:[UIFont systemFontOfSize:12.0f]];
        _leaveFactoryPricePre.frame = CGRectMake(10,170,labelSize.width,20);
        _leaveFactoryPricePre.textColor = RGB(0x66,0x66,0x66) ;
        _leaveFactoryPricePre.text = leaveFactoryPricePreString;
        _leaveFactoryPricePre.numberOfLines = 1;
        _leaveFactoryPricePre.font=[UIFont  fontWithName:@"Helvetica-Bold"  size:12];
        _leaveFactoryPricePre.textAlignment = UITextAlignmentLeft;
        [self addSubview:_leaveFactoryPricePre];
    }
    return _leaveFactoryPricePre;
}

-(UILabel*)leaveFactoryPrice
{
    if (!_leaveFactoryPrice) {
        _leaveFactoryPrice = [[UILabel alloc] init];
        NSString *leaveFactoryPricePreString = @"出厂价:";
        CGSize labelSize = [leaveFactoryPricePreString sizeWithFont:[UIFont systemFontOfSize:12.0f]];
        _leaveFactoryPrice.frame = CGRectMake(10+labelSize.width,170,147-labelSize.width-10,20);
        _leaveFactoryPrice.textColor = RGB(0xcc, 0x00, 0x00);
        _leaveFactoryPrice.numberOfLines = 1;
        _leaveFactoryPrice.font=[UIFont  fontWithName:@"Helvetica-Bold"  size:12];
        _leaveFactoryPrice.textAlignment = UITextAlignmentLeft;
        [self addSubview:_leaveFactoryPrice];
    }
    return _leaveFactoryPrice;
}

-(UILabel*)unit
{
    if (!_unit) {
        _unit = [[UILabel alloc] init];
        _unit.frame = CGRectMake(5,170,10,20);
        _unit.textColor = RGB(0x66,0x66,0x66) ;
        _unit.numberOfLines = 1;
        _unit.font=[UIFont  fontWithName:@"Helvetica-Bold"  size:12];
        _unit.textAlignment = UITextAlignmentLeft;
        [self addSubview:_unit];
    }
    return _unit;
}

-(UILabel*)loadingTextNotify
{
    if (!_loadingTextNotify) {
        _loadingTextNotify = [[UILabel alloc] init];
        NSString *loadText = @"图片加载中...:";
        CGSize labelSize = [loadText sizeWithFont:[UIFont systemFontOfSize:15.0f]];
        _loadingTextNotify.frame = CGRectMake(25,70,labelSize.width,labelSize.height);
        _loadingTextNotify.textColor = RGB(0x99,0x99,0x99) ;
        _loadingTextNotify.numberOfLines = 1;
        _loadingTextNotify.text = @"图片加载中...";
        _loadingTextNotify.font=[UIFont  fontWithName:@"Helvetica-Bold"  size:15.0f];
        _loadingTextNotify.textAlignment = UITextAlignmentCenter;
    }
    return _loadingTextNotify;
}

-(void) initBackGround{
    
    UIImage *backImg=[UIImage imageNamed:@"activity_bg_01.png"];
    backImg=[backImg stretchableImageWithLeftCapWidth:backImg.size.width/2 topCapHeight:backImg.size.height/2];
    self.blockBackImg=[[UIImageView alloc]initWithImage:backImg];
    [_blockBackImg setFrame:CGRectMake(0, 0, 155, 196)];
    [self addSubview:_blockBackImg];

}
- (void)dealloc {
    [_leaveFactoryImage release];
    [_subject release];
    [_leaveFactoryImageFocusIcon release];
    [_leaveFactoryPrice release];
    [_leaveFactoryPricePre release];
    [_unit release];
    [_listImg release];
    [_blockBackImg release];
    [_loadingTextNotify release];
    [super dealloc];
}
@end
