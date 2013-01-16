#import "AMImgMagazineRequest.h"
#import "ConstDef.h"
#import "SecurityUtil.h"

@implementation AMImgMagazineRequest

@synthesize transactionType = _transactionType;

@synthesize categoryid = _categoryid;
@synthesize page = _page;
@synthesize count = _count;

@synthesize requestURL;

-(id)init {
    [super init];
  if (self) {
    self.page = [NSNumber numberWithInt: 1];
    self.count = [NSNumber numberWithInt: 20];
	
    self.requestURL = OCEAN_API_URL_MAGAZINE_CATEGORIES;
  }
    return self;
}

// Impliment RKRequestSerializable delegate methods here

/**
 * The value of the Content-Type header for the HTTP Body representation of the serialization
 */
- (NSString*)HTTPHeaderValueForContentType {
    return @"application/x-www-form-urlencoded";
}

/**
 * An NSData representing the HTTP Body serialization of the object implementing the protocol
 */
- (NSData*)HTTPBody {

    NSString *signedBodyString = nil;

	if(self.transactionType == (int)OCEAN_API_URL_MAGAZINE_CATEGORIES) {
		signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:self.requestURL params:nil];
	}else{
		NSString *_data_ = [NSString stringWithFormat: @"{request:{page:%@,count:%@,categoryid:\"%@\"}}", self.page, self.count, self.categoryid];

		// Create NSDictionary object and setObject to it
		NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
		[params setObject: _data_ forKey: @"_data_"];
		signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:self.requestURL params:params];
        [params release];
	}
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
  [_categoryid release];
  [_page release];
  [_count release];
    
  self.requestURL = nil;
  
  [super dealloc];
}

@end
