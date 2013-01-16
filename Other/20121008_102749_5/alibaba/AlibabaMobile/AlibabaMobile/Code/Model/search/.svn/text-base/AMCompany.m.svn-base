#import "AMCompany.h"


@implementation AMCompany

@synthesize name = _name;
@synthesize homepageUrl = _homepageUrl;
@synthesize contact = _contact;
@synthesize mobileNumber = _mobileNumber;
@synthesize firstBizTypeName = _firstBizTypeName;
@synthesize packageName = _packageName;
@synthesize phoneAreaCode = _phoneAreaCode;
@synthesize phoneNumber = _phoneNumber;
@synthesize productionService = _productionService;
@synthesize productionServiceShort = _productionServiceShort;
@synthesize trustLogo = _trustLogo;
@synthesize creditInfo = _creditInfo;
@synthesize memberId = _memberId;
@synthesize establishedYear = _establishedYear;
@synthesize address = _address;
@synthesize foundedPlace = _foundedPlace;
@synthesize bizPlace = _bizPlace;
@synthesize trustScore = _trustScore;
@synthesize principal = _principal;
@synthesize province = _province;
@synthesize city = _city;
@synthesize longitude = _longitude;
@synthesize latitude = _latitude;
@synthesize aliwwStatus = _aliwwStatus;
@synthesize identifier = _identifier;
@synthesize regCapital=_regCapital;
+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCompany class]] retain];
			[sharedObjectMapping mapKeyPath:@"name" toAttribute:@"name"];
			[sharedObjectMapping mapKeyPath:@"homepageUrl" toAttribute:@"homepageUrl"];
			[sharedObjectMapping mapKeyPath:@"contact" toAttribute:@"contact"];
			[sharedObjectMapping mapKeyPath:@"mobileNumber" toAttribute:@"mobileNumber"];
			[sharedObjectMapping mapKeyPath:@"firstBizTypeName" toAttribute:@"firstBizTypeName"];
			[sharedObjectMapping mapKeyPath:@"packageName" toAttribute:@"packageName"];
			[sharedObjectMapping mapKeyPath:@"phoneAreaCode" toAttribute:@"phoneAreaCode"];
			[sharedObjectMapping mapKeyPath:@"phoneNumber" toAttribute:@"phoneNumber"];
			[sharedObjectMapping mapKeyPath:@"productionService" toAttribute:@"productionService"];
			[sharedObjectMapping mapKeyPath:@"productionServiceShort" toAttribute:@"productionServiceShort"];
			[sharedObjectMapping mapKeyPath:@"trustLogo" toAttribute:@"trustLogo"];
			[sharedObjectMapping mapKeyPath:@"memberId" toAttribute:@"memberId"];
			[sharedObjectMapping mapKeyPath:@"establishedYear" toAttribute:@"establishedYear"];
			[sharedObjectMapping mapKeyPath:@"address" toAttribute:@"address"];	
			[sharedObjectMapping mapKeyPath:@"foundedPlace" toAttribute:@"foundedPlace"];	
			[sharedObjectMapping mapKeyPath:@"bizPlace" toAttribute:@"bizPlace"];	
			[sharedObjectMapping mapKeyPath:@"trustScore" toAttribute:@"trustScore"];	
			[sharedObjectMapping mapKeyPath:@"principal" toAttribute:@"principal"];	
			[sharedObjectMapping mapKeyPath:@"province" toAttribute:@"province"];	
			[sharedObjectMapping mapKeyPath:@"city" toAttribute:@"city"];	
			[sharedObjectMapping mapKeyPath:@"longitude" toAttribute:@"longitude"];	
			[sharedObjectMapping mapKeyPath:@"latitude" toAttribute:@"latitude"];	
			[sharedObjectMapping mapKeyPath:@"aliwwStatus" toAttribute:@"aliwwStatus"];	
			[sharedObjectMapping mapKeyPath:@"id" toAttribute:@"identifier"];	
			[sharedObjectMapping mapKeyPath:@"regCapital" toAttribute:@"regCapital"];	
            
			[sharedObjectMapping mapRelationship:@"creditInfo" withMapping:[AMMemberCredit sharedObjectMapping]];
			
			// Setup object mapping
			RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
			[mappingProvider setMapping:[AMMemberCredit sharedObjectMapping] forKeyPath:@"creditInfo"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_name release];
  [_memberId release];
  [_homepageUrl release];
  [_principal release];
  [_contact release];
  [_mobileNumber release];
  [_establishedYear release];
  [_province release];
  [_city release];
  [_address release];
  [_foundedPlace release];
  [_bizPlace release];
  [_firstBizTypeName release];
  [_packageName release];
  [_phoneAreaCode release];
  [_phoneNumber release];
  [_productionService release];
  [_productionServiceShort release];
  [_trustLogo release];
  [_creditInfo release];
  [_longitude release];
  [_latitude release];
  [_trustScore release];
  [_aliwwStatus release];
  [_identifier release];
  
  [super dealloc];
}

@end
