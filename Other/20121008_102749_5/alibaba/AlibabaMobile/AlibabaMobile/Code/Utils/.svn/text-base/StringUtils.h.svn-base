//
//  StringUtils.h
//  AlibabaMobile
//
//  Created by mardin partytime on 2/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
//  create by Xiejin
//  tools of strings
//
//

#import <Foundation/Foundation.h>

@class AMAddress;

@interface StringUtils : NSObject

+ (NSString *) returnRevMessageString:(NSString *)_string ;

/*
 *xiejin
 *根据uid获取旺旺中文站头像的图片url
 */
+ (NSURL *) getWwHeadImageWithUid:(NSString *)uid;

/*
 *xiejin
 *获取日期的字符串表示，yyyy年mm月dd日
 */
+(NSString *) getDateStrShort:(double)timeStr;

/*
 *xiejin
 *获取日期的字符串表示，yyyy年mm月dd日 hh:mm:ss
 */
+(NSString *) getDateStrLong:(double)timeStr;

/*
 *xiejin
 *根据制定字体获取文本字符串的size
 */
+ (CGSize) getStringSize:(const NSString *)text font:(UIFont *)font;


/*
 *xiein
 *获取非空字符串，如果为nil，返回空字符串
 */
+ (NSString *) getNoNilString:(NSString *) str;

/*
 *xiejin
 *获取字符串数组的字符串序列
 */
+ (NSString *) getStringArrayString:(NSArray *)stringArray;

/*
 *xiejin
 *获取AMAddress的字符串表示
 */
+ (NSString *) getAddressString:(AMAddress *)address;

/*
 *xiejin
 *获取son字符串在father字符串中的其事位置
 */
+ (int) getIndexOf:(NSString *)sonStr inFather:(NSString *)fatherStr;

/*
 *xiejin
 *构造title字符串，去除html标签，空格，限定长度
 *
 */
+(NSString *) makeTitleFromString:(NSString *)srcStr ofLength:(int)length;

/*
 *
 *xiejin
 *去除字符串中的html tag和空格
 */
+(NSString *) removeHtmlLabelsAndBlanksFromString:(NSString *) srcStr;

/*
 *xiejin
 *获取制定长度的字符串子串
 */
+(NSString *) getSubStringFromString:(NSString *)srcStr ofLength:(int) length;

@end
