#import <Foundation/Foundation.h>

extern NSString * const FAVORITE_ADD_PRICE_EXISTS;
extern NSString * const FAVORITE_ADD_PRICE_OVER_MAXLIMITED;

@interface AMPriceBaseItem : NSObject {
  NSNumber * _identifier;
  NSString * _name;
}

@property(nonatomic, retain) NSNumber * identifier;
@property(nonatomic, retain) NSString * name;

@end
