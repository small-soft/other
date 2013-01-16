//
//  PFourLines.h
//  Persistence
//
//  Created by 佳 刘 on 12-9-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#define kField1Key @"Field1"
#define kField2Key @"Field2"
#define kField3Key @"Field3"
#define kField4Key @"Field4"

@interface PFourLines : NSObject <NSCoding,NSCopying>{
    
}

@property (nonatomic,retain) NSString *field1;
@property (nonatomic,retain) NSString *field2;
@property (nonatomic,retain) NSString *field3;
@property (nonatomic,retain) NSString *field4;

@end
