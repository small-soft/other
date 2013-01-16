#import "AMMemberCredit.h"

@implementation AMMemberCredit

@synthesize creditBalanceYuan = _creditBalanceYuan;
@synthesize trustLogo = _trustLogo;
@synthesize trustScore = _trustScore;
@synthesize sevenDaysCompensate = _sevenDaysCompensate;
@synthesize creditBalance = _creditBalance;
@synthesize garantee = _garantee;
@synthesize tradable = _tradable;
@synthesize trust = _trust;
@synthesize memberType = _memberType;
@synthesize trustLogoSmall = _trustLogoSmall;
@synthesize tpVersion = _tpVersion;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMMemberCredit class]] retain];
			[sharedObjectMapping mapKeyPath:@"creditBalanceYuan" toAttribute:@"creditBalanceYuan"];
			[sharedObjectMapping mapKeyPath:@"name" toAttribute:@"name"];
			[sharedObjectMapping mapKeyPath:@"trustLogo" toAttribute:@"trustLogo"];
			[sharedObjectMapping mapKeyPath:@"trustLogoSmall" toAttribute:@"trustLogoSmall"];
			[sharedObjectMapping mapKeyPath:@"trustScore" toAttribute:@"trustScore"];
			[sharedObjectMapping mapKeyPath:@"sevenDaysCompensate" toAttribute:@"sevenDaysCompensate"];
			[sharedObjectMapping mapKeyPath:@"creditBalance" toAttribute:@"creditBalance"];
			[sharedObjectMapping mapKeyPath:@"garantee" toAttribute:@"garantee"];
			[sharedObjectMapping mapKeyPath:@"tradable" toAttribute:@"tradable"];
			[sharedObjectMapping mapKeyPath:@"trust" toAttribute:@"trust"];
			[sharedObjectMapping mapKeyPath:@"memberType" toAttribute:@"memberType"];
			[sharedObjectMapping mapKeyPath:@"tpVersion" toAttribute:@"tpVersion"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
	[_creditBalanceYuan release];
	[_trustLogo release];
	[_trustScore release];
	[_sevenDaysCompensate release];
	[_creditBalance release];
	[_garantee release];
	[_tradable release];
	[_trust release];
	[_trustLogoSmall release];
	[_memberType release];
	[_tpVersion release];

	[super dealloc];
}

@end
