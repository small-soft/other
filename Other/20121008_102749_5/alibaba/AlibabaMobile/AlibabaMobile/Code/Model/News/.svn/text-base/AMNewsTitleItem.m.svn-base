#import "AMNewsTitleItem.h"
#import <RestKit/RestKit.h>

/**
 * 
 */

@implementation AMNewsTitleItem

@synthesize identifier = _identifier;
@synthesize title = _title;
@synthesize keyword = _keyword;
@synthesize areaid = _areaid;
@synthesize publishDate = _publishDate;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMNewsTitleItem class]] retain];
			[sharedObjectMapping mapKeyPath:@"id" toAttribute:@"identifier"];
			[sharedObjectMapping mapKeyPath:@"title" toAttribute:@"title"];
			[sharedObjectMapping mapKeyPath:@"keyword" toAttribute:@"keyword"];
			[sharedObjectMapping mapKeyPath:@"areaid" toAttribute:@"areaid"];
			[sharedObjectMapping mapKeyPath:@"publishDate" toAttribute:@"publishDate"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_identifier release];
  [_title release];
  [_keyword release];
  [_areaid release];
  [_publishDate release];
  
  [super dealloc];
}

@end
