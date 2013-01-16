//
//  StringTest.m
//  oct
//
//  Created by mardin partytime on 12-8-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "StringTest.h"

@implementation StringTest {
    NSString *_strLen4;
    NSString *_strLen8;
}

+ (void) stringCompare {
    NSString *str1 = @"1234";
    NSString *str2 = @"1234";
    
    if (str1 == str2) {
        NSLog(@"%@ = %@",str1,str2);
    }
}

@end
