#import "AMFavoritePriceItemV2.h"

/**
 * 
 */
@implementation AMFavoritePriceItemV2

@synthesize favoriteId;

- (void) dealloc {
  [_favoriteId release];
  
  [super dealloc];
}

@end
