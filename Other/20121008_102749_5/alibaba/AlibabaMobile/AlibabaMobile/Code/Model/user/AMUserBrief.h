#import "AMAddress.h"
#import "AMContact.h"
#import "AMPerson.h"

@interface AMUserBrief : AMPerson {

  /**
   * ��ϵ�˷�ʽ *
 */
  AMContact * contact;

  /**
   * ��ϵ�˵�ַ
 */
  AMAddress * address;

  /**
   * ��˾����
 */
  NSString * companyName;

  /**
   * ����
 */
  NSString * penName;
  NSString * headPic;
}

@property(nonatomic, retain) AMContact * contact;
@property(nonatomic, retain) NSString * companyName;
@property(nonatomic, retain) NSString * penName;
@property(nonatomic, retain) NSString * headPic;
@property(nonatomic, retain) AMAddress * address;

@end
