//
//  NSDate+DateUtil.m
//  AlibabaMobile
//
//  Created by 佳 刘 on 12-8-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "NSDate+DateUtil.h"

@implementation NSDate (DateUtil)

- (NSDateComponents *)components {
    NSCalendar *calendar = [[[NSCalendar alloc] initWithCalendarIdentifier:NSGregorianCalendar]autorelease]; 
    
    NSInteger unitFlags = NSYearCalendarUnit | NSMonthCalendarUnit | NSDayCalendarUnit | NSWeekdayCalendarUnit |  
    NSHourCalendarUnit | NSMinuteCalendarUnit | NSSecondCalendarUnit;  
    
    return [calendar components:unitFlags fromDate:self];
}

- (int)year {
    return [self components].year;
}

- (int)month {
    return [self components].month;
}

- (int)day {
    return [self components].day;
}

- (NSString *)formate:(NSString *)template {
    //实例化一个NSDateFormatter对象
    NSDateFormatter *dateFormatter = [[[NSDateFormatter alloc] init]autorelease];
    //设定时间格式,这里可以设置成自己需要的格式
    [dateFormatter setDateFormat:template];
    //用[NSDate date]可以获取系统当前时间
    return [dateFormatter stringFromDate:self];
}

@end
