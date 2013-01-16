#import "AMGuaranteeGroupMember.h"

@implementation AMGuaranteeGroupMember

@synthesize memberId = _memberId;
@synthesize memberType = _memberType;
@synthesize companyName = _companyName;
@synthesize tpYear = _tpYear;
@synthesize tpScore = _tpScore;
@synthesize totalCreditMoney = _totalCreditMoney;
@synthesize tpLogo = _tpLogo;
@synthesize memberPosition = _memberPosition;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMGuaranteeGroupMember class]] retain];
			
			// Super class
			[sharedObjectMapping mapKeyPath:@"memberId" toAttribute:@"memberId"];
            [sharedObjectMapping mapKeyPath:@"memberType" toAttribute:@"memberType"];
            [sharedObjectMapping mapKeyPath:@"companyName" toAttribute:@"companyName"];
            [sharedObjectMapping mapKeyPath:@"tpYear" toAttribute:@"tpYear"];
            [sharedObjectMapping mapKeyPath:@"tpScore" toAttribute:@"tpScore"];
            [sharedObjectMapping mapKeyPath:@"totalCreditMoney" toAttribute:@"totalCreditMoney"];
            [sharedObjectMapping mapKeyPath:@"tpLogo" toAttribute:@"tpLogo"];
            [sharedObjectMapping mapKeyPath:@"memberPosition" toAttribute:@"memberPosition"];
           
        }
    }
    
    return sharedObjectMapping;
}


- (void) dealloc {
  [_memberId release];
  [_memberType release];
  [_companyName release];
  [_tpYear release];
  [_tpScore release];
  [_totalCreditMoney release];
  [_tpLogo release];
  [_memberPosition release];
  
  [super dealloc];
}

@end
