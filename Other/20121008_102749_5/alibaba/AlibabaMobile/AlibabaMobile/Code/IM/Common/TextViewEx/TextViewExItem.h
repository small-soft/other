//
//  TextViewExItem.h
//  WangWang
//
//  Created by JerryChan on 10-6-30.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface TextViewExItem : NSObject {
	NSString *imagePath,*iconPath;
	NSRange range;
}

@property (nonatomic,retain) NSString *imagePath,*iconPath;
@property (nonatomic) NSRange range;

- (id) init:(NSString *)_imagePath range:(NSRange)_range;

@end
