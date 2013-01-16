#import "AMBusinessRegistration.h"

@implementation AMBusinessRegistration

@synthesize establishedYear = _establishedYear;
@synthesize foundedPlace = _foundedPlace;
@synthesize principal = _principal;
@synthesize companyType = _companyType;
@synthesize regCapital = _regCapital;
@synthesize currencyType = _currencyType;
@synthesize bank = _bank;
@synthesize account = _account;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMBusinessRegistration class]] retain];
			[sharedObjectMapping mapKeyPath:@"establishedYear" toAttribute:@"establishedYear"];
			[sharedObjectMapping mapKeyPath:@"foundedPlace" toAttribute:@"foundedPlace"];   
			[sharedObjectMapping mapKeyPath:@"principal" toAttribute:@"principal"];
			[sharedObjectMapping mapKeyPath:@"companyType" toAttribute:@"companyType"];
			[sharedObjectMapping mapKeyPath:@"regCapital" toAttribute:@"regCapital"];
			[sharedObjectMapping mapKeyPath:@"bank" toAttribute:@"bank"];
			[sharedObjectMapping mapKeyPath:@"account" toAttribute:@"account"];
			
			[sharedObjectMapping mapRelationship:@"currencyType" withMapping:[AMCategory sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMCategory sharedObjectMapping] forKeyPath:@"currencyType"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_establishedYear release];
  [_foundedPlace release];
  [_principal release];
  [_companyType release];
  [_regCapital release];
  [_currencyType release];
  [_bank release];
  [_account release];
  
  [super dealloc];
}

@end
