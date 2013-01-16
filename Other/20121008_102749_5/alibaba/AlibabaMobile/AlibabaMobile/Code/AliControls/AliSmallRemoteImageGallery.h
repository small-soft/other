//
//  AliOfferDetailGallery.h
//  AlibabaMobile
//
//  Created by xiejin on 12-2-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>
#import "HJObjManager.h"

@protocol AliGalleryDelegate <NSObject>

- (void) galleryClickAction;

@end

@interface AliSmallRemoteImageGallery : UIView<UIScrollViewDelegate>

@property (nonatomic, retain) id<AliGalleryDelegate> delegate;

- (void) setImageUrls:(NSMutableArray *) array;

@end
