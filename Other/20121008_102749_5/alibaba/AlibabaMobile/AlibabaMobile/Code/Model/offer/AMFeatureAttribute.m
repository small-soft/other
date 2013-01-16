#import "AMFeatureAttribute.h"
#import <RestKit/RestKit.h>

@implementation AMFeatureAttribute

@synthesize fid = _fid;
@synthesize name = _name;
@synthesize flag = _flag;
@synthesize values = _values;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMFeatureAttribute class]] retain];
            [sharedObjectMapping mapKeyPath:@"fid" toAttribute:@"fid"];
            [sharedObjectMapping mapKeyPath:@"name" toAttribute:@"name"];
            [sharedObjectMapping mapKeyPath:@"flag" toAttribute:@"flag"];
            [sharedObjectMapping mapKeyPath:@"values" toAttribute:@"values"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_fid release];
  [_name release];
  [_flag release];
  [_values release];
  
  [super dealloc];
}

@end
