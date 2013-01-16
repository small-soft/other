#import "AMObjectMappingDelegate.h"

@class AMLogisTraceStep;

@interface AMLogisSimpleOrder : NSObject <AMObjectMappingDelegate> {

  /**
   * 物流编号，例：AL01000000003649
 */
  NSString * _logisticsID;

  /**
   * 运单号(物流公司提供的跟踪号)
 */
  NSString * _mailNo;

  /**
   * 物流公司编号：DEPPON/XBWL/DTW/HOAU等<br>
   * 跟踪信息查询时物流公司参数
 */
  NSString * _logisticsCompanyid;

  /**
   * 物流公司名称：德邦物流/天地华宇
 */
  NSString * _logisticsCorpName;

  /**
   * 收货人公司名
 */
  NSString * _receiverCorpName;

  /**
   * 收货人姓名
 */
  NSString * _receiverName;

  /**
   * 货物名称
 */
  NSString * _cargoName;

  /**
   * 货物件数
 */
  NSNumber * _totalNumber;

  /**
   * 货物重量
 */
  NSNumber * _totalWeight;

  /**
   * 货物体积
 */
  NSNumber * _totalVolume;

  /**
   * UDB uid
 */
  NSString * _aliUID;

  /**
   * 中文站交易订单ID，例： 26676236
 */
  NSString * _tradeOrderId;

  /**
   * 最新物流状态，包含时间和物流信息
 */
  AMLogisTraceStep * _newestTraceStep;
}

@property(nonatomic, retain) NSString * logisticsID;
@property(nonatomic, retain) NSString * mailNo;
@property(nonatomic, retain) NSString * logisticsCompanyid;
@property(nonatomic, retain) NSString * logisticsCorpName;
@property(nonatomic, retain) NSString * receiverCorpName;
@property(nonatomic, retain) NSString * receiverName;
@property(nonatomic, retain) NSString * cargoName;
@property(nonatomic, retain) NSNumber * totalNumber;
@property(nonatomic, retain) NSNumber * totalWeight;
@property(nonatomic, retain) NSNumber * totalVolume;
@property(nonatomic, retain) NSString * aliUID;
@property(nonatomic, retain) NSString * tradeOrderId;
@property(nonatomic, retain) AMLogisTraceStep * newestTraceStep;

@end
