#import "AMCUDFavoriteRequest.h"
#import <RestKit/RestKit.h>

/**
 * 
 */

@implementation AMCUDFavoriteRequest

@synthesize memberId = _memberId;
@synthesize themeId = _themeId;
@synthesize area = _area;
@synthesize sourceFromId = _sourceFromId;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCUDFavoriteRequest class]] retain];
			[sharedObjectMapping mapKeyPath:@"memberId" toAttribute:@"memberId"];
			[sharedObjectMapping mapKeyPath:@"themeId" toAttribute:@"themeId"];
			[sharedObjectMapping mapKeyPath:@"area" toAttribute:@"area"];
			[sharedObjectMapping mapKeyPath:@"sourceFromId" toAttribute:@"sourceFromId"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_memberId release];
  [_themeId release];
  [_area release];
  [_sourceFromId release];
  
  [super dealloc];
}

@end
