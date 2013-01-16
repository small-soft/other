#import "AMObjectMappingDelegate.h"

@interface AMCUDResult : NSObject <AMObjectMappingDelegate> {
  NSString * resultCode;
  BOOL success;
}

@property(nonatomic, retain) NSString * resultCode;
@property(nonatomic) BOOL success;

@end
