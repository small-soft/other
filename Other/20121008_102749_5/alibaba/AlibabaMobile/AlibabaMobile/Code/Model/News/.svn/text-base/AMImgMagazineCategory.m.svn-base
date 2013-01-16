#import "AMImgMagazineCategory.h"
#import "AMNewsItem.h"
#import <RestKit/RestKit.h>

/**
 * 
 */

@implementation AMImgMagazineCategory

@synthesize categoryId = _categoryId;
@synthesize categoryName = _categoryName;
@synthesize categoryTags = _categoryTags;
@synthesize type = _type;
@synthesize listImgMagazineItem = _listImgMagazineItem;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMImgMagazineCategory class]] retain];
			[sharedObjectMapping mapKeyPath:@"categoryId" toAttribute:@"categoryId"];
			[sharedObjectMapping mapKeyPath:@"categoryName" toAttribute:@"categoryName"];
			[sharedObjectMapping mapKeyPath:@"categoryTags" toAttribute:@"categoryTags"];
			[sharedObjectMapping mapKeyPath:@"type" toAttribute:@"type"];
			
			[sharedObjectMapping mapRelationship:@"listImgMagazineItem" withMapping:[AMNewsItem sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMNewsItem sharedObjectMapping] forKeyPath:@"listImgMagazineItem"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_categoryId release];
  [_categoryName release];
  [_categoryTags release];
  [_type release];
  [_listImgMagazineItem release];
  
  [super dealloc];
}

@end
