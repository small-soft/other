//
//  UIHelp.m
//  AlibabaMobile
//
//  Created by mardin partytime on 2/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "UIHelp.h"
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "AliToastView.h"

@implementation UIHelp


+ (UIColor *) colorWithHexString: (const NSString *) stringToConvert
{
    return [UIHelp colorWithHexString:stringToConvert andAlpha:1.0f];
}

+ (UIColor *) colorWithHexString: (const NSString *) stringToConvert andAlpha:(float)alpha
{
    NSString *cString = [[stringToConvert stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]] uppercaseString];
    
    // String should be 6 or 8 characters
    if ([cString length] < 6) 
        return [UIColor clearColor];
    
    // strip 0X if it appears
    if ([cString hasPrefix:@"0X"]) 
        cString = [cString substringFromIndex:2];
    
    if ([cString hasPrefix:@"#"]) 
        cString = [cString substringFromIndex:1];
    
    if ([cString length] != 6) 
        return [UIColor clearColor];
    
    // Separate into r, g, b substrings
    NSRange range;
    range.location = 0;
    range.length = 2;
    NSString *rString = [cString substringWithRange:range];
    
    range.location = 2;
    NSString *gString = [cString substringWithRange:range];
    
    range.location = 4;
    NSString *bString = [cString substringWithRange:range];
    
    // Scan values
    unsigned int r, g, b;
    [[NSScanner scannerWithString:rString] scanHexInt:&r];
    [[NSScanner scannerWithString:gString] scanHexInt:&g];
    [[NSScanner scannerWithString:bString] scanHexInt:&b];
    
    return [UIColor colorWithRed:((float) r / 255.0f)
                           green:((float) g / 255.0f)
                            blue:((float) b / 255.0f)
                           alpha:alpha];
}

+ (UIImageView *) generateImageView:(UIImage *) image size:(CGSize)size
{
    UIImageView *imageView = [[[UIImageView alloc]initWithFrame:CGRectMake(0, 0, size.width, size.height)] autorelease];
    imageView.contentMode = UIViewContentModeScaleAspectFill;
    [imageView setImage:image];
    
    return imageView;
}

+ (void) showAlertDialogWithTitle:(NSString *)title andMsg:(NSString *)msg
{
    UIAlertView* alert = [[[UIAlertView alloc] initWithTitle:title message:msg delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil] autorelease];
	[alert show];

}
+ (void) showAlertDialogWithTitle:(NSString *)title andMsg:(NSString *)msg delegate:(id)delegate
{
    UIAlertView* alert = [[[UIAlertView alloc] initWithTitle:title message:msg delegate:delegate cancelButtonTitle:@"确定" otherButtonTitles:nil] autorelease];
	[alert show];
    
}
+ (CGSize) getLabelSizeWithFont:(UIFont *)font labelString:(NSString *)str labelHeight:(float)height
{
    return [str sizeWithFont:font constrainedToSize:CGSizeMake(MAXFLOAT, height)];
}

+(CGSize) getLabelSizeWithFont:(UIFont *)font labelString:(NSString *)str labelWidth:(float)width
{
    return [str sizeWithFont:font constrainedToSize:CGSizeMake(width, MAXFLOAT) lineBreakMode:UILineBreakModeWordWrap];
}
+ (CGPoint) getLabelTailWithFont:(UIFont *)font labelString:(NSString *)str labelWidth:(float)width lineHeight:(float)height labelOrigin:(CGPoint)origin
{
    CGSize sz = [str sizeWithFont:font constrainedToSize:CGSizeMake(MAXFLOAT, height)];
    CGSize linesSz = [str sizeWithFont:font constrainedToSize:CGSizeMake(width, MAXFLOAT) lineBreakMode:UILineBreakModeWordWrap];
    if(sz.width <= linesSz.width) //判断是否折行
    {
        return CGPointMake(origin.x + sz.width, origin.y);  
    }
    else  
    {  
        return CGPointMake(origin.x + (int)sz.width % (int)linesSz.width,linesSz.height - sz.height);  
    } 
}


@end
