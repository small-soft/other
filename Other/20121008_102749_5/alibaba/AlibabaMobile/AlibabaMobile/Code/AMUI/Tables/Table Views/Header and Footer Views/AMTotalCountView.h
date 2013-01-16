//
//  AMTotalCountView.h
//  AlibabaMobile
//
//  Created by  on 12-7-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface AMTotalCountView : UIView {
    UILabel *_totalCountResultLabel;
}
- (void)setTotalCount:(int)totalCount;
@end