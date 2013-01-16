//
//  UIHelp.h
//  AlibabaMobile
//
//  Created by xiejin on 2/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface UIHelp : NSObject

+ (UIColor *) colorWithHexString: (const NSString *) stringToConvert andAlpha:(float)alpha;


/*
 *xiejin
 *根据颜色值获取颜色
 */
+ (UIColor *) colorWithHexString: (const NSString *) stringToConvert;

/*
 *xiejin
 *获取图片控件，制定大小和图片源
 */
+ (UIImageView *) generateImageView:(NSString *) imgName size:(CGSize)size;

/*
 *xiejin
 *显示提示框
 */
+ (void) showAlertDialogWithTitle:(NSString *)title andMsg:(NSString *)msg; 

/*
 *xiejin
 *显示提示框,带delegate
 */
+ (void) showAlertDialogWithTitle:(NSString *)title andMsg:(NSString *)msg delegate:(id)delegate;

/*
 *xiejin
 *获取UILabel中字符串不换行时，UILabel大小
 */
+ (CGSize) getLabelSizeWithFont:(UIFont *)font labelString:(NSString *)str labelHeight:(float)height;

/*
 *xiejin
 *获取UILabel的大小，制定宽度，超过宽度则换行
 */
+(CGSize) getLabelSizeWithFont:(UIFont *)font labelString:(NSString *)str labelWidth:(float)width;

/*
 *xiejin
 *计算UILabel，固定宽度，自动换行的情况下，文字末尾的位置
 */
+ (CGPoint) getLabelTailWithFont:(UIFont *)font labelString:(NSString *)str labelWidth:(float)width lineHeight:(float)height labelOrigin:(CGPoint)origin;
@end
