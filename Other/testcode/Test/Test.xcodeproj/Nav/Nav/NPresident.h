//
//  NPresident.h
//  Nav
//
//  Created by 佳 刘 on 12-9-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#define kPresidentNumberKey @"President"
#define kPresidentNameKey @"Name"
#define kPresidentFromKey @"FromYear"
#define kPresidentToKey @"ToYear"
#define kPresidentPartyKey @"Party"

@interface President : NSObject<NSCoding>

@property int number;
@property (nonatomic,retain) NSString *name;
@property (nonatomic,retain) NSString *fromYear;
@property (nonatomic,retain) NSString *toYear;
@property (nonatomic,retain) NSString *party;

@end
