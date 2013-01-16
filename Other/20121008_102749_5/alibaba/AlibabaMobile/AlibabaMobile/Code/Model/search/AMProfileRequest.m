#import "AMProfileRequest.h"

@implementation AMProfileRequest

@synthesize memberId = _memberId;
@synthesize cookieId = _cookieId;

- (void) dealloc {
  [_memberId release];
  [_cookieId release];
  
  [super dealloc];
}

@end
