#import "AMOfferDetail.h"
#import "AMTradeInfo.h"
#import "AMMemberBrief.h"
#import "AMAddress.h"
#import "AMOfferRate.h"
#import "AMOfferStatus.h"
#import "AMPrice.h"
#import "AMImage.h"
#import "AMFeatureAttribute.h"

#import <RestKit/RestKit.h>

NSInteger const AMREALPRICE_VALID = 1;
NSInteger const AMREALPRICE_NOT_VALID = 2;
NSInteger const AMREALPRICE_NOT_EXISTS = 3;

/**
 * 
 */
@class AMOfferStatus;

@implementation AMOfferDetail

@synthesize detail = _detail;
@synthesize priceRange = _priceRange;
@synthesize priceUnit = _priceUnit;
@synthesize mixWholeSale = _mixWholeSale;
@synthesize featureAttributes = _featureAttributes;
@synthesize subject = _subject;
@synthesize tradeInfo = _tradeInfo;
@synthesize amount = _amount;
@synthesize companyBrief = _companyBrief;
@synthesize memberId = _memberId;
@synthesize imageList = _imageList;
@synthesize sendAddress = _sendAddress;
@synthesize offerId = _offerId;
@synthesize priceStatus = _priceStatus;
@synthesize productUnit = _productUnit;
@synthesize pictureAuthOffer = _pictureAuthOffer;
@synthesize priceAuthOffer = _priceAuthOffer;
@synthesize availableAmount = _availableAmount;
@synthesize dealedAmount = _dealedAmount;
@synthesize rate = _rate;
@synthesize offerStatus = _offerStatus;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMOfferDetail class]] retain];
            [sharedObjectMapping mapKeyPath:@"detail" toAttribute:@"detail"];
            [sharedObjectMapping mapKeyPath:@"priceUnit" toAttribute:@"priceUnit"];
            [sharedObjectMapping mapKeyPath:@"mixWholeSale" toAttribute:@"mixWholeSale"];
			[sharedObjectMapping mapKeyPath:@"subject" toAttribute:@"subject"];
			[sharedObjectMapping mapKeyPath:@"amount" toAttribute:@"amount"];
			[sharedObjectMapping mapKeyPath:@"memberId" toAttribute:@"memberId"];
			[sharedObjectMapping mapKeyPath:@"offerId" toAttribute:@"offerId"];
            [sharedObjectMapping mapKeyPath:@"priceStatus" toAttribute:@"priceStatus"];
			[sharedObjectMapping mapKeyPath:@"productUnit" toAttribute:@"productUnit"];
			[sharedObjectMapping mapKeyPath:@"pictureAuthOffer" toAttribute:@"pictureAuthOffer"];
			[sharedObjectMapping mapKeyPath:@"priceAuthOffer" toAttribute:@"priceAuthOffer"];
			[sharedObjectMapping mapKeyPath:@"availableAmount" toAttribute:@"availableAmount"];
            [sharedObjectMapping mapKeyPath:@"dealedAmount" toAttribute:@"dealedAmount"];
					
            [sharedObjectMapping mapRelationship:@"priceRange" withMapping:[AMPrice sharedObjectMapping]];
            [sharedObjectMapping mapRelationship:@"imageList" withMapping:[AMImage sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"tradeInfo" withMapping:[AMTradeInfo sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"companyBrief" withMapping:[AMMemberBrief sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"sendAddress" withMapping:[AMAddress sharedObjectMapping]];
            [sharedObjectMapping mapRelationship:@"featureAttributes" withMapping:[AMFeatureAttribute sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"rate" withMapping:[AMOfferRate sharedObjectMapping]];
            //[sharedObjectMapping mapRelationship:@"offerStatus" withMapping:[AMOfferStatus sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMPrice sharedObjectMapping] forKeyPath:@"priceRange"];
			[mappingProvider setMapping:[AMImage sharedObjectMapping] forKeyPath:@"imageList"];
			[mappingProvider setMapping:[AMTradeInfo sharedObjectMapping] forKeyPath:@"tradeInfo"];
			[mappingProvider setMapping:[AMMemberBrief sharedObjectMapping] forKeyPath:@"companyBrief"];
			[mappingProvider setMapping:[AMAddress sharedObjectMapping] forKeyPath:@"sendAddress"];
			[mappingProvider setMapping:[AMFeatureAttribute sharedObjectMapping] forKeyPath:@"featureAttributes"];
			[mappingProvider setMapping:[AMOfferRate sharedObjectMapping] forKeyPath:@"rate"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_memberId release];
  [_subject release];
  [_priceRange release];
  [_priceUnit release];
  [_productUnit release];
  [_tradeInfo release];
  [_imageList release];
  [_companyBrief release];
  [_sendAddress release];
  [_featureAttributes release];
  [_detail release];
  [_rate release];
  [_offerStatus release];
  [_mixWholeSale release];
  [_amount release];
  [_offerId release];
  [_priceStatus release];
  [_pictureAuthOffer release];
  [_priceAuthOffer release];
  [_availableAmount release];
  [_dealedAmount release];
  
  [super dealloc];
}

@end
