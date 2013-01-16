
/**会员类型*/
extern NSString *  const MEMBER_TYPE_ENTERPRICE;//企业会员
extern NSString *  const MEMBER_TYPE_PERSON;//个人会员
extern NSString *  const MEMBER_TYPE_ETC;//海外会员
extern NSString *  const MEMBER_TYPE_SM;//专业市场会员
extern NSString *  const MEMBER_TYPE_EM;//展会会员
extern NSString *  const MEMBER_TYPE_VIP;//VIP商城会员
extern NSString *  const MEMBER_TYPE_FREE;//免费会员

/** 经营模式*/
extern NSString *  const BIZ_TYPE_MANUFACTURER;//生产加工
extern NSString *  const BIZ_TYPE_WHOLESALE;//经销批发
extern NSString *  const BIZ_TYPE_INVESTMENT;//招商代理
extern NSString *  const BIZ_TYPE_TRADE;//商业服务
extern NSString *  const BIZ_TYPE_OTHER;//其他

/**诚保类型*/
extern NSString *  const GUARANTEE_TYPE_SUPER;//SUPER：超级圈成员（2011-9前系统中没有超级团）
extern NSString *  const GUARANTEE_TYPE_MASTER;//MASTER：普通圈主
extern NSString *  const GUARANTEE_TYPE_MEMBER;//MEMBER：普通圈成员
extern NSString *  const GUARANTEE_TYPE_GUARANTEE;//GUANRANTEE：普通诚保
extern NSString *  const GUARANTEE_TYPE_NON_GUARANTEE;//NON_GUARANTEE：非诚保

/**诚保版本*/
extern NSString *  const TP_VERSION_POPULAR_EDITION;//普及版
extern NSString *  const TP_VERSION_LIMIT_EDITION;//限量版
extern NSString *  const TP_VERSION_STANDARD_EDITION;//标准版
extern NSString *  const TP_VERSION_NONE_EDITION;//免费版

/**诚保团类型*/
extern NSString *  const GUARANTEE_GROUP_TYPE_SUPER;//超级团（2011-9前系统中没有超级团）
extern NSString *  const GUARANTEE_GROUP_TYPE_COMMON;//普通团

/**诚保团状态*/
extern NSString *  const GUARANTEE_GROUP_STATUS_CREATED;//已创建
extern NSString *  const GUARANTEE_GROUP_STATUS_OPENED;//已开通
extern NSString *  const GUARANTEE_GROUP_STATUS_FREEZED;//已冻结
extern NSString *  const GUARANTEE_GROUP_STATUS_CLOSED;//已关闭

/** 旺旺状态 */
const NSInteger ALIWW_STATUS_ONLINE; // 在线
const NSInteger ALIWW_STATUS_OFFLINE; // 用户不在线
const NSInteger ALIWW_STATUS_INVALID; // 非有效用户ID
const NSInteger ALIWW_STATUS_HIDDEN; // 隐身
const NSInteger ALIWW_STATUS_MOBILE_ONLINE; // 手机在线
const NSInteger ALIWW_STATUS_MOBILE_ONLINE_FORWARD; // 手机在线, 且设置了离线消息转手机
const NSInteger ALIWW_STATUS_OFFLINE_FORWARD; // 离线, 且设置了离线消息转手机
