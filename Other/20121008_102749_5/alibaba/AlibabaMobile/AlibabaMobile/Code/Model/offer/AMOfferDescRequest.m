#import "AMOfferDescRequest.h"
#import "AMImageSizeType.h"


/**
 * 
 */

@implementation AMOfferDescRequest

@synthesize imageSizeType = _imageSizeType;
@synthesize disableLink = _disableLink;

-(void) dealloc {
  [_imageSizeType release];
  [_disableLink release];
  
  [super dealloc];
}

@end
