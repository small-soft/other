#import "AMLogResult.h"

/**
 * Successful
 */
NSInteger const AMCODE_OK = 200;

/**
 * Client Error 4xx
 */
NSInteger const AMCODE_BAD_REQUEST = 400;
NSInteger const AMCODE_BAD_LENGTH = 401;
NSInteger const AMCODE_BAD_FORMAT = 402;

/**
 * Server Error 5xx
 */
NSInteger const AMCODE_BAD_SERVICE = 500;
NSInteger const AMCODE_BAD_DEPEND_ENV = 501;

@implementation AMLogResult

@synthesize success = _success;
@synthesize resultCode = _resultCode;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMLogResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"success" toAttribute:@"success"];
			[sharedObjectMapping mapKeyPath:@"resultCode" toAttribute:@"resultCode"];
        }
    }
    
    return sharedObjectMapping;
}

-(void) dealloc {
    [_success release];
    [_resultCode release];
    
    [super dealloc];
}

@end
