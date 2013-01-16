
/**
 * Simple Money
 * 
 * @author qizhi.tangqz
 */
#import "AMObjectMappingDelegate.h"

@class AMCurrency;

@interface AMMoney : NSObject <AMObjectMappingDelegate> {
    /**
     * 金额，以元为单位，。
     */
    NSNumber * _amount;
    
    /**
     * 金额，以分为单位。
     */
    NSNumber * _cent;
    
    /**
     * 币种
     */
    NSString * _currencyCode;
    
    /**
     * 货币对象
     */
    AMCurrency * _currency;
    
}

@property(nonatomic, retain) NSNumber * amount;
@property(nonatomic, retain) NSNumber * cent;
@property(nonatomic, retain) NSString * currencyCode;
@property(nonatomic, retain) AMCurrency * currency;

@end
