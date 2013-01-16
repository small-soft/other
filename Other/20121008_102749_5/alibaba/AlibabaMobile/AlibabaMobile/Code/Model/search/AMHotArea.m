#import "AMHotArea.h"

@implementation AMHotArea

@synthesize identifier = _identifier;
@synthesize showTitle = _showTitle;
@synthesize province = _province;
@synthesize city = _city;




+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMHotArea class]] retain];
			[sharedObjectMapping mapKeyPath:@"id" toAttribute:@"identifier"];
			[sharedObjectMapping mapKeyPath:@"province" toAttribute:@"province"];
			[sharedObjectMapping mapKeyPath:@"showTitle" toAttribute:@"showTitle"];
            [sharedObjectMapping mapKeyPath:@"city" toAttribute:@"city"];
        }
    }
    
    return sharedObjectMapping;
}


- (void) dealloc {
  [_identifier release];
  [_showTitle release];
  [_province release];
  [_city release];
  
  [super dealloc];
}

@end
