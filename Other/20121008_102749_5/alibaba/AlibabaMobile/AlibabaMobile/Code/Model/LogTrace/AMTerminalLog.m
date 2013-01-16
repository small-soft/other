#import "AMTerminalLog.h"
#import <RestKit/RestKit.h>

NSInteger const AMVERSION_ANDROID_PHONE = 1;
NSInteger const AMVERSION_IPHONE = 2;
NSInteger const AMVERSION_ANDROID_PAD = 3;
NSInteger const AMVERSION_IPAD = 4;

@implementation AMTerminalLog

@synthesize identifier = _identifier;
@synthesize appVersion = _appVersion;
@synthesize imei = _imei;
@synthesize imsi = _imsi;
@synthesize carrier = _carrier;
@synthesize access = _access;
@synthesize accessSubType = _accessSubType;
@synthesize appId = _appId;
@synthesize userId = _userId;
@synthesize phoneNumber = _phoneNumber;
@synthesize osVersion = _osVersion;
@synthesize reserves = _reserves;
@synthesize postTime = _postTime;
@synthesize screenWidth = _screenWidth;
@synthesize screenHeight = _screenHeight;
@synthesize model = _model;
@synthesize versionType = _versionType;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMTerminalLog class]] retain];
			[sharedObjectMapping mapKeyPath:@"id" toAttribute:@"identifier"];
			[sharedObjectMapping mapKeyPath:@"appVersion" toAttribute:@"appVersion"];
			[sharedObjectMapping mapKeyPath:@"imei" toAttribute:@"imei"];
			[sharedObjectMapping mapKeyPath:@"imsi" toAttribute:@"imsi"];
			[sharedObjectMapping mapKeyPath:@"carrier" toAttribute:@"carrier"];
			[sharedObjectMapping mapKeyPath:@"access" toAttribute:@"access"];
			[sharedObjectMapping mapKeyPath:@"accessSubType" toAttribute:@"accessSubType"];
			[sharedObjectMapping mapKeyPath:@"appId" toAttribute:@"appId"];
			[sharedObjectMapping mapKeyPath:@"userId" toAttribute:@"userId"];
			[sharedObjectMapping mapKeyPath:@"phoneNumber" toAttribute:@"phoneNumber"];
			[sharedObjectMapping mapKeyPath:@"phoneNumber" toAttribute:@"phoneNumber"];
			[sharedObjectMapping mapKeyPath:@"osVersion" toAttribute:@"osVersion"];
			[sharedObjectMapping mapKeyPath:@"reserves" toAttribute:@"reserves"];
			[sharedObjectMapping mapKeyPath:@"postTime" toAttribute:@"postTime"];
			[sharedObjectMapping mapKeyPath:@"screenWidth" toAttribute:@"screenWidth"];
			[sharedObjectMapping mapKeyPath:@"screenHeight" toAttribute:@"screenHeight"];
			[sharedObjectMapping mapKeyPath:@"model" toAttribute:@"model"];
			[sharedObjectMapping mapKeyPath:@"versionType" toAttribute:@"versionType"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_identifier release];
  [_appVersion release];
  [_imei release];
  [_imsi release];
  [_model release];
  [_carrier release];
  [_access release];
  [_accessSubType release];
  [_appId release];
  [_userId release];
  [_phoneNumber release];
  [_osVersion release];
  [_reserves release];
  [_postTime release];
  [_screenWidth release];
  [_screenHeight release];
  [_versionType release];
  
  [super dealloc];
}

@end
