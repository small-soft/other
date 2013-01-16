#import <RestKit/RKRequestSerializable.h>

#define OCEAN_API_URL_MAGAZINE_LIST ([@"/news.getImgMagazineList/" stringByAppendingString:AMCONST_APP_KEY])
#define OCEAN_API_URL_MAGAZINE_CATEGORIES ([@"/news.getImgMagazineCategories/" stringByAppendingString:AMCONST_APP_KEY])
 
@interface AMImgMagazineRequest : NSObject <RKRequestSerializable> {

  NSInteger _transactionType;
  
  /**
	 * 当前页，可选、默认1
  */
  NSNumber * _page;

  /**
	 * 每页条数，默认20 ，最大50条
  */
  NSNumber * _count;
  NSString * _categoryid;
}

@property (nonatomic) NSInteger transactionType;

@property(nonatomic, retain) NSString * categoryid;
@property(nonatomic, retain) NSNumber * page;
@property(nonatomic, retain) NSNumber * count;

@property(nonatomic, retain) NSString * requestURL;

- (id) init;

@end
