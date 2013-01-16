#import "AMObjectMappingDelegate.h"

/**
 * 用于调用方（客户端/WAP/推送服务器）的消息格式
 * 
 * @author qizhi.tangqz 2012-2-25
 */
 
extern NSInteger const AMSTATUS_INIT; // 初始状态，表示无需处理
extern NSInteger const AMSTATUS_SENT; // 已发送（未确认是否成功）
extern NSInteger const AMSTATUS_SUCCESS; // 发送成功
extern NSInteger const AMSTATUS_FAIL; // 发送失败
extern NSInteger const AMSTATUS_APP_NOT_ONLINE; // 用户APP不在线

extern NSString* const AMSource_All;
extern NSString* const AMSourceName_All;
extern NSString* const AMSource_New;
extern NSString* const AMSourceName_New;

extern NSString* const AMSource_ALI56;
extern NSString* const AMSourceName_ALI56;
extern NSString* const AMSource_JiaGe;
extern NSString* const AMSourceName_JiaGe;
extern NSString* const AMSource_Bing;
extern NSString* const AMSourceName_Bing;
extern NSString* const AMSource_TrustPass;
extern NSString* const AMSourceName_TrustPass;
extern NSString* const AMSource_Trade;
extern NSString* const AMSourceName_Trade;

extern NSString* const AMSourceName_Others;

@interface AMMobileMessage : NSObject <AMObjectMappingDelegate> {

  /**
   * ID
 */
  NSNumber * _identifier;

  /**
     * 事件来源(非空)，客户端可暂时不用
  */
  NSString * _source;

  /**
     * 事件发送者(非空)，客户端暂时不用
  */
  NSString * _sender;

  /**
     * 消息的接收者（会员id）
  */
  NSString * _receiver;

  /**
     * 手机消息类型（与网站的定义可能会不同），APP和WAP会根据这个类型进行消息的不同展现和处理（依赖type字段的值）
  */
  NSString * _type;

  /**
     * 消息标题
  */
  NSString * _title;

  /**
     * 消息的内容（纯文本）
  */
  NSString * _textData;

  /**
     * 如果是有格式的消息，可以提供json格式的元数据，方便消息使用方进行处理<br/>
     * 特别说明：如果是重要消息（需要务必通知到某用户），可在jsonData中增加短信配置（手机号和短信内容），比如：{'smsMobile':'13910153896','smsContent':'测试内容'}
     */
  NSString * _jsonData;

  /**
     * 消息的产生日期
     */
  NSNumber * _gmtOccured;

  /**
     * 是否已读
     */
  NSNumber * _hasRead;
}

@property(nonatomic, retain) NSNumber * identifier;
@property(nonatomic, retain) NSString * source;
@property(nonatomic, retain) NSString * sender;
@property(nonatomic, retain) NSString * receiver;
@property(nonatomic, retain) NSString * type;
@property(nonatomic, retain) NSString * title;
@property(nonatomic, retain) NSString * textData;
@property(nonatomic, retain) NSString * jsonData;
@property(nonatomic, retain) NSNumber * gmtOccured;
@property(nonatomic, retain) NSNumber * hasRead;

- (NSString *) sourceDisplayName;

@end
