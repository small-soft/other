#import "AMMobileMessageQueryResult.h"
#import "AMMobileMessage.h"
#import <RestKit/RestKit.h>

@implementation AMMobileMessageQueryResult

@synthesize totalCount = _totalCount;
@synthesize resultCount = _resultCount;
@synthesize messages = _messages;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMMobileMessageQueryResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"totalCount" toAttribute:@"totalCount"];
			[sharedObjectMapping mapKeyPath:@"resultCount" toAttribute:@"resultCount"];
			
			[sharedObjectMapping mapRelationship:@"messages" withMapping:[AMMobileMessage sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMMobileMessage sharedObjectMapping] forKeyPath:@"messages"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_totalCount release];
  [_resultCount release];
  [_messages release];
  
  [super dealloc];
}

@end
