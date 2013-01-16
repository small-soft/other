#import "AMFavoriteTag.h"
#import <RestKit/RestKit.h>

/**
 * 
 */

@implementation AMFavoriteTag

@synthesize identifier = _identifier;
@synthesize tagCount = _tagCount;
@synthesize memberId = _memberId;
@synthesize tagName = _tagName;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMFavoriteTag class]] retain];
			[sharedObjectMapping mapKeyPath:@"id" toAttribute:@"identifier"];
			[sharedObjectMapping mapKeyPath:@"tagCount" toAttribute:@"tagCount"];
			[sharedObjectMapping mapKeyPath:@"memberId" toAttribute:@"memberId"];
			[sharedObjectMapping mapKeyPath:@"tagName" toAttribute:@"tagName"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_identifier release];
  [_tagCount release];
  [_memberId release];
  [_tagName release];
  
  [super dealloc];
}

@end
