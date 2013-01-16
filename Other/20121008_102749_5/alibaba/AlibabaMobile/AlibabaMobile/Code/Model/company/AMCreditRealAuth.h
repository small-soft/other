#import "AMObjectMappingDelegate.h"

@interface AMCreditRealAuth : NSObject  <AMObjectMappingDelegate>{

  /**
   * 企业信息
 */
  NSString * _memberId;
  NSString * _companyAddress;
  NSString * _companyCity;
  NSString * _companyCountry;
  NSString * _companyProvince;
  NSString * _companyZip;
  NSString * _companyName;
  NSString * _companyNameEn;
  NSString * _companyPrincipal;
  NSString * _companyBusinessLine;
  NSString * _regCapital;
  NSString * _currencyType;
  NSString * _currencyUnit;
  NSString * _regOrgan;
  NSString * _regCode;
  NSString * _legalStatus;
  NSNumber * _establishedYear;
  NSNumber * _startYear;
  NSNumber * _endYear;
  NSNumber * _verifyDate;
  NSString * _checkYear;
  NSString * _organCode;
  NSString * _manageOrgan;
  NSNumber * _latestValidDate;

  /**
   * 申请人信息
 */
  NSString * _memberDepartment;
  NSString * _memberJobTitle;
  NSString * _memberName;
  NSString * _memberSex;

  /**
   * 个人实名认证信息
 */
  NSString * _hideIdCardNumber;
  NSString * _bankAccount;
  NSString * _bankCity;
  NSString * _bankProvince;
  NSString * _bankName;

  /**
   * 某些字段是否要显示的控制,字符串拼接
 */
  NSString * _showHiddenDescription;

  /**
   * 是否有ID转让记录
 */
  NSNumber * _companyChanged;

  /**
   * 认证公司信息
 */
  NSString * _avProvider;
  NSString * _code;
  NSString * _telephone;
  NSString * _fax;
  NSString * _logoAddr;
  NSString * _briefAddr;
}

@property(nonatomic, retain) NSString * memberId;
@property(nonatomic, retain) NSString * companyAddress;
@property(nonatomic, retain) NSString * companyCity;
@property(nonatomic, retain) NSString * companyCountry;
@property(nonatomic, retain) NSString * companyProvince;
@property(nonatomic, retain) NSString * companyZip;
@property(nonatomic, retain) NSString * companyName;
@property(nonatomic, retain) NSString * companyNameEn;
@property(nonatomic, retain) NSString * companyPrincipal;
@property(nonatomic, retain) NSString * companyBusinessLine;
@property(nonatomic, retain) NSString * regCapital;
@property(nonatomic, retain) NSString * currencyType;
@property(nonatomic, retain) NSString * currencyUnit;
@property(nonatomic, retain) NSString * regOrgan;
@property(nonatomic, retain) NSString * regCode;
@property(nonatomic, retain) NSString * legalStatus;
@property(nonatomic, retain) NSNumber * establishedYear;
@property(nonatomic, retain) NSNumber * startYear;
@property(nonatomic, retain) NSNumber * endYear;
@property(nonatomic, retain) NSNumber * verifyDate;
@property(nonatomic, retain) NSString * checkYear;
@property(nonatomic, retain) NSString * organCode;
@property(nonatomic, retain) NSString * manageOrgan;
@property(nonatomic, retain) NSNumber * latestValidDate;
@property(nonatomic, retain) NSString * memberDepartment;
@property(nonatomic, retain) NSString * memberJobTitle;
@property(nonatomic, retain) NSString * memberName;
@property(nonatomic, retain) NSString * memberSex;
@property(nonatomic, retain) NSString * hideIdCardNumber;
@property(nonatomic, retain) NSString * bankAccount;
@property(nonatomic, retain) NSString * bankCity;
@property(nonatomic, retain) NSString * bankProvince;
@property(nonatomic, retain) NSString * bankName;
@property(nonatomic, retain) NSString * showHiddenDescription;
@property(nonatomic, retain) NSNumber * companyChanged;
@property(nonatomic, retain) NSString * avProvider;
@property(nonatomic, retain) NSString * code;
@property(nonatomic, retain) NSString * telephone;
@property(nonatomic, retain) NSString * fax;
@property(nonatomic, retain) NSString * logoAddr;
@property(nonatomic, retain) NSString * briefAddr;

@end
