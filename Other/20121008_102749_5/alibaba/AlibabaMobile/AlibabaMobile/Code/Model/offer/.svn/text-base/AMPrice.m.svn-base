#import "AMPrice.h"


/**
 * 
 */

@implementation AMPrice

@synthesize beginAmount = _beginAmount;
@synthesize price = _price;
@synthesize endAmount = _endAmount;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMPrice class]] retain];
            [sharedObjectMapping mapKeyPath:@"beginAmount" toAttribute:@"beginAmount"];
            [sharedObjectMapping mapKeyPath:@"price" toAttribute:@"price"];
            [sharedObjectMapping mapKeyPath:@"endAmount" toAttribute:@"endAmount"];
        }
    }
    
    return sharedObjectMapping;
}


- (void) dealloc {
  [_beginAmount release];
  [_price release];
  [_endAmount release];
  
  [super dealloc];
}

@end
