//
//  AMSearchResultData.h
//  AlibabaMobile
//
//  Created by zzh on 12-2-17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AMSearchResultData : NSObject

@property (readonly,nonatomic) NSMutableArray*resultData;
-(void)saveData:(NSString*)data;
@end
