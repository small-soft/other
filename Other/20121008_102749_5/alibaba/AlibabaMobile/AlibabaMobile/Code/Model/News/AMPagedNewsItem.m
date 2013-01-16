#import "AMPagedNewsItem.h"
#import <RestKit/RestKit.h>

/**
 * 
 */

@implementation AMPagedNewsItem

@synthesize pagedContent = _pagedContent;
@synthesize newsItem = _newsItem;
@synthesize pageCount = _pageCount;
@synthesize pageSize = _pageSize;

- (void) dealloc {
  [_newsItem release];
  [_pagedContent release];
  [_pageCount release];
  [_pageSize release];
  
  [super dealloc];
}

@end
