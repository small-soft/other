#import "AMLogisSimpleOrder.h"
#import "AMLogisTraceStep.h"

@implementation AMLogisSimpleOrder

@synthesize logisticsID = _logisticsID;
@synthesize mailNo = _mailNo;
@synthesize logisticsCompanyid = _logisticsCompanyid;
@synthesize logisticsCorpName = _logisticsCorpName;
@synthesize receiverCorpName = _receiverCorpName;
@synthesize receiverName = _receiverName;
@synthesize cargoName = _cargoName;
@synthesize totalNumber = _totalNumber;
@synthesize totalWeight = _totalWeight;
@synthesize totalVolume = _totalVolume;
@synthesize aliUID = _aliUID;
@synthesize tradeOrderId = _tradeOrderId;
@synthesize newestTraceStep = _newestTraceStep;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMLogisSimpleOrder class]] retain];
			[sharedObjectMapping mapKeyPath:@"logisticsID" toAttribute:@"logisticsID"];
			[sharedObjectMapping mapKeyPath:@"mailNo" toAttribute:@"mailNo"];
			[sharedObjectMapping mapKeyPath:@"logisticsCompanyid" toAttribute:@"logisticsCompanyid"];
			[sharedObjectMapping mapKeyPath:@"logisticsCorpName" toAttribute:@"logisticsCorpName"];
			[sharedObjectMapping mapKeyPath:@"receiverCorpName" toAttribute:@"receiverCorpName"];
			[sharedObjectMapping mapKeyPath:@"receiverName" toAttribute:@"receiverName"];
			[sharedObjectMapping mapKeyPath:@"cargoName" toAttribute:@"cargoName"];
			[sharedObjectMapping mapKeyPath:@"totalNumber" toAttribute:@"totalNumber"];
			[sharedObjectMapping mapKeyPath:@"totalWeight" toAttribute:@"totalWeight"];
			[sharedObjectMapping mapKeyPath:@"totalVolume" toAttribute:@"totalVolume"];
			[sharedObjectMapping mapKeyPath:@"aliUID" toAttribute:@"aliUID"];
			[sharedObjectMapping mapKeyPath:@"tradeOrderId" toAttribute:@"tradeOrderId"];
			
			[sharedObjectMapping mapRelationship:@"newestTraceStep" withMapping:[AMLogisTraceStep sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMLogisTraceStep sharedObjectMapping] forKeyPath:@"newestTraceStep"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_logisticsID release];
  [_mailNo release];
  [_logisticsCompanyid release];
  [_logisticsCorpName release];
  [_receiverCorpName release];
  [_receiverName release];
  [_cargoName release];
  [_aliUID release];
  [_tradeOrderId release];
  [_newestTraceStep release];
  [_totalNumber release];
  [_totalWeight release];
  [_totalVolume release];
  
  [super dealloc];
}

@end
