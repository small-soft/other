#import "AMGeoInfo.h"

@implementation AMGeoInfo

@synthesize longitude = _longitude;
@synthesize latitude = _latitude;
@synthesize accuracy = _accuracy;
@synthesize matchLevel = _matchLevel;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMGeoInfo class]] retain];
			[sharedObjectMapping mapKeyPath:@"longitude" toAttribute:@"longitude"];
			[sharedObjectMapping mapKeyPath:@"latitude" toAttribute:@"latitude"];   
			[sharedObjectMapping mapKeyPath:@"accuracy" toAttribute:@"accuracy"];
			[sharedObjectMapping mapKeyPath:@"matchLevel" toAttribute:@"matchLevel"]; 			
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_longitude release];
  [_latitude release];
  [_accuracy release];
  [_matchLevel release];
  
  [super dealloc];
}

@end
