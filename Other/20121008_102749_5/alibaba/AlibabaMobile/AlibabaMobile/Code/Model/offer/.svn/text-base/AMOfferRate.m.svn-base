#import "AMOfferRate.h"
#import <RestKit/RestKit.h>

@implementation AMOfferRate

@synthesize remarkCount = _remarkCount;
@synthesize averageStarLevel = _averageStarLevel;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMOfferRate class]] retain];
            [sharedObjectMapping mapKeyPath:@"remarkCount" toAttribute:@"remarkCount"];
            [sharedObjectMapping mapKeyPath:@"averageStarLevel" toAttribute:@"averageStarLevel"];
        }
    }
    
    return sharedObjectMapping;
}

-(void) dealloc {
  [_remarkCount release];
  [_averageStarLevel release];
  
  [super dealloc];
}

@end
