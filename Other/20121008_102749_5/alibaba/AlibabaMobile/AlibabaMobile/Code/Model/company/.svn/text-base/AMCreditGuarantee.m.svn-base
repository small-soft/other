#import "AMCreditGuarantee.h"
#import "AMGuaranteeGroup.h"

@implementation AMCreditGuarantee

@synthesize position = _position;
@synthesize totalCreditMoney = _totalCreditMoney;
@synthesize totalFreezeMoney = _totalFreezeMoney;
@synthesize totalBalanceMoney = _totalBalanceMoney;
@synthesize freezeRecordsNum = _freezeRecordsNum;
@synthesize unFreezeRecordsNum = _unFreezeRecordsNum;
@synthesize guaranteeGroup = _guaranteeGroup;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCreditGuarantee class]] retain];
			
			// Super class
			[sharedObjectMapping mapKeyPath:@"position" toAttribute:@"position"];
            [sharedObjectMapping mapKeyPath:@"totalCreditMoney" toAttribute:@"totalCreditMoney"];
            [sharedObjectMapping mapKeyPath:@"totalFreezeMoney" toAttribute:@"totalFreezeMoney"];
            [sharedObjectMapping mapKeyPath:@"totalBalanceMoney" toAttribute:@"totalBalanceMoney"];
            [sharedObjectMapping mapKeyPath:@"freezeRecordsNum" toAttribute:@"freezeRecordsNum"];
            [sharedObjectMapping mapKeyPath:@"unFreezeRecordsNum" toAttribute:@"unFreezeRecordsNum"];
           
            [sharedObjectMapping mapRelationship:@"guaranteeGroup" withMapping:[AMGuaranteeGroup sharedObjectMapping]];
			
            
            RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			// For Super class
			[mappingProvider setMapping:[AMGuaranteeGroup sharedObjectMapping] forKeyPath:@"guaranteeGroup"];
        }
    }
    
    return sharedObjectMapping;
}



- (void) dealloc {
  [_position release];
  [_totalCreditMoney release];
  [_totalFreezeMoney release];
  [_totalBalanceMoney release];
  [_guaranteeGroup release];
  
  [super dealloc];
}

@end
