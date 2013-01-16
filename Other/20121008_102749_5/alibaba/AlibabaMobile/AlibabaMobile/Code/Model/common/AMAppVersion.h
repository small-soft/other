#import "AMObjectMappingDelegate.h"

/**
 * APP版本基本信息
 * 
 * @author qizhi.tangqz 2012-3-29 下午02:19:37
 */

@interface AMAppVersion : NSObject <AMObjectMappingDelegate> {

  /**
   * ID
 */
  NSNumber * _identifier;

  /**
   * Android/iOS/其他平台，具体取值取决于服务接口和APP的约定。
 */
  NSString * _platform;

  /**
   * 版本信息
 */
  NSString * _version;

  /**
   * 版本类型
 */
  NSString * _versionType;

  /**
   * changelog（给用户看的）
 */
  NSString * _changelog;

  /**
   * 发布时间
 */
  NSNumber * _gmtRelease;

  /**
   * 文件包大小（字节）
 */
  NSNumber * _downloadSize;

  /**
   * 下载地址
 */
  NSString * _downloadUrl;

  /**
   * md5校验码
 */
  NSString * _md5Checksum;
  
  /**
   * 是否有最新版本
 */
    NSNumber * _isVersionAvailable;
}

@property(nonatomic, retain) NSNumber * identifier;
@property(nonatomic, retain) NSString * platform;
@property(nonatomic, retain) NSString * version;
@property(nonatomic, retain) NSString * versionType;
@property(nonatomic, retain) NSString * changelog;
@property(nonatomic, retain) NSNumber * gmtRelease;
@property(nonatomic, retain) NSNumber * downloadSize;
@property(nonatomic, retain) NSString * downloadUrl;
@property(nonatomic, retain) NSString * md5Checksum;
@property(nonatomic, retain) NSNumber * isVersionAvailable;

@end
