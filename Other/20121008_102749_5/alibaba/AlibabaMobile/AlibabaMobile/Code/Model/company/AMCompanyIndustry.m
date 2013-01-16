#import "AMCompanyIndustry.h"

@implementation AMCompanyIndustry

@synthesize factorySize = _factorySize;
@synthesize annualRevenue = _annualRevenue;
@synthesize manufactureType = _manufactureType;
@synthesize productionCapacity = _productionCapacity;
@synthesize productionUnit = _productionUnit;
@synthesize warehouseArea = _warehouseArea;
@synthesize technologyType = _technologyType;
@synthesize tradeRegion = _tradeRegion;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCompanyIndustry class]] retain];
			[sharedObjectMapping mapKeyPath:@"factorySize" toAttribute:@"factorySize"];
			[sharedObjectMapping mapKeyPath:@"annualRevenue" toAttribute:@"annualRevenue"];   
			[sharedObjectMapping mapKeyPath:@"manufactureType" toAttribute:@"manufactureType"];
			[sharedObjectMapping mapKeyPath:@"productionCapacity" toAttribute:@"productionCapacity"]; 
			
			[sharedObjectMapping mapKeyPath:@"productionUnit" toAttribute:@"productionUnit"];
			[sharedObjectMapping mapKeyPath:@"warehouseArea" toAttribute:@"warehouseArea"];   
			[sharedObjectMapping mapKeyPath:@"technologyType" toAttribute:@"technologyType"];
			[sharedObjectMapping mapKeyPath:@"tradeRegion" toAttribute:@"tradeRegion"]; 
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_factorySize release];
  [_annualRevenue release];
  [_manufactureType release];
  [_productionCapacity release];
  [_productionUnit release];
  [_warehouseArea release];
  [_technologyType release];
  [_tradeRegion release];
  
  [super dealloc];
}

@end
