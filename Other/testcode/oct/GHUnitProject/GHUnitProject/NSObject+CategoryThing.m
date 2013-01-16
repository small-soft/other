//
//  NSObject+CategoryThing.m
//  GHUnitProject
//
//  Created by mardin partytime on 12-8-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "NSObject+CategoryThing.h"
//#import "CategoryThing+Thing1.m"
//#import "CategoryThing+Thing2.m"
//#import "CategoryThing+Thing3.m"

@implementation CategoryThing 
- (NSString *)description {
    return ([NSString stringWithFormat:@"thing1:%d,thing2:%d,thing3:%d",thing1,thing2,thing3]);
}

@end


