#import "AMGeographicResult.h"

@implementation AMGeographicResult

@synthesize longitude = _longitude;
@synthesize latitude = _latitude;
@synthesize province = _province;
@synthesize city = _city;
@synthesize town = _town;
@synthesize street = _street;
@synthesize postcode = _postcode;
@synthesize location = _location;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMGeographicResult class]] retain];
            [sharedObjectMapping mapKeyPath:@"longitude" toAttribute:@"longitude"];
            [sharedObjectMapping mapKeyPath:@"latitude" toAttribute:@"latitude"];
            [sharedObjectMapping mapKeyPath:@"province" toAttribute:@"province"];
            [sharedObjectMapping mapKeyPath:@"city" toAttribute:@"city"];
            [sharedObjectMapping mapKeyPath:@"town" toAttribute:@"town"];
            [sharedObjectMapping mapKeyPath:@"street" toAttribute:@"street"];
            [sharedObjectMapping mapKeyPath:@"postcode" toAttribute:@"postcode"];
            [sharedObjectMapping mapKeyPath:@"location" toAttribute:@"location"];
        }
    }
    
    return sharedObjectMapping;
}

- (NSString*)description {
    return [NSString stringWithFormat:@"%@ (ID: %@)", self.longitude, self.latitude];
}

- (void) dealloc {
  [_longitude release];
  [_latitude release];
  [_province release];
  [_city release];
  [_town release];
  [_street release];
  [_postcode release];
  [_location release];
  
  [super dealloc];
}

@end
