#import "AMNewsItemImageOffer.h"
#import <RestKit/RestKit.h>

/**
 * 
 */

@implementation AMNewsItemImageOffer

@synthesize gmtModified = _gmtModified;
@synthesize keywords = _keywords;
@synthesize tags = _tags;
@synthesize gmtCreate = _gmtCreate;
@synthesize pageMd5 = _pageMd5;
@synthesize priceUnit = _priceUnit;
@synthesize identifier = _identifier;
@synthesize title = _title;
@synthesize newsId = _newsId;
@synthesize price = _price;
@synthesize offerId = _offerId;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMNewsItemImageOffer class]] retain];
            [sharedObjectMapping mapKeyPath:@"gmtModified" toAttribute:@"gmtModified"];
            [sharedObjectMapping mapKeyPath:@"keywords" toAttribute:@"keywords"];
            [sharedObjectMapping mapKeyPath:@"tags" toAttribute:@"tags"];
            [sharedObjectMapping mapKeyPath:@"gmtCreate" toAttribute:@"gmtCreate"];
            [sharedObjectMapping mapKeyPath:@"pageMd5" toAttribute:@"pageMd5"];
            [sharedObjectMapping mapKeyPath:@"priceUnit" toAttribute:@"priceUnit"];
            [sharedObjectMapping mapKeyPath:@"id" toAttribute:@"identifier"];
            [sharedObjectMapping mapKeyPath:@"title" toAttribute:@"title"];
            [sharedObjectMapping mapKeyPath:@"newsId" toAttribute:@"newsId"];
            [sharedObjectMapping mapKeyPath:@"price" toAttribute:@"price"];
            [sharedObjectMapping mapKeyPath:@"offerId" toAttribute:@"offerId"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_tags release];
  [_pageMd5 release];
  [_priceUnit release];
  [_gmtModified release];
  [_keywords release];
  [_gmtCreate release];
  [_identifier release];
  [_title release];
  [_newsId release];
  [_offerId release];
  [_price release];
  
  [super dealloc];
}

@end
