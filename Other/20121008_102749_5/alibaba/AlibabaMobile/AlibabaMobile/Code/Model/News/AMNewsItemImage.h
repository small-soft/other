#import "AMImage.h"
#import "AMNewsItemImageOffer.h"
#import "AMObjectMappingDelegate.h"

@interface AMNewsItemImage : NSObject <AMObjectMappingDelegate> {
  NSString * _url;
  NSString * _surl;
  NSString * _picDesc;
  AMImage * _image;
  AMNewsItemImageOffer * _newsItemImageOffer;
}

@property(nonatomic, retain) NSString * url;
@property(nonatomic, retain) NSString * surl;
@property(nonatomic, retain) NSString * picDesc;
@property(nonatomic, retain) AMNewsItemImageOffer * newsItemImageOffer;
@property(nonatomic, retain) AMImage * image;

@end
