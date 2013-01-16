#import "AMAddress.h"
#import <RestKit/RestKit.h>

@implementation AMAddress

@synthesize cityId = _cityId;
@synthesize cityName = _cityName;
@synthesize countryId = _countryId;
@synthesize countryName = _countryName;
@synthesize provinceName  = _provinceName;
@synthesize streetAddress = _streetAddress;
@synthesize zipCode = _zipCode;
@synthesize areaCode = _areaCode;
@synthesize areaName = _areaName;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [RKObjectMapping mappingForClass:[AMAddress class]];
            [sharedObjectMapping mapKeyPath:@"cityId" toAttribute:@"cityId"];
            [sharedObjectMapping mapKeyPath:@"cityName" toAttribute:@"cityName"];
            [sharedObjectMapping mapKeyPath:@"countryId" toAttribute:@"countryId"];
            [sharedObjectMapping mapKeyPath:@"countryName" toAttribute:@"countryName"];
			[sharedObjectMapping mapKeyPath:@"provinceName" toAttribute:@"provinceName"];
			[sharedObjectMapping mapKeyPath:@"streetAddress" toAttribute:@"streetAddress"];
			[sharedObjectMapping mapKeyPath:@"zipCode" toAttribute:@"zipCode"];
			[sharedObjectMapping mapKeyPath:@"areaCode" toAttribute:@"areaCode"];
			[sharedObjectMapping mapKeyPath:@"areaName" toAttribute:@"areaName"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_cityId release];
  [_cityName release];
  [_countryId release];
  [_countryName release];
  [_provinceName release];
  [_streetAddress release];
  [_zipCode release];
  [_areaCode release];
  [_areaName release];
    
  [super dealloc];
}

@end
