//
//  Thingie.h
//  GHUnitProject
//
//  Created by 佳 刘 on 12-9-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Thingie : NSObject <NSCoding>

@property (copy) NSString *name;
@property int magicNumber;
@property float shoeSize;
@property (retain) NSMutableArray *subThingies;

- (id) initwithName: (NSString *) n
        magicNumber: (int) mc
           shoeSize: (float) ss;

@end
