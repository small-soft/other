#import "AMMoney.h"
#import "AMCurrency.h"
#import <RestKit/RestKit.h>

@implementation AMMoney


@synthesize amount = _amount;
@synthesize cent = _cent;
@synthesize currencyCode = _currencyCode;
@synthesize currency = _currency;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMMoney class]] retain];
			[sharedObjectMapping mapKeyPath:@"amount" toAttribute:@"amount"];
			[sharedObjectMapping mapKeyPath:@"cent" toAttribute:@"cent"];
			[sharedObjectMapping mapKeyPath:@"currencyCode" toAttribute:@"currencyCode"];
			
			[sharedObjectMapping mapRelationship:@"currency" withMapping:[AMCurrency sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMCurrency sharedObjectMapping] forKeyPath:@"currency"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_amount release];
  [_cent release];
  [_currencyCode release];
  [_currency release];
  
  [super dealloc];
}

@end
