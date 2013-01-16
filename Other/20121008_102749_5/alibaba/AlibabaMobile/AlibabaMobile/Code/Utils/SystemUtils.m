//
//  SystemUtils.m
//  AlibabaMobile
//
//  Created by mardin partytime on 2/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "SystemUtils.h"

@implementation SystemUtils

+ (void) makeCallWithNumber:(NSString *) phoneNumber
{    
#warning 修改人孟希羲
    NSURL *phoneURL = [NSURL URLWithString:[NSString stringWithFormat:@"tel://%@",phoneNumber]];    
    UIWebView *phoneCallWebView = [[UIWebView alloc] initWithFrame:CGRectZero];
    [phoneCallWebView loadRequest:[NSURLRequest requestWithURL:phoneURL]];
}

//+ (void) makeCallWithNumber2:(NSString *)phoneNumber
//{
//    NSString *num = [[NSString alloc] initWithFormat:@"tel://%@",phoneNumber]; //number为号码字符串    
//    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:num]]; //拨号 
//}

//通过系统浏览器打开url
+ (void) openBrowserWithUrl:(NSString *) url
{
     [[UIApplication sharedApplication] openURL:[NSURL URLWithString:url]]; 
}

+ (NSString *) getAppFilePath:(NSString *) fileName
{
    NSString *mainBundleDirectory = [[NSBundle mainBundle] bundlePath];
    NSString *path = [mainBundleDirectory  stringByAppendingPathComponent:fileName];
    return path;
}

@end
