//
//  AMBrandsCategoryRequest.m
//  AlibabaMobile
//
//  Created by alimobile on 12-8-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMBrandsCategoryRequest.h"


@implementation AMBrandsCategoryRequest


- (void) dealloc {
    

    
    [super dealloc];
}


- (NSString*)HTTPHeaderValueForContentType {
    return @"application/x-www-form-urlencoded";
}


- (NSData*)HTTPBody { 
    
//    NSString *signedBodyString = nil;
    
    NSString *bodyString = @"_data_={}";
    
//    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
//    [params setObject: _data_ forKey: @"_data_"];
//    signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_CUSTOMER_USERINFO params:params];
//    NSLog(@"REQUEST:%@",signedBodyString );
//    [params release];	
    
    return [bodyString dataUsingEncoding: NSUTF8StringEncoding];
    
}




@end
