//
//  AMCompanyProductRequest.h
//  AlibabaMobile
//
//  Created by mardin partytime on 1/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_COMPANY_PRODUCTLIST ([@"/search.offer.listMemberOffer/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMCompanyProductRequest : NSObject<RKRequestSerializable> {

    NSDictionary * _request;

    NSString * _memberId;
    NSNumber * _pageSize;
    NSNumber * _beginPage;
   
}

@property(nonatomic, retain) NSDictionary * request;
@property (nonatomic, retain) NSString *memberId;
@property (nonatomic, retain) NSNumber *beginPage;
@property (nonatomic, retain) NSNumber *pageSize;


@end


