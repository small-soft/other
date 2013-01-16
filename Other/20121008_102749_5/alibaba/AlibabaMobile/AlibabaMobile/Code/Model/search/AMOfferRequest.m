#import "AMOfferRequest.h"

#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>

NSString * const AM_SORT_TYPE_BOOKED = @"booked";
NSString * const AM_SORT_TYPE_PRICE = @"price";

@implementation AMOfferRequest

@synthesize transactionType = _transactionType;

@synthesize request = _request;
@synthesize keywords = _keywords;
@synthesize categoryId = _categoryId;
@synthesize categoryName = _categoryName;
@synthesize pop = _pop;
//@synthesize featureMap = _featureMap;
@synthesize province = _province;
@synthesize bizType = _bizType;
@synthesize longitude = _longitude;
@synthesize latitude = _latitude;
@synthesize distance = _distance;
@synthesize pageSize = _pageSize;
@synthesize city = _city;
@synthesize beginPage = _beginPage;
@synthesize priceEnabled = _priceEnabled;
@synthesize priceStart = _priceStart;
@synthesize priceEnd = _priceEnd;
@synthesize sortType = _sortType;
@synthesize descendOrder = _descendOrder;
@synthesize loginId = _loginId;
@synthesize clientId = _clientId;
@synthesize navigationCategoryId = _navigationCategoryId;
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
    
    NSMutableDictionary *wrappedParams = [[[NSMutableDictionary alloc] init] autorelease];
    
    if (self.keywords) {
        NSString *trimmedSpecialCharacters = [self.keywords stringByReplacingOccurrencesOfString:@"+" withString:@" "];
        [wrappedParams setObject: trimmedSpecialCharacters forKey:@"keywords"];
    }
    if (self.categoryId) {
        [wrappedParams setObject:self.categoryId forKey:@"categoryId"];
    }
    if (self.categoryName) {
        [wrappedParams setObject:self.categoryName forKey:@"categoryName"];
    }
    if (self.province) {
        [wrappedParams setObject:self.province forKey:@"province"];
    }
    if (self.bizType) {
        [wrappedParams setObject:self.bizType forKey:@"bizType"];
    }
    if (self.longitude) {
        [wrappedParams setObject:self.longitude forKey:@"longitude"];
    }
    if (self.latitude) {
        [wrappedParams setObject:self.latitude forKey:@"latitude"];
    }
    if (self.distance) {
        [wrappedParams setObject:self.distance forKey:@"distance"];
    }
    if (self.city) {
        [wrappedParams setObject:self.city forKey:@"city"];
    }
    if (self.beginPage) {
        [wrappedParams setObject:self.beginPage forKey:@"beginPage"];
    }
    if (self.pageSize) {
        [wrappedParams setObject:self.pageSize forKey:@"pageSize"];
    }
    
    if (self.priceEnabled) {
        [wrappedParams setObject:self.priceEnabled forKey:@"priceEnabled"];
    }
    if (self.priceStart) {
        [wrappedParams setObject:self.priceStart forKey:@"priceStart"];
    }
    if (self.priceEnd) {
        [wrappedParams setObject:self.priceEnd forKey:@"priceEnd"];
    }
    if (self.pop) {
        [wrappedParams setObject:self.pop forKey:@"pop"];
    }
    if (self.sortType) {
        [wrappedParams setObject:self.sortType forKey:@"sortType"];
    }
    if (self.descendOrder) {
        [wrappedParams setObject:self.descendOrder forKey:@"descendOrder"];
    }
    if (self.loginId) {
        [wrappedParams setObject:self.loginId forKey:@"loginId"];
    }
    if (self.clientId) {
        [wrappedParams setObject:self.clientId forKey:@"clientId"];
    }
    if (self.navigationCategoryId) {
        [wrappedParams setObject:self.navigationCategoryId forKey:@"navigationCategoryId"];
    }
    self.request = wrappedParams;
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMOfferRequest class]];
    [requestMapping mapKeyPath:@"request" toAttribute:@"request"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString * _data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_SEARCH_OFFER params:params];
    NSLog(@"search offer list = http://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile/search.offer.listOffer/5005?%@",signedBodyString);
    [params release];

    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    [_keywords release];
    [_categoryId release];
    [_categoryName release];
    //[_featureMap release];
    [_province release];
    [_city release];
    [_bizType release];
    [_longitude release];
    [_latitude release];
    [_distance release];
    [_sortType release];
    [_pageSize release];
    [_beginPage release];
    [_pop release];
    [_priceStart release];
    [_priceEnd release];
    [_priceEnabled release];
    [_descendOrder release];
    [_request release];
    [_loginId release];
    [_clientId release];
    [_navigationCategoryId release];
    [super dealloc];
}

@end
