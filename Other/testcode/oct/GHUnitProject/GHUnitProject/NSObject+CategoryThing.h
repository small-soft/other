//
//  NSObject+CategoryThing.h
//  GHUnitProject
//
//  Created by mardin partytime on 12-8-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CategoryThing :NSObject{
    int thing1;
    int thing2;
    int thing3;
}

@end

@interface CategoryThing (Thing1)

- (void) setThing1: (int) things;
- (int) thing1;

@end

@interface CategoryThing (Thing2)

- (void) setThing2: (int) things;
- (int) thing2;

@end

@interface CategoryThing (Thing3)

- (void) setThing3: (int) things;
- (int) thing3;

@end