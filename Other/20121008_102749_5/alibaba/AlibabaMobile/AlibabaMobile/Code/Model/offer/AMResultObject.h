
@interface AMResultObject : NSObject {

  /**
   * 是否成功
 */
  NSNumber * _success;

  /**
   * 错误代码
 */
  NSString * _errorCode;

  /**
   * 错误信息
 */
  NSString * _errorMsg;
}

@property(nonatomic, retain) NSString * errorCode;
@property(nonatomic, retain) NSString * errorMsg;
@property(nonatomic, retain) NSNumber * success;

@end
