#import "AMObjectMappingDelegate.h"

@interface AMNewsItem : NSObject <AMObjectMappingDelegate> {

  /** 资讯内容,当为画报资讯时，请通过newsItemImages获取画报列表*/
  NSString * _content;

  /** 资讯id*/
  NSNumber * _identifier;

  /** 标题*/
  NSString * _title;

  /** 创建时间*/
  NSString * _gmtCreate;

  /** 小图*/
  NSString * _imageSecondPath;

  /** 发布时间*/
  NSString * _publishDate;

  /** 封面图url*/
  NSString * _coverUrl;

  /** 资讯类型--文字（1）、offer画报（2）、非offer画报(3)*/
  NSString * _type;

  /** 资讯所有tag*/
  NSArray * _tags;

  /** 来源*/
  NSString * _agencyName;
  
  /** 投稿人*/
  NSString * _memberId;
  
  /** 画报资讯的画报信息*/
  NSArray * _newsItemImages;
}

@property(nonatomic, retain) NSString * content;
@property(nonatomic, retain) NSNumber * identifier;
@property(nonatomic, retain) NSString * title;
@property(nonatomic, retain) NSString * gmtCreate;
@property(nonatomic, retain) NSString * imageSecondPath;
@property(nonatomic, retain) NSString * publishDate;
@property(nonatomic, retain) NSString * coverUrl;
@property(nonatomic, retain) NSString * type;
@property(nonatomic, retain) NSArray * tags;
@property(nonatomic, retain) NSString * agencyName;
@property(nonatomic, retain) NSString * memberId;
@property(nonatomic, retain) NSArray * newsItemImages;

@end
