#import "AMMobileMessage.h"
#import <RestKit/RestKit.h>

NSInteger const AMSTATUS_INIT           = 0; // 初始状态，表示无需处理
NSInteger const AMSTATUS_SENT           = 1; // 已发送（未确认是否成功）
NSInteger const AMSTATUS_SUCCESS        = 2; // 发送成功
NSInteger const AMSTATUS_FAIL           = 3; // 发送失败
NSInteger const AMSTATUS_APP_NOT_ONLINE = 4; // 用户APP不在线

NSString* const AMSource_All             = @"AMSourceName_All";
NSString* const AMSourceName_All         = @"所有消息";
NSString* const AMSource_New             = @"AMSourceName_New";
NSString* const AMSourceName_New         = @"未读消息";

NSString* const AMSource_ALI56            =  @"ALI56";
NSString* const AMSourceName_ALI56        =  @"阿里物流";
NSString* const AMSource_JiaGe            =  @"cn.jiage";
NSString* const AMSourceName_JiaGe        =  @"价格行情";
NSString* const AMSource_Bing             =  @"Bing";
NSString* const AMSourceName_Bing         =  @"采购速配";
NSString* const AMSource_TrustPass        =  @"tpbopsTrustpass";
NSString* const AMSourceName_TrustPass    =  @"供应商信息";
NSString* const AMSource_Trade            =  @"trade";
NSString* const AMSourceName_Trade        =  @"交易提醒";
NSString* const AMSource_PM               =  @"pm";
NSString* const AMSourceName_PM           =  @"精准营销";
NSString* const AMSource_EQ               =  @"eq";
NSString* const AMSourceName_EQ           =  @"询盘管理";
NSString* const AMSource_TRUSTPASS        =  @"trustpassNotify";
NSString* const AMSourceName_TRUSTPASS    =  @"供应商信息";
NSString* const AMSource_Other            =  @"mobile.ops";
NSString* const AMSourceName_Other        =  @"温馨提醒";

@implementation AMMobileMessage

@synthesize identifier = _identifier;
@synthesize source = _source;
@synthesize sender = _sender;
@synthesize receiver = _receiver;
@synthesize type = _type;
@synthesize title = _title;
@synthesize textData = _textData;
@synthesize jsonData = _jsonData;
@synthesize gmtOccured = _gmtOccured;
@synthesize hasRead = _hasRead;


+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMMobileMessage class]] retain];
			[sharedObjectMapping mapKeyPath:@"id" toAttribute:@"identifier"];
			[sharedObjectMapping mapKeyPath:@"source" toAttribute:@"source"];		
			[sharedObjectMapping mapKeyPath:@"sender" toAttribute:@"sender"];	
			[sharedObjectMapping mapKeyPath:@"receiver" toAttribute:@"receiver"];	
			[sharedObjectMapping mapKeyPath:@"type" toAttribute:@"type"];	
			[sharedObjectMapping mapKeyPath:@"title" toAttribute:@"title"];	
			[sharedObjectMapping mapKeyPath:@"textData" toAttribute:@"textData"];	
			[sharedObjectMapping mapKeyPath:@"jsonData" toAttribute:@"jsonData"];
            [sharedObjectMapping mapKeyPath:@"gmtOccured" toAttribute:@"gmtOccured"];	
			[sharedObjectMapping mapKeyPath:@"hasRead" toAttribute:@"hasRead"];				
        }
    }
    
    return sharedObjectMapping;
}

- (NSString *) sourceDisplayName {
	if ([self.source isEqualToString: AMSource_ALI56]) {
		return AMSourceName_ALI56;
	}else if ([self.source isEqualToString: AMSource_JiaGe]) {
		return AMSourceName_JiaGe;
	}else if ([self.source isEqualToString: AMSource_Bing]) {
		return AMSourceName_Bing;
	}else if ([self.source isEqualToString: AMSource_TrustPass]) {
		return AMSourceName_TrustPass;
	}else if ([self.source isEqualToString: AMSource_Trade]) {
		return AMSourceName_Trade;
    }else if ([self.source isEqualToString: AMSource_All]) {
		return AMSourceName_All;
    }else if ([self.source isEqualToString: AMSource_New]) {
		return AMSourceName_New;
    }else if ([self.source isEqualToString: AMSource_PM]) {
		return AMSourceName_PM;
    }else if ([self.source isEqualToString: AMSource_EQ]) {
		return AMSourceName_EQ;
    }else if ([self.source isEqualToString: AMSource_TRUSTPASS]) {
		return AMSourceName_TRUSTPASS;
	}else{
        return AMSourceName_Other;
    }
	
	return nil;
}

- (void) dealloc {
  [_identifier release];
  [_source release];
  [_sender release];
  [_receiver release];
  [_type release];
  [_title release];
  [_textData release];
  [_jsonData release];
  [_gmtOccured release];
  [_hasRead release];
  
  [super dealloc];
}

@end
