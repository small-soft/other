//
//  AMCategorySub.h
//  AlibabaMobile
//
//  Created by zzh on 12-1-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"

@interface AMCategorySub : NSObject <AMObjectMappingDelegate> {
    NSString* _identifier;

    NSString * _name;
    BOOL _leaf;
 
}


/**
 * ¿‡ƒø±‡∫≈
 */
@property(nonatomic, retain) NSString * identifier;


/**
 * ¿‡ƒø√˚≥∆
 */
@property(nonatomic, retain) NSString * name;

/**
 *  «∑Ò“∂◊”¿‡ƒø
 */
@property(nonatomic) BOOL leaf;




@end
