/**会员类型*/


NSString *  const MEMBER_TYPE_ENTERPRICE = @"enterprise";//企业会员
NSString *  const MEMBER_TYPE_PERSON = @"person";//个人会员
NSString *  const MEMBER_TYPE_ETC = @"etc";//海外会员
NSString *  const MEMBER_TYPE_SM = @"sm";//专业市场会员
NSString *  const MEMBER_TYPE_EM = @"em";//展会会员
NSString *  const MEMBER_TYPE_VIP = @"vip";//VIP商城会员
NSString *  const MEMBER_TYPE_FREE = @"free";//免费会员

/** 经营模式*/
NSString *  const BIZ_TYPE_MANUFACTURER = @"1";//生产加工
NSString *  const BIZ_TYPE_WHOLESALE = @"2";//经销批发
NSString *  const BIZ_TYPE_INVESTMENT = @"3";//招商代理
NSString *  const BIZ_TYPE_TRADE = @"4";//商业服务
NSString *  const BIZ_TYPE_OTHER = @"5";//其他

/**诚保类型*/
NSString *  const GUARANTEE_TYPE_SUPER = @"1";//SUPER：超级圈成员（2011-9前系统中没有超级团）
NSString *  const GUARANTEE_TYPE_MASTER = @"2";//MASTER：普通圈主
NSString *  const GUARANTEE_TYPE_MEMBER = @"3";//MEMBER：普通圈成员
NSString *  const GUARANTEE_TYPE_GUARANTEE =@"4";//GUANRANTEE：普通诚保
NSString *  const GUARANTEE_TYPE_NON_GUARANTEE = @"5";//NON_GUARANTEE：非诚保

/**诚保版本*/
NSString *  const TP_VERSION_POPULAR_EDITION = @"1";//普及版
NSString *  const TP_VERSION_LIMIT_EDITION =@"2";//限量版
NSString *  const TP_VERSION_STANDARD_EDITION = @"3";//标准版
NSString *  const TP_VERSION_NONE_EDITION = @"4";//免费版

/**诚保团类型*/
NSString *  const GUARANTEE_GROUP_TYPE_SUPER =@"1";//超级团（2011-9前系统中没有超级团）
NSString *  const GUARANTEE_GROUP_TYPE_COMMON = @"2";//普通团

/**诚保团状态*/
NSString *  const GUARANTEE_GROUP_STATUS_CREATED = @"1";//已创建
NSString *  const GUARANTEE_GROUP_STATUS_OPENED =@"2";//已开通
NSString *  const GUARANTEE_GROUP_STATUS_FREEZED = @"3";//已冻结
NSString *  const GUARANTEE_GROUP_STATUS_CLOSED = @"4";//已关闭

/** 旺旺状态 */
const NSInteger ALIWW_STATUS_ONLINE = 0; // 在线
const NSInteger ALIWW_STATUS_OFFLINE = 1; // 用户不在线
const NSInteger ALIWW_STATUS_INVALID = 2; // 非有效用户ID
const NSInteger ALIWW_STATUS_HIDDEN = 3; // 隐身
const NSInteger ALIWW_STATUS_MOBILE_ONLINE = 4; // 手机在线
const NSInteger ALIWW_STATUS_MOBILE_ONLINE_FORWARD = 5; // 手机在线, 且设置了离线消息转手机
const NSInteger ALIWW_STATUS_OFFLINE_FORWARD = 6; // 离线, 且设置了离线消息转手机
