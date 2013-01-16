//
//  AMFavoriteRequest.h
//  AlibabaMobile
//
//  Created by zzh on 11-12-29.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>
#import "AMRequestDelegate.h"

#define NOTIFICATION_FROM_DETAIL            @"update_from_detail_page"
#define NOTIFICATION_MESSAGE_FORWARD_FAV_PRICE @"message_forward_fav_price"

#define OCEAN_API_URL_COMPANY_FAV ([@"/favorite.getFavoriteCompanyList/" stringByAppendingString:AMCONST_APP_KEY])
#define OCEAN_API_URL_OFFER_FAV ([@"/favorite.getFavoriteOfferList/" stringByAppendingString:AMCONST_APP_KEY])
#define OCEAN_API_URL_PRICE_FAV ([@"/news.priceMarket.queryFavoritesByMemberId/" stringByAppendingString:AMCONST_APP_KEY])
#define OCEAN_API_URL_COMPANY_DETAIL ([@"/company.getCompany/" stringByAppendingString:AMCONST_APP_KEY])
#define OCEAN_API_URL_COMPANY_TRUSTRECORD ([@"/company.getCreditDetail/" stringByAppendingString:AMCONST_APP_KEY])

// For adding/deleting favorites
#define OCEAN_API_URL_OFFER_FAV_ADD ([@"/favorite.addFavoriteOffer/" stringByAppendingString:AMCONST_APP_KEY])
#define OCEAN_API_URL_OFFER_FAV_DEL ([@"/favorite.deleteFavoriteOffers/" stringByAppendingString:AMCONST_APP_KEY])
#define OCEAN_API_URL_COMPANY_FAV_ADD ([@"/favorite.addFavoriteCompany/" stringByAppendingString:AMCONST_APP_KEY])
#define OCEAN_API_URL_COMPANY_FAV_DEL ([@"/favorite.deleteFavoriteCompanys/" stringByAppendingString:AMCONST_APP_KEY])
#define OCEAN_API_URL_PRICE_FAV_ADD ([@"/news.priceMarket.addFavoritePrice/" stringByAppendingString:AMCONST_APP_KEY])
#define OCEAN_API_URL_PRICE_FAV_DEL ([@"/news.priceMarket.deleteFavoritePrice/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMFavoriteRequest : NSObject <RKRequestSerializable, AMRequestDelegate> {
    NSInteger _transactionType;
    
    // Query favarite list
    NSString *_memberid;
    NSNumber *_beginPage;
    NSNumber *_pageSize;
	
    //for add offers
    NSNumber * _offerid;
	// for delete offers
	NSArray  *_offerids;
	
    //for add company
    NSNumber *_companyid;
	// for delete companies
	NSArray  *_companyids;
    
    // for Price favorite add/del
    NSString * _themeId;
    NSString * _area;
    NSString * _sourceFromId;
    NSString *_memberId;
	
    // for add and del price    
	NSDictionary *_request;
    
}

@property (nonatomic, retain) NSString *memberid;
@property (nonatomic, retain) NSNumber *beginPage;
@property (nonatomic, retain) NSNumber *pageSize;

@property (nonatomic, retain) NSArray  *offerids;
@property (nonatomic, retain) NSNumber  *offerid;
@property (nonatomic, retain) NSArray  *companyids;
@property (nonatomic, retain) NSNumber  *companyid;

@property(nonatomic, retain) NSString * themeId;
@property(nonatomic, retain) NSString * area;
@property(nonatomic, retain) NSString * sourceFromId;
@property (nonatomic, retain) NSString *memberId;

@property (nonatomic, retain) NSDictionary  *request;

@property (nonatomic) NSInteger transactionType;
@property (nonatomic, retain) NSString *requestURL;


@end