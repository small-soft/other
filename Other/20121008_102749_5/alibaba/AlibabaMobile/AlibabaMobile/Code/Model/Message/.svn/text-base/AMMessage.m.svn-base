#import "AMMessage.h"
#import <RestKit/RestKit.h>

@implementation AMMessage

@synthesize identifier = _identifier;
@synthesize title = _title;
@synthesize source = _source;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [RKObjectMapping mappingForClass:[AMMessage class]];
            [sharedObjectMapping mapKeyPath:@"id" toAttribute:@"identifier"];
            [sharedObjectMapping mapKeyPath:@"title" toAttribute:@"title"];
            [sharedObjectMapping mapKeyPath:@"source" toAttribute:@"source"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_identifier release];
  [_title release];
  [_source release];
    
  [super dealloc];
}

@end
