#import "AMTradeInfo.h"
#import <RestKit/RestKit.h>

/**
 * 
 */

@implementation AMTradeInfo

@synthesize etcEnable = _etcEnable;
@synthesize prechargeEnable = _prechargeEnable;
@synthesize instantEnable = _instantEnable;
@synthesize assureEnable = _assureEnable;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMTradeInfo class]] retain];
            [sharedObjectMapping mapKeyPath:@"etcEnable" toAttribute:@"etcEnable"];
            [sharedObjectMapping mapKeyPath:@"prechargeEnable" toAttribute:@"prechargeEnable"];
            [sharedObjectMapping mapKeyPath:@"instantEnable" toAttribute:@"instantEnable"];
            [sharedObjectMapping mapKeyPath:@"assureEnable" toAttribute:@"assureEnable"];
        }
    }
    
    return sharedObjectMapping;
}

-(void) dealloc {
  [_etcEnable release];
  [_prechargeEnable release];
  [_instantEnable release];
  [_assureEnable release];
  
  [super dealloc];
}

@end
