#import "AMPriceResult.h"

@implementation AMPriceItem

@synthesize attributes = _attributes;
@synthesize updown = _updown;
@synthesize sourceFromName= _sourceFromName;
@synthesize priceDate= _priceDate;
@synthesize price=_price;
@synthesize areaName= _areaName;
@synthesize sourceFromId= _sourceFromId;
@synthesize themeId= _themeId;
@synthesize description= _description;
@synthesize themeName= _themeName;
@synthesize areaId= _areaId;
@synthesize valid = _valid;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMPriceItem class]] retain];
			[sharedObjectMapping mapKeyPath:@"sourceFromName" toAttribute:@"sourceFromName"];
			[sharedObjectMapping mapKeyPath:@"priceDate" toAttribute:@"priceDate"];
			[sharedObjectMapping mapKeyPath:@"price" toAttribute:@"price"];
			[sharedObjectMapping mapKeyPath:@"areaName" toAttribute:@"areaName"];
			[sharedObjectMapping mapKeyPath:@"themeId" toAttribute:@"themeId"];
			[sharedObjectMapping mapKeyPath:@"sourceFromId" toAttribute:@"sourceFromId"];
			[sharedObjectMapping mapKeyPath:@"description" toAttribute:@"description"];
			[sharedObjectMapping mapKeyPath:@"themeName" toAttribute:@"themeName"];
			[sharedObjectMapping mapKeyPath:@"updown" toAttribute:@"updown"];
			[sharedObjectMapping mapKeyPath:@"areaId" toAttribute:@"areaId"];
			[sharedObjectMapping mapKeyPath:@"attribute" toAttribute:@"attributes"];
            [sharedObjectMapping mapKeyPath:@"valid" toAttribute:@"_valid"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_sourceFromName release];
  [_priceDate release];
  [_price release];
  [_areaName release];
  [_sourceFromId release];
  [_themeId release];
  [_description release];
  [_themeName release];
  [_areaId release];
  [_attributes release];
    [_valid release];
  
  [super dealloc];
}

@end


/**
 * 
 */

@implementation AMPriceResult

@synthesize total = _total;
@synthesize count = _count;
@synthesize page = _page;
@synthesize priceList = _priceList;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMPriceResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"total" toAttribute:@"total"];
			[sharedObjectMapping mapKeyPath:@"count" toAttribute:@"count"];
			[sharedObjectMapping mapKeyPath:@"page" toAttribute:@"page"];

			[sharedObjectMapping mapRelationship:@"priceList" withMapping:[AMPriceItem sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMPriceItem sharedObjectMapping] forKeyPath:@"priceList"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_total release];
  [_count release];
  [_page release];
  [_priceList release];
  
  [super dealloc];
}

@end
