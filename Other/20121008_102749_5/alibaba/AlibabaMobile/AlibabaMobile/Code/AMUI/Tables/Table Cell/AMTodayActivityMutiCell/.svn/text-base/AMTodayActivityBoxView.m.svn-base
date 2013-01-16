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


-(void)awakeFromNib
{
    [super awakeFromNib];
    [self addSubview:self.leaveFactoryImageFocusIcon];
    [self addSubview:self.leaveFactoryImage];
    [self addSubview:self.leaveFactoryPricePre];
    [self addSubview:self.leaveFactoryPrice];
    [self addSubview:self.unit];


}
-(UIImageView*)leaveFactoryImage
{
    if (!_leaveFactoryImage) {
        _leaveFactoryImage = [[UIImageView alloc] init];
        _leaveFactoryImage.frame = CGRectMake(0,10,130,130);
    }
    return _leaveFactoryImage;
}

-(UIImageView*)leaveFactoryImageFocusIcon
{
    if (!_leaveFactoryImageFocusIcon) {
        _leaveFactoryImageFocusIcon = [[UIImageView alloc] init];
        _leaveFactoryImageFocusIcon.frame = CGRectMake(0,10,130,130);
        _leaveFactoryImageFocusIcon.backgroundColor = [UIColor clearColor];
     
    }
    return _leaveFactoryImageFocusIcon;
}

-(UILabel*)subject
{
    if (!_subject) {
        _subject = [[UILabel alloc] init];
        _subject.frame = CGRectMake(0,140,130,30);
        _subject.textColor = RGB(0x66,0x66,0x66) ;
        _subject.numberOfLines = 2;
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
        CGSize labelSize = [leaveFactoryPricePreString sizeWithFont:[UIFont systemFontOfSize:14.0f]];
        _leaveFactoryPricePre.frame = CGRectMake(0,170,labelSize.width,20);
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
        CGSize labelSize = [leaveFactoryPricePreString sizeWithFont:[UIFont systemFontOfSize:14.0f]];
        _leaveFactoryPrice.frame = CGRectMake(labelSize.width,170,130,20);
//        _leaveFactoryPrice.textColor = RGB(0x66,0x66,0x66) ;
        _leaveFactoryPrice.textColor = [UIColor redColor];
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
        _unit.frame = CGRectMake(0,170,130,20);
        _unit.textColor = RGB(0x66,0x66,0x66) ;
        _unit.numberOfLines = 1;
        _unit.font=[UIFont  fontWithName:@"Helvetica-Bold"  size:12];
        _unit.textAlignment = UITextAlignmentLeft;
        [self addSubview:_unit];
    }
    return _unit;
}


//- (void) setLeaveFactoryAndUnitProperty:(NSString *)countValue unit:(NSString *)unitValue cell:(AMActivityDetailCell *) cellValue{
//    
//    
//    CGSize labelSize = [countValue sizeWithFont:[UIFont systemFontOfSize:14.0f]];
//    cellValue.leaveFactoryPriceAmountLabel.text = countValue;
//    
//    CGSize labelSizeEnd = [unitValue sizeWithFont:[UIFont systemFontOfSize:14.0f]];
//    
//    cellValue.unitLabel.frame = CGRectMake(62+labelSize.width, 235, labelSizeEnd.width, labelSizeEnd.height);
//    cellValue.unitLabel.text = unitValue;
//    
//    
//}

- (void)dealloc {
    [_leaveFactoryImage release];
    [_subject release];
    [_leaveFactoryImageFocusIcon release];
    [_leaveFactoryPrice release];
    [_leaveFactoryPricePre release];
    [_unit release];
    [super dealloc];
}
@end
