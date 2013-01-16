//
//  AMBrandsCategoryRequest.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-8-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMBrandsRequest.h"


@implementation AMBrandsRequest

@synthesize catId=_catId;

- (void) dealloc {
    

    //[_catId release];
    
    [super dealloc];
}


- (NSString*)HTTPHeaderValueForContentType {
    return @"application/x-www-form-urlencoded";
}


- (NSData*)HTTPBody { 
    

    
    NSString *bodyString =  [@"_data_=" stringByAppendingFormat:@"{catId:\"%d\"}",self.catId];
    

    NSLog(@"http body:%@",bodyString);
    
    return [bodyString dataUsingEncoding: NSUTF8StringEncoding];
    
}




@end
