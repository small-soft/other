#import "AMFavoriteCompany.h"
#import "AMFavoriteTag.h"
#import <RestKit/RestKit.h>

/**
 * 
 */
 
@implementation AMFavoriteCompany

@synthesize contact = _contact;
@synthesize name = _name;
@synthesize memberId = _memberId;
@synthesize address = _address;
@synthesize bizType = _bizType;
@synthesize productionService = _productionService;
@synthesize trust = _trust;
@synthesize establishedYear = _establishedYear;
@synthesize companyid = _companyid;
@synthesize phoneArea = _phoneArea;
@synthesize phoneCountry = _phoneCountry;
@synthesize phoneNumber = _phoneNumber;
@synthesize tpLogo = _tpLogo;
@synthesize mobileNumber = _mobileNumber;
@synthesize valid = _valid;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMFavoriteCompany class]] retain];
			//base class mapping
			[sharedObjectMapping mapKeyPath:@"collectedCount" toAttribute:@"collectedCount"];
			[sharedObjectMapping mapKeyPath:@"favoriteId" toAttribute:@"favoriteId"];
			
			[sharedObjectMapping mapRelationship:@"favoriteTaglList" withMapping:[AMFavoriteTag sharedObjectMapping]];
			
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMFavoriteTag sharedObjectMapping] forKeyPath:@"favoriteTaglList"];
			
			// derived class mapping
			[sharedObjectMapping mapKeyPath:@"contact" toAttribute:@"contact"];
			[sharedObjectMapping mapKeyPath:@"name" toAttribute:@"name"];
			[sharedObjectMapping mapKeyPath:@"memberId" toAttribute:@"memberId"];
			[sharedObjectMapping mapKeyPath:@"address" toAttribute:@"address"];
			[sharedObjectMapping mapKeyPath:@"bizType" toAttribute:@"bizType"];
			[sharedObjectMapping mapKeyPath:@"productionService" toAttribute:@"productionService"];
			[sharedObjectMapping mapKeyPath:@"trust" toAttribute:@"trust"];
			[sharedObjectMapping mapKeyPath:@"establishedYear" toAttribute:@"establishedYear"];
			[sharedObjectMapping mapKeyPath:@"companyid" toAttribute:@"companyid"];
			[sharedObjectMapping mapKeyPath:@"phoneArea" toAttribute:@"phoneArea"];
			[sharedObjectMapping mapKeyPath:@"phoneCountry" toAttribute:@"phoneCountry"];
			[sharedObjectMapping mapKeyPath:@"phoneNumber" toAttribute:@"phoneNumber"];
			[sharedObjectMapping mapKeyPath:@"tpLogo" toAttribute:@"tpLogo"];
			[sharedObjectMapping mapKeyPath:@"mobileNumber" toAttribute:@"mobileNumber"];
            [sharedObjectMapping mapKeyPath:@"valid" toAttribute:@"valid"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_name release];
  [_companyid release];
  [_memberId release];
  [_address release];
  [_bizType release];
  [_productionService release];
  [_trust release];
  [_contact release];
  [_establishedYear release];
  [_phoneArea release];
  [_phoneCountry release];
  [_phoneNumber release];
  [_tpLogo release];
  [_mobileNumber release];
    [_valid release];
  
  [super dealloc];
}

@end
