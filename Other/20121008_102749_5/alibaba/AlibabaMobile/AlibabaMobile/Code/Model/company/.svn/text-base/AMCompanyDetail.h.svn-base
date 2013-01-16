#import "AMAddress.h"
#import "AMCategory.h"
#import "AMMemberBrief.h"

/**
 * 公司信息
 * @author qizhi.tangqz
 * 
 */
@class AMCompanyIndustry;
@class AMBusinessRegistration;
@class AMGeoInfo;

@interface AMCompanyDetail : AMMemberBrief {

  /**
   * 公司ID
 */
  NSNumber * _identifier;

  /**
   * 公司图片
 */
  NSString * _logoUrl;

  /**
   * 主营行业
 */
  NSArray * _mainIndustries;

  /**
   * 主营产品/服务
 */
  NSArray * _productionService;

  /**
   * 员工人数描述
 */
  NSString * _employeesCount;

  /**
   * 中文站会员编号
 */
  NSString * _vaccountId;

  /**
   * 工商注册信息
 */
  AMBusinessRegistration * _registration;

  /**
   * 公司简介
 */
  NSString * _summary;

  /**
   * 公司联系地址
 */
  AMAddress * _address;

  /**
   * 公司地图经纬度信息
 */
  AMGeoInfo * _geoInfo;

  /**
   * 是否加工/定制
 */
  NSNumber * _manufactureSupplied;

  /**
   * 行业化信息
 */
  AMCompanyIndustry * _industry;
}

@property(nonatomic, retain) NSNumber * identifier;
@property(nonatomic, retain) NSString * logoUrl;
@property(nonatomic, retain) NSArray * mainIndustries;
@property(nonatomic, retain) NSArray * productionService;
@property(nonatomic, retain) NSString * employeesCount;
@property(nonatomic, retain) NSString * vaccountId;
@property(nonatomic, retain) AMBusinessRegistration * registration;
@property(nonatomic, retain) NSString * summary;
@property(nonatomic, retain) AMAddress * address;
@property(nonatomic, retain) AMGeoInfo * geoInfo;
@property(nonatomic, retain) NSNumber * manufactureSupplied;
@property(nonatomic, retain) AMCompanyIndustry * industry;

@end
