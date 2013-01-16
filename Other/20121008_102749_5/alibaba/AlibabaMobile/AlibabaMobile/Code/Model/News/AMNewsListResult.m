#import "AMNewsListResult.h"
#import "AMNewsItem.h"
#import <RestKit/RestKit.h>

@implementation AMNewsListResult

@synthesize total = _total;
@synthesize count = _count;
@synthesize page = _page;
@synthesize newsList = _newsList;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMNewsListResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"total" toAttribute:@"total"];
			[sharedObjectMapping mapKeyPath:@"count" toAttribute:@"count"];
			[sharedObjectMapping mapKeyPath:@"page" toAttribute:@"page"];
			
			[sharedObjectMapping mapRelationship:@"newsList" withMapping:[AMNewsItem sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMNewsItem sharedObjectMapping] forKeyPath:@"newsList"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_total release];
  [_count release];
  [_page release];
  [_newsList release];
  
  [super dealloc];
}

@end
