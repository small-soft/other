#import "AMLogisTraceStep.h"
#import <RestKit/RestKit.h>

@implementation AMLogisTraceStep

@synthesize acceptTime = _acceptTime;
@synthesize remark = _remark;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMLogisTraceStep class]] retain];
			[sharedObjectMapping mapKeyPath:@"acceptTime" toAttribute:@"acceptTime"];
			[sharedObjectMapping mapKeyPath:@"remark" toAttribute:@"remark"];
        }
    }
    
    return sharedObjectMapping;
}

- (NSString*)description {
    return [NSString stringWithFormat:@"remark: %@ (acceptTime: %@)", self.remark, self.acceptTime];
}

- (void) dealloc {
  [_acceptTime release];
  [_remark release];
  
  [super dealloc];
}

@end
