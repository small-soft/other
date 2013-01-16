//
//  SignatureDownloadOperation.h
//  WangWang
//
//  Created by Casten on 10-7-5.
//  Copyright 2010 Infothinker. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface SignatureDownloadOperation : NSOperation {
	NSString *uid;
    uint count;
}

///用uid进行初始化
- (id) initWithUID:(NSString *)_uid :(uint )_count;

@end
