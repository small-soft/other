//
//  AMCorporation.h
//  AlibabaMobile
//
//  Created by  on 12-1-4.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"

@interface AMCorporation : NSObject <AMObjectMappingDelegate> {
    NSString *_name;
    NSString *_code;
    NSString *_pinyin;
}

@property(nonatomic, retain) NSString * name;
@property(nonatomic, retain) NSString * code;
@property(nonatomic, retain) NSString * pinyin;

@end
