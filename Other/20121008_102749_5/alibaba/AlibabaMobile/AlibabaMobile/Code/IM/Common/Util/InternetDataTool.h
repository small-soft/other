//
//  InternetDataTool.h
//  WangWang
//
//  Created by littlejie chan on 10-5-31.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FaceItemView.h"
#import "TextViewExItem.h"

@interface InternetDataTool : NSObject {
	NSOperationQueue *operationQueue;
	NSMutableArray *facesCharArray;
}

@property(nonatomic, readonly) NSOperationQueue *operationQueue;
@property(nonatomic, retain) NSMutableArray *facesCharArray;

/*!
 @method		create:
 @abstract		静态创建对象方法
 @discussion	此工具类为单实例类，请勿使用init直接进行初始化
 @result		InternetDataTool对象
 */
+ (InternetDataTool *)create;

/*!
 @method		destoryObject:
 @abstract		静态注销对象方法
 @discussion	
 @result		InternetDataTool对象
 */
+ (void)destoryObject;

@end
