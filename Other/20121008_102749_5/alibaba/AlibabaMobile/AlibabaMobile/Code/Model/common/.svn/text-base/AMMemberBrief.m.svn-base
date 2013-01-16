#import "AMMemberBrief.h"
#import <RestKit/RestKit.h>

@implementation AMMemberBrief

@synthesize name = _name;
@synthesize bizType = _bizType;
@synthesize creditBase = _creditBase;
@synthesize contact = _contact;
@synthesize person = _person;
@synthesize memberType = _memberType;
@synthesize statusEnabled = _statusEnabled;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMMemberBrief class]] retain];
            [sharedObjectMapping mapKeyPath:@"bizType" toAttribute:@"bizType"];
            [sharedObjectMapping mapKeyPath:@"name" toAttribute:@"name"];
            [sharedObjectMapping mapKeyPath:@"memberType" toAttribute:@"memberType"];
            [sharedObjectMapping mapKeyPath:@"statusEnabled" toAttribute:@"statusEnabled"];
			
			[sharedObjectMapping mapRelationship:@"creditBase" withMapping:[AMCreditBase sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"contact" withMapping:[AMContact sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"person" withMapping:[AMPerson sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMCreditBase sharedObjectMapping] forKeyPath:@"creditBase"];
			[mappingProvider setMapping:[AMContact sharedObjectMapping] forKeyPath:@"contact"];
			[mappingProvider setMapping:[AMPerson sharedObjectMapping] forKeyPath:@"person"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_name release];
  [_bizType release];
  [_memberType release];
  [_creditBase release];
  [_contact release];
  [_person release];
  [_statusEnabled release];
    
  [super dealloc];
}

@end
