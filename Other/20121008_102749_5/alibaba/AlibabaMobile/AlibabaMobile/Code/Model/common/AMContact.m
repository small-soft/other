#import "AMContact.h"
#import <RestKit/RestKit.h>

@implementation AMContact

@synthesize phone = _phone;
@synthesize mobile = _mobile;
@synthesize fax = _fax;
@synthesize homepage = _homepage;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMContact class]] retain];
            [sharedObjectMapping mapKeyPath:@"phone" toAttribute:@"phone"];
            [sharedObjectMapping mapKeyPath:@"mobile" toAttribute:@"mobile"];
            [sharedObjectMapping mapKeyPath:@"fax" toAttribute:@"fax"];
            [sharedObjectMapping mapKeyPath:@"homepage" toAttribute:@"homepage"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_phone release];
  [_mobile release];
  [_fax release];
  [_homepage release];
  
  [super dealloc];
}

@end
