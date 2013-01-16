
/**
 * AMTerminalLog终端的设备信息和用户信息
 * 
 * @author qizhi.tangqz
 */
#import "AMObjectMappingDelegate.h"

extern NSInteger const AMVERSION_ANDROID_PHONE;
extern NSInteger const AMVERSION_IPHONE;
extern NSInteger const AMVERSION_ANDROID_PAD;
extern NSInteger const AMVERSION_IPAD;

@interface AMTerminalLog : NSObject <AMObjectMappingDelegate> {

  /**
   * 编号
 */
  NSString * _identifier;

  /**
   * 应用版本
 */
  NSString * _appVersion;

  /**
   * 版本类型  1=android手机版；2=iphone手机版；3=android pad版；4=ipad版
 */
  NSNumber * _versionType;

  /**
   * 国际手机唯一标识
 */
  NSString * _imei;

  /**
   * 国际移动用户唯一标识
 */
  NSString * _imsi;

  /**
   * 手机型号
 */
  NSString * _model;

  /**
   * 运营商
 */
  NSString * _carrier;

  /**
   * 网络类型
 */
  NSString * _access;

  /**
   * 网络子类型
 */
  NSString * _accessSubType;

  /**
   * 应用ID
 */
  NSString * _appId;

  /**
   * 用户ID
 */
  NSString * _userId;

  /**
   * 手机号码
 */
  NSString * _phoneNumber;

  /**
   * 操作系统版本
 */
  NSString * _osVersion;

  /**
   * 保留字段
 */
  NSString * _reserves;

  /**
   * 发送时间
 */
  NSString * _postTime;

  /**
   * 屏幕宽度
 */
  NSNumber * _screenWidth;

  /**
   * 屏幕高度
 */
  NSNumber * _screenHeight;
}

@property(nonatomic, retain) NSString * identifier;
@property(nonatomic, retain) NSString * appVersion;
@property(nonatomic, retain) NSString * imei;
@property(nonatomic, retain) NSString * imsi;
@property(nonatomic, retain) NSString * carrier;
@property(nonatomic, retain) NSString * access;
@property(nonatomic, retain) NSString * accessSubType;
@property(nonatomic, retain) NSString * appId;
@property(nonatomic, retain) NSString * userId;
@property(nonatomic, retain) NSString * phoneNumber;
@property(nonatomic, retain) NSString * osVersion;
@property(nonatomic, retain) NSString * reserves;
@property(nonatomic, retain) NSString * postTime;
@property(nonatomic, retain) NSNumber * screenWidth;
@property(nonatomic, retain) NSNumber * screenHeight;
@property(nonatomic, retain) NSString * model;
@property(nonatomic, retain) NSNumber * versionType;

@end
