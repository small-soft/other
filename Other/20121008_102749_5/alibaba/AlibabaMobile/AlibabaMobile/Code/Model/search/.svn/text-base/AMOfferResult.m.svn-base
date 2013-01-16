#import "AMOfferResult.h"

NSInteger const AMDEFAULT = 0;
NSInteger const AMKEYWORDS_EXTEND = 1;
NSInteger const AMKEYWORDS_REWRITE = 2;

@implementation AMOfferResult

@synthesize offerList = _offerList;
@synthesize total = _total;
@synthesize showIndustryAttributes = _showIndustryAttributes;
@synthesize industryAttributes = _industryAttributes;
@synthesize rewriteType = _rewriteType;
@synthesize rewritedKeywords = _rewritedKeywords;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMOfferResult class]] retain];
			[sharedObjectMapping mapKeyPath:@"total" toAttribute:@"total"];
			[sharedObjectMapping mapRelationship:@"offerList" withMapping:[AMOffer sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMOffer sharedObjectMapping] forKeyPath:@"offerList"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
    [_total release];
    [_offerList release];
    [_industryAttributes release]; 
    [_rewritedKeywords release];
    [_rewriteType release];
    [_showIndustryAttributes release];
    
    [super dealloc];
}

@end
