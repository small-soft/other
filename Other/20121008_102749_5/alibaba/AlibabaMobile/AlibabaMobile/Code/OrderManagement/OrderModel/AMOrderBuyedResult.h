//
//  AMOrderBuyedResult.h
//  AlibabaMobile
//
//  Created by 王 晓文 on 12-8-30.
//
//

#import <Foundation/Foundation.h>
#import "AMObjectMappingDelegate.h"

@interface AMOrderBuyedResult : NSObject <AMObjectMappingDelegate>
{
    NSNumber *_totalCount;
    NSNumber *_page;
    NSNumber *_curPageCount;
    NSNumber *_pageSize;
    NSArray *_modelList;
}
@property (nonatomic, retain) NSNumber *totalCount;
@property (nonatomic, retain) NSNumber *page;
@property (nonatomic, retain) NSNumber *curPageCount;
@property (nonatomic, retain) NSNumber *pageSize;
@property (nonatomic, retain) NSArray *modelList;
@end
