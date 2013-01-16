#import "AMCreditResult.h"
#import "AMCreditSummary.h"
#import "AMCreditGuarantee.h"
#import "AMCreditRealAuth.h"


@implementation AMCreditResult

@synthesize summary = _summary;
@synthesize guarantee = _guarantee;
@synthesize realAuth = _realAuth;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCreditResult class]] retain];
			
			// Super class
	
			[sharedObjectMapping mapRelationship:@"summary" withMapping:[AMCreditSummary sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"guarantee" withMapping:[AMCreditGuarantee sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"realAuth" withMapping:[AMCreditRealAuth sharedObjectMapping]];
			
						
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			// For Super class
 
			[mappingProvider setMapping:[AMCreditSummary sharedObjectMapping] forKeyPath:@"summary"];
			[mappingProvider setMapping:[AMCreditGuarantee sharedObjectMapping] forKeyPath:@"guarantee"];
			[mappingProvider setMapping:[AMCreditRealAuth sharedObjectMapping] forKeyPath:@"realAuth"];
			
        }
    }
    
    return sharedObjectMapping;
}


- (void) dealloc {
  [_summary release];
  [_guarantee release];
  [_realAuth release];
  
  [super dealloc];
}

@end
