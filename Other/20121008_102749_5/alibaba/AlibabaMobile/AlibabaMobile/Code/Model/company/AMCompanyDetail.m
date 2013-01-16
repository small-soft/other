#import "AMCompanyDetail.h"

#import "AMPerson.h"
#import "AMContact.h"
#import "AMCreditBase.h"
#import "AMBusinessRegistration.h"
#import "AMAddress.h"
#import "AMGeoInfo.h"
#import "AMCompanyIndustry.h"

@implementation AMCompanyDetail

@synthesize identifier = _identifier;
@synthesize logoUrl = _logoUrl;
@synthesize mainIndustries = _mainIndustries;
@synthesize productionService = _productionService;
@synthesize employeesCount = _employeesCount;
@synthesize vaccountId = _vaccountId;
@synthesize registration = _registration;
@synthesize summary = _summary;
@synthesize address = _address;
@synthesize geoInfo = _geoInfo;
@synthesize manufactureSupplied = _manufactureSupplied;
@synthesize industry = _industry;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCompanyDetail class]] retain];
			
			// Super class
			[sharedObjectMapping mapKeyPath:@"bizType" toAttribute:@"bizType"];
            [sharedObjectMapping mapKeyPath:@"name" toAttribute:@"name"];
            [sharedObjectMapping mapKeyPath:@"memberType" toAttribute:@"memberType"];
            [sharedObjectMapping mapKeyPath:@"statusEnabled" toAttribute:@"statusEnabled"];
			
			[sharedObjectMapping mapRelationship:@"creditBase" withMapping:[AMCreditBase sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"contact" withMapping:[AMContact sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"person" withMapping:[AMPerson sharedObjectMapping]];
			
			// Drived class
			[sharedObjectMapping mapKeyPath:@"id" toAttribute:@"identifier"];
			[sharedObjectMapping mapKeyPath:@"logoUrl" toAttribute:@"logoUrl"];
			[sharedObjectMapping mapKeyPath:@"mainIndustries" toAttribute:@"mainIndustries"];
			[sharedObjectMapping mapKeyPath:@"productionService" toAttribute:@"productionService"];
			[sharedObjectMapping mapKeyPath:@"employeesCount" toAttribute:@"employeesCount"];
			[sharedObjectMapping mapKeyPath:@"vaccountId" toAttribute:@"vaccountId"];
			[sharedObjectMapping mapKeyPath:@"summary" toAttribute:@"summary"];
			[sharedObjectMapping mapKeyPath:@"manufactureSupplie" toAttribute:@"manufactureSupplie"];
			
			[sharedObjectMapping mapRelationship:@"registration" withMapping:[AMBusinessRegistration sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"address" withMapping:[AMAddress sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"geoInfo" withMapping:[AMGeoInfo sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"industry" withMapping:[AMCompanyIndustry sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			// For Super class
			[mappingProvider setMapping:[AMCreditBase sharedObjectMapping] forKeyPath:@"creditBase"];
			[mappingProvider setMapping:[AMContact sharedObjectMapping] forKeyPath:@"contact"];
			[mappingProvider setMapping:[AMPerson sharedObjectMapping] forKeyPath:@"person"];
			
			//For Drived class
			[mappingProvider setMapping:[AMBusinessRegistration sharedObjectMapping] forKeyPath:@"registration"];
			[mappingProvider setMapping:[AMAddress sharedObjectMapping] forKeyPath:@"address"];
			[mappingProvider setMapping:[AMGeoInfo sharedObjectMapping] forKeyPath:@"geoInfo"];
			[mappingProvider setMapping:[AMCompanyIndustry sharedObjectMapping] forKeyPath:@"industry"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_identifier release];
  [_logoUrl release];
  [_mainIndustries release];
  [_productionService release];
  [_employeesCount release];
  [_vaccountId release];
  [_registration release];
  [_summary release];
  [_address release];
  [_geoInfo release];
  [_manufactureSupplied release];
  [_industry release];
  
  [super dealloc];
}

@end
