//
//  AMOfferDetailRequest.h
//  AlibabaMobile
//
//  Created by mardin partytime on 1/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_PRODUCT_DETAIL ([@"/offer.findOfferWithDescById/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMOfferDetailRequest : NSObject<RKRequestSerializable> {
    
    NSString * _offerId;
    
    NSDictionary * _request;
    
    NSNumber * _imageSizeType; 
    NSNumber * _disableLink;
}
@property(nonatomic, retain) NSDictionary * request;
@property (nonatomic, retain) NSString * offerId;
@property (nonatomic, retain) NSNumber * imageSizeType;
@property (nonatomic, retain) NSNumber * disableLink;

@end
