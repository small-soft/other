#import "AMCompanyRequest.h"

#import "ConstDef.h"
#import "SecurityUtil.h"
#import <RestKit/RestKit.h>

@implementation AMCompanyRequest

@synthesize request = _request;
@synthesize keywords = _keywords;
@synthesize categoryId = _categoryId;
@synthesize categoryName = _categoryName;
@synthesize province = _province;
@synthesize bizType = _bizType;
@synthesize longitude = _longitude;
@synthesize latitude = _latitude;
@synthesize distance = _distance;
@synthesize pageSize = _pageSize;
@synthesize city = _city;
@synthesize beginPage = _beginPage;

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
        [wrappedParams setObject: self.keywords forKey:@"keywords"];
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

    self.request = wrappedParams;
    
    RKObjectMapping* requestMapping = [RKObjectMapping mappingForClass:[AMCompanyRequest class]];
    [requestMapping mapKeyPath:@"request" toAttribute:@"request"];
    
    RKObjectSerializer* serializer = [RKObjectSerializer serializerWithObject:self mapping:requestMapping];
    NSError *error = nil;
    NSString * _data_ = [serializer serializedObjectForMIMEType:RKMIMETypeJSON error: &error];
    
    // Create NSDictionary object and setObject to it
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    [params setObject: _data_ forKey: @"_data_"];
    NSString *signedBodyString = [SecurityUtil generateSignedRequest:AMCONST_OCEAN_PREFIX resourcePath:OCEAN_API_URL_SEARCH_COMPANY params:params];
    
    [params release];
    
    return [signedBodyString dataUsingEncoding: NSUTF8StringEncoding];
}

- (void) dealloc {
    [_keywords release];
    [_categoryId release];
    [_categoryName release];
    [_province release];
    [_city release];
    [_bizType release];
    [_longitude release];
    [_latitude release];
    [_distance release];
    [_beginPage release];
    [_pageSize release];
    [_request release];
    
    [super dealloc];
}

@end
