#import "AMPriceBaseItem.h"

/**
 * 
 */
NSString * const FAVORITE_ADD_PRICE_EXISTS = @"1";
NSString * const FAVORITE_ADD_PRICE_OVER_MAXLIMITED = @"2";

@implementation AMPriceBaseItem

@synthesize identifier = _identifier;
@synthesize name = _name;

- (void) dealloc {
  [_identifier release];
  [_name release];
  
  [super dealloc];
}

@end
