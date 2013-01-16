#import "AMNewsTitle.h"
#import "AMNewsTitleItem.h"
#import <RestKit/RestKit.h>

/**
 * 
 */

@implementation AMNewsTitle

@synthesize categoryItem = _categoryItem;
@synthesize newsTitleItem = _newsTitleItem;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMNewsTitle class]] retain];
			[sharedObjectMapping mapRelationship:@"categoryItem" withMapping:[AMNewsTitleItem sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"newsTitleItem" withMapping:[AMNewsTitleItem sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMNewsTitleItem sharedObjectMapping] forKeyPath:@"categoryItem"];
			[mappingProvider setMapping:[AMNewsTitleItem sharedObjectMapping] forKeyPath:@"newsTitleItem"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_categoryItem release];
  [_newsTitleItem release];
  
  [super dealloc];
}

@end
