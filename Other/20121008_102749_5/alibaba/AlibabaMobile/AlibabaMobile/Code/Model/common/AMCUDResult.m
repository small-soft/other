#import "AMCUDResult.h"
#import <RestKit/RestKit.h>

/**
 * 
 */

@implementation AMCUDResult

@synthesize resultCode;
@synthesize success;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCUDResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"resultCode" toAttribute:@"resultCode"];
			[sharedObjectMapping mapKeyPath:@"success" toAttribute:@"success"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [resultCode release];
  [super dealloc];
}

@end
