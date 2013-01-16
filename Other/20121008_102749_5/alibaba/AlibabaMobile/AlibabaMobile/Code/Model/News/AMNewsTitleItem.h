#import "AMObjectMappingDelegate.h"

@interface AMNewsTitleItem : NSObject <AMObjectMappingDelegate> {
  NSString * _identifier;
  NSString * _title;
  NSString * _keyword;
  NSString * _areaid;
  NSString * _publishDate;
}

@property(nonatomic, retain) NSString * identifier;
@property(nonatomic, retain) NSString * title;
@property(nonatomic, retain) NSString * keyword;
@property(nonatomic, retain) NSString * areaid;
@property(nonatomic, retain) NSString * publishDate;

@end
