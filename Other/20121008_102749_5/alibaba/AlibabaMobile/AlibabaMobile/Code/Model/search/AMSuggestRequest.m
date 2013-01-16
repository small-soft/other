#import "AMSuggestRequest.h"

/**
 * 产品提示
 */
NSString * const AMTYPE_SELL_OFFER = @"selloffer";

/**
 * 公司提示
 */
NSString * const AMTYPE_COMPANY = @"company";

@implementation AMSuggestRequest

@synthesize keyword = _keyword;
@synthesize type = _type;
@synthesize count = _count;

- (void) dealloc {
  [_keyword release];
  [_type release];
  [_count release];
  
  [super dealloc];
}

@end
