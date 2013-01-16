

/**
 * LogTrace request
 * 
 * @author qizhi.tangqz
 */

#import <Foundation/Foundation.h>
#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_SEND_LOGS ([@"/ops.appclick.createAppClickLogs/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMLogRequest : NSObject<RKRequestSerializable> {
    
    NSInteger _transactionType;

  /**
    * 请求参数容器
    */
  NSDictionary * _request;
    
  /**
   * 搜索关键字
 */
  NSDictionary * _header;

  /**
   * 类目Id
 */
  NSArray * _logs;

}

@property (nonatomic) NSInteger transactionType;

@property(nonatomic, retain) NSDictionary * header;
@property(nonatomic, retain) NSArray * logs;

@property(nonatomic, retain) NSDictionary * request;
@property (nonatomic, retain) NSString *accessToken;

@end
