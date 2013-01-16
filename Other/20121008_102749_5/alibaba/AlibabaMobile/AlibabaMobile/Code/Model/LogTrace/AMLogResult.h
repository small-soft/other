#import "AMObjectMappingDelegate.h"

/**
 * LogResult日志记录结果
 * 
 * @author qizhi.tangqz
 */

/**
 * Successful
 */
extern NSInteger const AMCODE_OK;

/**
 * Client Error 4xx
 */
extern NSInteger const AMCODE_BAD_REQUEST;
extern NSInteger const AMCODE_BAD_LENGTH;
extern NSInteger const AMCODE_BAD_FORMAT;

/**
 * Server Error 5xx
 */
extern NSInteger const AMCODE_BAD_SERVICE;
extern NSInteger const AMCODE_BAD_DEPEND_ENV;

@interface AMLogResult : NSObject <AMObjectMappingDelegate> {

  /**
   * 是否成功
 */
  NSNumber * _success;

  /**
   * 结果代码
 */
  NSNumber * _resultCode;
}

@property(nonatomic,retain) NSNumber *  success;
@property(nonatomic, retain) NSNumber *  resultCode;

@end
