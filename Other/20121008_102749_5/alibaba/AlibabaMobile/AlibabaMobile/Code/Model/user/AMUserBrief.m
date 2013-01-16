#import "AMUserBrief.h"

@implementation AMUserBrief

@synthesize contact = _contact;
@synthesize companyName = _companyName;
@synthesize penName = _penName;
@synthesize headPic = _headPic;
@synthesize address = _address;

- (void) dealloc {
  [_contact release];
  [_address release];
  [_companyName release];
  [_penName release];
  [_headPic release];
    
  [super dealloc];
}

@end
