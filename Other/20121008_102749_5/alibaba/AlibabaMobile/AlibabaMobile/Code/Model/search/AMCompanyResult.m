#import "AMCompanyResult.h"
#import "AMCompany.h"

@implementation AMCompanyResult

@synthesize companyList = _companyList;
@synthesize total = _total;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCompanyResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"total" toAttribute:@"total"];
			
			[sharedObjectMapping mapRelationship:@"companyList" withMapping:[AMCompany sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMCompany sharedObjectMapping] forKeyPath:@"companyList"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_companyList release];
  [_total release];
  
  [super dealloc];
}

@end
