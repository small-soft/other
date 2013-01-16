#import "AMPerson.h"
#import <RestKit/RestKit.h>

@implementation AMPerson

@synthesize identifier = _identifier;
@synthesize name = _name;
@synthesize gender = _gender;
@synthesize jobTitle = _jobTitle;
@synthesize wwCode = _wwCode;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMPerson class]] retain];
            [sharedObjectMapping mapKeyPath:@"id" toAttribute:@"identifier"];
            [sharedObjectMapping mapKeyPath:@"name" toAttribute:@"name"];
            [sharedObjectMapping mapKeyPath:@"gender" toAttribute:@"gender"];
            [sharedObjectMapping mapKeyPath:@"jobTitle" toAttribute:@"jobTitle"];
			[sharedObjectMapping mapKeyPath:@"wwCode" toAttribute:@"wwCode"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_identifier release];
  [_name release];
  [_gender release];
  [_jobTitle release];
  [_wwCode release];
  
  [super dealloc];
}

@end
