#import "AMSmartNavigationResult.h"
#import "AMCategorySub.h"
@implementation AMSmartNavigationResult

@synthesize categories = _categories;
@synthesize features = _features;
@synthesize priceRanges = _priceRanges;
@synthesize requestCategory = _requestCategory;
@synthesize requestFeatures = _requestFeatures;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMSmartNavigationResult class]] retain];
			[sharedObjectMapping mapRelationship:@"categories" withMapping:[AMCategorySub sharedObjectMapping]];
           
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMCategorySub sharedObjectMapping] forKeyPath:@"categories"];
        }
    }
    
    return sharedObjectMapping;
}



- (void) dealloc {
  [_categories release];
  [_features release];
  [_priceRanges release];
  [_requestFeatures release];
  [_requestCategory release];
  
  [super dealloc];
}

@end
