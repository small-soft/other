#import "AMCUDResult.h"

NSString * const AMFAVORITE_ADD_EXISTS = @"1";
NSString * const AMFAVORITE_ADD_OVER_MAXLIMITED = @"2";
NSString * const AMFAVORITE_ADD_FAIL = @"3";

/**
 * 
 */

@implementation AMCUDResult

@synthesize resultCode = _resultCode;
@synthesize success = _success;

- (void) dealloc {
  [_resultCode release];
  [_success release];
  
  [super dealloc];
}

@end
