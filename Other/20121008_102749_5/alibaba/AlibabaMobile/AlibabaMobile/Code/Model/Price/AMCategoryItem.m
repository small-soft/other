#import "AMCategoryItem.h"


/**
 * 
 */

@implementation AMCategoryItem

@synthesize industryName = _industryName;
@synthesize industryId = _industryId;

- (void) dealloc {
  [_industryName release];
  [_industryId release];
  
  [super dealloc];
}

@end
