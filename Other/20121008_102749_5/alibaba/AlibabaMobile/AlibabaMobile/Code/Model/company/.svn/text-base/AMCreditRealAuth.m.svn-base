#import "AMCreditRealAuth.h"

@implementation AMCreditRealAuth

@synthesize memberId		   =	_memberId;
@synthesize companyAddress     =    _companyAddress;
@synthesize companyCity        =    _companyCity;
@synthesize companyCountry     =    _companyCountry;
@synthesize companyProvince    =    _companyProvince;
@synthesize companyZip         =    _companyZip;
@synthesize companyName        =    _companyName;
@synthesize companyNameEn      =    _companyNameEn;
@synthesize companyPrincipal   =    _companyPrincipal;
@synthesize companyBusinessLine=    _companyBusinessLine;
@synthesize regCapital         =    _regCapital;
@synthesize currencyType       =    _currencyType;
@synthesize currencyUnit       =    _currencyUnit;
@synthesize regOrgan           =    _regOrgan;
@synthesize regCode            =    _regCode;
@synthesize legalStatus        =    _legalStatus;
@synthesize establishedYear    =    _establishedYear;
@synthesize startYear          =    _startYear;
@synthesize endYear            =    _endYear;
@synthesize verifyDate         =    _verifyDate;
@synthesize checkYear          =    _checkYear;
@synthesize organCode          =    _organCode;
@synthesize manageOrgan        =    _manageOrgan;
@synthesize latestValidDate    =    _latestValidDate;
@synthesize memberDepartment   =    _memberDepartment;
@synthesize memberJobTitle     =    _memberJobTitle;
@synthesize memberName         =    _memberName;
@synthesize memberSex          =    _memberSex;
@synthesize hideIdCardNumber   =    _hideIdCardNumber;
@synthesize bankAccount        =    _bankAccount;
@synthesize bankCity           =    _bankCity;
@synthesize bankProvince       =    _bankProvince;
@synthesize bankName           =    _bankName;
@synthesize showHiddenDescription =  _showHiddenDescription;
@synthesize companyChanged      =   _companyChanged;
@synthesize avProvider          =   _avProvider;
@synthesize code                =   _code;
@synthesize telephone           =   _telephone;
@synthesize fax                 =   _fax;
@synthesize logoAddr            =   _logoAddr;
@synthesize briefAddr           =   _briefAddr;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMCreditRealAuth class]] retain];
			
			// Super class
			[sharedObjectMapping mapKeyPath:@"memberId" toAttribute:@"memberId"];
            [sharedObjectMapping mapKeyPath:@"companyAddress" toAttribute:@"companyAddress"];
            [sharedObjectMapping mapKeyPath:@"companyCity" toAttribute:@"companyCity"];
            [sharedObjectMapping mapKeyPath:@"companyCountry" toAttribute:@"companyCountry"];
            [sharedObjectMapping mapKeyPath:@"companyProvince" toAttribute:@"companyProvince"];
            [sharedObjectMapping mapKeyPath:@"companyZip" toAttribute:@"companyZip"];
            [sharedObjectMapping mapKeyPath:@"companyName" toAttribute:@"companyName"];
            [sharedObjectMapping mapKeyPath:@"companyNameEn" toAttribute:@"companyNameEn"];
            [sharedObjectMapping mapKeyPath:@"companyPrincipal" toAttribute:@"companyPrincipal"];
            [sharedObjectMapping mapKeyPath:@"companyBusinessLine" toAttribute:@"companyBusinessLine"];
            [sharedObjectMapping mapKeyPath:@"regCapital" toAttribute:@"regCapital"];
            [sharedObjectMapping mapKeyPath:@"currencyType" toAttribute:@"currencyType"];
            
            [sharedObjectMapping mapKeyPath:@"currencyUnit" toAttribute:@"currencyUnit"];
            [sharedObjectMapping mapKeyPath:@"regOrgan" toAttribute:@"regOrgan"];
            [sharedObjectMapping mapKeyPath:@"regCode" toAttribute:@"regCode"];
            [sharedObjectMapping mapKeyPath:@"legalStatus" toAttribute:@"legalStatus"];
            [sharedObjectMapping mapKeyPath:@"establishedYear" toAttribute:@"establishedYear"];
            [sharedObjectMapping mapKeyPath:@"startYear" toAttribute:@"startYear"];
            [sharedObjectMapping mapKeyPath:@"endYear" toAttribute:@"endYear"];
            [sharedObjectMapping mapKeyPath:@"verifyDate" toAttribute:@"verifyDate"];
            [sharedObjectMapping mapKeyPath:@"checkYear" toAttribute:@"checkYear"];
            [sharedObjectMapping mapKeyPath:@"organCode" toAttribute:@"organCode"];
            [sharedObjectMapping mapKeyPath:@"manageOrgan" toAttribute:@"manageOrgan"];
            [sharedObjectMapping mapKeyPath:@"newValidDate" toAttribute:@"latestValidDate"];
            
            
            [sharedObjectMapping mapKeyPath:@"memberDepartment" toAttribute:@"memberDepartment"];
            [sharedObjectMapping mapKeyPath:@"memberJobTitle" toAttribute:@"memberJobTitle"];
            [sharedObjectMapping mapKeyPath:@"memberName" toAttribute:@"memberName"];
            [sharedObjectMapping mapKeyPath:@"memberSex" toAttribute:@"memberSex"];
			
            [sharedObjectMapping mapKeyPath:@"hideIdCardNumber" toAttribute:@"hideIdCardNumber"];
            [sharedObjectMapping mapKeyPath:@"bankAccount" toAttribute:@"bankAccount"];
            [sharedObjectMapping mapKeyPath:@"bankCity" toAttribute:@"bankCity"];
            [sharedObjectMapping mapKeyPath:@"bankProvince" toAttribute:@"bankProvince"];
            [sharedObjectMapping mapKeyPath:@"bankName" toAttribute:@"bankName"];
            
            
            [sharedObjectMapping mapKeyPath:@"showHiddenDescription" toAttribute:@"showHiddenDescription"];
            [sharedObjectMapping mapKeyPath:@"companyChanged" toAttribute:@"companyChanged"];
            [sharedObjectMapping mapKeyPath:@"avProvider" toAttribute:@"avProvider"];
            [sharedObjectMapping mapKeyPath:@"code" toAttribute:@"code"];
            [sharedObjectMapping mapKeyPath:@"telephone" toAttribute:@"telephone"];
            
            [sharedObjectMapping mapKeyPath:@"fax" toAttribute:@"fax"];
            [sharedObjectMapping mapKeyPath:@"logoAddr" toAttribute:@"logoAddr"];
            [sharedObjectMapping mapKeyPath:@"briefAddr" toAttribute:@"briefAddr"];
        }
    }
    
    return sharedObjectMapping;
}



- (void) dealloc {
	[_memberId release];
	[_companyAddress release];
	[_companyCity release];
	[_companyCountry release];
	[_companyProvince release];
	[_companyZip release];
	[_companyName release];
	[_companyNameEn release];
	[_companyPrincipal release];
	[_companyBusinessLine release];
	[_regCapital release];
	[_currencyType release];
	[_currencyUnit release];
	[_regOrgan release];
	[_regCode release];
	[_legalStatus release];
	[_establishedYear release];
	[_startYear release];
	[_endYear release];
	[_verifyDate release];
	[_checkYear release];
	[_organCode release];
	[_manageOrgan release];
	[_latestValidDate release];
	[_memberDepartment release];
	[_memberJobTitle release];
	[_memberName release];
	[_memberSex release];
	[_hideIdCardNumber release];
	[_bankAccount release];
	[_bankCity release];
	[_bankProvince release];
	[_bankName release];
	[_showHiddenDescription release];
	[_companyChanged release];
	[_avProvider release];
	[_code release];
	[_telephone release];
	[_fax release];
	[_logoAddr release];
	[_briefAddr release];

	[super dealloc];
}

@end
