#import "AMRecentOfferSearch.h"

@implementation AMRecentOfferSearch

@synthesize zeroResult = _zeroResult;

- (void) dealloc {
	[_zeroResult release];
	
	[super dealloc];
}

@end
