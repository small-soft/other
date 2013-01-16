#import "AMNewsCategory.h"
#import <RestKit/RestKit.h>

/**
 * 
 */

@implementation AMNewsCategory

@synthesize identifier = _identifier;
@synthesize name = _name;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMNewsCategory class]] retain];
            [sharedObjectMapping mapKeyPath:@"id" toAttribute:@"identifier"];
            [sharedObjectMapping mapKeyPath:@"name" toAttribute:@"name"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_name release];
  [_identifier release];
  
  [super dealloc];
}

@end
