#import "AMCreditSummary.h"

@implementation AMCreditSummary

@synthesize certificateNum = _certificateNum;
@synthesize creditCode = _creditCode;
@synthesize vipSupplier = _vipSupplier;
@synthesize remarkCount = _remarkCount;
@synthesize remarkSatisfactionRate = _remarkSatisfactionRate;
@synthesize remarkCountFromBuyer = _remarkCountFromBuyer;
@synthesize remarkCountFromSeller = _remarkCountFromSeller;
@synthesize remarkAverageStarLevel = _remarkAverageStarLevel;
@synthesize recentDisputeCount = _recentDisputeCount;
@synthesize resolveDutyDispute = _resolveDutyDispute;
@synthesize unresolveDutyDispute = _unresolveDutyDispute;
@synthesize hisDispute = _hisDispute;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCreditSummary class]] retain];
			
            //super class 
            [sharedObjectMapping mapKeyPath:@"tpVersion" toAttribute:@"tpVersion"];
            [sharedObjectMapping mapKeyPath:@"tpYear" toAttribute:@"tpYear"];
            [sharedObjectMapping mapKeyPath:@"tpScore" toAttribute:@"tpScore"];
            [sharedObjectMapping mapKeyPath:@"guaranteeType" toAttribute:@"guaranteeType"];
			[sharedObjectMapping mapKeyPath:@"totalBalanceMoney" toAttribute:@"totalBalanceMoney"];
			[sharedObjectMapping mapKeyPath:@"memberId" toAttribute:@"memberId"];
			[sharedObjectMapping mapKeyPath:@"tpLogo" toAttribute:@"tpLogo"];
			[sharedObjectMapping mapKeyPath:@"fastpay" toAttribute:@"fastpay"];
            
			// self class
			[sharedObjectMapping mapKeyPath:@"certificateNum" toAttribute:@"certificateNum"];
            [sharedObjectMapping mapKeyPath:@"creditCode" toAttribute:@"creditCode"];
            [sharedObjectMapping mapKeyPath:@"vipSupplier" toAttribute:@"vipSupplier"];
            [sharedObjectMapping mapKeyPath:@"remarkCount" toAttribute:@"remarkCount"];
            [sharedObjectMapping mapKeyPath:@"remarkSatisfactionRate" toAttribute:@"remarkSatisfactionRate"];
            [sharedObjectMapping mapKeyPath:@"remarkCountFromBuyer" toAttribute:@"remarkCountFromBuyer"];
            [sharedObjectMapping mapKeyPath:@"remarkCountFromSeller" toAttribute:@"remarkCountFromSeller"];
            [sharedObjectMapping mapKeyPath:@"remarkAverageStarLevel" toAttribute:@"remarkAverageStarLevel"];
            [sharedObjectMapping mapKeyPath:@"recentDisputeCount" toAttribute:@"recentDisputeCount"];
            [sharedObjectMapping mapKeyPath:@"resolveDutyDispute" toAttribute:@"resolveDutyDispute"];
            [sharedObjectMapping mapKeyPath:@"unresolveDutyDispute" toAttribute:@"unresolveDutyDispute"];
            [sharedObjectMapping mapKeyPath:@"hisDispute" toAttribute:@"hisDispute"];

			
        }
    }
    
    return sharedObjectMapping;
}


- (void) dealloc {
	[_certificateNum release];
	[_creditCode release];
	[_vipSupplier release];
	[_remarkCount release];
	[_remarkSatisfactionRate release];
	[_remarkCountFromBuyer release];
	[_remarkCountFromSeller release];
	[_remarkAverageStarLevel release];
	[_recentDisputeCount release];
	[_resolveDutyDispute release];
	[_unresolveDutyDispute release];
	[_hisDispute release];

  [super dealloc];
}

@end
