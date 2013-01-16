#import "AMCompanyFavoriteListResult.h"
#import "AMFavoriteCompany.h"
#import <RestKit/RestKit.h>

/**
 * 
 */

@implementation AMCompanyFavoriteListResult

@synthesize totalCount = _totalCount;
@synthesize pagecount = _pagecount;
@synthesize pageindex = _pageindex;
@synthesize resultList = _resultList;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCompanyFavoriteListResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"totalCount" toAttribute:@"totalCount"];
			[sharedObjectMapping mapKeyPath:@"pagecount" toAttribute:@"pagecount"];
			[sharedObjectMapping mapKeyPath:@"pageindex" toAttribute:@"pageindex"];
			
			[sharedObjectMapping mapRelationship:@"resultList" withMapping:[AMFavoriteCompany sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMFavoriteCompany sharedObjectMapping] forKeyPath:@"resultList"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
	[_totalCount release];
	[_pagecount release];
	[_pageindex release];
	[_resultList release];
	
	[super dealloc];
}

@end
