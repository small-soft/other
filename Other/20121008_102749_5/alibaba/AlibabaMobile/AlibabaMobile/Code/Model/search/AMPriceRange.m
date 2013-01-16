
#import "AMPriceRange.h"

@implementation AMPriceRange

@synthesize priceStart = _priceStart;
@synthesize priceEnd = _priceEnd;

- (NSString *) description {
  return [NSString stringWithFormat:@"priceRange:{start:%f,end:%f}" ,self.priceStart, self.priceEnd];
}

- (void) dealloc {
  [_priceStart release];
  [_priceEnd release];
  
  [super dealloc];
}

@end
