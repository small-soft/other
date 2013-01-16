#import "AMOffer.h"

@implementation AMOffer

@synthesize brief = _brief;
@synthesize province = _province;
@synthesize city = _city;
@synthesize detailImgUrl = _detailImgUrl;
@synthesize detailUrl = _detailUrl;
@synthesize listImgUrl = _listImgUrl;
@synthesize image = _image;
@synthesize offerId = _offerId;
@synthesize memberId = _memberId;
@synthesize price = _price;
@synthesize rmbPrice = _rmbPrice;
@synthesize quantityBegin = _quantityBegin;
@synthesize subject = _subject;
@synthesize creditInfo = _creditInfo;
@synthesize longitude = _longitude;
@synthesize latitude = _latitude;
@synthesize useAlipay = _useAlipay;
@synthesize company = _company;
@synthesize unit = _unit;
@synthesize mixWholesale = _mixWholesale;
@synthesize retailWholesale = _retailWholesale;
@synthesize bookedCount = _bookedCount;
@synthesize evaluateCounts = _evaluateCounts;
@synthesize aliwwStatus = _aliwwStatus;
@synthesize industryAttributes = _industryAttributes;
@synthesize companyId = _companyId;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMOffer class]] retain];
			[sharedObjectMapping mapKeyPath:@"brief" toAttribute:@"brief"];
			[sharedObjectMapping mapKeyPath:@"province" toAttribute:@"province"];
			[sharedObjectMapping mapKeyPath:@"city" toAttribute:@"city"];
			[sharedObjectMapping mapKeyPath:@"detailImgUrl" toAttribute:@"detailImgUrl"];
			[sharedObjectMapping mapKeyPath:@"detailUrl" toAttribute:@"detailUrl"];
			[sharedObjectMapping mapKeyPath:@"listImgUrl" toAttribute:@"listImgUrl"];
			[sharedObjectMapping mapKeyPath:@"offerId" toAttribute:@"offerId"];
			[sharedObjectMapping mapKeyPath:@"memberId" toAttribute:@"memberId"];
			[sharedObjectMapping mapKeyPath:@"quantityBegin" toAttribute:@"quantityBegin"];
			[sharedObjectMapping mapKeyPath:@"subject" toAttribute:@"subject"];
			[sharedObjectMapping mapKeyPath:@"longitude" toAttribute:@"longitude"];
			[sharedObjectMapping mapKeyPath:@"latitude" toAttribute:@"latitude"];
			[sharedObjectMapping mapKeyPath:@"useAlipay" toAttribute:@"useAlipay"];
			[sharedObjectMapping mapKeyPath:@"company" toAttribute:@"company"];	
			[sharedObjectMapping mapKeyPath:@"unit" toAttribute:@"unit"];	
			[sharedObjectMapping mapKeyPath:@"mixWholesale" toAttribute:@"mixWholesale"];	
			[sharedObjectMapping mapKeyPath:@"retailWholesale" toAttribute:@"retailWholesale"];	
			[sharedObjectMapping mapKeyPath:@"bookedCount" toAttribute:@"bookedCount"];	
			[sharedObjectMapping mapKeyPath:@"evaluateCounts" toAttribute:@"evaluateCounts"];	
			[sharedObjectMapping mapKeyPath:@"aliwwStatus" toAttribute:@"aliwwStatus"];	
			[sharedObjectMapping mapKeyPath:@"industryAttributes" toAttribute:@"industryAttributes"];	
			[sharedObjectMapping mapKeyPath:@"companyId" toAttribute:@"companyId"];	
			
			[sharedObjectMapping mapRelationship:@"image" withMapping: [AMImage sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"price" withMapping:[AMMoney sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"rmbPrice" withMapping:[AMMoney sharedObjectMapping]];
			[sharedObjectMapping mapRelationship:@"creditInfo" withMapping:[AMMemberCredit sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMMoney sharedObjectMapping] forKeyPath:@"price"];
			[mappingProvider setMapping:[AMMoney sharedObjectMapping] forKeyPath:@"rmbPrice"];
			[mappingProvider setMapping:[AMImage sharedObjectMapping] forKeyPath:@"image"];
			[mappingProvider setMapping:[AMMemberCredit sharedObjectMapping] forKeyPath:@"creditInfo"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_brief release];
  [_province release];
  [_city release];
  [_company release];
  [_detailImgUrl release];
  [_detailUrl release];
  [_listImgUrl release];
  [_image release];
    [_offerId release];
  [_memberId release];
  [_price release];
  [_rmbPrice release];
  [_quantityBegin release];
  [_unit release];
  [_subject release];
  [_creditInfo release];
  [_longitude release];
  [_latitude release];
    [_useAlipay release];
    [_mixWholesale release];
  [_industryAttributes release];
    
  [super dealloc];
}

@end
