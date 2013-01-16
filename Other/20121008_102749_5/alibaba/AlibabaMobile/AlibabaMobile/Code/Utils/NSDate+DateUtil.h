//
//  NSDate+DateUtil.h
//  AlibabaMobile
//
//  Created by 佳 刘 on 12-8-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSDate (DateUtil)

- (int) year;
- (int) month;
- (int) day;

// 可以取得日期的年月日时分秒的集合
- (NSDateComponents *) components;
// 格式化日期，template如@"yyyy-MM-dd HH:mm:ss"
- (NSString *) formate:(NSString *)template;
@end
