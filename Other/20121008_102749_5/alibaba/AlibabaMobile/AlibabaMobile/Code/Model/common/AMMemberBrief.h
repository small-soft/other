#import "AMCreditBase.h"
#import "AMContact.h"
#import "AMPerson.h"

#import "AMObjectMappingDelegate.h"
/**
 * 会员基本信息
 * @author qizhi.tangqz
 * 
 */

@interface AMMemberBrief : NSObject <AMObjectMappingDelegate> {

  /**
   * 公司名称，如果是个人，则公司名称为null
 */
  NSString * _name;

  /**
   * 经营模式
 */
  NSString * _bizType;

  /**
   * 会员类型(免费、个人会员、企业会员、海外会员)
 */
  NSString * _memberType;

  /**
   * 诚信基本信息
 */
  AMCreditBase * _creditBase;

  /**
   * 会员状态
 */
  NSNumber * _statusEnabled;

  /**
   * 联系人方式 *
 */
  AMContact * _contact;

  /**
   * 联系人信息*
 */
  AMPerson * _person;
}

@property(nonatomic, retain) NSString * name;
@property(nonatomic, retain) NSString * bizType;
@property(nonatomic, retain) AMCreditBase * creditBase;
@property(nonatomic, retain) AMContact * contact;
@property(nonatomic, retain) AMPerson * person;
@property(nonatomic, retain) NSString * memberType;
@property(nonatomic, retain) NSNumber * statusEnabled;

@end
