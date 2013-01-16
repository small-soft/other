#import "AMCreditBase.h"
#import <RestKit/RestKit.h>

@implementation AMCreditBase

@synthesize tpVersion = _tpVersion;
@synthesize tpYear = _tpYear;
@synthesize tpScore = _tpScore;
@synthesize guaranteeType = _guaranteeType;
@synthesize totalBalanceMoney = _totalBalanceMoney;
@synthesize memberId = _memberId;
@synthesize tpLogo = _tpLogo;
@synthesize fastpay = _fastpay;
@synthesize ovAuth = _ovAuth;
@synthesize realPrice = _realPrice;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCreditBase class]] retain];
            [sharedObjectMapping mapKeyPath:@"tpVersion" toAttribute:@"tpVersion"];
            [sharedObjectMapping mapKeyPath:@"tpYear" toAttribute:@"tpYear"];
            [sharedObjectMapping mapKeyPath:@"tpScore" toAttribute:@"tpScore"];
            [sharedObjectMapping mapKeyPath:@"guaranteeType" toAttribute:@"guaranteeType"];
			[sharedObjectMapping mapKeyPath:@"totalBalanceMoney" toAttribute:@"totalBalanceMoney"];
			[sharedObjectMapping mapKeyPath:@"memberId" toAttribute:@"memberId"];
			[sharedObjectMapping mapKeyPath:@"tpLogo" toAttribute:@"tpLogo"];
			[sharedObjectMapping mapKeyPath:@"fastpay" toAttribute:@"fastpay"];
            [sharedObjectMapping mapKeyPath:@"ovAuth" toAttribute:@"ovAuth"];
            [sharedObjectMapping mapKeyPath:@"realPrice" toAttribute:@"realPrice"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_tpVersion release];
  [_tpYear release];
  [_tpLogo release];
  [_tpScore release];
  [_guaranteeType release];
  [_totalBalanceMoney release];
  [_memberId release];
  [_fastpay release];
    [_ovAuth release];
    [_realPrice release];
    
  [super dealloc];
}

@end
