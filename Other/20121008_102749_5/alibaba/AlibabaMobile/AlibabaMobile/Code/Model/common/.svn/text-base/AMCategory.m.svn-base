#import "AMCategory.h"
#import <RestKit/RestKit.h>

@implementation AMCategory

@synthesize identifier = _identifier;
@synthesize name = _name;
@synthesize leaf = _leaf;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCategory class]] retain];
            [sharedObjectMapping mapKeyPath:@"id" toAttribute:@"identifier"];
            [sharedObjectMapping mapKeyPath:@"name" toAttribute:@"name"];
            [sharedObjectMapping mapKeyPath:@"leaf" toAttribute:@"leaf"];
        }
    }
    
    return sharedObjectMapping;
}

- (NSString*)description {
    return [NSString stringWithFormat:@"%@ (ID: %@)", self.name, self.identifier];
}

- (void)dealloc {
    [_identifier release];
    [_name release];
    
    [super dealloc];
}

@end
