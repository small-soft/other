#import <RestKit/RKRequestSerializable.h>

#import "AMObjectMappingDelegate.h"
#import "AMRequestDelegate.h"

#define OCEAN_API_URL_NEWS_CATEGORIES ([@"/news.getNewsCategory/" stringByAppendingString:AMCONST_APP_KEY])
#define OCEAN_API_URL_HOTNEWS_LIST ([@"/news.getInfoAllRecommend/" stringByAppendingString:AMCONST_APP_KEY])
#define OCEAN_API_URL_NEWS_LIST ([@"/news.getNewsList/" stringByAppendingString:AMCONST_APP_KEY])

@interface AMNewsListRequest : NSObject <RKRequestSerializable, AMRequestDelegate> {

    NSInteger _transactionType;
    
    /**
	 * 当前页，可选、默认1
	 */
  NSNumber * _page;

    /**
	 * 每页条数，默认20 ，最大50条
	 */
  NSNumber * _count;

    /**
	 * 默认全部行业 支持多个行业，以逗号分隔 例cat_id=4,6，支持叶子类目
	 */
  NSString * _cateId;

    /**
	 * 螺纹钢,冶金等 支持多个tags，以逗号分隔
	 */
  NSString * _tags;

    /**
	 * 返回的列表类型，默认为hot（热点资讯信息列表）,目前没有用处
	 */
  NSString * _type;

    /**
	 * 资讯类型(全部、文字、画报 )，默认为文字，见Constants.Request_News_Type_* 
	 */
  NSString * _newsType;

    /**
	 * 排除此tags下搜索，目前只支持一个tags，同时，该参数有值时，tags也必须有值，否则该参数无效
	 */
  NSString * _excludeTags;

    /**
	 * 排除此类目下搜索，支持多个类目，以逗号分隔
	 */
  NSString * _excludeCats;
}

@property(nonatomic, retain) NSNumber * page;
@property(nonatomic, retain) NSNumber * count;
@property(nonatomic, retain) NSString * cateId;
@property(nonatomic, retain) NSString * tags;
@property(nonatomic, retain) NSString * type;
@property(nonatomic, retain) NSString * newsType;
@property(nonatomic, retain) NSString * excludeTags;
@property(nonatomic, retain) NSString * excludeCats;

@property(nonatomic) NSInteger transactionType;

- (id) init;

@end
