#import "AMResultObject.h"


/**
 * 
 */

@implementation AMResultObject

@synthesize errorCode = _errorCode;
@synthesize errorMsg = _errorMsg;
@synthesize success = _success;

- (void) dealloc {
  [_errorCode release];
  [_errorMsg release];
  [_success release];
  
  [super dealloc];
}

@end
