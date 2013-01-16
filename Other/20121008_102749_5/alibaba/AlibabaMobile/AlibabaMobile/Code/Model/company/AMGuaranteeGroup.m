#import "AMGuaranteeGroup.h"
#import "AMGuaranteeGroupMember.h"

@implementation AMGuaranteeGroup

@synthesize groupSize = _groupSize;
@synthesize groupLevel = _groupLevel;
@synthesize againCanJoinCount = _againCanJoinCount;
@synthesize gmtOpened = _gmtOpened;
@synthesize groupType = _groupType;
@synthesize status = _status;
@synthesize groupMemberList = _groupMemberList;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMGuaranteeGroup class]] retain];
			
			// Super class
			[sharedObjectMapping mapKeyPath:@"groupSize" toAttribute:@"groupSize"];
            [sharedObjectMapping mapKeyPath:@"groupLevel" toAttribute:@"groupLevel"];
            [sharedObjectMapping mapKeyPath:@"againCanJoinCount" toAttribute:@"againCanJoinCount"];
            [sharedObjectMapping mapKeyPath:@"gmtOpened" toAttribute:@"gmtOpened"];
            [sharedObjectMapping mapKeyPath:@"groupType" toAttribute:@"groupType"];
            [sharedObjectMapping mapKeyPath:@"status" toAttribute:@"status"];
            [sharedObjectMapping mapRelationship:@"groupMemberList" withMapping:[AMGuaranteeGroupMember sharedObjectMapping]];

            
            RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			// For Super class
			[mappingProvider setMapping:[AMGuaranteeGroupMember sharedObjectMapping] forKeyPath:@"groupMemberList"];
        }
    }
    
    return sharedObjectMapping;
}


- (void) dealloc {
  [_gmtOpened release];
  [_groupSize release];
  [_groupType release];
  [_groupLevel release];
  [_againCanJoinCount release];
  [_status release];
  [_groupMemberList release];
  
  [super dealloc];
}

@end
