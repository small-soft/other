/*!
 * @class			InterfaceCommandException 
 * @author			Littlejie
 * @brief			程序错误异常
 * @note			InterfaceCommandException 程序错误异常
 */


#import <Foundation/Foundation.h>


@interface InterfaceCommandException : NSException {

}

/*!
 @method     initWithReason:
 @brief		 初始化异常对象
 @note		 初始化异常对象
 @param      reason 异常的描述
 @param      userInfo 异常返回的数据信息
 @result     返回InterfaceCommandException对象
 */
- (id)initWithReason:(NSString *)reason userInfo:(NSDictionary *)userInfo;

/*!
 @method     exceptionWithReason:
 @brief		 初始化异常对象
 @note		 静态初始化异常对象
 @param      reason 异常的描述
 @param      userInfo 异常返回的数据信息
 @result     返回InterfaceCommandException对象
 */
+ (InterfaceCommandException *)exceptionWithReason:(NSString *)reason userInfo:(NSDictionary *)userInfo;

@end
