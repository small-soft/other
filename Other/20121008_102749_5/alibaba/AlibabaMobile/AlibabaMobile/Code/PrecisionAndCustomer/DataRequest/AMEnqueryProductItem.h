//
//  EnqueryProductItem.h
//  AlibabaMobile
//
//  Created by alimobile on 12-6-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "AMObjectMappingDelegate.h"

@interface AMEnqueryProductItem : NSObject<AMObjectMappingDelegate>
{
    NSString * _itemId;
    NSString * _productName;
    NSNumber * _price;
    NSNumber * _quantity;
    
}


@property(nonatomic, retain) NSString* itemId;
@property(nonatomic, retain) NSString* productName;
@property(nonatomic, retain) NSNumber* price;
@property(nonatomic, retain) NSNumber* quantity;



@end
