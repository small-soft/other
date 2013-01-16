#import "AMHotAreaResult.h"
#import "AMHotArea.h"
@implementation AMHotAreaResult

@synthesize hotAreaList = _hotAreaList;
@synthesize hotProvinceList = _hotProvinceList;
@synthesize hotCityList = _hotCityList;
@synthesize hotRegionList = _hotRegionList;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMHotAreaResult class]] retain];
			[sharedObjectMapping mapRelationship:@"hotAreaList" withMapping:[AMHotArea sharedObjectMapping]];
            [sharedObjectMapping mapRelationship:@"hotProvinceList" withMapping:[AMHotArea sharedObjectMapping]];
            [sharedObjectMapping mapRelationship:@"hotCityList" withMapping:[AMHotArea sharedObjectMapping]];
            [sharedObjectMapping mapRelationship:@"hotRegionList" withMapping:[AMHotArea sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMHotArea sharedObjectMapping] forKeyPath:@"hotAreaList"];
            [mappingProvider setMapping:[AMHotArea sharedObjectMapping] forKeyPath:@"hotProvinceList"];
            [mappingProvider setMapping:[AMHotArea sharedObjectMapping] forKeyPath:@"hotCityList"];
            [mappingProvider setMapping:[AMHotArea sharedObjectMapping] forKeyPath:@"hotRegionList"];
        }
    }
    
    return sharedObjectMapping;
}



- (void) dealloc {
  [_hotAreaList release];
  [_hotProvinceList release];
  [_hotCityList release];
  [_hotRegionList release];
  
  [super dealloc];
}

@end
