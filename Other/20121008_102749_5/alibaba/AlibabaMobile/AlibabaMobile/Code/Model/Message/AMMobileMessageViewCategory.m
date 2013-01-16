#import "AMMobileMessageViewCategory.h"
#import <RestKit/RestKit.h>

@implementation AMMobileMessageViewCategory

@synthesize source = _source;
@synthesize displayName = _displayName;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [RKObjectMapping mappingForClass:[AMMobileMessageViewCategory class]];  
            [sharedObjectMapping mapKeyPath:@"source" toAttribute:@"source"];
			[sharedObjectMapping mapKeyPath:@"displayName" toAttribute:@"displayName"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_source release];
  [_displayName release];
    
  [super dealloc];
}

@end
