//
//  TestSample.m
//  oct
//
//  Created by mardin partytime on 12-8-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "TestSample.h"

@implementation TestSample

//STAssertNotNil(a1, descrīption, ...)
//STAssertTrue(expression, descrīption, ...)
//STAssertFalse(expression, descrīption, ...)
//STAssertEqualObjects(a1, a2, descrīption, ...)
//STAssertEquals(a1, a2, descrīption, ...)
//STAssertThrows(expression, descrīption, ...)
//STAssertNoThrow(expression, descrīption, ...)
//STFail(descrīption, ...)

- (void) testComapre {
    NSString *s1 = @"abcd";
    NSString *s2 = @"abcd";
    
    STAssertEquals(s1, s2,@"%d = %d ?",s1,s2);
}



@end
