#import "AMOfferFavoriteListResult.h"
#import "AMFavoriteOffer.h"
#import <RestKit/RestKit.h>

/**
 * 
 */

@implementation AMOfferFavoriteListResult

@synthesize totalCount = _totalCount;
@synthesize pagecount = _pagecount;
@synthesize pageindex = _pageindex;
@synthesize resultList = _resultList;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMOfferFavoriteListResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"totalCount" toAttribute:@"totalCount"];
			[sharedObjectMapping mapKeyPath:@"pagecount" toAttribute:@"pagecount"];
			[sharedObjectMapping mapKeyPath:@"pageindex" toAttribute:@"pageindex"];
			
			[sharedObjectMapping mapRelationship:@"resultList" withMapping:[AMFavoriteOffer sharedObjectMapping]];
			
			// Setup object mapping
//			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
//			[mappingProvider setMapping:[AMFavoriteOffer sharedObjectMapping] forKeyPath:@"resultList"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_totalCount release];
  [_pagecount release];
  [_resultList release];
  [_pageindex release];
  
  [super dealloc];
}

@end
