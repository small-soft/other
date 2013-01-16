//
//  GHTestCaseExample.m
//  GHUnitProject
//
//  Created by mardin partytime on 12-8-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "GHTestCaseExample.h"

#import "GHUnitViewController.h"

#import "NSString+StringUtil.h"

#import "NSObject+CategoryThing.h"

#import "Car.h"

#import "Slant6.h"

#import "AllWeatherRadial.h"

#import "Thingie.h"

@implementation GHTestCaseExample

-(void)testString {
    NSString *string1 = @"a string";
    
    GHTestLog(@"I can log to the GHUnit test console: %@", string1);
    
    // Assert string1 is not NULL, with no custom error description
    
    GHAssertNotNULL(string1, nil);
    
    // Assert equal objects, add custom error description
    
    NSString *string2 = @"a string";
    
    GHAssertEqualObjects(string1, string2, @"A custom error message. string1 should be equal to: %@.", string2);
}

- (void) testAddOne {
    GHUnitViewController *vc = [[[GHUnitViewController alloc] initWithNibName:@"GHUnitViewController" bundle:nil] autorelease];
    
    GHTestLog(@"number init value is : %@", vc.number.text);
    GHAssertEqualObjects(vc.number.text, @"0", @"init number label's value is : %@.",vc.number.text);
    
//    NSArray *add1btn = [[NSBundle mainBundle] loadNibNamed:@"add1btn" owner:vc options:nil];
//    [vc addOne:[add1btn objectAtIndex:0]];
}

- (void) testCategoryString {
    GHAssertEquals([@"abcde" lengthAsNumber], [NSNumber numberWithUnsignedInt:5], @"equals?");
}

- (void) testCategoryThing {
    CategoryThing *thing = [[[CategoryThing alloc ]init]autorelease];
    
    [thing setThing1:5];
    [thing setThing2:6];
    [thing setThing3:7];
    
    GHTestLog(@"category thing description: %@", thing);

    GHAssertEqualObjects(@"thing1:5,thing2:6,thing3:7", thing.debugDescription, @"equals?");
}

- (void) testSelector {
    CategoryThing *thing = [[[CategoryThing alloc ]init]autorelease];
//    NSString *method = @"";
    
    [thing setThing1:5];
    [thing setThing2:6];
    [thing setThing3:7];
    
    SEL sel = @selector(testCategoryString);
    NSLog(@"sel is : %@",NSStringFromSelector(sel));
    
    
    GHAssertEqualObjects([thing respondsToSelector:@selector(setThing1:)], YES, @"can this obj response to this msg?");
    GHAssertEqualObjects([thing respondsToSelector:@selector(member:)], NO, @"can this obj response to this msg?");
}


- (void) testCarCopy {
    Car *car = [[[Car alloc]init]autorelease];
    
    car.engine = [[[Slant6 alloc]init]autorelease];
    
    for (int i = 0; i<4; i++) {
        [car.tires replaceObjectAtIndex:i withObject:[[[AllWeatherRadial alloc]init]autorelease]];
    }
    
    NSLog(@"new car:%@",car);
    
    Car *carCopy = [[car copy]autorelease];
    NSLog(@"copy car:%@",carCopy);
}

- (void) testReadAndWriteFile {
    NSArray *phrase = [NSArray arrayWithObjects:@"i",@"seem",@"to",@"be",@"a",@"good",@"person",@"?",nil];
    
    [phrase writeToFile:@"/tmp/verbiage.txt" atomically:YES];
    
    NSArray *phrase2 = [NSArray arrayWithContentsOfFile:@"/tmp/verbiage.txt"];
    NSLog(@"%@",phrase2);
    
    GHAssertEqualObjects(phrase, phrase2, @"two array equals?");
}

- (void) testCoder {
    Thingie *t = [[Thingie alloc]initwithName:@"test" magicNumber:1 shoeSize:1.2];
    Thingie *sub1 = [[[Thingie alloc]initwithName:@"test1" magicNumber:2 shoeSize:2.2]autorelease];
    Thingie *sub2 = [[[Thingie alloc]initwithName:@"test2" magicNumber:3 shoeSize:3.2]autorelease];
    Thingie *sub3 = [[[Thingie alloc]initwithName:@"test3" magicNumber:4 shoeSize:4.2]autorelease]; 
    
    t.subThingies = [[[NSMutableArray alloc]init]autorelease];
    [t.subThingies addObject:sub1];
    [t.subThingies addObject:sub2];
    [t.subThingies addObject:sub3];
    NSLog(@"t is %@",t);
    
    NSData *freezeDried = [NSKeyedArchiver archivedDataWithRootObject:t];
    NSLog(@"freezeDried:%@",freezeDried);
    
    [freezeDried writeToFile:@"/tmp/freezeDried.txt" atomically:YES];
    
    NSData *unFreezeDried = [NSData dataWithContentsOfFile:@"/tmp/freezeDried.txt"];
    Thingie *t2 = [NSKeyedUnarchiver unarchiveObjectWithData:unFreezeDried];
    NSLog(@"t2 is %@",t2);
    
    GHAssertEqualObjects(t.description, t2.description, @"two thingie equals?");
}

- (void) testKVC {
    Car *car = [[[Car alloc]init]autorelease]; 
    [car setValue:[[[Slant6 alloc]init]autorelease] forKey:@"engine"];
    for (int i = 0; i<4; i++) {
        [car.tires replaceObjectAtIndex:i withObject:[[[AllWeatherRadial alloc]init]autorelease]];
    }
    
    NSLog(@"user kvc to dis car engine : %@",[car valueForKey:@"engine"]);
    NSLog(@"user kvc to dis car tires : %@",[car valueForKey:@"tires"]);
}

- (void) testPath {
    Car *car = [[[Car alloc]init]autorelease]; 
    
    [car setValue:[NSNumber numberWithInt:123] forKeyPath:@"engine.horsePower"];
    
    GHAssertEqualObjects([NSNumber numberWithInt:123], [car valueForKeyPath:@"engine.horsePower"], @"two int equals?");
    
    GHAssertEqualObjects([NSNumber numberWithInt:4], [car valueForKeyPath:@"tires.@count"], @"two int equals?");
}

- (void) testKVCCompute {
    Car *car = [[[Car alloc]init]autorelease]; 
    for (int i = 0; i<4; i++) {
        [car.tires replaceObjectAtIndex:i withObject:[[[AllWeatherRadial alloc]initWithPressure:i*123. treadDepth:i + 456.]autorelease]];
        
    }
    
    GHAssertEqualObjects([NSNumber numberWithInt:4], [car valueForKeyPath:@"tires.@count"], @"two int equals?");
    
    NSLog(@"sum of pressure is %@:",[car valueForKeyPath:@"tires.@sum.pressure"]);
    NSLog(@"avg of pressure is %@:",[car valueForKeyPath:@"tires.@avg.pressure"]);
    
    GHAssertEqualObjects([NSNumber numberWithInt:738], [car valueForKeyPath:@"tires.@sum.pressure"], @"two int equals?");
    
    GHAssertEqualObjects([NSNumber numberWithFloat:184.5], [car valueForKeyPath:@"tires.@avg.pressure"], @"two float equals?");
}

- (void) testPredicate {
    Car *car = [[[Car alloc]init]autorelease];
    car.engine.horsePower = 152;
    
    NSPredicate *pre = [NSPredicate predicateWithFormat:@"engine.horsePower > 150"];
    
    GHAssertTrue([pre evaluateWithObject:car],@"is true?");
    
}

- (void) testPredicateFilter {
    NSMutableArray *cars = [NSMutableArray arrayWithCapacity:10];
    
    for (int i = 0; i<10; i++) {
        Car *car = [[[Car alloc]init]autorelease];
        car.engine.horsePower = i;
        
        [cars addObject:car];
    }
    
    NSPredicate *pre = [NSPredicate predicateWithFormat:@"engine.horsePower > 5"];
    
    NSArray *carsWithBigHorsePower = [cars filteredArrayUsingPredicate:pre];
    GHAssertTrue(4 == [carsWithBigHorsePower count], @"two int equals?");
    
    NSPredicate *pre2 = [NSPredicate predicateWithFormat:@"(engine.horsePower > 5) AND (engine.horsePower < 9)"];
    
    NSArray *carsWithBigHorsePower2 = [cars filteredArrayUsingPredicate:pre2];
    GHAssertTrue(3 == [carsWithBigHorsePower2 count], @"two int equals?");
    
    NSPredicate *pre3 = [NSPredicate predicateWithFormat:@"engine.horsePower BETWEEN {5 , 9}"];
    
    NSArray *carsWithBigHorsePower3 = [cars filteredArrayUsingPredicate:pre3];
    
    GHAssertTrue(5 == [carsWithBigHorsePower3 count], @"two int equals?");

}

- (void) testSearchDocument {
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *path = [paths objectAtIndex:0];
    GHTestLog(@"doucment path: %@", path);
    
    NSString *filename = [path stringByAppendingPathComponent:@"test.txt"];
    GHTestLog(@"test.txt total filename is: %@", filename);
    
    // 字符编码的使用
    NSStringEncoding encode = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000);
    NSString *content = [NSString stringWithContentsOfFile:filename usedEncoding:&encode error:nil];
    GHTestLog(@"test.txt content: %@", content);
}

- (void) testTempDir {
    NSString *tempPath = NSTemporaryDirectory();
    GHTestLog(@"temp path : %@",tempPath);
    
    NSString *filename = [tempPath stringByAppendingPathComponent:@"test.txt"];
    GHTestLog(@"test.txt total filename is: %@", filename);
    
    // 字符编码的使用
    NSStringEncoding encode = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000);
    NSString *content = [NSString stringWithContentsOfFile:filename usedEncoding:&encode error:nil];
    GHTestLog(@"test.txt content: %@", content);
}
@end
