#import "AMObjectMappingDelegate.h"

/**
 * 消息中心的type查询结果对象类。
 * 
 * @author rocky.wenk 2012-7-12
 */

@interface AMMobileMessageType : NSObject <AMObjectMappingDelegate> {
}

@property(nonatomic, retain) NSString * source;
@property(nonatomic, retain) NSString * displayName;

@end
