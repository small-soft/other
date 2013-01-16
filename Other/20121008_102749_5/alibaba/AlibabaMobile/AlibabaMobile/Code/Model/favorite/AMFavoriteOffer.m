#import "AMFavoriteOffer.h"
#import "AMFavoriteCompany.h"
#import "AMCategory.h"
#import "AMMoney.h"
#import "AMFavoriteTag.h"
#import <RestKit/RestKit.h>

/**
 * 
 */

@implementation AMFavoriteOffer

@synthesize sendAddress = _sendAddress;
@synthesize categories = _categories;
@synthesize offerid = _offerid;
@synthesize title = _title;
@synthesize price = _price;
@synthesize unit = _unit;
@synthesize valid = _valid;
@synthesize validDay = _validDay;
@synthesize validHour = _validHour;
@synthesize company = _company;
@synthesize firstImage = _firstImage;
@synthesize quantityBegin = _quantityBegin;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMFavoriteOffer class]] retain];
			//base class mapping
			[sharedObjectMapping mapKeyPath:@"collectedCount" toAttribute:@"collectedCount"];
			[sharedObjectMapping mapKeyPath:@"favoriteId" toAttribute:@"favoriteId"];
			
			[sharedObjectMapping mapRelationship:@"favoriteTaglList" withMapping:[AMFavoriteTag sharedObjectMapping]];
			
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMFavoriteTag sharedObjectMapping] forKeyPath:@"favoriteTaglList"];
			
			// derived class mapping
			[sharedObjectMapping mapKeyPath:@"sendAddress" toAttribute:@"sendAddress"];
			[sharedObjectMapping mapKeyPath:@"offerid" toAttribute:@"offerid"];
			[sharedObjectMapping mapKeyPath:@"title" toAttribute:@"title"];
			[sharedObjectMapping mapKeyPath:@"unit" toAttribute:@"unit"];
			[sharedObjectMapping mapKeyPath:@"valid" toAttribute:@"valid"];
			[sharedObjectMapping mapKeyPath:@"validDay" toAttribute:@"validDay"];
			[sharedObjectMapping mapKeyPath:@"validHour" toAttribute:@"validHour"];
			[sharedObjectMapping mapKeyPath:@"firstImage" toAttribute:@"firstImage"];
			[sharedObjectMapping mapKeyPath:@"quantityBegin" toAttribute:@"quantityBegin"];
			
			[sharedObjectMapping mapRelationship:@"categories" withMapping:[AMCategory sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"price" withMapping:[AMMoney sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"company" withMapping:[AMFavoriteCompany sharedObjectMapping]];
			
			[mappingProvider setMapping:[AMCategory sharedObjectMapping] forKeyPath:@"categories"];
			[mappingProvider setMapping:[AMMoney sharedObjectMapping] forKeyPath:@"price"];
			[mappingProvider setMapping:[AMFavoriteCompany sharedObjectMapping] forKeyPath:@"company"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_offerid release];
  [_title release];
  [_price release];
  [_unit release];
  [_valid release];
  [_validDay release];
  [_validHour release];
  [_company release];
  [_firstImage release];
  [_sendAddress release];
  [_categories release];
  [_quantityBegin release];
    [_valid release];
    
  [super dealloc];
}

@end
