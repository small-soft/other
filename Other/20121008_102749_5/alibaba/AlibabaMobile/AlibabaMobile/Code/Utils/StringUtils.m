//
//  StringUtils.m
//  AlibabaMobile
//
//  Created by mardin partytime on 2/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "StringUtils.h"
#import <Foundation/Foundation.h>
#import "AMAddress.h"
#import "InternetDataTool.h"
#define	BREAKSTRING				@"\\T"

@implementation StringUtils

+ (NSString *) returnRevMessageString:(NSString *)_string {
    NSArray *rAry = [NSArray arrayWithArray:[InternetDataTool create].facesCharArray];
    NSString *replaceStr;
    NSString *returnStr = _string;
    
    for (int i = 0; i < [rAry count]; i++) {
        
        TextViewExItem *dicItem = [rAry objectAtIndex:i];
        NSString *imageStr = dicItem.imagePath;
        
        replaceStr = [NSString stringWithFormat:@"%@%@%@",BREAKSTRING,imageStr,BREAKSTRING ];
        returnStr = [returnStr stringByReplacingOccurrencesOfString:imageStr withString:replaceStr];
        
    }
    
    return returnStr;
}

+ (NSURL *) getWwHeadImageWithUid:(NSString *)uid
{	
    //NSLog(@"ww head uid: %@", uid);
	NSURL *urlStr = nil;
    NSString * url;
	if (uid != nil && ![uid isEqualToString:@""]) {
        if ([[uid substringToIndex:8] isEqualToString:@"cntaobao"]) {
            url = [NSString stringWithFormat:@"http://jianghu.taobao.com/wangwang/headshow.htm?longId=%@", uid];
            urlStr = [NSURL URLWithString: url];
        } else if ([[uid substringToIndex:8] isEqualToString:@"cnalichn"] && uid.length >= 11) {
            NSString *shortUserId = [uid substringFromIndex:8];
            
            if (shortUserId.length <= 3) {
                url = [NSString stringWithFormat:@"http://img.china.alibaba.com/club/upload/pic/user/%@/%@/%@/%@.tom?random=1", [shortUserId substringToIndex:1], [shortUserId substringWithRange:NSMakeRange(1, 1)], [shortUserId substringWithRange:NSMakeRange(2, 1)], shortUserId];

            }else {
                url = [NSString stringWithFormat:@"http://img.china.alibaba.com/club/upload/pic/user/%@/%@/%@/%@/%@.tom?random=1", [shortUserId substringToIndex:1], [shortUserId substringWithRange:NSMakeRange(1, 1)], [shortUserId substringWithRange:NSMakeRange(2, 1)], [shortUserId substringWithRange:NSMakeRange(3, 1)], shortUserId];
            }
         
            urlStr = [NSURL URLWithString: url];
            
        } else if ([[uid substringToIndex:8] isEqualToString:@"enaliint"]) {
            url = [NSString stringWithFormat:@"http://atmgateway.client.alibaba.com/atmgateway/get_portrait.htm?memberId=%@", uid];
            urlStr = [NSURL URLWithString: url];
        }
		
	}
    //NSLog(@"ww head url: %@", urlStr);
    
    return urlStr;
}


+(NSString *) getDateStrLong:(double)timeStr
{

    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
    NSTimeInterval interval = timeStr;    
    NSDate *date = [NSDate dateWithTimeIntervalSince1970:interval];
    NSString * str = [dateFormatter stringFromDate:date];
    [dateFormatter release];

    
    return str;
}

+(NSString *) getDateStrShort:(double)timeStr
{
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyy年MM月dd日"];
    NSTimeInterval interval = timeStr;    
    NSDate *date = [NSDate dateWithTimeIntervalSince1970:interval];
    NSString * str = [dateFormatter stringFromDate:date];
    [dateFormatter release];

    
    return str;
}

+ (CGSize) getStringSize:(NSString *)text font:(UIFont *)font
{
    return  [text sizeWithFont: font
                         constrainedToSize:CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX)
                             lineBreakMode:UILineBreakModeWordWrap];
}

+ (NSString *) getStringArrayString:(NSArray *)stringArray
{
    if(stringArray != nil && stringArray.count > 0)
    {
        NSString * result = @"";
        int size = stringArray.count;
        for(int i=0; i<size;i++){
            NSString *string = [stringArray objectAtIndex:i];
            if(string != nil)
                result  = [result stringByAppendingString:string];
            
            if(i <size-1)
                result = [result stringByAppendingString:@","];
        }
        
        return result;
    }else{
        return @"";
    }
}

+ (NSString *) getNoNilString:(NSString *) str
{
    return str != nil? str:@"";
}

+ (NSString *) getAddressString:(AMAddress *)address
{
    if(address != nil){
        NSString * provinceName = [StringUtils getNoNilString:[address provinceName]];
        NSString * areaName = [StringUtils getNoNilString:[address areaName]];
        NSString * streetName = [StringUtils getNoNilString:[address streetAddress]];
        
        if([StringUtils getIndexOf:provinceName inFather:areaName] >=0){
            return [areaName stringByAppendingString:streetName];
            
        }else{
            return [[provinceName stringByAppendingString:areaName] stringByAppendingString:streetName];
        }
    }else{
        return nil;
    }
}

+ (int) getIndexOf:(NSString *)sonStr inFather:(NSString *)fatherStr
{
    if(fatherStr != nil 
       && sonStr != nil 
       && [fatherStr compare:@""] != NSOrderedSame 
       && [fatherStr length] > [sonStr length]){
        NSRange range = [fatherStr rangeOfString:sonStr];
        if(range.length>0){
            return range.location;
        }
    }
    
    return -1;
}

/*
 *xiejin
 *构造title字符串，去除html标签，空格，限定长度
 *
 */
+(NSString *) makeTitleFromString:(NSString *)srcStr ofLength:(int)length
{
    return[StringUtils getSubStringFromString:[StringUtils removeHtmlLabelsAndBlanksFromString:srcStr] ofLength:length];
}

/*
 *
 *xiejin
 *去除字符串中的html tag和空格
 */
+(NSString *) removeHtmlLabelsAndBlanksFromString:(NSString *) srcStr
{
    if(srcStr){
        NSMutableString *str = [[[NSMutableString alloc] initWithString:srcStr] autorelease];
        
        
        int tagLevel = 0;
        for(int i=0; i<str.length; i++){
            unichar c = [str characterAtIndex:i];
            if(c == ' '){
                [str deleteCharactersInRange:NSMakeRange(i, 1)];
                i--;
                continue;
            }
            
            if(tagLevel == 0){
                if(c == '<'){
                    tagLevel ++;
                    [str deleteCharactersInRange:NSMakeRange(i, 1)];
                    i--;
                }
            }else{
                if(c == '<'){
                    tagLevel ++;
                }else if(c == '>'){
                    tagLevel --;
                }
                
                [str deleteCharactersInRange:NSMakeRange(i, 1)];
                i--;
            }
        }
        
        return str;
    }
    return nil;
    
}

/*
 *
 *xiejin
 *获取制定长度的字符串子串
 */
+(NSString *) getSubStringFromString:(NSString *)srcStr ofLength:(int) length;
{
    if(srcStr){
        NSMutableString *str = [[[NSMutableString alloc] initWithString:srcStr] autorelease];
        int strLen = srcStr.length;
        
        if(strLen > length){
            [str deleteCharactersInRange:NSMakeRange(length, strLen-length)];
            [str insertString:@"..." atIndex:length];
        }
        
        return str;
    }
    return nil;
}

@end
