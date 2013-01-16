#import "AMFavoriteBaseItem.h"
#import "AMFavoriteTag.h"
#import <RestKit/RestKit.h>

NSString * const FAVORITE_ADD_CONTENT_HAS_EXISTED = @"CONTENT_HAS_EXISTED";
NSString * const FAVORITE_ADD_STORAGE_HAS_FULL = @"STORAGE_HAS_FULL";

/**
 * 
 */

@implementation AMFavoriteBaseItem

@synthesize collectedCount = _collectedCount;
@synthesize favoriteTaglList = _favoriteTaglList;
@synthesize favoriteId = _favoriteId;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMFavoriteBaseItem class]] retain];
			[sharedObjectMapping mapKeyPath:@"collectedCount" toAttribute:@"collectedCount"];
			[sharedObjectMapping mapKeyPath:@"favoriteId" toAttribute:@"favoriteId"];
			
			[sharedObjectMapping mapRelationship:@"favoriteTaglList" withMapping:[AMFavoriteTag sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMFavoriteTag sharedObjectMapping] forKeyPath:@"favoriteTaglList"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_collectedCount release];
  [_favoriteId release];
  [_favoriteTaglList release];
  
  [super dealloc];
}

@end
